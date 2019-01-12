#include "ai.h"
#include "triggers.h"
#include "RPG.h"
#include "game.h"
#include "sfont.h"
#include "render.h"
#include "items.h"
#include "video.h"
#include "interface.h"
#include "player.h"
#include "skills.h"
#include "sound.h"
#include "zmath.h"
#include "camera.h"
#include "monsters.h"
#include "globalvar.h"
#include "gpu.h"
#include "fields.h"
#include "zdialogs.h"
#include "flood.h"

#define FPMUL(x,y)	((((x)>>5)*((y)>>7))>>4)

Uint16 mainmenucount;
Uint8 musvolume,mainmenupos=1,mainmenupause=0,mainmenuspecial=0,mmsp=0;
Sint32 mmix=0,mmiy=0;

Uint8 pl_pic[100][200];
Sint16 chmenu_count;
Sint16 x0,y0;



void ClearIndicators(void)
{
indicator_count[0]=0;     
indicator_count[1]=0;
indicator_count[2]=0;
indicator_count[3]=0;
}

void GetPlayerPic(void)
{
  screen_y0=0;                               
  screen0_y0=screen_y0/2;
  screen_y1=239;                               
  screen0_y1=screen_y1/2+1;

Sint16 x;
Sint16 y;
zlvertex=0;
monster_angle[0]=SuperAngle(monster_angle[0]);
zlpoint(monster_x[0]+f_cos[monster_angle[0]]/7,monster_z[0],monster_y[0]+f_sin[monster_angle[0]]/7);

x0=vbufferx[0]*2-50;
y0=vbuffery[0]*2-140;

y0=0;
if (x0<0) x0=0;
else
if (x0>219) x0=219;

if (y0<0) y0=0;
else
if (y0>39) y0=39;

ClearIndicators();
renderscene();
for (x=0;x<100;x++)
for (y=0;y<200;y++)
{
pl_pic[x][y]=scrbuf[(x+x0)+(y+y0)*320];
}
}

Uint8 zVis_function(Uint8 i,Uint8 n)
{
Uint8 vis=0;      

Sint8 cx,cy,cz;
Sint8 nx,ny,nz;
Sint32 ix,iy,iz,r,it,st;
Sint32 x,y,z,t;

r=table_range[i][n];
it=r/32666;

if (it==0) vis=1;
else
 {
ix=(monster_x[n]-monster_x[i])/it;
iy=(monster_y[n]-monster_y[i])/it;
iz=(monster_z[n]-monster_z[i])/it;

cx=monster_cx[i];
cy=monster_cy[i];
cz=monster_cz[i];
x=monster_x[i];
y=monster_y[i];
z=monster_z[i]+20000;


st=0;vis=1;
 do
  {
              
   t=cx+cy*128+cz*16384;
   if (t<0) break;
   x=x+ix;           
   z=z+iz;           
   nx=x>>16;
   nz=z/65536;
   if (nx!=cx)
    {
    if (nx<cx)
      {
       if (tiledata_block[mapt1[t]]) vis=0;
      }
      else
      {
       if (tiledata_block[mapt2[t]]) vis=0;
      }           
    cx=nx;          
    }
    
   y=y+iy;           
   ny=y>>16;
   t=cx+cy*128+cz*16384;

   if (ny!=cy)
    {
    if (ny<cy)
      {
       if (tiledata_block[mapt3[t]]) vis=0;
      }
      else
      {
       if (tiledata_block[mapt4[t]]) vis=0;
      }           
    cy=ny;          
    }
   
   if (nz!=cz)
    {
    if (nz<cz)
      {
       if (tiledata_block[mapt0[t]]) vis=0;
      }
      else
      {
       if (tiledata_block[mapt5[t]]) vis=0;
      }           
    cz=nz;          
    }
   
   st++;           
  }while ((vis!=0)&(it!=st));
 }
return vis;
}
void proxy_calc(void)
{
Sint32 roomi,zi=monster_cz[0]*16384;
Sint8 x,y,i;
for (x=0;x<9;x++)
for (y=0;y<9;y++)
player_proxy[x][y]=255;
proxy_cache_x=monster_cx[0];
proxy_cache_y=monster_cy[0];
player_proxy[4][4]=0;
for (i=0;i<8;i++)
for (x=0;x<=8;x++)
for (y=0;y<=8;y++)
if (player_proxy[x][y]==i)
 {

 roomi=(x+monster_cx[0]-4)+(y+monster_cy[0]-4)*128+zi;
 if (x>0)
 if (x+monster_cx[0]-4>=0)
 if (tiledata_block[mapt1[roomi]]==0) 
 if (monster_status[0]&blockmapstatus[map[roomi-1]]==0)
 if (player_proxy[x-1][y]>i)
 player_proxy[x-1][y]=i+1;

 if (x<8)
 if (x+monster_cx[0]-4<levelx)
 if (tiledata_block[mapt2[roomi]]==0) 
 if (monster_status[0]&blockmapstatus[map[roomi+1]]==0)
 if (player_proxy[x+1][y]>i)
 player_proxy[x+1][y]=i+1;
                          
 if (y>0)
 if (y+monster_cy[0]-4>=0)
 if (tiledata_block[mapt3[roomi]]==0) 
 if (monster_status[0]&blockmapstatus[map[roomi-128]]==0)
 if (player_proxy[x][y-1]>i)
 player_proxy[x][y-1]=i+1;

 if (y<8)
 if (y+monster_cy[0]-4>=0)
 if (tiledata_block[mapt4[roomi]]==0) 
 if (monster_status[0]&blockmapstatus[map[roomi+128]]==0)
 if (player_proxy[x][y+1]>i)
 player_proxy[x][y+1]=i+1;

 }


}

void fill_table(void)
{
proxy_calc();//Leave me here
table_vis[0][0]=1;

for (Uint8 i=0;i<16;i++)
if (monster_ingame[i])
for (Uint8 n=0;n<16;n++)
if (monster_ingame[n])
if (n!=i)
{
if (i<n)
 {
 table_range[i][n]=fastrange(monster_x[i]-monster_x[n],monster_y[i]-monster_y[n]);
 table_angle[i][n]=arctan(monster_x[n]-monster_x[i],monster_y[n]-monster_y[i]);
 if ((monster_side[i]!=monster_side[n])&((monster_status[n]& STATUS_ALIVE)))
  table_vis[i][n]=zVis_function(i,n);
  else
  table_vis[i][n]=1;

 }
else
 {
 table_vis[i][n]=table_vis[n][i];
 table_range[i][n]=table_range[n][i];
 table_angle[i][n]=SuperAngle(2048+table_angle[n][i]);
 }
}
     
}

void monster_meleeproc(unsigned short int i)
{
Uint8 type=monster_type[i];
Sint16 exp=0;
if (i==0)
if (player_arm[0]) damage_meleeweapon();

Uint8 s=t_monster_meleesound[monster_type[i]];
if (s)
sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],s,406660+random(65534));
for (Uint8 n=0;n<16;n++)
if (n!=i)
if (monster_ingame[n])
if (monster_status[n]& STATUS_ALIVE)
if (monster_side[n]!=monster_side[i])
if (table_vis[i][n])
if (table_range[i][n]<monster_radius[i]+monster_radius[n]+t_monster_meleerange[monster_type[i]])
{
Sint32 angle=SuperAngle(table_angle[i][n]-monster_angle[i]);
if ((angle<1024)|(angle>3072))
 {
monster_angle[i]=table_angle[i][n];

Uint16 damage=t_monster_damage[type][0];
if (t_monster_damage[type][1])
damage+=random(t_monster_damage[type][1]+1);
monster_hurt(n,damage,0,i);     
 }
}     

}


void monster_map(Uint8 i)
{
Uint8 n=map[monster_roomi[i]];
switch (n)
 {
 case 2:
      if (monster_status[i]&STATUS_ALIVE)
      if (count%15==0) monster_hurt(i,2+random(10),2+random(10),16);  break;      
       
       
 }     
}

