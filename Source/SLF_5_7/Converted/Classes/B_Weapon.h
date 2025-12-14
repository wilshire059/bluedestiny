#pragma once

#include "CoreMinimal.h"
#include "B_Item.h"
#include "Components/AC_CollisionManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "B_Weapon.generated.h"

UCLASS()
class SLF_5_7_API AB_Weapon : public AB_Item
{
    GENERATED_BODY()

public:
    AB_Weapon();

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UAC_CollisionManager> CollisionManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> WeaponStaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMesh;

    // Interface overrides
    virtual void OnWeaponEquip_Implementation(bool bRightHand) override;
    virtual void OnWeaponUnequip_Implementation() override;

    // Functions
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void TryApplyDamage(AActor* DamagedActor, FHitResult Hit, double Multiplier);

protected:
    virtual void BeginPlay() override;

    // Helper to get active mesh
    UPrimitiveComponent* GetWeaponMesh() const;
};
