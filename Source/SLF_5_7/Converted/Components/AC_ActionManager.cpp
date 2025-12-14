#include "AC_ActionManager.h"
#include "Net/UnrealNetwork.h"

UAC_ActionManager::UAC_ActionManager()
{
    PrimaryComponentTick.bCanEverTick = true;
    MovementDirection = E_Direction::Forward;
}

void UAC_ActionManager::BeginPlay()
{
    Super::BeginPlay();
}

void UAC_ActionManager::SetMoveDir(FVector2D IAMove)
{
    // Logic to calculate 8-way direction from Vector2D
    E_Direction NewDir = E_Direction::None;
    
    if (IAMove.Y > 0)
    {
        if (IAMove.X > 0) NewDir = E_Direction::ForwardRight;
        else if (IAMove.X < 0) NewDir = E_Direction::ForwardLeft;
        else NewDir = E_Direction::Forward;
    }
    else if (IAMove.Y < 0)
    {
        if (IAMove.X > 0) NewDir = E_Direction::BackwardRight;
        else if (IAMove.X < 0) NewDir = E_Direction::BackwardLeft;
        else NewDir = E_Direction::Backward;
    }
    else
    {
        if (IAMove.X > 0) NewDir = E_Direction::Right;
        else if (IAMove.X < 0) NewDir = E_Direction::Left;
    }

    if (NewDir != MovementDirection && NewDir != E_Direction::None)
    {
        SRV_SetDirection(NewDir);
    }
}

void UAC_ActionManager::SRV_SetDirection_Implementation(E_Direction Direction)
{
    MC_SetDirection(Direction);
}

void UAC_ActionManager::MC_SetDirection_Implementation(E_Direction Direction)
{
    MovementDirection = Direction;
    OnDirectionChanged.Broadcast(MovementDirection);
}
