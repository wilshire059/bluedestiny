import os
import shutil

# Config
ROOT_DIR = r"Source/SLF_5_7/ManualConversion"
ARCHIVE_DIR = os.path.join(ROOT_DIR, "_Archive")

# Mapping Prefix -> Folder Name
FOLDER_MAP = {
    "AC_": "Components",
    "BPI_": "Interfaces",
    "E_": "Enums",
    "F": "Structs", # Heuristic for files starting with F
    "AN_": "AnimNotifies",
    "ANS_": "AnimNotifies",
    "BFL_": "Libraries",
    "BML_": "Libraries",
    "B_": "Classes",
    "ABP_": "Classes",
    "W_": "Widgets",
    "GM_": "Gamemodes",
    "PC_": "Gamemodes", 
    "GI_": "Gamemodes",
    "GS_": "Gamemodes",
    "PS_": "Gamemodes",
    "PDA_": "DataAssets",
    "EUW_": "EditorUtilities",
    "EUO_": "EditorUtilities",
    "AIC_": "Classes", # Controllers
    "BTS_": "BehaviorTree",
    "BTT_": "BehaviorTree",
    "Ali_": "Interfaces", # Locomotion Interface? Actually might be Library or Interface. "ALI_" probably AnimLayerInterface? Let's check.
    "ALI_": "Interfaces"
}

def ensure_folders():
    if not os.path.exists(ARCHIVE_DIR):
        os.makedirs(ARCHIVE_DIR)
    
    # Create target folders
    unique_folders = set(FOLDER_MAP.values())
    for folder in unique_folders:
        path = os.path.join(ROOT_DIR, folder)
        if not os.path.exists(path):
            os.makedirs(path)

def get_target_folder(filename):
    for prefix, folder in FOLDER_MAP.items():
        if filename.startswith(prefix):
            return folder
    return None

def move_files():
    ensure_folders()
    
    # List files in ROOT not dirs
    files = [f for f in os.listdir(ROOT_DIR) if os.path.isfile(os.path.join(ROOT_DIR, f))]
    
    for filename in files:
        target_folder = get_target_folder(filename)
        if not target_folder:
            print(f"Skipping {filename}: No known category or already root.")
            continue
            
        src = os.path.join(ROOT_DIR, filename)
        dest_dir = os.path.join(ROOT_DIR, target_folder)
        dest = os.path.join(dest_dir, filename)
        
        if os.path.exists(dest):
            # Duplicate handling
            src_stat = os.stat(src)
            dest_stat = os.stat(dest)
            
            # Simple heuristic: Keep Source if it's newer or larger by > 10%? 
            # Or assume Destination (Subfolder) is the "correct" one because we populated it later?
            # In previous steps we saw Classes/ had newer files.
            # So if SUBFOLDER file exists, it's likely the PRIORITY one.
            # We will Archive the ROOT file.
            
            print(f"Duplicate found: {filename} in root and {target_folder}")
            
            # Move ROOT file to Archive
            archive_path = os.path.join(ARCHIVE_DIR, filename)
            if os.path.exists(archive_path):
                 base, ext = os.path.splitext(filename)
                 archive_path = os.path.join(ARCHIVE_DIR, f"{base}_dupe{ext}")
            
            print(f"  -> Archiving root file to {archive_path}")
            shutil.move(src, archive_path)
            
        else:
            # No duplicate, just move
            print(f"Moving {filename} -> {target_folder}/")
            shutil.move(src, dest)

if __name__ == "__main__":
    move_files()
