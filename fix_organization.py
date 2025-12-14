import os
import shutil
import glob

ROOT_DIR = r"Source/SLF_5_7/ManualConversion"

def fix_collisions():
    # 1. Fix ControlRig
    cr_path = os.path.join(ROOT_DIR, "ControlRig")
    if os.path.isfile(cr_path):
        print("Restoring ControlRig file -> CR_Mannequin_BasicFootIK.cpp")
        shutil.move(cr_path, os.path.join(ROOT_DIR, "CR_Mannequin_BasicFootIK.cpp"))
    
    # 2. Fix CameraShakes
    cs_path = os.path.join(ROOT_DIR, "CameraShakes")
    if os.path.isfile(cs_path):
        print("Restoring CameraShakes file -> CS_Boss_Roar.cpp")
        shutil.move(cs_path, os.path.join(ROOT_DIR, "CS_Boss_Roar.cpp"))
        
    # 3. Fix SaveSystem
    ss_path = os.path.join(ROOT_DIR, "SaveSystem")
    if os.path.isfile(ss_path):
        print("Deleting 0-byte SaveSystem file")
        os.remove(ss_path)

def organize_leftovers():
    moves = {
        "ControlRig": ["CR_*.cpp", "CR_*.h"],
        "CameraShakes": ["CS_*.cpp", "CS_*.h"],
        "SaveSystem": ["SG_*.cpp", "SG_*.h"]
    }
    
    for folder, patterns in moves.items():
        dir_path = os.path.join(ROOT_DIR, folder)
        if not os.path.exists(dir_path):
            os.makedirs(dir_path)
            print(f"Created dir: {folder}")
            
        for pattern in patterns:
            full_pattern = os.path.join(ROOT_DIR, pattern)
            files = glob.glob(full_pattern)
            for f in files:
                filename = os.path.basename(f)
                dest = os.path.join(dir_path, filename)
                print(f"Moving {filename} -> {folder}/")
                shutil.move(f, dest)

if __name__ == "__main__":
    fix_collisions()
    organize_leftovers()
