import os
import re

SOURCE_DIR = r"Source/SLF_5_7/ManualConversion"

# Patterns to fix: remove "ManualConversion/", "Generated/", "Components/", etc. prefixes
# and use simple relative paths or just filenames
PATTERNS_TO_FIX = [
    # Remove ManualConversion/ prefix - these are inside the same module
    (r'#include "ManualConversion/([^"]+)"', r'#include "\1"'),
    
    # Remove Generated/ prefix and update enum/struct paths
    (r'#include "Generated/Enums/([^"]+)"', r'#include "../Enums/\1"'),
    (r'#include "Generated/Structs/([^"]+)"', r'#include "../Structs/\1"'),
    (r'#include "Generated/Classes/([^"]+)"', r'#include "../Interfaces/\1"'),  # BPI classes
    
    # Fix Components/ includes from within Components folder - just use filename
    (r'#include "Components/AC_([^"]+)"', r'#include "AC_\1"'),
    
    # Fix Interfaces/ includes from within cpp files
    (r'#include "Interfaces/(BPI_[^"]+)"', r'#include "\1"'),
    
    # Fix wrong E_TraceType include
    (r'#include "E_TraceType.h"', r'#include "../Enums/E_TraceType.h"'),
    
    # Fix B_StatusEffect include
    (r'#include "B_StatusEffect.h"', r'#include "../Classes/B_StatusEffect.h"'),
    
    # Fix AC_InputBuffer include
    (r'#include "AC_InputBuffer.h"', r'#include "../Components/AC_InputBuffer.h"'),
    
    # Fix AC_CollisionManager include from AnimNotifies
    (r'#include "AC_CollisionManager.h"', r'#include "../Components/AC_CollisionManager.h"'),
    
    # Fix AC_AI_BehaviorManager include
    (r'#include "AC_AI_BehaviorManager.h"', r'#include "../Components/AC_AI_BehaviorManager.h"'),
    
    # Fix AC_AI_CombatManager include
    (r'#include "AC_AI_CombatManager.h"', r'#include "../Components/AC_AI_CombatManager.h"'),
    
    # Fix BPI_Enemy, BPI_Player includes
    (r'#include "BPI_Enemy.h"', r'#include "../Interfaces/BPI_Enemy.h"'),
    (r'#include "BPI_Player.h"', r'#include "../Interfaces/BPI_Player.h"'),
]

def fix_includes():
    """Fix include paths in all C++ files."""
    count = 0
    
    for root, dirs, files in os.walk(SOURCE_DIR):
        for filename in files:
            if not (filename.endswith('.h') or filename.endswith('.cpp')):
                continue
                
            filepath = os.path.join(root, filename)
            
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
                
            original = content
            
            for pattern, replacement in PATTERNS_TO_FIX:
                content = re.sub(pattern, replacement, content)
                    
            if content != original:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                print(f"Fixed: {filename}")
                count += 1
                
    print(f"\nDone. Fixed {count} files.")

if __name__ == "__main__":
    fix_includes()
