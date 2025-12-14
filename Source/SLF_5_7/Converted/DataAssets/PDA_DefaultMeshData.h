// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/SkeletalMesh.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "PDA_DefaultMeshData.generated.h"

/**
 * Struct to hold default skeletal mesh parts.
 * Recreated based on Blueprint usage.
 */
USTRUCT(BlueprintType)
struct FSkeletalMeshData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> HeadMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> UpperBodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> ArmsMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> LowerBodyMesh;
};

/**
 * Data Asset for Default Mesh Data.
 */
UCLASS(BlueprintType)
class SLF_5_7_API UPDA_DefaultMeshData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_DefaultMeshData();

	/** The default mesh parts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	FSkeletalMeshData MeshData;

	/** The physics asset to use */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")
	UPhysicsAsset* FinalPhysicsAsset;

	/** Debug flag */
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DEBUG_DEFAULT_CHECK = true;
};
