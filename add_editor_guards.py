import os
import re

EDITOR_UTILS_DIR = r"Source/SLF_5_7/ManualConversion/EditorUtilities"

def add_editor_guards():
    """Add #if WITH_EDITOR / #endif guards to all files in EditorUtilities."""
    
    if not os.path.exists(EDITOR_UTILS_DIR):
        print(f"Directory not found: {EDITOR_UTILS_DIR}")
        return
        
    count = 0
    for filename in os.listdir(EDITOR_UTILS_DIR):
        if not (filename.endswith('.h') or filename.endswith('.cpp')):
            continue
            
        filepath = os.path.join(EDITOR_UTILS_DIR, filename)
        
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
            
        # Check if already has WITH_EDITOR guard
        if '#if WITH_EDITOR' in content:
            print(f"Skipping {filename}: Already has WITH_EDITOR guard")
            continue
            
        # For header files: Add guard after #pragma once
        if filename.endswith('.h'):
            # Find #pragma once line
            if '#pragma once' in content:
                content = content.replace('#pragma once', '#pragma once\n\n#if WITH_EDITOR', 1)
                # Add endif at end
                content = content.rstrip() + '\n\n#endif // WITH_EDITOR\n'
            else:
                # No pragma once, add at very beginning
                content = '#if WITH_EDITOR\n\n' + content + '\n\n#endif // WITH_EDITOR\n'
                
        # For cpp files: Add guard at beginning and end
        elif filename.endswith('.cpp'):
            # Add at beginning (after any copyright comments)
            lines = content.split('\n')
            insert_idx = 0
            
            # Skip initial comment block if present
            for i, line in enumerate(lines):
                if line.strip().startswith('//') or line.strip().startswith('/*') or line.strip().startswith('*'):
                    insert_idx = i + 1
                elif line.strip() == '':
                    insert_idx = i + 1
                else:
                    break
                    
            lines.insert(insert_idx, '#if WITH_EDITOR\n')
            content = '\n'.join(lines)
            content = content.rstrip() + '\n\n#endif // WITH_EDITOR\n'
            
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
            
        print(f"Added WITH_EDITOR guard to {filename}")
        count += 1
        
    print(f"Done. Modified {count} files.")

if __name__ == "__main__":
    add_editor_guards()
