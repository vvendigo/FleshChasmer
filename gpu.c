#include "gpu.h"
#include "zmath.h"
#include "sfont.h"
#include "globalvar.h"

#define FPMUL(x,y)	((((x)>>6)*((y)>>6))>>4)
#define FPDIV(x,y)	((((x)<<6)/((y)>>6))>>4)
//#define FPDIV(x,y)	((((x)<<6)/((y)>>2)))
#define FPMUL2(x,y)	((((x)>>8)*((y)))>>8)
#define FPMUL3(x,y)	((((x)>>8)*((y)))>>8)

Sint32 matrix2[16],mmatrix[16];
Uint8 vvis[3200],tcolor;
Uint16 zlvertex;
Sint32 vbufferx[3200],vbuffery[3200],vbufferz[3200],txbuffer[4],tybuffer[4],texture;
Uint8 modelcolor;

Sint32 matrixstack[16];
void zlpushmatrix(void)
{
for (Uint8 i=0;i<16;i++)     
matrixstack[i]=matrix[i];
}
void zlpopmatrix(void)
{
for (Uint8 i=0;i<16;i++)     
matrix[i]=matrixstack[i];
}

void zlpoint(Sint32 vx,Sint32 vy,Sint32 vz)
{
Sint32 x,y,t;
Sint32 v[4],v1[4];

v[0]=vx;v[1]=vy;v[2]=vz;v[3]=65536;
for (t=0;t<4;t++)
{v1[t]=0;
for (x=0;x<4;x++)
v1[t]+=FPMUL(v[x],matrix[x+t*4]);
}

t=v1[2]+dist;
if (t!=0)

if (v1[2]>-dist0)
{
vvis[zlvertex]=1;
vbufferx[zlvertex]=80+FPDIV(FPMUL(v1[0],dist),t);
vbuffery[zlvertex]=60-FPDIV(FPMUL(v1[1],dist),t);
vbufferz[zlvertex]=v1[2];
}else vvis[zlvertex]=0;
}





Sint32 ctexx,ctexy,texx0,texx1,texy0,texy1,dtexx,dtexy,xt,yt,cz0,cz1,cz,dz;

