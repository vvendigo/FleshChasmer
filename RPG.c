#include <RPG.h>
#include <globalvar.h>
#include <player.h>
#include <items.h>
#include <triggers.h>
#include <fields.h>
#include <sound.h>
#include <zmath.h>
#include <monsters.h>
void drain_MV(Uint8 i,Uint16 mv)
{
if (monster_mv[i]>mv) monster_mv[i]-=mv;
else monster_mv[i]=0;
}

void monster_healmv(Uint8 i,Uint16 healmv)
{
monster_mv[i]+=healmv;     
if (monster_mv[i]>t_monster_mv[monster_type[i]])
monster_mv[i]=t_monster_mv[monster_type[i]];
if (monster_action[i]==3) {monster_pause[i]=1;}
}

void monster_heal(Uint8 i,Uint16 heal,Uint8 owner)
{
Sint16 hl;
if (monster_hp[i]+heal<=monster_mhp[i]) hl=heal;
else
hl=(monster_mhp[i]-monster_hp[i]);

if (hl)
 {
 monster_healed[i]=9;
if (owner==0) GiveExp(hl/20);
 monster_hp[i]+=hl;
if (GameMode==GAME)
{
indicator_x[indicator_i]=monster_x[i];
indicator_y[indicator_i]=monster_y[i];
indicator_z[indicator_i]=monster_z[i]+20000;
indicator_arg[indicator_i]=hl;
indicator_count[indicator_i]=1;
indicator_i=(indicator_i+1)%4;
}      
       
       
 }
     
}

void monster_healmp(Uint8 i,Uint16 healmp)
{
Sint16 hl;
if (monster_mn[i]+healmp<=t_monster_mn[monster_type[i]]) hl=healmp;
else
hl=(t_monster_mn[monster_type[i]]-monster_mn[i]);

if (hl)
 {
if (i==0) GiveExp(hl/20);
 monster_mn[i]+=hl;
if (GameMode==GAME)
{
indicator_x[indicator_i]=monster_x[i];
indicator_y[indicator_i]=monster_y[i];
indicator_z[indicator_i]=monster_z[i]+10000;
indicator_arg[indicator_i]=-10000-hl;
indicator_count[indicator_i]=1;
indicator_i=(indicator_i+1)%4;
}      
       
       
 }
     
}

void monster_hurt(Uint8 i,Uint16 pdam0,Uint16 mdam0,Uint8 owner)
{
Uint8 type;
Uint16 pd;
Sint32 pdam,mdam;
pdam=pdam0;
mdam=mdam0;
if (owner<16)
{
if (monster_magicarmor[i]) pdam=pdam/2;
if (monster_shielded[i]) mdam=mdam/2;
}
if (monster_ingame[i])
if (monster_hp[i])
{
Sint16 dam;
type=monster_type[i];

if (i==0) pd=pdam;
else
if ((random(20)==0)& pdam<500)
pd=pdam*2;
else
pd=pdam;

if (i==0)
if (skill_l[29])
if (random(10)==0) pd=0;

dam=pd*(100-t_monster_armor[type])/100;
if (mdam<20) dam+=mdam;
else
{
Sint16 d2=mdam*(100-t_monster_resist[type])/100;
if (d2<20) dam+=20; else dam+=d2;
}

if (owner<16)
if (monster_blessed[owner]) dam=dam*12/10;

if (random(100)>35)
if ((dam>t_monster_con[type]|monster_mv[i]<t_monster_mv0[type]) & monster_blessed[i]==0)
{
monster_newpain(i);
monster_pause[i]=2+random(10);
if (monster_mv[i]<t_monster_mv0[type])
monster_pause[i]=monster_pause[i]*2;
if (monster_pause[i]>16) monster_pause[i]=16;

monster_ix[i]=monster_ix[i]/2;
monster_iy[i]=monster_iy[i]/2;
monster_action[i]=3;    
}

drain_MV(i,pdam/2);

if (dam>monster_hp[i]) dam=monster_hp[i];

monster_hp[i]-=dam;


Uint8 s;

if (monster_hp[i]>0)
{
if (pdam>0)
{
s=t_monster_painsound[type];
if (s)
sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],s,406660+random(65534));
}
                
}
else
{
s=t_monster_deathsound[type];
if (s)
sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],s,606660+random(65534));


