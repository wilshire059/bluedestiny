#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "W_AbilityDisplay.generated.h"

UCLASS()
class SLF_5_7_API UW_AbilityDisplay : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> AbilityIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> CooldownBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> AbilityNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> CooldownText;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetupAbility(UTexture2D* Icon, FText AbilityName);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void UpdateCooldown(float CurrentCooldown, float MaxCooldown);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetAbilityEnabled(bool bEnabled);
};
