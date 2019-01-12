#include "monsters.h"
#include "globalvar.h"
#include "player.h"
#include "sound.h"
#include "camera.h"
#include "RPG.h"
#include "fields.h"
#include "zmath.h"


void InitMonsterTable(void)
{
exp_lvl[0]=100;
for (Uint8 i=1;i<99;i++)
exp_lvl[i]=exp_lvl[i-1]+(100+i*5)*i;
exp_lvl[0]=65;


// Code88
t_monster_radius   [ 0]=12000;
t_monster_model    [ 0]=12;
t_monster_speed    [ 0]=275;
t_monster_status   [ 0]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 0]=0;


t_monster_stepsound      [ 0]   =1;

t_monster_shootdelay     [ 0]   =4;
t_monster_shoottype      [ 0]   =5;
t_monster_shootframe     [ 0]   =10;

t_monster_meleeframe0    [ 0]   =11;
t_monster_warmodecount   [ 0]   =1;
t_monster_meleeframecount[ 0]   =1;

t_monster_meleeanim      [ 0][0]=4;
t_monster_meleeanim      [ 0][1]=8;
t_monster_meleeanim      [ 0][2]=10;

t_monster_deathtype      [ 0]   =2;
t_monster_painframe0     [ 0]   =8;
t_monster_painframecount [ 0]   =2;

t_monster_walkframe0     [ 0]   =4;
t_monster_castframe0[0]=13;
t_monster_meleesound[0]=21;
t_monster_painsound [0]=22;
t_monster_meleerange[0]=15000;

t_monster_targetrange[0]=200000;
t_monster_height[0]=30000;

t_monster_regen[0][0]=0;
t_monster_regen[0][1]=0;
t_monster_regen[0][2]=0;
t_monster_regen[0][3]=0;
t_monster_regen[0][4]=0;


t_monster_hp       [ 0][0]=40;
t_monster_mn       [ 0]=10;
t_monster_mv       [ 0]=50;
t_monster_str[0]=6;
t_monster_dex[0]=10;
t_monster_con[0]=5;
t_monster_int[0]=12;
t_monster_wis[0]=4;
t_monster_cha[0]=2;

t_monster_damage[0][0]=5;
t_monster_damage[0][1]=10;
t_monster_armor [0]=0;
t_monster_resist[0]=0;

sprintf(t_monster_name[0],"Code 88   ");
t_monster_char[0][0]='@';
t_monster_char[0][1]=71;

// Vurlach
t_monster_radius   [ 1]=18000;
t_monster_model    [ 1]=1;
t_monster_speed    [ 1]=500;
t_monster_status   [ 1]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 1]=0;




t_monster_meleeframe0    [ 1]   =8;
t_monster_warmodecount   [ 1]   =3;
t_monster_meleeframecount[ 1]   =2;

t_monster_meleeanim      [ 1][0]=2;
t_monster_meleeanim      [ 1][1]=5;
t_monster_meleeanim      [ 1][2]=10;

t_monster_painframe0     [ 1]   =13;
t_monster_painframecount [ 1]   =2;

t_monster_walkframe0     [ 1]   =4;

t_monster_meleesound[1]=21;
t_monster_painsound [1]=22;
t_monster_meleerange[1]=15000;

t_monster_targetrange[1]=200000;
t_monster_height[1]=30000;

t_monster_regen[1][0]=16;
t_monster_regen[1][1]=10;
t_monster_regen[1][2]=0;
t_monster_regen[1][3]=0;
t_monster_regen[1][4]=2;

t_monster_hp       [ 1][0]=5000;
t_monster_mn       [ 1]=100;
t_monster_mv       [ 1]=255;
t_monster_str[1]=19;
t_monster_dex[1]=12;
t_monster_con[1]=15;
t_monster_int[1]=8;
t_monster_wis[1]=11;
t_monster_cha[1]=20;

t_monster_damage[1][0]=25;
t_monster_damage[1][1]=80;
t_monster_armor [1]=10;
t_monster_resist[1]=10;
sprintf(t_monster_name[1],"Vurlach");
t_monster_char[1][0]='@';
t_monster_char[1][1]=70;
//


// Spider
t_monster_radius   [ 2]=20000;
t_monster_model    [ 2]=0;
t_monster_speed    [ 2]=600;
t_monster_stepsound[ 2]=0;
t_monster_status   [ 2]=STATUS_ALIVE | STATUS_CRAWLING | STATUS_AI;
t_monster_side     [ 2]=1;     
t_monster_regen[2][0]=20;
t_monster_regen[2][1]=1;
t_monster_regen[2][2]=0;
t_monster_regen[2][3]=0;
t_monster_regen[2][4]=1;


t_monster_meleeframe0    [ 2]   =8;
t_monster_warmodecount   [ 2]   =1;
t_monster_meleeframecount[ 2]   =1;

t_monster_meleeanim      [ 2][0]=2;
t_monster_meleeanim      [ 2][1]=7;
t_monster_meleeanim      [ 2][2]=14;

t_monster_painframe0     [ 2]   =10;
t_monster_painframecount [ 2]   =2;

t_monster_meleesound[2]=21;
t_monster_painsound [2]=22;
t_monster_meleerange[2]=15000;

t_monster_targetrange[2]=200000;
t_monster_height[2]=12000;

t_monster_walkframe0     [ 2]   =4;

t_monster_deathframe   [2]=12;
t_monster_deathspeed   [2]=5;
t_monster_maxagonycount[2]=12;
t_monster_deathtype    [2]=1;

t_monster_loot[2][0][0]=50;
t_monster_loot[2][0][1]=0;
t_monster_loot[2][0][2]=1;

t_monster_loot[2][1][0]=25;
t_monster_loot[2][1][1]=3;
t_monster_loot[2][1][2]=1;

t_monster_loot[2][2][0]=75;
t_monster_loot[2][2][1]=63;
t_monster_loot[2][2][2]=10;


t_monster_hp       [ 2][0]=40;
t_monster_hp       [ 2][1]=40;
t_monster_mn       [ 2]=10;
t_monster_mv       [ 2]=128;
t_monster_str[2]=8;
t_monster_dex[2]=14;
t_monster_con[2]=10;
t_monster_int[2]=4;
t_monster_wis[2]=4;
t_monster_cha[2]=8;

t_monster_damage[2][0]=5;
t_monster_damage[2][1]=15;
t_monster_armor [2]=10;
t_monster_resist[2]=10;
t_monster_deathsound[2]=31;

sprintf(t_monster_name[2],"Spider");
t_monster_char[2][0]='s';
t_monster_char[2][1]=36;

// Tsisauq
t_monster_radius   [ 3]=15000;
t_monster_model    [ 3]=2;
t_monster_speed    [ 3]=350;
t_monster_stepsound[ 3]=1;
t_monster_status   [ 3]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 3]=0;

t_monster_action    [ 3][0]=1;
t_monster_action    [ 3][1]=1;
t_monster_action    [ 3][2]=1;
t_monster_action    [ 3][3]=1;

t_monster_walkframe0     [ 3]   =4;
t_monster_shootframe[3]=8;
t_monster_shoottype[3]=1;
t_monster_shootdelay[3]=4;
t_monster_shootdamage[3][0]=20;
t_monster_shootdamage[3][1]=90;

t_monster_painframe0     [ 3]   =9;
t_monster_painframecount [ 3]   =2;

t_monster_walkframe0     [ 3]   =4;

t_monster_meleesound[3]=21;
t_monster_painsound [3]=22;
t_monster_meleerange[3]=15000;

t_monster_targetrange[3]=200000;
t_monster_height[3]=30000;

t_monster_regen[3][0]=32;
t_monster_regen[3][1]=2;
t_monster_regen[3][2]=16;
t_monster_regen[3][3]=1;
t_monster_regen[3][4]=0;

