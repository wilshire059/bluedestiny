#include "W_Debug_HUD.h"
#include "Kismet/GameplayStatics.h"

void UW_Debug_HUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateDebugInfo();
}

void UW_Debug_HUD::UpdateDebugInfo()
{
	if (FPSText)
	{
		float FPS = 1.0f / FApp::GetDeltaTime();
		FPSText->SetText(FText::Format(NSLOCTEXT("Debug", "FPS", "FPS: {0}"), FMath::RoundToInt(FPS)));
	}

	if (LocationText)
	{
		if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0))
		{
			FVector Location = PlayerPawn->GetActorLocation();
			LocationText->SetText(FText::Format(NSLOCTEXT("Debug", "Location", "Loc: {0}, {1}, {2}"),
				FMath::RoundToInt(Location.X),
				FMath::RoundToInt(Location.Y),
				FMath::RoundToInt(Location.Z)));
		}
	}
}

void UW_Debug_HUD::ToggleDebugHUD()
{
	SetVisibility(GetVisibility() == ESlateVisibility::Visible ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
}
