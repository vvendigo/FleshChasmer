#include <interface.h>
#include <gpu.h>
#include <shop.h>
#include <ai.h>
#include <sfont.h>
#include <items.h>
#include <sound.h>
#include <skills.h>
#include <monsters.h>
#include <zmath.h>
#include <string.h>
#include <zdialogs.h>

#include <globalvar.h>


#include <flood.h>
#include <render.h>

Uint8 bngz[76800];

Uint8 s_border;
Uint8 ammoleftcount;
void RenderMap()
{
Uint8 x,y,ix,iy;

Uint32 map_pos;
if (CradleMode)
map_pos=255+175*320;
else
map_pos=265+185*320;

ix=(monster_x[0]-proxy_cache_x*65536)/14000;
iy=(monster_y[0]-proxy_cache_y*65536)/14000;
//if (ix==0) ix=4;
Sint32 r;
for (y=0;y<50;y+=2)
{
r=map_pos+y*320;
           
for (x=0;x<50;x+=2)
 {
 scrbuf[r+x]=16;         
 scrbuf[r+x+321]=16;         
 }
                    
}

for (x=0;x<9;x++)
for (y=0;y<9;y++)
if (player_proxy[x][y]<8)
 {
  for (Uint8 i=0;i<4;i++)
  for (Uint8 k=0;k<4;k++)
  scrbuf[map_pos+5-ix+x*5+i+320*(40-y*5+k+iy)]=127-player_proxy[x][y];
 }     
for (x=0;x<50;x++)
 {
 scrbuf[map_pos+x]=173;                  
 scrbuf[map_pos+50+x*320]=173;                  
 scrbuf[map_pos+320+x*320]=173;                  
 scrbuf[map_pos+1+320*50+x]=173;                  
 }
 
for (Uint8 i=0;i<16;i++)
if (monster_ingame[i])
if (monster_status[i] & STATUS_ALIVE)
if ((table_vis[0][i])|(i==0))
 {
 Sint32 mx= 24+(monster_x[i]-monster_x[0])/13000;
 Sint32 my= 24-(monster_y[i]-monster_y[0])/13000;
  if ((mx>3)&(my>6)&(mx<45)&(my<43))
   {
   Sint32 p=map_pos+mx+my*320;
   Uint8 c;
   c=t_monster_char[monster_type[i]][1];
   if (i==monster_ai_target[0]) 
   {
   if (count/2%2)c=30;else c=t_monster_char[monster_type[i]][1];
    }
/*   scrbuf[p]=c+1;
   scrbuf[p-1]=c;
   scrbuf[p+1]=c;
   scrbuf[p-320]=c;
   scrbuf[p+320]=c;*/
  l_textstring=sprintf(s_textstring,"%c",t_monster_char[monster_type[i]][0]);
  Sint16 px,py;
  px=p%320-2;py=p/320-3;
  s_drawtext(px-2,py,16);               
  s_drawtext(px,py,16);               
  s_drawtext(px-1,py-1,16);               
  s_drawtext(px-1,py+1,16);               
  s_drawtext(px-1,py,c);               


   }   
 }
/*
for (Uint8 i=0;i<16;i++)
if (loot_count[i]>1)
 {
 Sint32 mx= 24+(loot_x[i]-monster_x[0])/13000;
 Sint32 my= 24-(loot_y[i]-monster_y[0])/13000;
  if ((mx>1)&(my>1)&(mx<49)&(my<49))
   {
   Sint32 p=map_pos+mx+my*320;

   scrbuf[p]=92;
   }   
 }
*/
monster_angle[0]=SuperAngle(monster_angle[0]);
scrbuf[map_pos+(22+f_cos[monster_angle[0]]/5000)+(25-f_sin[monster_angle[0]]/5000)*320]=31;
scrbuf[map_pos+(22+f_cos[monster_angle[0]]/10000)+(25-f_sin[monster_angle[0]]/10000)*320]=31;

l_textstring=sprintf(s_textstring,"+");
Sint16 rc=SuperAngle(-rcamera[4]-1024);
s_drawtext(map_pos%320+(23-f_cos[rc]/3000),map_pos/320+(20+f_sin[rc]/3000),25);
l_textstring=sprintf(s_textstring,"#");
s_drawtext(map_pos%320+(23+f_cos[rc]/3500),map_pos/320+(20-f_sin[rc]/3500),27);

}








Uint8 ci[9]={39,179,94,91,243,51,54,55,55};

Uint16 mes_x,mes_y;

