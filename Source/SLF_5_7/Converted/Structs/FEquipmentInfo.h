#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enums/E_OverlayState.h"
#include "Structs/FEquipmentWeaponStatInfo.h"
#include "Structs/FEquipmentSocketInfo.h"
#include "FEquipmentInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FEquipmentInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    FGameplayTagContainer EquipSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    FGameplayTagContainer GrantedTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    E_OverlayState WeaponOverlay = E_OverlayState::Unarmed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    FEquipmentWeaponStatInfo WeaponStatInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    TArray<FEquipmentSocketInfo> AttachmentSockets;
};
