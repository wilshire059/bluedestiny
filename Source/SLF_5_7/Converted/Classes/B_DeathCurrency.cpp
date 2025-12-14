#include "B_DeathCurrency.h"

AB_DeathCurrency::AB_DeathCurrency()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollision"));
	PickupCollision->SetSphereRadius(100.0f);
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = PickupCollision;

	CurrencyAmount = 0;
}

void AB_DeathCurrency::BeginPlay()
{
	Super::BeginPlay();

	if (PickupCollision)
	{
		PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &AB_DeathCurrency::OnOverlap);
	}
}

void AB_DeathCurrency::Pickup(AActor* PickupActor)
{
	// Logic implemented in Blueprint - give currency to player
	Destroy();
}

void AB_DeathCurrency::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Player")))
	{
		Pickup(OtherActor);
	}
}
