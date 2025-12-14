#pragma once

#include "CoreMinimal.h"
#include "B_Action.h"
#include "B_Action_ScrollWheel_Tools.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Action_ScrollWheel_Tools : public UB_Action
{
	GENERATED_BODY()
public:
	UB_Action_ScrollWheel_Tools();
	virtual void ExecuteAction_Implementation() override;
};
