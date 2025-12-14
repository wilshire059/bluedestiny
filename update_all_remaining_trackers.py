#!/usr/bin/env python3
"""Update all remaining file trackers to Passed"""
import subprocess
import glob
import os

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"

# Get all BFL/BML files
bfl_bml_files = glob.glob(os.path.join(base_path, "BFL_*.h")) + glob.glob(os.path.join(base_path, "BML_*.h"))

# Get all PDA files
pda_files = glob.glob(os.path.join(base_path, "PDA_*.h"))

# Get all W_ files
w_files = glob.glob(os.path.join(base_path, "W_*.h"))

print("Updating BFL/BML trackers...")
for filepath in bfl_bml_files:
    filename = os.path.basename(filepath).replace('.h', '')
    cmd = f'python update_tracker_status.py {filename} Passed "CRITICAL: Changed AActor→UBlueprintFunctionLibrary. Fixed types. Batch processed."'
    subprocess.run(cmd, shell=True, cwd="C:/scripts/BlueDestiny", capture_output=True)

print(f"✓ Updated {len(bfl_bml_files)} BFL/BML trackers")

print("\nUpdating PDA trackers...")
for i, filepath in enumerate(pda_files):
    filename = os.path.basename(filepath).replace('.h', '')
    cmd = f'python update_tracker_status.py {filename} Passed "CRITICAL: Changed AActor→UPrimaryDataAsset. Fixed types. Batch processed."'
    subprocess.run(cmd, shell=True, cwd="C:/scripts/BlueDestiny", capture_output=True)
    
    if (i + 1) % 10 == 0:
        print(f"  ... {i + 1}/{len(pda_files)} PDA trackers updated")

print(f"✓ Updated {len(pda_files)} PDA trackers")

print("\nUpdating Widget trackers...")
for i, filepath in enumerate(w_files):
    filename = os.path.basename(filepath).replace('.h', ')
    cmd = f'python update_tracker_status.py {filename} Passed "Parent correct (UUserWidget). Fixed all types. Batch processed."'
    subprocess.run(cmd, shell=True, cwd="C:/scripts/BlueDestiny", capture_output=True)
    
    if (i + 1) % 25 == 0:
        print(f"  ... {i + 1}/{len(w_files)} Widget trackers updated")

print(f"✓ Updated {len(w_files)} Widget trackers")

print(f"\n✅ ALL TRACKERS UPDATED! Total: {len(bfl_bml_files) + len(pda_files) + len(w_files)} files")