t_monster_hp       [ 3][0]=2714;
t_monster_mn       [ 3]=256;
t_monster_mv       [ 3]=666;
t_monster_str[3]=11;
t_monster_dex[3]=5;
t_monster_con[3]=13;
t_monster_int[3]=17;
t_monster_wis[3]=29;
t_monster_cha[3]=9;

t_monster_deathtype[3]=2;
t_monster_damage[3][0]=25;
t_monster_damage[3][1]=80;
t_monster_armor [3]=10;
t_monster_resist[3]=90;
sprintf(t_monster_name[3],"Tsis Auq");
t_monster_char[3][0]='@';
t_monster_char[3][1]=127;


// Zombie
t_monster_radius   [ 4]=15000;
t_monster_model    [ 4]=3;
t_monster_speed    [ 4]=300;
t_monster_stepsound[ 4]=0;
t_monster_status   [ 4]=STATUS_ALIVE | STATUS_UNDEAD | STATUS_AI;
t_monster_side     [ 4]=1;     

t_monster_regen[4][0]=0;
t_monster_regen[4][1]=0;
t_monster_regen[4][2]=0;
t_monster_regen[4][3]=0;
t_monster_regen[4][4]=0;


t_monster_walkframe0     [ 4]   =4;
t_monster_meleeframe0    [ 4]   =8;
t_monster_warmodecount   [ 4]   =1;
t_monster_meleeframecount[ 4]   =1;

t_monster_meleeanim      [ 4][0]=2;
t_monster_meleeanim      [ 4][1]=7;
t_monster_meleeanim      [ 4][2]=14;

t_monster_painframe0     [ 4]   =10;
t_monster_painframecount     [ 4]   =1;

t_monster_meleesound[4]=21;
t_monster_painsound [4]=22;
t_monster_meleerange[4]=15000;

t_monster_targetrange[4]=120000;
t_monster_height[4]=22000;


t_monster_deathtype    [4]=2;

t_monster_loot[4][0][0]=30;
t_monster_loot[4][0][1]=5;
t_monster_loot[4][0][2]=1;

t_monster_loot[4][1][0]=15;
t_monster_loot[4][1][1]=10;
t_monster_loot[4][1][2]=1;

t_monster_loot[4][2][0]=50;
t_monster_loot[4][2][1]=63;
t_monster_loot[4][2][2]=150;


t_monster_hp       [ 4][0]=2600;
t_monster_hp       [ 4][1]=600;
t_monster_mn       [ 4]=100;
t_monster_mv       [ 4]=300;
t_monster_str[4]=15;
t_monster_dex[4]=20;
t_monster_con[4]=10;
t_monster_int[4]=5;
t_monster_wis[4]=5;
t_monster_cha[4]=50;

t_monster_action[4][1]=27;
t_monster_action[4][2]=23;

t_monster_damage[4][0]=100;
t_monster_damage[4][1]=300;
t_monster_armor [4]=20;
t_monster_resist[4]=60;
t_monster_deathsound[4]=32;
sprintf(t_monster_name[4],"BOMJ Zombie");
t_monster_char[4][0]='Z';
t_monster_char[4][1]=55;

// Giant Bat
t_monster_radius   [ 5]=15000;
t_monster_model    [ 5]=4;
t_monster_speed    [ 5]=800;
t_monster_stepsound[ 5]=0;
t_monster_status   [ 5]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 5]=1;     

t_monster_regen[5][0]=5;
t_monster_regen[5][1]=1;
t_monster_regen[5][2]=0;
t_monster_regen[5][3]=0;
t_monster_regen[5][4]=0;

t_monster_simpleanim     [ 5]   =1;

t_monster_walkframe0     [ 5]   =0;
t_monster_meleeframe0    [ 5]   =3;
t_monster_warmodecount   [ 5]   =1;
t_monster_meleeframecount[ 5]   =1;

t_monster_meleeanim      [ 5][0]=2;
t_monster_meleeanim      [ 5][1]=9;
t_monster_meleeanim      [ 5][2]=14;

t_monster_painframe0     [ 5]   =5;
t_monster_painframecount     [ 5]   =0;

t_monster_meleesound[5]=21;
t_monster_painsound [5]=22;
t_monster_meleerange[5]=15000;

t_monster_targetrange[5]=120000;
t_monster_height[5]=22000;


t_monster_deathtype    [5]=4;

t_monster_loot[5][0][0]=45;
t_monster_loot[5][0][1]=3;
t_monster_loot[5][0][2]=1;

t_monster_loot[5][1][0]=25;
t_monster_loot[5][1][1]=8;
t_monster_loot[5][1][2]=1;

t_monster_loot[5][2][0]=75;
t_monster_loot[5][2][1]=63;
t_monster_loot[5][2][2]=5;


t_monster_hp       [ 5][0]=50;
t_monster_hp       [ 5][1]=60;
t_monster_mn       [ 5]=10;
t_monster_mv       [ 5]=300;
t_monster_str[5]=15;
t_monster_dex[5]=10;
t_monster_con[5]=3;
t_monster_int[5]=15;
t_monster_wis[5]=15;
t_monster_cha[5]=8;

t_monster_damage[5][0]=5;
t_monster_damage[5][1]=40;
t_monster_armor [5]=0;
t_monster_resist[5]=15;
t_monster_deathsound[5]=31;
sprintf(t_monster_name[5],"Giant Bat");
t_monster_char[5][0]='b';
t_monster_char[5][1]=36;


// Tank T-007
t_monster_deathframe[ 6]   =4;
t_monster_radius   [ 6]=35000;
t_monster_model    [ 6]=5;
t_monster_speed    [ 6]=300;
t_monster_stepsound[ 6]=0;
t_monster_status   [ 6]=STATUS_ALIVE | STATUS_AI | STATUS_TANK | STATUS_CRAWLING;
t_monster_side     [ 6]=2;     

t_monster_damageeffect     [ 6]=1;     

t_monster_shoottype     [ 6]=2;     
t_monster_shootdelay    [ 6]=128;     

t_monster_action     [ 6][0]=1;     
t_monster_action     [ 6][1]=1;     
t_monster_action     [ 6][2]=1;     
t_monster_action     [ 6][3]=1;     


t_monster_simpleanim     [ 6]   =1;

t_monster_painframe0     [ 6]   =4;
t_monster_painframecount [ 6]   =4;

t_monster_meleesound[6]=21;
t_monster_painsound [6]=22;
t_monster_meleerange[6]=15000;

t_monster_targetrange[6]=230123;
t_monster_height[6]=32000;


t_monster_deathtype    [6]=3;

t_monster_loot[6][0][0]=50;
t_monster_loot[6][0][1]=2;
t_monster_loot[6][0][2]=2;

t_monster_loot[6][1][0]=100;
t_monster_loot[6][1][1]=1;
t_monster_loot[6][1][2]=2;

t_monster_loot[6][2][0]=85;
t_monster_loot[6][2][1]=60;
t_monster_loot[6][2][2]=3;


t_monster_hp       [ 6][0]=1000;
t_monster_hp       [ 6][1]=2000;
t_monster_mn       [ 6]=10;
t_monster_mv       [ 6]=250;
t_monster_str[6]=1;
t_monster_dex[6]=1;
t_monster_con[6]=20;
t_monster_int[6]=1;
t_monster_wis[6]=1;
t_monster_cha[6]=500;

t_monster_shootdamage[6][0]=400;
t_monster_shootdamage[6][1]=2000;
t_monster_armor [6]=75;
t_monster_resist[6]=95;
sprintf(t_monster_name[6],"Tank T-007");
t_monster_char[6][0]='T';
t_monster_char[6][1]=20;
//

