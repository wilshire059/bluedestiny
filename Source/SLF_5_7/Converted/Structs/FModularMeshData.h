#pragma once

#include "CoreMinimal.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/Skeleton.h"
#include "FModularMeshData.generated.h"

USTRUCT(BlueprintType)
struct FModularMeshData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Details")
	TSoftObjectPtr<USkeleton> Skeleton;

    // Add other fields if inferred later, for now based on JSON
};
