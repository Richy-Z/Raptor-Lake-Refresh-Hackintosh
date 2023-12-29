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
| 👀 Graphics | [AMD Radeon RX 6900 XT Gaming Z Trio 16GB](https://www.msi.com/Graphics-Card/Radeon-RX-6900-XT-GAMING-Z-TRIO-16G/Specification) | MSI XTXH Variant | Only XTX is supported in macOS - XTXH is not. Device ID has to be spoofed. | Very powerful graphics - Outperforms above. 🤓 |
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

### ✅ Enable
- VT-d and VT-x
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
  - Although untested, it should not cause any problems.
  - *Where exactly is the AI in this lol? It's just a BIOS... I dont expect it to have any AI features. How would you as a BIOS Vendor even implement that, and furthermore, how would American Megatrends implement it lol?*

## 🍉 Numelon Softworks (NSC Information)
The contents of this GitHub repository adhere to the [Numelon Standardisation Convention](https://numelon.com/site-landing/?site=nsc.numelon.com).
