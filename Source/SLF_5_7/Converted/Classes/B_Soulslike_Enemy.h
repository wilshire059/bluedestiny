#pragma once

#include "CoreMinimal.h"
#include "Classes/B_BaseCharacter.h"
#include "Interfaces/BPI_Enemy.h"
#include "Interfaces/BPI_Executable.h"
#include "Components/AC_LootDropManager.h"
#include "Perception/AIPerceptionComponent.h"
#include "B_Soulslike_Enemy.generated.h"

class AB_PatrolPath;

UCLASS()
class SLF_5_7_API AB_Soulslike_Enemy : public AB_BaseCharacter, public IBPI_Enemy, public IBPI_Executable
{
	GENERATED_BODY()

public:
	AB_Soulslike_Enemy();

protected:
	virtual void BeginPlay() override;

public:	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAC_LootDropManager* LootDropManager;

    // Interface BPI_Enemy
    virtual void UpdateEnemyHealth_Implementation(double CurrentValue, double MaxValue, double Change) override;
    virtual void GetExecutionMoveToTransform_Implementation(FVector& MoveToLocation, FRotator& Rotation) override;
    virtual void StopRotateTowardsTarget_Implementation() override;
    virtual void RotateTowardsTarget_Implementation(double Duration) override;
    virtual void PickAndSpawnLoot_Implementation() override;
    virtual AB_PatrolPath* GetPatrolPath_Implementation() override;
    virtual void DisplayDeathVfx_Implementation(FVector AttractorPosition) override;
    virtual void ToggleHealthbarVisual_Implementation(bool bVisible) override;

    // Interface BPI_Executable
    virtual void OnExecutionStarted_Implementation() override;
    virtual void OnExecuted_Implementation(FGameplayTag ExecutionTag) override;
    virtual void OnBackstabbed_Implementation(FGameplayTag ExecutionTag) override;

    // Custom Event Handlers (Not Overrides)
    UFUNCTION()
    void OnTargeted(bool bTargeted);
    
    UFUNCTION()
    void OnParried(AActor* Attacker); // Check signature against AC_CombatManager delegate

    UFUNCTION()
    void OnFinisherExecuted(AActor* Attacker); // Logic placeholder
};