void ClearMess(void)
{
Uint8 i;
for (i=0;i<16;i++)
loot_count[i]=0;
for (i=0;i<32;i++)
field_ingame[i]=0;

}
void ClearMonsters(void)
{
for (Uint8 i=0;i<16;i++)
if (monster_ingame[i])
monster_kill(i);     
monsters=0;     
}
void Game_LoadNewLevel(void)
{
ClearIndicators();deathtrigger=0;
dialogcount=0;movie_playing=16;
ClearMess();
ClearMonsters();     
ResetCamera();ResetTriggers();

LoadLevel(CurrentLevel);
Music_Volume=50;
if (levelmusictrack<50)
 {
 NextMusicTrack(levelmusictrack);     
 Music_Fade_Count=25;                      
 }
cscreenborder=40;
screenborder=0;
spawnmonster(playerstart_x,playerstart_y,playerstart_z,level_tag);
if (level_tag==0)
{UpdatePlayer();FullRevive();}

//camset(playerstart_x,playerstart_y,playerstart_z);
//camsync();
camera[0]=0;
camera[1]=0;
camera[2]=0;
camera[3]=0;
camera[4]=2048;
camera[5]=0;

camsync();

danger_status=-25;
ldanger_status=-25;
levelwarmusictrack=levelmusictrack;
trig_status[0]=1;
trig_x[0]=playerstart_x;
trig_y[0]=playerstart_y;
trig_z[0]=playerstart_z;

if (CurrentLevel==0) {NewGameMode=INTRO;GameMode=INTRO;renderintro();}
count=0;
}

void ProcVolControl(void)
{
//     if(Music_Fade_Count==0)
   {  if (controlpad.button[PAD_L2])
      if (volume)
      { volume--;volume_delay=20;}
     if (controlpad.button[PAD_R2])
      { volume++;if (volume>128) volume=128;volume_delay=20;}
   }
     
     
}
void gamecontrol(void)
{
ProcVolControl();
if (controlpad.button[PAD_START]) 
if (Music_Fade_Count<25)
{  Music_stack=Next_Music_Track;NextMusicTrack(10);musvolume=Music_Volume;Music_Volume=20;mmsp=0;mainmenuspecial=0;NewGameMode=MAINMENU;mainmenucount=0;sPlaySound(3,128,128);}


}

void ChestAlarm(Uint8 i)
{
Uint8 m=mapobj[monster_roomi[i]];
if (m==34 | m==35)
 {
 Sint32 tx=monster_x[i]-monster_cx[i]*65536;
 Sint32 ty=monster_y[i]-monster_cy[i]*65536;
 tx=tx-32666;
 ty=ty-32666;
 
 if (zabs(tx)<29000 | zabs(ty)<29000)
  {
  monster_ix[i]=tx/50;
  monster_iy[i]=ty/50;
  monster_x[i]+=monster_ix[i];
  monster_y[i]+=monster_iy[i];
  }
 }
}

void monster_walk(Uint8 i,Sint32 angle,Sint32 speed)
{
monster_ix[i]+=FPMUL(speed,f_cos[angle]);                       
monster_iy[i]+=FPMUL(speed,f_sin[angle]);                       
}


void procmonsters(void)
{
Sint32 t,floorheight,tx,ty,tz;
Uint8 blocked,wall,tp;
Sint32 rangex,rangey,ix,iy;

fill_table();
for (int i=0;i<16;i++)
if (monster_ingame[i])
 {
  tp=monster_type[i];                    

  if (table_vis[0][i]) monster_flood_score[i]=0;

  if (monster_pause[i]>0)
   {
   monster_pause[i]--;
   if (monster_pause[i]==0)                      
       if (monster_action[i]!=4)
       {
       monster_action[i]=0;                  
//       monster_frame0[i]=0;
//       monster_frame1[i]=0;
//       monster_animtag[i]=0;
       }                  
                         
   }



  if (i)
   if (monster_status[i] & STATUS_AI)
   AI_proc(i);
  //pushing&&moving
   if (monster_status[i] & STATUS_ALIVE)
  if (i<15)                   
  for (Uint8 k=i+1;k<16;k++)
   if (monster_ingame[k])
   if (monster_status[k] & STATUS_ALIVE)
   {
    rangex=monster_x[i]-monster_x[k];         
    rangey=monster_y[i]-monster_y[k];         
    if (zabs(rangex)<monster_radius[i]+monster_radius[k])             
    if (zabs(rangey)<monster_radius[i]+monster_radius[k])
     {
//if monster_x[2]

monster_walk(k,table_angle[i][k],170); 
monster_walk(i,table_angle[k][i],170); 
//      monster_ix[i]+=rangex>>8-2+random(5);                               
//      monster_iy[i]+=rangey>>8-2+random(5);                               
//      monster_ix[k]-=rangex>>8;                               
//      monster_iy[k]-=rangey>>8;                               
      
                                                   
     }

   }                   
  //moving&&pushing
#define c_SpeedLimit 7000

if (monster_ix[i]>c_SpeedLimit) monster_ix[i]=c_SpeedLimit;else
if (monster_ix[i]<-c_SpeedLimit) monster_ix[i]=-c_SpeedLimit;

if (monster_iy[i]>c_SpeedLimit) monster_iy[i]=c_SpeedLimit;else
if (monster_iy[i]<-c_SpeedLimit) monster_iy[i]=-c_SpeedLimit;

//animation

ChestAlarm(i);            

if (monster_action[i]==2)
{//Attack
monster_actioncount[i]++;
if (monster_actioncount[i]==t_monster_meleeanim[tp][0]) 
 {
monster_newmelee(i);
monster_meleeproc(i);
if (i==0) rcamera[3]+=3+random(7);
 }
else
if (monster_actioncount[i]==t_monster_meleeanim[tp][1]) {monster_newwarmode(i);}
else
if (monster_actioncount[i]==t_monster_meleeanim[tp][2]) {monster_newwarmode(i);}
}
else
if (monster_action[i]<2)
{
if (t_monster_simpleanim[tp])
{
monster_frame0[i]=count/2%4;
monster_frame1[i]=monster_frame0[i];

}
else
{
if (zabs(monster_ix[i])+zabs(monster_iy[i])<400) monster_action[i]=0;
else
 {
if (monster_action[i]==0) monster_animcount[i]=50;
monster_action[i]=1;                                            
 }
if (monster_animcount[i]>=monster_anim[i]-1)
 {//stand&walk

monster_frame0[i]=monster_frame1[i];                        
monster_animtag[i]=(monster_animtag[i]+1)%4;
if (monster_action[i]==1)
  {//walk
  monster_frame1[i]=t_monster_walkframe0[tp]+monster_animtag[i]; 
  monster_anim[i]=3;
//if (i==0)
{
t=t_monster_stepsound[monster_type[i]];
 if (t)
  if (monster_frame1[i]%2==1)
   {
   if (t>1)
   sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],t,346660+random(65300));
   else
   {
   Uint8 i_snd=5+2*tiledata_sound[mapt0[monster_roomi[i]]];
   if (random(5)==0) i_snd++;
   sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],i_snd,346660+random(65300));
   }
   }
}//sound  
  }
 else
  {//stand
  monster_frame1[i]=monster_animtag[i]; 
  monster_anim[i]=8;   
  }
monster_animcount[i]=0;                                            
 }
