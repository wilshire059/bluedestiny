import os
import re

SOURCE_DIR = r"Source/SLF_5_7/ManualConversion"

# String replacements to make
REPLACEMENTS = [
    # Rename FItemInfo to FSLFItemInfo to avoid collision with UE5 STreeView.h
    (r'\bFItemInfo\b', 'FSLFItemInfo'),
    
    # Fix enum references
    (r'E_Progress::NewEnumerator0', 'E_Progress::None'),
    
    # Fix StructUtils include path
    (r'#include "StructUtils/Public/InstancedStruct.h"', '#include "InstancedStruct.h"'),
    
    # Fix AB_Action to UB_Action (UObject-based action class)
    (r'\bAB_Action\b', 'UB_Action'),
]

def fix_types():
    """Fix type names and references."""
    count = 0
    
    for root, dirs, files in os.walk(SOURCE_DIR):
        for filename in files:
            if not (filename.endswith('.h') or filename.endswith('.cpp')):
                continue
                
            filepath = os.path.join(root, filename)
            
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
                
            original = content
            
            for pattern, replacement in REPLACEMENTS:
                content = re.sub(pattern, replacement, content)
                    
            if content != original:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                print(f"Fixed: {filename}")
                count += 1
                
    print(f"\nDone. Fixed {count} files.")

if __name__ == "__main__":
    fix_types()