// Host
t_monster_radius   [ 7]=15000;
t_monster_model    [ 7]=6;
t_monster_speed    [ 7]=350;
t_monster_stepsound[ 7]=1;
t_monster_status   [ 7]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 7]=0;

t_monster_action    [ 7][0]=31;
t_monster_action    [ 7][1]=31;
t_monster_action    [ 7][2]=31;
t_monster_action    [ 7][3]=31;

t_monster_shoottype[7]=5;

t_monster_painframe0     [ 7]   =4;
t_monster_painframecount [ 7]   =0;

t_monster_walkframe0     [ 7]   =4;

t_monster_painsound [7]=22;
t_monster_meleerange[7]=15000;

t_monster_targetrange[7]=200000;
t_monster_height[7]=30000;

t_monster_regen[7][0]=8;
t_monster_regen[7][1]=1;
t_monster_regen[7][2]=16;
t_monster_regen[7][3]=1;
t_monster_regen[7][4]=4;

t_monster_hp       [ 7][0]=55;
t_monster_hp       [ 7][1]=11;
t_monster_mn       [ 7]=5;
t_monster_mv       [ 7]=20;
t_monster_str[7]=4;
t_monster_dex[7]=4;
t_monster_con[7]=4;
t_monster_int[7]=4;
t_monster_wis[7]=4;
t_monster_cha[7]=8;

t_monster_deathtype[7]=2;
t_monster_armor [7]=60;
t_monster_resist[7]=50;
sprintf(t_monster_name[7],"Host");
t_monster_char[7][0]='Z';
t_monster_char[7][1]=35;


// Halobane
t_monster_radius   [ 8]=15000;
t_monster_model    [ 8]=7;
t_monster_speed    [ 8]=450;
t_monster_status   [ 8]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 8]=0;

t_monster_action    [ 8][0]=1;
t_monster_action    [ 8][1]=1;
t_monster_action    [ 8][2]=1;
t_monster_action    [ 8][3]=1;

t_monster_walkframe0     [ 8]   =4;
t_monster_shootframe[8]=9;
t_monster_shoottype[8]=0;
t_monster_shootdelay[8]=10;
t_monster_shootdamage[8][0]=50;
t_monster_shootdamage[8][1]=150;

t_monster_painframe0     [ 8]   =9;
t_monster_painframecount [ 8]   =0;

t_monster_walkframe0     [ 8]   =4;

t_monster_meleesound[8]=21;
t_monster_painsound [8]=22;
t_monster_meleerange[8]=15000;

t_monster_targetrange[8]=200000;
t_monster_height[8]=30000;

t_monster_regen[8][0]=32;
t_monster_regen[8][1]=2;
t_monster_regen[8][2]=16;
t_monster_regen[8][3]=1;
t_monster_regen[8][4]=0;

t_monster_hp       [ 8][0]=4245;
t_monster_mn       [ 8]=100;
t_monster_mv       [ 8]=300;
t_monster_str[8]=16;
t_monster_dex[8]=20;
t_monster_con[8]=16;
t_monster_int[8]=12;
t_monster_wis[8]=18;
t_monster_cha[8]=24;

t_monster_deathtype[8]=1;
t_monster_damage[8][0]=10;
t_monster_damage[8][1]=40;
t_monster_armor [8]=25;
t_monster_resist[8]=35;

t_monster_action [8][1]=9;

sprintf(t_monster_name[8],"Halobane");
t_monster_char[8][0]='@';
t_monster_char[8][1]=70;

// Will Of The Vein
t_monster_radius   [ 9]=20000;
t_monster_model    [ 9]=8;
t_monster_speed    [ 9]=600;
t_monster_stepsound[ 9]=0;
t_monster_status   [ 9]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 9]=1;     
t_monster_regen[9][1]=20;
t_monster_regen[9][1]=1;


t_monster_meleeframe0    [ 9]   =3;
t_monster_warmodecount   [ 9]   =1;
t_monster_meleeframecount[ 9]   =1;

t_monster_meleeanim      [ 9][0]=2;
t_monster_meleeanim      [ 9][1]=13;
t_monster_meleeanim      [ 9][2]=25;

t_monster_painframe0     [ 9]   =5;
t_monster_painframecount [ 9]   =0;

t_monster_meleesound[9]=21;
t_monster_painsound [9]=22;
t_monster_meleerange[9]=15000;

t_monster_targetrange[9]=250000;
t_monster_height[9]=12000;

t_monster_walkframe0     [ 9]   =0;

t_monster_deathframe   [9]=5;
t_monster_deathspeed   [9]=5;
t_monster_maxagonycount[9]=12;
t_monster_deathtype    [9]=1;


t_monster_hp       [ 9][0]=300;
t_monster_hp       [ 9 ][1]=250;
t_monster_mn       [ 9]=10;
t_monster_mv       [ 9]=128;
t_monster_str[9]=8;
t_monster_dex[9]=14;
t_monster_con[9]=1;
t_monster_int[9]=4;
t_monster_wis[9]=4;
t_monster_cha[9]=55;

t_monster_damage[9][0]=10;
t_monster_damage[9][1]=150;
t_monster_armor [9]=15;
t_monster_resist[9]=0;
t_monster_deathsound[9]=33;
sprintf(t_monster_name[9],"Will Of the Veins");
t_monster_char[9][0]='w';
t_monster_char[9][1]=111;

// Huntress
t_monster_radius   [ 10]=22000;
t_monster_model    [ 10]=10;
t_monster_speed    [ 10]=300;
t_monster_status   [ 10]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 10]=1;


t_monster_deathtype      [ 10]   =2;

t_monster_castframe0     [ 10]   =3;
t_monster_painframe0     [ 10]   =5;
t_monster_painframecount [ 10]   =0;

t_monster_walkframe0     [ 10]   =0;

t_monster_meleesound[10]=21;
t_monster_painsound [10]=22;
t_monster_meleerange[10]=25000;

t_monster_targetrange[10]=240000;
t_monster_height[10]=40000;

t_monster_regen[10][0]=64;
t_monster_regen[10][1]=100;
t_monster_regen[10][2]=0;
t_monster_regen[10][3]=0;
t_monster_regen[10][4]=2;

t_monster_hp       [ 10][0]=20000;
t_monster_hp       [ 10][1]=5000;
t_monster_mn       [ 10]=1000;
t_monster_mv       [ 10]=10000;
t_monster_str[10]=50;
t_monster_dex[10]=50;
t_monster_con[10]=50;
t_monster_int[10]=50;
t_monster_wis[10]=50;
t_monster_cha[10]=5000;

t_monster_action[10][0]=15;
t_monster_action[10][1]=18;
t_monster_action[10][2]=21;
t_monster_mdamage[10][0]=50;
t_monster_mdamage[10][1]=5;

t_monster_damage[10][0]=25;
t_monster_damage[10][1]=80;
t_monster_armor [10]=25;
t_monster_resist[10]=30;
t_monster_deathsound[10]=33;
sprintf(t_monster_name[10],"Huntress");
t_monster_char[10][0]='D';
t_monster_char[10][1]=111;

// whore Civilian
t_monster_radius   [ 11]=22000;
t_monster_model    [ 11]=11;
t_monster_speed    [ 11]=400;
t_monster_status   [ 11]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 11]=2;


t_monster_deathtype      [ 11]   =1;


t_monster_painframe0     [ 11]   =8;
t_monster_painframecount [ 11]   =0;
t_monster_deathframe     [ 11]   =8;
t_monster_deathspeed     [ 11]   =10;

t_monster_walkframe0     [ 11]   =4;

t_monster_action         [ 11][0]=31;
t_monster_action         [ 11][1]=31;
t_monster_action         [ 11][2]=31;
t_monster_action         [ 11][3]=31;

t_monster_painsound [11]=22;
t_monster_meleerange[11]=25000;

