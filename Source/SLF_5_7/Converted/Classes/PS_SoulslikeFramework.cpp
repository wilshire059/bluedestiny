#include "PS_SoulslikeFramework.h"

APS_SoulslikeFramework::APS_SoulslikeFramework()
{
}

void APS_SoulslikeFramework::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	// Copy custom properties to new player state
	if (APS_SoulslikeFramework* SFPlayerState = Cast<APS_SoulslikeFramework>(PlayerState))
	{
		// Copy any custom properties here
	}
}

void APS_SoulslikeFramework::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);

	// Override with properties from old player state
	if (APS_SoulslikeFramework* SFPlayerState = Cast<APS_SoulslikeFramework>(PlayerState))
	{
		// Override any custom properties here
	}
}
