#include <SDL.h>
#include <SDL_mixer.h>
#include "types.h"
#include "struct.h"
//#include "struct.h"
//SDL Genociding Support

//DELETE ME
extern Uint16 Model_Faces;
extern Uint16 Textured_Faces;
//DELETE ME


#ifdef PC
extern Uint8 ipal[256][3];
#endif

extern SDL_Surface *screen;
extern SDL_Joystick *joy;
//Sound SubEngine
extern int audio_rate;
extern Uint16 audio_format; 
extern int audio_channels;
extern int audio_buffers;
extern Uint8 volume;
extern Sint8 trackname_delay,volume_delay;
extern Sint8 SoundMode;
extern Uint8 ControlMode;

//extern Uint32 musicpos[50];
extern Uint8 Music_stack;

extern Mix_Chunk *music[50];
extern Uint8 music_loaded[50];
extern Mix_Chunk *d_sound[100];

extern Uint8 d_sound_count;
extern Uint8 showmap;
extern Uint8 blockmapstatus[256];

extern Uint8 Music_Volume_Mix,Music_Volume;
extern Sint8 Music_Fade_Count;
extern Uint8 Music_Track,Next_Music_Track;
extern Uint16 dialogcount,messagecount;

extern ZCONTROLPAD controlpad;
extern SDL_Joystick *USBjoy;

extern Uint8 GameLoopEnabled;
extern Uint8 GameMode,NewGameMode,EditorOn,fadecount;
extern Uint8 scrbuf[76800],scrbuf0[19200];

extern Uint8 screenborder,cscreenborder;
extern Uint32 count;
extern Sint8 menupos;

extern Uint8 ControlType;
extern char s_textstring[128];
extern int l_textstring;
extern Uint8 CradleMode;


extern Uint32 ltickcount,tickcount,tickcount2;
extern Uint8 fps,fps_done;


extern Uint32 Tile_offset[256];
extern Uint8 Tile[65536];
extern Uint8 model_scalei[256];

extern Sint32 matrix[16],camera[6],rcamera[6],width,height,dist,dist0,zbuffer[76800],zbuffer0[19200];
extern Uint8 agressive_cam;

extern Sint32 screen_x0,screen_x1,screen_y0,screen_y1,screen_cx,screen_cy;
extern Sint32 screen0_x0,screen0_x1,screen0_y0,screen0_y1,screen0_cx,screen0_cy;

extern Sint32 f_sin[4096],f_cos[4096],f_tan[1024];

extern Uint8 palfade0[256],palfade1[256],palfade2[256];

extern Sint32 fog0[160],fog1[160],fog2[160],fog3[160];

extern Sint32 debugval0,debugval1;
extern Uint8 cameradelay;
extern Uint8 deathtrigger;
//Models
extern Sint32 m_vx[32768],m_vy[32768],m_vz[32768];
extern Uint16 f_0[4096],f_1[4096],f_2[4096];
extern Uint8 f_c[4096];
extern Uint16 model_f0[256],model_v0[256];
extern Uint8 model_ani[256],model_fs[256],model_vs[256];
extern Sint32 model_scalex[256],model_scaley[256],model_scalez[256];

extern Sint16 proxy_cache_x,proxy_cache_y;
extern Sint8 interface_L,interface_R;
//Monsters
extern Uint8 playerstart_x,playerstart_y,playerstart_z,lastcamera;

extern Uint8 CameraMode;
extern Sint32 customcamera[6];

extern Uint8 monster_ai_target[16],monster_flood_score[16];
extern Uint8 monster_respawn[16];
extern Uint32 monster_respawni[16];
extern Uint8 monsters,monster_ingame[16];
extern Uint8          monster_spawnx[16],monster_spawny[16],monster_spawnz[16],monster_status[16];
extern Uint8          monster_ai_state[16],monster_ai_action[16],monster_ai_delay[16];
extern Sint32         monster_ai_angle[16],monster_cx[16],    monster_cy[16],    monster_cz[16];
extern Sint32         monster_x[16],     monster_y[16],     monster_z[16];
extern Sint32         monster_ix[16],    monster_iy[16],    monster_iz[16];
extern Sint32         monster_angle[16], monster_roomi[16],monster_radius[16], monster_speed[16];
extern Sint32         monster_anglex[16],monster_anglez[16];


extern Uint8  monster_pain[16],monster_warmode[16],monster_melee[16];
extern Uint8  monster_model[16],monster_frame0[16],monster_frame1[16],monster_anim[16],monster_animcount[16];
extern Uint16 model_mmv,model_mmf,model_mms;//For Memory Report Situation // EditorSpec
extern Uint8  monster_action[16],monster_type[16],monster_animtag[16];
extern Uint16  monster_pause[16],monster_actioncount[16];
extern Uint8  monster_side[16],monster_blinkcount[16],monster_visible[16],monster_deathtrigger[16];
extern Sint16 monster_hp[16],monster_mhp[16],monster_mn[16],monster_mv[16];
extern Uint16 monster_ill[16],monster_hasted[16],monster_blessed[16],monster_poisoned[16],monster_confuzed[16],monster_magicarmor[16],monster_shielded[16],monster_invisible[16],monster_slowed[16],monster_charmed[16];
extern Uint8 monster_modelcolor[16],monster_healed[16];
//
extern Sint32 table_range[16][16],table_angle[16][16];
extern Uint8 table_vis[16][16];
//Monster Table
extern Uint16 t_monster_exp[32];
extern Sint32 t_monster_radius[32];
extern Sint32 t_monster_speed[32],t_monster_speed0[32],t_monster_speed1[32];
extern Sint32 t_monster_attackradius[32],t_monster_height[32];
extern Uint8  t_monster_stepsound[32];
extern Uint8  t_monster_model[32];
extern Uint8  t_monster_status[32];
extern Uint8  t_monster_side[32],monster_agony[16];
extern Uint8  t_monster_ai[32][5][8];
extern Sint16 t_monster_hp[32][2],t_monster_mn[32],t_monster_mv[32],t_monster_mv0[32],t_monster_mv1[32];
extern char   t_monster_name[32][32];
extern Uint16  t_monster_str[32],t_monster_int[32],t_monster_dex[32],t_monster_con[32],t_monster_wis[32],t_monster_cha[32];
extern Uint16 t_monster_damage[32][2],t_monster_mdamage[32][2];
extern Uint16 t_monster_armor[32],t_monster_resist[32];
extern Uint8  t_monster_regen[32][5];

