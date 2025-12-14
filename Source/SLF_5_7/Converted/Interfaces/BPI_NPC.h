#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_NPC.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_NPC : public UInterface
{
	GENERATED_BODY()
};

class SLF_5_7_API IBPI_NPC
{
	GENERATED_BODY()

public:
	// NPC Interface - extend as needed based on blueprint implementation
};
