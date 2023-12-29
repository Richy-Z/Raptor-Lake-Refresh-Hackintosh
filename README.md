# 🦅 Raptor Lake Refresh Hackintosh with OpenCore
An OpenCore EFI configured for my personal Raptor Lake Refresh (Intel 14th Generation) system.

This Hackintosh is currently a fluke - I don't have much of an idea of how or why this hack even works.

After I changed an unknown BIOS setting or something in config.plist, it randomly decided to boot into the macOS Installer instead of the kernel panicking. I was so relieved but also surprised that I ended up regaining faith in God and started praying - like literally...
> "Thank You God for such a blessed day!"

Because of my lack of knowledge of completely unsupported systems with OpenCore (I only have experience with supported configurations such as an Intel Core i7-10700KF as an example), I will not be providing in-depth explanations here before I conduct a further investigation.

## 🖥️ Specifications
| Component | Name | Key Information | Hackintosh Notes | Hardware Comments |
| --------- | ---- | --------------- | ---------------- | ----------------- |
| 🌍 Motherboard | [ASUS TUF Gaming B760M-Plus](https://www.asus.com/uk/motherboards-components/motherboards/tuf-gaming/tuf-gaming-b760m-plus/techspec/) | B760 Chipset, ALC897, RTL8125 |   | Lovely motherboard! 😍 |
| 🧠 Processor | [Intel Core i9-14900KF](https://ark.intel.com/content/www/us/en/ark/products/236787/intel-core-i9-processor-14900kf-36m-cache-up-to-6-00-ghz.html) | 24 Cores [(8P + 16E)](https://www.intel.com/content/www/us/en/gaming/resources/how-hybrid-design-works.html), 32 Threads| Raptor Lake is not natively supported. Advanced configuration required. | Really powerful - Outperforms M2 Ultra and M3 Max even with non-native support! 💪🏻 |
| 👀 Graphics | [AMD Radeon RX 6900 XT Gaming Z Trio 16GB](https://www.msi.com/Graphics-Card/Radeon-RX-6900-XT-GAMING-Z-TRIO-16G/Specification) | MSI XTXH Variant | Only XTX is supported in macOS - XTXH is not. The device ID has to be spoofed. | Very powerful graphics - Outperforms above. 🤓 |
| 💭 Memory | [Corsair Dominator Titanium RGB 64GB](https://www.corsair.com/uk/en/p/memory/cmp64gx5m4b6400c32/dominator-titanium-rgb-4x16gb-ddr5-dram-6400mt-s-cl32-intel-xmp-memory-kit-cmp64gx5m4b6400c32#tab-techspecs) | DDR5 6400MHz, 4x16GB Configuration, Intel XMP | macOS does not recognise that it is DDR5 - this is purely cosmetic and doesnt affect anything. | Lovely colours with RGB! 🌈 |
| 💾 Storage | [WD_BLACK SN850X 2TB with Heatsink](https://www.westerndigital.com/en-gb/products/internal-drives/wd-black-sn850x-nvme-ssd?sku=WDS200T2XHE) | NVMe SSD, WD In-house controller | I'm not sure if this requires NVMeFix.kext as Apple and Western Digital go well together. | Really fast - up to 7,300MB/s. 🏃🏻💨 |

## ⚙️ BIOS Options
### ❌ Disable
- Fast Boot
- Secure Boot
    - **Secure Boot Mode:** Standard
    - **Secure Boot State:** Setup
    - Key management will turn off with these Secure Boot settings, however, this is required.
- Compatibility Support Module (CSM)
- Discrete Thunderbolt Support
- UEFI Variable Protection
  - This doesn't have to stay disabled - only for Post-Install Configuration.

### ✅ Enable
- VT-d and VT-x (The `DisableIoMapper` quirk **does not** have to be enabled. In fact, disabling VT-d or enabling `DisableIoMapper` actually causes issues.)
  - A long time ago (almost a decade ago), when Hackintoshes were a new thing, someone said that VT-d should be disabled. This is no longer the case however and macOS actually requires it! This false piece of information has stayed with the community, however.
- Above 4G Decoding
  - Resize BAR Support will become available - turn it on too.
- Hyper-Threading
- XHCI Handoff
- OS Type: Other OS
  - Contrary to what the OpenCore Install Guide says, we will set this to "Other OS" to disable Microsoft Secure Boot which isn't required for macOS.

### ℹ️ Other BIOS Settings
- Intel XMP
  - Intel XMP does not cause issues. This can be enabled to enhance the performance of your hack.
- ASUS AI Tweaker (BIOS Automatic Overclocking)
  - For some reason, people believe that overclocking can cause issues. Whilst this may be true on supported systems where power is managed properly, we do not care because we're doing enough spoofing with the CPU already and we need CPUFriend to handle our power management nevertheless. So, maximum performance it will be!
  - *Where exactly is the AI in this lol? It's just a BIOS... I don't expect it to have any AI features. How would you as a BIOS Vendor even implement that, and furthermore, how would American Megatrends implement it lol?*

## 👀 Enabling support for the RX 6900 XT
To be documented.

## 🧠 Fixing support for Raptor Lake (i9-14900KF)
To be documented.
- CPUFriend
- Apple Industry Standard ProcessorType
  - PlatformInfo > Generic > ProcessorType
- CFG Lock
- Spoofing the Processor Name and Type
  - NVRAM >> Add >> 4D1FDA02-38C7-4A6A-9CC6-4BCCA8B30102

## 📜 config.plist Configuration
To be further documented.
### DeviceProperties >> GPU Path
| Name      | Type   | Value                 |
| --------- | ------ | --------------------- |
| device-id | Data   | BF730000              |
| model     | String | AMD Radeon RX 6900 XT |

In [TylerLyczak's Guide for fixing RX 6900 XT support](https://github.com/TylerLyczak/Unsupported-6900XT-Hackintosh-Fix), the model string he set was `Radeon RX 6900 XT (XTXH)`. However, I believe that his model name didn't adhere to Apple's way of product naming.

I watched [MKBHD's MacPro7,1 Unboxing Video](https://www.youtube.com/watch?v=DOPswcaSsu8) and I found out that Apple tends not to include advanced information such as the GPU variant (in our case, `(XTXH)`. Apple is always for simplicity. So I made it `AMD Radeon RX 6900 XT` as that is how Apple would present it.
![Apple Product Naming Explanation](/documentation-assets/AppleProductNamingExplanation.png)
As you can see, Apple only includes the product name and no advanced information. The amount of VRAM is automatically appended by macOS, so we do NOT set this manually in the device model string.

I've also applied the same naming convention to the processor name, see below.

Remember, this is PURELY COSMETIC! So naming here doesn't matter much. I'm just going for the ultimate Apple experience.

### NVRAM >> Add >> 4D1FDA02-38C7-4A6A-9CC6-4BCCA8B30102
| Name       | Type             | Value                 |
| ---------- | ---------------- | --------------------- |
| revcpu     | Number (Integer) | 1                     |
| revcpuname | String           | 24-Core Intel Core i9 |

**Please note:** It is recommended to not go over 20 characters for `revcpuname`. However, I do not think that it matters that much. I've gone over by 1 character to display `24-Core Intel Core i9` and it still displays everything fine without issues.

As you can see here, I've applied the same naming convention to the CPU name as well. I've seen many configurations set the CPU name to be the full product name or a weird mix of everything combined. e.g. `Intel Core i9-14900KF` or even `24-Core Intel i9-14900KF`. I have an issue with both because the presentation of information is very un-Apple-like. Apple tends to go for simplicity and displays only the important information such as core count and the short product name. I **especially** have an issue with the latter, `24-Core Intel i9-14900KF`, because it just seems cursed not to say "Intel Core". Although Intel processors are not Apple's hardware, they are still respectful and display the full trademark name. Woo! Therefore, I have applied the same naming as Apple would have done.

![Screenshot 2023-12-29 at 15 37 24](https://github.com/Richy-Z/Raptor-Lake-Refresh-Hackintosh/assets/64844585/cf292668-0b33-49f4-aaa7-1be959793cb9)


### PlatformInfo >> Generic
| Name          | Type   | Value  |
| ------------- | ------ | ------ |
| ProcessorType | Number | `3841` |

I initially did not know that ProcessorType had to be set manually in order to apply a custom CPU name. Or, more specifically and more likely, because I have an unsupported Raptor Lake Refresh CPU, OpenCore was failing to determine a [ProcessorType](https://github.com/acidanthera/OpenCorePkg/blob/master/Include/Apple/IndustryStandard/AppleSmBios.h) so it defaulted to `0x00`, `AppleProcessorTypeUnknown` which I assume does not support CPU renaming. Hence, macOS was showing "3.18GHz Unknown" regardless of the CPU name I was attempting to set. The unknown will always be unknown!

## 🔐 Fixing CFG Lock on ASUS TUF Gaming B760M-Plus
❗️ **Be careful when modifying your BIOS directly. It can severely break your system!**

ℹ️ UEFI Variable Protection must be disabled in the BIOS.

After that, [instructions from the OpenCore Post-Install Guide](https://dortania.github.io/OpenCore-Post-Install/misc/msr-lock.html) can be followed as-is.


In my case, `VarOffset` was `0x44`. This meant that I had to use the following command in the [Modified GRUB Shell](https://github.com/datasone/grub-mod-setup_var):
```grub
setup_var_cv CpuSetup 0x44 0x01 0x00
```
The command above writes one byte of information, `0x00`, to offset `0x44` in `CpuSetup`.

## 🍉 Numelon Softworks (NSC Information)
The contents of this GitHub repository adhere to the [Numelon Standardisation Convention](https://numelon.com/site-landing/?site=nsc.numelon.com).
