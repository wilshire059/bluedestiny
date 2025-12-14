import os
import shutil
import re

LOG_CONTENT = r"""
C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FClass.h(7): Error: Struct 'FClass' shares engine name 'Class' with class 'UClass' in C:\Program Files\Epic Games\UE_5.7\Engine\Source\Runtime\CoreUObject\Public\UObject\Class.h(3791)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\AnimNotifies\ANS_RegisterAttackSequence.h(12): Error: Enum 'E_MontageSection' shares engine name 'E_MontageSection' with enum 'E_MontageSection' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Enums\E_MontageSection.h(5)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_BaseCharacterInfo.h(20): Error: Struct 'FSkeletalMeshMergeParams' shares engine name 'SkeletalMeshMergeParams' with struct 'FSkeletalMeshMergeParams' in C:\Program Files\Epic Games\UE_5.7\Engine\Plugins\Runtime\SkeletalMerging\Source\SkeletalMerging\Public\SkeletalMergingLibrary.h(16)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_Calculations.h(12): Error: Enum 'E_CalculationType' shares engine name 'E_CalculationType' with enum 'E_CalculationType' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Enums\E_CalculationType.h(5)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_Credits.h(14): Error: Struct 'FCreditsEntry' shares engine name 'CreditsEntry' with struct 'FCreditsEntry' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FCreditsEntry.h(7)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_Credits.h(30): Error: Struct 'FCreditsExtra' shares engine name 'CreditsExtra' with struct 'FCreditsExtra' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FCreditsExtra.h(8)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_DayNight.h(13): Error: Struct 'FDayNightInfo' shares engine name 'DayNightInfo' with struct 'FDayNightInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FDayNightInfo.h(7)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_DefaultMeshData.h(15): Error: Struct 'FSkeletalMeshData' shares engine name 'SkeletalMeshData' with struct 'FSkeletalMeshData' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FSkeletalMeshData.h(8)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_ExecutionAnimData.h(10): Error: Struct 'FExecutionInfo' shares engine name 'ExecutionInfo' with struct 'FExecutionInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FExecutionInfo.h(8)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_LoadingScreens.h(13): Error: Struct 'FLoadingScreenTip' shares engine name 'LoadingScreenTip' with struct 'FLoadingScreenTip' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FLoadingScreenTip.h(7)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FCraftingInfo.h(8): Error: Struct 'FCraftingInfo' shares engine name 'CraftingInfo' with struct 'FCraftingInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_Item.h(20)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FItemInfo.h(14): Error: Struct 'FItemInfo' shares engine name 'ItemInfo' with struct 'FItemInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_Item.h(35)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FItemStructs.h(17): Error: Struct 'FItemCategory' shares engine name 'ItemCategory' with struct 'FItemCategory' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FItemCategory.h(8)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FItemStructs.h(47): Error: Struct 'FEquipmentSocketInfo' shares engine name 'EquipmentSocketInfo' with struct 'FEquipmentSocketInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FEquipmentSocketInfo.h(6)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FItemStructs.h(83): Error: Struct 'FEquipmentWeaponStatInfo' shares engine name 'EquipmentWeaponStatInfo' with struct 'FEquipmentWeaponStatInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FEquipmentWeaponStatInfo.h(8)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FItemStructs.h(101): Error: Struct 'FEquipmentInfo' shares engine name 'EquipmentInfo' with struct 'FEquipmentInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FEquipmentInfo.h(15)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FWorldMeshInfo.h(10): Error: Struct 'FWorldMeshInfo' shares engine name 'WorldMeshInfo' with struct 'FWorldMeshInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FItemStructs.h(29)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_CategoryEntry.h(11): Error: Enum 'E_StatCategory' shares engine name 'E_StatCategory' with enum 'E_StatCategory' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Enums\E_StatCategory.h(6)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_CreditEntry.h(18): Error: Struct 'FCreditsNames' shares engine name 'CreditsNames' with struct 'FCreditsNames' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FCreditsNames.h(7)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_CreditEntry_Extra.h(12): Error: Struct 'FCreditsExtra' shares engine name 'CreditsExtra' with struct 'FCreditsExtra' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FCreditsExtra.h(8)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_InventoryActionAmount.h(11): Error: Enum 'E_InventoryAmountedActionType' shares engine name 'E_InventoryAmountedActionType' with enum 'E_InventoryAmountedActionType' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Enums\E_InventoryAmountedActionType.h(5)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_Inventory_CategoryEntry.h(11): Error: Struct 'FInventoryCategory' shares engine name 'InventoryCategory' with struct 'FInventoryCategory' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FInventoryCategory.h(9)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_HUD.h(9): Error: Enum 'E_FadeTypes' shares engine name 'E_FadeTypes' with enum 'E_FadeTypes' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Enums\E_FadeTypes.h(5)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_Radar_Cardinal.h(8): Error: Struct 'FCardinalData' shares engine name 'CardinalData' with struct 'FCardinalData' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FCardinalData.h(7)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_Resources.h(10): Error: Struct 'FStatInfo' shares engine name 'StatInfo' with struct 'FStatInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FStatInfo.h(8)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_RestMenu_TimeEntry.h(11): Error: Struct 'FDayNightInfo' shares engine name 'DayNightInfo' with struct 'FDayNightInfo' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FDayNightInfo.h(7)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_Settings_ControlEntry.h(11): Error: Struct 'FKeyMappingCorrelation' shares engine name 'KeyMappingCorrelation' with struct 'FKeyMappingCorrelation' in C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FKeyMappingCorrelation.h(8)
C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Widgets\W_Settings_Entry.h(11): Error: Enum 'E_SettingEntry' shares engine name 'E_SettingEntry' with enum 'E_SettingEntry' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Enums\E_SettingEntry.h(5)
C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FWeaponAttackPower.h(7): Error: Struct 'FWeaponAttackPower' shares engine name 'WeaponAttackPower' with struct 'FWeaponAttackPower' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FItemStructs.h(59)
C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FWeightedLoot.h(8): Error: Struct 'FWeightedLoot' shares engine name 'WeightedLoot' with struct 'FWeightedLoot' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\Structs\FLootItem.h(23)
C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\Structs\FVendorItems.h(7): Error: Struct 'FVendorItems' shares engine name 'VendorItems' with struct 'FVendorItems' in C:\scripts\BlueDestiny\Source\SLF_5_7\ManualConversion\DataAssets\PDA_Vendor.h(8)
"""