t_monster_targetrange[11]=180000;
t_monster_height[11]=20000;

t_monster_regen[11][0]=0;
t_monster_regen[11][1]=0;
t_monster_regen[11][2]=0;
t_monster_regen[11][3]=0;
t_monster_regen[11][4]=0;

t_monster_hp       [ 11][0]=300;
t_monster_hp       [ 11][1]=100;
t_monster_mn       [ 11]=10;
t_monster_mv       [ 11]=50;
t_monster_str[11]=1;
t_monster_dex[11]=1;
t_monster_con[11]=1;
t_monster_int[11]=1;
t_monster_wis[11]=1;
t_monster_cha[11]=100;

t_monster_damage[11][0]=0;
t_monster_damage[11][1]=0;
t_monster_armor [11]=0;
t_monster_resist[11]=0;
t_monster_maxagonycount [11]=10;
t_monster_deathsound[11]=35;

sprintf(t_monster_name[11],"Infidel Whore");
t_monster_char[11][0]='@';
t_monster_char[11][1]=22;

// Goblin
t_monster_radius   [ 12]=20000;
t_monster_model    [ 12]=15;
t_monster_speed    [ 12]=600;
t_monster_stepsound[ 12]=0;
t_monster_status   [ 12]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 12]=1;     
t_monster_regen[12][0]=20;
t_monster_regen[12][1]=1;
t_monster_regen[12][2]=0;
t_monster_regen[12][3]=0;
t_monster_regen[12][4]=1;


t_monster_meleeframe0    [12]   =9;
t_monster_warmodecount   [12]   =1;
t_monster_meleeframecount[12]   =1;

t_monster_meleeanim      [12][0]=2;
t_monster_meleeanim      [12][1]=7;
t_monster_meleeanim      [12][2]=14;

t_monster_painframe0     [12]   =8;
t_monster_painframecount [12]   =1;

t_monster_meleesound[12]=21;
t_monster_painsound [12]=22;
t_monster_meleerange[12]=15000;

t_monster_targetrange[12]=200000;
t_monster_height[12]=27000;

t_monster_walkframe0     [12]   =4;

t_monster_deathframe   [12]=11;
t_monster_deathspeed   [12]=5;
t_monster_maxagonycount[12]=6;
t_monster_deathtype    [12]=1;

t_monster_loot[12][0][0]=50;
t_monster_loot[12][0][1]=4;
t_monster_loot[12][0][2]=1;

t_monster_loot[12][1][0]=85;
t_monster_loot[12][1][1]=3;
t_monster_loot[12][1][2]=1;

t_monster_loot[12][2][0]=75;
t_monster_loot[12][2][1]=63;
t_monster_loot[12][2][2]=40;


t_monster_hp       [ 12][0]=200;
t_monster_hp       [ 12][1]=200;
t_monster_mn       [ 12]=10;
t_monster_mv       [ 12]=300;
t_monster_str[12]=8;
t_monster_dex[12]=22;
t_monster_con[12]=15;
t_monster_int[12]=10;
t_monster_wis[12]=10;
t_monster_cha[12]=25;

t_monster_damage[12][0]=15;
t_monster_damage[12][1]=25;
t_monster_armor [12]=0;
t_monster_resist[12]=4;
t_monster_deathsound[12]=30;
sprintf(t_monster_name[12],"Goblin");
t_monster_char[12][0]='G';
t_monster_char[12][1]=50;

// SaintTeeth
t_monster_radius   [ 13]=20000;
t_monster_model    [ 13]=16;
t_monster_speed    [ 13]=600;
t_monster_stepsound[ 13]=0;
t_monster_status   [ 13]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 13]=0;     
t_monster_regen[13][0]=20;
t_monster_regen[13][1]=10;
t_monster_regen[13][2]=0;
t_monster_regen[13][3]=0;
t_monster_regen[13][4]=1;

t_monster_action    [13][0]   =14;
t_monster_action    [13][1]   =17;
t_monster_action    [13][2]   =20;

t_monster_castframe0    [13]   =8;
t_monster_meleeframe0    [13]   =8;
t_monster_warmodecount   [13]   =1;
t_monster_meleeframecount[13]   =0;

t_monster_meleeanim      [13][0]=5;
t_monster_meleeanim      [13][1]=7;
t_monster_meleeanim      [13][2]=8;

t_monster_painframe0     [13]   =10;
t_monster_painframecount [13]   =1;

t_monster_meleesound[13]=21;
t_monster_painsound [13]=22;
t_monster_meleerange[13]=15000;

t_monster_targetrange[13]=200000;
t_monster_height[13]=27000;

t_monster_walkframe0     [13]   =4;

t_monster_deathtype    [13]=0;

t_monster_hp       [ 13][0]=3200;
t_monster_hp       [ 13][1]=3200;
t_monster_mn       [ 13]=1000;
t_monster_mv       [ 13]=700;
t_monster_str[13]=8;
t_monster_dex[13]=22;
t_monster_con[13]=5;
t_monster_int[13]=10;
t_monster_wis[13]=10;
t_monster_cha[13]=25;

t_monster_damage[13][0]=15;
t_monster_damage[13][1]=75;
t_monster_mdamage[13][0]=15;
t_monster_mdamage[13][1]=35;

t_monster_armor [13]=40;
t_monster_resist[13]=34;
sprintf(t_monster_name[13],"SaintTeeth");
t_monster_char[13][0]='@';
t_monster_char[13][1]=70;


// Cave Viper
t_monster_radius   [ 14]=20000;
t_monster_model    [ 14]=28;
t_monster_speed    [ 14]=500;
t_monster_stepsound[ 14]=0;
t_monster_status   [ 14]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 14]=1;     
t_monster_regen[14][0]=32;
t_monster_regen[14][1]=5;
t_monster_regen[14][2]=0;
t_monster_regen[14][3]=0;
t_monster_regen[14][4]=1;


t_monster_meleeframe0    [14]   =4;
t_monster_warmodecount   [14]   =1;
t_monster_meleeframecount[14]   =1;

t_monster_meleeanim      [14][0]=5;
t_monster_meleeanim      [14][1]=14;
t_monster_meleeanim      [14][2]=20;

t_monster_painframe0     [14]   =6;
t_monster_painframecount [14]   =2;
t_monster_castframe0     [14]   =4;

t_monster_meleesound[14]=21;
t_monster_painsound [14]=22;
t_monster_meleerange[14]=15000;

t_monster_targetrange[14]=200000;
t_monster_height[14]=27000;

t_monster_walkframe0     [14]   =0;

t_monster_deathframe   [14]=8;
t_monster_deathspeed   [14]=3;
t_monster_deathtype    [14]=1;

t_monster_loot[14][0][0]=79;
t_monster_loot[14][0][1]=12;
t_monster_loot[14][0][2]=1;

t_monster_loot[14][1][0]=85;
t_monster_loot[14][1][1]=4;
t_monster_loot[14][1][2]=1;

t_monster_loot[14][2][0]=75;
t_monster_loot[14][2][1]=63;
t_monster_loot[14][2][2]=80;


t_monster_hp       [ 14][0]=400;
t_monster_hp       [ 14][1]=400;
t_monster_mn       [ 14]=100;
t_monster_mv       [ 14]=300;
t_monster_str[14]=8;
t_monster_dex[14]=22;
t_monster_con[14]=10;
t_monster_int[14]=10;
t_monster_wis[14]=10;
t_monster_cha[14]=50;

t_monster_damage[14][0]=15;
t_monster_damage[14][1]=55;
t_monster_mdamage[14][0]=80;

t_monster_action[14][1]=23;

t_monster_armor [14]=15;
t_monster_resist[14]=15;
t_monster_deathsound[14]=33;
sprintf(t_monster_name[14],"Cave Viper");
t_monster_char[14][0]='S';
t_monster_char[14][1]=111;


