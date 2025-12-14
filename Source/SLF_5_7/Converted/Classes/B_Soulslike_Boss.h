#pragma once

#include "CoreMinimal.h"
#include "B_Soulslike_Enemy.h"
#include "Components/SphereComponent.h"
#include "B_Soulslike_Boss.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_Soulslike_Boss : public AB_Soulslike_Enemy
{
	GENERATED_BODY()

public:
	AB_Soulslike_Boss();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> TriggerCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	FName BossName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	bool bIsBossDefeated;

protected:
	UFUNCTION()
	void OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
