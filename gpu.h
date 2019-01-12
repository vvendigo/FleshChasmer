//#include "globalvar.h"
#include "types.h"

extern void zlpoint(Sint32 vx,Sint32 vy,Sint32 vz);
extern void zlrotatex(Sint32 alpha);
extern void zlrotatey(Sint32 alpha);
extern void zlrotatez(Sint32 alpha);
extern void zltranslate(Sint32 x,Sint32 y,Sint32 z);
extern void zlpushmatrix(void);
extern void zlpopmatrix(void);

extern Uint8 modelcolor;

//extern void zltexpoly(void);
extern void zltexquad(void);
extern void zltexquada(void);

extern Uint16 zlvertex;
extern Uint8 vvis[3200];
extern Sint32 txbuffer[4],tybuffer[4],texture,vbufferx[3200],vbuffery[3200],vbufferz[3200];

extern void rendermodel(Uint8 index,Uint8 frame);
extern void renderanimmodel(Uint8 index,Uint8 frame0,Uint8 frame1,Uint8 animcount,Uint8 anim);
