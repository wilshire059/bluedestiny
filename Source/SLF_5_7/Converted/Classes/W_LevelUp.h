#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "W_LevelUp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpConfirmed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpCancelled);

UCLASS()
class SLF_5_7_API UW_LevelUp : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpConfirmed OnLevelUpConfirmed;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpCancelled OnLevelUpCancelled;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TMap<FGameplayTag, int32> PendingStatUpgrades;

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void AddStatUpgrade(FGameplayTag StatTag);

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void RemoveStatUpgrade(FGameplayTag StatTag);

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void ConfirmLevelUp();

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void CancelLevelUp();

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	int64 CalculateTotalCost() const;

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	int32 CalculateNewLevel() const;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "LevelUp")
	void OnStatUpgradesChanged();
};