void RenderTarget(void)
{
if (monster_action[0]<2)
if (controlpad.button[PAD_A]==0 & controlpad.button[PAD_B]==0 & controlpad.button[PAD_X]==0 & controlpad.button[PAD_Y]==0)
 AI_getplayertarget();
if (monster_ai_target[0]<16) if (monster_hp[monster_ai_target[0]]==0) monster_ai_target[0]=16;

if (dialogcount==0)
if (monster_ingame[0]<16)
if (monster_ai_target[0]<16)
 { 
Uint8 t=monster_ai_target[0];

zlvertex=0;
zlpoint(monster_x[t],monster_z[t],monster_y[t]);
if (vbufferz[0]>0)
 {
if (MonsterHpMode)
  l_textstring=sprintf(s_textstring,"%s HP:%i/%i",t_monster_name[monster_type[t]],monster_hp[t],monster_mhp[t]);
  else
  l_textstring=sprintf(s_textstring,"%s",t_monster_name[monster_type[t]]);
//  l_textstring=sprintf(s_textstring,"%i",monster_ai_state[t]);
  Sint32 x=vbufferx[0]*2-l_textstring/2*5;
  Sint32 y=vbuffery[0]*2;
  Sint32 i,k,yi;

if (CradleMode)
{
  if (x<10) x=10;else
  if (x>310-l_textstring*5) x=310-l_textstring*5;
  if (y<10) y=10;else if(y>206)y=206;
  if (y<mes_y+10) y=mes_y+10;

if ((x<86)&(y>185))
{
if (x>35) x=86;else y=185;
}
else
if (showmap)
{
if ((x+l_textstring*5>250)&(y>160))
{
if (x<290)
x=250-l_textstring*5;
else y=160;
}
}
}
else
{
  if (x<0) x=0;else
  if (x>320-l_textstring*5) x=320-l_textstring*5;
  if (y<0) y=0;else if(y>216)y=216;
  if (y<mes_y) y=mes_y;

if ((x<79)&(y>190))
{
if (x>35) x=79;else y=190;
}
else
if (showmap)
{
if ((x+l_textstring*5>260)&(y>170))
{
if (x<290)
x=260-l_textstring*5;
else y=170;
}
}
}

if (dialogcount)
if (y>135) y=135;
  
  s_drawtext(x+1,y+1,16);        

Uint8 col;
if (table_range[0][t]<t_monster_radius[0]+t_monster_meleerange[0]+t_monster_radius[monster_type[t]])
col=31;else
col=24+table_range[0][t]*7/t_monster_targetrange[0];

  s_drawtext(x,y,col);        

  k=x+l_textstring*5-1;
  yi=(y+12)*320;
  for (i=x;i<=k;i++)
   {
   scrbuf[i+yi]=29;                
   scrbuf[i+yi+1600]=29;                
   }
   scrbuf[x+320+yi]=29;                
   scrbuf[x+640+yi]=29;                
   scrbuf[x+960+yi]=29;                
   scrbuf[x+1280+yi]=29;                
  
   scrbuf[k+320+yi]=29;                
   scrbuf[k+640+yi]=29;                
   scrbuf[k+960+yi]=29;                
   scrbuf[k+1280+yi]=29;                
  Sint32 l=x+(monster_hp[t]*(k-x)/monster_mhp[t]);
  Uint8 c=ci[8*monster_hp[t]/monster_mhp[t]];
  for (i=x+1;i<l;i++)
   {
   scrbuf[i+320+yi]=c;                
   scrbuf[i+640+yi]=c;                
   scrbuf[i+960+yi]=c;                
   scrbuf[i+1280+yi]=c;                
   }  
  if (l==x) l=x+1;
  for (i=l;i<k;i++)
   {
   scrbuf[i+320+yi]=16;                
   scrbuf[i+640+yi]=16;                
   scrbuf[i+960+yi]=16;                
   scrbuf[i+1280+yi]=16;                
   }  
  
  }
 }
     
     
}
Sint16 hpl,mpl,mvl;
Uint8 KeyStatus;
Uint8 Li,Ri;
void RenderStatus(void)
{
Uint8 i,c;
Sint16 t,a0,a1;

Li=zabs(interface_L);
Ri=zabs(interface_R);

Sint32 statusbar_i;
if (CradleMode)
statusbar_i=(210-Li*3)*320+Li+10;
else
statusbar_i=(215-Li*3)*320+Li;
//HP

if (exp_bonus)
{
l_textstring=sprintf(s_textstring,"+%i Exp",exp_bonus);
Uint8 yyy=0;
if (exp_count>7) yyy=exp_count-7;
s_drawtext(80-5*l_textstring,198-Li*2-yyy-CradleMode*5,17);               
s_drawtext(80-5*l_textstring,197-Li*2-yyy-CradleMode*5,28-exp_count/2);               

if (exp_count==15) exp_bonus=0;
exp_count++;         
}

if (monster_action[0]!=5)
{
if (ammoleftcount) ammoleftcount--;
}
else
if (t_monster_shoottype[level_tag]<5)
if (item_c[62-t_monster_shoottype[level_tag]])
{
ammoleftcount=12;
}
if (ammoleftcount)
{
l_textstring=sprintf(s_textstring,"Ammo Left:%i",item_c[62-t_monster_shoottype[level_tag]]);
Uint8 yy=0;
if (ammoleftcount<5) yy=5-ammoleftcount;
s_drawtext(266-5*l_textstring-CradleMode*15,228-yy-CradleMode*10,17);               
s_drawtext(265-5*l_textstring-CradleMode*15,227-yy-CradleMode*10,17+ammoleftcount);               
}


t=70*monster_hp[0]/monster_mhp[0];
if (hpl>t) hpl--;
else
if (hpl<t) hpl++;
Sint8 rhp=t+5;

t=70*monster_mn[0]/t_monster_mn[monster_type[0]];
if (mpl>t) mpl--;
else
if (mpl<t) mpl++;
Sint8 rmp=t+5;

t=70*monster_mv[0]/t_monster_mv[monster_type[0]];
if (mvl>t) mvl--;
else
if (mvl<t) mvl++;
Sint8 rmv=t+5;


c=39;


for (i=5;i<=75;i++)
{
scrbuf[statusbar_i+i]=173;
scrbuf[statusbar_i+i+1600]=173;
}

scrbuf[statusbar_i+320+4]=173;
scrbuf[statusbar_i+640+4]=173;
scrbuf[statusbar_i+960+4]=173;
scrbuf[statusbar_i+1280+4]=173;

scrbuf[statusbar_i+320+76]=173;
scrbuf[statusbar_i+640+76]=173;
scrbuf[statusbar_i+960+76]=173;
scrbuf[statusbar_i+1280+76]=173;
Uint8 l=5+hpl;
for (i=5;i<=l;i++)
{
scrbuf[statusbar_i+320+i]=c;
scrbuf[statusbar_i+640+i]=c;
scrbuf[statusbar_i+960+i]=c;
scrbuf[statusbar_i+1280+i]=c;
}
for (i=l+1;i<76;i++)
{
scrbuf[statusbar_i+320+i]=16;
scrbuf[statusbar_i+640+i]=16;
scrbuf[statusbar_i+960+i]=16;
scrbuf[statusbar_i+1280+i]=16;
}
if (zabs(l-rhp)>0)
 {
if (l>rhp) {a1=l;a0=rhp;} else {a1=rhp;a0=l;}
for (i=a0;i<=a1;i++)
{
scrbuf[statusbar_i+320+i]=32;
scrbuf[statusbar_i+640+i]=32;
scrbuf[statusbar_i+960+i]=32;
scrbuf[statusbar_i+1280+i]=32;
}
 }

c=85;
statusbar_i+=(7+Li)*320;
for (i=5;i<=75;i++)
{
scrbuf[statusbar_i+i]=173;
scrbuf[statusbar_i+i+1600]=173;
}

scrbuf[statusbar_i+320+4]=173;
scrbuf[statusbar_i+640+4]=173;
scrbuf[statusbar_i+960+4]=173;
scrbuf[statusbar_i+1280+4]=173;

scrbuf[statusbar_i+320+76]=173;
scrbuf[statusbar_i+640+76]=173;
scrbuf[statusbar_i+960+76]=173;
scrbuf[statusbar_i+1280+76]=173;
l=5+mpl;
for (i=5;i<=l;i++)
{
scrbuf[statusbar_i+320+i]=c;
scrbuf[statusbar_i+640+i]=c;
scrbuf[statusbar_i+960+i]=c;
scrbuf[statusbar_i+1280+i]=c;
}
for (i=l+1;i<76;i++)
{
scrbuf[statusbar_i+320+i]=16;
scrbuf[statusbar_i+640+i]=16;
scrbuf[statusbar_i+960+i]=16;
scrbuf[statusbar_i+1280+i]=16;
}
if (monster_mn[0]>5)
if (zabs(l-rmp)>0)
 {
if (l>rmp) {a1=l;a0=rmp;} else {a1=rmp;a0=l;}
for (i=a0;i<=a1;i++)
{
scrbuf[statusbar_i+320+i]=82;
scrbuf[statusbar_i+640+i]=82;
scrbuf[statusbar_i+960+i]=82;
scrbuf[statusbar_i+1280+i]=82;
}
 }


c=53;
statusbar_i+=(7+Li)*320;
for (i=5;i<=75;i++)
{
scrbuf[statusbar_i+i]=173;
scrbuf[statusbar_i+i+1600]=173;
}

scrbuf[statusbar_i+320+4]=173;
scrbuf[statusbar_i+640+4]=173;
scrbuf[statusbar_i+960+4]=173;
scrbuf[statusbar_i+1280+4]=173;

scrbuf[statusbar_i+320+76]=173;
scrbuf[statusbar_i+640+76]=173;
scrbuf[statusbar_i+960+76]=173;
scrbuf[statusbar_i+1280+76]=173;
l=5+mvl;
for (i=5;i<=l;i++)
{
scrbuf[statusbar_i+320+i]=c;
scrbuf[statusbar_i+640+i]=c;
scrbuf[statusbar_i+960+i]=c;
scrbuf[statusbar_i+1280+i]=c;
}
for (i=l+1;i<76;i++)
{
scrbuf[statusbar_i+320+i]=16;
scrbuf[statusbar_i+640+i]=16;
scrbuf[statusbar_i+960+i]=16;
scrbuf[statusbar_i+1280+i]=16;
}
if (zabs(l-rmv)>0)
 {
if (l>rmv) {a1=l;a0=rmv;} else {a1=rmv;a0=l;}
for (i=a0;i<=a1;i++)
{
scrbuf[statusbar_i+320+i]=50;
scrbuf[statusbar_i+640+i]=50;
scrbuf[statusbar_i+960+i]=50;
scrbuf[statusbar_i+1280+i]=50;
}
 }


 Sint16 x,y,k;
Uint8 ii,n;
if (interface_L!=0)
 {//item quick menu

   if (interface_L<5)
   interface_L++;
  if (controlpad.button[PAD_L1]==0) 
  if (interface_L>0)
    {
    if (interface_L==5) sPlaySound(4,100,0);
    interface_L=-interface_L;}             

 a0=Li*2-2;
 a1=10+Li*35;

 for (k=a0;k<a1;k++)
 {
 scrbuf[k+40*320]=173;    
 scrbuf[k+181*320]=173;    
 }

 for (y=41;y<180;y+=2)
 for (k=a0;k<a1;k+=2)
 {
 scrbuf[k+y*320]=16;    
 scrbuf[k+y*320+321]=16;     
 }
 

if (interface_L==5)
  {
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


if (i==-ii+chmenu_y[1]) 
{
Uint16 k;
 for (y=54+i*12;y<66+i*12;y+=2)
 for (k=20;k<184;k+=2)
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

s_drawtext(20,55+i*12,17);               
s_drawtext(20,54+i*12,c);               


l_textstring=sprintf(s_textstring,"%i",item_c[n]);
s_drawtext(181-5*l_textstring,55+i*12,17);               
s_drawtext(180-5*l_textstring,54+i*12,c);               

if ((n>=32)&(n<44))
  {
l_textstring=sprintf(s_textstring,"%i%c",weapon_points[n-32]/10,37);
s_drawtext(161-5*l_textstring,55+i*12,17);               
s_drawtext(160-5*l_textstring,54+i*12,c);               

              
}
}
 }
}
n=item_p[chmenu_y[1]];

if (n<64)
if (item_c[n])
{
l_textstring=sprintf(s_textstring,"%s",item_s[n*2+1]);
s_drawtext(40,164,18);               
s_drawtext(41,163,29);               
}       
//control
if (count% 2)
{
    switch (controlpad.angle)
      {
             case 0:if (chmenu_y[1]>0)
             {chmenu_y[1]--;
             sPlaySound(28,64,32);
             }break;
             case 4:if (chmenu_y[1]<63)
             {chmenu_y[1]++;
             sPlaySound(28,64,32);
             }break;
      }
                
if ((controlpad.button[PAD_A])|(controlpad.button[PAD_B])|(controlpad.button[PAD_X])|(controlpad.button[PAD_Y])|(controlpad.button[PAD_Z]))
 {
 if (KeyStatus==0)
 {
 if (item_p[chmenu_y[1]]<64)
 UseItem(item_p[chmenu_y[1]]);
 }
 KeyStatus=1;
 }
 else KeyStatus=0;

 }
//HP-MP-MV                   
 statusbar_i=statusbar_i-320*23;
 x=statusbar_i%320+78;
 y=statusbar_i/320-4;
  l_textstring=sprintf(s_textstring,"%i",monster_hp[0]);
  s_drawtext(x+1,y+1,33);        
  s_drawtext(x,y,38);        
  y=y+12; 

  l_textstring=sprintf(s_textstring,"%i",monster_mn[0]);
  s_drawtext(x+1,y+1,82);        
  s_drawtext(x,y,86);        
  y=y+12; 

  l_textstring=sprintf(s_textstring,"%i",monster_mv[0]);
  s_drawtext(x+1,y+1,51);        
  s_drawtext(x,y,55);        
                   
                   
  } 

 }//item quick menu     


