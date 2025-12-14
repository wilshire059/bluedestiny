#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "W_CraftingEntrySimple.generated.h"

UCLASS()
class SLF_5_7_API UW_CraftingEntrySimple : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> RequiredQuantityText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> OwnedQuantityText;

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void SetupSimpleEntry(UTexture2D* Icon, FText ItemName, int32 RequiredQuantity, int32 OwnedQuantity);
};
