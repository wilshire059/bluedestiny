#include "AIC_SoulslikeFramework.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

AAIC_SoulslikeFramework::AAIC_SoulslikeFramework()
{
	// Create perception component
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception")));
}

void AAIC_SoulslikeFramework::InitializeBehavior_Implementation(UBehaviorTree* BehaviorTree)
{
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AAIC_SoulslikeFramework::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (bAutoRunBehaviorTree && DefaultBehaviorTree)
	{
		RunBehaviorTree(DefaultBehaviorTree);
	}
}

void AAIC_SoulslikeFramework::OnUnPossess()
{
	Super::OnUnPossess();

	// Stop behavior tree when unpossessing
	UBrainComponent* BrainComp = GetBrainComponent();
	if (BrainComp)
	{
		BrainComp->StopLogic(TEXT("Unpossessed"));
	}
}
