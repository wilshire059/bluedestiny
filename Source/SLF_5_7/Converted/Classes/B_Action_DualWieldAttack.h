#pragma once

#include "CoreMinimal.h"
#include "B_Action.h"
#include "B_Action_DualWieldAttack.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API UB_Action_DualWieldAttack : public UB_Action
{
	GENERATED_BODY()

public:
	UB_Action_DualWieldAttack();
	virtual void ExecuteAction_Implementation() override;
};
