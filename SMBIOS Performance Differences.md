# 🏃‍♂️ Performance with different SMBIOSes
Please note that the single core and multi core scores are the values provided by the Geekbench 6 benchmark.

Performance actually also varies from SMBIOS! Surprise surprise.

This document outlines the performance gains presented from various configurations in a neat little table.

## MacPro7,1
| CpuTopologyRebuild | `-ctrsmt` Boot Argument | CPUFriend Data Provider | Single | Multi | Metal | OpenCL|
|--------------------|-------------------------|-------------------------|--------|-------|-------|-------|
| ❌                 | ❌                     | ❌                     |         |       |       |       |
| ✅                 | ❌                     | ❌                     |         |       |       |       |
| ✅                 | ✅                     | ❌                     |         |       |       |       |
| ✅                 | ✅                     | ✅                     |         |       |       |       |
| ❌                 | ❌                     | ✅                     |         |       |       |       |
| ✅                 | ❌                     | ✅                     |         |       |       |       |

## iMacPro1,1
| CpuTopologyRebuild | `-ctrsmt` Boot Argument | CPUFriend Data Provider | Single | Multi | Metal | OpenCL|
|--------------------|-------------------------|-------------------------|--------|-------|-------|-------|
| ❌                 | ❌                     | ❌                     |         |       |       |       |
| ✅                 | ❌                     | ❌                     |         |       |       |       |
| ✅                 | ✅                     | ❌                     |         |       |       |       |
| ✅                 | ✅                     | ✅                     |         |       |       |       |
| ❌                 | ❌                     | ✅                     |         |       |       |       |
| ✅                 | ❌                     | ✅                     |         |       |       |       |