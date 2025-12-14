#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "B_StatusEffect.generated.h"

class UPDA_StatusEffect;

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_StatusEffect : public UObject
{
	GENERATED_BODY()

public:
	UB_StatusEffect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	TObjectPtr<UPDA_StatusEffect> EffectData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	int32 Rank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	double CurrentBuildup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	double MaxBuildup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	bool bIsActive;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Status Effect")
	void OnTriggered();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Status Effect")
	void OnRemoved();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Status Effect")
	void OnTick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Status Effect")
	void AddBuildup(double Amount);
};