else monster_animcount[i]++;
}
}//passive state
else
if (monster_action[i]==6)
{//casting
monster_actioncount[i]++;
monster_animcount[i]++;               
}
else
if (monster_action[i]==4)//DEATH of Eric Cartman :)
{
switch (t_monster_deathtype[tp])
{
case 1:

Uint16 t;
t=monster_actioncount[i]/t_monster_deathspeed[tp];
if (t<3)
 {
monster_frame0[i]=t_monster_deathframe[tp]+t;
monster_frame1[i]=monster_frame0[i]+1;
monster_animcount[i]=monster_actioncount[i]%t_monster_deathspeed[tp];
 }
else
if (monster_agony[i])
{
if (monster_actioncount[i]%10==1)
 {
monster_frame0[i]=t_monster_deathframe[tp]+2+random(2);
 
monster_frame1[i]=monster_frame0[i];
  monster_agony[i]--;            
 } 
}
else
if (i>0)
{
if (monster_blinkcount[i]>90)
if (monster_blinkcount[i]<130)
monster_visible[i]=monster_blinkcount[i]/3%4;
else    
if (monster_blinkcount[i]<167)
monster_visible[i]=monster_blinkcount[i]/3%3;
else monster_kill(i);

monster_blinkcount[i]++;    
}
break;
case 2://zombie
if (monster_actioncount[i]%3==0)
 {
monster_modelcolor[i]=32;
field0_x=monster_x[i]-4000+random(8000);       
field0_y=monster_y[i]-4000+random(8000);        
field0_z=t_monster_height[monster_type[i]]+monster_z[i]+random(4000);        
monster_angle[i]=SuperAngle(monster_angle[i]);

field0_ix=f_cos[monster_angle[i]]/10-1400+random(2800);        
field0_iy=f_sin[monster_angle[i]]/10-1400+random(2800);        
field0_iz=-400+random(800);


field0_w=8000+random(5000);
field0_iw=random(2000);
field0_index=248;        
SpawnField();        
                                
 }
if (monster_actioncount[i]>32) monster_visible[i]=monster_actioncount[i]/4%2;

if (i==0)
{if (monster_actioncount[i]==200) monster_kill(i);}
else
if (monster_actioncount[i]==64) monster_kill(i);

break;
case 3://tank
if (monster_actioncount[i]%10==0)
sPlaySound(24,30+random(98),30+random(98));

if (monster_actioncount[i]%3==0)
 {

field0_x=monster_x[i]-20000+random(40000);       
field0_y=monster_y[i]-20000+random(40000);        
field0_z=t_monster_height[monster_type[i]]+monster_z[i]+random(4000);        
monster_angle[i]=SuperAngle(monster_angle[i]);

field0_ix=f_cos[monster_angle[i]]/10-1400+random(2800);        
field0_iy=f_sin[monster_angle[i]]/10-1400+random(2800);        
field0_iz=2000;


field0_w=8000+random(5000);
field0_iw=1000+random(2000);
field0_index=240;        
SpawnField();        
 }
monster_frame0[i]=t_monster_deathframe[tp]+(monster_actioncount[i]/40)%4;

monster_frame1[i]=t_monster_deathframe[tp]+(monster_actioncount[i]/40+1)%4;

monster_anim[i]=40;
monster_animcount[i]=monster_actioncount[i]%40;

monster_actioncount[i]++;                                
//if (monster_actioncount[i]>600) monster_visible[i]=monster_actioncount[i]/4%2;

if (monster_actioncount[i]==119) monster_kill(i);

break;
case 4://One frame dead
if (monster_actioncount[i]>32) monster_visible[i]=monster_actioncount[i]/4%2;

if (monster_actioncount[i]==64) monster_kill(i);

break;
case 5://Titan Leech
//if (monster_actioncount[i]%2==0)
 {
field0_x=monster_x[i]-4000+random(8000);       
field0_y=monster_y[i]-4000+random(8000);        
field0_z=monster_z[i]+t_monster_height[monster_type[i]]+random(4000);        
monster_angle[i]=SuperAngle(monster_angle[i]);

field0_ix=f_cos[monster_angle[i]]/8-4800+random(9600);        
field0_iy=f_sin[monster_angle[i]]/8-4800+random(9600);        
field0_iz=400+random(2400);

if (monster_actioncount[i]%3==0)
monster_modelcolor[i]=36;

field0_w=8000+random(5000);
field0_iw=random(2000);
field0_index=248;        
SpawnField();        
monster_frame0[i]=t_monster_painframe0[monster_type[i]]+monster_actioncount[i]/2%2;
monster_frame1[i]=monster_frame0[i];
 }
if (monster_actioncount[i]>128) monster_visible[i]=monster_actioncount[i]/4%2;

if (i==0)
{if (monster_actioncount[i]==200) monster_kill(i);}
else
if (monster_actioncount[i]==160) monster_kill(i);

break;
}


monster_actioncount[i]++;                         
}



//ends of animation
//ZZZ
//ZZZ


monster_cx[i]=monster_x[i]>>16;
monster_cy[i]=monster_y[i]>>16;
monster_cz[i]=(monster_z[i])>>16;



//if (monster_cx[i]<0) monster_cx[i]=0;

tx=monster_x[i]-monster_cx[i]*65536;
ty=monster_y[i]-monster_cy[i]*65536;
tz=monster_z[i]-monster_cz[i]*65536;

t=monster_cx[i]+monster_cy[i]*128+monster_cz[i]*16384;
monster_roomi[i]=t;
if (map[t]) monster_map(i);

if (monster_ix[i]!=0)
{
 if (monster_ix[i]>0)
 {
  if (monster_cx[i]<levelx)
  {
  wall=0;
  
  wall=(tiledata_block[mapt2[t]]);
  if (monster_cy[i]<levely)
  if (ty+monster_radius[i]>65535)
  {
  wall=wall | (tiledata_block[mapt2[t+128]]);
  if (monster_status[i]&blockmapstatus[map[t+129]]) wall=1;
  }
  if (monster_cy[i]>0)
  if (ty-monster_radius[i]<0)
  {
  wall=wall | (tiledata_block[mapt2[t-128]]);
  if (monster_status[i]&blockmapstatus[map[t-127]]) wall=1;
  }
  if (monster_status[i]&blockmapstatus[map[t+1]]) wall=1;
  } else wall=1;
  
  blocked=0;
  if (wall)
  if (tx+monster_ix[i]>65535-monster_radius[i])
  blocked=1;
 if (blocked)
  {monster_x[i]=monster_cx[i]*65536+65533-monster_radius[i];monster_ix[i]=-monster_ix[i];}
 else
 monster_x[i]+=monster_ix[i];                      
 }
 else//ix<0
 {
  if (monster_cx[i]>0)
  {
  wall=0;
  wall=(tiledata_block[mapt1[t]]);
  if (monster_cy[i]<levely)
  if (ty+monster_radius[i]>65535)
  {
  wall=wall | (tiledata_block[mapt1[t+128]]);
  if (monster_status[i]&blockmapstatus[map[t+127]]) wall=1;
  }
  if (monster_cy[i]>0)
  if (ty-monster_radius[i]<0)
  {
  wall=wall | (tiledata_block[mapt1[t-128]]);
  if (monster_status[i]&blockmapstatus[map[t-129]]) wall=1;
  }
  if (monster_status[i]&blockmapstatus[map[t-1]]) wall=1;
  } else wall=1;
  blocked=0;
  if (wall)
  if (tx+monster_ix[i]<monster_radius[i])
  blocked=1;
 if (blocked)
  {monster_x[i]=monster_cx[i]*65536+2+monster_radius[i];monster_ix[i]=-monster_ix[i];}
 else
 monster_x[i]+=monster_ix[i];                      
 }
 
}

//////////////yyyyyyyyyy
if (monster_iy[i]!=0)
{
 if (monster_iy[i]>0)
 {
  if (monster_cy[i]<levely)
  {
  wall=0;
  
  wall=(tiledata_block[mapt4[t]]);
  if (monster_cx[i]<levelx)
  if (tx+monster_radius[i]>65535)
  {
  wall=wall | (tiledata_block[mapt4[t+1]]);
  if (monster_status[i]&blockmapstatus[map[t+129]]) wall=1;
  }
  if (monster_cx[i]>0)
  if (tx-monster_radius[i]<0)
  {
  wall=wall | (tiledata_block[mapt4[t-1]]);
  if (monster_status[i]&blockmapstatus[map[t+127]]) wall=1;
  }
  if (monster_status[i]&blockmapstatus[map[t+128]]) wall=1;
  } else wall=1;
  
  blocked=0;
  if (wall)
  if (ty+monster_iy[i]>65535-monster_radius[i])
  blocked=1;
 if (blocked)
  {monster_y[i]=monster_cy[i]*65536+65533-monster_radius[i];monster_iy[i]=-monster_iy[i];}
 else
 monster_y[i]+=monster_iy[i];                      
 } 
 else//iy<0
 {
  if (monster_cy[i]>0)
  {
  wall=0;
  wall=(tiledata_block[mapt3[t]]);
  if (monster_cx[i]<levelx)
  if (tx+monster_radius[i]>65535)
  {
  wall=wall | (tiledata_block[mapt3[t+1]]);
  if (monster_status[i]&blockmapstatus[map[t-127]]) wall=1;
  }
  if (monster_cx[i]>0)
  if (tx-monster_radius[i]<0)
  {
  wall=wall | (tiledata_block[mapt3[t-1]]);
  if (monster_status[i]&blockmapstatus[map[t-129]]) wall=1;
  }
  if (monster_status[i]&blockmapstatus[map[t-128]]) wall=1;
  } else wall=1;
  blocked=0;
  if (wall)
  if (ty+monster_iy[i]<monster_radius[i])
  blocked=1;
 if (blocked)
  {monster_y[i]=monster_cy[i]*65536+2+monster_radius[i];monster_iy[i]=-monster_iy[i];}
 else
 monster_y[i]+=monster_iy[i];                      
 }
} 

monster_x[i]+=monster_ix[i];
monster_y[i]+=monster_iy[i];


monster_z[i]+=monster_iz[i];

monster_ix[i]=(monster_ix[i]*3)/4;
monster_iy[i]=(monster_iy[i]*3)/4;

monster_angle[i]=SuperAngle(monster_angle[i]);
                      
if (meshzdisplace[t]|meshzdisplace[t+1]|meshzdisplace[t+128]|meshzdisplace[t+129])
{
floorheight=FloorProbe(monster_x[i],monster_y[i],monster_z[i]);
}
else floorheight=meshz[t];


