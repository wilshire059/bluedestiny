#include "B_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Classes/PC_SoulslikeFramework.h"
#include "Classes/B_PickupItem.h"
#include "TimerManager.h"

AB_BaseCharacter::AB_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//========================================
	// CAPSULE DEFAULTS
	//========================================
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	//========================================
	// MESH TRANSFORM DEFAULTS
	//========================================
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -89.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->bCastDynamicShadow = true;

	//========================================
	// CHARACTER MOVEMENT DEFAULTS
	//========================================
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->MaxWalkSpeed = 500.0f;
	MoveComp->MaxWalkSpeedCrouched = 300.0f;
	MoveComp->JumpZVelocity = 700.0f;
	MoveComp->AirControl = 0.35f;
	MoveComp->GravityScale = 1.75f;
	MoveComp->MaxAcceleration = 1500.0f;
	MoveComp->BrakingDecelerationWalking = 2000.0f;
	MoveComp->GroundFriction = 8.0f;
	MoveComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MoveComp->bOrientRotationToMovement = true;

	//========================================
	// SPEED DEFAULTS
	//========================================
	RunSpeed = 500.0f;
	WalkSpeed = 200.0f;
	SprintSpeed = 700.0f;

	//========================================
	// STATE DEFAULTS
	//========================================
	bIsInHitstop = false;
	bIsLerpingLocation = false;
	bIsLerpingRotation = false;
	LerpAlpha = 0.0f;
	LerpSpeed = 1.0f;

	//========================================
	// CREATE COMPONENTS
	//========================================

	// Target Lock-On Widget
	TargetLockonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetLockonWidget"));
	TargetLockonWidget->SetupAttachment(RootComponent);
	TargetLockonWidget->SetRelativeLocation(FVector(29.057f, 0.0f, 0.0f));
	TargetLockonWidget->SetDrawSize(FVector2D(500.0f, 500.0f));
	TargetLockonWidget->SetVisibility(false);

	// Projectile Homing Position
	ProjectileHomingPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileHomingPosition"));
	ProjectileHomingPosition->SetupAttachment(RootComponent);
	ProjectileHomingPosition->SetRelativeLocation(FVector(60.0f, 0.0f, 50.0f));
	ProjectileHomingPosition->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	// Actor Components
	StatManager = CreateDefaultSubobject<UAC_StatManager>(TEXT("StatManager"));
	EquipmentManager = CreateDefaultSubobject<UAC_EquipmentManager>(TEXT("EquipmentManager"));
	ActionManager = CreateDefaultSubobject<UAC_ActionManager>(TEXT("ActionManager"));
	CombatManager = CreateDefaultSubobject<UAC_CombatManager>(TEXT("CombatManager"));
	InventoryManager = CreateDefaultSubobject<UAC_InventoryManager>(TEXT("InventoryManager"));
	StatusEffectManager = CreateDefaultSubobject<UAC_StatusEffectManager>(TEXT("StatusEffectManager"));

	//========================================
	// ACTOR TAGS
	//========================================
	Tags.Add(FName("Character"));
}

void AB_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Broadcast mesh initialized event
	if (GetMesh())
	{
		OnMeshInitialized.Broadcast();
	}
}

void AB_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle Location Lerp
	if (bIsLerpingLocation)
	{
		LerpAlpha += DeltaTime * LerpSpeed;
		if (LerpAlpha >= 1.0f)
		{
			SetActorLocation(LerpTargetLocation);
			bIsLerpingLocation = false;
			LerpAlpha = 0.0f;
			OnLocationLerpEnd.Broadcast();
		}
		else
		{
			FVector NewLocation = FMath::Lerp(GetActorLocation(), LerpTargetLocation, LerpAlpha);
			SetActorLocation(NewLocation);
		}
	}

	// Handle Rotation Lerp
	if (bIsLerpingRotation)
	{
		LerpAlpha += DeltaTime * LerpSpeed;
		if (LerpAlpha >= 1.0f)
		{
			SetActorRotation(LerpTargetRotation);
			bIsLerpingRotation = false;
			LerpAlpha = 0.0f;
			OnRotationLerpEnd.Broadcast();
		}
		else
		{
			FRotator NewRotation = FMath::Lerp(GetActorRotation(), LerpTargetRotation, LerpAlpha);
			SetActorRotation(NewRotation);
		}
	}
}

