#include "AN_FootstepTrace.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

FString UAN_FootstepTrace::GetNotifyName_Implementation() const
{
	return TEXT("Footstep");
}

void UAN_FootstepTrace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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

	// Get socket transform
	FTransform SocketTransform = MeshComp->GetSocketTransform(FootSocket);
	FVector Start = SocketTransform.GetLocation();
	FVector End = Start - (Owner->GetActorUpVector() * TraceLength);

	// Line trace
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	bool bHit = UKismetSystemLibrary::LineTraceSingle(
		Owner,
		Start,
		End,
		UEngineTypes::ConvertToTraceType(TraceType),
		false,
		ActorsToIgnore,
		bDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResult,
		true
	);

	if (bHit && HitResult.PhysMaterial.IsValid())
	{
		EPhysicalSurface SurfaceType = HitResult.PhysMaterial->SurfaceType;

		// Play sound if available
		if (TSoftObjectPtr<USoundBase>* SoundPtr = Sounds.Find(SurfaceType))
		{
			if (USoundBase* Sound = SoundPtr->LoadSynchronous())
			{
				UGameplayStatics::PlaySoundAtLocation(Owner, Sound, HitResult.ImpactPoint);
			}
		}

		// Spawn effect if available
		if (TSoftObjectPtr<UNiagaraSystem>* EffectPtr = Effects.Find(SurfaceType))
		{
			if (UNiagaraSystem* Effect = EffectPtr->LoadSynchronous())
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(Owner, Effect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
			}
		}
	}
}
