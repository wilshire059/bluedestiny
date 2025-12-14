#include "AN_InterruptMontage.h"
#include "Animation/AnimInstance.h"

FString UAN_InterruptMontage::GetNotifyName_Implementation() const
{
	return TEXT("Interrupt Montage");
}

void UAN_InterruptMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (AnimInstance)
	{
		UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
		if (CurrentMontage)
		{
			AnimInstance->Montage_Stop(BlendOutTime, CurrentMontage);
		}
	}
}
