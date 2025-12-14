#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_SequenceActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_SequenceActor : public AActor
{
	GENERATED_BODY()

public:
	AB_SequenceActor();

	UFUNCTION(BlueprintCallable, Category = "Sequence")
	void PlaySequence();

	UFUNCTION(BlueprintCallable, Category = "Sequence")
	void StopSequence();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence")
	bool bAutoPlay;
};
