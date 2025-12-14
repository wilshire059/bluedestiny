#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "B_DeathCurrency.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_DeathCurrency : public AActor
{
	GENERATED_BODY()

public:
	AB_DeathCurrency();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> PickupCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	int32 CurrencyAmount;

	UFUNCTION(BlueprintCallable, Category = "Currency")
	void Pickup(AActor* PickupActor);

protected:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