extern Uint8  t_monster_warmodecount[32];
extern Uint8  t_monster_meleeanim[32][3];
extern Uint8  t_monster_meleeframecount[32];
extern Uint8  t_monster_shootframe[32],t_monster_shoottype[32],t_monster_shootdelay[32];
extern Uint8  t_monster_walkframe0[32];
extern Uint8  t_monster_meleeframe0[32];
extern Uint8  t_monster_painframe0[32];
extern Uint8  t_monster_painframecount[32];
extern Uint8  t_monster_meleesound[32],t_monster_painsound[32];
extern Uint16 t_monster_shootdamage[32][2];
extern Uint16 t_monster_meleerange[32];
extern Uint32 t_monster_targetrange[32];
extern Uint8  t_monster_deathtype[32];
extern Uint8  t_monster_maxagonycount[32];
extern Uint8  t_monster_deathframe[32];
extern Uint8  t_monster_castframe0[32];
extern Uint8  t_monster_deathspeed[32];
extern Uint8  t_monster_action[32][5];
extern Uint8  t_monster_simpleanim[32];
extern Uint8  t_monster_damageeffect[32];
extern Uint8 t_monster_deathsound[32];
extern Uint8 t_monster_loot[32][3][3];
extern Uint8  t_monster_char[32][2];

//
extern Uint8 STATUS_ALIVE,STATUS_FLOATING,STATUS_TANK,STATUS_BOSS,STATUS_WORM,STATUS_UNDEAD,STATUS_CRAWLING,STATUS_AI;

//Indicators
extern Uint8 indicator_count[4],indicator_i;
extern Sint32 indicator_arg[4];
extern Sint32 indicator_x[4],indicator_y[4],indicator_z[4];

extern Uint8 player_proxy[9][9];

//Fields of Prophert (_type 0=> sprite)
extern Uint8  field_ingame[32],field_count[32],field_index[32],field_frame[32],field_type[32];
extern Sint32 field_x[32],field_y[32],field_z[32],field_ix[32],field_iy[32],field_iz[32],field_tx[32],field_ty[32],field_tz[32];
extern Sint32 field_w[32],field_iw[32];
//Sprites

//Loot
extern Sint32 loot_x[16],loot_y[16],loot_z[16],loot_x0[16],loot_y0[16],loot_z0[16];
extern Sint32 loot_rx[16],loot_ry[16],loot_rz[16];
extern Sint16 loot_count[16];
extern Uint8 loot_item[16],loot_itemcount[16];

//Player
extern Uint8 handsword,handpistol;

extern Sint8 danger_status,ldanger_status;
extern Uint32 iGameTime;
extern Sint32 exp_bonus,exp_count;
//extern Uint8 skill;
extern Uint8 chmenu_x,chmenu_y[4];
extern Uint8 lvlclass[4],ch_level,ch_class;
extern Sint32 ch_exp;
extern Sint32 exp_lvl[99];
extern Uint16 item_c[64],item_p[64];
extern Uint8 skill_l[32],skill_p[32];
extern Uint8 player_arm[3];

//LEVEL
extern Sint8 meshxdisplace[131072];
extern Sint8 meshydisplace[131072];
extern Sint8 meshzdisplace[131072];

extern Uint8 blockmapstarus[256];

extern Uint8 fogcolor,param,levelmusictrack,maxmonsters,counttextureanimation,tiledata_animated[256],tiledata_finalbreak[256],tiledata_breakable[256],tiledata_alpha[256],tiledata_block[256],tiledata_sound[256];
extern Uint8 levelwarmusictrack;
extern Sint32 fogrange0,fogrange1;
extern Sint8 CurrentLevel,LoadedLevel;
extern Uint8 levelx,levely,levelz,levelsight,triggers,movies;

extern Sint32 meshx[131072],meshy[131072],meshz[131072];
extern Uint8 map[131072],mapt0[131072],mapt1[131072],mapt2[131072],mapt3[131072],mapt4[131072],mapt5[131072];
extern Uint8 mapcam0[131072],mapcam1[131072],mapcam2[131072],mapcam3[131072],mapai[131072],mapobj[131072];
extern Uint8 staticcams;
extern Sint32 staticcam[128][6];
extern Uint8 level_tag;
extern Uint8 trig[512];
extern char new_message[64];
extern Uint8 movie_mode,lmovie_mode;
extern Uint8 lastcamdelay,MonsterHpMode;

//video background

extern Uint8 bng[76800];
extern Uint8 chbng[76800];

//end of video Bg

extern void LoadLevel(Uint8 num);
extern void ClearLevel(void);

extern void LoadBNG(void);
