import os
import plistlib

def find_plists_with_threshold(directory):
    matching_plists = []
    
    # Iterate through all files in the directory
    for filename in os.listdir(directory):
        if filename.endswith(".plist"):
            plist_path = os.path.join(directory, filename)
            
            # Load the plist file
            with open(plist_path, 'rb') as f:
                plist_data = plistlib.load(f)
                
                # Check if the specified condition is met
                if (
                    "IOPlatformPowerProfile" in plist_data
                    and "ThermalConfiguration" in plist_data["IOPlatformPowerProfile"]
                    and "Domain" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]
                    and "CPU" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]
                    and "ThermalPressure" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]
                    and "Heavy" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]
                    and "HighThreshold" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]["Heavy"]
                    and plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]["Heavy"]["HighThreshold"] == 200
                ) and (
                    "IOPlatformPowerProfile" in plist_data
                    and "ThermalConfiguration" in plist_data["IOPlatformPowerProfile"]
                    and "Domain" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]
                    and "CPU" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]
                    and "ThermalPressure" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]
                    and "Sleeping" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]
                    and "HighThreshold" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]["Sleeping"]
                    and plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]["Sleeping"]["HighThreshold"] == 252
                ) and (
                    "IOPlatformPowerProfile" in plist_data
                    and "Hibernate Mode" in plist_data["IOPlatformPowerProfile"]
                    and plist_data["IOPlatformPowerProfile"]["Hibernate Mode"] == 3
                ) and (
                    "IOPlatformPowerProfile" in plist_data
                    and "NetworkTimerDelay" in plist_data["IOPlatformPowerProfile"]
                    and plist_data["IOPlatformPowerProfile"]["NetworkTimerDelay"] == 900
                ) and (
                    "IOPlatformPowerProfile" in plist_data
                    and "ThermalConfiguration" in plist_data["IOPlatformPowerProfile"]
                    and "Domain" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]
                    and "CPU" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]
                    and "SFIMaintenance" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]
                    and "EffortCurve" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["SFIMaintenance"]
                    and plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["SFIMaintenance"]["EffortCurve"] == "40=0%,80=50%"
                ) and (
                    "IOPlatformPowerProfile" in plist_data
                    and "ThermalConfiguration" in plist_data["IOPlatformPowerProfile"]
                    and "Domain" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]
                    and "CPU" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]
                    and "SFIWindow" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]
                    and plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["SFIWindow"] == 50000
                ) and (
                    "IOPlatformPowerProfile" in plist_data
                    and "ThermalConfiguration" in plist_data["IOPlatformPowerProfile"]
                    and "Domain" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]
                    and "CPU" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]
                    and "QOSThermalThresholds" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]
                    and "NonFocal" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["QOSThermalThresholds"]
                    and "Utility" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["QOSThermalThresholds"]

                    and plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["QOSThermalThresholds"]["NonFocal"] == 250
                    and plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["QOSThermalThresholds"]["Utility"] == 250
                ) and (
                    "IOPlatformPowerProfile" in plist_data
                    and "ThermalConfiguration" in plist_data["IOPlatformPowerProfile"]
                    and "Domain" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]
                    and "CPU" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]
                    and "SFIAppNap" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]
                    and "EffortCurve" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["SFIAppNap"]
                    and plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["SFIAppNap"]["EffortCurve"] == "40=0%,80=50%"
                ) and (
                    "IOPlatformPowerProfile" in plist_data
                    and "ThermalConfiguration" in plist_data["IOPlatformPowerProfile"]
                    and "Domain" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]
                    and "CPU" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]
                    and "ThermalPressure" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]
                    and "Sleeping" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]
                    and "HighThreshold" in plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]["Sleeping"]
                    and plist_data["IOPlatformPowerProfile"]["ThermalConfiguration"]["Domain"]["CPU"]["ThermalPressure"]["Sleeping"]["HighThreshold"] == 252
                ):
                    matching_plists.append(plist_path)

    return matching_plists

# Replace 'your_directory_path' with the path to your directory containing plist files
directory_path = '/Users/richyz./Desktop/X86-CPU-Management-Mac_BoardID/'

matching_files = find_plists_with_threshold(directory_path)

if matching_files:
    print("Plists with HighThreshold equal: ", matching_files)
else:
    print("No matching plists found.")
