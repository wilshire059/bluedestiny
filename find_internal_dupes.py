import os

def check_internal_duplicates(report_file):
    with open(report_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    current_file = None
    paths = []
    internal_duplicates = {}

    for line in lines:
        line = line.strip()
        if line.startswith("Duplicate "):
            if current_file and len(paths) > 1:
                # Check if multiple paths start with ManualConversion
                manual_paths = [p for p in paths if p.startswith("ManualConversion")]
                if len(manual_paths) > 1:
                    internal_duplicates[current_file] = manual_paths
            
            current_file = line.split(" ")[1].strip(":")
            paths = []
        elif line.startswith("- "):
            paths.append(line[2:])
    
    # Check last entry
    if current_file and len(paths) > 1:
        manual_paths = [p for p in paths if p.startswith("ManualConversion")]
        if len(manual_paths) > 1:
            internal_duplicates[current_file] = manual_paths

    with open("internal_dupes.txt", "w", encoding="utf-8") as out:
        out.write("--- Internal ManualConversion Duplicates ---\n")
        for filename, locs in internal_duplicates.items():
            out.write(f"{filename}:\n")
            for loc in locs:
                out.write(f"  - {loc}\n")

if __name__ == "__main__":
    check_internal_duplicates("duplicates_report.txt")
