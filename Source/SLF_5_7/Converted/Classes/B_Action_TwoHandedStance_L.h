#pragma once

#include "CoreMinimal.h"
#include "B_Action.h"
#include "B_Action_TwoHandedStance_L.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Action_TwoHandedStance_L : public UB_Action
{
	GENERATED_BODY()
public:
	UB_Action_TwoHandedStance_L();
	virtual void ExecuteAction_Implementation() override;
};
