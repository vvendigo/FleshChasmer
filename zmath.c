#include "math.h"

#include "zmath.h"
#include "stdlib.h"
#include "globalvar.h"
#define FPDIV(x,y)	((((x)<<12)/((y)))>>4)

Uint16 arctan(Sint32 argx,Sint32 argy)
{
Sint16 val;       
Uint16 d,res; 
if (argx==0)
 {
  res=1024;          
 }
 else
 {
 d=1024;res=512;    
 val=FPDIV(argy,argx);    
 if (val<0) val=-val;
 while (d>1)
  {
   d=d>>1;    
  if (f_tan[res]>val) res=res-d;
  else    
  if (f_tan[res]<val) res=res+d;
  else d=0;
  }
 
 }
if ((argx<=0)&(argy>0)) res=2048-res;
else
if ((argx<=0)&(argy<0)) res=2048+res;
else
if ((argx>=0)&(argy<0)) res=4096-res;

return res;       
}

Uint32 fastrange(Sint32 argx,Sint32 argy)
{
Sint32 rs0,rs1;
rs0=argx;
rs1=argy;
if (rs0<0) rs0= - rs0;      
if (rs1<0) rs1= - rs1;      
if (rs0>rs1) return rs0; else return rs1;       
}


Uint32 srange(Sint32 argx,Sint32 argy)
{
float t0,t1,val;
t0=argx/65536;
t0=t0*t0;       
t1=argy/65536;
t1=t1*t1;       

val=sqrt(t0+t1);       
return 65536*val;       
}       
       
Uint16 rndseed,lrndseed;

Uint16 rnd(void)
{
rndseed=rand();
return rndseed;       
}

Uint16 random(Uint16 value)
{
       
return rnd()%value;       
}
Sint32 calcturn(Sint32 angle0,Sint32 angle1)
{
Sint32 de=(angle1-angle0);
if (de>2048) de=-4096+de;
else
if (de<-2048) de=4096+de;
       
return de;       
}
Sint32 zabs(Sint32 val)
{
if (val>=0) return val; else return -val;       
}


Sint16 SuperAngle(Sint32 value)
{
Sint16 val=value;
while (val<0) val+=4096;

while (val>=4096) val-=4096;
return val;
}

Sint32 FloorProbe(Sint32 x,Sint32 y,Sint32 z)
{
Uint8 cx=x>>16;
Uint8 cy=y>>16;
Uint8 cz=z>>16;
Sint32 t=cx+cy*128+cz*16384;
Sint32 ix=x-cx*65536;
Sint32 iy=y-cy*65536;
Sint32 rz,a,b;
a=meshz[t]+((meshz[t+1])-meshz[t])*ix/65536;
b=meshz[t+128]+((meshz[t+129])-meshz[t+128])*ix/65536;

rz=a+(b-a)*iy/65536;
return rz;
//add some level-end detection;     
}
