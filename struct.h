//typedef struct ZCONTROLPAD;//GenocideGenerationsGaming Emulation Of GamePad Controller
struct ZCONTROLPAD
{
 Sint8 angle;
 Uint8 button[11];           
};//GenocideGenerationsGaming Emulation Of GamePad Controller

//typedef enum GameModes;//GGG supported(*partialy could unsuppored yet) gameloop modes


enum GameModes
{
LOADING_EDITOR,//*
LOADING_NORMAL,//*
PLAYER_NAME,//*
LOADING_GAME,//*
GAME,//*
MAINMENU,//*
CLOSING_CREDITS,
CHARACTERMENU,//*
EDITOR_MENU,//*
EDITOR_LEVEL,
EDITOR_MODEL,
EDITOR_TEXTURE,//*
EDITOR_PALETTE,
EDITOR_AI,
INTRO,
NOGAME,
SHOP
};
enum MAP_VIRTUAL_PAD// GenocideGenerationGaming button mapping
{
     PAD_A,
     PAD_X,
     PAD_B,
     PAD_Y,
     PAD_L1,
     PAD_R1,
     PAD_L2,
     PAD_R2,
     PAD_SELECT,
     PAD_START,
     PAD_Z         
};