if (interface_R!=0)
 {//item skill menu

   if (interface_R<5)
   interface_R++;
  if (controlpad.button[PAD_R1]==0) 
  if (interface_R>0)
    {
    if (interface_R==5) sPlaySound(4,0,100);
    interface_R=-interface_R;}             


 a0=Ri*8-4;
 a1=10+Ri*32;

 for (k=150;k<300;k++)
 {
 scrbuf[k+a0*320-320]=173;    
 scrbuf[k+a1*320]=173;    
 }

 for (y=a0;y<a1;y+=2)
 for (k=150;k<300;k+=2)
 {
 scrbuf[k+y*320]=16;    
 scrbuf[k+y*320+321]=16;     
 }
 if (interface_R==5)
 {//SKILLLS
/////
if (count%2)
{
    switch (controlpad.angle)
      {
             case 0:if (chmenu_y[2]>0)
             {chmenu_y[2]--;
             sPlaySound(28,32,64);
             }break;
             case 4:if (chmenu_y[2]<31)
             {chmenu_y[2]++;
             sPlaySound(28,32,64);
             }break;
      }
                
if ((controlpad.button[PAD_A])|(controlpad.button[PAD_B])|(controlpad.button[PAD_X])|(controlpad.button[PAD_Y]))
     if (skill_l[skill_p[chmenu_y[2]]])
      {
      if ((controlpad.button[PAD_A]))
       t_monster_action[monster_type[0]][0]=skill_p[chmenu_y[2]];
      if ((controlpad.button[PAD_X]))
       t_monster_action[monster_type[0]][1]=skill_p[chmenu_y[2]];
      if ((controlpad.button[PAD_B]))
       t_monster_action[monster_type[0]][2]=skill_p[chmenu_y[2]];
      if ((controlpad.button[PAD_Y]))
       t_monster_action[monster_type[0]][3]=skill_p[chmenu_y[2]];
      }
}
////////////////

for (i=0;i<7;i++)
{
 {
if (chmenu_y[2]<3) ii=0;
else
if (chmenu_y[2]<28) ii=chmenu_y[2]-3;
else
ii=25;

n=skill_p[ii+i];
if (i==-ii+chmenu_y[2]) 
 for (y=41+i*12;y<53+i*12;y+=2)
 for (k=150;k<300;k+=2)
 {
 scrbuf[k+y*320]=16;    
 scrbuf[k+y*320+321]=16;     
 }
if (n<32)
if (skill_l[n])
  {
if (n==skill_p[chmenu_y[2]]) c=29;else c=22;
l_textstring=sprintf(s_textstring,"%s",skill_s[n*2]);
s_drawtext(160,42+i*12,18);               
s_drawtext(159,41+i*12,c);               
Uint8 m0t=monster_type[0];
if (n==t_monster_action[m0t][0])
   {
l_textstring=sprintf(s_textstring,"A");
s_drawtext(253,42+i*12,18);               
s_drawtext(254,41+i*12,90+count/2%4);               
   }
if (n==t_monster_action[m0t][1])
   {
l_textstring=sprintf(s_textstring,"X");
s_drawtext(262,42+i*12,18);               
s_drawtext(261,41+i*12,90+(count/2+1)%4);               
   }
if (n==t_monster_action[m0t][2])
   {
l_textstring=sprintf(s_textstring,"B");
s_drawtext(268,42+i*12,18);               
s_drawtext(267,41+i*12,90+(count/2+2)%4);               
   }
if (n==t_monster_action[m0t][3])
   {
l_textstring=sprintf(s_textstring,"Y");
s_drawtext(274,42+i*12,18);               
s_drawtext(273,41+i*12,90+(count/2+3)%4);               
   }
   
   
  }

 }
}
n=skill_p[chmenu_y[2]];
if (n<32)
if (skill_l[n])
{
l_textstring=sprintf(s_textstring,"%s",skill_s[n*2+1]);
s_drawtext(180,154,18);               
s_drawtext(181,153,29);               
l_textstring=sprintf(s_textstring,"%s",skill_s0[n]);
s_drawtext(170,142,18);               
s_drawtext(171,141,29);               

}       

 }//SKILLS
 }//quick skill menu     

}


