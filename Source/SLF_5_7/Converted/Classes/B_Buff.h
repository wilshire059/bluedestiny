#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "B_Buff.generated.h"

class UPDA_Buff;

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
};
