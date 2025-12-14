#include "AN_AoeDamage.h"

FString UAN_AoeDamage::GetNotifyName_Implementation() const
{
	return TEXT("AoE Damage");
}

void UAN_AoeDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	// Calculate origin position
	FVector Origin = OriginSocket.IsNone() ? Owner->GetActorLocation() : MeshComp->GetSocketLocation(OriginSocket);
	Origin += OriginOffset;

	// AoE damage logic - sphere overlap and damage application
}
