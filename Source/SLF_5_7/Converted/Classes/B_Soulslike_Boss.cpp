#include "B_Soulslike_Boss.h"
#include "GameFramework/Character.h"

AB_Soulslike_Boss::AB_Soulslike_Boss()
{
	TriggerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerCollision"));
	TriggerCollision->SetupAttachment(RootComponent);
	TriggerCollision->SetSphereRadius(1000.0f);
	TriggerCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	bIsBossDefeated = false;
}

void AB_Soulslike_Boss::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerCollision)
	{
		TriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &AB_Soulslike_Boss::OnTriggerOverlap);
	}
}

void AB_Soulslike_Boss::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Boss encounter trigger logic - to be implemented in Blueprint
}
