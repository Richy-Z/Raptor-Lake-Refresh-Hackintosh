# 🏃‍♂️ Performance with different SMBIOSes
Please note that the single core and multi core scores are the values provided by the Geekbench 6 benchmark.

Performance actually also varies from SMBIOS! Surprise surprise.

This document outlines the performance gains presented from various configurations in a neat little table.

## MacPro7,1
| CpuTopologyRebuild | `-ctrsmt` Boot Argument | CPUFriend Data Provider | Single | Multi | Metal  | OpenCL | Notes |
|--------------------|-------------------------|-------------------------|--------|-------|--------|--------|-|
| ❌                 | ❌                     | ❌                       | [1807](https://browser.geekbench.com/v6/cpu/6309832)   | [9310](https://browser.geekbench.com/v6/cpu/6309832)  | [224357](https://browser.geekbench.com/v6/compute/2259751) | [124823](https://browser.geekbench.com/v6/compute/2259756) | Base |
| ✅                 | ❌                     | ❌                       | [1709](https://browser.geekbench.com/v6/cpu/6311472) | [10439](https://browser.geekbench.com/v6/cpu/6311472) | ^ | ^ | No difference; this slight increase is just runtime variance. |
| ✅                 | ✅                     | ❌                       | [1722](https://browser.geekbench.com/v6/cpu/6311771) | [11807](https://browser.geekbench.com/v6/cpu/6311771) | [234316](https://browser.geekbench.com/v6/compute/2260508) | [125868](https://browser.geekbench.com/v6/compute/2260515) | Slight performance increase |
| ✅                 | ✅                     | ✅                       | [3135](https://browser.geekbench.com/v6/cpu/6312169) | [21285](https://browser.geekbench.com/v6/cpu/6312169) | [221301](https://browser.geekbench.com/v6/compute/2260620) | [120677](https://browser.geekbench.com/v6/compute/2260627) | |
| ❌                 | ❌                     | ✅                       |        |       |        |        | |
| ✅                 | ❌                     | ✅                       |        |       |        |        | |


## iMacPro1,1
| CpuTopologyRebuild | `-ctrsmt` Boot Argument | CPUFriend Data Provider | Single | Multi | Metal  | OpenCL | Notes |
|--------------------|-------------------------|-------------------------|--------|-------|--------|--------|-|
| ❌                 | ❌                     | ❌                       | | | | | |
| ✅                 | ❌                     | ❌                       | | | | | |
| ✅                 | ✅                     | ❌                       | | | | | |
| ✅                 | ✅                     | ✅                       | [3127](https://browser.geekbench.com/v6/cpu/6312337) | [21466](https://browser.geekbench.com/v6/cpu/6312337) | [219941](https://browser.geekbench.com/v6/compute/2260672) | [121118](https://browser.geekbench.com/v6/compute/2260675) | |
| ❌                 | ❌                     | ✅                       |        |       |        |        | |
| ✅                 | ❌                     | ✅                       |        |       |        |        | |