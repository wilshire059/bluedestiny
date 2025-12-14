#include "AC_RadarElement.h"

UAC_RadarElement::UAC_RadarElement()
{
	PrimaryComponentTick.bCanEverTick = false;
	ElementType = E_RadarElementType::Neutral;
	Color = FLinearColor::White;
	bShowOnRadar = true;
	IconScale = 1.0f;
}

void UAC_RadarElement::BeginPlay()
{
	Super::BeginPlay();
	// Register with radar manager
}

void UAC_RadarElement::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Unregister from radar manager
	Super::EndPlay(EndPlayReason);
}

void UAC_RadarElement::SetVisible(bool bVisible)
{
	bShowOnRadar = bVisible;
}

bool UAC_RadarElement::IsVisible() const
{
	return bShowOnRadar;
}
