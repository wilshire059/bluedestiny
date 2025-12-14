#include "AC_RadarManager.h"
#include "AC_RadarElement.h"

UAC_RadarManager::UAC_RadarManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	RadarRange = 2000.0f;
	RadarScale = 1.0f;
}

void UAC_RadarManager::BeginPlay()
{
	Super::BeginPlay();
}

void UAC_RadarManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateRadar();
}

void UAC_RadarManager::Initialize(UUserWidget* InRadarWidget, APawn* InPawn)
{
	RadarWidget = InRadarWidget;
	TrackedPawn = InPawn;
}

void UAC_RadarManager::RegisterElement(UAC_RadarElement* Element)
{
	if (Element && !RegisteredElements.Contains(Element))
	{
		RegisteredElements.Add(Element);
	}
}

void UAC_RadarManager::UnregisterElement(UAC_RadarElement* Element)
{
	RegisteredElements.Remove(Element);
}

void UAC_RadarManager::UpdateRadar()
{
	if (!TrackedPawn || !RadarWidget) return;

	FVector PawnLocation = TrackedPawn->GetActorLocation();

	for (UAC_RadarElement* Element : RegisteredElements)
	{
		if (!Element || !Element->IsVisible()) continue;

		AActor* ElementOwner = Element->GetOwner();
		if (!ElementOwner) continue;

		FVector ElementLocation = ElementOwner->GetActorLocation();
		float Distance = FVector::Dist(PawnLocation, ElementLocation);

		if (Distance <= RadarRange)
		{
			// Calculate relative position and update widget
			FVector RelativePos = ElementLocation - PawnLocation;
			// Widget update logic would go here
		}
	}
}
