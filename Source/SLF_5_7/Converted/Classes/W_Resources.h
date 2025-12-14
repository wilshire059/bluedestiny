#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "W_Resources.generated.h"

UCLASS()
class SLF_5_7_API UW_Resources : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> FPBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> HealthText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> FPText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> StaminaText;

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void UpdateHealth(float Current, float Max);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void UpdateFP(float Current, float Max);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void UpdateStamina(float Current, float Max);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void BindToStatManager();
};
