#include "B_Soulslike_NPC.h"

AB_Soulslike_NPC::AB_Soulslike_NPC()
{
	bCanInteract = true;
}

void AB_Soulslike_NPC::BeginPlay()
{
	Super::BeginPlay();
}

void AB_Soulslike_NPC::OnInteract_Implementation(AActor* InteractingActor)
{
	// Start dialog when interacted with
	StartDialog();
}

void AB_Soulslike_NPC::OnTraced_Implementation(AActor* TracedBy)
{
	// Implemented in Blueprint
}

void AB_Soulslike_NPC::TryGetItemInfo_Implementation(FSLFItemInfo& ItemInfo)
{
	// NPCs don't have item info
}

void AB_Soulslike_NPC::StartDialog()
{
	// Implemented in Blueprint
}

void AB_Soulslike_NPC::EndDialog()
{
	// Implemented in Blueprint
}

FText AB_Soulslike_NPC::GetNPCName() const
{
	return NPCName;
}