void zltexquada(void)
{
Sint32 i,x,y,x0,y0,x1,y1,x2,y2,x3,y3,xa,xb,xd,z,ly01,ly12,ly02,ly03,ly13,ly23,temp_deltay,temp0,xbxa,tempy;
Sint32 linedat0,linedat13,linedat12,linedat23,linedat2,linedat3;
Sint32 dtex0,dtex1,dtey0,dtey1,dz0,dz1,ly01d,ly02d,ly03d,ly12d,ly13d,ly23d;
Uint8 typeB;

if (vvis[0]&&vvis[1]&&vvis[2]&&vvis[3])
{     
Uint8 t,par[4];
par[0]=0;
par[1]=1;
par[2]=2;
par[3]=3;

for (i=0;i<3;i++)
 for (int k=0;k<3;k++)
  {
  if (vbuffery[par[k]]>vbuffery[par[k+1]])        
   {
    t=par[k];
    par[k]=par[k+1];
    par[k+1]=t;
   }                                     
  }
x0=vbufferx[par[0]];
x1=vbufferx[par[1]];
x2=vbufferx[par[2]];
x3=vbufferx[par[3]];

y0=vbuffery[par[0]];
y1=vbuffery[par[1]];
y2=vbuffery[par[2]];
y3=vbuffery[par[3]];


if ((y0>screen0_y1)||(y3<screen0_y0)) return;


ly01=(y1-y0);if (ly01) ly01d=65536/ly01;
ly02=(y2-y0);if (ly02) ly02d=65536/ly02;
ly03=(y3-y0);if (ly03) ly03d=65536/ly03;
ly12=(y2-y1);if (ly12) ly12d=65536/ly12;
ly13=(y3-y1);if (ly13) ly13d=65536/ly13;
ly23=(y3-y2);if (ly23) ly23d=65536/ly23;

cz=-(y3-y0);
dz=(x3-x0);
temp_deltay=(x0*cz+y0*dz);
typeB=((((x1)*cz+(y1)*dz-temp_deltay)>>6)*(((x2)*cz+(y2)*dz-temp_deltay)>>6)>1);


if (y1!=y0)
linedat0=((x1-x0)<<8)/(ly01);
if (y2!=y0)
linedat2=((x2-x0)<<8)/(ly02);
if (y3!=y0)
linedat3=((x3-x0)<<8)/(ly03);
if (y2!=y3)
linedat23=((x3-x2)<<8)/(ly23);

if (y1!=y3)
linedat13=((x3-x1)<<8)/(ly13);

if (y1!=y2)
linedat12=((x2-x1)<<8)/(ly12);


  {
  if (y0!=y1)                    
if ((y1>=screen0_y0)&&(y0<=screen0_y1))
{

 texx1=txbuffer[par[0]];
 texy1=tybuffer[par[0]];
 texx0=texx1;
 texy0=texy1;
 cz0=vbufferz[par[0]];
 cz1=cz0;

dtex0=FPMUL3(txbuffer[par[1]]-txbuffer[par[0]],ly01d);
dtey0=FPMUL3(tybuffer[par[1]]-tybuffer[par[0]],ly01d);
  dz0=FPMUL3(vbufferz[par[1]]-vbufferz[par[0]],ly01d);

if (typeB)
    {
  dtex1=FPMUL3(txbuffer[par[3]]-txbuffer[par[0]],ly03d);
  dtey1=FPMUL3(tybuffer[par[3]]-tybuffer[par[0]],ly03d);
  dz1=  FPMUL3(vbufferz[par[3]]-vbufferz[par[0]],ly03d);

    }
    else
    {
  dtex1=FPMUL3(txbuffer[par[2]]-txbuffer[par[0]],ly02d);
  dtey1=FPMUL3(tybuffer[par[2]]-tybuffer[par[0]],ly02d);
  dz1=  FPMUL3(vbufferz[par[2]]-vbufferz[par[0]],ly02d);
        
        
    }

  for (y=y0;y<y1;y++)
{
   
      
if ((y>=screen0_y0)&&(y<screen0_y1))
    {
  tempy=y*160;
  xa=x0+((y-y0)*linedat0>>8);
  if (typeB)
  xb=x0+((y-y0)*linedat3>>8);
  else
  xb=x0+((y-y0)*linedat2>>8);
  xbxa=xb-xa;
  if (xbxa)
 {
  temp0=65536/xbxa;
  dtexx=FPMUL2(texx1-texx0,temp0);
  dtexy=FPMUL2(texy1-texy0,temp0);
     dz=FPMUL2(cz1-cz0    ,temp0);

  ctexy=texy0;
  ctexx=texx0;
  cz=cz0;
  if (xb>xa)
{
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<screen0_x1)&&(xb>screen0_x0))
     for (x=xa;x<=xb;x++)
 {

         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
  {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
       if (tcolor)
   {
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
   }
  }
         ctexx+=dtexx;
         ctexy+=dtexy;
         cz+=dz;
 }       
}else
{    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
 {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;

         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
  {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
       if (tcolor)
   {
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
   }
  }
         ctexx-=dtexx;
         ctexy-=dtexy;
         cz-=dz;
 }
}
       
} 
}                    
texx0+=dtex0;
texy0+=dtey0;

texx1+=dtex1;
texy1+=dtey1;
cz0+=dz0;
cz1+=dz1;

}} 
  
  if ((y2!=y1))                    

 if ((y1<=screen0_y1)&&(y2>=screen0_y0))
{
    
    
  if (typeB)
    {
 texx0=txbuffer[par[0]]+FPMUL3(txbuffer[par[3]]-txbuffer[par[0]],ly03d)*ly01;
 texy0=tybuffer[par[0]]+FPMUL3(tybuffer[par[3]]-tybuffer[par[0]],ly03d)*ly01;
 cz0=vbufferz[par[0]]+  FPMUL3(vbufferz[par[3]]-vbufferz[par[0]],ly03d)*ly01;

dtex0=FPMUL3(txbuffer[par[3]]-txbuffer[par[0]],ly03d);
dtey0=FPMUL3(tybuffer[par[3]]-tybuffer[par[0]],ly03d);
dz0=  FPMUL3(vbufferz[par[3]]-vbufferz[par[0]],ly03d);

 texx1=txbuffer[par[1]];
 texy1=tybuffer[par[1]];
 cz1=  vbufferz[par[1]];


dtex1=FPMUL3(txbuffer[par[2]]-txbuffer[par[1]],ly12d);
dtey1=FPMUL3(tybuffer[par[2]]-tybuffer[par[1]],ly12d);
  dz1=FPMUL3(vbufferz[par[2]]-vbufferz[par[1]],ly12d);

    }
    else
    {
 texx0=txbuffer[par[1]];
 texy0=tybuffer[par[1]];
 cz0=vbufferz[par[1]];

dtex0=FPMUL3(txbuffer[par[3]]-txbuffer[par[1]],ly13d);
dtey0=FPMUL3(tybuffer[par[3]]-tybuffer[par[1]],ly13d);
dz0=FPMUL3(vbufferz[par[3]]-vbufferz[par[1]],ly13d);


 texx1=txbuffer[par[0]]+FPMUL3(txbuffer[par[2]]-txbuffer[par[0]],ly02d)*ly01;
 texy1=tybuffer[par[0]]+FPMUL3(tybuffer[par[2]]-tybuffer[par[0]],ly02d)*ly01;
 cz1=vbufferz[par[0]]+  FPMUL3(vbufferz[par[2]]-vbufferz[par[0]],ly02d)*ly01;

dtex1=FPMUL3(txbuffer[par[2]]-txbuffer[par[0]],ly02d);
dtey1=FPMUL3(tybuffer[par[2]]-tybuffer[par[0]],ly02d);
  dz1=FPMUL3(vbufferz[par[2]]-vbufferz[par[0]],ly02d);
   
    }

  for (y=y1;y<y2;y++)
{

  if ((y>=screen0_y0)&&(y<screen0_y1))
  {
  tempy=y*160;
  if (typeB)
  {
  xa=x0+((y-y0)*linedat3>>8);
  xb=x1+((y-y1)*linedat12>>8);
  }
  else
  {
  xa=x1+((y-y1)*linedat13>>8);
  xb=x0+((y-y0)*linedat2>>8);
  }

  xbxa=xb-xa;
  if (xbxa)
  {
  temp0=65536/xbxa;
  dtexx=FPMUL2(texx1-texx0,temp0);
  dtexy=FPMUL2(texy1-texy0,temp0);
     dz=FPMUL2(cz1-cz0    ,temp0);


  ctexx=texx0;
  ctexy=texy0;

  cz=cz0;
  }
  if (xb>xa)
    {
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<screen0_x1)&&(xb>screen0_x0))
     for (x=xa;x<=xb;x++)
      {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
       {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
       if (tcolor)
        {
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
        }
       }
         ctexx+=dtexx;
         ctexy+=dtexy;
         cz+=dz;

      }       
    }else
{    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
       {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+y*160;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
        {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
       if (tcolor)
         {
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
         }
        }
         ctexx-=dtexx;
         ctexy-=dtexy;
         cz-=dz;

       }       
}  
  
}

texx0+=dtex0;
texy0+=dtey0;
texx1+=dtex1;
texy1+=dtey1;
cz0+=dz0;
cz1+=dz1;

} 
  }                    
 ///////////////////////////////////////////////////// 
  if (y2!=y3)                    
 if ((y2<=screen0_y1)&&(y3>=screen0_y0))
{
    
  
 texx1=txbuffer[par[3]];
 texy1=tybuffer[par[3]];
 texx0=texx1;
 texy0=texy1;
 cz0=vbufferz[par[3]];
 cz1=cz0;
dtex0=FPMUL3(txbuffer[par[2]]-txbuffer[par[3]],ly23d);
dtey0=FPMUL3(tybuffer[par[2]]-tybuffer[par[3]],ly23d);
  dz0=FPMUL3(vbufferz[par[2]]-vbufferz[par[3]],ly23d);
if (typeB)
    {
  dtex1=FPMUL3(txbuffer[par[0]]-txbuffer[par[3]],ly03d);
  dtey1=FPMUL3(tybuffer[par[0]]-tybuffer[par[3]],ly03d);
  dz1=  FPMUL3(vbufferz[par[0]]-vbufferz[par[3]],ly03d);

    }
    else
    {
  dtex1=FPMUL3(txbuffer[par[1]]-txbuffer[par[3]],ly13d);
  dtey1=FPMUL3(tybuffer[par[1]]-tybuffer[par[3]],ly13d);
  dz1=  FPMUL3(vbufferz[par[1]]-vbufferz[par[3]],ly13d);
        
        
    }
  
  for (y=y3-1;y>=y2;y--)
{
texx0+=dtex0;
texy0+=dtey0;
texx1+=dtex1;
texy1+=dtey1;
cz0+=dz0;
cz1+=dz1;
  tempy=y*160;
   
    
  if ((y>=screen0_y0)&&(y<screen0_y1))
  {
  xa=x3+((y-y3)*linedat23>>8);
  if (typeB)
  xb=x3+((y-y3)*linedat3>>8);
  else
  xb=x3+((y-y3)*linedat13>>8);
  
  xbxa=xb-xa;
  if (xbxa)
  {
  if (xbxa==1)
   {
   dtexx=0;
   dtexy=0;
   dz=0;           
   }
   else
   {
  temp0=65536/xbxa;
  dtexx=FPMUL2(texx1-texx0,temp0);
  dtexy=FPMUL2(texy1-texy0,temp0);
     dz=FPMUL2(cz1-cz0    ,temp0);
   }
  ctexx=texx0;
  ctexy=texy0;
  cz=cz0;
  

  if (xb>xa)
    {
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<=screen0_x1)&&(xb>=screen0_x0))
     for (x=xa;x<=xb;x++)
      {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
       {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
       if (tcolor)
        {
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
        }
       }
         ctexx+=dtexx;
         ctexy+=dtexy;
         cz+=dz;

      }       
    }else
{
    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
      {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
       {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
       if (tcolor)
        {
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
        }
       }
         ctexx-=dtexx;
         ctexy-=dtexy;
         cz-=dz;

      }       
   
  
}
}                       
  } }    

}                     
 }     
     
 }     
}//PLEASE PROTECT


