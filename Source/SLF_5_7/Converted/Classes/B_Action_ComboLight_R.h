#pragma once

#include "CoreMinimal.h"
#include "B_Action.h"
#include "B_Action_ComboLight_R.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Action_ComboLight_R : public UB_Action
{
	GENERATED_BODY()

public:
	UB_Action_ComboLight_R();

	virtual void ExecuteAction_Implementation() override;
};
