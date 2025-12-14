#include "B_SkyManager.h"

AB_SkyManager::AB_SkyManager()
{
	PrimaryActorTick.bCanEverTick = true;

	TimeOfDay = 12.0f;
	TimeSpeed = 1.0f;
	SunLight = nullptr;
	SkyLightActor = nullptr;
}

void AB_SkyManager::BeginPlay()
{
	Super::BeginPlay();
	UpdateSkyState();
}

void AB_SkyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeSpeed > 0.0f)
	{
		TimeOfDay += DeltaTime * TimeSpeed / 60.0f;
		if (TimeOfDay >= 24.0f)
		{
			TimeOfDay -= 24.0f;
		}
		UpdateSkyState();
	}
}

void AB_SkyManager::SetTimeOfDay(float NewTime)
{
	TimeOfDay = FMath::Fmod(NewTime, 24.0f);
	if (TimeOfDay < 0.0f)
	{
		TimeOfDay += 24.0f;
	}
	UpdateSkyState();
}

void AB_SkyManager::UpdateSkyState()
{
	// Sun rotation based on time of day
	if (SunLight)
	{
		float SunPitch = (TimeOfDay / 24.0f) * 360.0f - 90.0f;
		SunLight->SetActorRotation(FRotator(SunPitch, 0.0f, 0.0f));
	}
}