void zltexquad(void)
{
Sint32 i,x,y,x0,y0,x1,y1,x2,y2,x3,y3,xa,xb,xd,z,ly01,ly12,ly02,ly03,ly13,ly23,temp_deltay,temp0,xbxa,tempy;
Sint32 linedat0,linedat13,linedat12,linedat23,linedat2,linedat3;
Sint32 dtex0,dtex1,dtey0,dtey1,dz0,dz1,ly01d,ly02d,ly03d,ly12d,ly13d,ly23d;
Uint8 typeB;

if (vvis[0]&&vvis[1]&&vvis[2]&&vvis[3])
{     
Uint8 t,par[4];
par[0]=0;
par[1]=1;
par[2]=2;
par[3]=3;

for (i=0;i<3;i++)
 for (int k=0;k<3;k++)
  {
  if (vbuffery[par[k]]>vbuffery[par[k+1]])        
   {
    t=par[k];
    par[k]=par[k+1];
    par[k+1]=t;
   }                                     
  }
x0=vbufferx[par[0]];
x1=vbufferx[par[1]];
x2=vbufferx[par[2]];
x3=vbufferx[par[3]];

y0=vbuffery[par[0]];
y1=vbuffery[par[1]];
y2=vbuffery[par[2]];
y3=vbuffery[par[3]];


if ((y0>screen0_y1)||(y3<screen0_y0)) return;


ly01=(y1-y0);if (ly01) ly01d=65536/ly01;
ly02=(y2-y0);if (ly02) ly02d=65536/ly02;
ly03=(y3-y0);if (ly03) ly03d=65536/ly03;
ly12=(y2-y1);if (ly12) ly12d=65536/ly12;
ly13=(y3-y1);if (ly13) ly13d=65536/ly13;
ly23=(y3-y2);if (ly23) ly23d=65536/ly23;

cz=-(y3-y0);
dz=(x3-x0);
temp_deltay=(x0*cz+y0*dz);
typeB=((((x1)*cz+(y1)*dz-temp_deltay)>>6)*(((x2)*cz+(y2)*dz-temp_deltay)>>6)>1);


if (y1!=y0)
linedat0=((x1-x0)<<8)/(ly01);
if (y2!=y0)
linedat2=((x2-x0)<<8)/(ly02);
if (y3!=y0)
linedat3=((x3-x0)<<8)/(ly03);
if (y2!=y3)
linedat23=((x3-x2)<<8)/(ly23);

if (y1!=y3)
linedat13=((x3-x1)<<8)/(ly13);

if (y1!=y2)
linedat12=((x2-x1)<<8)/(ly12);


  {
  if (y0!=y1)                    
if ((y1>=screen0_y0)&&(y0<=screen0_y1))
{

 texx1=txbuffer[par[0]];
 texy1=tybuffer[par[0]];
 texx0=texx1;
 texy0=texy1;
 cz0=vbufferz[par[0]];
 cz1=cz0;

dtex0=FPMUL3(txbuffer[par[1]]-txbuffer[par[0]],ly01d);
dtey0=FPMUL3(tybuffer[par[1]]-tybuffer[par[0]],ly01d);
  dz0=FPMUL3(vbufferz[par[1]]-vbufferz[par[0]],ly01d);

if (typeB)
    {
  dtex1=FPMUL3(txbuffer[par[3]]-txbuffer[par[0]],ly03d);
  dtey1=FPMUL3(tybuffer[par[3]]-tybuffer[par[0]],ly03d);
  dz1=  FPMUL3(vbufferz[par[3]]-vbufferz[par[0]],ly03d);

    }
    else
    {
  dtex1=FPMUL3(txbuffer[par[2]]-txbuffer[par[0]],ly02d);
  dtey1=FPMUL3(tybuffer[par[2]]-tybuffer[par[0]],ly02d);
  dz1=  FPMUL3(vbufferz[par[2]]-vbufferz[par[0]],ly02d);
        
        
    }

  for (y=y0;y<y1;y++)
{
   
      
if ((y>=screen0_y0)&&(y<screen0_y1))
    {
  tempy=y*160;
  xa=x0+((y-y0)*linedat0>>8);
  if (typeB)
  xb=x0+((y-y0)*linedat3>>8);
  else
  xb=x0+((y-y0)*linedat2>>8);
  xbxa=xb-xa;
  if (xbxa)
 {
  temp0=65536/xbxa;
  dtexx=FPMUL2(texx1-texx0,temp0);
  dtexy=FPMUL2(texy1-texy0,temp0);
     dz=FPMUL2(cz1-cz0    ,temp0);

  ctexy=texy0;
  ctexx=texx0;
  cz=cz0;
  if (xb>xa)
{
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<screen0_x1)&&(xb>screen0_x0))
     for (x=xa;x<=xb;x++)
 {

         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
  {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
  }
         ctexx+=dtexx;
         ctexy+=dtexy;
         cz+=dz;
 }       
}else
{    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
 {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;

         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
  {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
  }
         ctexx-=dtexx;
         ctexy-=dtexy;
         cz-=dz;
 }
}
       
} 
}                    
texx0+=dtex0;
texy0+=dtey0;

texx1+=dtex1;
texy1+=dtey1;
cz0+=dz0;
cz1+=dz1;

}} 
  
  if ((y2!=y1))                    

 if ((y1<=screen0_y1)&&(y2>=screen0_y0))
{
    
    
  if (typeB)
    {
 texx0=txbuffer[par[0]]+FPMUL3(txbuffer[par[3]]-txbuffer[par[0]],ly03d)*ly01;
 texy0=tybuffer[par[0]]+FPMUL3(tybuffer[par[3]]-tybuffer[par[0]],ly03d)*ly01;
 cz0=vbufferz[par[0]]+  FPMUL3(vbufferz[par[3]]-vbufferz[par[0]],ly03d)*ly01;

dtex0=FPMUL3(txbuffer[par[3]]-txbuffer[par[0]],ly03d);
dtey0=FPMUL3(tybuffer[par[3]]-tybuffer[par[0]],ly03d);
dz0=  FPMUL3(vbufferz[par[3]]-vbufferz[par[0]],ly03d);

 texx1=txbuffer[par[1]];
 texy1=tybuffer[par[1]];
 cz1=  vbufferz[par[1]];


dtex1=FPMUL3(txbuffer[par[2]]-txbuffer[par[1]],ly12d);
dtey1=FPMUL3(tybuffer[par[2]]-tybuffer[par[1]],ly12d);
  dz1=FPMUL3(vbufferz[par[2]]-vbufferz[par[1]],ly12d);

    }
    else
    {
 texx0=txbuffer[par[1]];
 texy0=tybuffer[par[1]];
 cz0=vbufferz[par[1]];

dtex0=FPMUL3(txbuffer[par[3]]-txbuffer[par[1]],ly13d);
dtey0=FPMUL3(tybuffer[par[3]]-tybuffer[par[1]],ly13d);
dz0=FPMUL3(vbufferz[par[3]]-vbufferz[par[1]],ly13d);


 texx1=txbuffer[par[0]]+FPMUL3(txbuffer[par[2]]-txbuffer[par[0]],ly02d)*ly01;
 texy1=tybuffer[par[0]]+FPMUL3(tybuffer[par[2]]-tybuffer[par[0]],ly02d)*ly01;
 cz1=vbufferz[par[0]]+  FPMUL3(vbufferz[par[2]]-vbufferz[par[0]],ly02d)*ly01;

dtex1=FPMUL3(txbuffer[par[2]]-txbuffer[par[0]],ly02d);
dtey1=FPMUL3(tybuffer[par[2]]-tybuffer[par[0]],ly02d);
  dz1=FPMUL3(vbufferz[par[2]]-vbufferz[par[0]],ly02d);
   
    }

  for (y=y1;y<y2;y++)
{

  if ((y>=screen0_y0)&&(y<screen0_y1))
  {
  tempy=y*160;
  if (typeB)
  {
  xa=x0+((y-y0)*linedat3>>8);
  xb=x1+((y-y1)*linedat12>>8);
  }
  else
  {
  xa=x1+((y-y1)*linedat13>>8);
  xb=x0+((y-y0)*linedat2>>8);
  }

  xbxa=xb-xa;
  if (xbxa)
  {
  temp0=65536/xbxa;
  dtexx=FPMUL2(texx1-texx0,temp0);
  dtexy=FPMUL2(texy1-texy0,temp0);
     dz=FPMUL2(cz1-cz0    ,temp0);


  ctexx=texx0;
  ctexy=texy0;

  cz=cz0;
  }
  if (xb>xa)
    {
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<screen0_x1)&&(xb>screen0_x0))
     for (x=xa;x<=xb;x++)
      {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
       {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
       }
         ctexx+=dtexx;
         ctexy+=dtexy;
         cz+=dz;

      }       
    }else
{    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
       {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+y*160;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
        {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
        }
         ctexx-=dtexx;
         ctexy-=dtexy;
         cz-=dz;

       }       
}  
  
}

texx0+=dtex0;
texy0+=dtey0;
texx1+=dtex1;
texy1+=dtey1;
cz0+=dz0;
cz1+=dz1;

} 
  }                    
 ///////////////////////////////////////////////////// 
  if (y2!=y3)                    
 if ((y2<=screen0_y1)&&(y3>=screen0_y0))
{
    
  
 texx1=txbuffer[par[3]];
 texy1=tybuffer[par[3]];
 texx0=texx1;
 texy0=texy1;
 cz0=vbufferz[par[3]];
 cz1=cz0;



dtex0=FPMUL3(txbuffer[par[2]]-txbuffer[par[3]],ly23d);
dtey0=FPMUL3(tybuffer[par[2]]-tybuffer[par[3]],ly23d);
  dz0=FPMUL3(vbufferz[par[2]]-vbufferz[par[3]],ly23d);

if (typeB)
    {
  dtex1=FPMUL3(txbuffer[par[0]]-txbuffer[par[3]],ly03d);
  dtey1=FPMUL3(tybuffer[par[0]]-tybuffer[par[3]],ly03d);
  dz1=  FPMUL3(vbufferz[par[0]]-vbufferz[par[3]],ly03d);

    }
    else
    {
  dtex1=FPMUL3(txbuffer[par[1]]-txbuffer[par[3]],ly13d);
  dtey1=FPMUL3(tybuffer[par[1]]-tybuffer[par[3]],ly13d);
  dz1=  FPMUL3(vbufferz[par[1]]-vbufferz[par[3]],ly13d);
        
        
    }
  //Sint32 cleverZ=vbufferz[par[3]];
  for (y=y3-1;y>=y2;y--)
{
texx0+=dtex0;
texy0+=dtey0;
texx1+=dtex1;
texy1+=dtey1;
cz0+=dz0;
cz1+=dz1;
//if (cz0<cleverZ) cz0=cleverZ;
//if (cz1<cleverZ) cz1=cleverZ;
  tempy=y*160;
   
    
  if ((y>=screen0_y0)&&(y<screen0_y1))
  {
  xa=x3+((y-y3)*linedat23>>8);
  if (typeB)
  xb=x3+((y-y3)*linedat3>>8);
  else
  xb=x3+((y-y3)*linedat13>>8);
  
  xbxa=xb-xa;
  if (xbxa)
  {
   if (zabs(xbxa)>3)
   {
           
  temp0=65536/xbxa;
  dtexx=FPMUL2(texx1-texx0,temp0);
  dtexy=FPMUL2(texy1-texy0,temp0);
     dz=FPMUL2(cz1-cz0    ,temp0);
   }
  ctexx=texx0;
  ctexy=texy0;
  cz=cz0;
  //dz=0;
  

  if (xb>xa)
    {
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<=screen0_x1)&&(xb>=screen0_x0))
     for (x=xa;x<=xb;x++)
      {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
       {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
       }
         ctexx+=dtexx;
         ctexy+=dtexy;
         cz+=dz;
      }       
    }else
{
    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
      {
         xt=ctexx>>12;                
         yt=ctexy>>12;
         xt=xt & 15;
         yt=yt & 15;
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>cz)
       {
        tcolor=Tile[Tile_offset[texture]+xt+yt*16];                
        zbuffer0[i]=cz;                 
        scrbuf0[i]=tcolor;
       }
         ctexx-=dtexx;
         ctexy-=dtexy;
         cz-=dz;

      }       
   
  
}
}                       
//texx0+=dtex0;
//texy0+=dtey0;
//texx1+=dtex1;
//texy1+=dtey1;
//cz0+=dz0;
//cz1+=dz1;
  }     

} }                    
 }     
     
 }     
}//PLEASE PROTECT




