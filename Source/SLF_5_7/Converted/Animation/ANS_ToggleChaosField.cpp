#include "ANS_ToggleChaosField.h"

FString UANS_ToggleChaosField::GetNotifyName_Implementation() const
{
	return TEXT("Chaos Field");
}

void UANS_ToggleChaosField::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp)
	{
		return;
	}

	// Activate chaos field effect
}

void UANS_ToggleChaosField::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	// Deactivate chaos field effect
}
