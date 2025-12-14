#include "W_Utility_Asset.h"

void UW_Utility_Asset::NativeConstruct()
{
	Super::NativeConstruct();

	if (AssetButton)
	{
		AssetButton->OnClicked.AddDynamic(this, &UW_Utility_Asset::HandleAssetClicked);
	}
}

void UW_Utility_Asset::SetupAsset(UObject* Asset, FText AssetName, UTexture2D* Icon)
{
	TrackedAsset = Asset;

	if (AssetNameText)
	{
		AssetNameText->SetText(AssetName);
	}

	if (AssetIcon && Icon)
	{
		AssetIcon->SetBrushFromTexture(Icon);
	}
}

void UW_Utility_Asset::HandleAssetClicked()
{
	if (TrackedAsset.IsValid())
	{
		OnUtilityAssetSelected.Broadcast(TrackedAsset.Get());
	}
}