void matrixmul(void)
{
int x,y,i;     
for (y=0;y<4;y++)
for (x=0;x<4;x++)
 {
  mmatrix[x+y*4]=0;
 for (i=0;i<4;i++)
  mmatrix[x+y*4]+=FPMUL(matrix[i+y*4],matrix2[x+i*4]);  
 }   
 for (i=0;i<16;i++) matrix[i]=mmatrix[i];
     
}

void zlrotatey(Sint32 alpha)
{
Sint32 sy = f_sin[alpha];
Sint32 cy = f_cos[alpha];
matrix2[0]=cy;matrix2[1]=0;matrix2[2]=-sy;matrix2[3]=0;
matrix2[4]=0;matrix2[5]=65536;matrix2[6]=0;matrix2[7]=0;
matrix2[8]=sy;matrix2[9]=0;matrix2[10]=cy;matrix2[11]=0;       
matrix2[12]=0;matrix2[13]=0;matrix2[14]=0;matrix2[15]=65536;

matrixmul();
}

void zlrotatex(Sint32 alpha)
{
Sint32 sy = f_sin[alpha];
Sint32 cy = f_cos[alpha];

matrix2[0]=65536;matrix2[1]=0;matrix2[2]=-0;matrix2[3]=0;
matrix2[4]=0;matrix2[5]=cy;matrix2[6]=-sy;matrix2[7]=0;
matrix2[8]=0;matrix2[9]=sy;matrix2[10]=cy;matrix2[11]=0;       
matrix2[12]=0;matrix2[13]=0;matrix2[14]=0;matrix2[15]=65536;

matrixmul();
}
void zlrotatez(Sint32 alpha)
{
Sint32 sy = f_sin[alpha];
Sint32 cy = f_cos[alpha];

matrix2[0]=cy;matrix2[1]=-sy;matrix2[2]=0;matrix2[3]=0;
matrix2[4]=sy;matrix2[5]=cy;matrix2[6]=0;matrix2[7]=0;
matrix2[8]=0;matrix2[9]=0;matrix2[10]=65536;matrix2[11]=0;       
matrix2[12]=0;matrix2[13]=0;matrix2[14]=0;matrix2[15]=65536;

matrixmul();
}

