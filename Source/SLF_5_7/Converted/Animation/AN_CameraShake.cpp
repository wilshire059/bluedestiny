#include "AN_CameraShake.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

FString UAN_CameraShake::GetNotifyName_Implementation() const
{
	return TEXT("Camera Shake");
}

void UAN_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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

	APawn* Pawn = Cast<APawn>(Owner);
	if (Pawn)
	{
		APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
		if (PC)
		{
			PC->ClientStartCameraShake(CameraShakeClass, Scale);
		}
	}
}
