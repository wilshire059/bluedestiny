#include "ANS_AI_RotateTowardsTarget.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

FString UANS_AI_RotateTowardsTarget::GetNotifyName_Implementation() const
{
	return TEXT("AI Rotate Towards Target");
}

void UANS_AI_RotateTowardsTarget::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UANS_AI_RotateTowardsTarget::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!MeshComp)
	{
		return;
	}

	APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (!Pawn)
	{
		return;
	}

	AAIController* AIC = Cast<AAIController>(Pawn->GetController());
	if (!AIC)
	{
		return;
	}

	AActor* FocusActor = AIC->GetFocusActor();
	if (FocusActor)
	{
		FRotator CurrentRotation = Pawn->GetActorRotation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Pawn->GetActorLocation(), FocusActor->GetActorLocation());

		if (bOnlyYaw)
		{
			TargetRotation.Pitch = CurrentRotation.Pitch;
			TargetRotation.Roll = CurrentRotation.Roll;
		}

		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, FrameDeltaTime, RotationSpeed);
		Pawn->SetActorRotation(NewRotation);
	}
}

void UANS_AI_RotateTowardsTarget::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
