#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_Projectile.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_Projectile : public UInterface
{
	GENERATED_BODY()
};

class SLF_5_7_API IBPI_Projectile
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Projectile")
	void InitializeProjectile(AActor* TargetActor);
};
