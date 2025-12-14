import os
import re

SOURCE_DIR = r"Source/SLF_5_7/ManualConversion"

# Mapping of short paths to correct paths
INCLUDE_FIXES = {
    # Components
    '"AC_StatManager.h"': '"Components/AC_StatManager.h"',
    '"ManualConversion/AC_StatManager.h"': '"Components/AC_StatManager.h"',
    '"AC_InventoryManager.h"': '"Components/AC_InventoryManager.h"',
    '"AC_EquipmentManager.h"': '"Components/AC_EquipmentManager.h"',
    '"AC_BuffManager.h"': '"Components/AC_BuffManager.h"',
    '"AC_ActionManager.h"': '"Components/AC_ActionManager.h"',
    '"AC_CombatManager.h"': '"Components/AC_CombatManager.h"',
    
    # Enums - fix relative paths
    '"Enums/E_FadeTypes.h"': '"../Enums/E_FadeTypes.h"',
    '"Enums/E_InventoryAmountedActionType.h"': '"../Enums/E_InventoryAmountedActionType.h"',
    '"Enums/E_SettingEntry.h"': '"../Enums/E_SettingEntry.h"',
    '"Enums/E_ItemCategory.h"': '"../Enums/E_ItemCategory.h"',
    '"Enums/E_StatCategory.h"': '"../Enums/E_StatCategory.h"',
    '"Enums/E_SaveBehavior.h"': '"../Enums/E_SaveBehavior.h"',
    '"E_StatScaling.h"': '"../Enums/E_StatScaling.h"',
    
    # Structs - fix relative paths
    '"Structs/FInventoryCategory.h"': '"../Structs/FInventoryCategory.h"',
    '"Structs/FCardinalData.h"': '"../Structs/FCardinalData.h"',
    '"Structs/FStatInfo.h"': '"../Structs/FStatInfo.h"',
    '"Structs/FDayNightInfo.h"': '"../Structs/FDayNightInfo.h"',
    '"Structs/FCreditsExtra.h"': '"../Structs/FCreditsExtra.h"',
    '"Structs/FWeaponAttackPower.h"': '"../Structs/FWeaponAttackPower.h"',
    '"Structs/FSaveGameInfo.h"': '"../Structs/FSaveGameInfo.h"',
    
    # DataAssets
    '"PDA_Item.h"': '"DataAssets/PDA_Item.h"',
    
    # SaveSystem
    '"SaveSystem/SG_SoulslikeFramework.h"': '"../SaveSystem/SG_SoulslikeFramework.h"',
    
    # Interfaces
    '"BPI_MainMenu.h"': '"Interfaces/BPI_MainMenu.h"',
    '"Interfaces/BPI_ExecutionIndicator.h"': '"../Interfaces/BPI_ExecutionIndicator.h"',
    '"BPI_Controller.h"': '"Interfaces/BPI_Controller.h"',
}

def fix_includes():
    """Fix include paths in all C++ files."""
    count = 0
    files_fixed = []
    
    for root, dirs, files in os.walk(SOURCE_DIR):
        for filename in files:
            if not (filename.endswith('.h') or filename.endswith('.cpp')):
                continue
                
            filepath = os.path.join(root, filename)
            
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
                
            original = content
            
            for old_include, new_include in INCLUDE_FIXES.items():
                if old_include in content:
                    content = content.replace(old_include, new_include)
                    
            if content != original:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                print(f"Fixed includes in {filename}")
                files_fixed.append(filename)
                count += 1
                
    print(f"\nDone. Fixed {count} files: {files_fixed}")

if __name__ == "__main__":
    fix_includes()
