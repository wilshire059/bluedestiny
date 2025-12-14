#include "ANS_FistTrace.h"

FString UANS_FistTrace::GetNotifyName_Implementation() const
{
	return TEXT("Fist Trace");
}

void UANS_FistTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	// Enable fist collision through collision manager
}

void UANS_FistTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// Disable fist collision
}
