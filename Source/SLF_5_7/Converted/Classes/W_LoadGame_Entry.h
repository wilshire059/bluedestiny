#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Structs/FSaveGameInfo.h"
#include "W_LoadGame_Entry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadEntrySelected, int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadEntryDeleteRequested, int32, SlotIndex);

UCLASS()
class SLF_5_7_API UW_LoadGame_Entry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> LoadButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SlotNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayTimeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> LocationText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UImage> ScreenshotImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UButton> DeleteButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 SlotIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLoadEntrySelected OnLoadEntrySelected;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLoadEntryDeleteRequested OnLoadEntryDeleteRequested;

	UFUNCTION(BlueprintCallable, Category = "LoadEntry")
	void SetupEntry(int32 InSlotIndex, const FSaveGameInfo& SaveInfo);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleLoadClicked();

	UFUNCTION()
	void HandleDeleteClicked();
};
