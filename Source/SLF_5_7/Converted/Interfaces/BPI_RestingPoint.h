#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_RestingPoint.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_RestingPoint : public UInterface
{
	GENERATED_BODY()
};

class SLF_5_7_API IBPI_RestingPoint
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resting Point")
	void GetRestingPointSpawnPosition(bool& bSuccess, FVector& Location, FRotator& Rotation);
};
