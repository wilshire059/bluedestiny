#include "B_Soulslike_Enemy.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Classes/B_PatrolPath.h"

AB_Soulslike_Enemy::AB_Soulslike_Enemy()
{
    LootDropManager = CreateDefaultSubobject<UAC_LootDropManager>(TEXT("LootDropManager"));
}

void AB_Soulslike_Enemy::BeginPlay()
{
	Super::BeginPlay();
    
    // Bind delegates here
}

// BPI_Enemy Implementation
void AB_Soulslike_Enemy::UpdateEnemyHealth_Implementation(double CurrentValue, double MaxValue, double Change) {}
void AB_Soulslike_Enemy::GetExecutionMoveToTransform_Implementation(FVector& MoveToLocation, FRotator& Rotation) {}
void AB_Soulslike_Enemy::StopRotateTowardsTarget_Implementation() {}
void AB_Soulslike_Enemy::RotateTowardsTarget_Implementation(double Duration) {}
void AB_Soulslike_Enemy::PickAndSpawnLoot_Implementation() {}
AB_PatrolPath* AB_Soulslike_Enemy::GetPatrolPath_Implementation() { return nullptr; }
void AB_Soulslike_Enemy::DisplayDeathVfx_Implementation(FVector AttractorPosition) {}
void AB_Soulslike_Enemy::ToggleHealthbarVisual_Implementation(bool bVisible) {}

// BPI_Executable Implementation
void AB_Soulslike_Enemy::OnExecutionStarted_Implementation() {}
void AB_Soulslike_Enemy::OnExecuted_Implementation(FGameplayTag ExecutionTag) {}
void AB_Soulslike_Enemy::OnBackstabbed_Implementation(FGameplayTag ExecutionTag) {}

// Custom Handlers
void AB_Soulslike_Enemy::OnTargeted(bool bTargeted) {}
void AB_Soulslike_Enemy::OnParried(AActor* Attacker) {}
void AB_Soulslike_Enemy::OnFinisherExecuted(AActor* Attacker) {}