void zltranslate(Sint32 x,Sint32 y,Sint32 z)
{
matrix2[0]=65536;matrix2[1]=0;matrix2[2]=0;matrix2[3]=x;
matrix2[4]=0;matrix2[5]=65536;matrix2[6]=0;matrix2[7]=y;
matrix2[8]=0;matrix2[9]=0;matrix2[10]=65536;matrix2[11]=z;       
matrix2[12]=0;matrix2[13]=0;matrix2[14]=0;matrix2[15]=65536;

matrixmul();
}




////////////////////////////////////////////////
void rendermodel(Uint8 index,Uint8 frame)
{
Sint32 x,y,x0,y0,x1,y1,x2,y2,xa,xb,xd,z,ly01,ly12,ly02,ly03,temp0,xbxa;
Sint32 linedat0,linedat12,linedat2,setz,tempy;


Uint16 i,f,v,delta;
Uint8 t,par[3],color,fi;


     
v=model_v0[index];
f=model_f0[index];


delta=model_v0[index]+model_vs[index]*frame;     
for (zlvertex=0;zlvertex<model_vs[index];zlvertex++)
zlpoint(m_vx[zlvertex+delta],m_vy[zlvertex+delta],m_vz[zlvertex+delta]);     

for (fi=0;fi<model_fs[index];fi++)
{
par[0]=f_0[f];
par[1]=f_1[f];
par[2]=f_2[f];
if (modelcolor) color=modelcolor;
else
color=f_c[f];
f++;
if (vvis[par[0]]&&vvis[par[1]]&&vvis[par[2]])
{     

for (i=0;i<2;i++)
 for (int k=0;k<2;k++)
  {
  if (vbuffery[par[k]]>vbuffery[par[k+1]])        
   {
    t=par[k];
    par[k]=par[k+1];
    par[k+1]=t;
   }                                     
  }
x0=vbufferx[par[0]];
x1=vbufferx[par[1]];
x2=vbufferx[par[2]];

y0=vbuffery[par[0]];
y1=vbuffery[par[1]];
y2=vbuffery[par[2]];


//if ((y0>screen0_y1)||(y2<screen0_y0)) return;


ly01=(y1-y0);
ly02=(y2-y0);
ly12=(y2-y1);
/*
setz=(vbufferz[par[0]]);
if (vbufferz[par[1]]<setz)
setz=(vbufferz[par[1]]);
else
if (vbufferz[par[2]]<setz)
setz=(vbufferz[par[2]]);
*/
setz=(vbufferz[par[2]]+vbufferz[par[1]]+vbufferz[par[0]])/3;
setz-=1000;
if (y1!=y0)
linedat0=((x1-x0)<<8)/(ly01);
if (y2!=y0)
linedat2=((x2-x0)<<8)/(ly02);
if (y1!=y2)
linedat12=((x2-x1)<<8)/(ly12);


  if (y0!=y1)                    
if ((y1>=screen0_y0)&&(y0<=screen0_y1))
{
  for (y=y0;y<y1;y++)
{
   
      
if ((y>=screen0_y0)&&(y<screen0_y1))
    {
  tempy=y*160;
  xa=x0+((y-y0)*linedat0>>8);
  xb=x0+((y-y0)*linedat2>>8);
  xbxa=xb-xa;
//  if (xbxa)
 {

  if (xb>xa)
{
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<screen0_x1)&&(xb>screen0_x0))
     for (x=xa;x<=xb;x++)
 {
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>setz)
  {
        zbuffer0[i]=setz;                 
        scrbuf0[i]=color;
  }
 }       
}else
{    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
 {
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>setz)
  {
        zbuffer0[i]=setz;                 
        scrbuf0[i]=color;
  }
 }
}
      
} 
}                    

}} 
///

  if (y1!=y2)                    