if (monster_status[i]&STATUS_CRAWLING)
 {

  t=FloorProbe(monster_x[i]+FPMUL(monster_radius[i],f_cos[monster_angle[i]]),
               monster_y[i]+FPMUL(monster_radius[i],f_sin[monster_angle[i]]),
               monster_z[i]
               );
  
  monster_anglez[i]=SuperAngle(arctan(monster_radius[i],t-monster_z[i]));                                     
                                      
  t=FloorProbe(monster_x[i]-FPMUL(monster_radius[i],f_sin[monster_angle[i]]),
               monster_y[i]+FPMUL(monster_radius[i],f_cos[monster_angle[i]]),
               monster_z[i]
               );
  
  monster_anglex[i]=SuperAngle(arctan(monster_radius[i],monster_z[i]-t));                                     

 }


if (monster_z[i]<floorheight) monster_z[i]=floorheight;
//    monster_z[i]+=100;     
         
//
floorheight+=400;//I'm gonna fly hard

monster_z[i]=floorheight;




 }     
}

Sint32 newangle;



Sint8 lastangle;
Uint8 a_keypressed[4];
void procplayercontrol(void)
{
//if (controlpad.button[PAD_SELECT]) 
//{NewGameMode=PLAYER_NAME;}
if ((interface_L<5)&(interface_R<5))
{
if (level_tag==0)
if (movie_mode==0) 
if (controlpad.button[PAD_SELECT]) 
if (Music_Fade_Count>25)
{
Music_Fade_Count==25;                        
}
else
if (Music_Fade_Count<24)
if (monster_hp[0]>0)
{chmenu_count=1; GetPlayerPic(); Music_stack=Next_Music_Track;NextMusicTrack(25);musvolume=Music_Volume;Music_Volume=95;GameMode=CHARACTERMENU;NewGameMode=CHARACTERMENU;sPlaySound(3,128,128);}

if (monster_action[0]<3)
 {
if (ControlMode==0)
{//camera relative-cmode
if (lastangle!=controlpad.angle) cameradelay=0;
if (controlpad.angle>=0)
   {

   newangle=1024-rcamera[4]-controlpad.angle*512;                     
//(800>zabs(calcturn(newangle,monster_angle[0])
while (newangle<0) newangle+=4096;

while (newangle>=4096) newangle-=4096;
    if (cameradelay==0)
    {
     monster_angle[0]=monster_angle[0]+calcturn(monster_angle[0],newangle)/5;
    }
     
monster_angle[0]=SuperAngle(monster_angle[0]);

  if (monster_pause[0]==0)
     monster_walk(0,monster_angle[0],monster_speed[0]);
     //monster_walk(0,newangle,700);
   } else cameradelay=0;    
     

     
lastangle=controlpad.angle;
}//camera relative-cmode
else
{//player relative-cmode
if (controlpad.angle>=0)
   {
    if ((controlpad.angle>=1)&(controlpad.angle<=3))
    {
    monster_walk(0,monster_angle[0],110);
    monster_angle[0]+=-128;
    }
    else
    if ((controlpad.angle>=5)&(controlpad.angle<=7))
    {
 monster_walk(0,monster_angle[0],110);
    monster_angle[0]+=128;
    }
    
monster_angle[0]=SuperAngle(monster_angle[0]);
if (monster_pause[0]==0)
 {
 if ((controlpad.angle==7)|(controlpad.angle<=1))
 monster_walk(0,monster_angle[0],monster_speed[0]);
 else
 if ((controlpad.angle>=3)&(controlpad.angle<=5))
 monster_walk(0,monster_angle[0],-monster_speed[0]);

 }
     
lastangle=controlpad.angle;
}//player relative-cmode

}

if (monster_action[0]<2)
{

if (controlpad.button[PAD_A])
{
if (a_keypressed[0]==0)
 {
 monster_skill(0,t_monster_action[level_tag][0]);
 if (t_monster_action[level_tag][0]>1) a_keypressed[0]=1;
 }
}else a_keypressed[0]=0;

if (controlpad.button[PAD_X])
{
if (a_keypressed[1]==0)
 {
 monster_skill(0,t_monster_action[level_tag][1]);
 if (t_monster_action[level_tag][1]>1) a_keypressed[1]=1;
 }
}else a_keypressed[1]=0;

if (controlpad.button[PAD_B])
{
if (a_keypressed[2]==0)
 {
 monster_skill(0,t_monster_action[level_tag][2]);
 if (t_monster_action[level_tag][2]>1) a_keypressed[2]=1;
 }
}else a_keypressed[2]=0;

if (controlpad.button[PAD_Y])
{
if (a_keypressed[3]==0)
 {
 monster_skill(0,t_monster_action[level_tag][3]);
 if (t_monster_action[level_tag][3]>1) a_keypressed[3]=1;
 }
}else a_keypressed[3]=0;


}
 

}


if ((controlpad.button[PAD_L1] & controlpad.button[PAD_R1]) ==0) 
{if (controlpad.button[PAD_L1]) 
if (interface_L==0)
if (interface_R==0)
{
interface_L=1;
sPlaySound(3,100,0);
}
if (level_tag==0) 
if (controlpad.button[PAD_R1]) 
if (interface_R==0)
if (interface_L==0)
{
interface_R=1;
sPlaySound(3,0,100);

}
}
}
}

void gamestep(void)
{
lmovie_mode=movie_mode;
Music_Volume=60;
movie_mode=0;
if (monster_hp[0]>0)
ProcTriggers();

if (movie_playing<16)
movie_mode=1+movie_type[movie_playing];


gamecontrol();

if (movie_mode) ProcMovie();

if (movie_mode!=1)
{
if (monster_hp[0]) ProcFLOOD();
procRPG();

if (monster_status[0]&STATUS_ALIVE)
{
procplayercontrol();     
}
ProcLoot();
procmonsters();
if (count>15)
if (movie_mode==0) procplayercamera();
}


}
void gameload(void)
{
 Game_LoadNewLevel();
 NewGameMode=GAME;     
}




void gamerender(void)
{
renderscene();     
RenderInterface();
if (messagecount) RenderMessage();
if (dialogcount) RenderDialog();
}

const char *s_mainmenu[6]=
{
"FleshChasmer","Resume Current Game","Restart Level","Options","Restart Game","Quit Game"
};
Uint16 mainmenucol[6];
Uint8 OptMenuPos;
Sint16 mby,mbh,mby1,mbh1,t;

