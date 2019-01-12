#include <flood.h>
#include <monsters.h>
#include <zmath.h>
#include <gpu.h>
#include <globalvar.h>
Uint8 monster_flood_data[16];
Uint8 monster_vis_data[16];

Uint8 floodcount;

Uint8 flood_breed[666];
Uint8 flood_breedi;

Uint8 flood_vis(Sint32 itx,Sint32 ity,Sint32 itz)
{
Uint8 vis=0;      

Sint8 cx,cy,cz;
Sint8 nx,ny,nz;
Sint32 ix,iy,iz,r,it,st;
Sint32 x,y,z,t;

r=srange(itx-monster_x[0],ity-monster_y[0]);
//r=srange(r,itz-camera[2]);

it=r/32666;

if (it==0) vis=1;
else
 {
ix=(itx-monster_x[0])/it;
iy=(ity-monster_y[0])/it;
iz=(itz-monster_z[0])/it;

x=monster_x[0];
y=monster_y[0];
z=monster_z[0];
cx=x/65536;
cy=y/65536;
cz=z/65536;


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



Uint8 camera_vis(Sint32 itx,Sint32 ity,Sint32 itz)
{
Uint8 vis=0;      

Sint8 cx,cy,cz;
Sint8 nx,ny,nz;
Sint32 ix,iy,iz,r,it,st;
Sint32 x,y,z,t;

zlvertex=0;
vbufferz[0]=0;
vbufferx[0]=-100;
vbuffery[0]=-100;
zlpoint(x,z,y);
if (vbufferz[0]>100)
if ((vbufferx[0]>-15)&(vbufferx[0]<175))
if ((vbuffery[0]>-15)&(vbuffery[0]<135))
{
r=srange(itx-rcamera[0],ity-rcamera[2]);
//r=srange(r,itz-camera[2]);

it=r/32666;

if (it==0) vis=1;
else
 {
ix=(rcamera[0]-itx)/it;
iy=(rcamera[2]-ity)/it;
iz=(rcamera[1]-itz)/it;

x=rcamera[0];
y=rcamera[2];
z=rcamera[1];
cx=x/65536;
cy=y/65536;
cz=z/65536;


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
}
return vis;
}






void FLOOD_Breeding(void)
{

Uint8 z=monster_cz[0];
Uint8 px,py;
Sint16 x,y,x0,x1,y0,y1;
Sint32 zt=z*16384;
x=monster_cx[0];    
y=monster_cy[0];
px=x;
py=y;
x0=x-4;
x1=x+4;
y0=y-4;
y1=y+4;
if (x0<0)x0=0;
if (y0<0)y0=0;
if (x1>=levelx)x1=levelx;
if (y1>=levely)y1=levely;

flood_breedi=0;
for (y=y0;y<=y1;y++)
for (x=x0;x<=x1;x++)
{
Uint8 p=player_proxy[x-px+4][y-py+4];
if (p>1 & p<13)
{
Sint32 ix,iy,iz;
ix=x*65536+32666;
iy=y*65536+32666;
iz=z*65536+32666;
if (flood_vis(ix,iy,iz)==0)
if (camera_vis(ix,iy,iz)==0)
{
Sint32 t=x+y*128+zt;
if ((mapobj[t]>1)&(mapobj[t]<33))
{
flood_breed[flood_breedi]=x;
flood_breed[flood_breedi+1]=y;
flood_breed[flood_breedi+2]=z;
flood_breed[flood_breedi+3]=mapobj[t]-1;
flood_breedi+=4;                                 
}
}}    
}
Uint8 newmonsters=(maxmonsters-monsters);
Uint8 freemonsters=flood_breedi/4;
while ((newmonsters>0)&(freemonsters>0))
{
Uint16 i;
i=random(freemonsters);
 spawnmonster(flood_breed[i*4],flood_breed[i*4+1],flood_breed[i*4+2],flood_breed[i*4+3]);

newmonsters--;     
freemonsters--;      
flood_breed[i*4]=flood_breed[freemonsters*4];
flood_breed[i*4+1]=flood_breed[freemonsters*4+1];
flood_breed[i*4+2]=flood_breed[freemonsters*4+2];
flood_breed[i*4+3]=flood_breed[freemonsters*4+3];

}


}

void FLOOD_Cleansing(void)
{
Uint8 i,enemy_of_flood;
for (i=1;i<16;i++)
if (monster_ingame[i])
 {
monster_flood_data[i]=table_vis[0][i];
//camera vis add bool add
if (monster_flood_data[i]==0)
monster_flood_data[i]=monster_flood_data[i]| camera_vis(monster_x[i],monster_y[i],monster_z[i]+t_monster_height[monster_type[i]]);

//monster_flood_data[i]=monster_flood_data[i] | flood_vis(monster_x[i],monster_y[i],monster_z[i]+t_monster_height[monster_type[i]]);
enemy_of_flood=0;
if (monster_flood_data[i]==0) monster_flood_score[i]++;
else monster_flood_score[i]=0;

if (monster_flood_score[i]>2) enemy_of_flood=1;
if (monsters>maxmonsters) enemy_of_flood=1;
if (monster_hp[i]==0) enemy_of_flood=1;

if (monster_deathtrigger[i]) enemy_of_flood=0;
//proxy
//and off-score



 if ((monster_flood_data[i]==0)&(enemy_of_flood)) 
 if (monster_status[i]& STATUS_BOSS)
 {if (monster_status[i]& STATUS_ALIVE==0)monster_kill(i);}
 else
 monster_kill(i);
 }
}

void ProcFLOOD(void)
{
floodcount++;
if (floodcount==25)
 {
 FLOOD_Cleansing();                   
 }
else
if (floodcount>50)
 {
 floodcount=0; 
if (maxmonsters>monsters)
 FLOOD_Breeding();

 }

//debugval0=flood_vis(monster_x[1],monster_y[1],monster_z[1]+t_monster_height[monster_type[1]]);
}
