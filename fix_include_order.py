import os
import re

SOURCE_ROOT = r"Source/SLF_5_7"

def fix_include_order():
    print(f"Scanning {SOURCE_ROOT} for include order issues...")
    
    count = 0
    generated_include_pattern = re.compile(r'^\s*#include\s+"([^"]+\.generated\.h)"')
    other_include_pattern = re.compile(r'^\s*#include\s+"([^"]+)"\s*$')
    # Use a simpler check for ANY include
    any_include_pattern = re.compile(r'^\s*#include\s+')
    
    for root, _, files in os.walk(SOURCE_ROOT):
        for filename in files:
            if not filename.endswith(".h"):
                continue
                
            filepath = os.path.join(root, filename)
            
            with open(filepath, 'r', encoding='utf-8') as f:
                lines = f.readlines()
                
            # 1. Locate the .generated.h include
            generated_idx = -1
            for i, line in enumerate(lines):
                if generated_include_pattern.search(line):
                    generated_idx = i
                    break
            
            if generated_idx == -1:
                continue # No generated header, skip
                
            # 2. Check for includes AFTER the generated header
            moved_includes = []
            new_lines = []
            
            # Keep lines up to generated header
            for i in range(generated_idx):
                new_lines.append(lines[i])
                
            # Now process the rest
            post_generated_lines = lines[generated_idx+1:]
            
            deferred_includes = []
            final_code_lines = []
            
            for line in post_generated_lines:
                if any_include_pattern.match(line):
                    # Found an include after generated!
                    deferred_includes.append(line)
                else:
                    final_code_lines.append(line)
            
            if not deferred_includes:
                continue # No issues found
                
            # Reconstruct file
            # [Pre-Generated Lines]
            # [Moved Includes]
            # [Generated Include]
            # [Rest of file]
            
            # Insert moving includes BEFORE the generated header
            # But wait, lines[generated_idx] IS the generated header line.
            # So:
            
            out_lines = []
            out_lines.extend(lines[:generated_idx]) # Everything before
            out_lines.extend(deferred_includes)     # The bad includes moved up
            out_lines.append(lines[generated_idx])  # The generated include
            out_lines.extend(final_code_lines)      # The rest
            
            print(f"Fixing {filename}: Moved {len(deferred_includes)} includes.")
            
            with open(filepath, 'w', encoding='utf-8') as f:
                f.writelines(out_lines)
            count += 1

    print(f"Done. Fixed {count} files.")

if __name__ == "__main__":
    fix_include_order()
