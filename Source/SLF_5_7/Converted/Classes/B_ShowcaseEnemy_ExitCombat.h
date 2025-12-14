#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "B_ShowcaseEnemy_ExitCombat.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_ShowcaseEnemy_ExitCombat : public AActor
{
	GENERATED_BODY()

public:
	AB_ShowcaseEnemy_ExitCombat();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerBox;

protected:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
