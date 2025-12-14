#include "ANS_AI_WeaponTrace.h"

FString UANS_AI_WeaponTrace::GetNotifyName_Implementation() const
{
	return TEXT("AI Weapon Trace");
}

void UANS_AI_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	// Enable weapon collision through collision manager
}

void UANS_AI_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// Disable weapon collision
}
