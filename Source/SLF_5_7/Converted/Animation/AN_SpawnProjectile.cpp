#include "AN_SpawnProjectile.h"
#include "GameFramework/Pawn.h"

FString UAN_SpawnProjectile::GetNotifyName_Implementation() const
{
	return TEXT("Spawn Projectile");
}

void UAN_SpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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

	// Get spawn transform
	FTransform SpawnTransform = SpawnSocket.IsNone() ? Owner->GetActorTransform() : MeshComp->GetSocketTransform(SpawnSocket);
	SpawnTransform.AddToTranslation(SpawnOffset);

	// Apply rotation
	if (bUseControlRotation)
	{
		APawn* Pawn = Cast<APawn>(Owner);
		if (Pawn && Pawn->GetController())
		{
			SpawnTransform.SetRotation(Pawn->GetControlRotation().Quaternion());
		}
	}
	SpawnTransform.SetRotation(SpawnTransform.GetRotation() * SpawnRotationOffset.Quaternion());

	// Projectile spawning - would be expanded in derived class
}
