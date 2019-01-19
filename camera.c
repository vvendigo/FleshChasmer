#include <camera.h>
#include <globalvar.h>
#include "zmath.h"

#define FPMUL(x,y)	((((x)>>6)*((y)>>6))>>4)
#define FPDIV(x,y)	((((x)<<6)/((y)>>6))>>4)

void camset(unsigned short int x,unsigned short int y,unsigned short int z)
{
Sint32 t=x+y*128+z*16384;
if (mapcam0[t])
 {
  if (mapcam0[t]<128)
   {
    for (int i=0;i<6;i++)
     camera[i]=staticcam[mapcam0[t]-1][i];                 
   }            
   else
   {//Saint Code Here
   Sint32 ang0=256*(mapcam1[t]&0xf);
   Sint32 ang1=-128+64*(mapcam1[t]>>4);
  // ang0=(count/10%16)*256;
   if (ang1<0) ang1=4096+ang1;//Begone the tables of love/ virtue of code hash you
   Sint32 rang=100000+20000*(mapcam2[t]&0xf);
   Sint32 rangx=FPMUL(f_cos[ang1],rang);

//   Sint32 ti=FPMUL(rang,f_sin[ang0]);

    camera[0]=meshx[t]+32666+FPMUL(rangx,f_cos[ang0]);   
    camera[1]=meshz[t]+32666+FPMUL(rang,f_sin[ang1]);
    camera[2]=meshy[t]+32666+FPMUL(rangx,f_sin[ang0]);   

    camera[3]=4096-ang1-200+25*(mapcam2[t]>>4);;

    camera[4]=3072-ang0-256+32*(mapcam3[t]&0xf);   
    camera[5]=-512+64*(mapcam3[t]>>4);   
   }         
 }
}

void camproc(void)
{
Uint8 i;
Sint32 de;

if (agressive_cam)
 {
 for (i=0;i<3;i++)
 rcamera[i]=rcamera[i]+(camera[i]-rcamera[i])/4;     

 for (i=3;i<6;i++)
 {
 de=(camera[i]-rcamera[i]);
 if (de>2048) de=-4096+de;
 else
 if (de<-2048) de=4096+de;
 rcamera[i]+=de/4;     
 }     
                  
                  
 }
 else
{
 for (i=0;i<3;i++)
 rcamera[i]=rcamera[i]+(camera[i]-rcamera[i])/8;     

 for (i=3;i<6;i++)
 {
 de=(camera[i]-rcamera[i]);
 if (de>2048) de=-4096+de;
 else
 if (de<-2048) de=4096+de;
 rcamera[i]+=de/8;     
 }     
}

for (i=3;i<6;i++)
{     
while (rcamera[i]<0) {rcamera[i]=4096+rcamera[i];}
while (rcamera[i]>=4096) {rcamera[i]=rcamera[i]-4096;}    
}     
for (i=3;i<6;i++)
{     
if (camera[i]<0) camera[i]=4096+camera[i];
camera[i]=camera[i]%4096;    
}     

}

void camsync(void)
{
for (Uint8 i=0;i<6;i++)
rcamera[i]=camera[i];     
}




int b_onmap_f(Sint16 x,Sint16 y,Sint16 z)
{
int i=1;

if (x<0) i=0;
if (y<0) i=0;
if (z<0) i=0;
if (x>levelx) i=0;
if (y>levely) i=0;
if (z>levelz) i=0;
    
return i;    
}

