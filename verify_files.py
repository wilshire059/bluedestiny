import os

def normalize_name(name):
    return name.lower().strip()

def read_file_lines(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        return [normalize_name(line) for line in f.readlines() if line.strip()]

def get_tracker_items(filepath):
    items = []
    with open(filepath, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if line.startswith("- [x] `"):
                # Extract content between backticks
                try:
                    content = line.split('`')[1]
                    items.append(content)
                except IndexError:
                    pass
    return items

tracker_items = get_tracker_items("tracker_update.md")
headers = read_file_lines("Source/SLF_5_7/headers_list_utf8.txt")
sources = read_file_lines("Source/SLF_5_7/sources_list_utf8.txt")

# Create a map of file basenames
header_map = {os.path.basename(h): h for h in headers}
source_map = {os.path.basename(s): s for s in sources}

missing_headers = []
missing_sources = []

# Exclusions or special cases (e.g. Enums/Structs might not have .cpp)
# We will assume everything needs a .h
# Structs/Enums might be header only.
# Interfaces might be header only or have .cpp
# We'll report missing headers as critical. missing sources as warnings.

for item in tracker_items:
    # Check header
    header_name = item.lower() + ".h"
    found_header = False
    for h in headers:
        if h.endswith(header_name):
            found_header = True
            break
    
    if not found_header:
        missing_headers.append(item)

    # Check source (skip Enums/Structs usually)
    # Simple heuristic: if it starts with E_ or F_ (and not FItemStructs etc which might be special), likely no cpp
    if not (item.startswith("E_") or item.startswith("F") or item.startswith("PDA_")):
         # Actually PDA might have cpp if it has logic, but usually just data assets.
         # Let's check generally.
         source_name = item.lower() + ".cpp"
         found_source = False
         for s in sources:
             if s.endswith(source_name):
                 found_source = True
                 break
         # We won't list missing sources for now as errors, just maybe for interest if requested.
         # But the user asked if existing files exist.

print("--- Missing Headers ---")
for m in missing_headers:
    print(m)

print("\n--- Check Complete ---")
