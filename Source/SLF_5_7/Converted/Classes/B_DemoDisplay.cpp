#include "B_DemoDisplay.h"

AB_DemoDisplay::AB_DemoDisplay()
{
	PrimaryActorTick.bCanEverTick = false;

	TextDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextDisplay"));
	RootComponent = TextDisplay;
}
