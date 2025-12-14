#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "FCreditsExtra.generated.h"

/**
 * Struct for Extra Credit Data (Images, Special thanks etc).
 */
USTRUCT(BlueprintType)
struct SLF_5_7_API FCreditsExtra
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Credits")
	bool BeforeEntry = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Credits")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Credits")
	TSoftObjectPtr<UTexture2D> Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Credits")
	FVector2D ImageSizeOverride = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Credits")
	double Score = 0.0;
};
