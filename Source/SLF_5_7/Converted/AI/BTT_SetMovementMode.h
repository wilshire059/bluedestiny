#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "E_MovementType.h"
#include "BTT_SetMovementMode.generated.h"

UCLASS()
class SLF_5_7_API UBTT_SetMovementMode : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTT_SetMovementMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	E_MovementType MovementType = E_MovementType::Run;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
