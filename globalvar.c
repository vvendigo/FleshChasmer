#include "globalvar.h"
#include <video.h>

//DELETE ME
Uint16 Model_Faces;
Uint16 Textured_Faces;
//DELETE ME
#ifdef PC
Uint8 ipal[256][3];
#endif

bool fullscreen = true;

SDL_Surface *screen;

Uint8 d_sound_count = 0;
int audio_channels = 2;
int audio_rate = 8000;

#ifdef GP2X
Uint16 audio_format = AUDIO_U8; 
int audio_buffers = 256;
#endif 
#ifdef PC
Uint16 audio_format = AUDIO_S16; 
int audio_buffers = 512;
#endif 

Uint8 Music_stack;
Mix_Chunk *music[50];
Uint8 music_loaded[50];
Mix_Chunk *d_sound[100];
Uint16 dialogcount,messagecount;

ZCONTROLPAD controlpad;
Uint8 Music_Volume_Mix=100,Music_Volume=50;
Sint8 Music_Fade_Count=0;
Uint8 Music_Track=255,Next_Music_Track;

Uint8 volume;
Sint8 trackname_delay,volume_delay=0;
Sint8 SoundMode=0;

SDL_Joystick *joy;
SDL_Joystick *USBjoy;

Uint8 CameraMode;
Sint32 customcamera[6];


Uint8 GameLoopEnabled=1,EditorOn=0;
Uint8 GameMode=LOADING_EDITOR,NewGameMode;
Sint8 menupos=0;
Sint32 debugval0,debugval1;
Uint8 cameradelay=0,IndicatorMode;

Uint8 ControlMode;
Uint8 CradleMode;
Uint8 scrbuf[76800],scrbuf0[19200],fadecount=2;
Uint8 palfade0[256],palfade1[256],palfade2[256];
Sint32 fog0[160],fog1[160],fog2[160],fog3[160];

Uint8 screenborder=20,cscreenborder=0;

Uint32 count;
Uint8 levelmusictrack=50,counttextureanimation,tiledata_animated[256],tiledata_alpha[256],tiledata_finalbreak[256],tiledata_breakable[256],tiledata_block[256],tiledata_sound[256];

char s_textstring[128];
int l_textstring;
Uint32 tickcount,tickcount2,ltickcount;
Uint8 fps,fps_done;

Uint8 agressive_cam;
Sint32 camera[6],rcamera[6],matrix[16],dist=95500,dist0=90000;
Sint32 zbuffer[76800],zbuffer0[19200];

//LevelStructDesc
Uint8 fogcolor=19,param=0,levelsight=5,maxmonsters=8;
Sint32 fogrange0=200000,fogrange1=300000;
Sint8 CurrentLevel=0,LoadedLevel=-1;
Uint8 levelx,levely,levelz,triggers,movies;


Uint8 blockmapstatus[256];

Sint16 proxy_cache_x,proxy_cache_y;
Sint8 interface_L,interface_R;
Uint8 deathtrigger;
//Monsters
Uint8 playerstart_x,playerstart_y,playerstart_z,lastcamera;
Uint8 model_scalei[256];

Uint8 showmap;
Uint8 monsters,monster_ingame[16],monster_flood_score[16],monster_deathtrigger[16],monster_healed[16];
Uint8          monster_spawnx[16],monster_spawny[16],monster_spawnz[16],monster_status[16];
Uint8          monster_ai_state[16],monster_ai_action[16],monster_ai_delay[16];
Sint32         monster_ai_angle[16],monster_cx[16],    monster_cy[16],    monster_cz[16];

Uint8 monster_ai_target[16];
Uint8 monster_respawn[16];
Uint32 monster_respawni[16];
Sint32         monster_x[16],     monster_y[16],     monster_z[16];
Sint32         monster_ix[16],    monster_iy[16],    monster_iz[16];
Sint32         monster_angle[16], monster_roomi[16], monster_radius[16],monster_speed[16];
Sint32         monster_anglex[16],monster_anglez[16];
Uint8  monster_pain[16],monster_warmode[16],monster_melee[16];
Uint8  monster_model[16],monster_frame0[16],monster_frame1[16],monster_anim[16],monster_animcount[16],monster_blinkcount[16],monster_visible[16];
Uint8  monster_action[16],monster_type[16],monster_animtag[16];
Uint16  monster_pause[16],monster_actioncount[16];
Uint8  monster_side[16],monster_agony[16];
Sint16 monster_hp[16],monster_mhp[16],monster_mn[16],monster_mv[16];
Uint16 monster_ill[16],monster_hasted[16],monster_blessed[16],monster_poisoned[16],monster_confuzed[16],monster_magicarmor[16],monster_shielded[16],monster_invisible[16],monster_slowed[16],monster_charmed[16];
Uint8 monster_modelcolor[16];
//
Sint32 table_range[16][16],table_angle[16][16];
Uint8 table_vis[16][16];
//Monster Table
Sint32 t_monster_radius[32];
Sint32 t_monster_speed[32],t_monster_speed0[32],t_monster_speed1[32];
Sint32 t_monster_attackradius[32],t_monster_height[32];
Uint8  t_monster_stepsound[32];
Uint8  t_monster_model[32];
Uint8  t_monster_status[32];
Uint8  t_monster_side[32];
Uint8  t_monster_ai[32][5][8];
Sint16 t_monster_hp[32][2],t_monster_mn[32],t_monster_mv[32],t_monster_mv0[32],t_monster_mv1[32];
char   t_monster_name[32][32];
Uint16  t_monster_str[32],t_monster_int[32],t_monster_dex[32],t_monster_con[32],t_monster_wis[32],t_monster_cha[32];
Uint16 t_monster_damage[32][2],t_monster_mdamage[32][2];
Uint16 t_monster_armor[32],t_monster_resist[32];
Uint8  t_monster_regen[32][5];

