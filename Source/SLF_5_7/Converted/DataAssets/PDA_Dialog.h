#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/AC_ProgressManager.h"
#include "Engine/DataTable.h"
#include "PDA_Dialog.generated.h"

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_Dialog : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Dialog")
    TSoftObjectPtr<UDataTable> GetDialogTableBasedOnProgress(UAC_ProgressManager* ProgressManager) const;
};
