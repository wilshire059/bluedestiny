#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "W_Boss_Healthbar.generated.h"

UCLASS()
class SLF_5_7_API UW_Boss_Healthbar : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UProgressBar> HealthBarBackground;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> BossNameText;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TWeakObjectPtr<AActor> TrackedBoss;

	UFUNCTION(BlueprintCallable, Category = "BossHealth")
	void SetupBossHealthbar(AActor* Boss, FText BossName);

	UFUNCTION(BlueprintCallable, Category = "BossHealth")
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "BossHealth")
	void ShowHealthbar();

	UFUNCTION(BlueprintCallable, Category = "BossHealth")
	void HideHealthbar();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Config")
	float DelayedBarSpeed = 2.0f;
};
