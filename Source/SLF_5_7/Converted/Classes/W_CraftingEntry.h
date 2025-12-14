#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Structs/FCraftingInfo.h"
#include "W_CraftingEntry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftingEntrySelected, int32, EntryIndex);

UCLASS()
class SLF_5_7_API UW_CraftingEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> EntryButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 EntryIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCraftingEntrySelected OnCraftingEntrySelected;

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void SetupEntry(int32 InEntryIndex, const FCraftingInfo& CraftingInfo);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void SetSelected(bool bSelected);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleEntryClicked();
};
