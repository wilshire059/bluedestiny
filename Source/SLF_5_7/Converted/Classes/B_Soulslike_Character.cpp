#include "B_Soulslike_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AC_InputBuffer.h"
#include "Components/AC_LadderManager.h"
#include "Components/AC_ProgressManager.h"
#include "Components/AC_AI_InteractionManager.h"
#include "Classes/PC_SoulslikeFramework.h"
#include "Classes/B_Ladder.h"
#include "Classes/B_PickupItem.h"
#include "DataAssets/PDA_Action.h"
#include "Interfaces/BPI_Interactable.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "LevelSequence.h"
#include "Animation/AnimMontage.h"

AB_Soulslike_Character::AB_Soulslike_Character()
{
	//========================================
	// OVERRIDE MESH POSITION
	//========================================
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -91.0f));

	//========================================
	// OVERRIDE ROTATION RATE
	//========================================
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1080.0f, 0.0f);

	//========================================
	// CAMERA BOOM (SPRING ARM)
	//========================================
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 25.0f);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.0f;
	SpringArm->bDoCollisionTest = true;

	//========================================
	// FOLLOW CAMERA
	//========================================
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->FieldOfView = 90.0f;
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);

	//========================================
	// TARGET SWAP TRACER
	//========================================
	TargetSwapTracer = CreateDefaultSubobject<USceneComponent>(TEXT("TargetSwapTracer"));
	TargetSwapTracer->SetupAttachment(RootComponent);
	TargetSwapTracer->SetRelativeLocation(FVector(142.5f, 0.0f, 0.0f));

	//========================================
	// NPC LOOK AT POINT
	//========================================
	NPCLookAtPoint = CreateDefaultSubobject<USphereComponent>(TEXT("NPCLookAtPoint"));
	NPCLookAtPoint->SetupAttachment(RootComponent);
	NPCLookAtPoint->InitSphereRadius(32.0f);
	NPCLookAtPoint->SetRelativeLocation(FVector(0.0f, 0.0f, 71.0f));
	NPCLookAtPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//========================================
	// CHAOS FORCE FIELD
	//========================================
	ChaosForceField = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChaosForceField"));
	ChaosForceField->SetupAttachment(RootComponent);

	//========================================
	// MODULAR MESH COMPONENTS
	//========================================
	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(GetMesh());
	HeadMesh->SetLeaderPoseComponent(GetMesh());

	UpperBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperBodyMesh"));
	UpperBodyMesh->SetupAttachment(GetMesh());
	UpperBodyMesh->SetLeaderPoseComponent(GetMesh());

	LowerBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBodyMesh"));
	LowerBodyMesh->SetupAttachment(GetMesh());
	LowerBodyMesh->SetLeaderPoseComponent(GetMesh());

	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	ArmsMesh->SetupAttachment(GetMesh());
	ArmsMesh->SetLeaderPoseComponent(GetMesh());

	//========================================
	// ADDITIONAL COMPONENTS
	//========================================
	InputBuffer = CreateDefaultSubobject<UAC_InputBuffer>(TEXT("InputBuffer"));
	LadderManager = CreateDefaultSubobject<UAC_LadderManager>(TEXT("LadderManager"));

	//========================================
	// DEFAULT VALUES
	//========================================
	CurrentTarget = nullptr;
	bIsTargetLocked = false;
	bIsLerpingToTarget = false;
	TargetLockRange = 1500.0f;
	TargetLockRotationSpeed = 10.0f;

	bIsGuarding = false;
	bIsCrouched = false;
	bIsClimbing = false;
	bIsClimbingDownFromTop = false;
	CurrentLadder = nullptr;

	ExecutionTarget = nullptr;
	bIsBeingExecuted = false;

	LastRestingPointLocation = FVector::ZeroVector;
	LastRestingPointRotation = FRotator::ZeroRotator;

	//========================================
	// ACTOR TAG
	//========================================
	Tags.Add(FName("Player"));
}

void AB_Soulslike_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AB_Soulslike_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update target lock rotation if locked
	if (bIsTargetLocked && CurrentTarget)
	{
		UpdateTargetLockRotation(DeltaTime);
	}
}

//========================================
// TARGET LOCK FUNCTIONS
//========================================