if ((y2>=screen0_y0)&&(y1<=screen0_y1))
{
  for (y=y2-1;y>=y1;y--)
{
   
      
if ((y>=screen0_y0)&&(y<screen0_y1))
    {
  tempy=y*160;
  xa=x2+((y-y2)*linedat12>>8);
  xb=x2+((y-y2)*linedat2>>8);
  xbxa=xb-xa;
//  if (xbxa)
 {

  if (xb>xa)
{
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<screen0_x1)&&(xb>screen0_x0))
     for (x=xa;x<=xb;x++)
 {
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>setz)
  {
        zbuffer0[i]=setz;                 
        scrbuf0[i]=color;
  }
 }       
}else
{    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
 {
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>setz)
  {
        zbuffer0[i]=setz;                 
        scrbuf0[i]=color;
  }
 }
}
      
} 
}                    

}} 
///


    
 }
}
     
}


///////////////////////////
void renderanimmodel(Uint8 index,Uint8 frame0,Uint8 frame1,Uint8 animcount,Uint8 anim)
{
Sint32 x,y,x0,y0,x1,y1,x2,y2,xa,xb,xd,z,ly01,ly12,ly02,ly03,temp0,xbxa;
Sint32 linedat0,linedat12,linedat2,setz,tempy;

Uint32 v0,v1;
Uint16 i,f,v,delta0,delta1;
Uint8 t,par[3],color,fi;


     
v=model_v0[index];
f=model_f0[index];


delta0=model_v0[index]+model_vs[index]*frame0;     
delta1=model_v0[index]+model_vs[index]*frame1;     

for (zlvertex=0;zlvertex<model_vs[index];zlvertex++)
{
    v0=zlvertex+delta0;
    v1=zlvertex+delta1;
zlpoint(
m_vx[v0]+((m_vx[v1]-m_vx[v0])*animcount)/anim,
m_vy[v0]+((m_vy[v1]-m_vy[v0])*animcount)/anim,
m_vz[v0]+((m_vz[v1]-m_vz[v0])*animcount)/anim
);     
}
Sint32 m_borderx0,m_borderx1,m_bordery0,m_bordery1;
m_borderx0=vbufferx[0];
m_borderx1=vbufferx[0];
m_bordery0=vbuffery[0];
m_bordery1=vbuffery[0];

for (zlvertex=1;zlvertex<model_vs[index];zlvertex++)
{
if (vbufferx[zlvertex]>m_borderx1)
m_borderx1=vbufferx[zlvertex];else
if (vbufferx[zlvertex]<m_borderx0)
m_borderx0=vbufferx[zlvertex];

if (vbuffery[zlvertex]>m_bordery1)
m_bordery1=vbuffery[zlvertex];else
if (vbuffery[zlvertex]<m_bordery0)
m_bordery0=vbuffery[zlvertex];

}
if ((m_borderx0<320))
if ((m_bordery0<240))
if ((m_borderx1>0))
if ((m_bordery1>0))
{
Model_Faces+=model_fs[index];
for (fi=0;fi<model_fs[index];fi++)
{
par[0]=f_0[f];
par[1]=f_1[f];
par[2]=f_2[f];
if (modelcolor) color=modelcolor;
else
color=f_c[f];

f++;
if (vvis[par[0]]&&vvis[par[1]]&&vvis[par[2]])
{     

for (i=0;i<2;i++)
 for (int k=0;k<2;k++)
  {
  if (vbuffery[par[k]]>vbuffery[par[k+1]])        
   {
    t=par[k];
    par[k]=par[k+1];
    par[k+1]=t;
   }                                     
  }
x0=vbufferx[par[0]];
x1=vbufferx[par[1]];
x2=vbufferx[par[2]];

y0=vbuffery[par[0]];
y1=vbuffery[par[1]];
y2=vbuffery[par[2]];


//if ((y0>screen0_y1)||(y2<screen0_y0)) return;


ly01=(y1-y0);
ly02=(y2-y0);
ly12=(y2-y1);
/*
setz=(vbufferz[par[0]]);
if (vbufferz[par[1]]<setz)
setz=(vbufferz[par[1]]);
else
if (vbufferz[par[2]]<setz)
setz=(vbufferz[par[2]]);
*/
setz=(vbufferz[par[2]]+vbufferz[par[1]]+vbufferz[par[0]])/3;

setz-=1000;
if (y1!=y0)
linedat0=((x1-x0)<<8)/(ly01);
if (y2!=y0)
linedat2=((x2-x0)<<8)/(ly02);
if (y1!=y2)
linedat12=((x2-x1)<<8)/(ly12);


  if (y0!=y1)                    
if ((y1>=screen0_y0)&&(y0<=screen0_y1))
{
  for (y=y0;y<y1;y++)
{
   
      
if ((y>=screen0_y0)&&(y<screen0_y1))
    {
  tempy=y*160;
  xa=x0+((y-y0)*linedat0>>8);
  xb=x0+((y-y0)*linedat2>>8);
  xbxa=xb-xa;
//  if (xbxa)
 {

  if (xb>xa)
{
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<screen0_x1)&&(xb>screen0_x0))
     for (x=xa;x<=xb;x++)
 {
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>setz)
  {
        zbuffer0[i]=setz;                 
        scrbuf0[i]=color;
  }
 }       
}else
{    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
 {
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>setz)
  {
        zbuffer0[i]=setz;                 
        scrbuf0[i]=color;
  }
 }
}
      
} 
}                    

}} 
///

  if (y1!=y2)                    
if ((y2>=screen0_y0)&&(y1<=screen0_y1))
{
  for (y=y2-1;y>=y1;y--)
{
   
      
if ((y>=screen0_y0)&&(y<screen0_y1))
    {
  tempy=y*160;
  xa=x2+((y-y2)*linedat12>>8);
  xb=x2+((y-y2)*linedat2>>8);
  xbxa=xb-xa;
//  if (xbxa)
 {

  if (xb>xa)
{
if (xb>screen0_x1) xb=screen0_x1;
if ((xa<screen0_x1)&&(xb>screen0_x0))
     for (x=xa;x<=xb;x++)
 {
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>setz)
  {
        zbuffer0[i]=setz;                 
        scrbuf0[i]=color;
  }
 }       
}else
{    if (xb<screen0_x0) xb=screen0_x0;
    if ((xb<=screen0_x1)&&(xa>=screen0_x0))
     for (x=xa;x>=xb;x--)
 {
         i=x+tempy;                
      if ((x>=screen0_x0)&&(x<=screen0_x1))
      if (zbuffer0[i]>setz)
  {
        zbuffer0[i]=setz;                 
        scrbuf0[i]=color;
  }
 }
}
      
} 
}                    

}} 
///


}    
 }
}
     
}
