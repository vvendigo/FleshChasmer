#include <items.h>
#include <zmath.h>
#include <RPG.h>
#include <skills.h>
#include <sound.h>
#include <player.h>
#include <fields.h>
#include <monsters.h>
#include <interface.h>
#include <globalvar.h>

Sint16 weapon_points[12];
const char item_s[128][32]=
/*
0123456789012345678901234
*/
{
"Tonic","Restores 20 HP 100 MV",//0
"Super Tonic","Restores 40 HP 500 MV",//1
"Injection Of Mobility","Restores ALL MV + haste",//2
"Herb","Restores 50 HP",//3
"Potion","Restores 200 HP",//4
"Healing Potion","Restores 500 HP",//5
"Medi-Kit","Restores 1000 HP",//6
"X-Potion","Restores ALL HP",//7
"Ether","Restores 50 MP",//8
"X-Ether","Restores 250 MP",//9
"Mana Potion","Restores 100 MP",//10
"Elexir","Restores ALL HP MP MV",//11
"Antidote","Cures 'Poison' status",//12
"Scroll Of Ice","Learn 'Ice' spell",//13
"Scroll Of Fire","Learn 'Fire' spell",//14
"Scroll Of Thunder","Learn 'Thunder' spell",//15
"Bless Scroll","Casts 'bless'",//16
"Ice wand","Casts 'Ice2' on all",//17
"Fire orb","Casts 'Fire2' on all",//18
"Thunder Stone","Casts 'Thunder2' on all",//19
"Remedy","Cures all status effects",//20
"Invisiblity Potion","Great hiding effect",//21
"GunSmith ToolBox","Repairs any gun",//22
"Blade Oil","Restores blades",//23
"Fuel Oil","For chainsaw",//24
"Panacea","Cures illness",//25
"Potion of Haste","Increases moving speed",//26
"Potion Of Experience","You should taste this!",//27
"Magical Pen","Renames your character",//28
"Doom Marine Part","Collect all 4 parts!",//29
"Scroll Of Protection","Improves defense",//30
"GP2X","The Best Handheld",//31
"Knife","Sharp, Maniac design",//32
"Longsword","Three feet long one",//33
"Katana","Hentai Anime Blade",//34
"Magic Rod","Increases INT",//35
"Mace","Heavy and strong",//36
"Glass Sword","Sharp but breakable",//37
"Defloration Scythe","Esoteric Inmaterial",//38
"Chainsaw","For master lumberjacker",//39
"9mm Pistol","Basic handgun",//40
"Assault Rfile","Best missle weapon",//41
"Rocket Launcher","Launches small missles",//42
"Plasma Cannon","Prototype of alien gun",//43
"Ring Of Protection","Increases armor",//44
"Ring Of Power","Increases STR and CON",//45
"Ring Of Magic","Increases INT and WIS",//46
"Amulet Of Remedy","Protects from any status",//47
"Sigil Of Chaos","+50 STR",//48
"Golden Hairpin","Halves consumed MP",//49
"Belt Of Dexterity","+45 DEX",//50
"Ring Of Diplomacy","+100 CHA",//51
"Leather Armor","Light armor",//52
"Bronze Breastplate","Armor of medium defence",//53
"Red Quake Armor","Best body armor",//54
"Ring Of Mobility","Fast MV regeneration",//55
"Ring Of Regeneration","Regenerates HP",//56
"Ring Of Wisdom","+25 INT +45 WIS",//57
"Amulet Of Sage","+150 WIS",//58
"Energy Cell","Energy class ammo",//59
"Small Rocket","Rocket launcher ammo",//60
"4.75x5.00 ammo","Assault rfile bullets",//61
"9mm ammo","Ammo for handguns",//62
"Gold Coin","For general trade"//63
};
void WearItem(Uint8 i,Uint8 puton)
{
switch (i)
 {
//"Knife","Sharp, Maniac design",//32
case 32:
if (puton) t_monster_cha[0]+=10;
else
t_monster_cha[0]-=10;
break;
//"Longsword","Four feet long one",
case 33:
if (puton) t_monster_con[0]+=15;
else
t_monster_con[0]-=15;
break;
//"Katana","From anime samurai",
case 34:
if (puton) t_monster_dex[0]+=20;
else
t_monster_dex[0]-=20;
break;
//"Magic Rod","Increases INT",
case 35:
if (puton) t_monster_int[0]+=20;
else
t_monster_int[0]-=20;
break;
//"Warhammer","Heavy and strong",
case 36:
if (puton) t_monster_str[0]+=50;
else
t_monster_str[0]-=50;
break;
//"Glass Sword","Sharp but breakable",
case 37:
if (puton) t_monster_wis[0]+=15;
else
t_monster_wis[0]-=15;
break;
//"Defloration Scythe","Esoteric Inmaterial",
case 38:
if (puton) t_monster_str[0]+=35;
else
t_monster_str[0]-=35;
break;
//"Chainsaw","For master lumberjacker",
case 39:
if (puton) t_monster_str[0]+=5;
else
t_monster_str[0]-=5;
break;

//"9mm Pistol","Basic handgun",//
case 40:
if (puton) 
{
t_monster_cha[0]+=16;
t_monster_shoottype[0]=0;
t_monster_shootdelay[0]=7;
}
else
{
t_monster_cha[0]-=16;
t_monster_shoottype[0]=5;
}
break;
//"Assault Rfile","Best missle weapon",
case 41:
if (puton) 
{
t_monster_str[0]+=2;
t_monster_shoottype[0]=1;
t_monster_shootdelay[0]=4;
}
else
{
t_monster_str[0]-=2;
t_monster_shoottype[0]=5;
}
break;
//"Rocket Launcher","Has bonus against tanks"
case 42:
if (puton) 
{
t_monster_dex[0]-=5;
t_monster_shoottype[0]=2;
t_monster_shootdelay[0]=16;
}
else
{
t_monster_dex[0]+=5;
t_monster_shoottype[0]=5;
}
break;
//"Plasma Cannon","Prototype of alien gun",//43
case 43:
if (puton) 
{
t_monster_shoottype[0]=3;
t_monster_shootdelay[0]=2;
}
else
{
t_monster_shoottype[0]=5;
}
break;
//"Ring Of Protection","Increases armor",//
//"Ring Of Power","Increases STR and CON",
case 45:
if (puton) 
{
t_monster_str[0]+=20;
t_monster_con[0]+=20;
}
else
{
t_monster_str[0]-=20;
t_monster_con[0]-=20;
}
break;
//"Ring Of Magic","Increases INT and WIS",
case 46:
if (puton) 
{
t_monster_int[0]+=20;
t_monster_wis[0]+=20;
}
else
{
t_monster_int[0]-=20;
t_monster_wis[0]-=20;
}
break;
//"Amulet Of Remedy","Protects from any status",
//"Sigil Of Chaos","+50 STR",
case 48:
if (puton) 
{
t_monster_str[0]+=50;
}
else
{
t_monster_str[0]-=50;
}
break;
//"Golden Hairpin","Halves consumed MP",
//"Belt Of Dexterity","+45 DEX",
case 50:
if (puton) 
{
t_monster_dex[0]+=45;
}
else
{
t_monster_dex[0]-=45;
}
break;
//"Ring Of Diplomacy","+100 CHA",
case 51:
if (puton) 
{
t_monster_cha[0]+=100;
}
else
{
t_monster_cha[0]-=100;
}
break;
//"Leather Armor","Light armor",52
//"Bronze Breastplate","Armor of medium defence",53
//"Red Quake Armor","Best body armor",54
//"Ring Of Mobility","Fast MV regeneration",55
//"Ring Of Regeneration","Regenerates HP",56
//"Ring Of Wisdom","+25 INT +45 WIS",
case 57:
if (puton) 
{
t_monster_int[0]+=25;
t_monster_wis[0]+=45;
}
else
{
t_monster_int[0]-=25;
t_monster_wis[0]-=45;
}
break;
//"Amulet Of Sage","+150 WIS",
case 58:
if (puton) 
{
t_monster_wis[0]+=150;
}
else
{
t_monster_wis[0]-=150;
}
break;
       
       
       
 }
}
void AddItem(unsigned short int i,unsigned short int ii)
{
if (item_c[i]+ii>55000)
{
sprintf(new_message,"Can't carry anymore!");
}
else
{
if (ii==1)
sprintf(new_message,"Got %s!",item_s[i*2]);
else
sprintf(new_message,"Got %i %s!",ii,item_s[i*2]);
}
NewMessage();
if (item_c[i]==0)
{
Uint8 n=0,a=1;

while (a)
{
if (item_p[n]==64) {a=0;}
//else
//if (item_c[item_p[n]]==64) {a=0;}
else
 n++;
}
//Uint8 t=0;
//while (item_p[t]!=n) t++;
//Uint8 t0=item_p[t];
//item_p[t]=item_p[n];
item_p[n]=i;
}

item_c[i]=item_c[i]+ii;
if (item_c[i]>55000) item_c[i]=55000;
}

