#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/ScrollBox.h"
#include "Structs/FSaveGameInfo.h"
#include "W_LoadGame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveSlotSelected, int32, SlotIndex);

UCLASS()
class SLF_5_7_API UW_LoadGame : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> SaveSlotContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSaveSlotSelected OnSaveSlotSelected;

	UFUNCTION(BlueprintCallable, Category = "LoadGame")
	void SetupSaveSlots(const TArray<FSaveGameInfo>& SaveSlots);

	UFUNCTION(BlueprintCallable, Category = "LoadGame")
	void SelectSlot(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "LoadGame")
	void DeleteSlot(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "LoadGame")
	void CloseMenu();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "LoadGame")
	void OnSetupSaveSlots(const TArray<FSaveGameInfo>& SaveSlots);
};
