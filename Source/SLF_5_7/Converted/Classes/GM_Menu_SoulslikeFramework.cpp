#include "GM_Menu_SoulslikeFramework.h"
#include "PC_Menu_SoulslikeFramework.h"

AGM_Menu_SoulslikeFramework::AGM_Menu_SoulslikeFramework()
{
	PlayerControllerClass = APC_Menu_SoulslikeFramework::StaticClass();
	DefaultPawnClass = nullptr; // Menu mode doesn't spawn pawn
}