void ProcLoot(void)
{
for (Uint8 i=0;i<16;i++)
if (loot_count[i]!=0)
{

if (loot_count[i]<0)
{
//go to player                  
 loot_rx[i]=loot_x[i]+(monster_x[0]-loot_x[i])*(10+loot_count[i])/10;
 loot_ry[i]=loot_y[i]+(monster_y[0]-loot_y[i])*(10+loot_count[i])/10;
 loot_rz[i]=loot_z[i]+(monster_z[0]+t_monster_height[level_tag]-loot_z[i])*(10+loot_count[i])/10;
if (loot_count[i]==-1)
{
 AddItem(loot_item[i],loot_itemcount[i]); 
 sPlaySound3D(monster_x[i],monster_z[i],monster_y[i],29,600000);

}
} 
else
if (loot_count[i]<=10) 
 {//fly to ground
 loot_rx[i]=loot_x0[i]+(loot_x[i]-loot_x0[i])*loot_count[i]/10;
 loot_ry[i]=loot_y0[i]+(loot_y[i]-loot_y0[i])*loot_count[i]/10;
 loot_rz[i]=loot_z0[i]+(loot_z[i]-loot_z0[i])*loot_count[i]*loot_count[i]/100;
 
 }
 else                
 {//try to loot
 if (zabs(loot_z[i]-monster_z[0])<20000)
 if (30000>fastrange(loot_x[i]-monster_x[0],loot_y[i]-monster_y[0]))
 loot_count[i]=-10;
 }
loot_count[i]++;
if (loot_count[i]>280) loot_rz[i]-=400;

if (loot_count[i]==320)
 loot_count[i]=0;

}
     
     
}

