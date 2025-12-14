#include "AN_LaunchField.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

FString UAN_LaunchField::GetNotifyName_Implementation() const
{
	return TEXT("Launch Field");
}

void UAN_LaunchField::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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

	// Calculate origin
	FVector Origin = OriginSocket.IsNone() ? Owner->GetActorLocation() : MeshComp->GetSocketLocation(OriginSocket);

	// Sphere overlap for characters
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	// Launch logic - sphere overlap and apply launch velocity to characters
}
