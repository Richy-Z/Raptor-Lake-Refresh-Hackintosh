# 🔌 USBX Device Creation
The SSDT-USBX.aml provided [here](https://github.com/dortania/OpenCore-Post-Install/blob/master/extra-files/SSDT-USBX.aml) creates an ACPI device named USBX and then creates a method to only enable it in Darwin (macOS) and disable it for everything else.
```dsl
/*
 * Original
 */
DefinitionBlock ("", "SSDT", 2, "DRTNIA", "SsdtUsbx", 0x00001000)
{
    Scope (\_SB)
    {
        Device (USBX)
        {
            Name (_ADR, Zero)  // _ADR: Address
            Method (_DSM, 4, NotSerialized)  // _DSM: Device-Specific Method
            {
                If ((Arg2 == Zero))
                {
                    Return (Buffer (One)
                    {
                         0x03                                             // .
                    })
                }

                Return (Package (0x08)
                {
                    "kUSBSleepPowerSupply", 
                    0x13EC, 
                    "kUSBSleepPortCurrentLimit", 
                    0x0834, 
                    "kUSBWakePowerSupply", 
                    0x13EC, 
                    "kUSBWakePortCurrentLimit", 
                    0x0834
                })
            }

            Method (_STA, 0, NotSerialized)  // _STA: Status
            {
                If (_OSI ("Darwin"))
                {
                    Return (0x0F)
                }
                Else
                {
                    Return (Zero)
                }
            }
        }
    }
}
```

However, wouldn't this be better?
```dsl
/*
 * Modified
 */
DefinitionBlock ("", "SSDT", 2, "DRTNIA", "SsdtUsbx", 0x00001000)
{
    Scope (\_SB)
    {
        If (_OSI ("Darwin"))
        {
            Device (USBX)
            {
                Name (_ADR, Zero)  // _ADR: Address
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (0x0F)
                }
                Method (_DSM, 4, NotSerialized)  // _DSM: Device-Specific Method
                {
                    If ((Arg2 == Zero))
                    {
                        Return (Buffer (One)
                        {
                             0x03                                             // .
                        })
                    }

                    Return (Package (0x08)
                    {
                        "kUSBSleepPowerSupply",
                        0x13EC,
                        "kUSBSleepPortCurrentLimit",
                        0x0834,
                        "kUSBWakePowerSupply",
                        0x13EC,
                        "kUSBWakePortCurrentLimit",
                        0x0834
                    })
                }
            }
        }
    }
}
```

This modified code only creates the device in the first place if macOS is detected, unlike the original which creates the device irregardless of whatever OS is present and then simply enables it on macOS.

This is my first time approaching the ASL language so I have a very small question:
Does disabling the device after creation disable it at a hardware level or at a software level?
i.e. If this ACPI patch were to be applied with OpenCore when running on Windows, would the device be visible and present to Windows but simply disabled on a software level, or would it be entirely disabled and not be seen by the OS at all?

If the latter is true, then in either case, the modified code is simply shorter, cleaner, and I guess you could say it is a bit more understandable as the first few lines very clearly declare that this device should only be created on macOS.