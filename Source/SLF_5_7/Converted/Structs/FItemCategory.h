#pragma once

#include "CoreMinimal.h"
#include "Enums/E_ItemCategory.h"
#include "FItemCategory.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FItemCategory
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Category")
    E_ItemCategory Category = E_ItemCategory::Tools;
};
