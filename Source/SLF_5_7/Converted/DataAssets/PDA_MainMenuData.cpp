// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDA_MainMenuData.h"

UPDA_MainMenuData::UPDA_MainMenuData()
{
	AdditionalWaitMin = 0.0;
	AdditionalWaitMax = 0.0;
	bRemoveOnFinish = false;
	DefaultLevelToLoad = TSoftObjectPtr<UWorld>(FSoftObjectPath(TEXT("/Game/SoulslikeFramework/Maps/L_Demo_Showcase.L_Demo_Showcase")));
}
