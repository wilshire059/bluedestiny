#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/FStatInfo.h"
#include "Structs/FModularMeshData.h"
#include "Engine/Texture2D.h"
#include "PDA_BaseCharacterInfo.generated.h"

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_BaseCharacterInfo : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
    FText CharacterClassName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
    TSoftObjectPtr<UTexture2D> BaseClassTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
    FStatInfo BaseStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
    TSoftObjectPtr<USkeletalMesh> DefaultMeshAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
    FModularMeshData ModularMeshData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
    TSoftObjectPtr<UTexture2D> SaveSlotTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
    TSoftObjectPtr<UTexture2D> QuitCardTexture;
};