Uint8  t_monster_warmodecount[32];
Uint8  t_monster_meleeanim[32][3];
Uint8  t_monster_meleeframecount[32];
Uint8  t_monster_walkframe0[32];
Uint8  t_monster_damageeffect[32];
Uint8  t_monster_meleeframe0[32];
Uint8  t_monster_painframe0[32];
Uint8  t_monster_painframecount[32];
Uint8  t_monster_meleesound[32],t_monster_painsound[32];
Uint8  t_monster_action[32][5];
Uint16 t_monster_meleerange[32];
Uint32 t_monster_targetrange[32];
Uint8  t_monster_castframe0[32];
Uint8  t_monster_deathtype[32];
Uint8  t_monster_maxagonycount[32];
Uint8  t_monster_deathframe[32];
Uint8  t_monster_deathspeed[32];
Uint8  t_monster_shootframe[32],t_monster_shoottype[32],t_monster_shootdelay[32];
Uint16 t_monster_shootdamage[32][2];
Uint8 t_monster_loot[32][3][3];

Uint8  t_monster_char[32][2];
Uint8  t_monster_simpleanim[32];
Uint8 t_monster_deathsound[32];
//how much attacks the mondel +1has+warmodecount (0-model has no) so for warmode

//
Uint8 STATUS_ALIVE=1;
Uint8 STATUS_FLOATING=2;
Uint8 STATUS_TANK=4;
Uint8 STATUS_BOSS=8;
Uint8 STATUS_WORM=16;
Uint8 STATUS_UNDEAD=32;
Uint8 STATUS_CRAWLING=64;
Uint8 STATUS_AI=128;
//

//Indicators
Uint8 indicator_count[4],indicator_i;
Sint32 indicator_arg[4];
Sint32 indicator_x[4],indicator_y[4],indicator_z[4];

Uint8 player_proxy[9][9];

//Fields of Prophert (_type 0=> sprite)
Uint8  field_ingame[32],field_count[32],field_index[32],field_frame[32],field_type[32];
Sint32 field_x[32],field_y[32],field_z[32],field_ix[32],field_iy[32],field_iz[32],field_tx[32],field_ty[32],field_tz[32];
Sint32 field_w[32],field_iw[32];
//Sprites

Uint8 handsword,handpistol;

//Loot
Sint32 loot_x[16],loot_y[16],loot_z[16],loot_x0[16],loot_y0[16],loot_z0[16];
Sint32 loot_rx[16],loot_ry[16],loot_rz[16];
Sint16 loot_count[16];
Uint8 loot_item[16],loot_itemcount[16];


//Player status etc
Sint8 danger_status,ldanger_status;
//Uint8 skill;
Sint32 exp_bonus,exp_count;
Uint8 chmenu_x,chmenu_y[4];
Uint8 lvlclass[4],ch_level,ch_class;
Sint32 ch_exp;
Sint32 exp_lvl[99];
Uint32 iGameTime=0;
Uint16 item_c[64],item_p[64];
Uint8 skill_l[32],skill_p[32];
Uint8 player_arm[3];
//Models
Sint32 m_vx[32768],m_vy[32768],m_vz[32768];
Uint16 f_0[4096],f_1[4096],f_2[4096];
Uint8 f_c[4096];
Uint16 model_f0[256],model_v0[256];
Uint8 model_ani[256],model_fs[256],model_vs[256];
Uint16 model_mmv,model_mmf,model_mms;
Sint32 model_scalex[256],model_scaley[256],model_scalez[256];
Uint8 staticcams=0;
Sint32 staticcam[128][6];
//Sint8 meshdisplace[131072];
Sint32 meshx[131072],meshy[131072],meshz[131072];
Uint8 map[131072],mapt0[131072],mapt1[131072],mapt2[131072],mapt3[131072],mapt4[131072],mapt5[131072];
Uint8 mapcam0[131072],mapcam1[131072],mapcam2[131072],mapcam3[131072],mapai[131072],mapobj[131072];
Uint8 lastcamdelay=0,MonsterHpMode;