if (monster_deathtrigger[i]) trig_status[monster_deathtrigger[i]]=1;

monster_status[i]=monster_status[i] & (!STATUS_ALIVE);
monster_status[i]=monster_status[i] & (!STATUS_AI);

monster_hasted[i]=0;
if (table_vis[0][i])
GenerateDrop(i);

if (owner==0) GiveExp(t_monster_cha[type]+t_monster_cha[level_tag]);
if (i==0) {NextMusicTrack(22); Music_Fade_Count=25;}
switch (t_monster_deathtype[monster_type[i]])
{//dead
case 0:monster_kill(i);break;
case 1:
monster_frame0[i]=t_monster_deathframe[monster_type[i]];
monster_frame1[i]=monster_frame0[i];
monster_anim[i]=t_monster_deathspeed[monster_type[i]];
monster_animcount[i]=0;

monster_action[i]=4;
monster_pause[i]=255; 
monster_actioncount[i]=0;
break;
case 2:
monster_frame0[i]=t_monster_painframe0[type];
monster_action[i]=4;
monster_pause[i]=255; 
monster_actioncount[i]=0;
break;
case 3:
monster_frame0[i]=t_monster_painframe0[type];
monster_action[i]=4;
monster_pause[i]=255; 
monster_actioncount[i]=0;
break;
case 4:
monster_frame0[i]=t_monster_painframe0[type];
monster_animcount[i]=0;
monster_frame1[i]=t_monster_painframe0[type];
monster_action[i]=4;
monster_pause[i]=255; 
monster_actioncount[i]=0;
break;
case 5:
monster_frame0[i]=t_monster_painframe0[type];
monster_animcount[i]=0;
monster_frame1[i]=t_monster_painframe0[type];
monster_action[i]=4;
monster_pause[i]=255; 
monster_actioncount[i]=0;
break;

}
}//dead.
if (monster_status[0]&STATUS_ALIVE)
if (i==0 | i==monster_ai_target[0])
{
indicator_x[indicator_i]=monster_x[i]-5000+random(10000);
indicator_y[indicator_i]=monster_y[i]-5000+random(10000);
indicator_z[indicator_i]=monster_z[i]+t_monster_height[type];
indicator_arg[indicator_i]=-dam;
indicator_count[indicator_i]=1;
indicator_i=(indicator_i+1)%4;
}
if (dam>0)
{
monster_modelcolor[i]=38;
switch( t_monster_damageeffect[type])
{
case 0:
 {
field0_x=monster_x[i]-4000+random(8000);       
field0_y=monster_y[i]-4000+random(8000);        
field0_z=t_monster_height[monster_type[i]]+monster_z[i]+random(4000);        

field0_ix=-1400+random(2800);        
field0_iy=-1400+random(2800);        
field0_iz=-1400+random(2800);


field0_w=7000+random(5000);
field0_iw=random(2000);
field0_index=248;        
SpawnField();        
 }
break;
}
} 
     
if (owner==0)
 if (dam>0)
 {
 GiveExp(dam);
 }
} 
}




