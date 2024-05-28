# ⚙️ SSDTs required for Raptor Lake
| SSDT          | Function                                                                                                            |
|---------------|---------------------------------------------------------------------------------------------------------------------|
| SSDT-PLUG-ALT | Changes Device objects back to Processor objects for macOS                                                          |
| SSDT-EC-USBX  | Creates fake Embedded Controller for macOS                                                                          |
| SSDT-AWAC     | Fix internal clock for macOS                                                                                        |
| SSDT-USBW     | Fixes USB wakeup issues. Notably an issue where you have to click once to wake macOS then again to wake the screen. |


Remember to check the source code of your SSDTs to ensure that they are ONLY applying patches if it detects that you are using Darwin (macOS). If not, some issues may arise when dual booting Windows and choosing Windows through the OpenCore boot menu, as patches will be applied to windows too which you dont want. 💀