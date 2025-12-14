#pragma once

#include "CoreMinimal.h"
#include "B_Action.h"
#include "B_Action_Execute.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Action_Execute : public UB_Action
{
	GENERATED_BODY()

public:
	UB_Action_Execute();
	virtual void ExecuteAction_Implementation() override;
};