void DropItem(Uint8 index,Uint8 x,Uint8 y,Uint8 z,Uint8 owner,Uint8 many)
{
Uint8 i;
i=0;
while ((i<16)&(loot_count[i]!=0))
i++;
if (i==16)
i=random(16);

loot_count[i]=1;
loot_item[i]=index;
loot_x[i]=x*65536+10000+random(40000);
loot_y[i]=y*65536+10000+random(40000);
loot_z[i]=10000+FloorProbe(loot_x[i],loot_y[i],z*65536+10000);

if (owner<16)
 {
loot_x0[i]=monster_x[owner];
loot_y0[i]=monster_y[owner];
loot_z0[i]=monster_z[owner]+t_monster_height[monster_type[owner]];
            
              
 }
else
 {
loot_x0[i]=loot_x[i];
loot_y0[i]=loot_y[i];
loot_z0[i]=loot_z[i]+32666;
 }   

loot_rx[i]=loot_x0[i];
loot_ry[i]=loot_y0[i];
loot_rz[i]=loot_z0[i];

loot_itemcount[i]=many;

}

void LoseItem(unsigned short int i)
{
 item_c[i]--;
 if (item_c[i]==0)
  for (Uint8 x=0;x<64;x++)
   if (item_p[x]==i) item_p[x]=64;
}

void LoseGold(Sint32 i)
{
 item_c[63]-=i;
 if (item_c[63]==0)
  for (Uint8 x=0;x<64;x++)
   if (item_p[x]==63) item_p[x]=64;
}

