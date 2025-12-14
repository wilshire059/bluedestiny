#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"
#include "W_Browser_StatusEffect_Tooltip.generated.h"

UCLASS()
class SLF_5_7_API UW_Browser_StatusEffect_Tooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> EffectNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URichTextBlock> DescriptionText;

	UFUNCTION(BlueprintCallable, Category = "Browser")
	void SetupTooltip(FText EffectName, FText Description);
};
