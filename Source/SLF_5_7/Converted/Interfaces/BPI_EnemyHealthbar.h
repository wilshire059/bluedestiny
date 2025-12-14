#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_EnemyHealthbar.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_EnemyHealthbar : public UInterface
{
	GENERATED_BODY()
};

class SLF_5_7_API IBPI_EnemyHealthbar
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Healthbar")
	void UpdateEnemyHealthbar(double CurrentHealth, double MaxHealth, double Change);
};