/// PROC FUNCtion!!
void procRPG(void)
{

  Uint8 t;                                   
//PLAYER Related
if (level_tag==0)
if (monster_hp[0])
{
switch (player_arm[2])
 {
 case 47:
 monster_ill[0]=0;
 monster_hasted[0]=0;
 monster_poisoned[0]=0;
 monster_slowed[0]=0;
 monster_confuzed[0]=0;
 monster_magicarmor[0]=0;
 monster_shielded[0]=0;
 monster_blessed[0]=0;
 break;
 case 55:
 monster_healmv(0,5);
 break;      
 case 56:
 if (count%56==0) monster_heal(0,80+random(41),16);
 break;      
       
 }
}

if (handpistol) handpistol--;
if (handsword) handsword--;
// EEEEEEEEEFFFFFFFEECTT RPG!
for (Uint8 i=0;i<16;i++)
if (monster_ingame[i])    
{
monster_modelcolor[i]=0;
if (monster_status[i]&STATUS_ALIVE)
 {
  t=monster_type[i];                          

  if (monster_mv[i]<t_monster_mv0[t])
   {
    monster_speed[i]=t_monster_speed0[t];          
                                
   }
   else
  if (monster_mv[i]<t_monster_mv1[t])
   {
monster_speed[i]=t_monster_speed1[t];                                
                                
   }
   else
   {// Normal HP/MP regeneration
monster_speed[i]=t_monster_speed[t];       

   if (monster_ill[i]==0)
   {
   if (t_monster_regen[t][0])
   if (count%t_monster_regen[t][0]==0)
   {
   monster_hp[i]+=t_monster_regen[t][1];

   if (monster_hp[i]>monster_mhp[i])
   monster_hp[i]=monster_mhp[i];  
   }
   if (t_monster_regen[t][2])
   if (count%t_monster_regen[t][2]==0)
   {
   monster_mn[i]+=t_monster_regen[t][3];

   if (monster_mn[i]>t_monster_mn[t])
   monster_mn[i]=t_monster_mn[t];  
   }
   }
   }

if (monster_ill[i]==0)
if (monster_action[i]==1)  
  {
  if (monster_mv[i]<t_monster_mv[t]) monster_mv[i]++;
  }
else
if (monster_action[i]==0)  
  {
  if (monster_mv[i]<t_monster_mv[t]) 
  {
  monster_mv[i]+=1+t_monster_regen[t][4];
  if (monster_mv[i]>t_monster_mv[t])monster_mv[i]=t_monster_mv[t];
  }
  }
//statuses
 if (monster_confuzed[i])
 {
 monster_confuzed[i]--;
 monster_angle[i]=SuperAngle(monster_angle[i]+300);
 monster_ai_angle[i]=monster_angle[i];
 if (count%16==0) monster_modelcolor[i]=23;
 }

if (monster_ill[i])
 {
 monster_ill[i]--; 
 if (count%8==6) monster_modelcolor[i]=104;
 }


if (monster_hasted[i])
 {
 monster_hasted[i]--;
 monster_speed[i]=monster_speed[i]*3/2;                     
 }
if (monster_charmed[i])
 {
 monster_charmed[i]--;
 if (count/3%5==3) monster_modelcolor[i]=16;
 if (monster_charmed[i]==0)
 monster_side[i]=t_monster_side[monster_type[i]];
 }

if (monster_slowed[i])
 {
 monster_hasted[i]=0;
 monster_slowed[i]--;
 monster_speed[i]=monster_speed[i]*3/5;                     
 if (count%8==7) monster_modelcolor[i]=111;
 }

if (monster_blessed[i])
 {
 monster_blessed[i]--;
 if (count%15==i) monster_modelcolor[i]=31;
 }
if (monster_magicarmor[i])
 {
 monster_magicarmor[i]--;
 if (count/3%5==2) monster_modelcolor[i]=90;
 }
if (monster_shielded[i])
 {
 monster_shielded[i]--;
 if (count/3%5==3) monster_modelcolor[i]=85;
 }

if (monster_poisoned[i])
 {
 if (count%8==5) monster_modelcolor[i]=55;
 
 if (count%16==0)
 {
 monster_hurt(i,0,1+monster_poisoned[i]/10,16);
 monster_poisoned[i]--;
 }
 }
if (monster_healed[i])
{
monster_healed[i]--;                      

monster_modelcolor[i]=55-monster_healed[i];
}

if (monster_invisible[i])
 {
 monster_modelcolor[i]=16;
 monster_invisible[i]--;
if (i==0)
monster_visible[i]=count/4%2;
else
monster_visible[i]=0;

if (monster_action[i]>1) monster_invisible[i]=0;
 }
else monster_visible[i]=1;

 }    
}
}

void GenerateDrop(Uint8 i)
{
Uint8 t=monster_type[i];

for (Uint8 n=0;n<3;n++)
if (t_monster_loot[t][n][0])
if (t_monster_loot[t][n][0]>random(101))
{
Uint8 c=t_monster_loot[t][n][2];
if (t_monster_loot[t][n][1]>=59)
if (c>1)
c=c+random(c/2);
DropItem(t_monster_loot[t][n][1],monster_cx[i],monster_cy[i],monster_cz[i],i,c);
}    
}
