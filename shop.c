#include <shop.h>
#include <globalvar.h>
#include <sound.h>
#include <render.h>
#include <sfont.h>
#include <zmath.h>
#include <interface.h>
#include <items.h>

Uint8 shopitem[64];
const Uint32 item_price[192]=
{
//"Tonic","Restores 20 HP 100 MV",//0
20,10,0,
//"Super Tonic","Restores 40 HP 500 MV",//1
80,40,15,
//"Injection Of Mobility","Restores ALL MV + haste",//2
350,175,35,
//"Herb","Restores 50 HP",//3
25,12,0,
//"Potion","Restores 200 HP",//4
100,50,0,
//"Healing Potion","Restores 500 HP",//5
250,125,25,
//"Medi-Kit","Restores 1000 HP",//6
500,250,35,
//"X-Potion","Restores ALL HP",//7
2000,750,40,
//"Ether","Restores 50 MP",//8
90,45,0,
//"X-Ether","Restores 250 MP",//9
450,225,20,
//"Mana Potion","Restores 100 MP",//10
180,90,10,
//"Elexir","Restores ALL HP MP MV",//11
4000,1500,0,
//"Antidote","Cures 'Poison' status",//12
40,1,0,
//"Scroll Of Ice","Learn 'Ice' spell",//13
10000,1,0,
//"Scroll Of Fire","Learn 'Fire' spell",//14
10000,1,0,
//"Scroll Of Thunder","Learn 'Thunder' spell",//15
10000,1,0,
//"Bless Scroll","Casts 'bless'",//16
500,350,15,
//"Ice wand","Casts 'Ice2' on all",//17
500,250,0,
//"Fire orb","Casts 'Fire2' on all",//18
550,275,20,
//"Thunder Stone","Casts 'Thunder2' on all",//19
580,290,30,
//"Remedy","Cures all status effects",//20
340,170,20,
//"Invisiblity Potion","Great hiding effect",//21
1000,500,25,
//"GunSmith ToolBox","Repairs any gun",//22
500,1,0,
//"Blade Oil","Restores blades",//23
500,1,0,
//"Fuel Oil","For chainsaw",//24
500,1,40,
//"Panacea","Cures Diseace",//25
40,1,0,
//"Potion of Haste","Increases moving speed",//26
600,300,0,
//"Potion Of Experience","You should taste this!",//27
10000,1,35,
//"Magical Pen","Renames your character",//28
50000,1,100,
//"Doom Marine Part","Collect all 4 parts!",//29
999,1,35,
//"Scroll Of Protection","Improves defense",//30
1000,500,20,
//"GP2X","Bought at www.gp2x.co.uk",//31
10000,999,80,
//"Knife","Sharp, Maniac design",//32
600,300,0,
//"Longsword","Three feet long one",//33
900,450,10,
//"Katana","Hentai Anime Blade",//34
1500,750,20,
//"Magic Rod","Increases INT",//35
2000,1000,15,
//"Mace","Heavy and strong",//36
1250,625,18,
//"Glass Sword","Sharp but breakable",//37
600,1,30,
//"Defloration Scythe","Esoteric Inmaterial",//38
3000,1,50,
//"Chainsaw","For master lumberjacker",//39
2500,1250,35,
//"9mm Pistol","Basic handgun",//40
2000,1000,25,
//"Assault Rfile","Best missle weapon",//41
4000,2000,35,
//"Rocket Launcher","Has bonus against tanks",//42
6000,3000,45,
//"Plasma Cannon","Prototype of alien gun",//43
7000,3500,45,
//"Ring Of Protection","Increases armor",//44
2000,1000,15,
//"Ring Of Power","Increases STR and CON",//45
2000,1000,15,
//"Ring Of Magic","Increases INT and WIS",//46
2000,1000,15,
//"Amulet Of Remedy","Protects from any status",//47
2000,1000,15,
//"Sigil Of Chaos","+50 STR",//48
1500,750,20,
//"Golden Hairpin","Halves consumed MP",//49
20000,1,30,
//"Belt Of Dexterity","+45 DEX",//50
1500,750,20,
//"Ring Of Diplomacy","+100 CHA",//51
1200,600,10,
//"Leather Armor","Light armor",//52
1000,500,10,
//"Bronze Breastplate","Armor of medium defence",//53
2000,1000,25,
//"Red Quake Armor","Best body armor",//54
4000,2000,40,
//"Ring Of Mobility","Fast MV regeneration",//55
3000,1500,30,
//"Ring Of Regeneration","Regenerates HP",//56
3000,1500,30,
//"Ring Of Wisdom","+25 INT +45 WIS",//57
2500,1250,30,
//"Amulet Of Sage","+150 WIS",//58
2000,1000,35,
//"Energy Cell","Energy class ammo",//59
16,10,0,
//"Small Rocket","Rocket launcher ammo",//60
100,60,0,
//"4.75x5.00 ammo","Assault rfile bullets",//61
4,4,0,
//"9mm ammo","Ammo for handguns",//62
2,2,0,
//"Gold Coin","For general trade"//63
1,1,100
};

