#include "AN_AdjustStat.h"
#include "Interfaces/BPI_Generic_Character.h"

FString UAN_AdjustStat::GetNotifyName_Implementation() const
{
	return TEXT("AdjustStat");
}

void UAN_AdjustStat::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (Owner && Owner->Implements<UBPI_Generic_Character>())
	{
		// Stat adjustment logic would be implemented here
		// IBPI_Generic_Character::Execute_AdjustStat(Owner, StatTag, AdjustmentValue, bIsPercentage);
	}
}
