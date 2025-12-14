#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_Demo_TimeSlider.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_Demo_TimeSlider : public AActor
{
	GENERATED_BODY()

public:
	AB_Demo_TimeSlider();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	float TimeOfDay;
};