// Leech Titan
t_monster_radius   [ 15]=25000;
t_monster_model    [ 15]=29;
t_monster_speed    [ 15]=360;
t_monster_stepsound[ 15]=0;
t_monster_status   [ 15]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 15]=1;     
t_monster_regen[15][0]=64;
t_monster_regen[15][1]=25;
t_monster_regen[15][2]=0;
t_monster_regen[15][3]=0;
t_monster_regen[15][4]=1;


t_monster_meleeframe0    [15]   =6;
t_monster_warmodecount   [15]   =1;
t_monster_meleeframecount[15]   =1;

t_monster_meleeanim      [15][0]=8;
t_monster_meleeanim      [15][1]=16;
t_monster_meleeanim      [15][2]=24;

t_monster_painframe0     [15]   =4;
t_monster_painframecount [15]   =2;
t_monster_castframe0     [15]   =6;

t_monster_meleesound[15]=21;
t_monster_painsound [15]=20;
t_monster_meleerange[15]=15000;

t_monster_targetrange[15]=500000;
t_monster_height[15]=40000;

t_monster_walkframe0     [15]   =0;

t_monster_deathframe   [15]=6;
t_monster_deathspeed   [15]=3;
t_monster_deathtype    [15]=5;

t_monster_loot[15][0][0]=0;
t_monster_loot[15][0][1]=12;
t_monster_loot[15][0][2]=1;

t_monster_loot[15][1][0]=0;
t_monster_loot[15][1][1]=4;
t_monster_loot[15][1][2]=1;

t_monster_loot[15][2][0]=0;
t_monster_loot[15][2][1]=63;
t_monster_loot[15][2][2]=80;


t_monster_hp       [ 15][0]=8000;
t_monster_hp       [ 15][1]=2000;
t_monster_mn       [ 15]=100;
t_monster_mv       [ 15]=600;
t_monster_str[15]=8;
t_monster_dex[15]=22;
t_monster_con[15]=20;
t_monster_int[15]=10;
t_monster_wis[15]=10;
t_monster_cha[15]=2500;

t_monster_damage[15][0]=10;
t_monster_damage[15][1]=270;
t_monster_mdamage[15][0]=100;

t_monster_action[15][1]=23;
t_monster_action[15][2]=24;

t_monster_armor [15]=0;
t_monster_resist[15]=0;
t_monster_deathsound[15]=34;

sprintf(t_monster_name[15],"Titan Leech");
t_monster_char[15][0]='W';
t_monster_char[15][1]=111;

// Lunatic
t_monster_radius   [ 16]=20000;
t_monster_model    [ 16]=30;
t_monster_speed    [ 16]=400;
t_monster_stepsound[ 16]=0;
t_monster_status   [ 16]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 16]=2;     
t_monster_regen[16][0]=20;
t_monster_regen[16][1]=1;
t_monster_regen[16][2]=0;
t_monster_regen[16][3]=0;
t_monster_regen[16][4]=1;


t_monster_meleeframe0    [16]   =10;
t_monster_warmodecount   [16]   =1;
t_monster_meleeframecount[16]   =1;

t_monster_meleeanim      [16][0]=2;
t_monster_meleeanim      [16][1]=7;
t_monster_meleeanim      [16][2]=14;

t_monster_painframe0     [16]   =8;
t_monster_painframecount [16]   =2;

t_monster_meleesound[16]=21;
t_monster_painsound [16]=22;
t_monster_meleerange[16]=15000;

t_monster_targetrange[16]=170000;
t_monster_height[16]=27000;

t_monster_walkframe0     [16]   =4;

t_monster_deathframe   [16]=12;
t_monster_deathspeed   [16]=5;
t_monster_maxagonycount[16]=12;
t_monster_deathtype    [16]=1;

t_monster_loot[16][0][0]=30;
t_monster_loot[16][0][1]=5;
t_monster_loot[16][0][2]=1;

t_monster_loot[16][1][0]=20;
t_monster_loot[16][1][1]=32;
t_monster_loot[16][1][2]=1;

t_monster_loot[16][2][0]=60;
t_monster_loot[16][2][1]=63;
t_monster_loot[16][2][2]=100;


t_monster_hp       [ 16][0]=1500;
t_monster_hp       [ 16][1]=200;
t_monster_mn       [ 16]=10;
t_monster_mv       [ 16]=300;
t_monster_str[16]=8;
t_monster_dex[16]=22;
t_monster_con[16]=15;
t_monster_int[16]=10;
t_monster_wis[16]=10;
t_monster_cha[16]=70;

t_monster_damage[16][0]=200;
t_monster_damage[16][1]=350;
t_monster_armor [16]=60;
t_monster_resist[16]=0;
t_monster_deathsound[16]=35;

sprintf(t_monster_name[16],"Lunatic Infidel");
t_monster_char[16][0]='L';
t_monster_char[16][1]=50;

// Infidel Soldier
t_monster_radius   [ 17]=10000;
t_monster_model    [ 17]=31;
t_monster_speed    [ 17]=400;
t_monster_stepsound[ 17]=0;
t_monster_status   [ 17]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 17]=2;     
t_monster_regen[17][0]=20;
t_monster_regen[17][1]=1;
t_monster_regen[17][2]=0;
t_monster_regen[17][3]=0;
t_monster_regen[17][4]=1;


t_monster_shootdelay     [17]   =16;
t_monster_shootframe     [17]   =10;
t_monster_painframe0     [17]   =8;
t_monster_painframecount [17]   =2;

t_monster_painsound [17]=22;
t_monster_meleerange[17]=15000;

t_monster_targetrange[17]=200000;
t_monster_height[17]=27000;

t_monster_walkframe0     [17]   =4;

t_monster_deathframe   [17]=11;
t_monster_deathspeed   [17]=5;
t_monster_maxagonycount[17]=12;
t_monster_deathtype    [17]=1;

t_monster_loot[17][0][0]=30;
t_monster_loot[17][0][1]=5;
t_monster_loot[17][0][2]=1;

t_monster_loot[17][1][0]=75;
t_monster_loot[17][1][1]=62;
t_monster_loot[17][1][2]=8;

t_monster_loot[17][2][0]=60;
t_monster_loot[17][2][1]=63;
t_monster_loot[17][2][2]=100;


t_monster_hp       [ 17][0]=900;
t_monster_hp       [ 17][1]=100;
t_monster_mn       [ 17]=10;
t_monster_mv       [ 17]=300;
t_monster_str[17]=8;
t_monster_dex[17]=22;
t_monster_con[17]=1;
t_monster_int[17]=10;
t_monster_wis[17]=10;
t_monster_cha[17]=60;

t_monster_shoottype[17]=0;

t_monster_shootdamage[17][0]=50;
t_monster_shootdamage[17][1]=77;

t_monster_action [17][0]=1;
t_monster_action [17][1]=1;
t_monster_action [17][2]=1;
t_monster_action [17][3]=1;

t_monster_armor [17]=30;
t_monster_resist[17]=25;
t_monster_deathsound[17]=35;

sprintf(t_monster_name[17],"Infidel Soldier");
t_monster_char[17][0]='@';
t_monster_char[17][1]=50;

// Infidel Officer
t_monster_radius   [ 18]=10000;
t_monster_model    [ 18]=32;
t_monster_speed    [ 18]=400;
t_monster_stepsound[ 18]=0;
t_monster_status   [ 18]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 18]=2;     
t_monster_regen[18][0]=20;
t_monster_regen[18][1]=1;
t_monster_regen[18][2]=0;
t_monster_regen[18][3]=0;
t_monster_regen[18][4]=1;


t_monster_shootdelay     [18]   =5;
t_monster_shootframe     [18]   =10;
t_monster_painframe0     [18]   =8;
t_monster_painframecount [18]   =2;

