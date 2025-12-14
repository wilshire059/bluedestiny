#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_Damageable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_Damageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for damageable actors.
 */
class SLF_5_7_API IBPI_Damageable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	bool IsDead();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	void TakeDamage(float Damage, AActor* DamageCauser);
};
