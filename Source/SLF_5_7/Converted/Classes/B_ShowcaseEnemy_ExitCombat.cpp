#include "B_ShowcaseEnemy_ExitCombat.h"

AB_ShowcaseEnemy_ExitCombat::AB_ShowcaseEnemy_ExitCombat()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(200.0f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = TriggerBox;
}

void AB_ShowcaseEnemy_ExitCombat::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AB_ShowcaseEnemy_ExitCombat::OnOverlap);
	}
}

void AB_ShowcaseEnemy_ExitCombat::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Implemented in Blueprint - triggers enemy to exit combat
}
