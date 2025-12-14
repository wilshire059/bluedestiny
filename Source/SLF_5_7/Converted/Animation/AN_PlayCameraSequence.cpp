#include "AN_PlayCameraSequence.h"

FString UAN_PlayCameraSequence::GetNotifyName_Implementation() const
{
	return TEXT("Play Camera Sequence");
}

void UAN_PlayCameraSequence::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	// Camera sequence playback - implemented in Blueprint or through Sequencer API
}
