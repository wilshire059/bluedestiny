#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AC_StatusEffectManager.generated.h"

class UPDA_StatusEffect;
class UObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatusEffectChanged, UPDA_StatusEffect*, Effect, bool, bAdded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStatusEffectBuildupChanged, UPDA_StatusEffect*, Effect, double, CurrentBuildup, double, MaxBuildup);

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_StatusEffectManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_StatusEffectManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	TArray<TObjectPtr<UObject>> ActiveEffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	TMap<FGameplayTag, double> EffectBuildup;

	UPROPERTY(BlueprintAssignable, Category = "Status Effects")
	FOnStatusEffectChanged OnStatusEffectChanged;

	UPROPERTY(BlueprintAssignable, Category = "Status Effects")
	FOnStatusEffectBuildupChanged OnStatusEffectBuildupChanged;

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void TryAddStatusEffect(UPDA_StatusEffect* EffectClass, int32 Rank = 1, bool bStartBuildup = true, double StartAmount = 0.0);

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void RemoveStatusEffect(UPDA_StatusEffect* Effect);

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void AddBuildup(UPDA_StatusEffect* Effect, double Amount);

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void DecayBuildup(UPDA_StatusEffect* Effect, double Amount);

	UFUNCTION(BlueprintPure, Category = "Status Effects")
	double GetBuildup(UPDA_StatusEffect* Effect) const;

	UFUNCTION(BlueprintPure, Category = "Status Effects")
	bool HasStatusEffect(UPDA_StatusEffect* Effect) const;

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void ClearAllEffects();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
