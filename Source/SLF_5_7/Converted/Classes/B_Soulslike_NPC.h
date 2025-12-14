#pragma once

#include "CoreMinimal.h"
#include "B_BaseCharacter.h"
#include "Interfaces/BPI_NPC.h"
#include "Interfaces/BPI_Interactable.h"
#include "B_Soulslike_NPC.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_Soulslike_NPC : public AB_BaseCharacter, public IBPI_NPC, public IBPI_Interactable
{
	GENERATED_BODY()

public:
	AB_Soulslike_NPC();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	FText NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	bool bCanInteract;

	// BPI_Interactable Interface
	virtual void OnInteract_Implementation(AActor* InteractingActor) override;
	virtual void OnTraced_Implementation(AActor* TracedBy) override;
	virtual void TryGetItemInfo_Implementation(FSLFItemInfo& ItemInfo) override;

	// Custom NPC functions
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void StartDialog();

	UFUNCTION(BlueprintCallable, Category = "NPC")
	void EndDialog();

	UFUNCTION(BlueprintCallable, Category = "NPC")
	FText GetNPCName() const;
};