void AB_Soulslike_Character::HandleTargetLock()
{
	if (bIsTargetLocked)
	{
		ResetLockOn();
	}
	else
	{
		AActor* Target = FindNearestTarget();
		if (Target)
		{
			LockOnTarget(Target);
		}
	}
}

void AB_Soulslike_Character::LockOnTarget(AActor* Target)
{
	if (!Target) return;

	CurrentTarget = Target;
	bIsTargetLocked = true;

	// Show lock-on widget on target
	ToggleLockonWidgetOnTarget(true);

	// Disable camera rotation to allow smooth lock-on
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AB_Soulslike_Character::ResetLockOn()
{
	// Hide lock-on widget
	ToggleLockonWidgetOnTarget(false);

	CurrentTarget = nullptr;
	bIsTargetLocked = false;

	// Re-enable camera rotation
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	OnTargetLockRotationEnd.Broadcast();
}

void AB_Soulslike_Character::ToggleLockonWidgetOnTarget(bool bVisible)
{
	if (CurrentTarget)
	{
		if (CurrentTarget->GetClass()->ImplementsInterface(UBPI_Generic_Character::StaticClass()))
		{
			IBPI_Generic_Character::Execute_ToggleLockonWidget(CurrentTarget, bVisible);
		}
	}
}

AActor* AB_Soulslike_Character::FindNearestTarget()
{
	TArray<AActor*> PotentialTargets;
	PerformTargetLockTrace(PotentialTargets);

	if (PotentialTargets.Num() == 0)
	{
		return nullptr;
	}

	// Find closest target
	AActor* ClosestTarget = nullptr;
	float ClosestDistance = MAX_FLT;

	for (AActor* Target : PotentialTargets)
	{
		float Distance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestTarget = Target;
		}
	}

	return ClosestTarget;
}

void AB_Soulslike_Character::SwitchTarget(bool bSwitchRight)
{
	if (!bIsTargetLocked) return;

	TArray<AActor*> PotentialTargets;
	PerformTargetLockTrace(PotentialTargets);

	if (PotentialTargets.Num() <= 1) return;

	// Remove current target from list
	PotentialTargets.Remove(CurrentTarget);

	// Find target based on screen position (left or right)
	AActor* BestTarget = nullptr;
	float BestScore = bSwitchRight ? -MAX_FLT : MAX_FLT;

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	FVector2D CurrentTargetScreen;
	PC->ProjectWorldLocationToScreen(CurrentTarget->GetActorLocation(), CurrentTargetScreen);

	for (AActor* Target : PotentialTargets)
	{
		FVector2D TargetScreen;
		if (PC->ProjectWorldLocationToScreen(Target->GetActorLocation(), TargetScreen))
		{
			float XDiff = TargetScreen.X - CurrentTargetScreen.X;
			if (bSwitchRight && XDiff > 0 && XDiff < BestScore)
			{
				BestScore = XDiff;
				BestTarget = Target;
			}
			else if (!bSwitchRight && XDiff < 0 && XDiff > BestScore)
			{
				BestScore = XDiff;
				BestTarget = Target;
			}
		}
	}

	if (BestTarget)
	{
		ToggleLockonWidgetOnTarget(false);
		CurrentTarget = BestTarget;
		ToggleLockonWidgetOnTarget(true);
	}
}

void AB_Soulslike_Character::UpdateTargetLockRotation(float DeltaTime)
{
	if (!CurrentTarget) return;

	FVector TargetLocation = CurrentTarget->GetActorLocation();
	FVector MyLocation = GetActorLocation();

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation);

	// Only rotate yaw
	FRotator CurrentRotation = GetControlRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, LookAtRotation, DeltaTime, TargetLockRotationSpeed);
	NewRotation.Pitch = CurrentRotation.Pitch;
	NewRotation.Roll = 0.0f;

	GetController()->SetControlRotation(NewRotation);
}

void AB_Soulslike_Character::PerformTargetLockTrace(TArray<AActor*>& OutTargets)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<AActor*> OverlappedActors;

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetActorLocation(),
		TargetLockRange,
		ObjectTypes,
		nullptr,
		ActorsToIgnore,
		OverlappedActors
	);

	for (AActor* Actor : OverlappedActors)
	{
		// Check if actor has "Enemy" tag
		if (Actor->ActorHasTag(FName("Enemy")))
		{
			OutTargets.Add(Actor);
		}
	}
}