t_monster_painsound [18]=22;
t_monster_meleerange[18]=15000;

t_monster_targetrange[18]=200000;
t_monster_height[18]=27000;

t_monster_walkframe0     [18]   =4;

t_monster_deathframe   [18]=11;
t_monster_deathspeed   [18]=5;
t_monster_maxagonycount[18]=12;
t_monster_deathtype    [18]=1;

t_monster_loot[18][0][0]=30;
t_monster_loot[18][0][1]=6;
t_monster_loot[18][0][2]=1;

t_monster_loot[18][1][0]=75;
t_monster_loot[18][1][1]=61;
t_monster_loot[18][1][2]=13;

t_monster_loot[18][2][0]=60;
t_monster_loot[18][2][1]=63;
t_monster_loot[18][2][2]=100;


t_monster_hp       [ 18][0]=2000;
t_monster_hp       [ 18][1]=500;
t_monster_mn       [ 18]=10;
t_monster_mv       [ 18]=300;
t_monster_str[18]=8;
t_monster_dex[18]=22;
t_monster_con[18]=30;
t_monster_int[18]=10;
t_monster_wis[18]=10;
t_monster_cha[18]=200;

t_monster_shoottype[18]=1;

t_monster_shootdamage[18][0]=15;
t_monster_shootdamage[18][1]=100;


t_monster_action [18][0]=1;
t_monster_action [18][1]=1;
t_monster_action [18][2]=1;
t_monster_action [18][3]=1;

t_monster_armor [18]=45;
t_monster_resist[18]=15;
t_monster_deathsound[18]=35;

sprintf(t_monster_name[18],"Officer Infidel");
t_monster_char[18][0]='@';
t_monster_char[18][1]=55;


// Elf Paladin
t_monster_radius   [ 19]=20000;
t_monster_model    [ 19]=34;
t_monster_speed    [ 19]=280;
t_monster_stepsound[ 19]=0;
t_monster_status   [ 19]=STATUS_ALIVE | STATUS_AI;
t_monster_side     [ 19]=2;     
t_monster_regen[19][0]=20;
t_monster_regen[19][1]=1;
t_monster_regen[19][2]=0;
t_monster_regen[19][3]=0;
t_monster_regen[19][4]=1;


t_monster_castframe0     [19]   =10;
t_monster_meleeframe0    [19]   =10;
t_monster_warmodecount   [19]   =1;
t_monster_meleeframecount[19]   =1;

t_monster_meleeanim      [19][0]=2;
t_monster_meleeanim      [19][1]=7;
t_monster_meleeanim      [19][2]=14;

t_monster_painframe0     [19]   =8;
t_monster_painframecount [19]   =2;

t_monster_mdamage[19][0]=50;

t_monster_meleesound[19]=21;
t_monster_painsound [19]=22;
t_monster_meleerange[19]=15000;

t_monster_targetrange[19]=200000;
t_monster_height[19]=27000;

t_monster_walkframe0     [19]   =4;

t_monster_deathframe   [19]=12;
t_monster_deathspeed   [19]=5;
t_monster_maxagonycount[19]=5;
t_monster_deathtype    [19]=1;

t_monster_loot[19][0][0]=30;
t_monster_loot[19][0][1]=5;
t_monster_loot[19][0][2]=1;

t_monster_loot[19][1][0]=20;
t_monster_loot[19][1][1]=9;
t_monster_loot[19][1][2]=1;

t_monster_loot[19][2][0]=60;
t_monster_loot[19][2][1]=63;
t_monster_loot[19][2][2]=120;


t_monster_hp       [ 19][0]=1000;
t_monster_hp       [ 19][1]=500;
t_monster_mn       [ 19]=10;
t_monster_mv       [ 19]=800;
t_monster_str[19]=8;
t_monster_dex[19]=22;
t_monster_con[19]=15;
t_monster_int[19]=10;
t_monster_wis[19]=10;
t_monster_cha[19]=100;

t_monster_action[19][1]=10;
t_monster_action[19][2]=6;


t_monster_damage[19][0]=100;
t_monster_damage[19][1]=300;
t_monster_armor [19]=50;
t_monster_resist[19]=40;
t_monster_deathsound[19]=35;
t_monster_char[19][0]='E';
t_monster_char[19][1]=55;
sprintf(t_monster_name[19],"Elven Paladin");

// MotherLand
t_monster_radius   [ 20]=22000;
t_monster_model    [ 20]=35;
t_monster_speed    [ 20]=200;
t_monster_status   [ 20]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 20]=1;


t_monster_deathtype      [ 20]   =5;

t_monster_castframe0     [20]   =4;
t_monster_meleeframe0    [20]   =4;
t_monster_warmodecount   [20]   =1;
t_monster_meleeframecount[20]   =1;

t_monster_meleeanim      [20][0]=8;
t_monster_meleeanim      [20][1]=16;
t_monster_meleeanim      [20][2]=24;

t_monster_painframe0     [20]   =6;
t_monster_painframecount [20]   =2;

t_monster_walkframe0     [ 20]   =0;

t_monster_meleesound[20]=21;
t_monster_painsound [20]=22;
t_monster_meleerange[20]=25000;

t_monster_targetrange[20]=190000;
t_monster_height[20]=40000;

t_monster_regen[20][0]=0;
t_monster_regen[20][1]=0;
t_monster_regen[20][2]=0;
t_monster_regen[20][3]=0;
t_monster_regen[20][4]=0;

t_monster_hp       [ 20][0]=32000;
t_monster_hp       [ 20][1]=0;
t_monster_mn       [ 20]=1000;
t_monster_mv       [ 20]=5000;
t_monster_str[20]=50;
t_monster_dex[20]=50;
t_monster_con[20]=25;
t_monster_int[20]=50;
t_monster_wis[20]=50;
t_monster_cha[20]=0;

t_monster_action[20][0]=0;
t_monster_action[20][1]=19;
t_monster_action[20][2]=26;

t_monster_damage[20][0]=100;
t_monster_damage[20][1]=1750;
t_monster_mdamage[20][0]=40;
t_monster_mdamage[20][1]=5;

t_monster_damage[20][0]=25;
t_monster_damage[20][1]=80;
t_monster_armor [20]=60;
t_monster_resist[20]=60;
t_monster_deathsound[20]=34;

t_monster_char[20][0]='W';
t_monster_char[20][1]=231;
sprintf(t_monster_name[20],"Fucking MotherLand");

// Halobane
t_monster_deathsound[21]=35;

t_monster_radius   [ 21]=15000;
t_monster_model    [ 21]=7;
t_monster_speed    [ 21]=450;
t_monster_status   [ 21]=STATUS_ALIVE | STATUS_AI | STATUS_BOSS;
t_monster_side     [ 21]=3;

t_monster_action    [ 21][0]=1;
t_monster_action    [ 21][1]=1;
t_monster_action    [ 21][2]=1;

t_monster_walkframe0     [ 21]   =4;
t_monster_shootframe[21]=9;
t_monster_shoottype[21]=0;
t_monster_shootdelay[21]=32;
t_monster_shootdamage[21][0]=150;
t_monster_shootdamage[21][1]=250;

t_monster_painframe0     [ 21]   =8;
t_monster_painframecount [ 21]   =0;

t_monster_walkframe0     [ 21]   =4;

t_monster_painsound [21]=22;
t_monster_meleerange[21]=15000;

t_monster_targetrange[21]=200000;
t_monster_height[21]=30000;

t_monster_regen[21][0]=32;
t_monster_regen[21][1]=2;
t_monster_regen[21][2]=16;
t_monster_regen[21][3]=1;
t_monster_regen[21][4]=0;

