#include "AN_WorldCameraShake.h"
#include "Kismet/GameplayStatics.h"

FString UAN_WorldCameraShake::GetNotifyName_Implementation() const
{
	return TEXT("World Camera Shake");
}

void UAN_WorldCameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp || !CameraShakeClass)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	UGameplayStatics::PlayWorldCameraShake(
		Owner,
		CameraShakeClass,
		Owner->GetActorLocation(),
		InnerRadius,
		OuterRadius,
		Falloff,
		bOrientShakeTowardsEpicenter
	);
}