void AB_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//========================================
// MOVEMENT FUNCTIONS
//========================================

void AB_BaseCharacter::SetSpeed(float Speed)
{
	if (HasAuthority())
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
	else
	{
		SRV_SetSpeed(Speed);
	}
}

void AB_BaseCharacter::SetCharacterMovementMode(EMovementMode NewMode)
{
	GetCharacterMovement()->SetMovementMode(NewMode);
}

void AB_BaseCharacter::SetMovementMode_Implementation(E_MovementType MovementType)
{
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (!MoveComp)
	{
		return;
	}

	switch (MovementType)
	{
	case E_MovementType::Walk:
		MoveComp->MaxWalkSpeed = WalkSpeed;
		break;
	case E_MovementType::Run:
		MoveComp->MaxWalkSpeed = RunSpeed;
		break;
	case E_MovementType::Sprint:
		MoveComp->MaxWalkSpeed = SprintSpeed;
		break;
	default:
		break;
	}
}

void AB_BaseCharacter::Jump_Custom()
{
	if (HasAuthority())
	{
		Jump();
	}
	else
	{
		SRV_Jump();
	}
}

//========================================
// HITSTOP FUNCTIONS
//========================================

void AB_BaseCharacter::StartHitstop(float Duration)
{
	if (bIsInHitstop) return;

	bIsInHitstop = true;
	CustomTimeDilation = 0.0001f; // Nearly frozen

	// Set timer to end hitstop
	GetWorld()->GetTimerManager().SetTimer(
		HitstopTimerHandle,
		this,
		&AB_BaseCharacter::StopHitstop,
		Duration,
		false
	);
}

void AB_BaseCharacter::StopHitstop()
{
	if (!bIsInHitstop) return;

	bIsInHitstop = false;
	CustomTimeDilation = 1.0f; // Normal speed

	GetWorld()->GetTimerManager().ClearTimer(HitstopTimerHandle);
	OnHitstopEnd.Broadcast(0.0f);
}

//========================================
// STAT/STATUS FUNCTIONS
//========================================

bool AB_BaseCharacter::IsStatusEffectActive(FGameplayTag StatusEffectTag) const
{
	// StatusEffectManager uses HasStatusEffect with UPDA_StatusEffect*, not FGameplayTag
	// For now, return false - this would need custom lookup by tag
	// TODO: Extend UAC_StatusEffectManager to support tag-based lookup if needed
	return false;
}

FStatInfo AB_BaseCharacter::GetStat(FGameplayTag StatTag) const
{
	FStatInfo Result;
	if (StatManager)
	{
		if (UB_Stat* Stat = StatManager->GetStat(StatTag))
		{
			Result.Tag = StatTag;
			Result.Value = Stat->CurrentValue;
			Result.MaxValue = Stat->MaxValue;
		}
	}
	return Result;
}

APC_SoulslikeFramework* AB_BaseCharacter::GetSoulslikeController() const
{
	AController* OwnerController = GetController();
	if (OwnerController)
	{
		return Cast<APC_SoulslikeFramework>(OwnerController);
	}
	return nullptr;
}

//========================================
// SERVER RPC IMPLEMENTATIONS
//========================================

void AB_BaseCharacter::SRV_PlayMontage_Implementation(UAnimMontage* Montage, float PlayRate, float StartPos, FName StartSection)
{
	MC_PlayMontage(Montage, PlayRate, StartPos, StartSection);
}

void AB_BaseCharacter::SRV_SpawnNiagaraOneshotAttached_Implementation(UNiagaraSystem* System, USceneComponent* AttachComponent, FName SocketName, FVector Location, FRotator Rotation)
{
	MC_SpawnNiagaraOneshotAttached(System, AttachComponent, SocketName, Location, Rotation);
}

