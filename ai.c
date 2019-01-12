#include "ai.h"
#include "globalvar.h"
#include "zmath.h"
#include "monsters.h"
#include "skills.h"
#define FPMUL(x,y)	((((x)>>5)*((y)>>7))>>4)


Uint8 ai_wall[4];
void ai_scanwalls(Uint8 i)
{
Uint8 k;
     
Uint32 t=monster_cx[i]+monster_cy[i]*128+monster_cz[i]*16384;
     
for (k=0;k<4;k++)
 ai_wall[k]=0;


if (monster_cx[i]==0)
ai_wall[3]=1;
else
 if ((tiledata_block[mapt1[t]])|(monster_status[i]&blockmapstatus[map[t-1]])) ai_wall[3]=1;

if (monster_cx[i]==levelx)
ai_wall[1]=1;
else
 if ((tiledata_block[mapt2[t]])|(monster_status[i]&blockmapstatus[map[t+1]])) ai_wall[1]=1;
     
if (monster_cy[i]==0)
ai_wall[2]=1;
else
 if ((tiledata_block[mapt3[t]])|(monster_status[i]&blockmapstatus[map[t-128]])) ai_wall[2]=1;

if (monster_cy[i]==levely)
ai_wall[0]=1;
else
 if ((tiledata_block[mapt4[t]])|(monster_status[i]&blockmapstatus[map[t+128]])) ai_wall[0]=1;
}

void monster_step(Uint8 i,Sint32 angle,Sint32 speed)
{
monster_ix[i]+=FPMUL(speed,f_cos[angle]);                       
monster_iy[i]+=FPMUL(speed,f_sin[angle]);                       
}


void AI_gettarget(unsigned short i)
{
Uint32 mrange=t_monster_targetrange[monster_type[i]];

monster_ai_target[i]=16;
if (monster_confuzed[i]==0)
for (Uint8 n=0;n<16;n++)
 if (n!=i)
 if (monster_ingame[n])
 if (monster_side[i]!=monster_side[n])
 if (monster_status[n]& STATUS_ALIVE)
 if (table_vis[i][n])
 if (table_range[i][n]<mrange)
 if (monster_invisible[n]==0)
 {
 mrange=table_range[i][n];
 monster_ai_target[i]=n;
 }     
}
void AI_getplayertarget(void)
{
Uint32 mrange=t_monster_targetrange[level_tag];

monster_ai_target[0]=16;

if (monster_confuzed[0]==0)
for (Uint8 n=1;n<16;n++)
 if (monster_ingame[n])
 if (monster_side[0]!=monster_side[n])
 if (monster_status[n]& STATUS_ALIVE)
 if (table_vis[0][n])
 if (table_range[0][n]<mrange)
 if (monster_invisible[n]==0)
 if (zabs(calcturn(table_angle[0][n],monster_angle[0]))<1024)

 {
 mrange=table_range[0][n];
 monster_ai_target[0]=n;
 }     
}

