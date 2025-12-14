import os
import collections

ROOT_DIR = r"Source/SLF_5_7"
GENERATED_DIR = os.path.join(ROOT_DIR, "Generated")
MANUAL_DIR = os.path.join(ROOT_DIR, "ManualConversion")

def find_all_files(directory):
    file_list = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            file_list.append(os.path.join(root, file))
    return file_list

def find_duplicates():
    input_files = find_all_files(MANUAL_DIR)
    generated_files = find_all_files(GENERATED_DIR)
    
    # Map Filename -> Path
    manual_map = {os.path.basename(f).lower(): f for f in input_files}
    generated_map = {os.path.basename(f).lower(): f for f in generated_files}
    
    common_files = set(manual_map.keys()) & set(generated_map.keys())
    
    print(f"Found {len(common_files)} duplicate filenames.")
    
    with open("current_duplicates.txt", "w", encoding="utf-8") as f:
        for filename in sorted(common_files):
            f.write(f"{filename}\n")
            f.write(f"  Manual: {manual_map[filename]}\n")
            f.write(f"  Generated: {generated_map[filename]}\n")

if __name__ == "__main__":
    find_duplicates()
