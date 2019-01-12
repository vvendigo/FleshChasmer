#include "controlpad.h"
#include "camera.h"
#include <stdlib.h>
#include "sound.h"
#include "editor.h"
#include "game.h"

static const Sint8 dirpad[8][2]=
{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
void proccontrol(void)
{
ControlPadUpdate();
}
void MiscProc(void)
{
counttextureanimation=count/3%4;
if (cscreenborder!=screenborder)
 {
  if (cscreenborder>screenborder) cscreenborder-=2;else cscreenborder+=2;
  
  screen_y0=cscreenborder;                               
  screen0_y0=screen_y0/2;
  screen_y1=239-cscreenborder;                               
  screen0_y1=screen_y1/2+1;
 }     
     
     
}


void Gameprocess(void)
{
MiscProc();
proccontrol();
ProcSound();     
if (EditorOn) ProcEditor();
if (GameMode==GAME) gamestep();
camproc();

}
