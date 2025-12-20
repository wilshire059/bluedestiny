#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Blueprint/UMGSequencePlayMode.h"
#include "BPI_MainMenu.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_MainMenu : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for Main Menu Button interactions.
 * Matches Blueprint BPI_MainMenu exactly.
 */
class SLF_5_7_API IBPI_MainMenu
{
	GENERATED_BODY()

public:
	/** Called when menu button is pressed */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MainMenu")
	void OnMenuButtonPressed();

	/** Set button selected state */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MainMenu")
	void SetMenuButtonSelected(bool bSelected);

	/** Play button initialization animation */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MainMenu")
	void PlayButtonInitAnimation(double StartTime, int32 Loops, EUMGSequencePlayMode::Type Mode, double PlayRate);
};