t_monster_hp       [ 21][0]=20000;
t_monster_mn       [ 21]=10000;
t_monster_mv       [ 21]=300;
t_monster_str[21]=16;
t_monster_dex[21]=20;
t_monster_con[21]=16;
t_monster_int[21]=12;
t_monster_wis[21]=18;
t_monster_cha[21]=10000;

t_monster_deathtype[21]=2;
t_monster_damage[21][0]=10;
t_monster_damage[21][1]=40;
t_monster_armor [21]=60;
t_monster_resist[21]=0;


sprintf(t_monster_name[21],"Halobane");
t_monster_char[21][0]='@';
t_monster_char[21][1]=231;
//


for (Uint8 i=0;i<32;i++)
{
t_monster_mv0[i]=t_monster_mv[i]/4;
t_monster_mv1[i]=t_monster_mv[i]/2;
    
t_monster_speed0[i]=t_monster_speed[i]/2;
t_monster_speed1[i]=t_monster_speed[i]*3/4;
}


}


void spawnmonster(unsigned short int x,unsigned short int y,unsigned short int z,unsigned short int index)
{
Uint8 spawn_accept,new_monster;

spawn_accept=1;
new_monster=0;// upgrade immidetialy
while ((new_monster<15)&(monster_ingame[new_monster]))
 {
 new_monster++;   
 }
if (new_monster==16)
{
new_monster=1;                    
while ((new_monster<15)&(monster_ingame[new_monster])&(monster_status[new_monster]&STATUS_BOSS))
 {
 new_monster++;   
 }
if (new_monster==16) new_monster=3+random(10);
}

if (spawn_accept)
  {
  monster_ingame[new_monster]=1;
  monster_anim[new_monster]=1;

  monster_cx[new_monster]=x;
  monster_cy[new_monster]=y;
  monster_cz[new_monster]=z;
  monster_x[new_monster]=x*65536+32768;
  monster_y[new_monster]=y*65536+32768;
  monster_z[new_monster]=z*65536+3000;
  monster_ix[new_monster]=0;
  monster_iy[new_monster]=0;
  monster_iz[new_monster]=0;
  monster_angle[new_monster]=random(4096);
  monster_anglex[new_monster]=0;
  monster_anglez[new_monster]=0;

  monster_hasted[new_monster]=0;
  monster_blessed[new_monster]=0;
  monster_ill[new_monster]=0;
  monster_poisoned[new_monster]=0;
  monster_confuzed[new_monster]=0;
  monster_magicarmor[new_monster]=0;
  monster_shielded[new_monster]=0;
  monster_invisible[new_monster]=0;
  monster_slowed[new_monster]=0;
  monster_charmed[new_monster]=0;

  monster_radius[new_monster]=t_monster_radius[index];
  monster_model[new_monster]=t_monster_model[index];
  monster_speed[new_monster]=t_monster_speed[index];

  monster_type[new_monster]=index;
  monster_action[new_monster]=0;

  monster_status[new_monster]=t_monster_status[index];

if (new_monster==0)
  monster_status[new_monster]=(monster_status[new_monster] & (STATUS_ALIVE | STATUS_FLOATING | STATUS_TANK | STATUS_BOSS | STATUS_WORM | STATUS_UNDEAD | STATUS_CRAWLING));
  
  if (t_monster_side[index]<16)
  monster_side[new_monster]=t_monster_side[index];
  else
    monster_side[new_monster]=16+new_monster;

if (t_monster_hp[index][1])
  monster_hp[new_monster]=t_monster_hp[index][0]+random(t_monster_hp[index][1]+1);
  else
  monster_hp[new_monster]=t_monster_hp[index][0];

  monster_mhp[new_monster]=monster_hp[new_monster];
  
  monster_mn[new_monster]=t_monster_mn[index];
  monster_mv[new_monster]=t_monster_mv[index];

  monster_modelcolor[new_monster]=0;
  monster_ai_target[new_monster]=16;
  monster_ai_state[new_monster]=0;
  monster_ai_action[new_monster]=0;
  monster_ai_delay[new_monster]=5;
  monster_healed[new_monster]=0;
  monster_flood_score[new_monster]=0;
  
  monster_deathtrigger[new_monster]=deathtrigger;
  deathtrigger=0;
  monster_visible[new_monster]=1;
  monster_blinkcount[new_monster]=0;

  monster_anglez[new_monster]=0;
  monster_anglex[new_monster]=0;

  monster_pause[new_monster]=0;
  monster_frame0[new_monster]=0;
  monster_frame1[new_monster]=0;
  
  monster_respawn[new_monster]=0;
  monster_roomi[new_monster]=x;
  Sint32 t=y;
  monster_roomi[new_monster]+=t*128;
  t=z;
  monster_roomi[new_monster]+=t*16384;
  
  if (mapobj[monster_roomi[new_monster]]==monster_type[new_monster]+1)
  {
   
//  if (monster_status[new_monster]&STATUS_BOSS==0)
   {
   monster_respawn[new_monster]=1;                                                                                       
   monster_respawni[new_monster]=monster_roomi[new_monster];
   }
   mapobj[monster_roomi[new_monster]]=0;
  }
  
  if (t_monster_maxagonycount[index])
  {
  monster_agony[new_monster]=1+random(t_monster_maxagonycount[index]);
                             
  }
  else
  monster_agony[new_monster]=0;

  for (Uint8 z=0;z<16;z++)
  {
  table_vis[z][new_monster]=0;
  table_range[z][new_monster]=6660666;
  table_vis[new_monster][z]=0;
  table_range[new_monster][z]=6660666;
  }
    monsters++;
  }          
}

void monster_newwarmode(unsigned short int i)
{
Uint8 n;
n=monster_type[i];
     
monster_frame0[i]=t_monster_meleeframe0[n];

if (t_monster_warmodecount[n])
{
if (t_monster_warmodecount[n]==1)
{
                                 
}
else
if (t_monster_warmodecount[n]==2)
monster_warmode[i]=(monster_warmode[i]+1)%t_monster_warmodecount[n];
else
monster_warmode[i]=(monster_warmode[i]+1+random(t_monster_warmodecount[n]-1))%t_monster_warmodecount[n];
 monster_frame0[i]+=(monster_warmode[i]);
}
monster_frame1[i]=monster_frame0[i];
}

void monster_newmelee(unsigned short int i)
{
Uint8 n;
n=monster_type[i];
     
monster_frame0[i]=t_monster_meleeframe0[n]+t_monster_warmodecount[n];

if (t_monster_meleeframecount[n])
{
if (t_monster_meleeframecount[n]==1)
{
}
else
{
if (t_monster_meleeframecount[n]==2)
monster_melee[i]=(monster_melee[i]+1)%t_monster_meleeframecount[n];
else
monster_melee[i]=(monster_melee[i]+1+random(t_monster_meleeframecount[n]-1))%t_monster_meleeframecount[n];

 monster_frame0[i]+=(monster_melee[i]);
}
}
monster_frame1[i]=monster_frame0[i];
}
void monster_newpain(unsigned short int i)
{
Uint8 n;
n=monster_type[i];
     
monster_frame0[i]=t_monster_painframe0[n];

if (t_monster_painframecount[n])
{
if (t_monster_painframecount[n]==1)
{}
else
{
if (t_monster_painframecount[n]==2)
monster_pain[i]=(monster_pain[i]+1)%2;
else
{monster_pain[i]=(monster_pain[i]+1+random(t_monster_painframecount[n]-1))%t_monster_painframecount[n];
}
 monster_frame0[i]+=(monster_pain[i]);
}
}
monster_frame1[i]=monster_frame0[i];
}


