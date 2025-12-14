#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "W_Interaction.generated.h"

UCLASS()
class SLF_5_7_API UW_Interaction : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractionText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UImage> InteractionKeyIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ItemNameText;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ShowInteraction(FText ActionText, FText ItemName = FText::GetEmpty());

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void HideInteraction();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractionKey(FKey Key);
};
