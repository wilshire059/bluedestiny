#include "W_Radar_TrackedElement.h"
#include "Components/CanvasPanelSlot.h"

void UW_Radar_TrackedElement::SetTrackedActor(AActor* Actor, UTexture2D* Icon)
{
	TrackedActor = Actor;

	if (ElementIcon && Icon)
	{
		ElementIcon->SetBrushFromTexture(Icon);
	}
}

void UW_Radar_TrackedElement::UpdatePosition(FVector2D RadarPosition)
{
	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot))
	{
		CanvasSlot->SetPosition(RadarPosition);
	}
}

bool UW_Radar_TrackedElement::IsActorValid() const
{
	return TrackedActor.IsValid();
}
