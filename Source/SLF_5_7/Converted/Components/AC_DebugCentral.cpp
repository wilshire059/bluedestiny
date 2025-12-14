#include "AC_DebugCentral.h"

UAC_DebugCentral::UAC_DebugCentral()
{
	PrimaryComponentTick.bCanEverTick = true;
	bDebugEnabled = false;
	bShowStats = false;
	bShowAI = false;
	bShowCombat = false;
}

void UAC_DebugCentral::BeginPlay()
{
	Super::BeginPlay();
}

void UAC_DebugCentral::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_DebugCentral::ToggleDebug()
{
	bDebugEnabled = !bDebugEnabled;
}

void UAC_DebugCentral::LogDebugMessage(const FString& Message, FLinearColor Color)
{
	if (bDebugEnabled)
	{
		UE_LOG(LogTemp, Log, TEXT("[Debug] %s"), *Message);
	}
}
