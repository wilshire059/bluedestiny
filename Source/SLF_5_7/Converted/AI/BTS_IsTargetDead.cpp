#include "BTS_IsTargetDead.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BPI_Damageable.h"

UBTS_IsTargetDead::UBTS_IsTargetDead()
{
	NodeName = TEXT("Is Target Dead");

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_IsTargetDead, TargetKey), AActor::StaticClass());
	IsDeadKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_IsTargetDead, IsDeadKey));
}

void UBTS_IsTargetDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));

	bool bIsDead = true; // Default to dead if no target

	if (TargetActor)
	{
		// Check if target implements damageable interface
		if (TargetActor->GetClass()->ImplementsInterface(UBPI_Damageable::StaticClass()))
		{
			bIsDead = IBPI_Damageable::Execute_IsDead(TargetActor);
		}
		else
		{
			bIsDead = false; // Target exists but doesn't implement interface
		}
	}

	BlackboardComp->SetValueAsBool(IsDeadKey.SelectedKeyName, bIsDead);
}
