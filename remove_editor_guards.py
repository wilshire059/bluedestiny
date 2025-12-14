import os

EDITOR_UTILS_DIR = r"Source/SLF_5_7/ManualConversion/EditorUtilities"

def remove_editor_guards():
    """Remove #if WITH_EDITOR / #endif guards from all files in EditorUtilities."""
    
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
            
        # Check if has WITH_EDITOR guard
        if '#if WITH_EDITOR' not in content:
            continue
            
        # Remove the guards
        # Pattern 1: After #pragma once
        content = content.replace('#pragma once\n\n#if WITH_EDITOR\n', '#pragma once\n')
        content = content.replace('#pragma once\r\n\r\n#if WITH_EDITOR\r\n', '#pragma once\r\n')
        
        # Pattern 2: At start of cpp file
        content = content.replace('#if WITH_EDITOR\n\n', '')
        content = content.replace('#if WITH_EDITOR\r\n\r\n', '')
        content = content.replace('#if WITH_EDITOR\n', '')
        content = content.replace('#if WITH_EDITOR\r\n', '')
        
        # Remove endif at end
        content = content.replace('\n\n#endif // WITH_EDITOR\n', '\n')
        content = content.replace('\r\n\r\n#endif // WITH_EDITOR\r\n', '\r\n')
        content = content.replace('\n#endif // WITH_EDITOR\n', '\n')
        content = content.replace('\r\n#endif // WITH_EDITOR\r\n', '\r\n')
        content = content.rstrip() + '\n'
            
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
            
        print(f"Removed WITH_EDITOR guard from {filename}")
        count += 1
        
    print(f"Done. Modified {count} files.")

if __name__ == "__main__":
    remove_editor_guards()
