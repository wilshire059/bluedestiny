#pragma once

#include "CoreMinimal.h"
#include "Classes/B_BaseCharacter.h"
#include "Interfaces/BPI_Player.h"
#include "Interfaces/BPI_DestructibleHelper.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Classes/B_Interactable.h"
#include "InputMappingContext.h"
#include "Structs/FModularMeshData.h"
#include "B_Soulslike_Character.generated.h"

// Forward declarations
class UAC_InputBuffer;
class UAC_LadderManager;
class AB_Ladder;
class UPDA_Action;
class UPDA_BaseCharacterInfo;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetLockRotationEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraResetFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputDetected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDataLoaded, const FString&, LoadedData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnedFromSave);

UCLASS()
class SLF_5_7_API AB_Soulslike_Character : public AB_BaseCharacter, public IBPI_Player, public IBPI_DestructibleHelper
{
	GENERATED_BODY()

public:
	AB_Soulslike_Character();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	//========================================
	// CAMERA COMPONENTS
	//========================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
	UCameraComponent* CameraComponent;

	//========================================
	// TARGETING COMPONENTS
	//========================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Targeting")
	USceneComponent* TargetSwapTracer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Targeting")
	USphereComponent* NPCLookAtPoint;

	//========================================
	// CHAOS/PHYSICS COMPONENTS
	//========================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Physics")
	UChildActorComponent* ChaosForceField;

	//========================================
	// MODULAR MESH COMPONENTS
	//========================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|ModularMesh")
	USkeletalMeshComponent* HeadMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|ModularMesh")
	USkeletalMeshComponent* UpperBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|ModularMesh")
	USkeletalMeshComponent* LowerBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|ModularMesh")
	USkeletalMeshComponent* ArmsMesh;

	//========================================
	// ADDITIONAL COMPONENTS
	//========================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAC_InputBuffer* InputBuffer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAC_LadderManager* LadderManager;

	//========================================
	// TARGET LOCK PROPERTIES
	//========================================

	UPROPERTY(BlueprintReadOnly, Category = "Targeting")
	AActor* CurrentTarget;

	UPROPERTY(BlueprintReadOnly, Category = "Targeting")
	bool bIsTargetLocked;

	UPROPERTY(BlueprintReadOnly, Category = "Targeting")
	bool bIsLerpingToTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetLockRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetLockRotationSpeed;

	//========================================
	// STATE PROPERTIES
	//========================================

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsGuarding;

	// Note: bIsCrouched is inherited from ACharacter

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsClimbing;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsClimbingDownFromTop;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	AB_Ladder* CurrentLadder;

	//========================================
	// EXECUTION PROPERTIES
	//========================================

	UPROPERTY(BlueprintReadOnly, Category = "Execution")
	AActor* ExecutionTarget;

	UPROPERTY(BlueprintReadOnly, Category = "Execution")
	bool bIsBeingExecuted;

	//========================================
	// SAVE/LOAD PROPERTIES
	//========================================

	UPROPERTY(BlueprintReadOnly, Category = "Save")
	FVector LastRestingPointLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Save")
	FRotator LastRestingPointRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FGameplayTag SelectedClass;

	//========================================
	// NEARBY INTERACTABLES
	//========================================

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	TArray<AB_Interactable*> NearbyInteractables;

	//========================================
	// DELEGATES
	//========================================

	UPROPERTY(BlueprintAssignable, Category = "Events|Targeting")
	FOnTargetLockRotationEnd OnTargetLockRotationEnd;

	UPROPERTY(BlueprintAssignable, Category = "Events|Camera")
	FOnCameraResetFinished OnCameraResetFinished;

	UPROPERTY(BlueprintAssignable, Category = "Events|Input")
	FOnInputDetected OnInputDetected;

	UPROPERTY(BlueprintAssignable, Category = "Events|Input")
	FOnInteractPressed OnInteractPressed;

	UPROPERTY(BlueprintAssignable, Category = "Events|Save")
	FOnCharacterDataLoaded OnDataLoaded;

	UPROPERTY(BlueprintAssignable, Category = "Events|Save")
	FOnSpawnedFromSave OnSpawnedFromSaveDelegate;

	//========================================
	// TARGET LOCK FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void HandleTargetLock();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void LockOnTarget(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void ResetLockOn();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void ToggleLockonWidgetOnTarget(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	AActor* FindNearestTarget();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void SwitchTarget(bool bSwitchRight);

	//========================================
	// EXECUTION FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Execution")
	void OnExecuted(AActor* Attacker);

	UFUNCTION(BlueprintCallable, Category = "Execution")
	void OnBackstabbed(AActor* Attacker);

