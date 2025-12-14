// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDA_LoadingScreens.h"

UPDA_LoadingScreens::UPDA_LoadingScreens()
{
	// Defaults
}

void UPDA_LoadingScreens::GetRandomLoadingScreenData(TSoftObjectPtr<UTexture2D>& OutTexture, FLoadingScreenTip& OutTip)
{
	if (Textures.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, Textures.Num() - 1);
		OutTexture = Textures[Index];
	}

	if (Tips.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, Tips.Num() - 1);
		OutTip = Tips[Index];
	}
}
