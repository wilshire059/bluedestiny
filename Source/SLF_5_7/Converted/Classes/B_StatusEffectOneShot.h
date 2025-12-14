#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_StatusEffectOneShot.generated.h"

class UPDA_StatusEffect;

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_StatusEffectOneShot : public AActor
{
	GENERATED_BODY()

public:
	AB_StatusEffectOneShot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect OneShot")
	TObjectPtr<UPDA_StatusEffect> StatusEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect OneShot")
	int32 Rank;

	UFUNCTION(BlueprintCallable, Category = "Status Effect OneShot")
	void TriggerOnActor(AActor* TargetActor);

protected:
	virtual void BeginPlay() override;
};
