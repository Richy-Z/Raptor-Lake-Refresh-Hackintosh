#define P_CORE_MAX_COUNT 32
#define E_CORE_MAX_COUNT 64

#include "CpuTopologyRebuild.h"
#include <i386/cpu_topology.h>
#include <Headers/kern_api.hpp>
#include <Headers/kern_patcher.hpp>
#include <Headers/kern_version.hpp>

OSDefineMetaClassAndStructors(CpuTopologyRebuild, IOService)

bool ADDPR(debugEnabled) = true;
uint32_t ADDPR(debugPrintDelay) = 0;

bool smt_spoof = false;
x86_lcpu_t *p0_cpus[P_CORE_MAX_COUNT]; // P-Cores
x86_lcpu_t *p1_cpus[P_CORE_MAX_COUNT]; // P-Cores HT
x86_lcpu_t *e0_cpus[E_CORE_MAX_COUNT]; // E-Cores
int p0_count, p1_count, e0_count;
int e_core_first = -1;

extern "C" void x86_validate_topology(void);

static void print_cache_info(x86_cpu_cache_t *cache) {
    x86_lcpu_t *cpu;

    const char *cache_name;
    if (cache->type == 1) {
        cache_name = "L1D";
    } else if (cache->type == 2) {
        cache_name = "L1I";
    } else if (cache->level == 2) {
        cache_name = "L2";
    } else {
        cache_name = "LLC";
    }

    char buf[5];
    char lcpus[256];
    lcpus[0] = '\0';
    int i = 0;
    cpu = cache->cpus[i];
    while (cpu != nullptr) {
        snprintf(buf, 5, "%d,", cpu->pnum);
        strlcat(lcpus, buf, 256);
        cpu = cache->cpus[++i];
    }

    DBGLOG("ctr", "  %s/type=%d/level=%d/%dKB/maxcpus=%d/nlcpus=%d/lcpus=%s",
        cache_name, cache->type, cache->level, cache->cache_size / 1024, cache->maxcpus, cache->nlcpus, lcpus);
}

static void print_cache_topology(void) {
    x86_pkg_t  *pkg = x86_pkgs;
    x86_lcpu_t *cpu;
    x86_cpu_cache_t *cache;
    x86_cpu_cache_t *caches[256];
    int cache_count = 0;

    DBGLOG("ctr", "Cache info:");
    for (int i = 2; i >= 0; --i) { // LLC->L2->L1
        cpu = pkg->lcpus;
        while (cpu != nullptr) {
            cache = cpu->caches[i];
            bool new_cache = true;
            for (int j = 0; j < cache_count; ++j) {
                if (cache == caches[j]) {
                    new_cache = false;
                    break;
                }
            }
            if (new_cache) {
                print_cache_info(cache);
                caches[cache_count++] = cache;
            }
            cpu = cpu->next_in_pkg;
        }
    }
}

static void print_cpu_topology(void) {
    x86_pkg_t  *pkg = x86_pkgs;
    x86_core_t *core;
    x86_lcpu_t *cpu;

    DBGLOG("ctr", "CPU: physical_cpu_max=%d, logical_cpu_max=%d", machine_info.physical_cpu_max, machine_info.logical_cpu_max);
    core = pkg->cores;
    while (core != nullptr) {
        DBGLOG("ctr", "  Core(p/l): %d/%d (lcpus: %d)", core->pcore_num, core->lcore_num, core->num_lcpus);
        cpu = core->lcpus;
        while (cpu != nullptr) {
            const char *type = cpu->pnum < e_core_first ? (cpu->pnum % 2 == 0 ? "P0" : "P1") : "E0";
            DBGLOG("ctr", "    LCPU_%s(n/p/l): %2d/%2d/%d", type, cpu->cpu_num, cpu->pnum, cpu->lnum);
            cpu = cpu->next_in_core;
        }
        core = core->next_in_pkg;
    }
}