void AB_BaseCharacter::SRV_SpawnNiagaraOneshot_Implementation(UNiagaraSystem* System, FVector Location, FRotator Rotation)
{
	MC_SpawnNiagaraOneshot(System, Location, Rotation);
}

void AB_BaseCharacter::SRV_SpawnPickupItem_Implementation(TSubclassOf<AB_PickupItem> ItemClass, FVector Location, FRotator Rotation)
{
	if (HasAuthority() && ItemClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<AB_PickupItem>(ItemClass, Location, Rotation, SpawnParams);
	}
}

void AB_BaseCharacter::SRV_SpawnActor_Implementation(TSubclassOf<AActor> ActorClass, FTransform Transform)
{
	if (HasAuthority() && ActorClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(ActorClass, Transform, SpawnParams);
	}
}

void AB_BaseCharacter::SRV_DestroyActor_Implementation(AActor* ActorToDestroy)
{
	if (HasAuthority() && ActorToDestroy)
	{
		ActorToDestroy->Destroy();
	}
}

void AB_BaseCharacter::SRV_SetSpeed_Implementation(float NewSpeed)
{
	MC_SetSpeed(NewSpeed);
}

void AB_BaseCharacter::SRV_Jump_Implementation()
{
	MC_Jump();
}

//========================================
// MULTICAST RPC IMPLEMENTATIONS
//========================================

void AB_BaseCharacter::MC_PlayMontage_Implementation(UAnimMontage* Montage, float PlayRate, float StartPos, FName StartSection)
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(Montage, PlayRate, EMontagePlayReturnType::MontageLength, StartPos);
		if (!StartSection.IsNone())
		{
			AnimInstance->Montage_JumpToSection(StartSection, Montage);
		}
	}
}

void AB_BaseCharacter::MC_SpawnNiagaraOneshotAttached_Implementation(UNiagaraSystem* System, USceneComponent* AttachComponent, FName SocketName, FVector Location, FRotator Rotation)
{
	if (System && AttachComponent)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			System,
			AttachComponent,
			SocketName,
			Location,
			Rotation,
			EAttachLocation::KeepRelativeOffset,
			true // bAutoDestroy
		);
	}
}

void AB_BaseCharacter::MC_SpawnNiagaraOneshot_Implementation(UNiagaraSystem* System, FVector Location, FRotator Rotation)
{
	if (System)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			System,
			Location,
			Rotation,
			FVector(1.0f),
			true, // bAutoDestroy
			true, // bAutoActivate
			ENCPoolMethod::None,
			true // bPreCullCheck
		);
	}
}

void AB_BaseCharacter::MC_SetSpeed_Implementation(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AB_BaseCharacter::MC_Jump_Implementation()
{
	Jump();
}

//========================================
// BPI_GENERIC_CHARACTER IMPLEMENTATIONS
//========================================

void AB_BaseCharacter::SpawnActorReplicated_Implementation(TSubclassOf<AActor> ActorClass, FTransform Transform, ESpawnActorCollisionHandlingMethod CollisionMethod, AActor* ActorOwner, APawn* InstigatorPawn)
{
	if (ActorClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = CollisionMethod;
		SpawnParams.Owner = ActorOwner;
		SpawnParams.Instigator = InstigatorPawn;
		GetWorld()->SpawnActor<AActor>(ActorClass, Transform, SpawnParams);
	}
}

void AB_BaseCharacter::PlaySoftSoundAtLocation_Implementation(const TSoftObjectPtr<USoundBase>& SoundBase, FVector Location, FRotator Rotation, double Volume, double Pitch, double StartTime, USoundAttenuation* Attenuation, USoundConcurrency* Concurrency, AActor* ActorOwner, UInitialActiveSoundParams* InitialParams)
{
	if (!SoundBase.IsNull())
	{
		if (USoundBase* LoadedSound = SoundBase.LoadSynchronous())
		{
			UGameplayStatics::PlaySoundAtLocation(this, LoadedSound, Location, Rotation, Volume, Pitch, StartTime, Attenuation, Concurrency, ActorOwner);
		}
	}
}

USceneComponent* AB_BaseCharacter::GetHomingPositionComponent_Implementation()
{
	return ProjectileHomingPosition ? ProjectileHomingPosition : GetMesh();
}

bool AB_BaseCharacter::GetMeshInitialized_Implementation()
{
	return GetMesh() != nullptr && GetMesh()->GetSkeletalMeshAsset() != nullptr;
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
	if (ProjectileClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = CollisionMethod;
		SpawnParams.Owner = ActorOwner;
		SpawnParams.Instigator = InstigatorPawn;

		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, InitialTransform, SpawnParams);
		// Projectile spawned - initialization is handled by the projectile's BeginPlay
	}
}

