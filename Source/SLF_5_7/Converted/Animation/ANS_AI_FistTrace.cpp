#include "ANS_AI_FistTrace.h"

FString UANS_AI_FistTrace::GetNotifyName_Implementation() const
{
	return TEXT("AI Fist Trace");
}

void UANS_AI_FistTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	// Enable collision on fist - call collision manager
}

void UANS_AI_FistTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	// Trace logic is handled by collision manager
}

void UANS_AI_FistTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// Disable collision on fist
}
