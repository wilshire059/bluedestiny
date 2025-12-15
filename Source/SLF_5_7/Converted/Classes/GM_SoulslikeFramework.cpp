#include "GM_SoulslikeFramework.h"
#include "GS_SoulslikeFramework.h"
#include "PC_SoulslikeFramework.h"
#include "PS_SoulslikeFramework.h"

AGM_SoulslikeFramework::AGM_SoulslikeFramework()
{
	GameStateClass = AGS_SoulslikeFramework::StaticClass();
	PlayerControllerClass = APC_SoulslikeFramework::StaticClass();
	PlayerStateClass = APS_SoulslikeFramework::StaticClass();
	// DefaultPawnClass set in Blueprint child
}
