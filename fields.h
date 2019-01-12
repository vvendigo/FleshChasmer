#include <types.h>
extern void ProcFields(void);
extern void SpawnField(void);

extern Uint8 field0_index,field0_type;
extern Sint32 field0_x ,field0_y ,field0_z ;
extern Sint32 field0_tx,field0_ty,field0_tz;
extern Sint32 field0_ix,field0_iy,field0_iz;
extern Sint32 field0_w,field0_iw;

extern void SummonField(Uint8 index,Uint8 x,Uint8 y,Uint8 z);
extern void SummonFieldOn(Uint8 index,Uint8 target,Uint8 owner);
extern void SpawnField0(Sint32 x,Sint32 y,Sint32 z,Uint8 t);
