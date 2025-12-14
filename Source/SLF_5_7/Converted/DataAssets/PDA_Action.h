#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Classes/B_Action.h" // Circular dependency potential, careful
#include "PDA_Action.generated.h"

class UB_Action;

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_Action : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    TSubclassOf<UB_Action> ActionClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
    FText ActionName;
};
