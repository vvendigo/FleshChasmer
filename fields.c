#include <fields.h>
#include <globalvar.h>
#include <zmath.h>

//spawn of field begin
Uint8 field0_index,field0_type;
Sint32 field0_x ,field0_y ,field0_z ;
Sint32 field0_tx,field0_ty,field0_tz;
Sint32 field0_ix,field0_iy,field0_iz;
Sint32 field0_w,field0_iw;

//spawn of field end

void ProcFields(void)
{
for (Uint8 i=0;i<32;i++)     
if (field_ingame[i])
// else
 {
 field_x[i]+=field_ix[i];
 field_y[i]+=field_iy[i];
 field_z[i]+=field_iz[i];
 field_w[i]+=field_iw[i];

field_index[i]++;
 
 field_count[i]++;
 if (field_count[i]==8) field_ingame[i]=0;
 }
}

void SpawnField(void)
{
Uint8 i=0;
while ((i<32)&(field_ingame[i]))
i++;
if (i==32) i=random(32);
field_ingame[i]=1;

field_x[i]=field0_x;
field_y[i]=field0_y;
field_z[i]=field0_z;

field_ix[i]=field0_ix;
field_iy[i]=field0_iy;
field_iz[i]=field0_iz;

field_w[i]=field0_w;
field_iw[i]=field0_iw;
field_index[i]=field0_index;
field_count[i]=0;
}

void SpawnField0(Sint32 x,Sint32 y,Sint32 z,Uint8 t)
{
Uint8 i=0;
while ((i<32)&(field_ingame[i]))
i++;
if (i==32) i=random(32);
field_ingame[i]=1;

field_x[i]=x;
field_y[i]=y;
field_z[i]=z;

field_ix[i]=-500+random(1000);
field_iy[i]=-500+random(1000);
field_iz[i]=-500+random(1000);

field_w[i]=20000;
field_iw[i]=2000;
field_index[i]=248-t*8;
field_count[i]=0;
}

void SummonField(Uint8 index,Uint8 x,Uint8 y,Uint8 z)
{
       
}

void SummonFieldOn(Uint8 index,Uint8 target,Uint8 owner)
{
       
       
}
