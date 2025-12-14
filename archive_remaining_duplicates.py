import os
import shutil

SOURCE_ROOT = r"Source/SLF_5_7"
GENERATED_DIR = os.path.join(SOURCE_ROOT, "Generated")
MANUAL_DIR = os.path.join(SOURCE_ROOT, "ManualConversion")
ARCHIVE_ROOT = r"_Archive_Duplicates/Generated_Cleanup"

def archive_remaining_dupes():
    if not os.path.exists(GENERATED_DIR):
        print(f"Generated directory not found at {GENERATED_DIR}")
        return

    # 1. Index all files in ManualConversion (filename -> path)
    manual_files = {}
    print("Indexing ManualConversion...")
    for root, _, files in os.walk(MANUAL_DIR):
        for f in files:
            manual_files[f.lower()] = os.path.join(root, f)
            
    # 2. Walk Generated, check for collisions
    print(f"Scanning Generated ({len(manual_files)} manual files indexed)...")
    count = 0
    for root, _, files in os.walk(GENERATED_DIR):
        for f in files:
            if f.lower() in manual_files:
                # Collision found!
                gen_path = os.path.join(root, f)
                man_path = manual_files[f.lower()]
                
                print(f"Duplicate found: {f}")
                print(f"  Manual: {man_path}")
                print(f"  Generated: {gen_path}")
                
                # Archive it
                rel_path = os.path.relpath(gen_path, SOURCE_ROOT) # e.g. Generated/Structs/Foo.h
                archive_path = os.path.join(ARCHIVE_ROOT, rel_path)
                
                os.makedirs(os.path.dirname(archive_path), exist_ok=True)
                try:
                    shutil.move(gen_path, archive_path)
                    print(f"  -> Archived to {archive_path}")
                    count += 1
                except Exception as e:
                    print(f"  -> FAILED to archive: {e}")

    print(f"Done. Archived {count} files.")

if __name__ == "__main__":
    archive_remaining_dupes()
