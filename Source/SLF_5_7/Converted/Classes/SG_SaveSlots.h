#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SG_SaveSlots.generated.h"

/**
 * SaveGame class for storing the list of save slot names
 */
UCLASS()
class SLF_5_7_API USG_SaveSlots : public USaveGame
{
	GENERATED_BODY()

public:
	USG_SaveSlots();

	// Add a new save slot
	UFUNCTION(BlueprintCallable, Category = "Save Slots")
	void AddSlot(const FString& SlotName);

	// Remove a save slot
	UFUNCTION(BlueprintCallable, Category = "Save Slots")
	void RemoveSlot(const FString& SlotName);

	// Check if slot exists
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save Slots")
	bool HasSlot(const FString& SlotName) const;

	// Get all slots
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save Slots")
	const TArray<FString>& GetSlots() const { return Slots; }

protected:
	// Array of save slot names
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Save Slots")
	TArray<FString> Slots;
};
