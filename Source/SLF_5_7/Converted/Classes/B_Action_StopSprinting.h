#pragma once

#include "CoreMinimal.h"
#include "B_Action.h"
#include "B_Action_StopSprinting.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Action_StopSprinting : public UB_Action
{
	GENERATED_BODY()
public:
	UB_Action_StopSprinting();
	virtual void ExecuteAction_Implementation() override;
};
