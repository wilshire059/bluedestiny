#include "B_Chaos_ForceField.h"

AB_Chaos_ForceField::AB_Chaos_ForceField()
{
	PrimaryActorTick.bCanEverTick = true;

	ForceFieldCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ForceFieldCollision"));
	ForceFieldCollision->SetSphereRadius(500.0f);
	RootComponent = ForceFieldCollision;

	Radius = 500.0f;
	DamagePerSecond = 10.0f;
}

void AB_Chaos_ForceField::BeginPlay()
{
	Super::BeginPlay();
}
