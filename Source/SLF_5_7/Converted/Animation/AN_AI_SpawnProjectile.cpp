#include "AN_AI_SpawnProjectile.h"

FString UAN_AI_SpawnProjectile::GetNotifyName_Implementation() const
{
	return TEXT("AI Spawn Projectile");
}

void UAN_AI_SpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp || !ProjectileClass)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	// Spawn location from socket
	FTransform SpawnTransform = MeshComp->GetSocketTransform(SpawnSocket);
	SpawnTransform.AddToTranslation(SpawnOffset);

	// Projectile spawning logic - would be expanded in Blueprint
}
