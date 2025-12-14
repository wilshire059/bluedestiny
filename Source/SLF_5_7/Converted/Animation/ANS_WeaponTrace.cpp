#include "ANS_WeaponTrace.h"
#include "GameFramework/Pawn.h"

FString UANS_WeaponTrace::GetNotifyName_Implementation() const
{
	return TEXT("Trace");
}

void UANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp)
	{
		return;
	}

	APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (Pawn)
	{
		// Get equipment manager and enable weapon trace through collision manager
	}
}

void UANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (Pawn)
	{
		// Disable weapon trace through collision manager
	}
}
