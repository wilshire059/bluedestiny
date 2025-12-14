#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_MainMenu.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBPI_MainMenu : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for Main Menu Button interactions.
 */
class SLF_5_7_API IBPI_MainMenu
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MainMenu")
	void SetMenuButtonSelected(bool bSelected);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MainMenu")
	void PlayButtonInitAnimation();
};