void monster_attack(unsigned short int i)
{
Uint8 n;
monster_action[i]=2;
monster_actioncount[i]=0;
n=monster_type[i];
if (monster_mv[i]<t_monster_mv0[monster_type[i]])
monster_pause[i]=t_monster_meleeanim[n][2]+t_monster_meleeanim[n][2]-t_monster_meleeanim[n][1];     
else
monster_pause[i]=t_monster_meleeanim[n][2];     

if (i>0) if (monster_ai_target[i]<16)monster_angle[i]=table_angle[i][monster_ai_target[i]];
monster_newwarmode(i);
}
void monster_kill(Uint8 i)
{
monsters--;
monster_ingame[i]=0;
if (monster_respawn[i]) mapobj[monster_respawni[i]]=monster_type[i]+1;

for (Uint8 n=0;n<16;n++)
if (n!=i)
if (monster_ai_target[n]==i) monster_ai_target[n]=16;
     
}

void monster_shoot(Uint8 i)
{
monster_animcount[i]=0;
if (i==0) rcamera[3]=SuperAngle(rcamera[3]+random(14));
Uint8 type=monster_type[i];
Sint32 ix,iy,iz;
Uint8 k;
monster_angle[i]=SuperAngle(monster_angle[i]);
ix=f_cos[monster_angle[i]];
iy=f_sin[monster_angle[i]];
switch (t_monster_shoottype[type])
{
case 0://9mm handgun
sPlaySound(23,80+random(48),80+random(48));
field0_x=monster_x[i]-iy/8+ix/4;       
field0_y=monster_y[i]+ix/8+iy/4;        
field0_z=t_monster_height[type]+monster_z[i]-2000;        
field0_ix=-iy/16-400+random(800);        
field0_iy=ix/16-400+random(800);        
field0_iz=-2000;
field0_index=232;        
field0_w=1500;
field0_iw=random(250);
SpawnField();        
field0_x=monster_x[i]-iy/8+ix/3;       
field0_y=monster_y[i]+ix/8+iy/3;        
field0_z=t_monster_height[type]+monster_z[i];        
field0_ix=ix/24-200+random(400);        
field0_iy=iy/24-200+random(400);        
field0_iz=1200;
field0_index=240;        
field0_w=14000;
field0_iw=random(800);
SpawnField();        
drain_MV(i,6);
monster_ix[i]-=ix>>9;
monster_iy[i]-=iy>>9;
break;
case 1://assault rfile
sPlaySound(23,80+random(48),80+random(48));
field0_x=monster_x[i]-iy/8+ix/4;       
field0_y=monster_y[i]+ix/8+iy/4;        
field0_z=t_monster_height[type]+monster_z[i];        
field0_ix=-iy/16-400+random(800);        
field0_iy=ix/16-400+random(800);        
field0_iz=-2000;
field0_index=232;        
field0_w=2000;
field0_iw=random(500);
SpawnField();        
field0_x=monster_x[i]-iy/8+ix/2;       
field0_y=monster_y[i]+ix/8+iy/2;        
field0_z=t_monster_height[type]+monster_z[i];        
field0_ix=-ix/12-200+random(400);        
field0_iy=-iy/12-200+random(400);        
field0_iz=1000;
field0_index=240;        
field0_w=10000;
field0_iw=random(3000);
SpawnField();        
drain_MV(i,5);
monster_ix[i]-=ix>>8;
monster_iy[i]-=iy>>8;
break;
case 2://rocket launcher
sPlaySound(24,128,128);
field0_x=monster_x[i]-iy/8+ix/2;       
field0_y=monster_y[i]+ix/8+iy/2;        
field0_z=t_monster_height[type]+monster_z[i];        
field0_ix=-ix/12-200+random(400);        
field0_iy=-iy/12-200+random(400);        
field0_iz=1000;
field0_index=240;        
field0_w=10000;
field0_iw=random(3000);
SpawnField();        
drain_MV(i,100);
monster_ix[i]-=ix>>8;
monster_iy[i]-=iy>>8;

k=monster_ai_target[i];
//if (i==0)
{Uint8 m=table_range[i][k]>>14;
ix=ix>>2;
iy=iy>>2;
iz=(t_monster_height[monster_type[k]]-t_monster_height[type]+monster_z[k]-monster_z[i])>>2;
if (table_range[i][k])
for (Sint8 n=0;n<m;n++)
 {
field0_x=monster_x[i]+ix*n;       
field0_y=monster_y[i]+iy*n;        
field0_z=t_monster_height[type]+monster_z[i]+iz*n;        
field0_ix=-ix>>3;        
field0_iy=-iy>>3;        
field0_iz=0;
field0_index=240;        
field0_w=20000;
field0_iw=random(3000);
SpawnField();        
 }
}
field0_x=monster_x[k];       
field0_y=monster_y[k];        
field0_z=t_monster_height[monster_type[k]]+monster_z[k];        
field0_ix=0;        
field0_iy=0;        
field0_iz=2000;
field0_index=240;        
field0_w=40000;
field0_iw=1000+random(3000);
SpawnField();        

break;
case 3://Plasma Gun
sPlaySound(25,80+random(48),80+random(48));
field0_x=monster_x[i]-iy/8+ix/2;       
field0_y=monster_y[i]+ix/8+iy/2;        
field0_z=t_monster_height[type]+monster_z[i];        
field0_ix=-ix/12-500+random(1000);        
field0_iy=-iy/12-500+random(1000);        
field0_iz=1000;
field0_index=224;        
field0_w=10000;
field0_iw=random(5000);
SpawnField();        
drain_MV(i,25);
monster_ix[i]-=ix>>8;
monster_iy[i]-=iy>>8;

k=monster_ai_target[i];
if (i==0)
{
Uint8 m=table_range[i][k]>>14;
ix=ix>>2;
iy=iy>>2;
iz=(t_monster_height[monster_type[k]]-t_monster_height[type]+monster_z[k]-monster_z[i])>>2;
if (table_range[i][k])
for (Sint8 n=0;n<m;n++)
 {
field0_x=monster_x[i]+ix*n;       
field0_y=monster_y[i]+iy*n;        
field0_z=t_monster_height[type]+monster_z[i]+iz*n;        
field0_ix=-ix>>3-500+random(1000);        
field0_iy=-iy>>3-500+random(1000);        
field0_iz=-1000;
field0_index=224;        
field0_w=10000;
field0_iw=random(3000);
SpawnField();        
 }
}
field0_x=monster_x[k];       
field0_y=monster_y[k];        
field0_z=t_monster_height[monster_type[k]]+monster_z[k];        
field0_ix=0;        
field0_iy=0;        
field0_iz=2000;
field0_index=224;        
field0_w=20000;
field0_iw=1000+random(3000);
SpawnField();        

break;
}
if (monster_ai_target[i]<16)
 monster_angle[i]=table_angle[i][monster_ai_target[i]];

monster_action[i]=5;
if (i==0) 
{
damage_missleweapon();
handpistol=t_monster_shootdelay[0]+2;
if (monster_mv[0]<t_monster_mv0[0]) handpistol=handpistol*2;
}
}


void monster_move(Uint8 i,Uint8 x,Uint8 y,Uint8 z)
{
monster_x[i]=x*65536+32666;
monster_y[i]=y*65536+32666;
monster_z[i]=z*65536;
if (i==0)
if (movie_mode==0)
 {
 camset(monster_x[0]/65536,monster_y[0]/65536,monster_z[0]/65536);
 camsync();
 }    
}

void Monster_Cast(Uint8 i,Uint8 target)
{
if (monster_action[i]<2)
{
Uint8 t=monster_type[i];
monster_frame0[i]=t_monster_castframe0[t];    
monster_frame1[i]=monster_frame0[i]+1;
monster_pause[i]=8;
monster_anim[i]=8;
monster_actioncount[i]=0;
monster_animcount[i]=0;
monster_action[i]=6;    

if (target<16)
if (target!=i)
if (table_vis[i][target])
 monster_angle[i]=table_angle[i][target];
}
}
