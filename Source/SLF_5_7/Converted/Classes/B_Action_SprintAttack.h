#pragma once

#include "CoreMinimal.h"
#include "B_Action.h"
#include "B_Action_SprintAttack.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Action_SprintAttack : public UB_Action
{
	GENERATED_BODY()
public:
	UB_Action_SprintAttack();
	virtual void ExecuteAction_Implementation() override;
};