Uint8 SafeSave;
void mainmenu(void)
{
if (mainmenupos==1)
if (monster_hp[0]==0) mainmenupos=2;

Sint16 mmy=0;
Uint8 i;
if (mainmenucount<15) 
{
if (mainmenucount==0)
 {
 mby=120;
 mbh=10;                    
  cscreenborder=60;
//  Music_stack=Music_Track;
SafeSave=1;
if (danger_status>-25) SafeSave=0;
if (monster_hp[0]==0) SafeSave=0;
if (movie_mode) SafeSave=0;

 }        

if (mainmenucount==1)
 {
mmix=0;
mmiy=0;
}
mainmenucount++;mmy=-(16-mainmenucount)*5;
};

mainmenucol[0]=35;
mainmenucol[1]=25;
mainmenucol[2]=24;
mainmenucol[3]=23;
mainmenucol[4]=22;
mainmenucol[5]=21;
if (monster_hp[0]==0) mainmenucol[1]=16;


if (mbh!=mbh1)
mbh=mbh+(mbh1-mbh)/3;

if (mby!=mby1)
mby=mby+((mby1-mby)/3);
//mby=mby & 254;
for (Uint32 i=0;i<76800;i++)
scrbuf[i]=bng[i];    


for (Uint16 i=0;i<100;i++)
{
Uint32 n=3+random(315)+(2+random(mby-mbh))*320;
scrbuf[n+1]=scrbuf[n];    
scrbuf[n-1]=scrbuf[n];    
scrbuf[n-322]=scrbuf[n];    
scrbuf[n+322]=scrbuf[n];    

}

for (Uint16 i=0;i<100;i++)
{
Uint32 n=3+random(315)+(mby+mbh+random(238-mby-mbh))*320;
scrbuf[n+1]=scrbuf[n];    
scrbuf[n-1]=scrbuf[n];    
scrbuf[n-322]=scrbuf[n];    
scrbuf[n+322]=scrbuf[n];    

}


for (Uint16 y=mby-mbh;y<mby+mbh;y+=2)
for (Uint16 x=0;x<320;x+=2)
{
scrbuf[x+y*320]=16;    
scrbuf[x+y*320+321]=16;    
}
t=mby-mbh;
for (Uint16 x=0;x<320;x++)
scrbuf[x+t*320]=16;    
for (Uint16 x=0;x<320;x++)
scrbuf[x+t*320-640]=16;    

t=mby+mbh;
for (Uint16 x=0;x<320;x++)
scrbuf[x+t*320]=16;    

for (Uint16 x=0;x<320;x++)
scrbuf[x+t*320+640]=16;    

//for (i=1;i<6;i++)
//if (mainmenupos==i)
mainmenucol[mainmenupos]=mainmenucol[mainmenupos]+5+count/4%2;
switch (mainmenuspecial)
{
case 0:
Music_Volume=30;                    

     mmix=mmix>>1;
     mmiy=mmiy>>1;
     
 mby1=133;
 mbh1=66;                    
     break;       

case 1://Options
Music_Volume=40;                    

     mmix=mmix-(-90-mmiy)/4;
     mmiy=mmiy-(10-mmiy)/8;
 mby1=120;
 mbh1=90;             
  l_textstring=sprintf(s_textstring,"Options");
  s_drawtext2(211,mby-mbh-24,20);               
  s_drawtext2(210,mby-mbh-23,26);               

  l_textstring=sprintf(s_textstring,"Sound Mode");
  s_drawtext2(21,61+(0-OptMenuPos),16);               
  if (OptMenuPos==0)
  s_drawtext2(20,60,24+count/4%2);
  else               
  s_drawtext2(20,60,20);
  
 switch (SoundMode)
  {
  case 0:l_textstring=sprintf(s_textstring,"Stereo Sound");break;      
  case 1:l_textstring=sprintf(s_textstring,"Reversed Stereo");break;      
  case 2:l_textstring=sprintf(s_textstring,"Monoral Sound");break;      
  }              
  s_drawtext2(141,61,83);               
  s_drawtext2(140,60,85);               

  l_textstring=sprintf(s_textstring,"Control");
  s_drawtext2(21,85+(1-OptMenuPos),16);               
  if (OptMenuPos==1)
  s_drawtext2(20,84,24+count/4%2);
  else               
  s_drawtext2(20,84,20);

 switch (ControlMode)
  {
  case 0:l_textstring=sprintf(s_textstring,"Directional");break;      
  case 1:l_textstring=sprintf(s_textstring,"Positional");break;      
  }              
  s_drawtext2(141,85,83);               
  s_drawtext2(140,84,85);               

     
  l_textstring=sprintf(s_textstring,"Camera");
  s_drawtext2(21,109+(2-OptMenuPos),16);               
  if (OptMenuPos==2)
  s_drawtext2(20,108,24+count/4%2);
  else               
  s_drawtext2(20,108,20);
 switch (CameraMode)
  {
  case 0:l_textstring=sprintf(s_textstring,"Classic");break;      
  case 1:l_textstring=sprintf(s_textstring,"Custom 1");break;      
  case 2:l_textstring=sprintf(s_textstring,"Custom 2");break;      
  }              
  s_drawtext2(141,109,83);               
  s_drawtext2(140,108,85);               



  l_textstring=sprintf(s_textstring,"Monster HP");
  s_drawtext2(21,133+(3-OptMenuPos),16);               
  if (OptMenuPos==3)
  s_drawtext2(20,132,24+count/4%2);
  else               
  s_drawtext2(20,132,20);
 switch (MonsterHpMode)
  {
  case 0:l_textstring=sprintf(s_textstring,"Hidden");break;      
  case 1:l_textstring=sprintf(s_textstring,"Display");break;      
  }              
  s_drawtext2(141,133,83);               
  s_drawtext2(140,132,85);               




  l_textstring=sprintf(s_textstring,"Show Map");
  s_drawtext2(21,157+(4-OptMenuPos),16);               
  if (OptMenuPos==4)
  s_drawtext2(20,156,24+count/4%2);
  else               
  s_drawtext2(20,156,20);
 switch (showmap)
  {
  case 0:l_textstring=sprintf(s_textstring,"Disabled");break;      
  case 1:l_textstring=sprintf(s_textstring,"Enabled");break;      
  }              
  s_drawtext2(141,157,83);               
  s_drawtext2(140,156,85);               


  l_textstring=sprintf(s_textstring,"Return to Main Menu");
  s_drawtext2(91,186+(5-OptMenuPos),16);               
  if (OptMenuPos==5)
  s_drawtext2(90,185,24+count/4%2);
  else               
  s_drawtext2(90,185,22);
     
 break;       
case 2:
if (count/10%2)
{

if (SafeSave)
  l_textstring=sprintf(s_textstring,"Your game progress will be SAVED.");
  else
  l_textstring=sprintf(s_textstring,"Your game progress will be NOT SAVED!");
  s_drawtext(160-l_textstring*5/2,1+15*CradleMode,18);               
  s_drawtext(160-l_textstring*5/2,0+15*CradleMode,31);               
}

Music_Volume=50;                    

 mby1=90;
 mbh1=20;                    

     mmix=mmix+(-90-mmiy)/4;
     mmiy=mmiy+(10-mmiy)/8;
  l_textstring=sprintf(s_textstring,"Do you wish to quit game?");
  s_drawtext2(51,71,18);               
  s_drawtext2(50,70,24);               


  l_textstring=sprintf(s_textstring,"Yes");
  s_drawtext2(176,93,18);               
 if (mmsp==0)
  s_drawtext2(175,92,24+count/4%2);
  else              
  s_drawtext2(175,92,21);

  l_textstring=sprintf(s_textstring,"No");
  s_drawtext2(226,93,18);               
 if (mmsp==01)
  s_drawtext2(225,92,24+count/4%2);
  else               
  s_drawtext2(225,92,21);
     
     break;       
}

if (mainmenucount<15)
  {
//  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[0]);
//  s_drawtext2(61,41+mmy,mainmenucol[0]);               

  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[1]);
  s_drawtext2(61,71-mmy,mainmenucol[1]);               
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[2]);
  s_drawtext2(61,93-mmy,mainmenucol[2]);               
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[3]);
  s_drawtext2(61-mmy,117,mainmenucol[3]);               
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[4]);
  s_drawtext2(61+mmy,141,mainmenucol[4]);               
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[5]);
  s_drawtext2(61,165-mmy,mainmenucol[5]);               
  }
  else
  {
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[0]);
  s_drawtext2(62+mmix,41+mmiy,16);               
  s_drawtext2(60+mmix,41+mmiy,16);               
  s_drawtext2(61+mmix,42+mmiy,16);               
  s_drawtext2(61+mmix,40+mmiy,16);               
  s_drawtext2(61+mmix,41+mmiy,mainmenucol[0]);               

  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[1]);
  s_drawtext2(62+mmix,70+mmiy+(1-mainmenupos),16);               
  s_drawtext2(61+mmix,69+mmiy,mainmenucol[1]);               
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[2]);
  s_drawtext2(62+mmix,94+mmiy+(2-mainmenupos),16);               
  s_drawtext2(61+mmix,93+mmiy,mainmenucol[2]);               
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[3]);
  s_drawtext2(62+mmix,118+mmiy+(3-mainmenupos),16);               
  s_drawtext2(61+mmix,117+mmiy,mainmenucol[3]);               
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[4]);
  s_drawtext2(62+mmix,142+mmiy+(4-mainmenupos),16);               
  s_drawtext2(61+mmix,141+mmiy,mainmenucol[4]);               
  l_textstring=sprintf(s_textstring,"%s",s_mainmenu[5]);
  s_drawtext2(62+mmix,166+mmiy+(5-mainmenupos),16);               
  s_drawtext2(61+mmix,165+mmiy,mainmenucol[5]);               
  }
    

