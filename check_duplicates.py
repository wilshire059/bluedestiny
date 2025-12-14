import os
import collections

def check_duplicates_to_file(list_file, file_type, output_file):
    if not os.path.exists(list_file):
        print(f"File not found: {list_file}")
        return

    with open(list_file, 'r', encoding='utf-8') as f:
        paths = [line.strip() for line in f if line.strip()]

    file_map = collections.defaultdict(list)
    for path in paths:
        filename = os.path.basename(path).lower()
        file_map[filename].append(path)

    with open(output_file, 'a', encoding='utf-8') as out:
        out.write(f"--- Checking {file_type} ---\n")
        duplicates_found = False
        for filename, locations in file_map.items():
            if len(locations) > 1:
                duplicates_found = True
                out.write(f"Duplicate {filename}:\n")
                for loc in locations:
                    out.write(f"  - {loc}\n")
        
        if not duplicates_found:
            out.write("No duplicates found.\n")
        out.write("\n")

if __name__ == "__main__":
    if os.path.exists("duplicates_report.txt"):
        os.remove("duplicates_report.txt")
    
    check_duplicates_to_file("Source/SLF_5_7/headers_list_utf8.txt", "Headers", "duplicates_report.txt")
    check_duplicates_to_file("Source/SLF_5_7/sources_list_utf8.txt", "Sources", "duplicates_report.txt")
