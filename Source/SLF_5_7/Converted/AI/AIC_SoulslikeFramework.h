#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BPI_AIC.h"
#include "AIC_SoulslikeFramework.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class SLF_5_7_API AAIC_SoulslikeFramework : public AAIController, public IBPI_AIC
{
	GENERATED_BODY()

public:
	AAIC_SoulslikeFramework();

	// BPI_AIC Interface
	virtual void InitializeBehavior_Implementation(UBehaviorTree* BehaviorTree) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTree> DefaultBehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool bAutoRunBehaviorTree = false;
};
