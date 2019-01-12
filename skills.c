#include <skills.h>

#include <monsters.h>
#include <sound.h>
#include <interface.h>
#include <items.h>
#include <fields.h>
#include <zmath.h>
#include <RPG.h>
#include <globalvar.h>

/*
0123456789012345678901234
*/
const char class_s[40][20]=
{
"Fighter",     
"Warrior",     
"Gladiator",     
"Executer",     
"Berserker",     
"Warlord",     
"Destroyer",     
"Demon Knight",     
"Demon Lord",     
"Godslayer",     
"Thief",     
"Scout",     
"Rogue",     
"Headhunter",     
"Assasin",     
"GunSlider",     
"Master",     
"Abyss Walker",     
"Ghost Sniper",     
"Rift Master",     
"Magic-user",     
"Mage",     
"Sorcerer",     
"Wizard",     
"Warlock",     
"Black Wizard",     
"Summoner",     
"Spellsinger",     
"Master Mage",     
"Demigod",     
"Acolyte",     
"Disciple",     
"Seer",     
"Priest",     
"Elder",     
"High Priest",     
"Incarnated",     
"Prophet",     
"Outsider",     
"Messiah"
};
const char skill_s0[32][25]=
{
"Cost MV equal to STR",
"Requires adequite ammo",
"100MP",
"PASSIVE",
"40MP",
"80MP",
"10MP",     
"15MP",
"100MP",
"30MP",
"50MP",
"25MP",
"75MP",
"125MP",
"5MP",
"25MP",
"125MP",     
"6MP",
"30MP",
"150MP",
"7MP",
"35MP",
"175MP",
"23MP",
"20MP",
"45MP",
"50MP",     
"44MP",
"Cost FULL MV bar",
"You deserve this free",
"Item should disapear!",
"100 Gold Coins"};

const Sint16 skill_cost[32]=
{
0,
0,
100,
80,
40,
80,
10,     
15,
90,
30,
50,
25,
75,
125,
5,
25,
125,     
6,
30,
150,
7,
35,
175,
23,
20,
45,
50,     
44,
0,
0,
0,
0};

const char skill_s[64][25]=
{
"Attack",//0
"Melee strike",
"Shoot",//1
"Fire missle weapon",
"Charm",//2
"To induce behavior",
"Veins Of Bullets",//3
"Summon ammo for guns",
"Swift Move",//4
"Fast step to target",
"Invisiblity",//5
"Makes you invisible",
"Heal",//6
"Restores HP",
"Antidote",//7
"Cures Poison",
"Greater Heal",//8
"Restores HP",
"Bless",//9
"Blesses you",
"Haste",//10
"Increases moving speed",
"Cure Diseace",//11
"Cures illness",
"Magic Armor",//12
"Absorbs phisycal damage",
"Shield",//13
"Absorbs magic damage",
"Ice",//14
"Magic Attack Spell",
"Ice2",//15
"Magic Attack Spell",
"Ice3",//16
"Magic Attack Spell",
"Fire",//17
"Magic Attack Spell",
"Fire2",//18
"Magic Attack Spell",
"Fire3",//19
"Magic Attack Spell",
"Thunder",//20
"Magic Attack Spell",
"Thunder2",//21
"Magic Attack Spell",
"Thunder3",//22
"Magic Attack Spell",
"Poison",//23
"Fires Poison Dart",
"Slow",//24
"Slows enemy",
"Remedy",//25
"Removes statuses",
"Confuze",//26
"Confuzes enemy",
"Diseace Strike",//27
"Causes Illness",
"First Aid",//28
"Taking care of wounds",
"Guardian",//29
"1/10 chance of to block",
"Quick Item",//30
"First inventory item",
"NULL skill",//31
"If monster totaly lazy"
};