//========================================
// EXECUTION FUNCTIONS
//========================================

void AB_Soulslike_Character::OnExecuted(AActor* Attacker)
{
	bIsBeingExecuted = true;
	// Play execution victim animation
}

void AB_Soulslike_Character::OnBackstabbed(AActor* Attacker)
{
	bIsBeingExecuted = true;
	// Play backstab victim animation
}

void AB_Soulslike_Character::OnExecutionStarted(AActor* Target)
{
	ExecutionTarget = Target;
	// Play execution attacker animation
}

void AB_Soulslike_Character::SetExecutionTarget(AActor* Target)
{
	ExecutionTarget = Target;
}

bool AB_Soulslike_Character::GetIsBehindTarget() const
{
	if (!CurrentTarget) return false;

	FVector TargetForward = CurrentTarget->GetActorForwardVector();
	FVector ToTarget = (CurrentTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	float DotProduct = FVector::DotProduct(TargetForward, ToTarget);

	// If dot product is negative, we're behind the target
	return DotProduct < -0.5f;
}

//========================================
// MOVEMENT/STATE FUNCTIONS
//========================================

void AB_Soulslike_Character::ToggleCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
		bIsCrouched = false;
	}
	else
	{
		Crouch();
		bIsCrouched = true;
	}
}

bool AB_Soulslike_Character::GetIsCrouched() const
{
	return bIsCrouched;
}

bool AB_Soulslike_Character::GetIsGuarding() const
{
	return bIsGuarding;
}

void AB_Soulslike_Character::SetGuardState(bool bGuarding)
{
	bIsGuarding = bGuarding;
}

bool AB_Soulslike_Character::GetIsMoving2D() const
{
	FVector Velocity = GetVelocity();
	return FVector2D(Velocity.X, Velocity.Y).Size() > 10.0f;
}

bool AB_Soulslike_Character::IsEnemyDead(AActor* Enemy) const
{
	if (!Enemy) return true;

	if (Enemy->GetClass()->ImplementsInterface(UBPI_Generic_Character::StaticClass()))
	{
		// Check if enemy is dead via interface or component
		// This would typically check the combat manager
	}

	return false;
}

//========================================
// INPUT/ACTION FUNCTIONS
//========================================

void AB_Soulslike_Character::ConsumeInputBuffer()
{
	if (InputBuffer)
	{
		InputBuffer->ConsumeInputBuffer();
	}
}

void AB_Soulslike_Character::ExecuteActionImmediately(UPDA_Action* Action)
{
	if (ActionManager && Action)
	{
		// ActionManager uses PerformAction with FGameplayTag
		// Need to look up the action tag - for now use primary asset ID as tag
		FPrimaryAssetId AssetId = Action->GetPrimaryAssetId();
		FGameplayTag ActionTag = FGameplayTag::RequestGameplayTag(FName(AssetId.PrimaryAssetName.ToString()), false);
		if (ActionTag.IsValid())
		{
			ActionManager->PerformAction(ActionTag);
		}
	}
}

void AB_Soulslike_Character::QueueAction(UPDA_Action* Action)
{
	if (InputBuffer && Action)
	{
		// InputBuffer uses QueueAction with FGameplayTag
		FPrimaryAssetId AssetId = Action->GetPrimaryAssetId();
		FGameplayTag ActionTag = FGameplayTag::RequestGameplayTag(FName(AssetId.PrimaryAssetName.ToString()), false);
		if (ActionTag.IsValid())
		{
			InputBuffer->QueueAction(ActionTag);
		}
	}
}

void AB_Soulslike_Character::SwitchInputContext(const TArray<UInputMappingContext*>& ContextsToEnable, const TArray<UInputMappingContext*>& ContextsToDisable)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if (!Subsystem) return;

	// Remove disabled contexts
	for (UInputMappingContext* Context : ContextsToDisable)
	{
		if (Context)
		{
			Subsystem->RemoveMappingContext(Context);
		}
	}

	// Add enabled contexts
	for (UInputMappingContext* Context : ContextsToEnable)
	{
		if (Context)
		{
			Subsystem->AddMappingContext(Context, 0);
		}
	}
}

float AB_Soulslike_Character::GetAxisValue(FName AxisName) const
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		return PC->GetInputAxisValue(AxisName);
	}
	return 0.0f;
}

//========================================
// LADDER FUNCTIONS
//========================================