if (mainmenupause) mainmenupause--;
else
 {

if (controlpad.button[PAD_START])
if (mainmenuspecial==0)
if (monster_hp[0])
 {
if (Music_Fade_Count<25)
{  NextMusicTrack(Music_stack);                   
 NewGameMode=GAME;Music_Volume=musvolume;sPlaySound(4,128,128);
}
 }
else
{mainmenucount=1;mainmenupause=5;mainmenuspecial=0;sPlaySound(2,128,128);}
                  
switch (mainmenuspecial)
{
 case 0:
if (count%2)
    switch (controlpad.angle)
      {
             case 0:if (mainmenupos>1){mainmenupos--;sPlaySound(0,96-mainmenupos*4,32);}break;
             case 4:if (mainmenupos<5){mainmenupos++;sPlaySound(0,32,64+mainmenupos*4);}break;
      }
if ((controlpad.button[PAD_A])|(controlpad.button[PAD_B])|(controlpad.button[PAD_X])|(controlpad.button[PAD_Y])|(controlpad.button[PAD_Z])|(controlpad.button[PAD_L1])|(controlpad.button[PAD_R1]))
 switch (mainmenupos)
      {
      case 1:if (Music_Fade_Count<25)
if (monster_hp[0])
{  NextMusicTrack(Music_stack);NewGameMode=GAME;sPlaySound(2,128,128);Music_Volume=musvolume;}
else
if (count%5==0)
{sPlaySound(1,128,128);}
      break;              
      case 2:
      if (Music_Fade_Count<25)
      {
      InitPlayerStatus();
      LoadPlayerStatus();
      count=0;fadecount=10;NewGameMode=LOADING_GAME;
      }
      
      break; 
//      case 3:mainmenupause=5;sPlaySound(1,128,128);break;              
      case 3:mainmenuspecial=1;mainmenupause=5;sPlaySound(2,96,128);break;              
      case 4:
InitPlayerStatus();
SavePlayerStatus();
      count=0;fadecount=10;NewGameMode=LOADING_GAME;

/* 
           mainmenupause=5;sPlaySound(1,128,128);
           fadecount=0;NewGameMode=EDITOR_MENU;//enchance this
           EditorOn=1; 
           NextMusicTrack(50);
*/           
           break;              
      case 5:mainmenuspecial=2;mainmenupause=5;sPlaySound(4,128,128);break;              
      }
 break;     
 case 1://OPTIONS
if (count%2)
    {
    switch (controlpad.angle)
      {
             case 0:if (OptMenuPos>0){OptMenuPos--;sPlaySound(0,96-OptMenuPos*6,32);}break;
             case 4:if (OptMenuPos<5){OptMenuPos++;sPlaySound(0,32,64+OptMenuPos*6);}break;
      }

    switch (controlpad.angle)
      {
             case 2://right arrow
             switch (OptMenuPos)
             {
      case 0:SoundMode=(SoundMode+1)%3;sPlaySound(0,128,128);break;              
      case 1:ControlMode=(ControlMode+1)%2;sPlaySound(0,128,128);break;              
      case 2:CameraMode=(CameraMode+1)%3;sPlaySound(0,128,128);break;              
      case 3:MonsterHpMode=(MonsterHpMode+1)%2;sPlaySound(0,128,128);break;              
      case 4:showmap=(showmap+1)%2;sPlaySound(0,128,128);break;              
             }
                  
             break;
             case 6://left arrow
             switch (OptMenuPos)
             {
      case 0:if (SoundMode) SoundMode--; else SoundMode=2;sPlaySound(0,128,128);break;              
      case 1:ControlMode=(ControlMode+1)%2;sPlaySound(0,128,128);break;              
      case 2:if (CameraMode) CameraMode=(CameraMode-1); else CameraMode=2;sPlaySound(0,128,128);break;              
      case 3:MonsterHpMode=(MonsterHpMode+1)%2;sPlaySound(0,128,128);break;              
      case 4:showmap=(showmap+1)%2;sPlaySound(0,128,128);break;              
             }
                          
             break;
      }

if ((controlpad.button[PAD_A])|(controlpad.button[PAD_B])|(controlpad.button[PAD_X])|(controlpad.button[PAD_Y])|(controlpad.button[PAD_Z])|(controlpad.button[PAD_L1])|(controlpad.button[PAD_R1]))
 switch (OptMenuPos)
      {
      case 0:SoundMode=(SoundMode+1)%3;sPlaySound(0,128,128);break;              

      case 1:ControlMode=(ControlMode+1)%2;sPlaySound(0,128,128);break;              
      case 2:CameraMode=(CameraMode+1)%3;sPlaySound(0,128,128);break;              
      case 3:MonsterHpMode=(MonsterHpMode+1)%2;sPlaySound(0,128,128);break;              
      case 4:showmap=(showmap+1)%2;sPlaySound(0,128,128);break;              

      case 5:mainmenucount=1;mainmenupause=5;mainmenuspecial=0;sPlaySound(2,128,128);break;              
      }
     }
 break;     

case 2:
    switch (controlpad.angle)
      {
             case 2:if (mmsp<1){mmsp=1;sPlaySound(0,0,96);}break;
             case 6:if (mmsp>0){mmsp=0;sPlaySound(0,96,0);}break;
      }
if ((controlpad.button[PAD_A])|(controlpad.button[PAD_B])|(controlpad.button[PAD_X])|(controlpad.button[PAD_Y])|(controlpad.button[PAD_Z])|(controlpad.button[PAD_L1])|(controlpad.button[PAD_R1]))
 switch (mmsp)
      {
      case 0:
if (monster_hp[0]>0)
if (danger_status==-25)
if (movie_mode==0)
SavePlayerStatus();
GameLoopEnabled=0;break;              
      case 1:mainmenucount=1;mainmenupause=5;mainmenuspecial=0;sPlaySound(2,128,128);break;              

      }    
 break;
 }
}
ProcVolControl();
     
}



Uint8 tim[5];
Uint32 x,y;
Sint32 i;
Sint32 x1,y1;
Sint32 exp_loss;
Uint8 item_selected=65;
Uint8 skill_selected=32;
Uint8 n,c,ii,mi;