ARCHIVE_ROOT = r"_Archive_Duplicates/Log_Cleanup"
SOURCE_ROOT = r"C:\scripts\BlueDestiny\Source\SLF_5_7"

def archive_log_conflicts():
    print("Parsing log for Generated conficts...")
    
    # Updated regex to capture paths ending in .h within the Generated folder
    # Looking for: ...\Generated\...\SameName.h
    
    generated_pattern = re.compile(r'(C:[^:\n]*\\Generated\\[^:\n]+\.h)', re.IGNORECASE)
    
    matches = generated_pattern.findall(LOG_CONTENT)
    unique_paths = set(matches) # dedup
    
    print(f"Found {len(unique_paths)} unique Generated files to archive.")
    
    count = 0
    for file_path in unique_paths:
        # Check if file exists
        if not os.path.exists(file_path):
            print(f"Skipping (not found): {file_path}")
            continue
            
        # Construct archive path
        # Rel path from Source/SLF_5_7
        # file_path is abs: C:\scripts\BlueDestiny\Source\SLF_5_7\Generated\X
        
        try:
            rel_path = os.path.relpath(file_path, SOURCE_ROOT)
        except ValueError:
            # If paths are on different drives or something weird (unlikely)
            print(f"Error calculating relpath for {file_path}")
            continue
            
        dest_path = os.path.join(ARCHIVE_ROOT, rel_path)
        
        os.makedirs(os.path.dirname(dest_path), exist_ok=True)
        
        try:
            shutil.move(file_path, dest_path)
            print(f"Archived: {rel_path}")
            count += 1
        except Exception as e:
            print(f"Failed to move {file_path}: {e}")
            
    print(f"Done. Archived {count} files.")

if __name__ == "__main__":
    archive_log_conflicts()