static void load_cpus(void) {
    x86_pkg_t  *pkg = x86_pkgs;
    x86_lcpu_t *cpu;
    x86_lcpu_t *cpus_reverse[P_CORE_MAX_COUNT * 2 + E_CORE_MAX_COUNT];
    int count = 0;

    p0_count = p1_count = e0_count = 0;

    cpu = pkg->lcpus;
    while (cpu != nullptr) {
        cpus_reverse[count++] = cpu;
        if (e_core_first == -1 || e_core_first - cpu->pnum == 2) {
            e_core_first = cpu->pnum;
        }
        cpu = cpu->next_in_pkg;
    }
    for (int i = 0; i < count; ++i) {
        cpu = cpus_reverse[count - 1 - i];
        if (cpu->pnum < e_core_first) { // P-Core
            if (cpu->pnum % 2 == 0) { // primary
                p0_cpus[p0_count++] = cpu;
            } else { // HT core
                p1_cpus[p1_count++] = cpu;
            }
        } else { // E-Core
            e0_cpus[e0_count++] = cpu;
        }
    }

    if (p1_count == 0) {
        smt_spoof = true;
    }
}

static void rebuild_cache_topology(void) {
    x86_lcpu_t *cpu;
    x86_cpu_cache_t *l1;
    x86_cpu_cache_t *l2;

    // E-Core fix
    x86_lcpu_t *e_primary;

    for (int i = 0; i < (e0_count / 4); ++i) {
        e_primary = e0_cpus[i * 4];
        e_primary->caches[0]->cache_size = 64 * 1024; // 64KB
        l2 = e_primary->caches[1];
        l2->cache_size = 2 * 1024 * 1024; // 2MB
        for (int j = 1; j < 4; ++j) {
            cpu = e0_cpus[i * 4 + j];
            cpu->caches[0]->cache_size = 64 * 1024; // 64KB
            cpu->caches[1] = l2;
            l2->cpus[j] = cpu;
            l2->nlcpus++;
        }
    }

    // P-Core HTT fix
    x86_lcpu_t *p0;
    x86_lcpu_t *p1;

    for (int i = 0; i < p1_count; ++i) {
        p0 = p0_cpus[i];
        p1 = p1_cpus[i];
        l1 = p0->caches[0];
        l2 = p0->caches[1];

        p1->caches[0] = l1;
        p1->caches[1] = l2;

        l1->nlcpus = l2->nlcpus = 2;
        l1->cpus[1] = l2->cpus[1] = p1;
    }
}

static void setClusterProperty(x86_lcpu_t *cpu, int cluster) {
    cpu->setProperty("Cluster", OSString::withCString(std::to_string(cluster).c_str()));
}

static void rebuild_cluster_topology(void) {
    x86_lcpu_t *cpu;

    // Original performance core handling with added cluster support
    for (int i = 0; i < p0_count; ++i) {
        cpu = p0_cpus[i];
        cpu->lnum = 0;

        // Determine cluster based on index
        int cluster = (i < p0_count / 2) ? 1 : 2;

        // Modify the behavior for Performance Cores in Cluster 1
        if (cluster == 1) {
            setClusterProperty(cpu, 1);
        }

        cpu->core->cluster_num = cluster;
        cpu->core->lcore_num = cpu->core->pcore_num = i;
        cpu->core->num_lcpus = 1;
        cpu->core->lcpus = cpu;

        if (i != 0) {
            cpu->core->next_in_pkg = cpu->core->next_in_die = p0_cpus[i - 1]->core;
        }
    }

    // Efficiency core handling with added cluster support
    for (int i = 0; i < e0_count; ++i) {
        cpu = e0_cpus[i];

        // Determine cluster for efficiency cores (always Cluster 2)
        int cluster = 2;

        // Modify the behavior for Efficiency Cores in Cluster 2
        setClusterProperty(cpu, 2);

        cpu->lnum = 0;
        cpu->core->cluster_num = cluster;
        cpu->core->lcore_num = cpu->core->pcore_num = p0_count + i;
        cpu->core->num_lcpus = 1;
        cpu->core->lcpus = cpu;

        if (i != 0) {
            cpu->core->next_in_pkg = cpu->core->next_in_die = e0_cpus[i - 1]->core;
        }
    }
}

