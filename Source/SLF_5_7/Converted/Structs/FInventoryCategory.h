#pragma once

#include "CoreMinimal.h"
#include "Enums/E_ItemCategory.h"
#include "Engine/Texture2D.h"
#include "Internationalization/Text.h"
#include "FInventoryCategory.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FInventoryCategory
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText CategoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	E_ItemCategory CategoryEnum = E_ItemCategory::Tools;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSoftObjectPtr<UTexture2D> CategoryIcon;
};