Sint8 meshxdisplace[131072];
Sint8 meshydisplace[131072];
Sint8 meshzdisplace[131072];
Uint8 levelwarmusictrack;
Uint8 level_tag;
Uint8 movie_mode=0,lmovie_mode=0;

char new_message[64];
Uint8 trig[512];
//RenderScreenDesc
Sint32 screen_x0=0,screen_x1=319,screen_y0=20,screen_y1=218,screen_cx=160,screen_cy=120;
Sint32 screen0_x0=0,screen0_x1=159,screen0_y0=10,screen0_y1=109,screen0_cx=80,screen0_cy=60;


//STATICLOADED TABLES
Sint32 f_sin[4096],f_cos[4096],f_tan[1024];


//STATICLOADED TILESET
Uint32 Tile_offset[256];
Uint8 Tile[65536];

//STATICLOADED MODELS


//BG
Uint8 bng[76800];
Uint8 chbng[76800];


//Dynamic Loading

void LoadBNG(void)
{
Sint32 i;
FILE *fp;
fp=fopen("data/pic00.bng","rb");
if (fp)
 {
 for (i=0;i<76800;i++) bng[i]=fgetc(fp);
 fclose(fp);       
 }
fp=fopen("data/pic01.bng","rb");
if (fp)
 {
 for (i=0;i<76800;i++) chbng[i]=fgetc(fp);
 fclose(fp);       
 }


}
void LoadLevel(Uint8 num)
{
FILE *fp;
Uint8 c,c1,ext,j;
ClearLevel();
Uint8 x,y,z,k;
Uint16 i;
Uint32 t;
char spath[64];
sprintf(spath,"data/Level%i%i.zgz",num/10,num%10);
fp=fopen(spath,"rb");
if (fp)
{
fogcolor=fgetc(fp);
levelx=fgetc(fp);
levely=fgetc(fp);
levelz=fgetc(fp);
levelsight=fgetc(fp);
maxmonsters=fgetc(fp);
levelmusictrack=fgetc(fp);
level_tag=fgetc(fp);

for (z=0;z<=levelz+1;z++)     
for (y=0;y<=levely+1;y++)
for (x=0;x<=levelx+1;x++)
{
 meshx[x+y*128+z*16384]=65536*x;
 meshy[x+y*128+z*16384]=65536*y;
 meshz[x+y*128+z*16384]=65536*z;
}
for (z=0;z<=levelz;z++)     
for (y=0;y<=levely;y++)
for (x=0;x<=levelx;x++)
{
t=x+y*128+z*16384;
c=fgetc(fp);
if (c & 1) map[t]=fgetc(fp);    
if (c & 2) mapt0[t]=fgetc(fp);
if (c & 4) mapt1[t]=fgetc(fp);
if (c & 8) mapt2[t]=fgetc(fp);
if (c & 16) mapt3[t]=fgetc(fp);
if (c & 32) mapt4[t]=fgetc(fp);
if (c & 64) mapt5[t]=fgetc(fp);    
if (c & 128) {

c1=fgetc(fp);
if (c1 & 1) 
      {
      meshxdisplace[t]=fgetc(fp);    
      meshx[t]=65536*x+(meshxdisplace[t])*256;
      }
if (c1 & 2) 
      {
      meshydisplace[t]=fgetc(fp);    
      meshy[t]=65536*y+(meshydisplace[t])*256;
      }
if (c1 & 4) 
      {
      meshzdisplace[t]=fgetc(fp);    
      meshz[t]=65536*z+(meshzdisplace[t])*256;
      }
if (c1 & 8) 
      {
      mapcam0[t]=fgetc(fp);
      if (mapcam0[t] &128)    
       {
       mapcam1[t]=fgetc(fp);
       mapcam2[t]=fgetc(fp);
       mapcam3[t]=fgetc(fp);
       }
      }
if (c1 & 16) 
  {
   mapobj[t]=fgetc(fp);
   if (mapobj[t]==1) {playerstart_x=x;playerstart_y=y;playerstart_z=z;}
  }
if (c1 & 32) mapai[t]=fgetc(fp);
 }
}

/*
{
t=x+y*128+z*16384;
c=fgetc(fp);
if (c & 1) map[t]=fgetc(fp);    
if (c & 2) mapt0[t]=fgetc(fp);
if (c & 4) mapt1[t]=fgetc(fp);
if (c & 8) mapt2[t]=fgetc(fp);
if (c & 16) mapt3[t]=fgetc(fp);
if (c & 32) mapt4[t]=fgetc(fp);
if (c & 64) mapt5[t]=fgetc(fp);    
if (c & 128) mapai[t]=fgetc(fp);

c=fgetc(fp);
if (c & 1) 
      {
      meshxdisplace[t]=fgetc(fp);    
      meshx[t]=65536*x+(meshxdisplace[t])*256;
      }
if (c & 2) 
      {
      meshydisplace[t]=fgetc(fp);    
      meshy[t]=65536*y+(meshydisplace[t])*256;
      }
if (c & 4) 
      {
      meshzdisplace[t]=fgetc(fp);    
      meshz[t]=65536*z+(meshzdisplace[t])*256;
      }
if (c & 8) 
      {
      mapcam0[t]=fgetc(fp);
      if (mapcam0[t] &128)    
       {
       mapcam1[t]=fgetc(fp);
       mapcam2[t]=fgetc(fp);
       mapcam3[t]=fgetc(fp);
       }
      }
if (c & 16) 
  {
   mapobj[t]=fgetc(fp);
   if (mapobj[t]=1) {playerstart_x=x;playerstart_y=y;playerstart_z=z;}
  }

}
*/


staticcams=fgetc(fp);//Static Cameras
if (staticcams>0)
 for (i=0;i<staticcams;i++)
 for (k=0;k<6;k++)
  staticcam[i][k]=fgetc(fp)*65536+fgetc(fp)*256+fgetc(fp);

//Triggers
for (i=0;i<512;i++)
 trig[i]=fgetc(fp);

//Videos

//movie
for (i=0;i<16;i++)
{
movie_length[i]=fgetc(fp)*256+fgetc(fp);
if (movie_length[i])
 {
movie_type[i]=fgetc(fp);
movie_num_layers[i]=fgetc(fp);
 //layers 0-7
for (Uint8 k=0;k<=movie_num_layers[i];k++)
 {           
movie_layer_nodes[i][k]=fgetc(fp);
if (movie_layer_nodes[i][k])
  {
   for (Uint8 n=0;n<movie_layer_nodes[i][k];n++)
   {
   for (j=0;j<3;j++)
    {
    movie_node[i][n][k][j]=fgetc(fp)*65536+fgetc(fp)*256+fgetc(fp);
    }
   for (j=3;j<6;j++)
    {
    movie_node[i][n][k][j]=fgetc(fp)*256+fgetc(fp);
    }
    movie_node_pos[i][n][k]=fgetc(fp)*256+fgetc(fp);

   }                         
  }           
 }              
                    
 //control layer 8(eight - not a smile with no teeth)
 movie_control_nodes[i]=fgetc(fp);
 if (movie_control_nodes[i])
  {
   for (Uint8 n=0;n<movie_control_nodes[i];n++)
   {
   for (j=0;j<3;j++)
    {
    movie_control_node[i][n][j]=fgetc(fp);
    }
    movie_control_node_pos[i][n]=fgetc(fp)*256+fgetc(fp);

   }                           
                            
  }
 }
}


fclose(fp);       
}
     
     
     
}
void ClearLevel(void)
{
ClearMovie();

messagecount=0;
dialogcount=0;

monsters=0;     
     
levelx=0;
levely=0;
levelz=0;
fogcolor=16;
levelsight=5;
levelmusictrack=50;
staticcams=0;movies=0;triggers=0;

Sint32 t;
int x,y,z;
for (z=0;z<8;z++)     
for (y=0;y<128;y++)
for (x=0;x<128;x++)
 {
    t=x+y*128+z*16384;               
 map  [t]=0;
 mapt0[t]=0;
 mapt1[t]=0;
 mapt2[t]=0;
 mapt3[t]=0;
 mapt4[t]=0;
 mapt5[t]=0;
 mapai[t]=0;
 mapcam0[t]=0;
 mapcam1[t]=0;
 mapcam2[t]=0;
 mapcam3[t]=0;
 mapobj[t]=0;
 map[t]=0;
 meshxdisplace[t]=0;
 meshydisplace[t]=0;
 meshzdisplace[t]=0;

 meshx[t]=65536*x;
 meshy[t]=65536*y;
 meshz[t]=65536*z;
 }     

for (z=0;z<126;z++)
{
staticcam[z][0]=0;    
staticcam[z][1]=0;
staticcam[z][2]=0;
staticcam[z][3]=0;
staticcam[z][4]=0;
staticcam[z][5]=0;
}     
for (t=0;t<512;t++)
trig[t]=0;
}


