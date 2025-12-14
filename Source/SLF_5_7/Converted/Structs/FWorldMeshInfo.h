#pragma once

#include "CoreMinimal.h"
#include "Enums/E_WorldMeshStyle.h"
#include "NiagaraSystem.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "FWorldMeshInfo.generated.h"

USTRUCT(BlueprintType)
struct SLF_5_7_API FWorldMeshInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	E_WorldMeshStyle WorldDisplayStyle = E_WorldMeshStyle::ShowMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	TSoftObjectPtr<UNiagaraSystem> WorldNiagaraSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	TSoftObjectPtr<UStaticMesh> WorldStaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	TSoftObjectPtr<USkeletalMesh> WorldSkeletalMesh;
};
