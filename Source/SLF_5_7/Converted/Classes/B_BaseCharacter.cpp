#include "B_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AB_BaseCharacter::AB_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    TargetLockonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetLockonWidget"));
    TargetLockonWidget->SetupAttachment(RootComponent);
    TargetLockonWidget->SetVisibility(false);

    StatManager = CreateDefaultSubobject<UAC_StatManager>(TEXT("StatManager"));
    EquipmentManager = CreateDefaultSubobject<UAC_EquipmentManager>(TEXT("EquipmentManager"));
    ActionManager = CreateDefaultSubobject<UAC_ActionManager>(TEXT("ActionManager"));
    CombatManager = CreateDefaultSubobject<UAC_CombatManager>(TEXT("CombatManager"));
    InventoryManager = CreateDefaultSubobject<UAC_InventoryManager>(TEXT("InventoryManager"));
}

void AB_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AB_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AB_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Interface Implementation Stubs
void AB_BaseCharacter::SpawnActorReplicated_Implementation(TSubclassOf<AActor> ActorClass, FTransform Transform, ESpawnActorCollisionHandlingMethod CollisionMethod, AActor* ActorOwner, APawn* InstigatorPawn)
{
    if (ActorClass)
    {
        GetWorld()->SpawnActor<AActor>(ActorClass, Transform);
    }
}

void AB_BaseCharacter::PlaySoftSoundAtLocation_Implementation(const TSoftObjectPtr<USoundBase>& SoundBase, FVector Location, FRotator Rotation, double Volume, double Pitch, double StartTime, USoundAttenuation* Attenuation, USoundConcurrency* Concurrency, AActor* ActorOwner, UInitialActiveSoundParams* InitialParams)
{
    // Stub
}

USceneComponent* AB_BaseCharacter::GetHomingPositionComponent_Implementation()
{
    return GetMesh();
}

bool AB_BaseCharacter::GetMeshInitialized_Implementation()
{
    return GetMesh() != nullptr;
}

USceneComponent* AB_BaseCharacter::GetLockonComponent_Implementation()
{
    return TargetLockonWidget;
}

void AB_BaseCharacter::ToggleLockonWidget_Implementation(bool bVisible)
{
    if (TargetLockonWidget)
    {
        TargetLockonWidget->SetVisibility(bVisible);
    }
}

void AB_BaseCharacter::SpawnProjectile_Implementation(AActor* TargetActor, TSubclassOf<AActor> ProjectileClass, FTransform InitialTransform, ESpawnActorCollisionHandlingMethod CollisionMethod, AActor* ActorOwner, APawn* InstigatorPawn)
{
    // Stub
}

void AB_BaseCharacter::OpenContainer_Implementation(UAnimMontage* Montage, AB_Container* Container)
{
    PlayAnimMontage(Montage);
    // Notify container?
}

void AB_BaseCharacter::StartWorldCameraShake_Implementation(TSubclassOf<UCameraShakeBase> Shake, FVector Epicenter, double InnerRadius, double OuterRadius, double Falloff, bool bOrientTowardsEpicenter)
{
    UGameplayStatics::PlayWorldCameraShake(this, Shake, Epicenter, InnerRadius, OuterRadius, Falloff, bOrientTowardsEpicenter);
}

void AB_BaseCharacter::PlaySoftNiagaraOneshotAtLocationReplicated_Implementation(const TSoftObjectPtr<UNiagaraSystem>& VFXSystem, FVector Location, FRotator Rotation, bool bAutoDestroy, bool bAutoActivate, bool bPreCullCheck)
{
    // Stub
}

void AB_BaseCharacter::EnableRagdoll_Implementation()
{
    GetMesh()->SetSimulatePhysics(true);
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AB_BaseCharacter::PlayIkReaction_Implementation(double IKScale)
{
    // Stub
}

void AB_BaseCharacter::GenericLocationAndRotationLerp_Implementation(double Scale, FVector TargetLocation, FRotator TargetRotation)
{
    // Stub
}

void AB_BaseCharacter::GenericRotationLerp_Implementation(double Scale, FRotator TargetRotation)
{
    // Stub
}

void AB_BaseCharacter::GenericLocationLerp_Implementation(double Scale, FVector TargetLocation)
{
    // Stub
}

void AB_BaseCharacter::TryClimbLadder_Implementation(AB_Ladder* Ladder, bool bIsTopDown)
{
    // Implement using Ladder Manager or similar
}

void AB_BaseCharacter::StopActiveMontage_Implementation(double BlendOutDuration)
{
    StopAnimMontage();
}

UAnimInstance* AB_BaseCharacter::GetSoulslikeAnimInstance_Implementation()
{
    return GetMesh()->GetAnimInstance();
}

void AB_BaseCharacter::OpenDoor_Implementation(UAnimMontage* Montage, AB_Door* Door)
{
    PlayAnimMontage(Montage);
}
