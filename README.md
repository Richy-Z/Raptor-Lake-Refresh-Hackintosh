# 🦅 Raptor Lake Refresh Hackintosh with OpenCore
An OpenCore EFI configured for my personal Raptor Lake Refresh (Intel 14th Generation) system.

This was quite a pleasant journey and a slight deviation from the ✨ *smooth hacks* ✨ I previously built on widely supported hardware such as the Intel Core i7-10700KF and the B460 motherbooard chipset. That being said, I really enjoyed the challenge of researching and delving deep into my own hardware (and Apple's) in order to get the smoothest, fastest, and most Apple-like experience as an end result.

**⚠️⚠️ This hack is currently in the process of being perfected and polished. The repository will be updated later with a more user-friendly and in-depth guide once a "final" stable configuration has been made.**

ℹ️ A "final" configuration does not mean that this repository will stop receiving updates. It is simply an indicator of the configuration working optimally and smoothly, providing the best Apple-like experience, and with horrendous bugs patched out and no drastic instability issues that affect day to day use of the hack.

### 🐣 The May 2024 revisit of this project
I initially started this project in December of 2023 and possibly used the Hackintosh as a daily driver until around January 2024. I decided to get a taste of Linux again to see how much Wine improved and I was pleasantly surprised! However the lack of support for Adobe products such as Photoshop (and maybe even Roblox purposefully blocking Wine💀) has prompted me to regrettably install the dreaded Windows 11 again.

So I restarted this project in May 2024 to get a fresh taste of macOS again! This time though, Sonoma shall be the chosen one. I specifically stayed on Ventura last time because that is the last version of macOS which supports the `Broadcom BCM94360CD` chip present in my Fenvi T919 card. However, this time I *will* be installing Sonoma because I realised that I was actually missing out on certain software features present in CrossOver. Plus, I don't really care about WiFi anyways since this is a desktop and I use ethernet anyways.

In the initial `README.md` file (December 2023 - January 2024), I said this:
> After I changed an unknown BIOS setting or something in config.plist, it randomly decided to boot into the macOS Installer instead of kernel panicking. I was so relieved and surprised that I ended up regaining faith in God and started praying - like literally...
>> "Thank You God for such a blessed day!"

With the May 2024 revisit of this project, this Hackintosh is no longer a fluke nor a message sent from God. 👼 I know every bit of how and why this hack works. 🤓 Woo!

## 🖥️ Specifications
| Component | Name | Key Information | Hackintosh Notes | Hardware Comments |
| --------- | ---- | --------------- | ---------------- | ----------------- |
| 🌍 Motherboard | [ASUS TUF Gaming B760M-Plus](https://www.asus.com/uk/motherboards-components/motherboards/tuf-gaming/tuf-gaming-b760m-plus/techspec/) | B760 Chipset, ALC897, RTL8125 | Will not boot at all without the `SetupVirtualMap` quirk enabled in config.plist. BIOS Version 1646 and up changes the USB map. | Lovely motherboard! 😍 |
| 🧠 Processor | [Intel Core i9-14900KF](https://ark.intel.com/content/www/us/en/ark/products/236787/intel-core-i9-processor-14900kf-36m-cache-up-to-6-00-ghz.html) | 24 Cores [(8P + 16E)](https://www.intel.com/content/www/us/en/gaming/resources/how-hybrid-design-works.html), 32 Threads| Raptor Lake is not natively supported. Advanced configuration required. | Really powerful - Outperforms M2 Ultra and M3 Max even with non-native support! 💪🏻 |
| 👀 Graphics | [AMD Radeon RX 6900 XT Gaming Z Trio 16GB](https://www.msi.com/Graphics-Card/Radeon-RX-6900-XT-GAMING-Z-TRIO-16G/Specification) | MSI XTXH Variant | Only XTX is supported in macOS - XTXH is not. The device ID has to be spoofed. | Very powerful graphics - Outperforms above. 🤓 |
| 💭 Memory | [Corsair Dominator Titanium RGB 64GB](https://www.corsair.com/uk/en/p/memory/cmp64gx5m4b6400c32/dominator-titanium-rgb-4x16gb-ddr5-dram-6400mt-s-cl32-intel-xmp-memory-kit-cmp64gx5m4b6400c32#tab-techspecs) | DDR5 6600MHz, 4x16GB Configuration, Intel XMP | macOS does not recognise that it is DDR5 - this is purely cosmetic and doesnt affect anything. Also, you won't be able to control RGB from macOS. | Lovely colours with RGB! 🌈 |
| 💾 Storage | [WD_BLACK SN850X 2TB with Heatsink](https://www.westerndigital.com/en-gb/products/internal-drives/wd-black-sn850x-nvme-ssd?sku=WDS200T2XHE) | NVMe SSD, WD In-house controller | I'm not sure if this requires NVMeFix.kext as Apple and Western Digital go well together. | Really fast - up to 7,300MB/s. 🏃🏻💨 |
| 🛜 Wireless | [Fenvi T-919](https://fenvi.com/product_detail_16.html) | Broadcom BCM94360CD | Has native support in macOS up to Ventura (only WiFi and the features depending on that are disabled on Sonoma and up). | Just a regular card 👍🏻 |

### Other components
| Component | Name | Key Information | Hackintosh Notes | Hardware Comments |
| --------- | ---- | --------------- | ---------------- | ----------------- |
| ❄️ CPU Cooler | [Corsair iCUE H100i ELITE LCD XT](https://www.corsair.com/uk/en/p/cpu-coolers/cw-9060074-ww/icue-h100i-elite-lcd-xt-display-liquid-cpu-cooler) | AIO Liquid Cooler, 65.57 CFM, 240mm Radiator | You will not be able to control it from within macOS. Set your settings in Windows and leave it alone. | Keeps the CPU very cool. Idles ranging from 26℃ to 29℃. ☃️ |
| 🪭 Case Fans | [Corsair iCUE AR120 Digital RGB](https://www.corsair.com/uk/en/p/120mm-fans/co-9050167-ww/icue-ar120-digital-rgb-120mm-pwm-fan-triple-pack-co-9050167-ww#tab-techspecs) | 59 CFM, 120mm | This is controlled by the Corsair iCUE Commander Core XT, so you won't be able to control it either from macOS. | They look pretty in the case and circulate air optimally. 🧊 |
| ⛑️ Case | [Asus Prime AP201](https://www.asus.com/uk/motherboards-components/gaming-cases/prime/asus-prime-ap201-tempered-glass-microatx-case/) | microATX, Mini Tower |   | Really easy to work with, given its small size. 👏🏻 |
| ⚡️ Power Supply | [Corsair HX1000 Platinum](https://www.corsair.com/uk/en/p/psu/cp-9020139-uk/hx-series-hx1000-1000-watt-80-plus-platinum-certified-fully-modular-psu-uk-cp-9020139-uk) | 1000W, Fully modular |   | Really efficient and powerful. 🔌 |