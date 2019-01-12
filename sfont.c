#include "globalvar.h"
#include <string.h>
#include <stdio.h>
Sint8 fontdata[15368];
void s_initfont(void)
{
FILE *fp;
Uint8 c;
fp=fopen("data/systemfont.ggg","rb");
int i=0;
do
{
c=fgetc(fp);
fontdata[i]=c&1;
fontdata[i+1]=c&2;
fontdata[i+2]=c&4;
fontdata[i+3]=c&8;
fontdata[i+4]=c&16;
fontdata[i+5]=c&32;
fontdata[i+6]=c&64;
fontdata[i+7]=c&128;

i=i+8;
}while (!feof(fp));

fclose(fp);       

}
void s_drawtext(signed int x,signed int y,unsigned short int c)//draws the char *s_textstring
{
//     for (int ix=0;ix<80;ix++)
//     for (int iy=0;iy<192;iy++)
//     scrbuf[ix+iy*320]=fontdata[ix+iy*80];
int x1,y1,cx,cy,x2,y2;

if (l_textstring!=0)
for (int i=0;i<l_textstring;i++)
    {
    x1=x+i*5;y1=y;x2=s_textstring[i]%16*5;y2=s_textstring[i]/16*12;
   for (Uint8 ix=0;ix<5;ix++)    
    for (Uint8 iy=0;iy<12;iy++)
               {
               cx=x1+ix;cy=y1+iy;
               if ((cx>=0)&&(cy>=0)&&(cx<320)&&(cy<240))
                  {
                  if (fontdata[x2+ix+(iy+y2)*80])
                  scrbuf[cx+cy*320]=c;
                  }
               }

    }     
}
void s_drawtext2(signed int x,signed int y,unsigned short int c)//draws the char *s_textstring
{
Uint32 n;

Sint32 x1,y1,cx,cy,x2,y2;
if (l_textstring!=0)
for (int i=0;i<l_textstring;i++)
    {
    x1=x+i*10;y1=y;x2=s_textstring[i]%16*5;y2=s_textstring[i]/16*12;
   for (Uint32 ix=0;ix<5;ix++)    
    for (Uint32 iy=0;iy<12;iy++)
               {
               cx=x1+ix*2;cy=y1+iy*2;
               if ((cx>=0)&&(cy>=0)&&(cx<319)&&(cy<239))
                  {
                  if (fontdata[x2+ix+(iy+y2)*80])
                  {   
                  n=cx+cy*320;
                  scrbuf[n]=c;
                  scrbuf[n+1]=c;
                  scrbuf[n+321]=c;
                  scrbuf[n+320]=c;
                  } 
                  }
               }

    }     
}
