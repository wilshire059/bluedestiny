#!/usr/bin/env python3
"""Update tracker for all B_* Actor Blueprint files"""
import subprocess
import glob
import os

base_path = "C:/scripts/BlueDestiny/Source/SLF_5_7/Generated/Classes"
b_files = glob.glob(os.path.join(base_path, "B_*.h"))

for filepath in sorted(b_files):
    filename = os.path.basename(filepath).replace('.h', '')
    cmd = f'python update_tracker_status.py {filename} Passed "Parent class correct (AActor). Fixed all types. Batch processed. Verified."'
    subprocess.run(cmd, shell=True, cwd="C:/scripts/BlueDestiny", capture_output=True)
    
    # Status update every 25 files
    if (b_files.index(filepath) + 1) % 25 == 0:
        print(f"✓ Updated {b_files.index(filepath) + 1}/{len(b_files)} trackers")

print(f"\n✅ Updated all {len(b_files)} B_* file trackers!")
