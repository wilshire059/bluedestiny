#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AC_BuffManager.generated.h"

class UPDA_Buff;
class UObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBuffDetected, UPDA_Buff*, Buff, bool, bAdded);

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_BuffManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_BuffManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buffs")
	TArray<TObjectPtr<UObject>> ActiveBuffs;

	UPROPERTY(BlueprintAssignable, Category = "Buffs")
	FOnBuffDetected OnBuffDetected;

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void TryAddBuff(UPDA_Buff* Buff, int32 Rank = 1, bool bIsLoading = false);

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void DelayedRemoveBuff(float DelayDuration, UPDA_Buff* Buff);

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	TArray<UObject*> GetBuffsWithTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void RemoveAllBuffsWithTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void RemoveBuffWithTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void RemoveAllBuffsOfType(UPDA_Buff* Buff);

	UFUNCTION(BlueprintCallable, Category = "Buffs")
	void RemoveBuffOfType(UPDA_Buff* Buff);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UObject> CacheBuff;
};