static void rebuild_cpu_topology(void) {
    // do nothing if E-Cores disabled
    if (e0_count == 0) return;

    x86_pkg_t  *pkg = x86_pkgs;
    x86_die_t  *die = pkg->dies;
    x86_core_t *core;
    x86_lcpu_t *cpu;

    x86_core_t *p_core_last = p0_cpus[p0_count - 1]->core;

    if (smt_spoof) {
        pkg->cores = die->cores = p_core_last;
        die->num_cores = p0_count;
        machine_info.physical_cpu_max = p0_count;
    } else {
        core = e0_cpus[0]->core;
        core->next_in_die = core->next_in_pkg = p_core_last;
        die->num_cores = p0_count + e0_count;
        machine_info.physical_cpu_max = p0_count + e0_count;
    }

    // Original performance core handling with added cluster support
    for (int i = 0; i < p0_count; ++i) {
        cpu = p0_cpus[i];
        cpu->lnum = 0;
        core = cpu->core;

        // Determine cluster based on index
        int cluster = (i < p0_count / 2) ? 1 : 2;

        // Modify the behavior for Performance Cores in Cluster 1
        if (cluster == 1) {
            setClusterProperty(cpu, 1);
        }

        core->cluster_num = cluster;
        core->lcore_num = core->pcore_num = i;
        core->num_lcpus = 1;
        core->lcpus = cpu;

        if (i != 0) {
            core->next_in_pkg = core->next_in_die = p0_cpus[i - 1]->core;
        }
    }

    // Hyper-Threaded core handling with added cluster support
    for (int i = 0; i < p1_count; ++i) {
        cpu = p1_cpus[i];
        core = p0_cpus[i]->core;

        // Modify the behavior for Hyper-Threaded Cores in Cluster 1
        setClusterProperty(cpu, 1);

        cpu->lnum = core->num_lcpus++;
        cpu->core = core;
        cpu->next_in_core = core->lcpus;
        core->lcpus = cpu;
    }

    // Efficiency core handling with added cluster support
    rebuild_cluster_topology();
}

void my_x86_validate_topology(void) {
    load_cpus();
    DBGLOG("ctr", "---- CPU/Cache topology before rebuild ----");
    print_cpu_topology();
    print_cache_topology();
    rebuild_cpu_topology();
    DBGLOG("ctr", "---- CPU/Cache topology after rebuild ----");
    print_cpu_topology();
    print_cache_topology();
    // FunctionCast(my_x86_validate_topology, org_x86_validate_topology)(); // skip topology validation
}

IOService *CpuTopologyRebuild::probe(IOService *provider, SInt32 *score) {
    if (!IOService::probe(provider, score)) return nullptr;
    if (!provider) return nullptr;

    OSNumber *cpuNumber = OSDynamicCast(OSNumber, provider->getProperty("processor-index"));
    if (!cpuNumber || cpuNumber->unsigned32BitValue() != 0) return nullptr;

    static bool done = false;
    if (!done) {
        lilu_get_boot_args("liludelay", &ADDPR(debugPrintDelay), sizeof(ADDPR(debugPrintDelay)));
        ADDPR(debugEnabled) = checkKernelArgument("-ctrdbg") || checkKernelArgument("-liludbgall");
        smt_spoof = checkKernelArgument("-ctrsmt");

        done = true;

        uint8_t patchData[6 + sizeof(uintptr_t)] = {0xFF, 0x25};

        void (*fn)(void) = my_x86_validate_topology;
        lilu_os_memcpy(&patchData[6], &fn, sizeof(fn));

        if (UNLIKELY(MachInfo::setKernelWriting(true, KernelPatcher::kernelWriteLock) != KERN_SUCCESS)) {
            SYSLOG("ctr", "failed to obtain write permissions for f/r");
            return nullptr;
        }

        lilu_os_memcpy((void *)x86_validate_topology, patchData, sizeof(patchData));

        if (UNLIKELY(MachInfo::setKernelWriting(false, KernelPatcher::kernelWriteLock) != KERN_SUCCESS)) {
            SYSLOG("ctr", "failed to restore write permissions for f/r");
        }

        setProperty("VersionInfo", kextVersion);
        return this;
    }

    return nullptr;
}
