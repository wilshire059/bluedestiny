#include "B_ShowcaseEnemy_StatDisplay.h"

AB_ShowcaseEnemy_StatDisplay::AB_ShowcaseEnemy_StatDisplay()
{
	PrimaryActorTick.bCanEverTick = false;

	StatWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatWidget"));
	RootComponent = StatWidget;

	LinkedEnemy = nullptr;
}
