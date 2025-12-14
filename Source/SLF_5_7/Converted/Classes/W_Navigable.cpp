#include "W_Navigable.h"

bool UW_Navigable::CanNavigate_Implementation()
{
    return IsVisible();
}
