# 🔌 USB Mapping
Mapping USB on my motherboard was absolute HELL. I've noticed that a few months ago a new BIOS build was released which completely altered the original USB map, and the new configuration is ***really, really weird***.

## 💡 Mapping Notes
USB 3 ports (physical / hardware ports) have two personalities (software ports), one for USB 3 itself and one for USB 2 compatibility.

Do note that those two personalities are *companions* to eachother, and should be of the same type. (e.g. the USB 2 personality of a physical USB 3 port should still have type `3` for USB 3 Type A, and not type `0` for USB 2 Type A).

I had to find that out by looking at the source code of USBToolBox, lol. It's good the open source code exists!

## 🔨 USB Port Declarations for my system
### ASMedia USB 3.1 eXtensible Host Controller
| Accumulative Personality Index | Controller Index | Type | Physical Port                                      | USB Personality         | Notes |
|-------------------|------------------|------|----------------------------------------------------|-------------------------|-|
| 1                 | 1                | 3    | Motherboard -> Top -> USB 3 10G Ports -> **Right** | USB ***3*** Personality | |
| 2                 | 2                | 3    | Motherboard -> Top -> USB 3 10G Ports -> **Left**  | USB ***3*** Personality | |
| 3                 | 3                | 3    | Motherboard -> Top -> USB 3 10G Ports -> **Right** | USB ***2*** Personality | |
| 4                 | 4                | 3    | Motherboard -> Top -> USB 3 10G Ports -> **Left**  | USB ***2*** Personality | |

### Intel(R) USB 3.20 eXtensible Host Controller
| Accumulative sPersonality Index | Controller Index | Type | Physical Port                                      | USB Personality         | Notes |
|-------------------|------------------|------|----------------------------------------------------|-------------------------|-|
| 1                 | 1                | 3    | Motherboard -> Top -> USB 3 10G Ports -> **Right** | USB ***3*** Personality | |
| 2                 | 2                | 3    | Motherboard -> Top -> USB 3 10G Ports -> **Left**  | USB ***3*** Personality | |
| 3                 | 3                | 3    | Motherboard -> Top -> USB 3 10G Ports -> **Right** | USB ***2*** Personality | |
| 4                 | 4                | 3    | Motherboard -> Top -> USB 3 10G Ports -> **Left**  | USB ***2*** Personality | |

# PLACEHOLDER - Will edit later
Indexes mentioned hereupon are controller indexes, not the accumulative personality index.

## Mapping attempt 1 - Horrible
Intel USB Controller:
18 - Type C without switch, 19 is companion
19 - Type C without switch

25 - Case USB 3.0 Both ports

6 - MB Top USB 2 Left

5 - MB Top USB 2 Right

24 - MB Middle USB 3 5G

17 - MB Middle Type C 20G with switch

10 - no fucking clue. this motherboard's usb declarations are so messed up. the physical port is usb 3 but it seems like a usb 2 hub. 

9 - usb 2?

## Mapping attempt 2 - ASMedia Controller disabled
For some reason I thought that disabling the ASMedia Controller in the BIOS would alleviate the inconsistencies with this motherboard during mapping. It, in fact, did not.

25 - USB 3

10 - usb 2

## Mapping attempt 3 - Proper mapping
*omittable* - Can be completely ignored and not mapped due to the limited functions it provides within macOS. Good for freeing up the limited amount of ports.

### 1. Miscellaneous personality detection (Internal software ports)
**Intel**

*omittable* 2 - Type 255, Motherboard AURA LED Controller

*omittable* 4 - Type 255, Corsair Elite LCD Water Cooler LCD Cap

8 - Type 255, Fenvi T919 WiFi & Bluetooth

*omittable* 11 - Type 255, Corsair iCUE Commander Core

### 2. USB 3 / 4 Personality Detection
**ASMedia**

2 - Type 3, Motherboard Top USB 3 10G Left

1 - Type 3, Motherboard Top USB 3 10G Right



**Intel**

18 - Type C without switch, Case Type C, Companion to 19

19 - Type C without switch, Case Type C, Companion to 18

25 - Type 3, Case Left USB 3

25 - Type 3, Case Right USB 3

6 - Type 0, Motherboard Top USB 2 Left

5 - Type 0, Motherboard Top USB 2 Right

24 - Type 3, Motherboard Middle USB 3 5G

17 - Type C with switch, Motherboard Middle Type C 20G

25 - Type 3, Motherboard Bottom USB 3 5G Left

25 - Type 3, Motherboard Bottom USB 3 5G Right

### 3. USB 2 Compatibility Personality Detection
**ASMedia**

4 - Type 3, Motherboard Top USB 3 10G Left

3 - Type 3, Motherboard Top USB 3 10G Right

**Intel**

3 - Type C with switch, Case Type C

- Remember that although this is the USB 2 compatibility personality of the Type C port on my case, it must still be marked as a regular Type C with switch (USB 3), and not Type C USB 2.0 only.

10 - Type 3, Case Left USB 3

10 - Type 3, Case Right USB 3

9 - Type 3, Motherboard Middle USB 3 5G

1 - Type C with switch, Motherboard Middle Type C 20G

10 - Type 3, Motherboard Bottom USB 3 5G Left

10 - Type 3, Motherboard Bottom USB 3 5G Right

- Remember that although this is the USB 2 compatibility personality of the Type C port on my case, it must still be marked as a regular Type C with switch (USB 3), and not Type C USB 2.0 only.

### 4. USB Controller Load Balancing Detection
After a BIOS update, it looks like Asus has implemented USB controller load balancing for my motherboard which essentially distributes the load of MANY (literally all USB ports plugged in) across various personalities and hubs, etc, notably ones that we didnt even discover in steps 2 or 3.

Therefore, this steps ensures that we are not missing out on any "worst case scenario" personalities which were otherwise hidden without every physical USB port having something plugged in.

Ive noticed this feature in some BIOS before version 1646, but as of 1656 it does not look like thsi feature is present anymore. Either way, its a good idea to check this when you are mapping your USB ports on your system.