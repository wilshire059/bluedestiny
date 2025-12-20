#pragma once

#include "CoreMinimal.h"
#include "Enums/E_StrafeMethod.h"
#include "FStrafeMethodInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FStrafeMethodInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strafe")
	E_StrafeMethod StrafeMethod = E_StrafeMethod::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strafe")
	float Score = 0.0f;
};
