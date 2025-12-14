#include "ANS_Trail.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

FString UANS_Trail::GetNotifyName_Implementation() const
{
	return TEXT("Trail");
}

void UANS_Trail::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp || !TrailEffect.IsValid())
	{
		return;
	}

	if (UNiagaraSystem* Effect = TrailEffect.LoadSynchronous())
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			Effect,
			MeshComp,
			AttachSocket,
			LocationOffset,
			RotationOffset,
			EAttachLocation::SnapToTarget,
			true
		);
	}
}

void UANS_Trail::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// Trail effect auto-destroys
}