void AddSkill(unsigned short int i)
{

if (skill_l[i]==0)
{
sprintf(new_message,"Learned new skill '%s'!",skill_s[i*2]);
NewMessage();
                  

Uint8 n=0,a=1;

while (a)
{
if (skill_p[n]==32) {a=0;}
else
 n++;
}
//Uint8 t=0;
//while (item_p[t]!=n) t++;
//Uint8 t0=item_p[t];
//item_p[t]=item_p[n];
skill_p[n]=i;
  
skill_l[i]=1;
}       
}
void FieldEffect(Uint8 i)
{

field0_x=monster_x[i]-2000+random(4000);       
field0_y=monster_y[i]-2000+random(4000);        
field0_z=t_monster_height[monster_type[i]]+monster_z[i]+random(2000);        

field0_ix=-400+random(800);        
field0_iy=-400+random(800);        
field0_iz=400+random(1800);


field0_w=15000;
field0_iw=2500+random(800);
SpawnField();
}
void SpellEffect1(Uint8 i)
{
Sint32 ix,iy;
monster_angle[i]=SuperAngle(monster_angle[i]);
ix=f_cos[monster_angle[i]];     
iy=f_sin[monster_angle[i]];

field0_x=monster_x[i]-2000+random(4000)-ix/2;       
field0_y=monster_y[i]-2000+random(4000)-iy/2;        
field0_z=t_monster_height[monster_type[i]]+monster_z[i]+random(2000);        

field0_ix=-400+random(800)+ix/10;        
field0_iy=-400+random(800)+iy/10;        
field0_iz=-400+random(800);


field0_w=8000;
field0_iw=2500;
SpawnField();
Uint8 t=monster_ai_target[i];
if (t<16)
{
field0_x=monster_x[t]-2000+random(4000)+ix/3;       
field0_y=monster_y[t]-2000+random(4000)+iy/3;        
field0_z=+monster_z[i]+t_monster_height[monster_type[t]];

field0_ix=-400+random(800)-ix/16;        
field0_iy=-400+random(800)-iy/16;        
field0_iz=1400+random(800);


field0_w=8000;
field0_iw=1500;
SpawnField();
         
         
}

}
void SpellEffect2(Uint8 i)
{
Uint8 type=monster_type[i];
Sint32 ix,iy,iz;
monster_angle[i]=SuperAngle(monster_angle[i]);
ix=f_cos[monster_angle[i]];     
iy=f_sin[monster_angle[i]];

field0_x=monster_x[i]-2000+random(4000)-ix/2;       
field0_y=monster_y[i]-2000+random(4000)-iy/2;        
field0_z=t_monster_height[monster_type[i]]+monster_z[i]+random(2000);        

field0_ix=-400+random(800)+ix/10;        
field0_iy=-400+random(800)+iy/10;        
field0_iz=-400+random(800);


field0_w=8000;
field0_iw=2500;
SpawnField();
Uint8 t=monster_ai_target[i];
Uint8 k=t;
if (t<16)
{
Uint32 m=table_range[i][k]>>14;
ix=ix>>2;
iy=iy>>2;
iz=(t_monster_height[monster_type[k]]-t_monster_height[type]+monster_z[k]-monster_z[i])>>2;
if (table_range[i][k])
for (Sint32 n=0;n<m;n++)
 {
field0_x=monster_x[i]+ix*n;       
field0_y=monster_y[i]+iy*n;        
field0_z=t_monster_height[type]+monster_z[i]+iz*n;        
field0_ix=-ix>>3-500+random(1000);        
field0_iy=-iy>>3-500+random(1000);        
field0_iz=-1000;
field0_w=10000;
field0_iw=random(3000);
SpawnField();        
 }



field0_x=monster_x[t]-2000+random(4000)+ix/3;       
field0_y=monster_y[t]-2000+random(4000)+iy/3;        
field0_z=+monster_z[i]+t_monster_height[monster_type[t]];

field0_ix=-400+random(800)-ix/16;        
field0_iy=-400+random(800)-iy/16;        
field0_iz=1400+random(800);


field0_w=28000;
field0_iw=1500;
SpawnField();
         
         
}

}
void SpellEffect3(Uint8 i)
{
Uint8 type=monster_type[i];
Sint32 ix,iy,iz;
monster_angle[i]=SuperAngle(monster_angle[i]);
ix=f_cos[monster_angle[i]];     
iy=f_sin[monster_angle[i]];

field0_x=monster_x[i]-2000+random(4000)-ix/2;       
field0_y=monster_y[i]-2000+random(4000)-iy/2;        
field0_z=t_monster_height[monster_type[i]]+monster_z[i]+random(2000);        

field0_ix=-400+random(800)+ix/10;        
field0_iy=-400+random(800)+iy/10;        
field0_iz=-400+random(800);


field0_w=8000;
field0_iw=2500;
SpawnField();
Uint8 t=monster_ai_target[i];
Uint8 k=t;
if (t<16)
{
Uint32 m=table_range[i][k]>>14;
ix=ix>>2;
iy=iy>>2;
iz=(t_monster_height[monster_type[k]]-t_monster_height[type]+monster_z[k]-monster_z[i])>>2;
if (table_range[i][k])
for (Sint32 n=0;n<m;n++)
 {
field0_x=monster_x[i]+ix*n;       
field0_y=monster_y[i]+iy*n;        
field0_z=t_monster_height[type]+monster_z[i]+iz*n;        
field0_ix=-ix>>3-5000+random(10000);        
field0_iy=-iy>>3-5000+random(10000);        
field0_iz=-1000;
field0_w=20000;
field0_iw=random(3000);
SpawnField();        
 }



field0_x=monster_x[t]-2000+random(4000)+ix/3;       
field0_y=monster_y[t]-2000+random(4000)+iy/3;        
field0_z=+monster_z[i]+t_monster_height[monster_type[t]];

field0_ix=-400+random(800)-ix/16;        
field0_iy=-400+random(800)-iy/16;        
field0_iz=1400+random(800);


field0_w=48000;
field0_iw=1500;
SpawnField();
         
         
}

}


