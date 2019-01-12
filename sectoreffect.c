#include <sectoreffect.h>
#include <sound.h>
#include <zmath.h>


#include <globalvar.h>
void SectorEffect(Uint8 x,Uint8 y,Uint8 z)
{
Uint32 t=x+y*128+z*16384;
Uint8 effect=mapobj[t]-43;
switch (effect)
{
case 0://Flesh wall wave effect
Sint32 c=(count*31+x*50+y*2+z*5)%4096;
meshx[t]=x*65536+f_sin[c]/16;
meshy[t]=y*65536+f_cos[c]/16;
meshz[t]=z*65536+zabs(f_sin[(count*31+x*73+y*121+z*11)%2048]/16);
break;
}
}
