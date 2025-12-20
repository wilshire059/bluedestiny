#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "B_Buff.generated.h"

class UPDA_Buff;
class UAC_StatManager;

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Buff : public UObject
{
	GENERATED_BODY()

public:
	UB_Buff();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TObjectPtr<UPDA_Buff> BuffData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	int32 Rank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	float RemainingDuration;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	void OnGranted();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	void OnRemoved();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	void OnTick(float DeltaTime);

	// Get the multiplier for the current rank from the RankMultiplierCurve
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Buff")
	float GetMultiplierForCurrentRank() const;

	// Get the StatManager component from the OwnerActor
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Buff")
	UAC_StatManager* GetOwnerStatManager() const;
};