void AB_BaseCharacter::OpenContainer_Implementation(UAnimMontage* Montage, AB_Container* Container)
{
	if (Montage)
	{
		PlayAnimMontage(Montage);
	}
}

void AB_BaseCharacter::StartWorldCameraShake_Implementation(TSubclassOf<UCameraShakeBase> Shake, FVector Epicenter, double InnerRadius, double OuterRadius, double Falloff, bool bOrientTowardsEpicenter)
{
	UGameplayStatics::PlayWorldCameraShake(this, Shake, Epicenter, InnerRadius, OuterRadius, Falloff, bOrientTowardsEpicenter);
}

void AB_BaseCharacter::PlaySoftNiagaraOneshotAtLocationReplicated_Implementation(const TSoftObjectPtr<UNiagaraSystem>& VFXSystem, FVector Location, FRotator Rotation, bool bAutoDestroy, bool bAutoActivate, bool bPreCullCheck)
{
	if (!VFXSystem.IsNull())
	{
		if (UNiagaraSystem* LoadedSystem = VFXSystem.LoadSynchronous())
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				LoadedSystem,
				Location,
				Rotation,
				FVector(1.0f),
				bAutoDestroy,
				bAutoActivate,
				ENCPoolMethod::None,
				bPreCullCheck
			);
		}
	}
}

void AB_BaseCharacter::EnableRagdoll_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
}

void AB_BaseCharacter::PlayIkReaction_Implementation(double IKScale)
{
	// IK reaction implementation - typically handled by animation blueprint
	// Set IK blend weight or trigger IK animation
}

void AB_BaseCharacter::GenericLocationAndRotationLerp_Implementation(double Scale, FVector TargetLocation, FRotator TargetRotation)
{
	LerpTargetLocation = TargetLocation;
	LerpTargetRotation = TargetRotation;
	LerpSpeed = Scale;
	LerpAlpha = 0.0f;
	bIsLerpingLocation = true;
	bIsLerpingRotation = true;
}

void AB_BaseCharacter::GenericRotationLerp_Implementation(double Scale, FRotator TargetRotation)
{
	LerpTargetRotation = TargetRotation;
	LerpSpeed = Scale;
	LerpAlpha = 0.0f;
	bIsLerpingRotation = true;
}

void AB_BaseCharacter::GenericLocationLerp_Implementation(double Scale, FVector TargetLocation)
{
	LerpTargetLocation = TargetLocation;
	LerpSpeed = Scale;
	LerpAlpha = 0.0f;
	bIsLerpingLocation = true;
}

void AB_BaseCharacter::TryClimbLadder_Implementation(AB_Ladder* Ladder, bool bIsTopDown)
{
	// Delegate to Ladder Manager component if available
	// For now, basic implementation
	if (Ladder)
	{
		// Set climbing state
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void AB_BaseCharacter::StopActiveMontage_Implementation(double BlendOutDuration)
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Stop(BlendOutDuration);
	}
}

UAnimInstance* AB_BaseCharacter::GetSoulslikeAnimInstance_Implementation()
{
	return GetMesh()->GetAnimInstance();
}

void AB_BaseCharacter::OpenDoor_Implementation(UAnimMontage* Montage, AB_Door* Door)
{
	if (Montage)
	{
		PlayAnimMontage(Montage);
	}
}
