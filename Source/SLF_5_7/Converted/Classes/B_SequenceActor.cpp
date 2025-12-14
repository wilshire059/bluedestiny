#include "B_SequenceActor.h"

AB_SequenceActor::AB_SequenceActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bAutoPlay = false;
}

void AB_SequenceActor::PlaySequence()
{
	// Implemented in Blueprint
}

void AB_SequenceActor::StopSequence()
{
	// Implemented in Blueprint
}
