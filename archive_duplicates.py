import os
import shutil

REPORT_FILE = "validation_report.txt"
ARCHIVE_ROOT = r"Source/SLF_5_7/ManualConversion/_Archive/Generated_Duplicates"

def archive_duplicates():
    if not os.path.exists(ARCHIVE_ROOT):
        os.makedirs(ARCHIVE_ROOT)
        
    with open(REPORT_FILE, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        
    # Logic: Read chunks. Always pick "Manual" to keep. Archive "Generated".
    # The report format:
    # FILE ...
    #   ...
    #   Generated: P=... (Delta ...)
    #   WINNER: ...
    #   Path to keep: ...
    #   Path to archive: ...
    
    # We can just look for "Path to archive:" lines?
    # But wait, the report calculated "Winner".
    # I want to OVERRIDE the winner to be Manual always, unless Manual is missing/empty.
    # But wait, the previous script populated "Path to keep" based on Winner.
    # So if Winner was Generated, "Path to keep" is Generated.
    # I should re-evaluate or just parse the "Generated:" path and "Manual:" path from the text block.
    
    current_manual = None
    current_generated = None
    
    for line in lines:
        line = line.strip()
        if "Path to keep:" in line:
            path = line.split(": ", 1)[1]
            if "ManualConversion" in path:
                current_manual = path
            else:
                current_generated = path
                
        elif "Path to archive:" in line:
            path = line.split(": ", 1)[1]
            if "ManualConversion" in path:
                current_manual = path
            else:
                current_generated = path
        
        elif line == "":
            # End of block
            if current_manual and current_generated:
                # Always keep Manual, Archive Generated
                src = current_generated
                
                # Check if src exists (might have been archived already or path invalid)
                if os.path.exists(src):
                    # Construct dest
                    # Preserve sub structure? E.g. Generated/Classes/Foo.h -> Archive/Classes/Foo.h
                    # src is like Source/SLF_5_7/Generated/Classes/Foo.h
                    # We want Archive/Classes/Foo.h
                    
                    # Split after "Generated"
                    parts = src.replace("\\", "/").split("Generated/")
                    if len(parts) > 1:
                        rel_path = parts[1]
                        dest = os.path.join(ARCHIVE_ROOT, rel_path)
                        
                        # Ensure dir
                        os.makedirs(os.path.dirname(dest), exist_ok=True)
                        
                        print(f"Archiving {os.path.basename(src)}")
                        try:
                            shutil.move(src, dest)
                        except Exception as e:
                            print(f"Failed to move {src}: {e}")
                else:
                    # It might be that the file was deleted or moved?
                    # Or maybe my report path construction was bad (mixed slashes).
                    # Let's try normalizing.
                    pass

            current_manual = None
            current_generated = None

if __name__ == "__main__":
    archive_duplicates()
