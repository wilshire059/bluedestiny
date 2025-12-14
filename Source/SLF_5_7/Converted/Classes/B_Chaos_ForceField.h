#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "B_Chaos_ForceField.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_Chaos_ForceField : public AActor
{
	GENERATED_BODY()

public:
	AB_Chaos_ForceField();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> ForceFieldCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ForceField")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ForceField")
	float DamagePerSecond;
};
