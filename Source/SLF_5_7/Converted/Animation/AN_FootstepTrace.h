#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Engine/EngineTypes.h"
#include "Sound/SoundBase.h"
#include "NiagaraSystem.h"
#include "AN_FootstepTrace.generated.h"

UCLASS()
class SLF_5_7_API UAN_FootstepTrace : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	FName FootSocket = FName("foot_l");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	float TraceLength = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	TEnumAsByte<ECollisionChannel> TraceType = ECC_Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	bool bDebugTrace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	TMap<TEnumAsByte<EPhysicalSurface>, TSoftObjectPtr<USoundBase>> Sounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	TMap<TEnumAsByte<EPhysicalSurface>, TSoftObjectPtr<UNiagaraSystem>> Effects;

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
