#include "B_Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AB_Weapon::AB_Weapon()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create Components
    WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
    RootComponent = WeaponSkeletalMesh;

    WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
    WeaponStaticMesh->SetupAttachment(RootComponent);

    CollisionManager = CreateDefaultSubobject<UAC_CollisionManager>(TEXT("CollisionManager"));
}

void AB_Weapon::BeginPlay()
{
    Super::BeginPlay();

    // Determine Active Mesh (Logic similar to BP Select)
    // If SkeletalMesh is set (SkeletalMesh asset assigned), usage implies it's the primary.
    // Logic: Default to Root if not specific.
    
    // Bind Collision Manager Delegate
    if (CollisionManager)
    {
        CollisionManager->OnActorTraced.AddDynamic(this, &AB_Weapon::TryApplyDamage);
    }
}

UPrimitiveComponent* AB_Weapon::GetWeaponMesh() const
{
    if (WeaponSkeletalMesh && WeaponSkeletalMesh->GetSkeletalMeshAsset())
    {
        return WeaponSkeletalMesh;
    }
    if (WeaponStaticMesh && WeaponStaticMesh->GetStaticMesh())
    {
        return WeaponStaticMesh;
    }
    return WeaponSkeletalMesh; // Fallback to root
}

void AB_Weapon::OnWeaponEquip_Implementation(bool bRightHand)
{
    // Get Socket Name from ItemInfo
    FName SocketName = NAME_None;
    
    // Access Socket Info
    const FEquipmentInfo& EquipDetails = ItemInfo.EquipmentDetails;
    if (EquipDetails.AttachmentSockets.Num() > 0)
    {
        const FEquipmentSocketInfo& SocketInfo = EquipDetails.AttachmentSockets[0];
        SocketName = bRightHand ? SocketInfo.RightHandSocketName : SocketInfo.LeftHandSocketName;
    }
    
    // Fallback defaults
    if (SocketName.IsNone())
    {
        SocketName = bRightHand ? FName("Hand_R_Socket") : FName("Hand_L_Socket");
    }

    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        USceneComponent* ParentMesh = OwnerActor->GetComponentByClass<USkeletalMeshComponent>();
        if (ParentMesh)
        {
            AttachToComponent(ParentMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
        }
    }
}

void AB_Weapon::OnWeaponUnequip_Implementation()
{
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AB_Weapon::TryApplyDamage(AActor* DamagedActor, FHitResult Hit, double Multiplier)
{
    if (!DamagedActor || DamagedActor == this || DamagedActor == GetInstigator())
    {
        return;
    }

    // Calculate Damage
    // TODO: Retrieve BaseDamage from ItemInfo or AttributeSet. Struct FEquipmentWeaponStatInfo missing BaseDamage field?
    float BaseDamage = 10.0f; 
    
    float FinalDamage = BaseDamage * Multiplier;

    UGameplayStatics::ApplyPointDamage(
        DamagedActor,
        FinalDamage,
        Hit.ImpactNormal,
        Hit,
        GetInstigatorController(),
        this,
        UDamageType::StaticClass()
    );
}
