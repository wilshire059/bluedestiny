import os
import shutil
import glob

ROOT_DIR = r"Source/SLF_5_7/ManualConversion"
MOVES = {
    "ControlRig": ["CR_*.cpp", "CR_*.h"],
    "CameraShakes": ["CS_*.cpp", "CS_*.h"],
    "SaveSystem": ["SG_*.cpp", "SG_*.h"]
}

def cleanup():
    # Ensure dirs
    for folder in MOVES.keys():
        path = os.path.join(ROOT_DIR, folder)
        if not os.path.exists(path):
            os.makedirs(path)
            print(f"Created {path}")

    # Move files
    for folder, patterns in MOVES.items():
        for pattern in patterns:
            full_pattern = os.path.join(ROOT_DIR, pattern)
            files = glob.glob(full_pattern)
            for f in files:
                filename = os.path.basename(f)
                dest = os.path.join(ROOT_DIR, folder, filename)
                print(f"Moving {filename} -> {folder}/")
                shutil.move(f, dest)

if __name__ == "__main__":
    cleanup()
