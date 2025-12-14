#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/BPI_Item.h"
#include "Structs/FSLFItemInfo.h"
#include "B_Item.generated.h"

UCLASS()
class SLF_5_7_API AB_Item : public AActor, public IBPI_Item
{
    GENERATED_BODY()
    
public:    
    AB_Item();

protected:
    virtual void BeginPlay() override;

public: 
    // Interface Implementation
    virtual void OnUse_Implementation() override;
    virtual void OnWeaponEquip_Implementation(bool bRightHand) override;
    virtual void OnWeaponUnequip_Implementation() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FSLFItemInfo ItemInfo;

    // bReplicates is an Actor property, initialized in constructor.
};