void UseItem(unsigned short int i)
{
monster_invisible[0]=0;
if (item_c[i])
 if (i<32)
 {
 Uint8 used=0;
  switch (i)
  {
  case 0: //tonic
  if ((monster_hp[0]<monster_mhp[0])|(monster_mv[0]<t_monster_mv[level_tag]))     
    {
    used=1;
    monster_confuzed[0]=0;
    monster_heal(0,20,0);                                                                               
    monster_healmv(0,100);                                                                               
    }
  break;       
  case 1: //super tonic
  if ((monster_hp[0]<monster_mhp[0])|(monster_mv[0]<t_monster_mv[level_tag]))     
    {
    monster_confuzed[1]=0;
    used=1;
    monster_heal(0,40,0);                                                                               
    monster_healmv(0,500);                                                                               
    }
  break;       
  case 2: //injection of movement
  if ((monster_mv[0]<t_monster_mv[level_tag]))     
    {
    monster_confuzed[1]=1;
    used=1;
    monster_mv[0]=t_monster_mv[level_tag];

 if (monster_hasted[0]<320) monster_hasted[0]=320;
    }
  break;       
  case 3: //Herb
  if (monster_hp[0]<monster_mhp[0])     
    {
    used=1;
    monster_heal(0,50,0);                                                                               
    }
  break;       
  case 4: //Potion
  if (monster_hp[0]<monster_mhp[0])     
    {
    used=1;
    monster_heal(0,200,0);                                                                               
    }
  break;       
  case 5: //Healing Potion
  if (monster_hp[0]<monster_mhp[0])     
    {
    used=1;
    monster_heal(0,500,0);                                                                               
    }
  break;       
  case 6: //Medikit
  if (monster_hp[0]<monster_mhp[0])     
    {
  Monster_Cast(0,16);
    used=1;
    monster_heal(0,1000,0);                                                                               
    }
  break;       
  case 7: //X-Potion
  if (monster_hp[0]<monster_mhp[0])     
    {
    used=1;
    monster_heal(0,10000,0);                                                                               
    }
  break;       
  case 8: //Ether
  if (monster_mn[0]<t_monster_mn[level_tag])     
    {
    used=1;
    monster_healmp(0,50);                                                                               
    }
  break;
  case 9: //X-Ether
  if (monster_mn[0]<t_monster_mn[level_tag])     
    {
    used=1;
    monster_healmp(0,250);                                                                               
    }
  break;       
  case 10: //Mana Potion
  if (monster_mn[0]<t_monster_mn[level_tag])     
    {
    used=1;
    monster_healmp(0,100);                                                                               
    }
  break;       
  case 11: //Elexir
  if ((monster_mn[0]<t_monster_mn[level_tag])|(monster_hp[0]<monster_mhp[0])|(monster_mv[0]<t_monster_mv[level_tag]))
    {
    used=1;
    monster_heal(0,10000,0);                                                                               
    monster_healmp(0,10000);                                                                               
    monster_healmv(0,10000);                                                                               
    }
  break;       
  case 12: //Antidote
  Monster_Cast(0,16);
  if (monster_poisoned[0])     
    {
    used=1;
    monster_poisoned[0]=0;                                                                               
    }
  break;       

  case 13://ice scroll
  Monster_Cast(0,16);
  if (skill_l[14]==0) {used=1;AddSkill(14);}
  else
  if (skill_l[15]==0) {used=1;AddSkill(15);}
  else
  if (skill_l[16]==0) {used=1;AddSkill(16);}
  break;
  case 14://fire scroll
  Monster_Cast(0,16);
  if (skill_l[17]==0) {used=1;AddSkill(17);}
  else
  if (skill_l[18]==0) {used=1;AddSkill(18);}
  else
  if (skill_l[19]==0) {used=1;AddSkill(19);}
  break;
  case 15://thunder scroll
  Monster_Cast(0,16);
  if (skill_l[20]==0) {used=1;AddSkill(20);}
  else
  if (skill_l[21]==0) {used=1;AddSkill(21);}
  else
  if (skill_l[22]==0) {used=1;AddSkill(22);}
  break;

  case 16: //Scroll Of Bless
  Monster_Cast(0,16);
used=1;
if (monster_blessed[0]<1000) monster_blessed[0]=1000;
if (GameMode==GAME)
{
field0_index=152;        
FieldEffect(i);        
}
break;
case 17://ice wand
if (GameMode==GAME)
{
sPlaySound(27,128,128);
Monster_Cast(0,16);
used=1;
field0_index=144;        
FieldEffect(0);        
 for (Uint8 k=1;k<16;k++)
 if (monster_ingame[k])
 if (monster_hp[k]>0)
 if (monster_side[0]!=monster_side[k])
 if (table_vis[0][k])
 if (table_range[0][k]<t_monster_targetrange[level_tag])
 {
 monster_hurt(k,0,800,0);
field0_index=144;        
 FieldEffect(k);        
 }
}   
break;
case 18://fire orb
if (GameMode==GAME)
{
sPlaySound(26,128,128);
Monster_Cast(0,16);
used=1;
field0_index=136;        
FieldEffect(0);        
 for (Uint8 k=1;k<16;k++)
 if (monster_ingame[k])
 if (monster_hp[k]>0)
 if (monster_side[0]!=monster_side[k])
 if (table_vis[0][k])
 if (table_range[0][k]<t_monster_targetrange[level_tag])
 {
 monster_hurt(k,0,1000,0);
field0_index=136;        
 FieldEffect(k);        
 }
}   
break;
case 19://thunder stone
if (GameMode==GAME)
{
sPlaySound(25,128,128);
Monster_Cast(0,16);
used=1;
field0_index=224;        
FieldEffect(0);        
 for (Uint8 k=1;k<16;k++)
 if (monster_ingame[k])
 if (monster_hp[k]>0)
 if (monster_side[0]!=monster_side[k])
 if (table_vis[0][k])
 if (table_range[0][k]<t_monster_targetrange[level_tag])
 {
field0_index=224;        
 FieldEffect(k);        
 monster_hurt(k,0,1150,0);
 }
}   
break;
  
  case 20://remedy
  Monster_Cast(0,16);
  monster_ill[0]=0;
  monster_poisoned[0]=0;
  monster_hasted[0]=0;
  monster_slowed[0]=0;
  monster_confuzed[0]=0;
  monster_magicarmor[0]=0;
  monster_shielded[0]=0;
  monster_blessed[0]=0;

  monster_healed[0]=8;
  used=1;    
  break;  
  case 21://invisiblity
  used=1;
  if (monster_invisible[0]<800) monster_invisible[0]=800;
  break;

  case 22://toolbox
  if (player_arm[1]==0)
  {
  sprintf(new_message,"Must have gun to repair!");
  NewMessage();
  }
  else
  if (weapon_points[player_arm[1]-32]==1000)
  {
  sprintf(new_message,"Cannot repair any futher!");
  NewMessage();
  }
  else
  {
  sprintf(new_message,"Succesful repair!");
  NewMessage();
  weapon_points[player_arm[1]-32]+=400+random(400);
  if (weapon_points[player_arm[1]-32]>1000) weapon_points[player_arm[1]-32]=1000;
  used=1;
  }
  break;
  case 23://blade oil
  if (player_arm[0]==0 | player_arm[0]>34)
  {
  sprintf(new_message,"Must have ordinary blade to repair!");
  NewMessage();
  }
  else
  if (weapon_points[player_arm[0]-32]==1000)
  {
  sprintf(new_message,"Cannot repair any futher!");
  NewMessage();
  }
  else
  {
  sprintf(new_message,"Succesful repair!");
  NewMessage();
  weapon_points[player_arm[0]-32]+=400+random(400);
  if (weapon_points[player_arm[0]-32]>1000) weapon_points[player_arm[0]-32]=1000;
  used=1;
  }
  break;
  case 24://Fuel
  if (player_arm[0]!=39)
  {
  sprintf(new_message,"Where you put your chaingsaw?!!");
  NewMessage();
  }
  else
  if (weapon_points[player_arm[0]-32]==1000)
  {
  sprintf(new_message,"Fuel tank full!");
  NewMessage();
  }
  else
  {
  sprintf(new_message,"Succesfuly recharged!");
  NewMessage();
  weapon_points[player_arm[0]-32]+=400+random(400);
  if (weapon_points[player_arm[0]-32]>1000) weapon_points[player_arm[0]-32]=1000;
  used=1;
  }
  break;


  case 25://panacea
  if (monster_ill[0])
   {
   monster_ill[0]=0;
   used=1;                  
   }
  break;
  case 26://haste
  used=1;
  if (monster_hasted[0]<1600) monster_hasted[0]=1600;
  break;
  case 27:
used=1;
if (GameMode==GAME)
{
field0_x=monster_x[0]-4000+random(8000);       
field0_y=monster_y[0]-4000+random(8000);        
field0_z=t_monster_height[level_tag]+monster_z[0]+random(4000);        

field0_ix=-400+random(800);        
field0_iy=-400+random(800);        
field0_iz=-400+random(800);


field0_w=12000;
field0_iw=2000;
field0_index=152;        
}
SpawnField();        
AddLevel();  
  break;
  case 28: PlayerReName();break;
  case 29://doomed statue quest
  if( item_c[29]>3)
  {
  used=1;
  LoseItem(i);
  LoseItem(i);
  LoseItem(i);
  AddItem(31,1);
  AddItem(28,1);
  }
  break;
  case 30:
  Monster_Cast(0,16);
  monster_magicarmor[0]=3200;
  monster_shielded[0]=3200;
  used=1;
  break;
  case 31: //GP2X
  if (GameMode==GAME)
    {
  switch (random(9))
     {
     case 0:sprintf(new_message,"Look! It has FleshChamer 2 Demo Version on her SD card!");break;
     case 1:sprintf(new_message,"Shit! 'Sword Of Mana'(GBA) doesn't launch :(");break;
     case 2:sprintf(new_message,"I should sell this to somebody and buy more herbs.");break;
     case 3:sprintf(new_message,"Wow! A MP3!");NextMusicTrack(random(49));Music_Fade_Count=25;;break;
     case 4:sprintf(new_message,"I wish this was a spare rocket.");break;
     case 5:sprintf(new_message,"Is there any 9mm bullets inside this unit?");break;
     case 6:sprintf(new_message,"Listen! I'm not a Lara Croft! I'm the %s",t_monster_name[level_tag]);break;
     case 7:sprintf(new_message,"There is no secret game ending with this GP2X item!");break;
     case 8:sprintf(new_message,"Crap! I thought just have lost my joystic cap! >_<");break;
     
     }
     NewMessage();
    }
  break;       
         
       
  }//used item effects 

 if (used) 
 {
 sprintf(new_message,"Used %s.",item_s[i*2]);NewMessage();
 
 LoseItem(i);sPlaySound(2,100,100);}else sPlaySound(1,100,100);
 }
 else
 if (level_tag==0)
 if (i<59)
 {
 Uint8 last;
 if (i<40)
  {
  last=player_arm[0];
  WearItem(player_arm[0],0);
  if (i==last) player_arm[0]=0;else player_arm[0]=i;
  UpdatePlayer();
  }
  else
 if (i<44)
  {
  last=player_arm[1];
  WearItem(player_arm[1],0);
  if (i==last) player_arm[1]=0;else player_arm[1]=i;
  UpdatePlayer();
  }
  else     
  {
  last=player_arm[2];
  WearItem(player_arm[2],0);
  if (i==last) player_arm[2]=0;else player_arm[2]=i;

  UpdatePlayer();
  }
  if (last!=i)
   {
   WearItem(i,1);
   UpdatePlayer();
   }
 }  
 else
 if (i<63)
 {
    sprintf(new_message,"Get your gunn (c)Marilyn Manson");
    NewMessage();
 }
 else
 {
    sprintf(new_message,"Find a shop to spend your money.");
    NewMessage();
 }
}
