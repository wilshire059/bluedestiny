#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_AbilityEffectBase.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_AbilityEffectBase : public AActor
{
	GENERATED_BODY()

public:
	AB_AbilityEffectBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	bool bDestroyOnComplete;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect")
	void ActivateEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect")
	void DeactivateEffect();

protected:
	virtual void BeginPlay() override;
};
