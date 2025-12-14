#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Structs/FItemCategory.h"
#include "Structs/FWorldMeshInfo.h"
#include "Structs/FEquipmentInfo.h"
#include "Structs/FCraftingInfo.h"
#include "Engine/Texture2D.h"
#include "FSLFItemInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FSLFItemInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FGameplayTag ItemTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FItemCategory Category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ShortDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText LongDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText DiscoveryDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool bIsUsable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool bIsRechargeable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText OnUseDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSoftObjectPtr<UTexture2D> IconSmall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSoftObjectPtr<UTexture2D> IconLargeOptional;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxAmount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FGameplayTag ActionToTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSoftClassPtr<AActor> ItemClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FWorldMeshInfo WorldPickupInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FEquipmentInfo EquipmentDetails;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FCraftingInfo CraftingDetails;
};
