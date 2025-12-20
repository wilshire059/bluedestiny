#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "BPI_Player.generated.h"

// Forward Declarations
class AB_Interactable;
class ULevelSequence;
class UAnimMontage;
class USkeletalMesh;
class UAC_AI_InteractionManager;

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_Player : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for player characters.
 * Matches Blueprint BPI_Player exactly.
 */
class SLF_5_7_API IBPI_Player
{
	GENERATED_BODY()

public:
	// ============================================================
	// CAMERA FUNCTIONS
	// ============================================================

	/** Reset camera to default view with time scale */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Camera")
	void ResetCameraView(double TimeScale);

	/** Stop any active camera sequence */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Camera")
	void StopActiveCameraSequence();

	/** Play a camera sequence with settings */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Camera")
	void PlayCameraSequence(ULevelSequence* Sequence, FMovieSceneSequencePlaybackSettings Settings);

	// ============================================================
	// EXECUTION/COMBAT FUNCTIONS
	// ============================================================

	/** Play backstab execution montage */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void PlayBackstabMontage(UAnimMontage* Montage, FGameplayTag ExecutionTag);

	/** Play execute montage */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void PlayExecuteMontage(UAnimMontage* Montage, FGameplayTag ExecutionTag);

	/** Enable/disable chaos destruction field */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void TriggerChaosField(bool bEnable);

	/** Called when target lock state changes */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnTargetLocked(bool bTargetLocked, bool bRotateTowards);

	// ============================================================
	// INTERACTION FUNCTIONS
	// ============================================================

	/** Called when an interactable is traced */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteractableTraced(AB_Interactable* Interactable);

	/** Called when resting at a campfire/resting point */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnRest(AActor* TargetCampfire);

	/** Called when looting an item */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnLootItem(AActor* Item);

	/** Called when discovering a new resting point */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DiscoverRestingPoint(UAnimMontage* InteractionMontage, AActor* Point);

	/** Called when dialog starts with an NPC */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnDialogStarted(UAC_AI_InteractionManager* DialogComponent);

	/** Called when NPC is traced for interaction */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnNpcTraced(AActor* NPC);

	// ============================================================
	// CHARACTER ACCESS
	// ============================================================

	/** Get the soulslike character actor */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	AActor* GetSoulslikeCharacter();

	/** Toggle crouch state (replicated) */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	void ToggleCrouchReplicated();

	// ============================================================
	// EQUIPMENT VISUAL FUNCTIONS
	// ============================================================

	/** Reset greaves to default mesh */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipment")
	void ResetGreaves();

	/** Reset gloves to default mesh */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipment")
	void ResetGloves();

	/** Reset armor to default mesh */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipment")
	void ResetArmor();

	/** Reset headpiece to default mesh */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipment")
	void ResetHeadpiece();

	/** Change greaves mesh */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipment")
	void ChangeGreaves(USkeletalMesh* NewMesh);

	/** Change gloves mesh */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipment")
	void ChangeGloves(USkeletalMesh* NewMesh);

	/** Change armor mesh */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipment")
	void ChangeArmor(USkeletalMesh* NewMesh);

	/** Change headpiece mesh */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipment")
	void ChangeHeadpiece(USkeletalMesh* NewMesh);
};