char message[3][64]={"","",""};
Uint8 message_x[3];
Uint8 message_pause=0;


void NewMessage(void)
{
if (GameMode==GAME)
{
Uint8 i=0; 
if (strlen(message[0])) 
{
i=1;
if (strlen(message[1])) 
 {
 i=2;                   
if (strlen(message[2])) 
 i=3;       
 }
if (i==3)
 {
 i=2;        
 sprintf(message[0],"%s",message[1]);
 sprintf(message[1],"%s",message[2]);
// sprintf(message[2],"%s",new_message);
 }
}
sprintf(message[i],"%s",new_message);


//if (i==0)
//if (message_pause<32)
if (i==0)
message_pause=0;
//else 
//if (i>0)
//message_pause=43;

message_x[i]=5;//...or something like this...
}
}
void RenderStrings(void)
{
Uint16 l;
Uint16 x,y;
Uint8 c_border=CradleMode*10;
x=300;y=0;
if (strlen(message[2])) y=40;
else
if (strlen(message[1])) y=28;
else
if (strlen(message[0])) y=16;

if (x>319) x=319;
//if (CradleMode) y+=10;


mes_x=x;      
if (mes_y>y) mes_y-=2;
else
mes_y=y;
Sint32 ii=c_border+c_border*320;      
if (y>c_border)
{
for (Uint16 ix=0;ix<mes_x;ix+=2)
{
for (Uint16 iy=0;iy<mes_y;iy+=2)

 {
 Uint16 i=ii+ix+(iy)*320;
 scrbuf[i]=83;
 scrbuf[i+321]=83;
 }
}
for (Uint16 ix=0;ix<mes_x;ix++)
{
scrbuf[ix+ii]=29;    
scrbuf[ii+ix+mes_y*320]=29;    
}
for (Uint16 iy=0;iy<mes_y;iy++)
{
scrbuf[ii+iy*320]=29;    
scrbuf[ii+mes_x+iy*320]=29;    
}
}

l_textstring=sprintf(s_textstring,"%s",message[0]);
if (l_textstring)
{
l=message_x[0]*4+5;
s_drawtext(l+1+c_border,3+c_border,16);               
if (message_pause<32)
s_drawtext(l+c_border,2+c_border,29);
else
s_drawtext(l+c_border,2+c_border,29-(message_pause-32));
}
l_textstring=sprintf(s_textstring,"%s",message[1]);
if (l_textstring)
{
l=message_x[1]*4+5;
s_drawtext(l+1+c_border,15+c_border,16);               
s_drawtext(l+c_border,14+c_border,30);               
}
l_textstring=sprintf(s_textstring,"%s",message[2]);
if (l_textstring)
{
l=message_x[2]*4+5;
s_drawtext(l+1+c_border,27+c_border,16);               
s_drawtext(l+c_border,26+c_border,31);               
}     
message_pause++;

for (Uint8 i=0;i<3;i++)
if (message_x[i]) message_x[i]--;

if (message_pause==45)
 {
 message_pause=0;
 sprintf(message[0],"%s",message[1]);
 sprintf(message[1],"%s",message[2]);
 sprintf(message[2],"");
 
 message_x[0]=message_x[1];
 message_x[1]=message_x[2];
 }

}
void ProcMusic(void)
{
     
ldanger_status=danger_status;
if (monster_ai_target[0]<16)
{
if (table_range[0][monster_ai_target[0]]<70000)
{
if (danger_status<50) danger_status++;
}
else                        
if (danger_status<25) danger_status++;
else
if (danger_status>25) danger_status--;

                        
}
else
if (danger_status>-25) danger_status--;
     
     
if (danger_status!=ldanger_status)
if (danger_status==-25) NextMusicTrack(levelmusictrack);
else
if (danger_status==25) 
{
NextMusicTrack(levelwarmusictrack);
}
}
char gameover[11]="GAME OVER ";
void RenderGameOver()
{
Uint8 c=monster_actioncount[0],cl;     

if (c>32)
 {
 if (c>150) NewGameMode=MAINMENU;
 Uint8 n,i;
 n=(c-32)/8;
 if (n>10) n=10;
 for (i=0;i<n;i++)
 {
 if (i==n-1)
 cl=32+c%8;
 else
 cl=39;
 l_textstring=sprintf(s_textstring,"%c",gameover[i]);
 s_drawtext2(161-n*5+i*10,89+cl,16);
 s_drawtext2(160-n*5+i*10,88+cl,cl);
 }
         
 }     
}
void s_statusdrawtext(Uint16 x,Uint8 y,Uint8 c)
{
s_drawtext(x+1,y,16);
s_drawtext(x-1,y,16);
s_drawtext(x,y-1,16);
s_drawtext(x,y+1,16);
s_drawtext(x,y,c);
}
void RenderState(void)
{
Sint16 x,y;
x=5+CradleMode*15;
y=mes_y+2+CradleMode*10;
Uint8 ml=0;
if (monster_mv[0]<t_monster_mv1[level_tag])
 {
  if (monster_mv[0]<t_monster_mv0[level_tag])
   {
 l_textstring=sprintf(s_textstring,"Exausted");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,39-count%8);
 ml=l_textstring;
   }
   else
   {
 l_textstring=sprintf(s_textstring,"Tired");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,39-count/2%8);
 ml=l_textstring;
   }  
  x=x+5+ml*5;                               
 }