void procplayercamera(void)
{
if (CameraMode == 3) {
Sint32 a=SuperAngle(-monster_angle[0]+1024);
camera[0]=monster_x[0];//-f_cos[monster_angle[0]];
camera[1]=monster_z[0]+65536-17800;
camera[2]=monster_y[0];//-f_sin[monster_angle[0]];
camera[3]=4096-86;
camera[4]=a;
camera[5]=0;
camsync();
} else
if (CameraMode)
{
Sint32 a=SuperAngle(-monster_angle[0]+1024);
Uint8 c_far=1+CameraMode*2;
camera[0]=monster_x[0]-f_cos[monster_angle[0]]*c_far;               
camera[1]=monster_z[0]+c_far*65536;               
camera[2]=monster_y[0]-f_sin[monster_angle[0]]*c_far;               
camera[3]=4096-436;               
camera[4]=a;               
camera[5]=0;               
camsync();               
}
else
{
Uint8 cx,cy,cz;
Sint32 x,y,z;


Sint32 cm[4][6],tx,ty,tz,delta;


x=monster_x[0];
y=monster_y[0];
z=monster_z[0];

 x+=FPMUL(monster_radius[0]*12/15,f_cos[monster_angle[0]]);
 y+=FPMUL(monster_radius[0]*12/15,f_sin[monster_angle[0]]);
cx=x/65536;
cy=y/65536;
cz=z/65536;

Uint32 roomi=cx+cy*128+cz*16384;

Uint8 cam=mapcam0[roomi];

if (lastcamdelay)
{lastcamdelay--;
if (lastcamdelay==0)
 {
 camset(cx,cy,cz);
 camsync();
 lastcamera=cam;
 }
}
else
{

{
if (cam!=lastcamera) 
{
 cameradelay=1;
 camset(cx,cy,cz);
 camsync();
}
else
if (cam>=128)
 {
camset(cx,cy,cz);
 for (Uint8 i=0;i<6;i++) cm[0][i]=camera[i];
 
 tx=x-cx*65536-32768;            
 ty=y-cy*65536-32768;
 tz=z-cz*65536;             

 if (tx<0)
 { 
  if (cx>0)
  if (mapcam0[roomi-1]==cam)
  {
 camset(cx-1,cy,cz);
 for (Uint8 i=0;i<6;i++) cm[1][i]=camera[i];
  delta=-tx;
 for (Uint8 i=0;i<3;i++) camera[i]=cm[0][i]+FPMUL((cm[1][i]-cm[0][i]),delta);
 for (Uint8 i=3;i<6;i++) camera[i]=cm[0][i]+FPMUL(calcturn(cm[0][i],cm[1][i]),delta);
          
  }
 }
 else
 { 
  if (cx<levelx)
  if (mapcam0[roomi+1]==cam)
  {
 camset(cx+1,cy,cz);
 for (Uint8 i=0;i<6;i++) cm[1][i]=camera[i];
  delta=tx;
 for (Uint8 i=0;i<3;i++) camera[i]=cm[0][i]+FPMUL((cm[1][i]-cm[0][i]),delta);
 for (Uint8 i=3;i<6;i++) camera[i]=cm[0][i]+FPMUL(calcturn(cm[0][i],cm[1][i]),delta);
          
  }
  }
 for (Uint8 i=0;i<6;i++) cm[2][i]=camera[i];


 if (ty<0)
 { 
  if (cy>0)
  if (mapcam0[roomi-128]==cam)
  {
 camset(cx,cy-1,cz);
 for (Uint8 i=0;i<6;i++) cm[3][i]=camera[i];
  delta=-ty;
 for (Uint8 i=0;i<3;i++) camera[i]=cm[2][i]+FPMUL((cm[3][i]-cm[2][i]),delta);
 for (Uint8 i=3;i<6;i++) camera[i]=cm[2][i]+FPMUL(calcturn(cm[2][i],cm[3][i]),delta);
          
  }
 }
 else
 { 
  if (cy<levely)
  if (mapcam0[roomi+128]==cam)
  {
 camset(cx,cy+1,cz);
 for (Uint8 i=0;i<6;i++) cm[3][i]=camera[i];
  delta=ty;
 for (Uint8 i=0;i<3;i++) camera[i]=cm[2][i]+FPMUL((cm[3][i]-cm[2][i]),delta);
 for (Uint8 i=3;i<6;i++) camera[i]=cm[2][i]+FPMUL(calcturn(cm[2][i],cm[3][i]),delta);
  }
  }
 }

}

if (lastcamera!=cam) 
 {
 lastcamdelay=16;
 lastcamera=cam;

// camset(cx,cy,cz);
 camsync();
//debugval1=cam;     

 }

}


debugval0=lastcamdelay;     
}
}
void ResetCamera(void)
{
lastcamdelay=0;
}