void AB_Soulslike_Character::SetCurrentLadder(AB_Ladder* Ladder)
{
	CurrentLadder = Ladder;
}

void AB_Soulslike_Character::SetIsClimbing(bool bClimbing)
{
	bIsClimbing = bClimbing;
	if (bClimbing)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

void AB_Soulslike_Character::SetIsClimbingDownFromTop(bool bClimbingDown)
{
	bIsClimbingDownFromTop = bClimbingDown;
}

//========================================
// EQUIPMENT FUNCTIONS
//========================================

UAC_EquipmentManager* AB_Soulslike_Character::GetEquipmentComponent() const
{
	return EquipmentManager;
}

bool AB_Soulslike_Character::AreBothWeaponSlotsActive() const
{
	if (EquipmentManager)
	{
		return EquipmentManager->AreBothWeaponSlotsActive();
	}
	return false;
}

bool AB_Soulslike_Character::DoesEquipmentSupportGuard() const
{
	if (EquipmentManager)
	{
		// Check if we have a valid guard sequence (indicates we can block)
		return EquipmentManager->ActiveBlockSequence != nullptr;
	}
	return false;
}

int32 AB_Soulslike_Character::GetActiveWeaponSlot() const
{
	if (EquipmentManager)
	{
		return static_cast<int32>(EquipmentManager->GetActiveWeaponSlot());
	}
	return 0;
}

bool AB_Soulslike_Character::IsDualWieldPossible() const
{
	if (EquipmentManager)
	{
		// Check if both weapon slots have items equipped
		return EquipmentManager->AreBothWeaponSlotsActive();
	}
	return false;
}

//========================================
// SAVE/LOAD FUNCTIONS
//========================================

void AB_Soulslike_Character::OnSpawnedFromSave(const FString& SaveData)
{
	OnDataLoaded.Broadcast(SaveData);
	OnSpawnedFromSaveDelegate.Broadcast();
}

void AB_Soulslike_Character::SerializeAllDataForSaving(TArray<FInstancedStruct>& OutData)
{
	// Collect data from all components that need to be saved
	if (StatManager)
	{
		// StatManager->SerializeForSave(OutData);
	}
	if (EquipmentManager)
	{
		// EquipmentManager->SerializeForSave(OutData);
	}
	if (InventoryManager)
	{
		// InventoryManager->SerializeForSave(OutData);
	}
}

bool AB_Soulslike_Character::GetSaveDataByTag(FGameplayTag SaveTag, FInstancedStruct& OutData) const
{
	APC_SoulslikeFramework* PC = GetSoulslikeController();
	if (PC)
	{
		// return PC->GetSaveDataByTag(SaveTag, OutData);
	}
	return false;
}

void AB_Soulslike_Character::SetSelectedClass(FGameplayTag ClassTag)
{
	SelectedClass = ClassTag;
}

FGameplayTag AB_Soulslike_Character::GetSelectedClass() const
{
	return SelectedClass;
}

void AB_Soulslike_Character::SetLastRestingPoint(FVector Location, FRotator Rotation)
{
	LastRestingPointLocation = Location;
	LastRestingPointRotation = Rotation;
}

//========================================
// MODULAR MESH FUNCTIONS
//========================================

void AB_Soulslike_Character::RefreshModularPieces()
{
	// Refresh all modular mesh pieces from equipment
	if (EquipmentManager)
	{
		// Get equipped armor and update meshes
	}
}

FModularMeshData AB_Soulslike_Character::MakeModularMeshData() const
{
	FModularMeshData Data;
	// Populate with current mesh data
	return Data;
}

void AB_Soulslike_Character::SetSoftSkeletalMeshAsset(USkeletalMeshComponent* MeshComponent, TSoftObjectPtr<USkeletalMesh> MeshAsset)
{
	if (MeshComponent && !MeshAsset.IsNull())
	{
		USkeletalMesh* LoadedMesh = MeshAsset.LoadSynchronous();
		if (LoadedMesh)
		{
			MeshComponent->SetSkeletalMesh(LoadedMesh);
		}
	}
}

//========================================
// INTERACTION FUNCTIONS
//========================================

void AB_Soulslike_Character::OnInteract()
{
	OnInteractPressed.Broadcast();

	AB_Interactable* Closest = GetClosestInteractable();
	if (Closest)
	{
		IBPI_Interactable::Execute_OnInteract(Closest, this);
	}
}

void AB_Soulslike_Character::AddToNearbyInteractables(AB_Interactable* Interactable)
{
	if (Interactable && !NearbyInteractables.Contains(Interactable))
	{
		NearbyInteractables.Add(Interactable);
	}
}

void AB_Soulslike_Character::RemoveFromNearbyInteractables(AB_Interactable* Interactable)
{
	NearbyInteractables.Remove(Interactable);
}

AB_Interactable* AB_Soulslike_Character::GetClosestInteractable() const
{
	if (NearbyInteractables.Num() == 0) return nullptr;

	AB_Interactable* Closest = nullptr;
	float ClosestDist = MAX_FLT;

	for (AB_Interactable* Interactable : NearbyInteractables)
	{
		if (Interactable)
		{
			float Dist = FVector::Dist(GetActorLocation(), Interactable->GetActorLocation());
			if (Dist < ClosestDist)
			{
				ClosestDist = Dist;
				Closest = Interactable;
			}
		}
	}

	return Closest;
}

//========================================
// UTILITY FUNCTIONS
//========================================

bool AB_Soulslike_Character::ActorTagMatches(AActor* Actor, FName Tag) const
{
	return Actor && Actor->ActorHasTag(Tag);
}

UUserWidget* AB_Soulslike_Character::GetPlayerHUD() const
{
	APC_SoulslikeFramework* PC = GetSoulslikeController();
	if (PC)
	{
		return PC->GetPlayerHUD_Implementation();
	}
	return nullptr;
}

UAC_ProgressManager* AB_Soulslike_Character::GetProgressManager() const
{
	APC_SoulslikeFramework* PC = GetSoulslikeController();
	if (PC)
	{
		return PC->GetProgressManager();
	}
	return nullptr;
}

void AB_Soulslike_Character::LootItemToInventory(AB_PickupItem* Item)
{
	if (Item && InventoryManager)
	{
		// Get item data and add to inventory
		// InventoryManager->AddItem(Item->GetItemData());
		Item->Destroy();
	}
}

// Note: ResetCameraView moved to BPI_Player interface implementations section

void AB_Soulslike_Character::SendBigScreenMessage(const FText& Message, float Duration)
{
	APC_SoulslikeFramework* PC = GetSoulslikeController();
	if (PC)
	{
		// BPI_Controller::SendBigScreenMessage takes (Text, GradientMaterial, bBackdrop, PlayRate)
		IBPI_Controller::Execute_SendBigScreenMessage(PC, Message, nullptr, false, static_cast<double>(Duration));
	}
}

//========================================
// CHAOS FIELD FUNCTIONS
//========================================

void AB_Soulslike_Character::EnableChaosDestroy_Implementation()
{
	if (AActor* Child = ChaosForceField->GetChildActor())
	{
		Child->SetActorHiddenInGame(false);
		Child->SetActorEnableCollision(true);
	}
}

void AB_Soulslike_Character::DisableChaosDestroy_Implementation()
{
	if (AActor* Child = ChaosForceField->GetChildActor())
	{
		Child->SetActorHiddenInGame(true);
		Child->SetActorEnableCollision(false);
	}
}

//========================================
// BPI_Player INTERFACE
//========================================

void AB_Soulslike_Character::OnInteractableTraced_Implementation(AB_Interactable* Interactable)
{
	// Update UI to show interaction prompt
	if (Interactable)
	{
		AddToNearbyInteractables(Interactable);
	}
}

void AB_Soulslike_Character::OnRest_Implementation(AActor* Campfire)
{
	// Handle resting at campfire/bonfire
	if (Campfire)
	{
		SetLastRestingPoint(Campfire->GetActorLocation(), Campfire->GetActorRotation());

		// Heal to full
		if (StatManager)
		{
			// StatManager->RestoreAllStats();
		}

		// Open rest menu
	}
}

void AB_Soulslike_Character::OnLootItem_Implementation(AActor* Item)
{
	AB_PickupItem* PickupItem = Cast<AB_PickupItem>(Item);
	if (PickupItem)
	{
		LootItemToInventory(PickupItem);
	}
}

void AB_Soulslike_Character::TriggerChaosField_Implementation(bool bEnable)
{
	if (bEnable)
	{
		EnableChaosDestroy_Implementation();
	}
	else
	{
		DisableChaosDestroy_Implementation();
	}
}

// Camera Functions
void AB_Soulslike_Character::ResetCameraView_Implementation(double TimeScale)
{
	// Reset camera to default position with optional time scaling
	if (SpringArm)
	{
		SpringArm->TargetArmLength = 300.0f;
		SpringArm->SocketOffset = FVector(0.0f, 0.0f, 25.0f);
	}

	OnCameraResetFinished.Broadcast();
}

void AB_Soulslike_Character::StopActiveCameraSequence_Implementation()
{
	// Stop any currently playing camera sequence
	// Implementation would depend on how camera sequences are tracked
}

void AB_Soulslike_Character::PlayCameraSequence_Implementation(ULevelSequence* Sequence, FMovieSceneSequencePlaybackSettings Settings)
{
	// Play a camera sequence with the given settings
	// Would typically use ULevelSequencePlayer to play the sequence
}

// Combat Functions
void AB_Soulslike_Character::PlayBackstabMontage_Implementation(UAnimMontage* Montage, FGameplayTag ExecutionTag)
{
	// Play backstab execution montage
	if (Montage && GetMesh() && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(Montage);
	}
}

void AB_Soulslike_Character::PlayExecuteMontage_Implementation(UAnimMontage* Montage, FGameplayTag ExecutionTag)
{
	// Play execution montage (similar to backstab)
	if (Montage && GetMesh() && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(Montage);
	}
}

void AB_Soulslike_Character::OnTargetLocked_Implementation(bool bTargetLocked, bool bRotateTowards)
{
	// Handle target lock state change
	bIsTargetLocked = bTargetLocked;
	// bRotateTowards would typically control camera/character rotation behavior
}

// Interaction Functions
void AB_Soulslike_Character::DiscoverRestingPoint_Implementation(UAnimMontage* InteractionMontage, AActor* Point)
{
	// Handle discovering a new resting point
	if (Point)
	{
		// Play interaction montage if provided
		if (InteractionMontage && GetMesh() && GetMesh()->GetAnimInstance())
		{
			GetMesh()->GetAnimInstance()->Montage_Play(InteractionMontage);
		}
	}
}

void AB_Soulslike_Character::OnDialogStarted_Implementation(UAC_AI_InteractionManager* DialogComponent)
{
	// Handle dialog starting with an NPC
	// Would typically lock player input and show dialog UI
}

void AB_Soulslike_Character::OnNpcTraced_Implementation(AActor* NPC)
{
	// Handle NPC trace for interaction
	// Could show interaction prompt or highlight NPC
}

// Character Access
AActor* AB_Soulslike_Character::GetSoulslikeCharacter_Implementation()
{
	return this;
}

void AB_Soulslike_Character::ToggleCrouchReplicated_Implementation()
{
	// Toggle crouch state - this would be replicated across network
	// Implementation depends on movement component setup
}

// Equipment Visual Functions
void AB_Soulslike_Character::ResetGreaves_Implementation()
{
	// Reset greaves to default mesh
	// Would restore the default skeletal mesh for leg armor
}

void AB_Soulslike_Character::ResetGloves_Implementation()
{
	// Reset gloves to default mesh
}

void AB_Soulslike_Character::ResetArmor_Implementation()
{
	// Reset armor to default mesh
}

void AB_Soulslike_Character::ResetHeadpiece_Implementation()
{
	// Reset headpiece to default mesh
}

void AB_Soulslike_Character::ChangeGreaves_Implementation(USkeletalMesh* NewMesh)
{
	// Change greaves mesh
	if (NewMesh)
	{
		// Apply new mesh to greaves component
	}
}

void AB_Soulslike_Character::ChangeGloves_Implementation(USkeletalMesh* NewMesh)
{
	// Change gloves mesh
	if (NewMesh)
	{
		// Apply new mesh to gloves component
	}
}

void AB_Soulslike_Character::ChangeArmor_Implementation(USkeletalMesh* NewMesh)
{
	// Change armor mesh
	if (NewMesh)
	{
		// Apply new mesh to armor component
	}
}

void AB_Soulslike_Character::ChangeHeadpiece_Implementation(USkeletalMesh* NewMesh)
{
	// Change headpiece mesh
	if (NewMesh)
	{
		// Apply new mesh to headpiece component
	}
}