	UFUNCTION(BlueprintCallable, Category = "Execution")
	void OnExecutionStarted(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Execution")
	void SetExecutionTarget(AActor* Target);

	UFUNCTION(BlueprintPure, Category = "Execution")
	bool GetIsBehindTarget() const;

	//========================================
	// MOVEMENT/STATE FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ToggleCrouch();

	UFUNCTION(BlueprintPure, Category = "Movement")
	bool GetIsCrouched() const;

	UFUNCTION(BlueprintPure, Category = "Combat")
	bool GetIsGuarding() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetGuardState(bool bGuarding);

	UFUNCTION(BlueprintPure, Category = "Movement")
	bool GetIsMoving2D() const;

	UFUNCTION(BlueprintPure, Category = "Combat")
	bool IsEnemyDead(AActor* Enemy) const;

	//========================================
	// INPUT/ACTION FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ConsumeInputBuffer();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ExecuteActionImmediately(UPDA_Action* Action);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void QueueAction(UPDA_Action* Action);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SwitchInputContext(const TArray<UInputMappingContext*>& ContextsToEnable, const TArray<UInputMappingContext*>& ContextsToDisable);

	UFUNCTION(BlueprintPure, Category = "Input")
	float GetAxisValue(FName AxisName) const;

	//========================================
	// LADDER FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Ladder")
	void SetCurrentLadder(AB_Ladder* Ladder);

	UFUNCTION(BlueprintCallable, Category = "Ladder")
	void SetIsClimbing(bool bClimbing);

	UFUNCTION(BlueprintCallable, Category = "Ladder")
	void SetIsClimbingDownFromTop(bool bClimbingDown);

	//========================================
	// EQUIPMENT FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	UAC_EquipmentManager* GetEquipmentComponent() const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool AreBothWeaponSlotsActive() const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool DoesEquipmentSupportGuard() const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	int32 GetActiveWeaponSlot() const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsDualWieldPossible() const;

	//========================================
	// SAVE/LOAD FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Save")
	void OnSpawnedFromSave(const FString& SaveData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SerializeAllDataForSaving(TArray<FInstancedStruct>& OutData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool GetSaveDataByTag(FGameplayTag SaveTag, FInstancedStruct& OutData) const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetSelectedClass(FGameplayTag ClassTag);

	UFUNCTION(BlueprintPure, Category = "Save")
	FGameplayTag GetSelectedClass() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetLastRestingPoint(FVector Location, FRotator Rotation);

	//========================================
	// MODULAR MESH FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "ModularMesh")
	void RefreshModularPieces();

	UFUNCTION(BlueprintCallable, Category = "ModularMesh")
	FModularMeshData MakeModularMeshData() const;

	UFUNCTION(BlueprintCallable, Category = "ModularMesh")
	void SetSoftSkeletalMeshAsset(USkeletalMeshComponent* MeshComponent, TSoftObjectPtr<USkeletalMesh> MeshAsset);

	//========================================
	// INTERACTION FUNCTIONS
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnInteract();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void AddToNearbyInteractables(AB_Interactable* Interactable);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void RemoveFromNearbyInteractables(AB_Interactable* Interactable);

	UFUNCTION(BlueprintPure, Category = "Interaction")
	AB_Interactable* GetClosestInteractable() const;

	//========================================
	// UTILITY FUNCTIONS
	//========================================

	UFUNCTION(BlueprintPure, Category = "Utility")
	bool ActorTagMatches(AActor* Actor, FName Tag) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetPlayerHUD() const;

	UFUNCTION(BlueprintCallable, Category = "Progress")
	class UAC_ProgressManager* GetProgressManager() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LootItemToInventory(class AB_PickupItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ResetCameraView();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SendBigScreenMessage(const FText& Message, float Duration);

	//========================================
	// CHAOS FIELD FUNCTIONS (BPI_DestructibleHelper)
	//========================================

	UFUNCTION(BlueprintCallable, Category = "Physics")
	virtual void EnableChaosDestroy_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Physics")
	virtual void DisableChaosDestroy_Implementation() override;

	//========================================
	// BPI_Player INTERFACE
	//========================================

	virtual void OnInteractableTraced_Implementation(AB_Interactable* Interactable) override;
	virtual void OnRest_Implementation(AActor* Campfire) override;
	virtual void OnLootItem_Implementation(AActor* Item) override;
	virtual void TriggerChaosField_Implementation(bool bEnable) override;

protected:
	//========================================
	// INTERNAL HELPERS
	//========================================

	void UpdateTargetLockRotation(float DeltaTime);
	void PerformTargetLockTrace(TArray<AActor*>& OutTargets);
};
