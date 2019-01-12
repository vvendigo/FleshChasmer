#include <SDL.h>
#include "globalvar.h"


#ifdef GP2X// GP2X button mapping

enum MAP_KEY
{
	VK_UP         , // 0
	VK_UP_LEFT    , // 1
	VK_LEFT       , // 2
	VK_DOWN_LEFT  , // 3
	VK_DOWN       , // 4
	VK_DOWN_RIGHT , // 5
	VK_RIGHT      , // 6
	VK_UP_RIGHT   , // 7
	VK_START      , // 8
	VK_SELECT     , // 9
	VK_FL         , // 10
	VK_FR         , // 11
	VK_FA         , // 12
	VK_FB         , // 13
	VK_FX         , // 14
	VK_FY         , // 15
	VK_VOL_UP     , // 16
	VK_VOL_DOWN   , // 17
	VK_FZ           // 18 :)
};
enum USBMAP_KEY
{
	USBVK_FA         , // 0
	USBVK_FX         , // 1
	USBVK_FB         , // 2
	USBVK_FY         , // 3
	USBVK_VOL_DOWN   , // 4
	USBVK_VOL_UP     , // 5
	USBVK_FL         , // 6
	USBVK_FR         , // 7
	USBVK_SELECT     , // 8
	USBVK_START      , // 9
	USBVK_FZ          // 10
};
#endif
#ifdef PC// WIN button mapping
enum MAP_KEY
{
	VK_FA         , // 0
	VK_FX         , // 1
	VK_FB         , // 2
	VK_FY         , // 3
	VK_VOL_DOWN   , // 4
	VK_VOL_UP     , // 5
	VK_FL         , // 6
	VK_FR         , // 7
	VK_SELECT     , // 8
	VK_START      , // 9
	VK_FZ          // 10
};
#endif


void ControlPadUpdate(void);