Uint8 shopbuf[76800];
Uint8 shopindex[64];
Uint8 shopx,shopy,keypress;
void ShopProc(void)
{
Sint32 i;
Sint32 ii,n,c,y,x;
for (i=0;i<76800;i++)
scrbuf[i]=shopbuf[i];
     

//Draw

//SHOP
for (i=0;i<7;i++)
{
 {

if (shopy<3) ii=0;
else
if (shopy<60) ii=shopy-3;
else
ii=57;

n=shopindex[ii+i];


if (shopx==0)
if (i==-ii+shopy) 
{
Uint16 k;
 for (y=66+i*12;y<78+i*12;y+=2)
 for (k=10;k<140;k+=2)
 {
 scrbuf[k+y*320]=16;    
 scrbuf[k+y*320+321]=16;     
 }
}

if (n<64)
{
if (shopy==i+ii) c=90+count/2%2;else c=28-zabs(i-3);

l_textstring=sprintf(s_textstring,"%s",item_s[n*2]);

s_drawtext(20,67+i*12,17);               
s_drawtext(20,66+i*12,c);               


}
}
}
//ITEMS
for (i=0;i<7;i++)
{
 {

if (chmenu_y[1]<3) ii=0;
else
if (chmenu_y[1]<60) ii=chmenu_y[1]-3;
else
ii=57;

n=item_p[ii+i];


if (shopx==1)
if (i==-ii+chmenu_y[1]) 
{
Uint16 k;
 for (y=66+i*12;y<78+i*12;y+=2)
 for (k=150;k<310;k+=2)
 {
 scrbuf[k+y*320]=16;    
 scrbuf[k+y*320+321]=16;     
 }
}

if (n<64)
if (item_c[n])
{



if (n==item_p[chmenu_y[1]]) c=90+count/2%2;else c=28-zabs(i-3);

if (((n==player_arm[0])|(n==player_arm[1])|(n==player_arm[2]))&(n>0))
l_textstring=sprintf(s_textstring,"+%s",item_s[n*2]);
else
l_textstring=sprintf(s_textstring,"%s",item_s[n*2]);

s_drawtext(160,67+i*12,17);               
s_drawtext(160,66+i*12,c);               


l_textstring=sprintf(s_textstring,"%i",item_c[n]);
s_drawtext(300-5*l_textstring,67+i*12,17);               
s_drawtext(300-5*l_textstring,66+i*12,c);               
}
}
}
//item selected

if (shopx)
{
n=item_p[chmenu_y[1]];
if (n<64)
if (item_c[n]==0) n=64;
}
else
n=shopindex[shopy];

Sint32 price=0;
Uint8 cursoritem=n;
if (n<63)
{
for (x=0;x<16;x++)
for (y=0;y<16;y++)
{
Uint8 c=Tile[(160+n)*256+x+y*16];
Uint32 z;
z=156+x*2+(172+y*2)*320;
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
if (shopx==0) price=-item_price[n*3];else price=item_price[n*3+1];


if (cursoritem<63)
if (price>0)
if (cursoritem>=32)
if (item_c[cursoritem]==1)
if (player_arm[0]==cursoritem | player_arm[1]==cursoritem | player_arm[2]==cursoritem)
{
cursoritem=64;
price=0;                         
}

if (cursoritem<63)
if (price>0)
if ((cursoritem>=32)&(cursoritem<44))
if (item_c[cursoritem]==1)
if (player_arm[0]==cursoritem | player_arm[1]==cursoritem | player_arm[2]==cursoritem | weapon_points[cursoritem-32]<1000)
{
cursoritem=64;
price=0;                         
}

if (price>0)
{
l_textstring=sprintf(s_textstring,"SELL %i",price);
s_drawtext2(21,173,16);               
s_drawtext2(20,172,31);               
}
else
{
l_textstring=sprintf(s_textstring,"%i GP",-price);
s_drawtext2(141-l_textstring*10,173,16);               
s_drawtext2(140-l_textstring*10,172,31);               
}


l_textstring=sprintf(s_textstring,"%s",item_s[n*2]);
s_drawtext(190,173,18);               
s_drawtext(191,172,30);               

l_textstring=sprintf(s_textstring,"%s",item_s[n*2+1]);
s_drawtext(180,185,18);               
s_drawtext(181,184,26);               

l_textstring=sprintf(s_textstring,"You have %i",item_c[n]);
s_drawtext(305-l_textstring*5,195,18);               
s_drawtext(304-l_textstring*5,196,30);               
}       


l_textstring=sprintf(s_textstring,"SHOP");
s_drawtext2(21,37,16);               
if (shopx==0)
s_drawtext2(20,36,90);
else
s_drawtext2(20,36,20);

l_textstring=sprintf(s_textstring,"INVENTORY");
s_drawtext2(211,37,16);               
if (shopx==1)
s_drawtext2(210,36,90);
else
s_drawtext2(210,36,20);

l_textstring=sprintf(s_textstring,"Welcome to the SHOP");
s_drawtext2(11,7,16);               
s_drawtext2(10,8,30);

l_textstring=sprintf(s_textstring,"%i GP",item_c[63]);
s_drawtext2(311-l_textstring*10,215,16);               
s_drawtext2(310-l_textstring*10,214,90);


//Shop Control 3000

/*
if ((n>=32)&(n<44))
  {
l_textstring=sprintf(s_textstring,"%i%c",weapon_points[n-32]/10,37);
s_drawtext(260-5*l_textstring,55+i*12,17);               
s_drawtext(260-5*l_textstring,54+i*12,c);               
  }
*/
if (count%2)
{
if (controlpad.button[PAD_A] | controlpad.button[PAD_B] | controlpad.button[PAD_X] | controlpad.button[PAD_Y])
 {
 if (keypress==0 | keypress>3)
 {
 if (cursoritem<63)
  {
  if (price>0)
   {
   LoseItem(cursoritem);
   AddItem(63,price);     
   sPlaySound(0,40,70);
   }
   else
  if (price<0)
   if (item_c[63]<-price)
   {
   sPlaySound(1,128,128);
                        
   keypress=1;                      
   }
   else
   {
   LoseGold(-price);
   AddItem(cursoritem,1);     
   sPlaySound(0,70,40);
   }
   
                   
  }
 }
 if (keypress<100)
 keypress++;                            
 } 
 else
 keypress=0;
}


if (controlpad.button[PAD_START])
{
sPlaySound(3,128,128);
NextMusicTrack(levelmusictrack);
NewGameMode=GAME;
GameMode=GAME;
}

if (count%2)
 {
 if (controlpad.angle==2 | controlpad.button[PAD_R1])
  if (shopx==0)
  {
  shopx++;
  sPlaySound(0,0,128);
  }
 if (controlpad.angle==6 | controlpad.button[PAD_L1])
  if (shopx==1)
  {
  shopx--;
  sPlaySound(0,128,0);
  }
  


if (shopx)
 {
 if (controlpad.angle==0)
  {
  if (chmenu_y[1])
  {
  chmenu_y[1]--;
  sPlaySound(0,60,50);
  }
  }
  else
 if (controlpad.angle==4)
  {
  if (chmenu_y[1]<63)
  {
  chmenu_y[1]++;
  sPlaySound(0,50,60);
  }
  }
 }
 else             
 {
  if (controlpad.angle==0)
  {
  if (shopy)
  {
  shopy--;
  sPlaySound(0,60,50);
  }
  }
  else
 if (controlpad.angle==4)
  {
  if (shopy<63)
  {
  shopy++;
  sPlaySound(0,50,60);
  }
  }
 }

 }

}
void EnterShop(void)
{
sPlaySound(4,128,128);
Uint32 i,n;

for (i=0;i<64;i++)
shopindex[i]=64;
n=0;
for (i=0;i<64;i++)
if (item_price[i*3+2]<=ch_level)
{
shopindex[n]=i;
n++;
}



indicator_count[0]=0;     
indicator_count[1]=0;
indicator_count[2]=0;
indicator_count[3]=0;

renderscene();
for (i=0;i<76800;i++)
shopbuf[i]=scrbuf[i];

Uint32 x,y;

for (x=150;x<310;x++)
for (y=40;y<209;y++)
shopbuf[x+y*320]=16;

for (x=153;x<307;x++)
for (y=43;y<207;y++)
shopbuf[x+y*320]=17;

for (x=156;x<304;x++)
for (y=46;y<204;y++)
shopbuf[x+y*320]=18;


for (x=10;x<145;x++)
for (y=40;y<209;y++)
shopbuf[x+y*320]=16;

for (x=13;x<142;x++)
for (y=43;y<207;y++)
shopbuf[x+y*320]=17;

for (x=16;x<139;x++)
for (y=46;y<204;y++)
shopbuf[x+y*320]=18;


for (x=5;x<315;x++)
for (y=5;y<35;y++)
shopbuf[x+y*320]=16;
for (x=7;x<313;x++)
for (y=7;y<33;y++)
shopbuf[x+y*320]=17;
for (x=9;x<311;x++)
for (y=9;y<31;y++)
shopbuf[x+y*320]=18;

for (x=5;x<315;x++)
for (y=210;y<240;y++)
shopbuf[x+y*320]=16;
for (x=7;x<313;x++)
for (y=212;y<238;y++)
shopbuf[x+y*320]=17;
for (x=9;x<311;x++)
for (y=214;y<236;y++)
shopbuf[x+y*320]=18;


     
NextMusicTrack(30);
NewGameMode=SHOP;
}

void LootChest(void)
{
sprintf(new_message,"Looting the chest!");
NewMessage();
switch ((random(1+ch_level))%33)
{
case 0:AddItem(0,1+random(1+ch_level/3));break;
case 1:AddItem(63,50+random(25*(1+ch_level)));break;
case 2:AddItem(3,1);break;
case 3:AddItem(3,1+random(1+ch_level/2));break;
case 4:AddItem(8,1);break;
case 5:AddItem(25,1);break;
case 6:AddItem(23,1);break;
case 7:AddItem(20,1);break;
case 8:AddItem(17,1);break;
case 9:AddItem(18,1);break;
case 10:AddItem(12,1);break;
case 11:AddItem(16,1);break;
case 12:AddItem(10,1);break;
case 13:AddItem(1,1+random(10));break;
case 14:AddItem(52,1);break;
case 15:AddItem(19,1);break;
case 16:AddItem(22,1);break;
case 17:AddItem(26,1);break;
case 18:sprintf(new_message,"Chest is empty! You, bastards!");NewMessage();break;
case 19:AddItem(29,1);break;
case 20:AddItem(30,1);break;
case 21:AddItem(32,1);break;
case 22:AddItem(33,1);break;
case 23:AddItem(34,1);break;
case 24:AddItem(35,1);break;
case 25:AddItem(36,1);break;
case 26:AddItem(37,1);break;
case 27:AddItem(44,1);break;
case 28:AddItem(45,1);break;
case 29:AddItem(50,1);break;
case 30:sprintf(new_message,"You found note 'goblin trader was here :)'!");NewMessage();break;
case 31:AddItem(53,1);break;
case 32:AddItem(55,1);break;

}
}
