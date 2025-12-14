#include "ANS_AI_Trail.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

FString UANS_AI_Trail::GetNotifyName_Implementation() const
{
	return TEXT("AI Trail");
}

void UANS_AI_Trail::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
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
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			true
		);
	}
}

void UANS_AI_Trail::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// Trail deactivation is handled by Niagara auto-destroy
}
