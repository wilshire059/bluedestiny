#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Sound/SoundBase.h"
#include "NiagaraSystem.h"
#include "Camera/CameraShakeBase.h"
#include "Animation/AnimMontage.h"
#include "Components/SceneComponent.h"
#include "Classes/B_Ladder.h"
#include "Classes/B_Container.h"
#include "Classes/B_Door.h"
#include "E_MovementType.h"
#include "BPI_Generic_Character.generated.h"

UINTERFACE(MinimalAPI)
class UBPI_Generic_Character : public UInterface
{
	GENERATED_BODY()
};

class SLF_5_7_API IBPI_Generic_Character
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void SpawnActorReplicated(TSubclassOf<AActor> ActorClass, FTransform Transform, ESpawnActorCollisionHandlingMethod CollisionMethod, AActor* ActorOwner, APawn* InstigatorPawn);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void PlaySoftSoundAtLocation(const TSoftObjectPtr<USoundBase>& SoundBase, FVector Location, FRotator Rotation, double Volume, double Pitch, double StartTime, USoundAttenuation* Attenuation, USoundConcurrency* Concurrency, AActor* ActorOwner, UInitialActiveSoundParams* InitialParams);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    USceneComponent* GetHomingPositionComponent();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    bool GetMeshInitialized();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    USceneComponent* GetLockonComponent();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void ToggleLockonWidget(bool bVisible);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void SpawnProjectile(AActor* TargetActor, TSubclassOf<AActor> ProjectileClass, FTransform InitialTransform, ESpawnActorCollisionHandlingMethod CollisionMethod, AActor* ActorOwner, APawn* InstigatorPawn);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void OpenContainer(UAnimMontage* Montage, AB_Container* Container);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void StartWorldCameraShake(TSubclassOf<UCameraShakeBase> Shake, FVector Epicenter, double InnerRadius, double OuterRadius, double Falloff, bool bOrientTowardsEpicenter);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void PlaySoftNiagaraOneshotAtLocationReplicated(const TSoftObjectPtr<UNiagaraSystem>& VFXSystem, FVector Location, FRotator Rotation, bool bAutoDestroy, bool bAutoActivate, bool bPreCullCheck);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void EnableRagdoll();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void PlayIkReaction(double IKScale);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void GenericLocationAndRotationLerp(double Scale, FVector TargetLocation, FRotator TargetRotation);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void GenericRotationLerp(double Scale, FRotator TargetRotation);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void GenericLocationLerp(double Scale, FVector TargetLocation);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void TryClimbLadder(AB_Ladder* Ladder, bool bIsTopDown);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void StopActiveMontage(double BlendOutDuration);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    UAnimInstance* GetSoulslikeAnimInstance();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void OpenDoor(UAnimMontage* Montage, AB_Door* Door);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void SetMovementMode(E_MovementType MovementType);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void PlayMontageReplicated(UAnimMontage* Montage, float PlayRate, float StartPosition, FName StartSection);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Character")
    void PlaySoftMontageReplicated(const TSoftObjectPtr<UAnimMontage>& Montage, float PlayRate, float StartPosition, FName StartSection, bool bPriority);
};