void AI_proc(unsigned short i)
{
Uint8 k,n,l,a;     

if (monster_pause[i]==0)
if (monster_ai_delay[i])
  {
  monster_ai_delay[i]--;

  
  switch (monster_ai_action[i])
   {
  case 0://IDLE_AI
  monster_angle[i]=monster_angle[i]+calcturn(monster_angle[i],monster_ai_angle[i])/5;
  break;//_IDLE_AI

  case 1://RandomStep_AI
  monster_step(i,monster_angle[i],monster_speed[i]);                      
  monster_angle[i]=monster_angle[i]+calcturn(monster_angle[i],monster_ai_angle[i])/5;
  break;//_RandomStep_AI

  case 2://RandomStep_AI
  monster_step(i,monster_angle[i],monster_speed[i]);                      
  monster_angle[i]=monster_angle[i]+calcturn(monster_angle[i],monster_ai_angle[i])/5;
  break;//_RandomStep_AI

  case 3://TargetStep_AI
  monster_step(i,monster_angle[i],monster_speed[i]);                      
  monster_angle[i]=monster_angle[i]+calcturn(monster_angle[i],monster_ai_angle[i])/5;
  break;//_TargetStep_AI

  case 4://RetreatStep_AI
  monster_step(i,monster_ai_angle[i],monster_speed[i]);                      
  monster_angle[i]=monster_angle[i]+calcturn(monster_angle[i],monster_ai_angle[i])/5;
  break;//_RetreatStep_AI

  case 8://MAP_AI
  monster_step(i,monster_angle[i],monster_speed[i]);                      
  monster_angle[i]=monster_angle[i]+calcturn(monster_angle[i],monster_ai_angle[i])/5;
  break;//_MAP_AI
   }
  }
  else
  {//////////////////////////////////////////////
      
      //iteration AI??
   Uint8 lasthero=monster_ai_target[i];
   AI_gettarget(i);
   if (monster_ai_target[i]<16)
     {
      Uint8 targ=monster_ai_target[i];
      //no attack at all
      monster_ai_state[i]=1;                   

      if (table_range[i][targ]<monster_radius[i]+monster_radius[targ]+t_monster_meleerange[monster_type[i]])
      {
      monster_ai_state[i]=3;
      }
//      else
      if (monster_hp[i]<monster_mhp[i]>>2)
      monster_ai_state[i]=4;      
     
     }   
      else
      {
      if ((lasthero<16)|(monster_ai_state[i]))    
      monster_ai_state[i]=2;
      else  
      monster_ai_state[i]=0;
      }


   //AI MINE    
    monster_ai_delay[i]=16+random(8);


    Uint8 ai_dice,ai_score;
    ai_dice=0;
    Uint8 k;
    k=monster_type[i];
    for (n=0;n<8;n++)
    ai_dice+=t_monster_ai[k][monster_ai_state[i]][n];

    monster_ai_action[i]=0;


    if (ai_dice)
     {
     ai_score=random(ai_dice);
     while (ai_score>=t_monster_ai[k][monster_ai_state[i]][monster_ai_action[i]])
       {
       ai_score-=t_monster_ai[k][monster_ai_state[i]][monster_ai_action[i]];
       monster_ai_action[i]++;
       }
     }
    if (mapai[monster_roomi[i]])
    {
     Uint8 ai_i=(mapai[monster_roomi[i]]-1)/4;
     switch (ai_i)
     {
     case 0:if (monster_ai_state[i]==0 | monster_ai_state[i]==2)monster_ai_action[i]=8;break;     
     case 1:if (monster_hp[i]==monster_mhp[i]|monster_ai_state[i]==0 | monster_ai_state[i]==2)monster_ai_action[i]=8;break;     
     case 2:monster_ai_action[i]=8;break;
     }
    }
  switch (monster_ai_action[i])
   {
  case 8://AI map
  monster_step(i,monster_angle[i],monster_speed[i]);                      
  monster_ai_angle[i]=SuperAngle(1024*((mapai[monster_roomi[i]]-1)%4)+128-random(256));
  break;//AI map

  case 0://Idle
if (monster_ai_state[i]==2) 
  {
  monster_step(i,monster_angle[i],monster_speed[i]);                      
  monster_ai_angle[i]=SuperAngle(monster_angle[i]+1024+random(2048));
  }
  
  
  break;       
  case 1://RandomStep_AI


    ai_scanwalls(i);
    n=0;
//    if (monster_ai_camefrom[i]>=0) ai_wall[monster_ai_camefrom[i]]=1;
    

    for (k=0;k<4;k++)
    if (ai_wall[k]==0) n++;
    if (n==0) 
    {
    monster_ai_angle[i]=random(4096);
    }
    else
    {
    l=random(n);
    n=0;a=0;
    for (k=0;k<4;k++) 
    if (ai_wall[k]==0) {if (n==l) a=k;;n++;};


//  monster_ai_camefrom[i]=-1;
      monster_ai_angle[i]=SuperAngle(1024-a*1024-200+random(401)); 
    }
//  */
  break;//_RandomStep_AI
  case 2://HuntPlayer
//  if (monster_cz[i]!=monster_cz[0])
//      monster_ai_angle[i]=random(4096);
//  else
   { 
   Sint8 x,y;
   x=monster_cx[i]-monster_cx[0];
   y=monster_cy[i]-monster_cy[0];
    if ((zabs(x)<5)&(zabs(y)<5))
     {
     x=x+4;                           
     y=y+4;
       Uint8 r=player_proxy[x][y];
     if (r>0)
     if (r<10)
      {
       Uint8 a[4],c,w,n;
       a[0]=0;
       a[1]=0;
       a[2]=0;
       a[3]=0;
       if (x>0) if (player_proxy[x-1][y]<r) a[3]=1;
       if (y>0) if (player_proxy[x][y-1]<r) a[2]=1;
       if (x<8) if (player_proxy[x+1][y]<r) a[1]=1;
       if (y<8) if (player_proxy[x][y+1]<r) a[0]=1;
  //      debugval1=a[3]*1000+a[2]*100+a[1]*10+a[0];
       c=1+random(2);w=0;
       while (c)
        {
        if (a[w]) {c--;}
        if (c)
        {
        w++;
        if (w==4) w=0;
        }
        }
        monster_ai_delay[i]=10;
  monster_ai_angle[i]=SuperAngle(1024-w*1024-400+random(800));
//        debugval0=w;
       
                               
      }
     }
    
   }
  break;//_HuntPlayer_AI
  case 3://StepTotarget
  
  if ((monster_cz[i]==monster_cz[0])&(table_range[i][0]>50000))
  monster_ai_angle[i]=SuperAngle(table_angle[i][0]-512+random(1024));
  else
  monster_ai_angle[i]=4096;     
       
       
  break;//_StepToTarget_AI
  case 4://Retreat
  if (monster_ai_target[i]<16)
  monster_ai_angle[i]=SuperAngle(2048+table_angle[i][monster_ai_target[i]]-512+random(1024));     
       
       
       
  break;//_Retreat_AI
  case 5://action0<<<<<<<<<<<<<<<<<<<<<   <<<<<<<<<<<<<<<<<<
  monster_ai_delay[i]=1;
  monster_skill(i,t_monster_action[k][0]);
  break;//action0
  case 6://action0<<<<<<<<<<<<<<<<<<<<<   <<<<<<<<<<<<<<<<<<
  monster_ai_delay[i]=1;
  monster_skill(i,t_monster_action[k][1]);
  break;//action0
  case 7://action0<<<<<<<<<<<<<<<<<<<<<   <<<<<<<<<<<<<<<<<<
  monster_ai_delay[i]=1;
  monster_skill(i,t_monster_action[k][2]);
  break;//action0

   }
      
      
   //AI MINE
  }
monster_angle[i]=SuperAngle(monster_angle[i]);     
}
