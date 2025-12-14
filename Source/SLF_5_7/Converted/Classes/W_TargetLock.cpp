#include "W_TargetLock.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void UW_TargetLock::SetLockedTarget(AActor* Target)
{
	LockedTarget = Target;

	if (Target)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UW_TargetLock::ClearLockedTarget()
{
	LockedTarget = nullptr;
	SetVisibility(ESlateVisibility::Collapsed);
}

void UW_TargetLock::UpdatePosition()
{
	if (!LockedTarget.IsValid())
	{
		return;
	}

	// Position update would project 3D location to screen space
	// Implemented in Blueprint with more control over positioning
}

void UW_TargetLock::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (LockedTarget.IsValid())
	{
		UpdatePosition();
	}
	else if (GetVisibility() == ESlateVisibility::Visible)
	{
		ClearLockedTarget();
	}
}
