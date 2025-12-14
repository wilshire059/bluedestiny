#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "W_EnemyHealthbar.generated.h"

UCLASS()
class SLF_5_7_API UW_EnemyHealthbar : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UProgressBar> StanceBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> EnemyNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> LevelText;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TWeakObjectPtr<AActor> TrackedEnemy;

	UFUNCTION(BlueprintCallable, Category = "EnemyHealth")
	void SetupEnemyHealthbar(AActor* Enemy, FText EnemyName, int32 Level);

	UFUNCTION(BlueprintCallable, Category = "EnemyHealth")
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "EnemyHealth")
	void UpdateStance(float CurrentStance, float MaxStance);

	UFUNCTION(BlueprintCallable, Category = "EnemyHealth")
	void ShowHealthbar();

	UFUNCTION(BlueprintCallable, Category = "EnemyHealth")
	void HideHealthbar();
};
