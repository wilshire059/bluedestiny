#include "W_LoadingScreen.h"

void UW_LoadingScreen::NativeConstruct()
{
	Super::NativeConstruct();
	SetupLoadingScreen();
}

void UW_LoadingScreen::SetupLoadingScreen()
{
	if (LoadingScreenAsset)
	{
		TSoftObjectPtr<UTexture2D> Texture;
		FLoadingScreenTip Tip;
		LoadingScreenAsset->GetRandomLoadingScreenData(Texture, Tip);

		if (TipText)
		{
			TipText->SetText(Tip.TipDescription);
		}

		// Background image would be set asynchronously in Blueprint
	}
}
