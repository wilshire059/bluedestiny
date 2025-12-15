#include "BTT_SetKey.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_SetKey::UBTT_SetKey()
{
	NodeName = TEXT("Set Key");
}

EBTNodeResult::Type UBTT_SetKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	switch (KeyType)
	{
	case EBlackboardKeyType::Bool:
		BlackboardComp->SetValueAsBool(Key.SelectedKeyName, BoolValue);
		break;
	case EBlackboardKeyType::Int:
		BlackboardComp->SetValueAsInt(Key.SelectedKeyName, IntValue);
		break;
	case EBlackboardKeyType::Float:
		BlackboardComp->SetValueAsFloat(Key.SelectedKeyName, FloatValue);
		break;
	case EBlackboardKeyType::Vector:
		BlackboardComp->SetValueAsVector(Key.SelectedKeyName, VectorValue);
		break;
	case EBlackboardKeyType::Object:
		// Object requires external reference, clear it
		BlackboardComp->ClearValue(Key.SelectedKeyName);
		break;
	}

	return EBTNodeResult::Succeeded;
}
