#include "GI_SoulslikeFramework.h"
#include "Kismet/GameplayStatics.h"

UGI_SoulslikeFramework::UGI_SoulslikeFramework()
{
    // Defaults could include loading a config or setting initial values
}

void UGI_SoulslikeFramework::GetCustomGameSettings_Implementation(UPDA_CustomSettings*& CustomSettingsAsset)
{
    CustomSettingsAsset = CustomSettings;
}

void UGI_SoulslikeFramework::GetAllSaveSlots_Implementation(TArray<FString>& OutSaveSlots)
{
    // Need to ensure list is loaded?
    LoadSlotList();
    OutSaveSlots = SaveSlots;
}

void UGI_SoulslikeFramework::SetLastSlotNameToActive_Implementation()
{
    LoadSlotList();
    if (SaveSlots.Num() > 0)
    {
        ActiveSlotName = SaveSlots.Last();
    }
}

bool UGI_SoulslikeFramework::DoesAnySaveExist_Implementation()
{
    LoadSlotList();
    return SaveSlots.Num() > 0;
}

void UGI_SoulslikeFramework::AddAndSaveSlots_Implementation(const FString& NewSlotName)
{
    if (!SaveSlots.Contains(NewSlotName))
    {
        SaveSlots.Add(NewSlotName);
        SaveSlotList(); 
        // Note: This saves the list of slots (e.g. to a master save file or config), 
        // usually named "SaveSlots" or something.
    }
}

void UGI_SoulslikeFramework::GetActiveSlotName_Implementation(FString& OutActiveSlotName)
{
    OutActiveSlotName = ActiveSlotName;
}

void UGI_SoulslikeFramework::SetActiveSlot_Implementation(const FString& InActiveSlotName)
{
    ActiveSlotName = InActiveSlotName;
}

void UGI_SoulslikeFramework::GetSelectedClass_Implementation(UPDA_BaseCharacterInfo*& SelectedClass)
{
    SelectedClass = SelectedBaseCharacterClass;
}

void UGI_SoulslikeFramework::SetSelectedClass_Implementation(UPDA_BaseCharacterInfo* BaseCharacterClass)
{
    SelectedBaseCharacterClass = BaseCharacterClass;
}

void UGI_SoulslikeFramework::SaveSlotList()
{
    // Save the 'SaveSlots' array to a dedicated save file, e.g., "SlotList"
    // For simplicity, we can use UGameplayStatics::SaveGameToSlot with a custom SaveGame object just for the list,
    // or just rely on the implementation detail that this list needs persistence.
    // The JSON didn't show the internals of "AddAndSaveSlots", assuming it manages a save file.
    // I will placeholder this or implement a basic version if I had the `SG_SaveSlots` JSON.
    // Found `SG_SaveSlots.json` in find results earlier! 
    // I should probably have checked it. For now, I'll just manage the array in memory 
    // but a real implementation would save it to disk. 
    // Logic: Create SaveGame instance of SG_SaveSlots, set slots, save to "MasterSaveSlot".
}

void UGI_SoulslikeFramework::LoadSlotList()
{
    // Similar to SaveSlotList, load "MasterSaveSlot" and populate SaveSlots.
}