extern void monster_skill(unsigned short int i,unsigned short int iskill)
{
Uint8 succesful=0;
Uint8 type=monster_type[i];
Uint16 mpcost=0;
Uint8 target=monster_ai_target[i];
mpcost=skill_cost[iskill];

if (i==0)//Cost
switch (iskill)
{
case 1://shoot
mpcost=10000;
if (t_monster_shoottype[type]<2)
if (skill_l[3])
mpcost=2+t_monster_shoottype[type]*3;

if (item_c[62-t_monster_shoottype[type]]) mpcost=0;     
break;
}
 Uint16 dam; 

///SKILLZ
if (i==0)
if (mpcost<10000)
if (player_arm[2]==49)
mpcost=1+mpcost/2;

if (monster_mn[i]>=mpcost)
{
if (monster_action[i]<2)
switch (iskill)
 {
 case 0:// Melee
 monster_attack(i);
 drain_MV(i,t_monster_str[type]);
 break;      
 case 1:// Shoot
// monster_action[i]=5;

if (t_monster_shoottype[type]<5)
 if (monster_ai_target[i]<16) 
 {
 monster_angle[i]=table_angle[i][monster_ai_target[i]];
 if (table_vis[i][monster_ai_target[i]]) 
  {monster_hurt(monster_ai_target[i],t_monster_shootdamage[type][0]+random(1+t_monster_shootdamage[type][1]),0,i);
   monster_shoot(i);
  }

 }
 else
 if (t_monster_shoottype[type]<2)
 monster_shoot(i);

if (monster_action[i]==5)
  {
  
if (monster_mv[i]<t_monster_mv0[type])
  monster_pause[i]=t_monster_shootdelay[type]*2;
  else
  monster_pause[i]=t_monster_shootdelay[type];


   monster_frame0[i]=t_monster_shootframe[type];
 monster_frame1[i]=monster_frame0[i];
                       
if (i==0)
{

if (item_c[62-t_monster_shoottype[type]]) LoseItem(62-t_monster_shoottype[type]);
else
 succesful=1;
}
  }

 break;
 case 2://You my charming... <giggles>...
 if (monster_ai_target[i]<16)
 {
 Monster_Cast(i,monster_ai_target[i]);
 sPlaySound3D(monster_x[monster_ai_target[i]],monster_z[monster_ai_target[i]],monster_y[monster_ai_target[i]],25,600000);

 field0_index=224;        
FieldEffect(monster_ai_target[i]);
 if ((monster_status[monster_ai_target[i]]& STATUS_BOSS) ==0)
  {
  monster_charmed[monster_ai_target[i]]=320;
  monster_side[monster_ai_target[i]]=monster_side[i];
  }
  succesful=1;
 }
 break;
 case 3://Veins Of Bullets
 sprintf(new_message,"Use this skill not here! Get your gunn(c)MM!");
 NewMessage();
 break;
 case 4:// Swift Move
 if (target==16) succesful=0;
 else
 if (monster_cz[target]!=monster_cz[i]) succesful=0;
 else
 if (table_range[i][target]>100000) succesful=0;
 else
 {
 succesful=1;
 monster_x[i]=monster_x[target]+f_cos[table_angle[target][i]]/4;
 monster_y[i]=monster_y[target]+f_sin[table_angle[target][i]]/4;

 }
 if (succesful==0) 
 {
 sprintf(new_message,"Can't reach target!");
 NewMessage();
 }
 break;
 case 5:// Invisiblity
// Monster_Cast(i,16);
 monster_invisible[i]=400;
 if (i==0)
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);
  succesful=1;
 break;
 case 6://Heal
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);
 succesful=1;Monster_Cast(i,16);
 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1);
 if (i==0) dam+=lvlclass[3]*9;
 monster_heal(i,dam,i);

 for (Uint8 k=0;k<16;k++)
 if (monster_ingame[k])
 if (monster_hp[k]>0)
 if (k!=i)
 if (monster_side[i]==monster_side[k])
 if (table_vis[i][k])
 {
 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1);
 monster_heal(k,dam,i);
 }
 break;
 case 7://Antidote
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);
 succesful=1;Monster_Cast(i,16);
 monster_poisoned[i]=0;
 break;
 case 8://Greater Heal
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);
 succesful=1;Monster_Cast(i,16);
 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1);
 if (i==0) dam+=lvlclass[3]*9;
 monster_heal(i,dam*9,i);
 break;
 case 9://Bless
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);

 field0_index=152;        
 FieldEffect(i); 
 succesful=1;Monster_Cast(i,16);
 monster_blessed[i]=500;
 for (Uint8 k=0;k<16;k++)
 if (monster_ingame[k])
 if (monster_hp[k]>0)
 if (k!=i)
 if (monster_side[i]==monster_side[k])
 if (table_vis[i][k])
 {
 monster_blessed[k]=400;
 }
 break;
 case 10:// Haste
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);
 succesful=1;
 Monster_Cast(i,16);
 monster_hasted[i]=600;
 break;

 case 11://Dicease Cure
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);

 succesful=1;Monster_Cast(i,16);
 monster_ill[i]=0;
 break;
 case 12://Magic Armor
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);
 field0_index=152;        
 if (i==0)
 FieldEffect(i); 
 succesful=1;Monster_Cast(i,16);
 monster_magicarmor[i]=600;
 break;
 case 13://Shield
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);

 field0_index=152;        
 if (i==0)
 FieldEffect(i); 
 succesful=1;Monster_Cast(i,16);
 monster_shielded[i]=600;
 break;

 case 14://Ice
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],27,600000);
 
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=144;        
 SpellEffect1(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1)/2;
 monster_hurt(monster_ai_target[i],0,dam,i);
 succesful=1;
 }
 break;
 case 15://Ice2
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],27,900000);
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=144;        
 SpellEffect2(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1)/2;
 monster_hurt(monster_ai_target[i],0,dam*4,i);
 succesful=1;
 }
 break;
 case 16://Ice3
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],27,900000);
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=144;        
 SpellEffect3(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1)/2;
 monster_hurt(monster_ai_target[i],0,dam*12,i);
 succesful=1;
 }
 break;

 case 17://Fire
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],26,600000);
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=136;        
 SpellEffect1(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1);
 monster_hurt(monster_ai_target[i],0,dam,i);
 succesful=1;
 }
 break;
 case 18://Fire2
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],26,600000);
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=136;        
 SpellEffect2(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1);
 monster_hurt(monster_ai_target[i],0,dam*4,i);
 succesful=1;
 }
 break;
 case 19://Fire3
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],26,800000);
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=136;        
 SpellEffect3(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1);
 monster_hurt(monster_ai_target[i],0,dam*12,i);
 succesful=1;
 }
 break;
 case 20://Thunder
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],25,600000);
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=224;        
 SpellEffect1(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1)*8/6;
 monster_hurt(monster_ai_target[i],0,dam,i);
 succesful=1;
 }

 break;
 case 21://Thunder2
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],25,600000);
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=224;        
 SpellEffect2(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1)*8/6;
 monster_hurt(monster_ai_target[i],0,dam*4,i);
 succesful=1;
 }
 break;
 case 22://Thunder3
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],25,800000);
 Monster_Cast(i,monster_ai_target[i]);
 field0_index=224;        
 SpellEffect3(i); 
 if (monster_ai_target[i]<16)
 {
 Uint16 dam=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1])
 t_monster_mdamage[type][0]+=random(t_monster_mdamage[type][1]+1)*8/6;
 monster_hurt(monster_ai_target[i],0,dam*12,i);
 succesful=1;
 }
 break;
 case 23://poison
 if (monster_ai_target[i]<16)
 {
 Monster_Cast(i,monster_ai_target[i]);
 Uint32 damage=t_monster_mdamage[type][0];
 if (t_monster_mdamage[type][1]) damage+=random(1+t_monster_mdamage[type][1]);
 if (i==0) damage=damage+10*lvlclass[1];
 if (monster_poisoned[monster_ai_target[i]]<damage) monster_poisoned[monster_ai_target[i]]=damage;
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],22,600000);
 succesful=1;
 }
 break;
 case 24://slow
 if (monster_ai_target[i]<16)
 {
 Monster_Cast(i,monster_ai_target[i]);
 monster_slowed[monster_ai_target[i]]=600;
 sPlaySound3D(monster_x[monster_ai_target[i]],monster_z[monster_ai_target[i]],monster_y[monster_ai_target[i]],3,600000);
 succesful=1;
 }
 break;
 case 25://Remedy
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],2,600000);
 succesful=1;Monster_Cast(i,16);
 monster_healed[i]=8;

  monster_ill[i]=0;
  monster_poisoned[i]=0;
  monster_slowed[i]=0;
  monster_hasted[i]=0;
  monster_confuzed[i]=0;
  monster_magicarmor[i]=0;
  monster_shielded[i]=0;
  monster_blessed[i]=0;
 break;
 case 26://Thou shalt wander..
 if (monster_ai_target[i]<16)
 {
 Monster_Cast(i,monster_ai_target[i]);
 sPlaySound3D(monster_x[monster_ai_target[i]],monster_z[monster_ai_target[i]],monster_y[monster_ai_target[i]],25,600000);

 field0_index=224;        
FieldEffect(monster_ai_target[i]);
// if ((monster_status[monster_ai_target[i]]& STATUS_BOSS) ==0)
  {
  monster_confuzed[monster_ai_target[i]]=160;
  }
  succesful=1;
 }
 break;

 case 27://diseace
 if (monster_ai_target[i]<16)
 {
 Monster_Cast(i,monster_ai_target[i]);
 monster_ill[monster_ai_target[i]]=600;
 sPlaySound3D(monster_x[monster_ai_target[i]],monster_z[monster_ai_target[i]],monster_y[monster_ai_target[i]],22,600000);
 succesful=1;
 }
 break;
 case 28://First Aid
 if (monster_mv[0]==t_monster_mv[level_tag])
  {
  monster_mv[0]=0;
  monster_heal(0,lvlclass[0]*11,0);                                          
  }
 break;
 case 30://Quick Item
 if (item_p[0]<64) UseItem(item_p[0]);
 break;      
 }      
if (i==0)
if (succesful) monster_mn[0]-=mpcost;
}
}
