import os

def delete_duplicates(report_file):
    with open(report_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    current_file = None
    paths = []
    
    # helper to process a group
    def process_group(filename, group_paths):
        # Find the one in the root ManualConversion folder
        # root one will have path like "ManualConversion\B_Door.h"
        # classes one will have "ManualConversion\Classes\B_Door.h"
        
        root_candidate = None
        classes_candidate = None
        
        for p in group_paths:
            # Normalize slashes
            norm_p = p.replace('\\', '/')
            parts = norm_p.split('/')
            
            # If parts is ["ManualConversion", "Filename"], it's root
            if len(parts) == 2 and parts[0] == "ManualConversion":
                root_candidate = p
            elif len(parts) > 2 and parts[1] == "Classes":
                classes_candidate = p
                
        if root_candidate and classes_candidate:
            full_path = os.path.join("Source", "SLF_5_7", root_candidate)
            if os.path.exists(full_path):
                print(f"Deleting stale duplicate: {full_path}")
                os.remove(full_path)
            else:
                 # Check absolute path assumption
                 # The report had relative paths from Source\SLF_5_7 ? 
                 # Wait, check_duplicates.py used read_file_lines from headers_list.txt which had relative lines?
                 # No, headers_list.txt had "ManualConversion\..." 
                 # But my cwd is c:\scripts\BlueDestiny
                 # So path is Source\SLF_5_7\ManualConversion\...
                 # Let's verify path construction.
                 full_path_v2 = os.path.join("Source", "SLF_5_7", root_candidate)
                 if os.path.exists(full_path_v2):
                     print(f"Deleting stale duplicate: {full_path_v2}")
                     os.remove(full_path_v2) 
                 else:
                     print(f"Could not find exact file to delete: {root_candidate} (tried {full_path})")

    for line in lines:
        line = line.strip()
        if line.startswith("Duplicate ") or line.endswith(":"): # "filename:" from find_internal_dupes output
            if current_file and len(paths) > 0:
                process_group(current_file, paths)
            
            current_file = line.strip(":")
            paths = []
        elif line.startswith("- "):
            paths.append(line[2:].strip())

    if current_file and paths:
         process_group(current_file, paths)

if __name__ == "__main__":
    delete_duplicates("internal_dupes.txt")
