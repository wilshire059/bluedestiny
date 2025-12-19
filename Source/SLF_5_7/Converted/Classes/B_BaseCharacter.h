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
#include "Components/AC_StatusEffectManager.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "DataAssets/PDA_MovementSpeedData.h"
#include "B_BaseCharacter.generated.h"

// Movement/Lerp Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLocationLerpEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRotationLerpEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLocationRotationLerpEnd);

// Status/Combat Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMeshInitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitstopEnd, float, Duration);

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

    //========================================
    // COMPONENTS
    //========================================

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UWidgetComponent* TargetLockonWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* ProjectileHomingPosition;

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_StatusEffectManager* StatusEffectManager;

    //========================================
    // MOVEMENT PROPERTIES
    //========================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
    UPDA_MovementSpeedData* SpeedAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
    float RunSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
    float WalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
    float SprintSpeed;

    //========================================
    // HITSTOP PROPERTIES
    //========================================

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Hitstop")
    bool bIsInHitstop;

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Hitstop")
    FTimerHandle HitstopTimerHandle;

    //========================================
    // LERP PROPERTIES
    //========================================

    UPROPERTY(BlueprintReadOnly, Category = "Movement|Lerp")
    bool bIsLerpingLocation;

    UPROPERTY(BlueprintReadOnly, Category = "Movement|Lerp")
    bool bIsLerpingRotation;

    UPROPERTY(BlueprintReadOnly, Category = "Movement|Lerp")
    FVector LerpTargetLocation;

    UPROPERTY(BlueprintReadOnly, Category = "Movement|Lerp")
    FRotator LerpTargetRotation;

    UPROPERTY(BlueprintReadOnly, Category = "Movement|Lerp")
    float LerpAlpha;

    UPROPERTY(BlueprintReadOnly, Category = "Movement|Lerp")
    float LerpSpeed;

    //========================================
    // DELEGATES
    //========================================

    UPROPERTY(BlueprintAssignable, Category = "Events|Movement")
    FOnLocationLerpEnd OnLocationLerpEnd;

    UPROPERTY(BlueprintAssignable, Category = "Events|Movement")
    FOnRotationLerpEnd OnRotationLerpEnd;

    UPROPERTY(BlueprintAssignable, Category = "Events|Movement")
    FOnLocationRotationLerpEnd OnLocationRotationLerpEnd;

    UPROPERTY(BlueprintAssignable, Category = "Events|Combat")
    FOnHitstopEnd OnHitstopEnd;

    UPROPERTY(BlueprintAssignable, Category = "Events|Initialization")
    FOnMeshInitialized OnMeshInitialized;

    //========================================
    // MOVEMENT FUNCTIONS
    //========================================

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetSpeed(float Speed);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetMovementMode(EMovementMode NewMode);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Jump_Custom();

    //========================================
    // HITSTOP FUNCTIONS
    //========================================

    UFUNCTION(BlueprintCallable, Category = "Combat|Hitstop")
    void StartHitstop(float Duration);

    UFUNCTION(BlueprintCallable, Category = "Combat|Hitstop")
    void StopHitstop();

    //========================================
    // STAT/STATUS FUNCTIONS
    //========================================

    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool IsStatusEffectActive(FGameplayTag StatusEffectTag) const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    FStatInfo GetStat(FGameplayTag StatTag) const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    class APC_SoulslikeFramework* GetSoulslikeController() const;

    //========================================
    // NETWORK REPLICATION (Server RPCs)
    //========================================

    UFUNCTION(Server, Reliable, Category = "Network")
    void SRV_PlayMontage(UAnimMontage* Montage, float PlayRate, float StartPos, FName StartSection);

    UFUNCTION(Server, Reliable, Category = "Network")
    void SRV_SpawnNiagaraOneshotAttached(UNiagaraSystem* System, USceneComponent* AttachComponent, FName SocketName, FVector Location, FRotator Rotation);

    UFUNCTION(Server, Reliable, Category = "Network")
    void SRV_SpawnNiagaraOneshot(UNiagaraSystem* System, FVector Location, FRotator Rotation);

    UFUNCTION(Server, Reliable, Category = "Network")
    void SRV_SpawnPickupItem(TSubclassOf<class AB_PickupItem> ItemClass, FVector Location, FRotator Rotation);

    UFUNCTION(Server, Reliable, Category = "Network")
    void SRV_SpawnActor(TSubclassOf<AActor> ActorClass, FTransform Transform);

    UFUNCTION(Server, Reliable, Category = "Network")
    void SRV_DestroyActor(AActor* ActorToDestroy);

    UFUNCTION(Server, Reliable, Category = "Network")
    void SRV_SetSpeed(float NewSpeed);

    UFUNCTION(Server, Reliable, Category = "Network")
    void SRV_Jump();

    //========================================
    // NETWORK REPLICATION (Multicast RPCs)
    //========================================

    UFUNCTION(NetMulticast, Reliable, Category = "Network")
    void MC_PlayMontage(UAnimMontage* Montage, float PlayRate, float StartPos, FName StartSection);

    UFUNCTION(NetMulticast, Reliable, Category = "Network")
    void MC_SpawnNiagaraOneshotAttached(UNiagaraSystem* System, USceneComponent* AttachComponent, FName SocketName, FVector Location, FRotator Rotation);

    UFUNCTION(NetMulticast, Reliable, Category = "Network")
    void MC_SpawnNiagaraOneshot(UNiagaraSystem* System, FVector Location, FRotator Rotation);

    UFUNCTION(NetMulticast, Reliable, Category = "Network")
    void MC_SetSpeed(float NewSpeed);

    UFUNCTION(NetMulticast, Reliable, Category = "Network")
    void MC_Jump();

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
