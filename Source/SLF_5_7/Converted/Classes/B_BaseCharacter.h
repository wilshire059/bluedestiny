#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/BPI_Generic_Character.h"
#include "Components/WidgetComponent.h"
#include "Components/AC_StatManager.h"
#include "Components/AC_EquipmentManager.h"
#include "Components/AC_ActionManager.h"
#include "Components/AC_CombatManager.h"
#include "Components/AC_InventoryManager.h"
#include "B_BaseCharacter.generated.h"

UCLASS()
class SLF_5_7_API AB_BaseCharacter : public ACharacter, public IBPI_Generic_Character
{
	GENERATED_BODY()

public:
	AB_BaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UWidgetComponent* TargetLockonWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_StatManager* StatManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_EquipmentManager* EquipmentManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_ActionManager* ActionManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_CombatManager* CombatManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_InventoryManager* InventoryManager;

    // BPI_Generic_Character Implementation
    virtual void SpawnActorReplicated_Implementation(TSubclassOf<AActor> ActorClass, FTransform Transform, ESpawnActorCollisionHandlingMethod CollisionMethod, AActor* ActorOwner, APawn* InstigatorPawn) override;
    virtual void PlaySoftSoundAtLocation_Implementation(const TSoftObjectPtr<USoundBase>& SoundBase, FVector Location, FRotator Rotation, double Volume, double Pitch, double StartTime, USoundAttenuation* Attenuation, USoundConcurrency* Concurrency, AActor* ActorOwner, UInitialActiveSoundParams* InitialParams) override;
    virtual USceneComponent* GetHomingPositionComponent_Implementation() override;
    virtual bool GetMeshInitialized_Implementation() override;
    virtual USceneComponent* GetLockonComponent_Implementation() override;
    virtual void ToggleLockonWidget_Implementation(bool bVisible) override;
    virtual void SpawnProjectile_Implementation(AActor* TargetActor, TSubclassOf<AActor> ProjectileClass, FTransform InitialTransform, ESpawnActorCollisionHandlingMethod CollisionMethod, AActor* ActorOwner, APawn* InstigatorPawn) override;
    virtual void OpenContainer_Implementation(UAnimMontage* Montage, AB_Container* Container) override;
    virtual void StartWorldCameraShake_Implementation(TSubclassOf<UCameraShakeBase> Shake, FVector Epicenter, double InnerRadius, double OuterRadius, double Falloff, bool bOrientTowardsEpicenter) override;
    virtual void PlaySoftNiagaraOneshotAtLocationReplicated_Implementation(const TSoftObjectPtr<UNiagaraSystem>& VFXSystem, FVector Location, FRotator Rotation, bool bAutoDestroy, bool bAutoActivate, bool bPreCullCheck) override;
    virtual void EnableRagdoll_Implementation() override;
    virtual void PlayIkReaction_Implementation(double IKScale) override;
    virtual void GenericLocationAndRotationLerp_Implementation(double Scale, FVector TargetLocation, FRotator TargetRotation) override;
    virtual void GenericRotationLerp_Implementation(double Scale, FRotator TargetRotation) override;
    virtual void GenericLocationLerp_Implementation(double Scale, FVector TargetLocation) override;
    virtual void TryClimbLadder_Implementation(AB_Ladder* Ladder, bool bIsTopDown) override;
    virtual void StopActiveMontage_Implementation(double BlendOutDuration) override;
    virtual UAnimInstance* GetSoulslikeAnimInstance_Implementation() override;
    virtual void OpenDoor_Implementation(UAnimMontage* Montage, AB_Door* Door) override;
};
