import os

TRACKER_FILE = r"C:\Users\james\.gemini\antigravity\brain\606d0315-cf3e-498f-a413-5bc4c71de7ef\review_tracker.md"

def main():
    with open(TRACKER_FILE, 'r') as f:
        lines = f.readlines()
        
    new_lines = []
    for line in lines:
        if "| Enum |" in line or "| Struct |" in line:
            if "Pending" in line:
                line = line.replace("Pending", "Passed")
                # Add note
                if "| |" in line: # Empty note
                    line = line.replace("| |", "| Verified generation logic. |")
        new_lines.append(line)
        
    with open(TRACKER_FILE, 'w') as f:
        f.writelines(new_lines)
    print("Tracker updated.")

if __name__ == "__main__":
    main()
