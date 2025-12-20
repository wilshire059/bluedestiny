#include "GI_SoulslikeFramework.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/SG_SaveSlots.h"

UGI_SoulslikeFramework::UGI_SoulslikeFramework()
{
	// Set defaults from classDefaults in JSON
	SlotsSaveName = TEXT("SLF_Slots");
	bFirstTimeOnDemoLevel = true;

	// Default CustomGameSettings path: /Game/SoulslikeFramework/Data/CustomSettings/DA_CustomGameSettings
	static ConstructorHelpers::FObjectFinder<UPDA_CustomSettings> CustomSettingsAsset(
		TEXT("/Game/SoulslikeFramework/Data/CustomSettings/DA_CustomGameSettings.DA_CustomGameSettings"));
	if (CustomSettingsAsset.Succeeded())
	{
		CustomGameSettings = CustomSettingsAsset.Object;
	}

	// Default SelectedBaseClass: /Game/SoulslikeFramework/Data/BaseCharacters/DA_Quinn
	static ConstructorHelpers::FObjectFinder<UPDA_BaseCharacterInfo> BaseCharacterAsset(
		TEXT("/Game/SoulslikeFramework/Data/BaseCharacters/DA_Quinn.DA_Quinn"));
	if (BaseCharacterAsset.Succeeded())
	{
		SelectedBaseClass = BaseCharacterAsset.Object;
	}
}

void UGI_SoulslikeFramework::Init()
{
	Super::Init();

	// ReceiveInit logic from JSON EventGraph
	// Check if SlotsSaveName save file exists
	if (UGameplayStatics::DoesSaveGameExist(SlotsSaveName, 0))
	{
		// Load existing save slots
		USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SlotsSaveName, 0);
		if (LoadedGame)
		{
			SGO_Slots = Cast<USG_SaveSlots>(LoadedGame);
		}
	}
	else
	{
		// Create new save slots object if doesn't exist
		if (!SGO_Slots)
		{
			SGO_Slots = Cast<USG_SaveSlots>(UGameplayStatics::CreateSaveGameObject(USG_SaveSlots::StaticClass()));
		}
	}
}

void UGI_SoulslikeFramework::GetCustomGameSettings_Implementation(UPDA_CustomSettings*& CustomSettingsAsset)
{
	CustomSettingsAsset = CustomGameSettings;
}

void UGI_SoulslikeFramework::GetAllSaveSlots_Implementation(TArray<FString>& OutSaveSlots)
{
	if (SGO_Slots)
	{
		OutSaveSlots = SGO_Slots->GetAllSlots();
	}
	else
	{
		OutSaveSlots.Empty();
	}
}

void UGI_SoulslikeFramework::SetLastSlotNameToActive_Implementation()
{
	if (SGO_Slots)
	{
		ActiveSlot = SGO_Slots->GetLastSaveSlot();
	}
}

bool UGI_SoulslikeFramework::DoesAnySaveExist_Implementation()
{
	return UGameplayStatics::DoesSaveGameExist(SlotsSaveName, 0);
}

void UGI_SoulslikeFramework::AddAndSaveSlots_Implementation(const FString& NewSlotName)
{
	if (SGO_Slots)
	{
		// AddSlot to the save slots object
		SGO_Slots->AddSlot(NewSlotName);

		// Save the slots object to disk asynchronously
		UGameplayStatics::AsyncSaveGameToSlot(SGO_Slots, SlotsSaveName, 0);

		// Print debug message
		FString Message = FString::Printf(TEXT("\"%s\" has been added to slots list."), *NewSlotName);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, Message);
		}
		UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
	}
}

void UGI_SoulslikeFramework::GetActiveSlotName_Implementation(FString& OutActiveSlotName)
{
	OutActiveSlotName = ActiveSlot;
}

void UGI_SoulslikeFramework::SetActiveSlot_Implementation(const FString& InActiveSlotName)
{
	ActiveSlot = InActiveSlotName;
}

void UGI_SoulslikeFramework::GetSelectedClass_Implementation(UPDA_BaseCharacterInfo*& SelectedClass)
{
	SelectedClass = SelectedBaseClass;
}

void UGI_SoulslikeFramework::SetSelectedClass_Implementation(UPDA_BaseCharacterInfo* BaseCharacterClass)
{
	SelectedBaseClass = BaseCharacterClass;

	// Broadcast the delegate
	OnSelectedClassChanged.Broadcast();
}

void UGI_SoulslikeFramework::SaveSlotList()
{
	if (SGO_Slots)
	{
		// Save the slots object to disk
		UGameplayStatics::SaveGameToSlot(SGO_Slots, SlotsSaveName, 0);
	}
}

void UGI_SoulslikeFramework::LoadSlotList()
{
	if (UGameplayStatics::DoesSaveGameExist(SlotsSaveName, 0))
	{
		USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SlotsSaveName, 0);
		if (LoadedGame)
		{
			SGO_Slots = Cast<USG_SaveSlots>(LoadedGame);
		}
	}
}