if (monster_blessed[0])
 {
 l_textstring=sprintf(s_textstring,"Bless");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,248+count/3%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
if (monster_hasted[0])
 {
 l_textstring=sprintf(s_textstring,"Haste");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,88+count%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
if (monster_invisible[0])
 {
 l_textstring=sprintf(s_textstring,"Invisible");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,24+count/2%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
if (monster_magicarmor[0])
 {
 l_textstring=sprintf(s_textstring,"Armor");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,160+count/2%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
if (monster_shielded[0])
 {
 l_textstring=sprintf(s_textstring,"Shield");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,80+count/2%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
if (monster_poisoned[0])
 {
 l_textstring=sprintf(s_textstring,"Poison");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,55-count/2%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
if (monster_ill[0])
 {
 l_textstring=sprintf(s_textstring,"Dicease");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,216+count/4%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
if (monster_slowed[0])
 {
 l_textstring=sprintf(s_textstring,"Slow");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,103-count/3%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
if (monster_confuzed[0])
 {
 l_textstring=sprintf(s_textstring,"Confuzed");
// s_drawtext(x+1,y+1,16);
 s_statusdrawtext(x,y,231-count%8);
  ml=l_textstring;
  x=x+5+ml*5;                               
 }
}

void RenderInterface(void)
{
if (movie_mode!=1)
{
screenborder=0;
if (monster_status[0]&STATUS_ALIVE)
{
if (movie_mode!=1)
{
if ((interface_L==0)&(interface_R==0))
{
RenderTarget();
if (showmap)
RenderMap();
}
RenderState();
ProcZInterface();
}
RenderStatus();

RenderStrings();
ProcMusic();

//l_textstring=sprintf(s_textstring,"%i/%i",monsters,maxmonsters);
//s_drawtext(200,216,28);
//for (Uint8 i=1;i<16;i++)
//if (monster_ingame[i])
//{
//l_textstring=sprintf(s_textstring,"%i",monster_flood_data[i]);
//s_drawtext(100+i*5,0,28);
                      
//}
}
else
{
screenborder=26;
RenderGameOver();   
}
}
}

char cname_table[5][13]=
{
"ABCDEFabcdef",
"GHIKLMghiklm",
"NOPQRSnopqrs",
"TVUWXYtvuwxy",
"Z12345z67890" 
};
Uint8 cname_x,cname_y,cname_i;

void PlayerNameMenu(void)
{
//Super Background
l_textstring=sprintf(s_textstring,"#include <conio.h>");s_drawtext(160,60,18);
l_textstring=sprintf(s_textstring,"#include <stdlib.h>");s_drawtext(160,72,18);
l_textstring=sprintf(s_textstring,"#include <cmath.h>");s_drawtext(160,84,18);
l_textstring=sprintf(s_textstring,"#include <stdio.h>");s_drawtext(160,96,18);
l_textstring=sprintf(s_textstring,"int i;");s_drawtext(160,120,18);
l_textstring=sprintf(s_textstring,"void main( void)");s_drawtext(160,132,18);
l_textstring=sprintf(s_textstring,"{");s_drawtext(160,144,18);
l_textstring=sprintf(s_textstring,"printf(':P');");s_drawtext(160,144,18);
l_textstring=sprintf(s_textstring,"}// displays :P");s_drawtext(160,156,18);
     
     
     
     
     
     
     
//Super Background
l_textstring=sprintf(s_textstring,"Please name your character:");
s_drawtext(20,24,27);

l_textstring=sprintf(s_textstring,"Name:");
s_drawtext2(21,37,22);
s_drawtext2(20,36,27);

l_textstring=sprintf(s_textstring,"%s",t_monster_name[0]);
s_drawtext2(81,37,32);
s_drawtext2(80,36,36);
if (count/2%2)
{
l_textstring=sprintf(s_textstring,"_");
s_drawtext2(81+cname_i*10,39,22);
s_drawtext2(80+cname_i*10,38,31);
}
for (Uint8 x=0;x<12;x++)
for (Uint8 y=0;y<5;y++)
{
Sint16 cx=100+x*15;   
Sint16 cy=80+y*24;
l_textstring=sprintf(s_textstring,"%c",cname_table[y][x]);
if (x==cname_x & y==cname_y)
{cx=cx-1+count/2%3;
s_drawtext2(cx+1,cy+1,25);
s_drawtext2(cx,cy,31);
}
else    
{
s_drawtext2(cx+1,cy+1,18);
s_drawtext2(cx,cy,22);
}
}
if (CradleMode==0)
{
l_textstring=sprintf(s_textstring,"When ready press START");
s_drawtext(10,228,27);
}
l_textstring=sprintf(s_textstring,"L R - shift cursor");
s_drawtext(10,216,27);
l_textstring=sprintf(s_textstring,"X - empty space");
s_drawtext(10,204,27);

if (count%2)
{

if (controlpad.angle%2==0) sPlaySound(0,100,100);
switch (controlpad.angle)
{
case 0:if (cname_y)cname_y--;break;
case 2:if (cname_x<11)cname_x++;break;
case 4:if (cname_y<4)cname_y++;break;
case 6:if (cname_x)cname_x--;break;
}       
       


if (controlpad.button[PAD_L1])
if (cname_i)
{
cname_i--;
sPlaySound(0,128,0);
}    
if (controlpad.button[PAD_R1])
if (cname_i<7)
{
sPlaySound(0,0,128);
cname_i++;
}    
if (controlpad.button[PAD_X]) 
{
t_monster_name[0][cname_i]=' ';
sPlaySound(0,0,128);
if (cname_i<7)cname_i++;
}
else
if (controlpad.button[PAD_A] | controlpad.button[PAD_B] | controlpad.button[PAD_Y])
{
t_monster_name[0][cname_i]=cname_table[cname_y][cname_x];
sPlaySound(0,0,128);
if (cname_i<7)cname_i++;
}
                
if (controlpad.button[PAD_START])
 {
 sPlaySound(37,120,120);
 NewGameMode=GAME;
 }
} 
}



Uint8 Ztimer=0,Ztimer1=0;
char z_text[64];
void ProcZInterface(void)
{
Uint8 item=0;
Sint32 ri=monster_roomi[0];
Uint8 rim=map[ri];
if (rim>=20 & rim<24)
item=1;//ladder
else
if (rim==24)
item=3;//shop
if (mapobj[ri]==35)item=2;

if (danger_status>25) item=0; 

if (Ztimer>0) {Ztimer--;item=0;}


Uint8 c=17+Ztimer1;

if (item==0)
{
if (Ztimer1) Ztimer1--;
}
else
{
if (Ztimer1<14)
Ztimer1++;

switch (item)
 {

 case 1:      
if (CradleMode)
sprintf(z_text,"Press L+R to climb");
else
sprintf(z_text,"Press L+R to climb");
//sprintf(z_text,"Press Z to climb");

  if (Ztimer1>8)
  if (controlpad.button[PAD_Z] | (controlpad.button[PAD_L1] & controlpad.button[PAD_R1]))
   {
   Uint8 x,y,z;
   x=monster_cx[0];
   y=monster_cy[0];
   z=monster_cz[0];
   Sint8 iz=0,ix=0,iy=0;
   switch (map[monster_roomi[0]])
   {
   case 20:
        if (mapt2[monster_roomi[0]]==0) {iz=-1;x=x+1;}else {iz=1;ix=1;}
        break;

   case 21:
        if (mapt4[monster_roomi[0]]==0) {iz=-1;y=y+1;}else {iz=1;iy=1;}
        break;

   case 22:
        if (mapt1[monster_roomi[0]]==0) {iz=-1;x=x-1;}else {iz=1;ix=-1;}
        break;

   case 23:
        if (mapt3[monster_roomi[0]]==0) {iz=-1;y=y-1;}else {iz=1;iy=-1;}
        break;
   }
   while (iz)
   {
   z=z+iz;Sint32 i=x+y*128+z*16384;
   if (iz>0) 
    {
    if (mapt5[i]) {iz=0;x=x+ix;y=y+iy;}
    }
    else
   if (iz<0)
    {
    if (mapt0[i]) {iz=0;}
            
    } 
   }    
   if (z!=monster_cz[0])
   {
   sPlaySound(2,127,127);
   GameMode=NOGAME;
   NewGameMode=GAME;
   monster_move(0,x,y,z);
   }
   Ztimer=48;                    
//   Ztimer1=0;                            
   }
 break;
 case 2://chest
sprintf(z_text,"");
   {
   mapobj[ri]=34;
   LootChest();
   sPlaySound(2,128,128);
   }
 break;
 case 3://shop
if (CradleMode)
sprintf(z_text,"Press L+R to trade");
else
sprintf(z_text,"Press L+R to trade");
//sprintf(z_text,"Press Z to trade");
  if (Ztimer1>8)
if (controlpad.button[PAD_Z] | (controlpad.button[PAD_L1] & controlpad.button[PAD_R1]))
   {
   EnterShop();
   Ztimer=48;
   }
 break;

 }

         
}
if (dialogcount==0)
if (Ztimer1)
{
l_textstring=sprintf(s_textstring,"%s",z_text);
s_drawtext2(161-l_textstring*5,141,16);
s_drawtext2(161-l_textstring*5,139,16);
s_drawtext2(162-l_textstring*5,140,16);
s_drawtext2(160-l_textstring*5,140,16);
s_drawtext2(161-l_textstring*5,140,c);
}

}
void PlayerReName(void)
{
sPlaySound(37,120,120);
NewGameMode=PLAYER_NAME;
}


char credits[64][64]={
"           FleshChasmer chapter I: the Eve",
"", 
"               Game Credits",
"",
"",
"             Engine Programming",
"                Sergei 'Quasist' Zverev",
"",
"             Game Programming",
"                Sergei 'Quasist' Zverev",
"",
"             3D animation",
"                Sergei 'Quasist' Zverev",
"",
"             2D artist",
"                Sergei 'Quasist' Zverev",
"",
"             Level Designer",
"                Sergei 'Quasist' Zverev",
"",
"             Music and SFX artist",
"                Sergei 'Quasist' Zverev",
"",
"             Script scenes",
"                Sergei 'Quasist' Zverev",
"",
"             Testers",
"                500MHz",
"                Hahahoj",
"                LoL_XaMMAx",
"",
"             Quality Assurance",
"                CruelPussy",
"                Fudoshi Nayur",
"",
"",
"",
"",
"",
"               Thanks For Playing",
""
     
};
Uint16 creditcount=0;

void creditsproc(void)
{

Uint8 c;
Sint32 y,y2;
creditcount=count;
//if (creditcount==3) NextMusicTrack(0);
if (creditcount==800) GameLoopEnabled=0;

for (Uint8 i=0;i<64;i++)
{
y=240-creditcount+i*12;   
y2=160+(y-160)*4/3;
l_textstring=sprintf(s_textstring,"%s",credits[i]);
if (y2>-12 & y2<240)
s_drawtext(0,y2,17);
}
for (Uint8 i=0;i<64;i++)
{
y=240-creditcount+i*12;   
l_textstring=sprintf(s_textstring,"%s",credits[i]);
c=31;
if (y<80) c=16+y/8;
else
if (y>160) c=31-(y-160)/8;
if (y>0 & y<240)
s_drawtext(0,y,c);
}
     
}


void renderintro(void)
{
Sint32 i;
for (i=0;i<76800;i++) scrbuf[i]=17;
sPlaySound(20,28,28);
scrbuf_draw();

SetMusic(43);
SDL_Delay(1000);

FILE *fp;

for (i=0;i<76800;i++) scrbuf[i]=16;
scrbuf_draw();
sPlaySound(20,128,128);
SDL_Delay(1000);

fp=fopen("data/logo.bng","rb");
 for (i=0;i<76800;i++) bngz[i]=fgetc(fp);
 fclose(fp);       
sPlaySound(20,128,128);
for (i=0;i<76800;i++) scrbuf[i]=bngz[i];
scrbuf_draw();
SDL_Delay(5000);
sPlaySound(34,128,128);

for (Sint16 k=0;k<400;k++)
{

for (Uint16 j=0;j<k+20;j++)
{
Uint32 n=5+random(312)+(2+random(236))*320;
scrbuf[n+1]=scrbuf[n];    
scrbuf[n-1]=scrbuf[n];    
scrbuf[n-323]=33;    
scrbuf[n-322]=scrbuf[n];    
scrbuf[n+322]=scrbuf[n];    
scrbuf[n+323]=36;    

}

scrbuf_draw();
#ifdef PC
SDL_Delay(5);
#endif
}

for (i=0;i<76800;i++) scrbuf[i]=16;
sPlaySound(20,128,128);
scrbuf_draw();
SDL_Delay(3000);

SetMusic(50);

}
