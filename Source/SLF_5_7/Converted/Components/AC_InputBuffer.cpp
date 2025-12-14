#include "AC_InputBuffer.h"

UAC_InputBuffer::UAC_InputBuffer()
{
	PrimaryComponentTick.bCanEverTick = true;
    bBufferOpen = false;
}

void UAC_InputBuffer::BeginPlay()
{
	Super::BeginPlay();
}

void UAC_InputBuffer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_InputBuffer::ToggleBuffer(bool bOpen)
{
    bBufferOpen = bOpen;
}

void UAC_InputBuffer::QueueAction(FGameplayTag ActionTag)
{
    QueueNext(ActionTag);
}

void UAC_InputBuffer::QueueNext(FGameplayTag ActionTag)
{
    if (bBufferOpen)
    {
        ConsumeInputBuffer();
        if (IgnoreNextOfActions.HasTag(ActionTag))
        {
            // Ignore logic
            return;
        }
        IncomingActionTag = ActionTag;
    }
    else
    {
        // JSON logic implies setting incoming tag and maybe waiting for next tick or condition
        if (!IncomingActionTag.IsValid())
        {
            IncomingActionTag = ActionTag;
        }
        else
        {
            // Already have action pending?
        }
    }
}

void UAC_InputBuffer::ConsumeInputBuffer()
{
    if (IncomingActionTag.IsValid())
    {
        OnInputBufferConsumed.Broadcast(IncomingActionTag);
        IncomingActionTag = FGameplayTag::EmptyTag; // Consume
    }
}