void CharacterMenu(void)
{//HELP YOURSELF!!!


if (chmenu_count<0)
{
x1=20+(x0-20)*(9+chmenu_count)/10;
y1=20+(y0-20)*(9+chmenu_count)/10;

for (y=0;y<200;y++)
for (x=0;x<100;x++)
scrbuf[x1+x+(y1+y)*320]=pl_pic[x][y];
                  
                   
}
else
if (chmenu_count<10)
{
item_selected=64;

x1=x0+(20-x0)*chmenu_count/10;
y1=y0+(20-y0)*chmenu_count/10;

for (y=0;y<200;y++)
for (x=0;x<100;x++)
scrbuf[x1+x+(y1+y)*320]=pl_pic[x][y];
}
else
{
for (y=0;y<240;y++)
for (x=0;x<320;x++)
{
    i=x+320*y;
scrbuf[i]=chbng[i];    
}
for (y=0;y<200;y++)
for (x=0;x<100;x++)
scrbuf[21+x+(21+y)*320]=pl_pic[x][y];

//GameTime=10;
tim[0]=iGameTime/3600;
tim[1]=iGameTime/600%6;
tim[2]=iGameTime/60%10;
tim[3]=iGameTime/10%6;
tim[4]=iGameTime%10;
l_textstring=sprintf(s_textstring,"Time %i:%i%i:%i%i",tim[0],tim[1],tim[2],tim[3],tim[4]);
s_drawtext(230,206,18);               
s_drawtext(229,205,27);               

l_textstring=sprintf(s_textstring,"Status");
s_drawtext(161,27,18);               
if (chmenu_x==0)
s_drawtext(160,26,27+count/4%2);               
else
s_drawtext(160,26,22);               

l_textstring=sprintf(s_textstring,"Items");
s_drawtext(201,27,18);               
if (chmenu_x==1)
s_drawtext(200,26,27+count/4%2);               
else
s_drawtext(200,26,22);               

l_textstring=sprintf(s_textstring,"Skills");
s_drawtext(236,27,18);               
if (chmenu_x==2)
s_drawtext(235,26,27+count/4%2);               
else
s_drawtext(235,26,22);               

l_textstring=sprintf(s_textstring,"Class");
s_drawtext(276,27,18);               
if (chmenu_x==3)
s_drawtext(275,26,27+count/4%2);               
else
s_drawtext(275,26,22);               
Sint32 vle;

switch (chmenu_x)
{
case 0:
l_textstring=sprintf(s_textstring," Name : %s",t_monster_name[level_tag]);
s_drawtext(161,43,18);               
s_drawtext(160,42,26);               
l_textstring=sprintf(s_textstring,"Lvl %i",ch_level);
s_drawtext(251,43,18);               
s_drawtext(250,42,26);               

l_textstring=sprintf(s_textstring,"Exp");
s_drawtext(251,55,18);               
s_drawtext(250,54,26);
vle=ch_exp;
if (vle>1000000)
l_textstring=sprintf(s_textstring,"%iKK",vle/1000000);
else
if (vle>10000)
l_textstring=sprintf(s_textstring,"%iK",vle/1000);
else
l_textstring=sprintf(s_textstring,"%i",vle);

s_drawtext(301-l_textstring*5,55,18);               
s_drawtext(300-l_textstring*5,54,26);
if (ch_level<99)
{
l_textstring=sprintf(s_textstring,"Next");
s_drawtext(251,67,18);               
s_drawtext(250,66,26);               

vle=exp_lvl[ch_level]-ch_exp;
if (vle>1000000)
l_textstring=sprintf(s_textstring,"%iKK",vle/1000000);
else
if (vle>10000)
l_textstring=sprintf(s_textstring,"%iK",vle/1000);
else
l_textstring=sprintf(s_textstring,"%i",vle);



s_drawtext(301-l_textstring*5,67,18);               
s_drawtext(300-l_textstring*5,66,26);
}
l_textstring=sprintf(s_textstring,"GP");
s_drawtext(251,79,18);               
s_drawtext(250,78,26);               
l_textstring=sprintf(s_textstring,"%i",item_c[63]);
s_drawtext(301-l_textstring*5,79,18);               
s_drawtext(300-l_textstring*5,78,26);


l_textstring=sprintf(s_textstring," HP   : %i/%i",monster_hp[0],monster_mhp[0]);
s_drawtext(161,55,32);               
s_drawtext(160,54,36);               
l_textstring=sprintf(s_textstring," MP   : %i/%i",monster_mn[0],t_monster_mn[monster_type[0]]);
s_drawtext(161,67,82);               
s_drawtext(160,66,86);               
l_textstring=sprintf(s_textstring," MV   : %i/%i",monster_mv[0],t_monster_mv[monster_type[0]]);
s_drawtext(161,79,48);               
s_drawtext(160,78,53);               


l_textstring=sprintf(s_textstring,"STR %i",t_monster_str[level_tag]);
s_drawtext(161,103,18);               
s_drawtext(160,102,26);               

l_textstring=sprintf(s_textstring,"DEX %i",t_monster_dex[level_tag]);
s_drawtext(201,103,18);               
s_drawtext(200,102,26);               
     
l_textstring=sprintf(s_textstring,"CON %i",t_monster_con[level_tag]);
s_drawtext(241,103,18);               
s_drawtext(240,102,26);               
     
l_textstring=sprintf(s_textstring,"INT %i",t_monster_int[level_tag]);
s_drawtext(161,115,18);               
s_drawtext(160,114,26);               

l_textstring=sprintf(s_textstring,"WIS %i",t_monster_wis[level_tag]);
s_drawtext(201,115,18);               
s_drawtext(200,114,26);               
     
l_textstring=sprintf(s_textstring,"CHA %i",t_monster_cha[level_tag]);
s_drawtext(241,115,18);               
s_drawtext(240,114,26);               

l_textstring=sprintf(s_textstring,"AC:%i",t_monster_armor[level_tag]);
s_drawtext(161,91,16);               
s_drawtext(160,90,25);               

l_textstring=sprintf(s_textstring,"SR:%i",t_monster_resist[level_tag]);
s_drawtext(201,91,16);               
s_drawtext(200,90,25);               

l_textstring=sprintf(s_textstring,"MDmg:%i-%i",t_monster_mdamage[level_tag][0],t_monster_mdamage[level_tag][0]+t_monster_mdamage[level_tag][1]);
s_drawtext(231,91,16);               
s_drawtext(230,90,25);               


if (player_arm[0]==0)
l_textstring=sprintf(s_textstring,"Spiked glove (%i-%i)",t_monster_damage[0][0],t_monster_damage[0][0]+t_monster_damage[0][1]);
else
l_textstring=sprintf(s_textstring,"%s (%i-%i)",item_s[player_arm[0]*2],t_monster_damage[0][0],t_monster_damage[0][0]+t_monster_damage[0][1]);
s_drawtext(156,148,16);               
s_drawtext(155,147,27);               

if (player_arm[1]==0)
l_textstring=sprintf(s_textstring,"Missle weapon slot empty");
else
l_textstring=sprintf(s_textstring,"%s (%i-%i)",item_s[player_arm[1]*2],t_monster_shootdamage[0][0],t_monster_shootdamage[0][0]+t_monster_shootdamage[0][1]);
s_drawtext(156,160,16);               
s_drawtext(155,159,27);               
if (player_arm[2]==0)
l_textstring=sprintf(s_textstring,"Amulet Slot empty");
else
l_textstring=sprintf(s_textstring,"%s",item_s[player_arm[2]*2]);
s_drawtext(156,172,16);               
s_drawtext(155,171,27);               

//if (count==5)
// GameTime=0;
     
     
break;      
case 1:
for (i=0;i<7;i++)
{
 {
if (chmenu_y[1]<3) ii=0;
else
if (chmenu_y[1]<60) ii=chmenu_y[1]-3;
else
ii=57;

n=item_p[ii+i];

if (i==-ii+chmenu_y[1]) 
{
Uint16 k;
 for (y=42+i*12;y<54+i*12;y+=2)
 for (k=155;k<304;k+=2)
 {
 scrbuf[k+y*320]=16;    
 scrbuf[k+y*320+321]=16;     
 }
}

if (n<64)
if (item_c[n])
{



if (n==item_p[chmenu_y[1]]) c=29;else c=22;
mi=0;
if (item_selected<64)
if (n==item_p[item_selected]) mi=5;

if (((n==player_arm[0])|(n==player_arm[1])|(n==player_arm[2]))&(n>0))
l_textstring=sprintf(s_textstring,"+%s",item_s[n*2]);
else
l_textstring=sprintf(s_textstring,"%s",item_s[n*2]);

s_drawtext(160+mi,43+i*12,18);               
s_drawtext(159+mi,42+i*12,c);               


l_textstring=sprintf(s_textstring,"%i",item_c[n]);
s_drawtext(301-5*l_textstring,43+i*12,18);               
s_drawtext(300-5*l_textstring,42+i*12,c);               

if ((n>=32)&(n<44))
  {
l_textstring=sprintf(s_textstring,"%i%c",weapon_points[n-32]/10,37);
s_drawtext(281-5*l_textstring,43+i*12,18);               
s_drawtext(280-5*l_textstring,42+i*12,c);               

              
  }

 }
 }
}
n=item_p[chmenu_y[1]];
if (n<64)
if (item_c[n])
{

for (x=0;x<16;x++)
for (y=0;y<16;y++)
{
Uint8 c=Tile[(160+n)*256+x+y*16];
Uint32 z;
z=154+x*2+(148+y*2)*320;
if (c)
 {
 scrbuf[z]=c;
 scrbuf[z+1]=c;
 scrbuf[z+321]=c;
 scrbuf[z+320]=c;
 }
else
 {
 scrbuf[z]=16;
 scrbuf[z+321]=16;
 }
}
if (chmenu_y[1]==0)
{
l_textstring=sprintf(s_textstring,"Quick Item");
s_drawtext(230,139,16);               
s_drawtext(231,138,90);               
                   
}
l_textstring=sprintf(s_textstring,"%s",item_s[n*2]);
s_drawtext(180,148,18);               
s_drawtext(181,147,26);               

l_textstring=sprintf(s_textstring,"%s",item_s[n*2+1]);
s_drawtext(180,160,18);               
s_drawtext(181,159,26);               
if (item_c[n]>1)
{

l_textstring=sprintf(s_textstring,"Amount: %i",item_c[n]);
s_drawtext(180,172,18);               
s_drawtext(181,171,26);               
}
}       
break;      
case 2:
for (i=0;i<7;i++)
{
 {
if (chmenu_y[2]<3) ii=0;
else
if (chmenu_y[2]<28) ii=chmenu_y[2]-3;
else
ii=25;
Uint16 k;
n=skill_p[ii+i];
if (i==-ii+chmenu_y[2]) 
 for (y=42+i*12;y<54+i*12;y+=2)
 for (k=155;k<304;k+=2)
 {
 scrbuf[k+y*320]=16;    
 scrbuf[k+y*320+321]=16;     
 }
 
if (n<32)
if (skill_l[n])
  {
if (n==skill_p[chmenu_y[2]]) c=29;else c=22;
mi=0;
if (skill_selected<32)
if (n==skill_p[skill_selected]) mi=5;
l_textstring=sprintf(s_textstring,"%s",skill_s[n*2]);
s_drawtext(160+mi,43+i*12,18);               
s_drawtext(159+mi,42+i*12,c);               
Uint8 m0t=monster_type[0];
if (n==t_monster_action[m0t][0])
   {
l_textstring=sprintf(s_textstring,"A");
s_drawtext(273,43+i*12,18);               
s_drawtext(274,42+i*12,90+count/2%4);               
   }
if (n==t_monster_action[m0t][1])
   {
l_textstring=sprintf(s_textstring,"X");
s_drawtext(282,43+i*12,18);               
s_drawtext(281,42+i*12,90+(count/2+1)%4);               
   }
if (n==t_monster_action[m0t][2])
   {
l_textstring=sprintf(s_textstring,"B");
s_drawtext(288,43+i*12,18);               
s_drawtext(287,42+i*12,90+(count/2+2)%4);               
   }
if (n==t_monster_action[m0t][3])
   {
l_textstring=sprintf(s_textstring,"Y");
s_drawtext(294,43+i*12,18);               
s_drawtext(293,42+i*12,90+(count/2+3)%4);               
   }
   
   
  }

 }
}

n=skill_p[chmenu_y[2]];
if (n<32)
if (skill_l[n])
{
l_textstring=sprintf(s_textstring,"%s",skill_s[n*2+1]);
s_drawtext(161,154,18);               
s_drawtext(160,153,26);               
l_textstring=sprintf(s_textstring,"%s",skill_s0[n]);
s_drawtext(300-l_textstring*5,166,18);               
s_drawtext(301-l_textstring*5,165,26);               

}       
break;      
case 3:
exp_loss=0;
if (chmenu_y[3]!=ch_class)
{
if (ch_level>0)
{
exp_loss=ch_exp-exp_lvl[ch_level-1];
}
else
exp_loss=ch_exp;

if (exp_loss>0 & ch_level<99)
{
l_textstring=sprintf(s_textstring,"Warning: you will");
s_drawtext(161,102,32);               
s_drawtext(160,101,36);               
l_textstring=sprintf(s_textstring,"         lose %i Exp!",exp_loss);
s_drawtext(161,114,32);               
s_drawtext(160,113,36);               
}                          
                          
}
l_textstring=sprintf(s_textstring,"%s",class_s[lvlclass[0]/10]);
s_drawtext(171,44,18);               
if (chmenu_y[3]==0)
s_drawtext(170,43,26);
else
s_drawtext(170,43,22);

l_textstring=sprintf(s_textstring,"%s",class_s[lvlclass[1]/10+10]);
s_drawtext(171,56,18);               
if (chmenu_y[3]==1)
s_drawtext(170,55,26);
else
s_drawtext(170,55,22);

l_textstring=sprintf(s_textstring,"%s",class_s[lvlclass[2]/10+20]);
s_drawtext(171,68,18);               
if (chmenu_y[3]==2)
s_drawtext(170,67,26);
else
s_drawtext(170,67,22);

l_textstring=sprintf(s_textstring,"%s",class_s[lvlclass[3]/10+30]);
s_drawtext(171,80,18);               
if (chmenu_y[3]==3)
s_drawtext(170,79,26);
else
s_drawtext(170,79,22);

l_textstring=sprintf(s_textstring,"Lvl %i",lvlclass[0]);
s_drawtext(236,44,18);               
s_drawtext(235,43,25);               

l_textstring=sprintf(s_textstring,"Lvl %i",lvlclass[1]);
s_drawtext(236,56,18);               
s_drawtext(235,55,25);               

l_textstring=sprintf(s_textstring,"Lvl %i",lvlclass[2]);
s_drawtext(236,68,18);               
s_drawtext(235,67,25);               

l_textstring=sprintf(s_textstring,"Lvl %i",lvlclass[3]);
s_drawtext(236,80,18);               
s_drawtext(235,79,25);               

l_textstring=sprintf(s_textstring,"*");
s_drawtext(165,44+ch_class*12,18);               
s_drawtext(164,43+ch_class*12,29);               


switch (chmenu_y[3])
{
case 0:l_textstring=sprintf(s_textstring,"Powerful and strong");break;
case 1:l_textstring=sprintf(s_textstring,"Fast and deadly");break;
case 2:l_textstring=sprintf(s_textstring,"Great attack magic");break;
case 3:l_textstring=sprintf(s_textstring,"Perfect support magic");break;
}
s_drawtext(160,154,18);               
s_drawtext(161,153,26);               


break;      
       
}


if (count%2)
{
if ((controlpad.button[PAD_L1])|(controlpad.angle==6))
if (chmenu_x>0){chmenu_x--;sPlaySound(0,96,96);}
if ((controlpad.button[PAD_R1])|(controlpad.angle==2))
if (chmenu_x<3){chmenu_x++;sPlaySound(0,96,96);}

      
    switch (chmenu_x)
     {
     case 1:
    switch (controlpad.angle)
      {
             case 0:if (chmenu_y[1]>0){chmenu_y[1]--;sPlaySound(0,96,96);}break;
             case 4:if (chmenu_y[1]<63){chmenu_y[1]++;sPlaySound(0,96,96);}break;
      }
                
if ((controlpad.button[PAD_A])|(controlpad.button[PAD_B])|(controlpad.button[PAD_X])|(controlpad.button[PAD_Y])|(controlpad.button[PAD_Z]))
   {
   if (item_selected==64)
    {
    if (item_p[chmenu_y[1]]<64)
    if (item_c[item_p[chmenu_y[1]]])
    {
     sPlaySound(0,128,128);
     item_selected=chmenu_y[1];
    }
    }
    else
    {
    
     if (item_p[item_selected]==item_p[chmenu_y[1]])
     {
     if (item_p[item_selected]<64)
     UseItem(item_p[item_selected]);
     }
     else
     {
     sPlaySound(2,96,96);
    Uint8 t=item_p[item_selected];
    item_p[item_selected]=item_p[chmenu_y[1]];
    item_p[chmenu_y[1]]=t;
     }
     item_selected=64;   
    }                                                                                                                                                                                                  
   }
    break;
     case 2:
    switch (controlpad.angle)
      {
             case 0:if (chmenu_y[2]>0){chmenu_y[2]--;sPlaySound(0,96,96);}break;
             case 4:if (chmenu_y[2]<31){chmenu_y[2]++;sPlaySound(0,96,96);}break;
      }
                
if ((controlpad.button[PAD_A])|(controlpad.button[PAD_B])|(controlpad.button[PAD_X])|(controlpad.button[PAD_Y])|(controlpad.button[PAD_Z]))
   {
//   if ()
   if (skill_selected==32)
    {
                          
    if (skill_l[skill_p[chmenu_y[2]]])
if (skill_p[chmenu_y[2]]<32)
    {
     sPlaySound(0,128,128);
     skill_selected=chmenu_y[2];
    }
    }
    else
    {
     if (skill_p[skill_selected]==skill_p[chmenu_y[2]])
     {
     if (skill_l[skill_p[skill_selected]])
      {
      if ((controlpad.button[PAD_A]))
       t_monster_action[monster_type[0]][0]=skill_p[skill_selected];
      if ((controlpad.button[PAD_X]))
       t_monster_action[monster_type[0]][1]=skill_p[skill_selected];
      if ((controlpad.button[PAD_B]))
       t_monster_action[monster_type[0]][2]=skill_p[skill_selected];
      if ((controlpad.button[PAD_Y]))
       t_monster_action[monster_type[0]][3]=skill_p[skill_selected];
      }
     }
     else
     {
     sPlaySound(2,96,96);
    Uint8 t=skill_p[skill_selected];
    skill_p[skill_selected]=skill_p[chmenu_y[2]];
    skill_p[chmenu_y[2]]=t;
     }
     skill_selected=32;   
    }                                                                                                                                                                                                  
   }
    break;
     case 3:
    switch (controlpad.angle)
      {
             case 0:if (chmenu_y[3]>0){chmenu_y[3]--;sPlaySound(0,96,96);}break;
             case 4:if (chmenu_y[3]<3){chmenu_y[3]++;sPlaySound(0,96,96);}break;
      }
                
if ((controlpad.button[PAD_A])|(controlpad.button[PAD_B])|(controlpad.button[PAD_X])|(controlpad.button[PAD_Y])|(controlpad.button[PAD_Z]))

 {

if (ch_class!=chmenu_y[3])
{
exp_loss=0;
if (ch_level)
{
exp_loss=ch_exp-exp_lvl[ch_level-1];
}
else
exp_loss=ch_exp;

ch_exp-=exp_loss;
sPlaySound(3,128,128);
ch_class=chmenu_y[3];
}
//AddLevel();                                                                                                                                                                                  
 }


     break; 
     }

{}
}


if ((controlpad.button[PAD_START])|(controlpad.button[PAD_SELECT]))
if (Music_Fade_Count<25)
 {
 chmenu_count=-10;
 }
}
if (chmenu_x!=1)
 item_selected=64;
 else
if (chmenu_x!=2)
 skill_selected=32;
else
if (chmenu_x!=3)
chmenu_y[3]=ch_class;

chmenu_count++;

if (chmenu_count==0)
 {
 NextMusicTrack(Music_stack);                   
 NewGameMode=GAME;Music_Volume=musvolume;sPlaySound(4,128,128);
 GameMode=GAME; 
 }
ProcVolControl();
}
