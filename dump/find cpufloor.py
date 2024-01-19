import os
import plistlib

def find_plists_with_threshold(directory, threshold):
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
                    and "CPUFloor" in plist_data["IOPlatformPowerProfile"]
                    and plist_data["IOPlatformPowerProfile"]["CPUFloor"] == threshold
                ):
                    matching_plists.append(plist_path)

    return matching_plists

# Replace 'your_directory_path' with the path to your directory containing plist files
directory_path = '/Users/richyz./Desktop/X86-CPU-Management-Mac_BoardID/'
threshold_value = 1200

matching_files = find_plists_with_threshold(directory_path, threshold_value)

if matching_files:
    print("Plists with IOPlatformPowerProfile.CPUFloor equal to", threshold_value, ":", matching_files)
else:
    print("No matching plists found.")
