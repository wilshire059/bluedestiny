// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDA_DayNight.h"

UPDA_DayNight::UPDA_DayNight()
{
	// Defaults
}

void UPDA_DayNight::GetInfoForTimeTag(FGameplayTag TimeTag, FDayNightInfo& OutEntry, bool& bSuccess)
{
	bSuccess = false;

	for (const FDayNightInfo& Entry : Entries)
	{
		if (Entry.Tag == TimeTag)
		{
			OutEntry = Entry;
			bSuccess = true;
			return;
		}
	}
}
