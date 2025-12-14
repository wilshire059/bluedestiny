#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "W_LootNotification.generated.h"

UCLASS()
class SLF_5_7_API UW_LootNotification : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float DisplayDuration = 3.0f;

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void ShowLootNotification(UTexture2D* Icon, FText ItemName, int32 Quantity = 1);

protected:
	FTimerHandle HideTimerHandle;

	UFUNCTION()
	void HideNotification();
};
