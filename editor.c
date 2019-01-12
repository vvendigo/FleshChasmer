#include "editor.h" 
#include "skills.h"
#include "render.h"
#include "camera.h"
#include "sound.h"
#include "items.h"
#include "stdlib.h"//forgive myself?

#include "video.h"

#include "zdialogs.h"
#include "globalvar.h"

#include "zmath.h"

#define FPMUL(x,y)	((((x)>>6)*((y)>>6))>>4)
#define FPDIV(x,y)	((((x)<<6)/((y)>>6))>>4)


Uint8 curlayer,layer_spec_mode=0,node_axis=0;
Uint32 editorcount;
Uint8 color,colorbuf[3],levelmode,selaxis,selstep=1,curmovie,curtrigger,lastlmode;
Uint8 aiedit;
Uint8 ex,ey,tile,tileedit[16][16],grid,tiledatcur=0,MapTag,objcur;

Uint8 CurrentTile,TileSelector,SoundPlayer,TilePlace,twosidedtile;
Uint8 cam0,cam1,cam2,cam3,camfollowmode;
Sint32 editorcamera_speed=3400;
Sint8 cursorx,cursory,cursorz,cursortarget,relativecursor,solidcursor;//My precioss
Sint32 cursori;

Sint16 starx[100],stary[100];
Sint16 starix[100],stariy[100];
Uint8 inTrigEdit=0;

const char *st_ch[2]=
{
"Off","On"
};
const char c_hex[16]=
{
'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'      
};

const char ai_text[13][20]=
{
"Normal AI",
"Walk East",
"Walk North",
"Walk West",
"Walk South",
"Run East",
"Run North",
"Run West",
"Run South",
"Panic East",
"Panic North",
"Panic West",
"Panic South"
};


const char *MapTaginfo[]=
{
"Empty(Unassigned)","Block Player","Floor Damage Low","Unknown 1","Unknown 2",
"Trigger 1",
"Trigger 2",
"Trigger 3",
"Trigger 4",
"Trigger 5",
"Trigger 6",
"Trigger 7",
"Trigger 8",
"Trigger 9",
"Trigger 10",
"Trigger 11",
"Trigger 12",
"Trigger 13",
"Trigger 14",
"Trigger 15",
"Climb East",
"Climb North",
"Climb West",
"Climb South",
"SHOP TIME!"
};
const Uint8 MapTaginfo_num=25;


Uint8 currentnode,currentconnode;


//con movie node
void GetCurrentConNode(void)
{
currentconnode=0;     

if (movie_control_nodes[curmovie])
{
while
(
(movie_control_node_pos[curmovie][currentconnode]<c_movie_step)
&
(currentconnode<movie_control_nodes[curmovie])
)
 {currentconnode++;}
}
}



//anim_movie node
void GetCurrentNode(void)
{
currentnode=0;     

if (movie_layer_nodes[curmovie][curlayer])
{
while
(
(movie_node_pos[curmovie][currentnode][curlayer]<c_movie_step)
&
(currentnode<movie_layer_nodes[curmovie][curlayer])
)
 {currentnode++;}
}
// c_movie_step=movie_node_pos[curmovie][currentnode][curlayer];
}
Uint8 ccon[3],cconi;
Uint8 CCON_SI=11;
char ccon_s[11][20]=
{
     "NOP",
     "SETMODEL_L_I",
     "SETFRAME_L_I",
     "SETANIM_L_I",
     "PLAYMUS_I",
     "PLAYSND_I",
     "ENDLEVEL",
     "ACTTRIG",
     "_DIALOG",
     "S_FIELD",
     "_RENAME"
     };
void MInsert_ConNode(void)
{
//currentnode=curmovie*64;
if (movie_control_nodes[curmovie]<128)
{
GetCurrentNode();
for (Uint8 i=movie_control_nodes[curmovie];i>currentconnode;i--)
{
movie_control_node_pos[curmovie][i]=movie_control_node_pos[curmovie][i-1];
movie_control_node[curmovie][i][0]=movie_control_node[curmovie][i-1][0];
movie_control_node[curmovie][i][1]=movie_control_node[curmovie][i-1][1];
movie_control_node[curmovie][i][2]=movie_control_node[curmovie][i-1][2];
}
movie_control_node_pos[curmovie][currentconnode]=c_movie_step;

movie_control_node[curmovie][currentconnode][0]=ccon[0];
movie_control_node[curmovie][currentconnode][1]=ccon[1];
movie_control_node[curmovie][currentconnode][2]=ccon[2];

movie_control_nodes[curmovie]++;
}
}
void MDelete_ConNode(void)
{
//currentnode=curmovie*64;
if (movie_control_nodes[curmovie]>0)
{
GetCurrentConNode();
for (Uint8 i=currentconnode;i<movie_control_nodes[curmovie]-1;i++)
{
movie_control_node_pos[curmovie][i]=movie_control_node_pos[curmovie][i+1];
movie_control_node[curmovie][i][0]=movie_control_node[curmovie][i+1][0];
movie_control_node[curmovie][i][1]=movie_control_node[curmovie][i+1][1];
movie_control_node[curmovie][i][2]=movie_control_node[curmovie][i+1][2];
}
movie_control_nodes[curmovie]--;
}
}


void MInsert_Node(void)
{
//currentnode=curmovie*64;
if (movie_layer_nodes[curmovie][curlayer]<64)
{
GetCurrentNode();
for (Uint8 i=movie_layer_nodes[curmovie][curlayer];i>currentnode;i--)
{
movie_node_pos[curmovie][i][curlayer]=movie_node_pos[curmovie][i-1][curlayer];
movie_node[curmovie][i][curlayer][0]=movie_node[curmovie][i-1][curlayer][0];
movie_node[curmovie][i][curlayer][1]=movie_node[curmovie][i-1][curlayer][1];
movie_node[curmovie][i][curlayer][2]=movie_node[curmovie][i-1][curlayer][2];
movie_node[curmovie][i][curlayer][3]=movie_node[curmovie][i-1][curlayer][3];
movie_node[curmovie][i][curlayer][4]=movie_node[curmovie][i-1][curlayer][4];
movie_node[curmovie][i][curlayer][5]=movie_node[curmovie][i-1][curlayer][5];
}
movie_node_pos[curmovie][currentnode][curlayer]=c_movie_step;

movie_node[curmovie][currentnode][curlayer][0]=rcamera[0];
movie_node[curmovie][currentnode][curlayer][1]=rcamera[1];
movie_node[curmovie][currentnode][curlayer][2]=rcamera[2];
movie_node[curmovie][currentnode][curlayer][3]=rcamera[3];
movie_node[curmovie][currentnode][curlayer][4]=rcamera[4];
movie_node[curmovie][currentnode][curlayer][5]=rcamera[5];
movie_layer_nodes[curmovie][curlayer]++;
}
}

void MDelete_Node(void)
{
//currentnode=curmovie*64;
if (movie_layer_nodes[curmovie][curlayer]>0)
{
GetCurrentNode();
for (Uint8 i=currentnode;i<movie_layer_nodes[curmovie][curlayer]-1;i++)
{
movie_node_pos[curmovie][i][curlayer]=movie_node_pos[curmovie][i+1][curlayer];
movie_node[curmovie][i][curlayer][0]=movie_node[curmovie][i+1][curlayer][0];
movie_node[curmovie][i][curlayer][1]=movie_node[curmovie][i+1][curlayer][1];
movie_node[curmovie][i][curlayer][2]=movie_node[curmovie][i+1][curlayer][2];
movie_node[curmovie][i][curlayer][3]=movie_node[curmovie][i+1][curlayer][3];
movie_node[curmovie][i][curlayer][4]=movie_node[curmovie][i+1][curlayer][4];
movie_node[curmovie][i][curlayer][5]=movie_node[curmovie][i+1][curlayer][5];
}
movie_layer_nodes[curmovie][curlayer]--;
}
}

void ClearLEditor()
{
cursorx=0;     
cursory=0;
cursorz=0;     
camera[0]=0;     
camera[1]=0;
camera[2]=0;
camera[3]=0;
camera[4]=0;
camera[5]=0;
camfollowmode=0;cursortarget=0;objcur=0;
twosidedtile=0;
relativecursor=1;
solidcursor=0;
cam0=0;
cam1=0x88;
cam2=0x88;
cam3=0x88;
curmovie=0;
curtrigger=0;
}
void savetiledata(void)
{
Uint8 c;     
FILE *fp;
fp=fopen("data/tiledata.ggc","wb");

for (int i=0;i<=255;i++)
 {
 c=0;
 if (tiledata_alpha[i])      c=c | 1;
 if (tiledata_animated[i])   c=c | 2;
 if (tiledata_block[i])      c=c | 4;
 if (tiledata_breakable[i])  c=c | 8;
 if (tiledata_finalbreak[i]) c=c | 16;
 c=c+tiledata_sound[i]*32;
 fputc(c,fp);
 }
     
fclose(fp);
}

void RenderEditorCursor(void)
{
Sint32 t=cursorx+cursory*128+cursorz*16384;
if (controlpad.button[PAD_Y])
{
zlcolor=39;
zlline(meshx[t],meshz[t],meshy[t],meshx[t]+1000,meshz[t]+2000,meshy[t]+1000);     
}
if (controlpad.button[PAD_Y])
zlcolor=22; else zlcolor=19;
zlline(meshx[t],meshz[t],meshy[t],meshx[t+1],meshz[t+1],meshy[t+1]);     
zlline(meshx[t],meshz[t],meshy[t],meshx[t+128],meshz[t+128],meshy[t+128]);     
zlline(meshx[t+1],meshz[t+1],meshy[t+1],meshx[t+129],meshz[t+129],meshy[t+129]);     
zlline(meshx[t+128],meshz[t+128],meshy[t+128],meshx[t+129],meshz[t+129],meshy[t+129]);     
zlcolor=19;
zlline(meshx[t],meshz[t],meshy[t],meshx[t+16384],meshz[t+16384],meshy[t+16384]);     
zlline(meshx[t+1],meshz[t+1],meshy[t+1],meshx[t+16385],meshz[t+16385],meshy[t+16385]);     
zlline(meshx[t+128],meshz[t+128],meshy[t+128],meshx[t+16512],meshz[t+16512],meshy[t+16512]);     
zlline(meshx[t+129],meshz[t+129],meshy[t+129],meshx[t+16513],meshz[t+16513],meshy[t+16513]);     
t=t+16384;
if (controlpad.button[PAD_Y])
zlcolor=24;
zlline(meshx[t],meshz[t],meshy[t],meshx[t+1],meshz[t+1],meshy[t+1]);     
zlline(meshx[t],meshz[t],meshy[t],meshx[t+128],meshz[t+128],meshy[t+128]);     
zlline(meshx[t+1],meshz[t+1],meshy[t+1],meshx[t+129],meshz[t+129],meshy[t+129]);     
zlline(meshx[t+128],meshz[t+128],meshy[t+128],meshx[t+129],meshz[t+129],meshy[t+129]);     
if ((!camfollowmode)&cursortarget)
{
camera[4]=1024-arctan(cursorx*65536+32666-camera[0],cursory*65536+32666-camera[2]);
camera[3]=arctan(srange(cursorx*65536+32666-camera[0],cursory*65536+32666-camera[2]),cursorz*65536+32666-camera[1]);
}
if (controlpad.button[PAD_Y])
 {
 l_textstring=sprintf(s_textstring,"Cursor Control");
 s_drawtext(246,203,16);
 s_drawtext(245,202,14);
 }
}


void SaveLevel(Uint8 num)
{
FILE *fp;
Uint8 c,c1,ext,k,n,j;
Uint8 x,y,z;
Uint32 t;
Uint16 i;
char spath[25];
sprintf(spath,"data/Level%i%i.zgz",num/10,num%10);
fp=fopen(spath,"wb");
if (fp)
{
ext=0;
fputc(fogcolor,fp);
fputc(levelx,fp);
fputc(levely,fp);
fputc(levelz,fp);
fputc(levelsight,fp);
fputc(maxmonsters,fp);
fputc(levelmusictrack,fp);
fputc(level_tag,fp);

for (z=0;z<=levelz;z++)     
for (y=0;y<=levely;y++)
for (x=0;x<=levelx;x++)
 {
                       
 t=x+y*128+z*16384;
 //FLAG0
 c=0;
 if (map[t]) c=c | 1;
 if (mapt0[t]) c=c | 2;
 if (mapt1[t]) c=c | 4;
 if (mapt2[t]) c=c | 8;
 if (mapt3[t]) c=c | 16;
 if (mapt4[t]) c=c | 32;
 if (mapt5[t]) c=c | 64;
 


 c1=0;  
 if (meshxdisplace[t]) c1=c1 | 1;
 if (meshydisplace[t]) c1=c1 | 2;
 if (meshzdisplace[t]) c1=c1 | 4;
 if (mapcam0[t]) c1=c1 | 8;
 if (mapobj[t]) c1=c1 | 16;
 if (mapai[t]) c1=c1 | 32;
//we got freespace descent III here

 if (c1) c=c | 128;

 fputc(c,fp);

 if (map[t]) fputc(map[t],fp);
 if (mapt0[t]) fputc(mapt0[t],fp);
 if (mapt1[t]) fputc(mapt1[t],fp);
 if (mapt2[t]) fputc(mapt2[t],fp);
 if (mapt3[t]) fputc(mapt3[t],fp);
 if (mapt4[t]) fputc(mapt4[t],fp);
 if (mapt5[t]) fputc(mapt5[t],fp);
 if (c1) fputc(c1,fp);
if (c1)
{
 //FLAG1
// if (mapt4[t]) c=c | 32;
// if (mapt5[t]) c=c | 64;
// if (mapai[t]) c=c | 128;
 
// fputc(c1,fp);
 if (meshxdisplace[t]) fputc(meshxdisplace[t],fp);
 if (meshydisplace[t]) fputc(meshydisplace[t],fp);
 if (meshzdisplace[t]) fputc(meshzdisplace[t],fp);
 if (mapcam0[t]) 
  {
   fputc(mapcam0[t],fp);
   if (mapcam0[t] & 128)
    {
    fputc(mapcam1[t],fp);
    fputc(mapcam2[t],fp);
    fputc(mapcam3[t],fp);
    }  
  }
 if (mapobj[t]) fputc(mapobj[t],fp);
 if (mapai[t]) fputc(mapai[t],fp);
}///c1
 }
fputc(staticcams,fp);//Static Cameras
if (staticcams)
 for (i=0;i<staticcams;i++)
 {
 for (k=0;k<6;k++)
  {
//   staticcam[i][k]=camera[k];//he-eh=hehe
  c=staticcam[i][k]/65536 %256;
  fputc(c,fp);
  c=staticcam[i][k]/256 %256;
  fputc(c,fp);
  c=staticcam[i][k]%256;
  fputc(c,fp);
  }
   // I should listen you more, my love            
 }
for (i=0;i<512;i++)
{
fputc(trig[i],fp);
}
//movie
for (i=0;i<16;i++)
{
c=movie_length[i]/256;
fputc(c,fp);
c=movie_length[i]%256;
fputc(c,fp);
if (movie_length[i])
 {
fputc(movie_type[i],fp);
fputc(movie_num_layers[i],fp);
 //layers 0-7
for (Uint8 k=0;k<=movie_num_layers[i];k++)
 {           
fputc(movie_layer_nodes[i][k],fp);
if (movie_layer_nodes[i][k])
  {
   for (Uint8 n=0;n<movie_layer_nodes[i][k];n++)
   {
   for (j=0;j<3;j++)
    {
    c=movie_node[i][n][k][j]/65536;
    fputc(c,fp);
    c=movie_node[i][n][k][j]/256;
    fputc(c,fp);
    c=movie_node[i][n][k][j];
    fputc(c,fp);
    }
   for (j=3;j<6;j++)
    {
    c=movie_node[i][n][k][j]/256;
    fputc(c,fp);
    c=movie_node[i][n][k][j];
    fputc(c,fp);
    }
    c=movie_node_pos[i][n][k]/256;
    fputc(c,fp);
    c=movie_node_pos[i][n][k];
    fputc(c,fp);


   }                         
  }           
 }              
                    
 //control layer 8(eight - not a smile with no teeth)
 fputc(movie_control_nodes[i],fp);
 if (movie_control_nodes[i])
  {
   for (Uint8 n=0;n<movie_control_nodes[i];n++)
   {
   for (j=0;j<3;j++)
    {
    c=movie_control_node[i][n][j];
    fputc(c,fp);
    }
    c=movie_control_node_pos[i][n]/256;
    fputc(c,fp);
    c=movie_control_node_pos[i][n];
    fputc(c,fp);

   }                           
                            
  }
 }
}


//Close Level File
fclose(fp);       
}

     
     
}

void RenderETileSelector(void)
{
     int ix,iy;       
     int c,a,d,n;
     c=CurrentTile/32*32;
     for (int a=0;a<32;a++)
      {
       ix=10+((a%8)*38);
       iy=20+((a/8)*38);
       for (int x=0;x<16;x++)        
       for (int y=0;y<16;y++)
       { 
        n=ix+x*2+(iy+y*2)*320;
        d=Tile[Tile_offset[CurrentTile/32*32+a]+x+y*16];
        scrbuf[n]=d;
        scrbuf[n+1]=d;
        scrbuf[n+320]=d;
        scrbuf[n+321]=d;
       }       
              
      }

       ix=9+(((CurrentTile%32)%8)*38);
       iy=19+(((CurrentTile%32)/8)*38);
d=13+count/5%3;
for (c=0;c<34;c++)
{
 scrbuf[ix+c+(iy)*320]=d;   
 scrbuf[ix+c+(iy+33)*320]=d;   
 scrbuf[ix+(iy+c)*320]=d;   
 scrbuf[ix+33+(iy+c)*320]=d;   
    
}


if (GameMode==EDITOR_TEXTURE)
{
       for (int x=0;x<16;x++)        
       for (int y=0;y<16;y++)
       { 
        n=20+x*2+(180+y*2)*320;
        d=tileedit[x][y];
        scrbuf[n]=d;
        scrbuf[n+1]=d;
        scrbuf[n+320]=d;
        scrbuf[n+321]=d;
       }       



 l_textstring=sprintf(s_textstring,"X:Read   Y:Write");
 s_drawtext(20,226,14);
}
if (editorcount>10)
{
l_textstring=sprintf(s_textstring,"Select: Save");
s_drawtext(130,226,15);
}
      
l_textstring=sprintf(s_textstring,"Tile Element N:%i",CurrentTile);
s_drawtext(220,2,14);
if (editorcount>10)
{
l_textstring=sprintf(s_textstring,"Tile Selector");
s_drawtext(10,2,14);
}      

l_textstring=sprintf(s_textstring,"L: Previous Page");
s_drawtext(230,192,14);

l_textstring=sprintf(s_textstring,"R: Next Page");
s_drawtext(230,204,14);

l_textstring=sprintf(s_textstring,"Start: Return");
s_drawtext(230,226,15);
     
}

void RenderETexture(void)
{//R_TEXTURE EDITOR
if (editorcount>10)        
{
l_textstring=sprintf(s_textstring,"Texture editor");
s_drawtext(10,10,14);
}

l_textstring=sprintf(s_textstring,"Start: Exit");
s_drawtext(230,226,15);
if (!controlpad.button[PAD_L1])
{
l_textstring=sprintf(s_textstring,"Vol-:Tiles  Vol+:Grid");
s_drawtext(20,226,14);
}

if (controlpad.button[PAD_L1])
{
l_textstring=sprintf(s_textstring,"Tiledata %i",CurrentTile);
s_drawtext(240,20,14);
s_drawtext(239,19,15);

l_textstring=sprintf(s_textstring,"b_AlphaChannel %i",tiledata_alpha[CurrentTile]);
if (tiledatcur==0)
s_drawtext(230,32,13);else s_drawtext(230,32,14);
l_textstring=sprintf(s_textstring,"b_Animated     %i",tiledata_animated[CurrentTile]);
if (tiledatcur==1)
s_drawtext(230,44,13);else s_drawtext(230,44,14);
l_textstring=sprintf(s_textstring,"b_Blocking     %i",tiledata_block[CurrentTile]);
if (tiledatcur==2)
s_drawtext(230,56,13);else s_drawtext(230,56,14);
l_textstring=sprintf(s_textstring,"b_Breakable    %i",tiledata_breakable[CurrentTile]);
if (tiledatcur==3)
s_drawtext(230,68,13);else s_drawtext(230,68,14);
l_textstring=sprintf(s_textstring,"b_FinalDamage  %i",tiledata_finalbreak[CurrentTile]);
if (tiledatcur==4)
s_drawtext(230,80,13);else s_drawtext(230,80,14);

l_textstring=sprintf(s_textstring,"i_Sound %i=5+2*%i",5+tiledata_sound[CurrentTile]*2,tiledata_sound[CurrentTile]);
if (tiledatcur==5)
s_drawtext(230,92,13);else s_drawtext(230,92,14);

if (editorcount>10)
{
l_textstring=sprintf(s_textstring,"Select: Save TileData");
s_drawtext(205,104,15);
}

}
else
if (controlpad.button[PAD_R1])
{
l_textstring=sprintf(s_textstring,"Palette");
s_drawtext(240,126,14);
for (int y=0;y<12;y++)
for (int x=0;x<12;x++)
 {
 scrbuf[277+x+(y+126)*320]=color;   
 }
}
//else
//{
//l_textstring=sprintf(s_textstring,"Tile N%i",CurrentTile);
//s_drawtext(40,202,14);
//}

for (int y=0;y<16;y++)
for (int x=0;x<16;x++)
 {
 scrbuf[13010+x+y*320]=tileedit[x][y];   
 }
 scrbuf[12690+ex]=15;   
 scrbuf[18130+ex]=15;   

 scrbuf[13009+ey*320]=15;   
 scrbuf[13026+ey*320]=15;   

for (int y=40;y<200;y++)
for (int x=40;x<200;x++)
{
 scrbuf[x+320*y]=tileedit[(x-40)/10][(y-40)/10];   
}

for (int y=140;y<204;y++)
for (int x=240;x<304;x++)
{
 scrbuf[x+320*y]=(x-240)/4+(y-140)/4*16;   
}
         Uint8 c,i;i=16+count/13%4*3;
int ix,iy;
ix=240+color%16*4;iy=140+color/16*4;
for (c=0;c<4;c++)
{
 scrbuf[ix+c+(iy)*320]=i;   
 scrbuf[ix+c+(iy+4)*320]=i;   
 scrbuf[ix+(iy+c)*320]=i;   
 scrbuf[ix+4+(iy+c)*320]=i;   
    
}

if (grid)
{
         c=15+grid*4;
for (int y=40;y<201;y++)
for (int x=40;x<201;x++)
 {
if ((x%10==0)||(y%10==0))
 scrbuf[x+320*y]=c;   
 }
      
         
}
if (controlpad.button[PAD_R1]==0)
{
ix=40+ex*10;iy=40+ey*10;
for (c=0;c<10;c++)
 {
 scrbuf[ix+c+(iy)*320]=color;   
 scrbuf[ix+c+(iy+10)*320]=color;   
 scrbuf[ix+(iy+c)*320]=color;   
 scrbuf[ix+10+(iy+c)*320]=color;   
 }
}


}//R_TEXTURE EDITOR END;

void SavePalette(void)
{
FILE *fp;char c;
fp=fopen("data/palette.ggg","wb");
for (int i=0;i<256;i++)
{
#ifdef GP2X
fputc(screen->format->palette->colors[i].r,fp);
fputc(screen->format->palette->colors[i].g,fp);
fputc(screen->format->palette->colors[i].b,fp);
#endif
#ifdef PC
fputc(ipal[i][0],fp);
fputc(ipal[i][1],fp);
fputc(ipal[i][2],fp);
#endif
}    
fclose(fp);     
}
void SaveTiles(void)
{
FILE *fp;
fp=fopen("data/tileset.ggg","wb");
for (int i=0;i<65536;i++)
{
fputc(Tile[i],fp);
}    
fclose(fp);     
}

void RenderEPalette(void)
{
if (editorcount>10)        
{
l_textstring=sprintf(s_textstring,"Palette editor");
s_drawtext(10,10,14);
}

for (int y=0;y<16;y++)
for (int x=0;x<16;x++)
 {
 scrbuf[13010+x+y*320]=x+y*16;   
 }
 scrbuf[12690+color%16]=15;   
 scrbuf[18130+color%16]=15;   

 scrbuf[13009+color/16*320]=15;   
 scrbuf[13026+color/16*320]=15;   

for (int y=40;y<200;y++)
for (int x=40;x<200;x++)
{
 scrbuf[x+320*y]=(x-40)/10+(y-40)/10*16;   
}

 scrbuf[12840+color%16*10+color/16*3200]=15;   
 scrbuf[15720+color%16*10+color/16*3200]=15;   
 scrbuf[12849+color%16*10+color/16*3200]=15;   
 scrbuf[15729+color%16*10+color/16*3200]=15;   


l_textstring=sprintf(s_textstring,"index: %i",color);
s_drawtext(210,60,13);
#ifdef GP2X
l_textstring=sprintf(s_textstring,"R: %i",screen->format->palette->colors[color].r);
s_drawtext(230,72,13);
l_textstring=sprintf(s_textstring,"G: %i",screen->format->palette->colors[color].g);
s_drawtext(230,84,13);
l_textstring=sprintf(s_textstring,"B: %i",screen->format->palette->colors[color].b);
s_drawtext(230,96,13);
#endif
#ifdef PC
l_textstring=sprintf(s_textstring,"R: %i",ipal[color][0]);
s_drawtext(230,72,13);
l_textstring=sprintf(s_textstring,"G: %i",ipal[color][1]);
s_drawtext(230,84,13);
l_textstring=sprintf(s_textstring,"B: %i",ipal[color][2]);
s_drawtext(230,96,13);
#endif

l_textstring=sprintf(s_textstring,"X/Y: Copy/Paste");
s_drawtext(230,190,13);

l_textstring=sprintf(s_textstring,"Select: Save");
s_drawtext(150,226,15);
l_textstring=sprintf(s_textstring,"Start: Exit");
s_drawtext(230,226,15);
     
}

void RenderEMenu(void)
{

Uint8 i;     
for (i=0;i<100;i++)
{
if ((starx[i]>0)&(stary[i]>0)&(starx[i]<319)&(stary[i]<239))
 {
 scrbuf[starx[i]+stary[i]*320]=18+i%12;
 starx[i]+=starix[i];                                                           
 stary[i]+=stariy[i]; 
 }
else
 {
 starx[i]=150+rand()%21;
 stary[i]=110+rand()%21;
 starix[i]=-7+rand()%15;
 if (starix[i]==0) starix[i]=-1;
 stariy[i]=-7+rand()%15;
 if (stariy[i]==0) stariy[i]=-1;
 
 }   
}     
     
     
l_textstring=sprintf(s_textstring,"Editor Main Menu");
s_drawtext2(20,10,19);     
     
int c;
l_textstring=sprintf(s_textstring,"0. Level Editor %i",CurrentLevel);
if (menupos==0) c=13; else c=14;
s_drawtext(20,34,c);     
l_textstring=sprintf(s_textstring,"1. Model Viewer");
if (menupos==1) c=13; else c=14;
s_drawtext(20,46,c);     
l_textstring=sprintf(s_textstring,"2. Texture Editor");
if (menupos==2) c=13; else c=14;
s_drawtext(20,58,c);     
l_textstring=sprintf(s_textstring,"3. Palette Editor");
if (menupos==3) c=13; else c=14;
s_drawtext(20,70,c);     
l_textstring=sprintf(s_textstring,"4. Music Player  %i",Next_Music_Track);
if (menupos==4) c=13; else c=14;
s_drawtext(20,82,c);     
if (d_sound_count)
l_textstring=sprintf(s_textstring,"5. Sound Player  %i",SoundPlayer);
else
l_textstring=sprintf(s_textstring,"5. No Sounds To Hear",SoundPlayer);
if (menupos==5) c=13; else c=14;
s_drawtext(20,94,c);     
l_textstring=sprintf(s_textstring,"6. AI Editor");
if (menupos==6) c=13; else c=14;
s_drawtext(20,106,c);     

l_textstring=sprintf(s_textstring,"7. Disable EE Runtime");
if (menupos==7) c=13; else c=14;
s_drawtext(20,118,c);     
l_textstring=sprintf(s_textstring,"8. Exit");
if (menupos==8) c=13; else c=14;
s_drawtext(20,130,c);     
if (menupos==5)
 {
 switch (SoundMode)
  {
  case 0:l_textstring=sprintf(s_textstring,"<SELECT>Stereo Sound Mode");break;      
  case 1:l_textstring=sprintf(s_textstring,"<SELECT>Reversed Stereo Mode");break;      
  case 2:l_textstring=sprintf(s_textstring,"<SELECT>Monoral Sound Mode");break;      
  }              
 s_drawtext(160,94,14);     
               
 }

switch (menupos)
{
case 0:l_textstring=sprintf(s_textstring,"A-Return X-Load B-New (loaded:%i)",LoadedLevel);break;
case 1:l_textstring=sprintf(s_textstring,"View Models");break;
case 2:l_textstring=sprintf(s_textstring,"Built-in texture drawing tool");break;
case 3:l_textstring=sprintf(s_textstring,"Change Color Set");break;
case 4:l_textstring=sprintf(s_textstring,"Enjoy ingame music while developing other content");break;
case 5:
     if (d_sound_count)
     l_textstring=sprintf(s_textstring,"Channel: A-left   X=center   B-right");
     else
     l_textstring=sprintf(s_textstring,"You promised to not leave all that silent!");
     break;
case 6:l_textstring=sprintf(s_textstring,"AI table managment");break;
case 7:l_textstring=sprintf(s_textstring,"Begin testing :)");break;
#ifdef PC
case 8:l_textstring=sprintf(s_textstring,"Return to WINDOWS (actualy you are inside already!)");break;
#endif
#ifdef GP2X
case 8:l_textstring=sprintf(s_textstring,"Return to GP2X OS menu");break;
#endif
}
s_drawtext(300-l_textstring*5,182,14);     

l_textstring=sprintf(s_textstring,"Genocide Generation Gaming engine 0.64f");
s_drawtext(320-l_textstring*5,228,15);     
}



void renderLeditor(void)
{
     
renderscene();
 Uint8 t;
if (controlpad.button[PAD_L1] && controlpad.button[PAD_R1])
{
l_textstring=sprintf(s_textstring,"Level %i",CurrentLevel);
s_drawtext(36,22,16);     
s_drawtext(35,21,15);     

int c;
c=36+12*levelmode;
c=c*320;

for (int x=16;x<200;x+=2)
{
 scrbuf[x+c]=16;   
 scrbuf[x+c+321]=16;   
 scrbuf[x+c+640]=16;   
 scrbuf[x+c+961]=16;   
 scrbuf[x+c+1280]=16;   
 scrbuf[x+c+1601]=16;   
 scrbuf[x+c+1920]=16;   
 scrbuf[x+c+2241]=16;   
 scrbuf[x+c+2560]=16;   
 scrbuf[x+c+2881]=16;   
    
}

l_textstring=sprintf(s_textstring,"Description Header");
if (levelmode==0) c=13; else c=14;
s_drawtext(36,36,16);     
s_drawtext(35,35,c);     

l_textstring=sprintf(s_textstring,"Mesh Editor");
if (levelmode==1) c=13; else c=14;
s_drawtext(36,48,16);     
s_drawtext(35,47,c);     
                             
if (levelmode!=2) 
l_textstring=sprintf(s_textstring,"Tile Wrapper");
else
if (twosidedtile)
l_textstring=sprintf(s_textstring,"Tile Wrapper two sided");
else
l_textstring=sprintf(s_textstring,"Tile Wrapper one sided");
if (levelmode==2) c=13; else c=14;
s_drawtext(36,60,16);     
s_drawtext(35,59,c);     

l_textstring=sprintf(s_textstring,"Edit Map Tags");
if (levelmode==3) c=13; else c=14;
s_drawtext(36,72,16);     
s_drawtext(35,71,c);     

if (levelmode!=4) 
l_textstring=sprintf(s_textstring,"Camera Tool");
else
l_textstring=sprintf(s_textstring,"Camera Tool    FollowMode %s",st_ch[camfollowmode]);

if (levelmode==4) c=13; else c=14;
s_drawtext(36,84,16);     
s_drawtext(35,83,c);     

l_textstring=sprintf(s_textstring,"Object Placer");
if (levelmode==5) c=13; else c=14;
s_drawtext(36,96,16);     
s_drawtext(35,95,c);     
l_textstring=sprintf(s_textstring,"AI Nodes");
if (levelmode==6) c=13; else c=14;
s_drawtext(36,108,16);     
s_drawtext(35,107,c);     

l_textstring=sprintf(s_textstring,"Trigger Scripts");
if (levelmode==7) c=13; else c=14;
s_drawtext(36,120,16);     
s_drawtext(35,119,c);     

l_textstring=sprintf(s_textstring,"Movie Editor %i/%i l:%i type:%i lrs:%i",curmovie,movies,movie_length[curmovie],movie_type[curmovie],movie_num_layers[curmovie]);
if (levelmode==8) c=13; else c=14;
s_drawtext(36,132,16);     
s_drawtext(35,131,c);     

l_textstring=sprintf(s_textstring,"Camera Speed : %i",editorcamera_speed/100-9);
if (levelmode==11) c=13; else c=14;
s_drawtext(36,168,16);     
s_drawtext(35,167,c);     

l_textstring=sprintf(s_textstring,"Camera follow cursor : %s",st_ch[cursortarget]);
if (levelmode==12) c=13; else c=14;
s_drawtext(36,180,16);     
s_drawtext(35,179,c);

l_textstring=sprintf(s_textstring,"Relative cursor : %s",st_ch[relativecursor]);
if (levelmode==13) c=13; else c=14;
s_drawtext(36,192,16);     
s_drawtext(35,191,c);

l_textstring=sprintf(s_textstring,"Solid cursor : %s",st_ch[solidcursor]);
if (levelmode==14) c=13; else c=14;
s_drawtext(36,204,16);     
s_drawtext(35,203,c);
     
}
else     
switch (levelmode)
{     
case 0://header
     
     l_textstring=sprintf(s_textstring,"Level %i Descriptor Editor ",CurrentLevel);
     s_drawtext(320-l_textstring*5,228,14);     
     l_textstring=sprintf(s_textstring,">X>");
     s_drawtext(0,228,14);     

     switch (param)
      {
            case 0:  

     l_textstring=sprintf(s_textstring,"Fog Color: %i",fogcolor);
     s_drawtext(15,228,14);     
            break;        
            case 1:            
     l_textstring=sprintf(s_textstring,"LevelX: %i",levelx);
     s_drawtext(15,228,14);     
            break;        
            case 2:            
     l_textstring=sprintf(s_textstring,"LevelY: %i",levely);
     s_drawtext(15,228,14);     
            break;        
            case 3:            
     l_textstring=sprintf(s_textstring,"LevelZ: %i",levelz);
     s_drawtext(15,228,14);     
            break;        
            case 4:            
     l_textstring=sprintf(s_textstring,"LevelSight: %i",levelsight);
     s_drawtext(15,228,14);     
            break;        
            case 5:            
     l_textstring=sprintf(s_textstring,"MaxMonsters: %i",maxmonsters);
     s_drawtext(15,228,14);     
            break;        
            case 6:            
     if (levelmusictrack==50)
     l_textstring=sprintf(s_textstring,"Default Music Disabled");
     else
     l_textstring=sprintf(s_textstring,"Default Music Track: %i",levelmusictrack);
     s_drawtext(15,228,14);     
            break;        
            case 7:            
     l_textstring=sprintf(s_textstring,"level_tag: %i",level_tag);
     s_drawtext(15,228,14);     
            break;        
             
            
      }
     
     
     
     break;//header
case 1://mesh
  RenderEditorCursor();
cursori=cursorx+cursory*128+cursorz*16384;
   switch (selaxis)
   {
   case 0:
     l_textstring=sprintf(s_textstring,"Currently selected X-Axis");
   break;
   case 1:
     l_textstring=sprintf(s_textstring,"Currently selected Y-Axis");
   break;
   case 2:
     l_textstring=sprintf(s_textstring,"Currently selected Z-Axis");
   break;
   }
     s_drawtext(5,228,14);     
     l_textstring=sprintf(s_textstring,"Step:%i",selstep);

     s_drawtext(275,228,14);     

     l_textstring=sprintf(s_textstring,"X:%i Y:%i Z:%i",meshxdisplace[cursori],meshydisplace[cursori],meshzdisplace[cursori]);
     s_drawtext(315-5*l_textstring,218,14);     

  break;//mesh
  case 2://tiles
  RenderEditorCursor();
  cursori=cursorx+cursory*128+cursorz*16384;
  Sint16 tmp;tmp=CurrentTile;
  if (tiledata_animated[tmp]) tmp=tmp+counttextureanimation;
  for (int y=0;y<16;y++)
  for (int x=0;x<16;x++)
  {
   scrbuf[x+2+(2+y)*320]=Tile[Tile_offset[tmp]+x+y*16];    
  }
  switch (TilePlace)
  {
  case 0:tmp=mapt0[cursori];break;       
  case 1:tmp=mapt1[cursori];break;       
  case 2:tmp=mapt2[cursori];break;       
  case 3:tmp=mapt3[cursori];break;       
  case 4:tmp=mapt4[cursori];break;       
  case 5:tmp=mapt5[cursori];break;       
  }
  if (tiledata_animated[tmp]) tmp=tmp+counttextureanimation;
  for (int y=0;y<16;y++)
  for (int x=0;x<16;x++)
  {
   scrbuf[x+80+(2+y)*320]=Tile[Tile_offset[tmp]+x+y*16];    
  }



     l_textstring=sprintf(s_textstring,"Tile : %i",CurrentTile);
     s_drawtext(20,3,14);     
     switch (TilePlace)
     {
            case 0:l_textstring=sprintf(s_textstring,"Down");break;
            case 1:l_textstring=sprintf(s_textstring,"West");break;
            case 2:l_textstring=sprintf(s_textstring,"East");break;
            case 3:l_textstring=sprintf(s_textstring,"South");break;
            case 4:l_textstring=sprintf(s_textstring,"North");break;
            case 5:l_textstring=sprintf(s_textstring,"Up");break;
     }


     if (twosidedtile)
      {

     s_drawtext(120,3,14);     
  tmp=-1;
  switch (TilePlace)
  {
  case 0:
       if (cursorz>0)
       tmp=mapt5[cursori-16384];break;       
  case 1:if (cursorx>0)
       tmp=mapt2[cursori-1];
       break;       
  case 2:if (cursorx<levelx)
       tmp=mapt1[cursori+1];
       break;       
  case 3:if (cursory>0)
       tmp=mapt4[cursori-128];
       break;       
  case 4:if (cursory<levely)
       tmp=mapt3[cursori+128];
       break;       
  case 5:if (cursorz<levelz)
       tmp=mapt0[cursori+16384];
       break;       
      
  }
  if (tmp>=0)
  {
  if (tiledata_animated[tmp]) tmp=tmp+counttextureanimation;
  for (int y=0;y<16;y++)
  for (int x=0;x<16;x++)
   {
   scrbuf[x+100+(2+y)*320]=Tile[Tile_offset[tmp]+x+y*16];    
   }
  }              
      }
else      s_drawtext(100,3,14);      

      zlcolor=16+15*(count/10%2);
     switch (TilePlace)
     {
      case 0:
      zlline(meshx[cursori],meshz[cursori]+1500,meshy[cursori],meshx[cursori+128],meshz[cursori+128]+1500,meshy[cursori+128]);
      zlline(meshx[cursori+128],meshz[cursori+128]+1500,meshy[cursori+128],meshx[cursori+129],meshz[cursori+129]+1500,meshy[cursori+129]);
      zlline(meshx[cursori+1],meshz[cursori+1]+1500,meshy[cursori+1],meshx[cursori+129],meshz[cursori+129]+1500,meshy[cursori+129]);
      zlline(meshx[cursori],meshz[cursori]+1500,meshy[cursori],meshx[cursori+1],meshz[cursori+1]+1500,meshy[cursori+1]);
      break;
      case 1:
      zlline(meshx[cursori]+1500,meshz[cursori],meshy[cursori],meshx[cursori+128]+1500,meshz[cursori+128],meshy[cursori+128]);
      zlline(meshx[cursori]+1500,meshz[cursori],meshy[cursori],meshx[cursori+16384]+1500,meshz[cursori+16384],meshy[cursori+16384]);
      zlline(meshx[cursori+16512]+1500,meshz[cursori+16512],meshy[cursori+16512],meshx[cursori+16384]+1500,meshz[cursori+16384],meshy[cursori+16384]);
      zlline(meshx[cursori+128]+1500,meshz[cursori+128],meshy[cursori+128],meshx[cursori+16512]+1500,meshz[cursori+16512],meshy[cursori+16512]);
      break;
      case 2:
      zlline(meshx[cursori+1]-1500,meshz[cursori+1],meshy[cursori+1],meshx[cursori+129]-1500,meshz[cursori+129],meshy[cursori+129]);
      zlline(meshx[cursori+1]-1500,meshz[cursori+1],meshy[cursori+1],meshx[cursori+16385]-1500,meshz[cursori+16385],meshy[cursori+16385]);
      zlline(meshx[cursori+16513]-1500,meshz[cursori+16513],meshy[cursori+16513],meshx[cursori+16385]-1500,meshz[cursori+16385],meshy[cursori+16385]);
      zlline(meshx[cursori+129]-1500,meshz[cursori+129],meshy[cursori+129],meshx[cursori+16513]-1500,meshz[cursori+16513],meshy[cursori+16513]);
      break;
      case 3:
      zlline(meshx[cursori],meshz[cursori],meshy[cursori]+1500,meshx[cursori+1],meshz[cursori+1],meshy[cursori+1]+1500);
      zlline(meshx[cursori+1],meshz[cursori+1],meshy[cursori+1]+1500,meshx[cursori+16385],meshz[cursori+16385],meshy[cursori+16385]+1500);
      zlline(meshx[cursori+16384],meshz[cursori+16384],meshy[cursori+16384]+1500,meshx[cursori+16385],meshz[cursori+16385],meshy[cursori+16385]+1500);
      zlline(meshx[cursori+16384],meshz[cursori+16384],meshy[cursori+16384]+1500,meshx[cursori],meshz[cursori],meshy[cursori]+1500);
      break;
      case 4:
      zlline(meshx[cursori+16513],meshz[cursori+16513],meshy[cursori+16513]-1500,meshx[cursori+129],meshz[cursori+129],meshy[cursori+129]-1500);
      zlline(meshx[cursori+128],meshz[cursori+128],meshy[cursori+128]-1500,meshx[cursori+129],meshz[cursori+129],meshy[cursori+129]-1500);
      zlline(meshx[cursori+128],meshz[cursori+128],meshy[cursori+128]-1500,meshx[cursori+16512],meshz[cursori+16512],meshy[cursori+16512]-1500);
      zlline(meshx[cursori+16513],meshz[cursori+16513],meshy[cursori+16513]-1500,meshx[cursori+16512],meshz[cursori+16512],meshy[cursori+16512]-1500);
      break;
      
      case 5:
      cursori+=16384;
      zlline(meshx[cursori],meshz[cursori]-1500,meshy[cursori],meshx[cursori+128],meshz[cursori+128]-1500,meshy[cursori+128]);
      zlline(meshx[cursori+128],meshz[cursori+128]-1500,meshy[cursori+128],meshx[cursori+129],meshz[cursori+129]-1500,meshy[cursori+129]);
      zlline(meshx[cursori+1],meshz[cursori+1]-1500,meshy[cursori+1],meshx[cursori+129],meshz[cursori+129]-1500,meshy[cursori+129]);
      zlline(meshx[cursori],meshz[cursori]-1500,meshy[cursori],meshx[cursori+1],meshz[cursori+1]-1500,meshy[cursori+1]);
      cursori-=16384;
      break;
     }
 
  break;//tiles tiles
  case 3://map tags
  RenderEditorCursor();
  cursori=cursorx+cursory*128+cursorz*16384;
  
     if (MapTag<MapTaginfo_num)
     l_textstring=sprintf(s_textstring," Brush : %i - %s",MapTag,MapTaginfo[MapTag]);
     else
     l_textstring=sprintf(s_textstring," Brush : %i - Unknown Entry",MapTag);
     
     s_drawtext(41,33,16);     
     s_drawtext(40,32,14);     

     Uint8 c;
     c=map[cursori];
     if (c<MapTaginfo_num)
     l_textstring=sprintf(s_textstring,"Cursor : %i - %s",c,MapTaginfo[c]);
     else
     l_textstring=sprintf(s_textstring,"Cursor : %i - Unknown Entry",c);
     
     s_drawtext(41,21,16);     
     s_drawtext(40,20,14);     
  
  break;//map tags
  case 4://Camera spirit
  RenderEditorCursor();
  cursori=cursorx+cursory*128+cursorz*16384;
  t=mapcam0[cursori];
  if ((t>0)&(t<128))
   {
   t=t-1;
   zlcolor=80+(count/2%8);
   
   zlline(meshx[cursori],meshz[cursori],meshy[cursori],staticcam[t][0],staticcam[t][1],staticcam[t][2]);            
   zlline(meshx[cursori+1],meshz[cursori+1],meshy[cursori+1],staticcam[t][0],staticcam[t][1],staticcam[t][2]);            
   zlline(meshx[cursori+128],meshz[cursori+128],meshy[cursori+128],staticcam[t][0],staticcam[t][1],staticcam[t][2]);            
   zlline(meshx[cursori+129],meshz[cursori+129],meshy[cursori+129],staticcam[t][0],staticcam[t][1],staticcam[t][2]);            
   }
     if (camfollowmode)
     {
     l_textstring=sprintf(s_textstring,"Follow Camera Mode");
     s_drawtext(41,21,16);     
     s_drawtext(40,20,14);     
     
     if (mapcam0[cursori]>=128)
        if (!controlpad.button[PAD_Y])

      {
        if (controlpad.button[PAD_X])
          l_textstring=sprintf(s_textstring,"Target");
          else
          l_textstring=sprintf(s_textstring,"Position");
 s_drawtext(246,203,16);
 s_drawtext(245,202,14);
      }  
     
     
     }
     if ((staticcams==0)&(cam0==0))
     l_textstring=sprintf(s_textstring,"No Cameras! Press both <Z> and <+> to add one(Assing<X>)");
     else
     if (cam0==0)
     l_textstring=sprintf(s_textstring,"Free Camera 0/%i",staticcams);
     else
     if (cam0<128)
     l_textstring=sprintf(s_textstring,"Static Camera %i/%i (<Z>+<X> set place)",cam0,staticcams);
     else   
     l_textstring=sprintf(s_textstring,"%c%c %c%c %c%c %c%c",
     c_hex[cam0/16],c_hex[cam0%16],
     c_hex[cam1/16],c_hex[cam1%16],
     c_hex[cam2/16],c_hex[cam2%16],
     c_hex[cam3/16],c_hex[cam3%16]);
     s_drawtext(20,228,14);     
  
     l_textstring=sprintf(s_textstring,"%c%c %c%c %c%c %c%c",
     c_hex[mapcam0[cursori]/16],c_hex[mapcam0[cursori]%16],
     c_hex[mapcam1[cursori]/16],c_hex[mapcam1[cursori]%16],
     c_hex[mapcam2[cursori]/16],c_hex[mapcam2[cursori]%16],
     c_hex[mapcam3[cursori]/16],c_hex[mapcam3[cursori]%16]);
     s_drawtext(201,21,16);     
     s_drawtext(200,20,14);     
 
  break;
  //Camera spirit
  
  case 5://Holy objects
  RenderEditorCursor();
  cursori=cursorx+cursory*128+cursorz*16384;
  c=mapobj[cursori];
     l_textstring=sprintf(s_textstring,"Map[x,y,z]=%i",c);
     s_drawtext(41,21,16);     
     s_drawtext(40,20,14);     

if (objcur==0)
l_textstring=sprintf(s_textstring,"Game Object Brush: Empty");
else
if (objcur<33)
     l_textstring=sprintf(s_textstring,"Game Object Brush: %i - %s",objcur,t_monster_name[objcur-1]);
else
if (objcur<43)
     l_textstring=sprintf(s_textstring,"Visual: %i",objcur-33);
else
if (objcur<53)
     l_textstring=sprintf(s_textstring,"Effect: %i",objcur-43);
else
     l_textstring=sprintf(s_textstring,"Ogject: %i - /* I won't put this on map!*/",objcur);

//else     

     s_drawtext(41,33,16);     
     s_drawtext(40,32,14);     
  
  break;//Holy Objects
  
  
  case 6://Mind washing
  RenderEditorCursor();
  cursori=cursorx+cursory*128+cursorz*16384;
  c=mapai[cursori];
     l_textstring=sprintf(s_textstring,"Mapai[x,y,z]=%i:%s",c,ai_text[c]);
     s_drawtext(41,21,16);     
     s_drawtext(40,20,14);     
l_textstring=sprintf(s_textstring,"%i:%s",aiedit,ai_text[aiedit]);

     s_drawtext(41,33,16);     
     s_drawtext(40,32,14);     
  
  break;//Mind washing

  case 7://unholy scrtipts
     RenderEditorCursor();
     l_textstring=sprintf(s_textstring,"Press <Z> to enter FleshChasmer Assembler...");
     s_drawtext(0,0,31);     
 
  break;
  case 8://porn scenes
     l_textstring=sprintf(s_textstring,"Movie %i[%i/%i]",curmovie,c_movie_step,movie_length[curmovie]);
     s_drawtext(0,0,15);     
if (layer_spec_mode<2)
{
     l_textstring=sprintf(s_textstring,"Layer %i/%i",curlayer,movie_num_layers[curmovie]);
     s_drawtext(0,12,15);     
     GetCurrentNode();
     l_textstring=sprintf(s_textstring,"Node %i/%i",currentnode,movie_layer_nodes[curmovie][curlayer]);
     s_drawtext(0,24,15);     
}


//aaaaaaaaa

Uint16 x;
if (movie_length[curmovie])
{
GetCurrentNode();
GetCurrentConNode();
     if (currentnode<movie_layer_nodes[curmovie][curlayer])
     {
     Sint32 v[6];
//     for (Uint8 i=0;i<6;i++) 
//      {v[i]=movie_node[curmovie][currentnode][curlayer][i];
//       l_textstring=sprintf(s_textstring,"%i=%i*65536+%i*256+%i",v[i],zabs(v[i]/65536),zabs(v[i]/256%256),v[i]%256);
//       s_drawtext(0,150+i*12,15);     
//      }
     }

if (curlayer)
{
Sint32 x,y,z;
x=c_movie_layer[curlayer][0];
y=c_movie_layer[curlayer][1];
z=c_movie_layer[curlayer][2];
zlcolor=34;
zlline(x,y,z+1000,x,y,z-1000);
zlline(x,y+1000,z,x,y-1000,z);
zlline(x+1000,y,z,x-1000,y,z);
             
}

if (layer_spec_mode==2)
{
for (x=0;x<320;x++)scrbuf[x+38*320]=19;
for (Uint8 i=0;i<movie_control_nodes[curmovie];i++)
{
x=319*movie_control_node_pos[curmovie][i]/movie_length[curmovie];
scrbuf[x+38*320]=29;
     l_textstring=sprintf(s_textstring,"%i",i);

     s_drawtext(x,38,34);     
}
scrbuf[319*c_movie_step/movie_length[curmovie]+37*320]=29;
    
    
}
else{
for (x=0;x<320;x++)scrbuf[x+38*320]=19;
for (Uint8 i=0;i<movie_layer_nodes[curmovie][curlayer];i++)
{
x=319*movie_node_pos[curmovie][i][curlayer]/movie_length[curmovie];
scrbuf[x+38*320]=29;
     l_textstring=sprintf(s_textstring,"%i",i);

     s_drawtext(x,38,28);     
}
scrbuf[319*c_movie_step/movie_length[curmovie]+37*320]=29;
}
}
     if (layer_spec_mode==2)
       {
     l_textstring=sprintf(s_textstring,"ConNode Mode (c_nodes=%i)",movie_control_nodes[movie_playing]);
     s_drawtext(100,0,15);     
    if (controlpad.button[PAD_Z]==0) 
     l_textstring=sprintf(s_textstring,"X-insert control node");
     else
     l_textstring=sprintf(s_textstring,"X-delete control node");
     s_drawtext(100,12,15);     
if (ccon[0]==8)
if (ccon[1]<editor_dialognum)
{
l_textstring=sprintf(s_textstring,"%s %s",zdialogs[2*ccon[1]],zdialogs[1+2*ccon[1]]);
     s_drawtext(0,228,15);     

}

     l_textstring=sprintf(s_textstring,"%s",ccon_s[ccon[0]]);
     if (cconi==0)s_drawtext(0,12,30);else s_drawtext(0,12,24);     
     l_textstring=sprintf(s_textstring,"%i",ccon[1]);
     if (cconi==1)s_drawtext(0,24,30);else s_drawtext(0,24,24);     
     l_textstring=sprintf(s_textstring,"%i",ccon[2]);
     if (cconi==2)s_drawtext(50,24,30);else s_drawtext(50,24,24);     
       }
     else
     if (layer_spec_mode==1)
       {
     l_textstring=sprintf(s_textstring,"Precision editor");
     s_drawtext(100,0,15);     

     l_textstring=sprintf(s_textstring,"Axis:%i(X to switch)",node_axis);
     s_drawtext(100,12,15);     
       }
       else
{
     l_textstring=sprintf(s_textstring,"Free Camera Layer Mode");
     s_drawtext(100,0,15);     
   if (controlpad.button[PAD_Z]==0)
     l_textstring=sprintf(s_textstring,"X-insert new node");
     else
     l_textstring=sprintf(s_textstring,"X-delete node %i",currentnode);
     s_drawtext(100,12,15);     

}     
  break;//finaly.. porn scenes
}
}



void savemodelscale(void)
{
FILE *fp;char c;Sint32 i,v;
fp=fopen("data/modscale.gmg","wb");
for (Sint32 i=0;i<256;i++)
 {
 v=model_scalex[i]-32768;          
 fputc(v/256,fp);        
 fputc(v%256,fp);            

 v=model_scaley[i]-32768;          
 fputc(v/256,fp);        
 fputc(v%256,fp);            

 v=model_scalez[i]-32768;          
 fputc(v/256,fp);        
 fputc(v%256,fp);            
            
 }
for (Sint32 i=0;i<256;i++)
 {
 fputc(model_scalei[i],fp);            
            
 }
 
fclose(fp);
}

Sint32 modelv0,modelv1,modelvr,modelvi,modelvi_tri,model_vicol;
Uint8 model_scalev,model_scaledelay;
Uint8 animationmode;
void RenderEModel(void)
{
     
modelv0=SuperAngle(modelv0);
modelv1=SuperAngle(modelv1);

Sint32 rr=FPMUL(modelvr,f_cos[modelv1]);
camera[0]=32768+FPMUL(f_cos[modelv0],rr);
camera[1]=12768+FPMUL(f_sin[modelv1],modelvr);
camera[2]=32768+FPMUL(f_sin[modelv0],rr);

camera[3]=4096-modelv1;
camera[4]=SuperAngle(4096-modelv0-1024);
camera[5]=0;


screenborder=0;
renderscene();        
Sint32 v0,v1,v2,f,t;

switch (animationmode)    
 {
 case 0:
  l_textstring=sprintf(s_textstring,"Frame %i/%i",monster_frame0[0],model_ani[monster_model[0]]-1);
  s_drawtext(5,17,14);
      
      l_textstring=sprintf(s_textstring,"Frame Preview");

        break;
 case 1:
      
  l_textstring=sprintf(s_textstring,"x:%i",model_scalex[modelvi]);
  if (model_scalev==0) 
  s_drawtext(270,105,15);
  else
  s_drawtext(270,105,14);

  l_textstring=sprintf(s_textstring,"y:%i",model_scaley[modelvi]);
  if (model_scalev==1) 
  s_drawtext(270,117,15);
  else
  s_drawtext(270,117,14);
  l_textstring=sprintf(s_textstring,"z:%i",model_scalez[modelvi]);
  if (model_scalev==2) 
  s_drawtext(270,129,15);
  else
  s_drawtext(270,129,14);
  
  l_textstring=sprintf(s_textstring,"i:%i",model_scalei[modelvi]);
  if (model_scalev==3) 
  s_drawtext(270,141,15);
  else
  s_drawtext(270,141,14);
      
      
      
      l_textstring=sprintf(s_textstring,"Scale Settings");
       break;

 case 2:
 zlcolor=16+15*(count/5%2);

f=model_f0[modelvi]+modelvi_tri;
t=model_v0[modelvi]+monster_frame0[0]*model_vs[modelvi];
v0=f_0[f]+t;
v1=f_1[f]+t;
v2=f_2[f]+t;    

zlline(32768+m_vx[v0],m_vy[v0],32768+m_vz[v0],32768+m_vx[v1],m_vy[v1],32768+m_vz[v1]);     
zlline(32768+m_vx[v2],m_vy[v2],32768+m_vz[v2],32768+m_vx[v1],m_vy[v1],32768+m_vz[v1]);     
zlline(32768+m_vx[v0],m_vy[v0],32768+m_vz[v0],32768+m_vx[v2],m_vy[v2],32768+m_vz[v2]);     

 l_textstring=sprintf(s_textstring,"i_Color1=%i",model_vicol);
 s_drawtext(255,108,model_vicol);     
 l_textstring=sprintf(s_textstring,"i_Color0=%i",f_c[f]);
 s_drawtext(255,120,f_c[f]);     
 l_textstring=sprintf(s_textstring,"face %i/%i",modelvi_tri,model_fs[modelvi]-1);
 s_drawtext(255,132,14);     


        l_textstring=sprintf(s_textstring,"Color Override Maker");
        break;
 case 3:l_textstring=sprintf(s_textstring,"Animation preview");
        break;
 case 4:l_textstring=sprintf(s_textstring,"Secret");
        break;
 
 
 }

 s_drawtext(315-l_textstring*5,204,14);     
     
 if (editorcount<10)
 {
 l_textstring=sprintf(s_textstring,"Please Wait...");
 s_drawtext(5,4,14);     
 }
 else
 if (count<120)
 {
 l_textstring=sprintf(s_textstring,"Model Viewer Untility");
 s_drawtext(5,4,15);     
 }
 else
 {
 l_textstring=sprintf(s_textstring,"Model %i/%i",modelvi,model_mms-1);
 s_drawtext(5,4,14);     
 }
 
  if (count<80)
  {   
 l_textstring=sprintf(s_textstring,"Memory Manager Report:");
 s_drawtext(5,208,14);     
 l_textstring=sprintf(s_textstring,"Vertexes %i/32768  Faces: %i/4096",model_mmv,model_mmf);
 s_drawtext(5,220,14);     
  }
  {   
  }     

}

Uint8 e_monsteri,e_aix,e_aiy;
void RenderEAI(void)
{
     Uint8 c;

 if (editorcount<10)
 {
 l_textstring=sprintf(s_textstring,"Please Wait...");
 s_drawtext(240,228,15);     
 }

 l_textstring=sprintf(s_textstring,"Monster %i%i : %s",e_monsteri/10%10,e_monsteri%10,t_monster_name[e_monsteri]);
 s_drawtext(5,5,14);
 
 l_textstring=sprintf(s_textstring,"Peace");
if (e_aix==0) s_drawtext(5,17,15);else s_drawtext(5,17,14);
 l_textstring=sprintf(s_textstring,"Target");
if (e_aix==1) s_drawtext(45,17,15);else s_drawtext(45,17,14);
 l_textstring=sprintf(s_textstring,"Hunt");
if (e_aix==2) s_drawtext(85,17,15);else s_drawtext(85,17,14);
 l_textstring=sprintf(s_textstring,"Melee");
if (e_aix==3) s_drawtext(125,17,15);else s_drawtext(125,17,14);
 l_textstring=sprintf(s_textstring,"Panic");
if (e_aix==4) s_drawtext(165,17,15);else s_drawtext(165,17,14);



 if (e_aiy==0) c=15;else c=14;
  l_textstring=sprintf(s_textstring,"Idle");s_drawtext(205,29,c);
 if (e_aiy==1) c=15;else c=14;
 l_textstring=sprintf(s_textstring,"RandomStep");s_drawtext(205,41,c);
 if (e_aiy==2) c=15;else c=14;
 l_textstring=sprintf(s_textstring,"HuntPlayer");s_drawtext(205,53,c);
 if (e_aiy==3) c=15;else c=14;
 l_textstring=sprintf(s_textstring,"StepToTarget");s_drawtext(205,65,c);
 if (e_aiy==4) c=15;else c=14;
 l_textstring=sprintf(s_textstring,"Retreat");s_drawtext(205,77,c);
 if (e_aiy==5) c=15;else c=14;
 l_textstring=sprintf(s_textstring,"%s",skill_s[2*t_monster_action[e_monsteri][0]]);s_drawtext(205,89,c);
 if (e_aiy==6) c=15;else c=14;
 l_textstring=sprintf(s_textstring,"%s",skill_s[2*t_monster_action[e_monsteri][1]]);s_drawtext(205,101,c);
 if (e_aiy==7) c=15;else c=14;
 l_textstring=sprintf(s_textstring,"%s",skill_s[2*t_monster_action[e_monsteri][2]]);s_drawtext(205,113,c);
      
for(Uint8 x=0;x<5;x++)
for(Uint8 y=0;y<8;y++)     
{
 l_textstring=sprintf(s_textstring,"%i",t_monster_ai[e_monsteri][x][y]);
if ((x==e_aix)&(y==e_aiy))
 s_drawtext(5+40*x,29+y*12,15);
 else
 s_drawtext(5+40*x,29+y*12,14);
          
          
}     
 l_textstring=sprintf(s_textstring,"HP:%i-%i MP:%i MV:%i",t_monster_hp[e_monsteri][0],t_monster_hp[e_monsteri][0]+t_monster_hp[e_monsteri][1],t_monster_mn[e_monsteri],t_monster_mv[e_monsteri]);
 s_drawtext(5,144,14);
 l_textstring=sprintf(s_textstring,"STR:%i DEX:%i CON:%i INT:%i WIS:%i CHA:%i",t_monster_str[e_monsteri],t_monster_dex[e_monsteri],t_monster_con[e_monsteri],t_monster_int[e_monsteri],t_monster_wis[e_monsteri],t_monster_cha[e_monsteri]);
 s_drawtext(5,156,14);
 l_textstring=sprintf(s_textstring,"Speed:%i",t_monster_speed[e_monsteri]);
 s_drawtext(5,168,14);
 l_textstring=sprintf(s_textstring,"P-Damage:%i-%i M-Damage:%i-%i",t_monster_damage[e_monsteri][0],t_monster_damage[e_monsteri][0]+t_monster_damage[e_monsteri][1],t_monster_mdamage[e_monsteri][0],t_monster_mdamage[e_monsteri][0]+t_monster_mdamage[e_monsteri][1]);
 s_drawtext(5,180,14);
 l_textstring=sprintf(s_textstring,"AC:%i MagicResistance:%i",t_monster_armor[e_monsteri],t_monster_resist[e_monsteri]);
 s_drawtext(5,192,14);


}


void ModelEditorModelSwitch(void)
{
monster_model[0]=modelvi;
monster_frame0[0]=0;
monster_frame1[0]=0;     
modelvi_tri=0;
model_vicol=31;
}

void PrepareEModel(void)
{
ClearLevel();
mapt0[0]=1;
monster_x[0]=32768;     
monster_y[0]=32768;
monster_z[0]=0;     
monster_visible[0]=1;
monster_angle[0]=0;
monster_ingame[0]=1;     
monster_frame0[0]=0;
monster_frame1[0]=0;
monsters=1;
count=0;
modelv0=0;
modelv1=0;
modelvr=190131;

modelvi=0;
monster_model[0]=modelvi;
animationmode=0;
modelvi_tri=0;model_vicol=31;
}

void SaveColorOverride(void)
{
FILE *fp;
char fname[50];
sprintf(fname,"override.%i%i%i",modelvi/100,modelvi/10%10,modelvi%10);
fp=fopen(fname,"wb");
for (int i=0;i<model_fs[modelvi];i++)
fputc(f_c[model_f0[modelvi]+i],fp);
fclose(fp);     
}

void SaveAI(void)
{
FILE *fp;
fp=fopen("data/monster.ai","wb");
for (int i=0;i<32;i++)
for (int x=0;x<5;x++)
for (int y=0;y<8;y++)
 {
fputc(t_monster_ai[i][x][y],fp);
 }
fclose(fp);     
}



Uint8 asm_com=47;
char fchasm[48][10]=
{
"NOP",
"PLAYMUS",//music attack
"PLAYSND",//PlaySound
"ADDSKILL",// learn something
"ADDITEM",// add item
"KILLTRIG",//kill this trigger. he will get no response
"DAMAGE",// damage player
"DAMAGx10",// damage*10 player

"DAMAGx50",// damage*50 player
"CLREMOBS",// Clear enemy
"CLRAMOBS",// Clear enemy&friends
"SETLMUS",//levermusictrack
"SETWMUS",//levelwarmusic
"PLVIDEO",//begin cutscene
"ACTTRIG",//Wanna more triggerz?
"SPAWNMOB",//Gonna be a party

"SETX",//cursor coordinates
"SETY",//by default they are always monster_roomi[0]
"SETZ",//
"COPY",//from coord0 to coord1 
"DELAY",//Make trigger wait
"SPAWNITM",//Drop item
"SPWNFLD0",//On Player
"SPAWFLD1",//Just in place 

"MAPT0",
"MAPT1",
"MAPT2",
"MAPT3",
"MAPT4",
"MAPT5",
"MAPCAM0",
"MAPTAG",

"MDISPLX",
"MDISPLY",
"MDISPLZ",
"DIALOG",
"LMESSAGE",
"TMESSAGE",
"DMGALL10",//Damage all monsters
"FOGCOLOR",

"TELEPLR",//Teleport Player
"LSIGHT",//levelsight
"NOITEMS",//player looses all items
"MAPOBG",//set mapobj
"MAXMONST",//Maxmonsters paramets.. Flood shold be crazy/happy
"NEXTLVL",
"SETAMUS",//All music
"DTHTRIG"

};
Uint8 se_buffer[2];
const char c_curs[2]={'_',' '};
Uint8 tex=0,tey=0;
void RenderTriggerEditor(void)
{
l_textstring=sprintf(s_textstring,"FleshChasmer Assembler 1.0");
s_drawtext(0,0,31);
l_textstring=sprintf(s_textstring,"Trigger[%i] [L-R]",curtrigger);
s_drawtext(0,12,31);
if (curtrigger)
l_textstring=sprintf(s_textstring,"misc info : none");
else
l_textstring=sprintf(s_textstring,"misc info : Autorun");
s_drawtext(0,24,31);

l_textstring=sprintf(s_textstring,"Cursor x:%i y:%i z:%i",cursorx,cursory,cursorz);
s_drawtext(150,0,31);

Sint16 i=0;
for (i=0;i<320;i++)
scrbuf[i+320*35]=20;
for (Uint8 y=0;y<7;y++)
{
i=trig[curtrigger*32+tey*2]-3+y;
if (i>=0 & i<48)
{
 l_textstring=sprintf(s_textstring,"%s",fchasm[i]);
 if (y==3)
 s_drawtext(5,36+y*12,31);
 else
 s_drawtext(5,36+y*12,19+2*zabs(y-3));
                
}
}
i=curtrigger*32+tey*2;
l_textstring=sprintf(s_textstring,"No Operation Info%c",c_curs[count/4%2]);
Uint8 c=29;
switch (trig[i])
{
case 3:
if (trig[i+1]>31) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
else
l_textstring=sprintf(s_textstring,"Learn '%s'%c",skill_s[2*trig[i+1]],c_curs[count/4%2]);
break;       
case 4:
if (trig[i+1]>63) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
else
l_textstring=sprintf(s_textstring,"Recieve '%s'%c",item_s[2*trig[i+1]],c_curs[count/4%2]);
break;       
case 13:
if (trig[i+1]>15) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
break;       
case 14:
if (trig[i+1]>15) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
break;       

case 15:
if (trig[i+1]>31) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
else
l_textstring=sprintf(s_textstring,"Spawn %s%c",t_monster_name[trig[i+1]],c_curs[count/4%2]);
break;       

case 21:
if (trig[i+1]>63) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
else
l_textstring=sprintf(s_textstring,"Drop '%s'%c",item_s[2*trig[i+1]],c_curs[count/4%2]);
break;       
case 35:
if (trig[i+1]>=editor_dialognum) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
else
l_textstring=sprintf(s_textstring,"%s %s",zdialogs[2*trig[i+1]],zdialogs[1+2*trig[i+1]]);
break;       
case 36:
if (trig[i+1]>=editor_messagenum) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
else
l_textstring=sprintf(s_textstring,"%s",zmessages[trig[i+1]]);
break;       
case 37:
if (trig[i+1]>=editor_messagenum) {l_textstring=sprintf(s_textstring,"It gonna be a grash!");c=35;}
else
l_textstring=sprintf(s_textstring,"%s",zmessages[trig[i+1]]);
break;       
       
}
s_drawtext(0,228,c);

l_textstring=sprintf(s_textstring,"Buffer:%c%c%c%c",c_hex[se_buffer[0]/16],c_hex[se_buffer[0]%16],c_hex[se_buffer[1]/16],c_hex[se_buffer[1]%16]);
s_drawtext(0,204,26);


for (Uint8 y=0;y<16;y++)     
{
l_textstring=sprintf(s_textstring,"%i:",curtrigger*32+y*2);
s_drawtext(155-l_textstring*5,36+y*12,28);

for (Uint8 x=0;x<2;x++)
{
 if (x==0)
 l_textstring=sprintf(s_textstring,"%s",fchasm[trig[curtrigger*32+y*2]]);
 else
 l_textstring=sprintf(s_textstring,"%i",trig[curtrigger*32+y*2+1]);
Uint8 c;
 if ((x==tex)&(y==tey))
 c=30+count/2%2;
 else c=23;
 s_drawtext(160+x*50,36+y*12,c);
 }     
}
#ifdef GP2X
SDL_Delay(15);
#endif
}


void RenderEditor(void)
{

switch (GameMode)
{
case EDITOR_MENU:RenderEMenu();break;       
case EDITOR_PALETTE:RenderEPalette();break;       
case EDITOR_TEXTURE:if (TileSelector) RenderETileSelector(); else RenderETexture();break;       
case EDITOR_LEVEL:
if (TileSelector) RenderETileSelector(); else 
if (inTrigEdit)
RenderTriggerEditor();
else
renderLeditor();
break;       
case EDITOR_MODEL:RenderEModel();break;       
case EDITOR_AI:RenderEAI();break;       

};

     
}
void ProcEditor(void)
{







editorcount++;    
if (editorcount>10)        
{
//Editor Menu Demonstration
/*
controlpad.angle=-1;
for (int i=0;i<11;i++)
controlpad.button[i]=0;

if (count%4==0)
{
if (menupos<7) controlpad.angle=4;
else controlpad.button[PAD_A]=1;
}
*/
//Editor Menu Demonstration
                           
if (inTrigEdit)
{
if (count%2)   
 {
if (controlpad.button[PAD_R2])
if (controlpad.button[PAD_L2])
if (controlpad.button[PAD_R1])
if (controlpad.button[PAD_L1])
for (Uint16 i=0;i<512;i++) trig[i]=0;
      switch (controlpad.angle)
      {
            case 0:if (tey)tey--;break;
            case 2:if (tex<1)tex++;break;
            case 4:if (tey<15)tey++;break;
            case 6:if (tex)tex--;break;

      }
if (controlpad.button[PAD_L1])
 {if (curtrigger)curtrigger--;}
else
if (controlpad.button[PAD_R1])
 {if (curtrigger<15)curtrigger++;}
Uint16 cii=curtrigger*32+tey*2+tex;
if (controlpad.button[PAD_L2])
{
if (trig[cii]) trig[cii]--;
}
else
if (controlpad.button[PAD_R2])
{
if (tex==0) {if (trig[cii]<asm_com) trig[cii]++;}
else
{if (trig[cii]<255) trig[cii]++;}
}
if (controlpad.button[PAD_X])trig[cii]=0;
if (controlpad.button[PAD_A])
{
cii=cii/2*2;
se_buffer[0]=trig[cii];
se_buffer[1]=trig[cii+1];
}
if (controlpad.button[PAD_B])
{
cii=cii/2*2;
trig[cii]=se_buffer[0];
trig[cii+1]=se_buffer[1];
}

if (controlpad.button[PAD_Z]|controlpad.button[PAD_START]) {inTrigEdit=0;editorcount=0;}
 }                 
}
else             
if (TileSelector)
{
if (GameMode==EDITOR_TEXTURE)
                {
if (controlpad.button[PAD_SELECT]) {SaveTiles();editorcount=0;}//Here,here, SaintTeeth :)
                if (controlpad.button[PAD_Y]) 
                {for (int x=0;x<16;x++)
                 for (int y=0;y<16;y++)
                  Tile[Tile_offset[CurrentTile]+x+y*16]=tileedit[x][y];                
                  editorcount=6;
                  }
                if (controlpad.button[PAD_X]) 
                {
                for (int x=0;x<16;x++)
                 for (int y=0;y<16;y++)
                  tileedit[x][y]=Tile[Tile_offset[CurrentTile]+x+y*16];                
                  editorcount=6;
                  TileSelector=0;
                  }
                }//TextureEditor TileSelector Mod
else
if (GameMode==EDITOR_LEVEL)
 {
if (controlpad.button[PAD_A]) {TileSelector=0;editorcount=5;}
 }

if (controlpad.button[PAD_START]) {TileSelector=0;editorcount=0;}
      if (count%2==0)
      {
if (controlpad.button[PAD_L1]) CurrentTile-=32;
if (controlpad.button[PAD_R1]) CurrentTile+=32;

      switch (controlpad.angle)
      {
            case 0:CurrentTile-=8;break;
            case 2:CurrentTile++;break;
            case 4:CurrentTile+=8;break;
            case 6:CurrentTile--;break;
      }
      }    
}
else
switch (GameMode)
{
case EDITOR_LEVEL:
 if (camfollowmode) 
  {
  if (levelmode!=4) camfollowmode=0;
  }
  else 
  {
  if (levelmode==8) 
  {
  if (movie_type[curmovie]==0)
  screenborder=40;else screenborder=0;
  }
  else
if (levelmode==4)  screenborder=0;
 else
  screenborder=20;
  }
if (camfollowmode & (levelmode==4)) camset(cursorx,cursory,cursorz);
       if (controlpad.button[PAD_START]) {fadecount=10;NewGameMode=EDITOR_MENU;}
       else
       if (controlpad.button[PAD_SELECT]) {SaveLevel(CurrentLevel);fadecount=10;NewGameMode=EDITOR_MENU;}

if (controlpad.button[PAD_L1] && controlpad.button[PAD_R1])
 {    
if (count%2)      
if (controlpad.button[PAD_A])
  {
         switch (levelmode)    
           {
            case 2:editorcount=5;twosidedtile=!twosidedtile; break;    
            case 4:editorcount=5;camfollowmode=!camfollowmode; break;    
            case 7:if (triggers>0) triggers--;if (curtrigger>triggers)curtrigger=triggers;break;    
            case 8:if (movies>0) movies--;if (curmovie>movies){curmovie=movies;c_movie_step=0;}break;
            case 12:if (cursortarget) cursortarget=0;else cursortarget=1;break;    
            case 13:if (relativecursor) relativecursor=0;else relativecursor=1;break;    
            }                                         
                                                      
  }      
     if (count %2)
     if (controlpad.button[PAD_B])
  {
         switch (levelmode)    
           {
            case 2:editorcount=5;twosidedtile=!twosidedtile; break;    
            case 4:editorcount=5;camfollowmode=!camfollowmode; break;    
            case 7:if (triggers<15) triggers++;break;    
            case 8:if (movies<15) movies++;break;
            case 12:if (cursortarget) cursortarget=0;else cursortarget=1;break;    
            case 13:if (relativecursor) relativecursor=0;else relativecursor=1;break;    
            case 14:if (solidcursor) solidcursor=0;else solidcursor=1;break;    
            }                                         
                                                      
  } 
     if (levelmode==8)
     {
     if (count %2)
      {
      if (controlpad.button[PAD_Z]) movie_type[curmovie]=(movie_type[curmovie]+1)%2;
      if (controlpad.button[PAD_X])
      movie_num_layers[curmovie]=(movie_num_layers[curmovie]+1)%8;
      }
     if (controlpad.button[PAD_L2]) if (movie_length[curmovie])movie_length[curmovie]--;
     if (controlpad.button[PAD_R2]) if (movie_length[curmovie]<10000)movie_length[curmovie]++;

     }   
        switch (controlpad.angle)
       {
        case 0:if (levelmode>0) levelmode--;break;
        case 4:if (levelmode<14) levelmode++;break;
   
        case 2://right arrow
         switch (levelmode)    
           {
            case 2:twosidedtile=1; break;    
            case 4:camfollowmode=1; break;    

            case 7:if (curtrigger<triggers) curtrigger++;break;    
            case 8:if (curmovie<movies) curmovie++;c_movie_step=0;curlayer=0;break;
                
            case 11:if (editorcamera_speed<3400)editorcamera_speed+=100;break;      
            case 12:cursortarget=1;break;    
            case 13:relativecursor=1;break;    
            case 14:solidcursor=1;break;    
           }  
        break;
        case 6://left arrow
         switch (levelmode)    
           {
            case 2:twosidedtile=0; break;    
            case 4:camfollowmode=0; break;    
            case 7:if (curtrigger>0) curtrigger--;break;    
            case 8:if (curmovie>0) curmovie--;c_movie_step=0;curlayer=0;break;
            case 11:if (editorcamera_speed>1000)editorcamera_speed-=100;break;      
            case 12:cursortarget=0;break;    
            case 13:relativecursor=0;break;    
            case 14:solidcursor=0;break;    
           }  
        break;
       }   
 }// LEVEL EDITOR MODE SELECTOR
 else
 if (layer_spec_mode)
 {
MovieStep();
 if (layer_spec_mode==2)
   {//2222222222
 if (controlpad.button[PAD_L2]&controlpad.button[PAD_R2])
  {layer_spec_mode=0;editorcount=5;}
    if (controlpad.button[PAD_X]) 
    if (controlpad.button[PAD_Z]==0) 
    {editorcount=5;MInsert_ConNode();}
    else
    {editorcount=5;MDelete_ConNode();}
if (controlpad.button[PAD_L2])
if (ccon[cconi])ccon[cconi]--;
if (controlpad.button[PAD_R2])
{ccon[cconi]++;if (cconi==0) if (ccon[0]>=CCON_SI) ccon[0]=CCON_SI-1;}
if (count%2)
if (controlpad.button[PAD_Y]) cconi=(cconi+1)%3;


    if (controlpad.button[PAD_L1]) if (c_movie_step)c_movie_step--;
    if (controlpad.button[PAD_R1]) if (c_movie_step<movie_length[curmovie])c_movie_step++;               
movie_playing=curmovie;

                        
   }///22222222222
   else
 if (layer_spec_mode==1)//precious
   {

 if (controlpad.button[PAD_L2]&controlpad.button[PAD_R2])
  {layer_spec_mode=2;editorcount=5;}
if (movie_layer_nodes[curmovie][curlayer])
{
GetCurrentNode();
Sint32 sp;
if (node_axis>2) sp=10; else sp=1500;
if (controlpad.button[PAD_L2]) movie_node[curmovie][currentnode][curlayer][node_axis]-=sp;
if (controlpad.button[PAD_R2]) movie_node[curmovie][currentnode][curlayer][node_axis]+=sp;
if (node_axis>2) movie_node[curmovie][currentnode][curlayer][node_axis]=SuperAngle(movie_node[curmovie][currentnode][curlayer][node_axis]);
}
    if (count%2)
    if (controlpad.button[PAD_X]) node_axis=(node_axis+1)%6;

    if (controlpad.button[PAD_Y])
    {
    if (node_axis>2) movie_node[curmovie][currentnode][curlayer][node_axis]=0;
    else
    if (currentnode) movie_node[curmovie][currentnode][curlayer][node_axis]=movie_node[curmovie][currentnode-1][curlayer][node_axis];                            
    }


    if (controlpad.button[PAD_L1]) if (c_movie_step)c_movie_step--;
    if (controlpad.button[PAD_R1]) if (c_movie_step<movie_length[curmovie])c_movie_step++;               
movie_playing=curmovie;
//  aaaaaaaaa
  }
 }
 else
if (controlpad.button[PAD_Y] && (levelmode>0))//cursorcontrol
{
if (count%2)
   {
            
   Sint8 angle=controlpad.angle;         
   if (relativecursor)
    {
    if (angle>=0)
     {
     angle=(angle+((rcamera[4]+3584)%4096)/1024*2+2)%8;            
     }
    }
    
   if (solidcursor)
    {
   cursori=cursorx+cursory*128+cursorz*16384;
   switch (angle)
      {
             case 0:if (cursory<levely) 
             if (!tiledata_block[mapt4[cursori]])
             cursory++;break;
             case 2:if (cursorx<levelx) 
             if (!tiledata_block[mapt2[cursori]])
             cursorx++;break;
             case 4:if (cursory>0)
             if (!tiledata_block[mapt3[cursori]])
             cursory--;break;
             case 6:if (cursorx>0) 
             if (!tiledata_block[mapt1[cursori]])

             cursorx--;break;
      }
   if (controlpad.button[PAD_L1]) {if (cursorz>0)if (!tiledata_block[mapt0[cursori]])cursorz--;}
   else
   if (controlpad.button[PAD_R1]) if (cursorz<levelz)if (!tiledata_block[mapt5[cursori]]) cursorz++;
                   
    }
    else
    { 
   switch (angle)
      {

             case 0:if (cursory<levely) cursory++;break;
             case 2:if (cursorx<levelx) cursorx++;break;
             case 4:if (cursory>0) cursory--;break;
             case 6:if (cursorx>0) cursorx--;break;
      }
   if (controlpad.button[PAD_L1]) {if (cursorz>0) cursorz--;}
   else
   if (controlpad.button[PAD_R1]) if (cursorz<levelz) cursorz++;
    }
   }                              
}
else
if ((camfollowmode)& (levelmode==4))
{//camera follow mode 
cursori=cursorx+cursory*128+cursorz*16384;
 if (mapcam0[cursori]>=128)
 if (count%2)
 {
Uint8 c0=mapcam1[cursori]%16;
Uint8 c1=mapcam1[cursori]/16;
Uint8 c2=mapcam2[cursori]%16;
Uint8 c3=mapcam2[cursori]/16;
Uint8 c4=mapcam3[cursori]%16;
Uint8 c5=mapcam3[cursori]/16;


if (controlpad.button[PAD_L1]) c5--;else
if (controlpad.button[PAD_R1]) c5++;else

if (controlpad.button[PAD_A]) c2--;else
if (controlpad.button[PAD_B]) c2++;else
    
if (controlpad.button[PAD_X]) 
      switch (controlpad.angle)
      {
             case 6:c4--;break;
             case 2:c4++;break;
             case 0:c3++;break;
             case 4:c3--;break;
      }
      else
      switch (controlpad.angle)
      {
             case 6:c0--;break;
             case 2:c0++;break;
             case 0:c1++;break;
             case 4:c1--;break;
      }
      
    c0=c0&15;  
    c1=c1&15;  
    c2=c2&15;  
    c3=c3&15;  
    c4=c4&15;  
    c5=c5&15;  
 mapcam1[cursori]=c0+c1*16;
 mapcam2[cursori]=c2+c3*16;
 mapcam3[cursori]=c4+c5*16;
 }

if (controlpad.button[PAD_Z])
 {
     if (controlpad.button[PAD_X])
     {
     cursori=cursorx+cursory*128+cursorz*16384;
     mapcam0[cursori]=cam0;                             
     mapcam1[cursori]=cam1;                             
     mapcam2[cursori]=cam2;                             
     mapcam3[cursori]=cam3;                             
     }
     else
     {
     cursori=cursorx+cursory*128+cursorz*16384;
     cam0=mapcam0[cursori];
     cam1=mapcam1[cursori];
     cam2=mapcam2[cursori];
     cam3=mapcam3[cursori];
     }
  
     
 }


}
else
{//static
     if (controlpad.button[PAD_A])
        {
        Sint32 speed=editorcamera_speed;                          
        Sint32 r=FPMUL(speed,f_cos[rcamera[3]]);                          
           camera[1]+=FPMUL(speed,f_sin[rcamera[3]]);                       
           camera[0]+=FPMUL(r,f_sin[rcamera[4]]);                       
           camera[2]+=FPMUL(r,f_cos[rcamera[4]]);                       

        }
     if (controlpad.button[PAD_B])
        {
        Sint32 speed=-editorcamera_speed;                          
        Sint32 r=FPMUL(speed,f_cos[rcamera[3]]);                          
           camera[1]+=FPMUL(speed,f_sin[rcamera[3]]);                       
           camera[0]+=FPMUL(r,f_sin[rcamera[4]]);                       
           camera[2]+=FPMUL(r,f_cos[rcamera[4]]);                       

        }


       if (controlpad.button[PAD_L1]) camera[5]-=6;
       if (controlpad.button[PAD_R1]) camera[5]+=6;
      switch (controlpad.angle)
      {

             case 0:camera[3]+=12;break;
             case 2:camera[4]+=12;break;
             case 4:camera[3]-=12;break;
             case 6:camera[4]-=12;break;
      }

     

if (levelmode>8) levelmode=lastlmode;else lastlmode=levelmode;

if (count%2==0)
 switch (levelmode)
{
        case 0://header
    {
     if (controlpad.button[PAD_X]) param=(param+1)%8;
     if (controlpad.button[PAD_R2]) 
            switch (param)
            {
            case 0:if (fogcolor<255)fogcolor++;break;       
            case 1:if (levelx<126) levelx++;break;       
            case 2:if (levely<126)levely++;break;       
            case 3:if (levelz<6)levelz++;break;       
            case 4:if (levelsight<9)levelsight++;break;       
            case 5:if (maxmonsters<16) maxmonsters++;break;       
            case 6:if (levelmusictrack<50) levelmusictrack++;break;       
            case 7:if (level_tag<31) level_tag++;break;       
            }
      
     if (controlpad.button[PAD_L2]) 
            switch (param)
            {
            case 0:if (fogcolor>16)fogcolor--;break;       
            case 1:if (levelx>0)levelx--;break;       
            case 2:if (levely>0)levely--;break;       
            case 3:if (levelz>0)levelz--;break;       
            case 4:if (levelsight>5) levelsight--;break;       
            case 5:if (maxmonsters>2) maxmonsters--;break;       
            case 6:if (levelmusictrack>0) levelmusictrack--;break;       
            case 7:if (level_tag>0) level_tag--;break;       
            }
            break;//header
case 1://mesh
if (controlpad.button[PAD_Z]) 
if (selstep<64)
selstep=selstep<<1;
else selstep=1; 
if (controlpad.button[PAD_X]) selaxis=(selaxis+1)%3;

cursori=cursorx+cursory*128+cursorz*16384;
if (controlpad.button[PAD_R2]) 
{
 
switch (selaxis)
 {
  case 0://X
  meshxdisplace[cursori]+=selstep;
  meshx[cursori]=65535*cursorx+meshxdisplace[cursori]*256;
  break;   
  case 1://Y
  meshydisplace[cursori]+=selstep;
  meshy[cursori]=65535*cursory+meshydisplace[cursori]*256;
  break;   
  case 2://Z
  meshzdisplace[cursori]+=selstep;
  meshz[cursori]=65535*cursorz+meshzdisplace[cursori]*256;
  break;   
     
 
 }                               
if (controlpad.button[PAD_L2]) 
 {
  meshxdisplace[cursori]=0;
  meshx[cursori]=65535*cursorx;
  meshydisplace[cursori]=0;
  meshy[cursori]=65535*cursory;
  meshzdisplace[cursori]=0;
  meshz[cursori]=65535*cursorz;
editorcount=0; 
                               
 }
}
else
if (controlpad.button[PAD_L2]) 
{
switch (selaxis)
 {
  case 0://X
  meshxdisplace[cursori]-=selstep;
  meshx[cursori]=65535*cursorx+(meshxdisplace[cursori])*256;
  break;   
  case 1://Y
  meshydisplace[cursori]-=selstep;
  meshy[cursori]=65535*cursory+(meshydisplace[cursori])*256;
  break;   
  case 2://Z
  meshzdisplace[cursori]-=selstep;
  meshz[cursori]=65535*cursorz+(meshzdisplace[cursori])*256;
  break;   
     
 }                               
}
   break;//mesh
   case 2://Tile Wrap
   if (controlpad.button[PAD_Z]) {TileSelector=1;editorcount=5;}
if (controlpad.button[PAD_R2]&controlpad.button[PAD_L2]){TileSelector=1;editorcount=5;};
   if (count%2==0)
      {
   if (controlpad.button[PAD_L2]) if (TilePlace>0) TilePlace--;else TilePlace=5;
   if (controlpad.button[PAD_R2]) if (TilePlace<5) TilePlace++;else TilePlace=0;

   if (controlpad.button[PAD_X]) 
    {
    cursori=cursorx+cursory*128+cursorz*16384;
    switch (TilePlace)
     {
     case 0://Down
     mapt0[cursori]=CurrentTile;
     break;      
     case 1://west
     mapt1[cursori]=CurrentTile;
     break;      
     case 2://east
     mapt2[cursori]=CurrentTile;
     break;      
     case 3://south
     mapt3[cursori]=CurrentTile;
     break;      
     case 4://north
     mapt4[cursori]=CurrentTile;
     break;      
     case 5://Up
     mapt5[cursori]=CurrentTile;
     break;      
     }
     if (twosidedtile)
       switch (TilePlace)
  {
  case 0:
       if (cursorz>0)
       mapt5[cursori-16384]=CurrentTile;break;       
  case 1:if (cursorx>0)
       mapt2[cursori-1]=CurrentTile;
       break;       
  case 2:if (cursorx<levelx)
       mapt1[cursori+1]=CurrentTile;
       break;       
  case 3:if (cursory>0)
       mapt4[cursori-128]=CurrentTile;
       break;       
  case 4:if (cursory<levely)
       mapt3[cursori+128]=CurrentTile;
       break;       
  case 5:if (cursorz<levelz)
       mapt0[cursori+16384]=CurrentTile;
       break;       
      
  }


     }
    }
   
   break;//Tile Wrap
   case 3://Map Tagging
   if (controlpad.button[PAD_L2]) if (MapTag) MapTag--;
   if (controlpad.button[PAD_R2]) if (MapTag<MapTaginfo_num) MapTag++;
   if (controlpad.button[PAD_X]) 
    {
    cursori=cursorx+cursory*128+cursorz*16384;
    map[cursori]=MapTag;
    }    
   break;//Map Tagging

   case 4://Camera Spirit

   if (controlpad.button[PAD_Z]) 
    {
   if (controlpad.button[PAD_X])
    if ((cam0>0)&(cam0<128))
     {
     if (camera[0]<0) camera[0]=0;
     if (camera[1]<0) camera[1]=0;
     if (camera[2]<0) camera[2]=0;

     staticcam[cam0-1][0]=camera[0];                           
     staticcam[cam0-1][1]=camera[1];                           
     staticcam[cam0-1][2]=camera[2];                           
     staticcam[cam0-1][3]=camera[3];                           
     staticcam[cam0-1][4]=camera[4];                           
     staticcam[cam0-1][5]=camera[5];                           
     }


   if (controlpad.button[PAD_R2])
    if (staticcams<127) staticcams++;

   if (controlpad.button[PAD_L2])
    if (staticcams>0) staticcams--;
    }
    else// with no Z
    {
     if (controlpad.button[PAD_X])
     {
     cursori=cursorx+cursory*128+cursorz*16384;
     mapcam0[cursori]=cam0;                             
     mapcam1[cursori]=cam1;                             
     mapcam2[cursori]=cam2;                             
     mapcam3[cursori]=cam3;                             
                                  
     }           
     {
     if (cam0<128)
     {   
     if (controlpad.button[PAD_R2])
      if (cam0<staticcams) cam0++; else cam0=128;
     if (controlpad.button[PAD_L2])
     if (cam0>0) cam0--;
     }
     else
     {
     if (controlpad.button[PAD_R2])
      if (cam0<255)cam0++;
     if (controlpad.button[PAD_L2])
     if (cam0>128) cam0--;else cam0=staticcams;
     }
     }
    }

   break;//Camera Spirit
   case 5://Holy objects
   if (controlpad.button[PAD_R2]) 
   objcur++;
   if (controlpad.button[PAD_L2]) 
   objcur--;
   
   if (controlpad.button[PAD_Z])
   if (objcur<128) objcur=128; else 
   objcur=0; 

   
   if (controlpad.button[PAD_X]) 
    {
    cursori=cursorx+cursory*128+cursorz*16384;
    mapobj[cursori]=objcur;
    }    
   break;//Holy Objects
   case 6://Mind washing
   if (controlpad.button[PAD_R2]) 
   if (aiedit<12)
   aiedit++;
   if (controlpad.button[PAD_L2]) 
   if (aiedit)
   aiedit--;
   
  
   if (controlpad.button[PAD_X]) 
    {
    cursori=cursorx+cursory*128+cursorz*16384;
    mapai[cursori]=aiedit;
    }    
   break;//Mind washing

   case 7: //Unholy Scripts
if (controlpad.button[PAD_Z]) {inTrigEdit=1;editorcount=5;}
if (controlpad.button[PAD_R2]&controlpad.button[PAD_L2]) {inTrigEdit=1;editorcount=5;}



   break; //Unholy Scripts
   case 8: //So i memorized a words to a porno movie
   if ((controlpad.button[PAD_L2])&(controlpad.button[PAD_R2]))
   {
   layer_spec_mode=1;editorcount=5;
   }
   else
   {
    if (controlpad.button[PAD_Z]==0)
    {
    if (controlpad.button[PAD_X]) {MInsert_Node();editorcount=5;}


    if (controlpad.button[PAD_L2]) if (c_movie_step)c_movie_step--;           
    if (controlpad.button[PAD_R2]) if (c_movie_step<movie_length[curmovie])c_movie_step++;               
    }
   else
    {
    if (controlpad.button[PAD_X]) {MDelete_Node();editorcount=5;}
    if (controlpad.button[PAD_L2]) if (curlayer)curlayer--;           
    if (controlpad.button[PAD_R2]) if (curlayer<movie_num_layers[curmovie])curlayer++;               
    }
   }
   break;//So i memorized a words to a porno movie
}      
}      
 }            

     break;//EDITOR_LEVEL

case EDITOR_MENU:
//     if(Music_Fade_Count==0)
   {  if (controlpad.button[PAD_L2])
     if (volume)
      { volume--;volume_delay=20;}
     if (controlpad.button[PAD_R2])
      { volume++;if (volume>128) volume=128;volume_delay=20;}
   }

      if (count%2==0)
      switch (controlpad.angle)
      {
             case 0:if (menupos>0){menupos--;sPlaySound(0,96-menupos*4,32);}break;
             case 4:if (menupos<8){menupos++;sPlaySound(0,32,64+menupos*4);}break;
             
             case 2:
                  switch (menupos)
                  { 
                  case 0:if (CurrentLevel<49)CurrentLevel++;break;
                  case 4:Next_Music_Track++;if (Next_Music_Track>49)Next_Music_Track=49;break;
                  case 5:if (SoundPlayer<d_sound_count-1)SoundPlayer++;break;
                  };  break;
             case 6:
                  switch (menupos)
                  { 
                  case 0:if (CurrentLevel>0)CurrentLevel--;break;
                  case 4:if (Next_Music_Track>0)Next_Music_Track--;break;
                  case 5:if (SoundPlayer>0)SoundPlayer--;break;
                  };  break;
      };             

      if (controlpad.button[PAD_SELECT]) 
       {
       if (count%2)
       if (menupos==5)
        SoundMode=(SoundMode+1)%3;                                  
                                         
       }       




      if (controlpad.button[PAD_START]) menupos=8;        



      if (controlpad.button[PAD_X])        
      switch (menupos)
      {
            case 0:
            ClearLEditor();
            editorcount=0;fadecount=10;NewGameMode=EDITOR_LEVEL;LoadLevel(CurrentLevel);LoadedLevel=CurrentLevel;
            if (staticcams)
             {
             camera[0]=staticcam[0][0];              
             camera[1]=staticcam[0][1];              
             camera[2]=staticcam[0][2];              
             camera[3]=staticcam[0][3];              
             camera[4]=staticcam[0][4];              
             camera[5]=staticcam[0][5];              
             }
             //NextMusicTrack(levelmusictrack);
            break; 
            case 5:if (d_sound_count) sPlaySound(SoundPlayer,128,128);editorcount=5;break;
            case 8:GameLoopEnabled=0;break;
      };
      if (controlpad.button[PAD_B])        
      switch (menupos)
      {
            case 0:
            ClearLEditor();
            editorcount=0;NewGameMode=EDITOR_LEVEL;ClearLevel();LoadedLevel=CurrentLevel;
            break; 
            case 4:NextMusicTrack(Next_Music_Track);break; 
            case 5:if (d_sound_count) sPlaySound(SoundPlayer,0,128);editorcount=5;break;
            case 8:GameLoopEnabled=0;break;
      };
      
      if (controlpad.button[PAD_A])        
      switch (menupos)
      {
            case 0:editorcount=0;if (LoadedLevel>=0) {fadecount=10;NewGameMode=EDITOR_LEVEL;}break;//RETURN to Leditor 
            case 1:editorcount=0;fadecount=10;NewGameMode=EDITOR_MODEL;PrepareEModel(); break; 
            case 2:editorcount=0;fadecount=10;NewGameMode=EDITOR_TEXTURE;color=0;break; 
            case 3:editorcount=0;fadecount=10;NewGameMode=EDITOR_PALETTE;color=0;break; 
            case 4:NextMusicTrack(Next_Music_Track);break; 
            case 5:if (d_sound_count) sPlaySound(SoundPlayer,128,0);editorcount=5;break;
            case 6:editorcount=0;fadecount=10;NewGameMode=EDITOR_AI;break; 
            case 7:EditorOn=0;count=0;fadecount=10;NewGameMode=LOADING_GAME;break; 
            case 8:GameLoopEnabled=0;break;
      };
     
     break;//EDITOR_MENU       
     case EDITOR_MODEL:
     if (controlpad.button[PAD_START]) {LoadedLevel=-1;ClearLevel();editorcount=6;fadecount=10;NewGameMode=EDITOR_MENU;}
      switch (controlpad.angle)
      {
             case 0:modelv1-=16;break;
             case 2:modelv0+=24;break;
             case 4:modelv1+=16;break;
             case 6:modelv0-=24;break;
      }
      if (controlpad.button[PAD_A])
      {  if (modelvr>65535) modelvr-=10000;}
      else
      if (controlpad.button[PAD_B])
      if (modelvr<265535) modelvr+=10000;
      if (count%2)
      {
      if (controlpad.button[PAD_Z]) 
      {
      animationmode=(animationmode+1)%3;
      monster_frame0[0]=0;
      monster_frame1[0]=0;
      monster_anim[0]=4;      
      monster_animcount[0]=0;      
      }

switch (animationmode)
{
       case 0://frame
      if (controlpad.button[PAD_L1])
      {if (modelvi>0) modelvi--;ModelEditorModelSwitch();}
      else
      if (controlpad.button[PAD_R1])
      {if (modelvi<model_mms-1) modelvi++;ModelEditorModelSwitch();}
       
      
      
      if (controlpad.button[PAD_L2])
       { if (monster_frame0[0]>0) monster_frame0[0]--;}
       else
      if (controlpad.button[PAD_R2])
        if (monster_frame0[0]<model_ani[modelvi]-1) monster_frame0[0]++;
      monster_frame1[0]=monster_frame0[0];
       break;
       case 1://scale
       
       if(model_scalev==0)
       {
       if (controlpad.button[PAD_L1])
       {model_scalex[modelvi]-=1+model_scaledelay*4;model_scaledelay+=2;if (model_scalex[modelvi]<32768) model_scalex[modelvi]=32768;}
       else
       if (controlpad.button[PAD_R1])
       {model_scalex[modelvi]+=1+model_scaledelay*5;model_scaledelay+=2;if (model_scalex[modelvi]>98300) model_scalex[modelvi]=98300;}
       }
       else
       if(model_scalev==1)
       {
       if (controlpad.button[PAD_L1])
       {model_scaley[modelvi]-=1+model_scaledelay*4;model_scaledelay+=2;if (model_scaley[modelvi]<32768) model_scaley[modelvi]=32768;}
       else
       if (controlpad.button[PAD_R1])
       {model_scaley[modelvi]+=1+model_scaledelay*5;model_scaledelay+=2;if (model_scaley[modelvi]>98300) model_scaley[modelvi]=98300;}
       }
       else
       if(model_scalev==2)
       {
       if (controlpad.button[PAD_L1])
       {model_scalez[modelvi]-=1+model_scaledelay*4;model_scaledelay+=2;if (model_scalez[modelvi]<32768) model_scalez[modelvi]=32768;}
       else
       if (controlpad.button[PAD_R1])
       {model_scalez[modelvi]+=1+model_scaledelay*5;model_scaledelay+=2;if (model_scalez[modelvi]>98300) model_scalez[modelvi]=98300;}
       }
       else
       if(model_scalev==3)
        {
       if (controlpad.button[PAD_L1]) {if (model_scalei[modelvi]) model_scalei[modelvi]--;}
       else
       if (controlpad.button[PAD_R1]) {if (model_scalei[modelvi]<32) model_scalei[modelvi]++;}
                          
        }       
       if (model_scaledelay)
       if (model_scaledelay>100) model_scaledelay=100;
        else
       model_scaledelay--;
      if (count%2)
      {
      if (controlpad.button[PAD_L2]) {if (model_scalev>0) model_scalev--;else model_scalev=3;}
      else
      if (controlpad.button[PAD_R2]) {if (model_scalev<3) model_scalev++;else model_scalev=0;}
        if (controlpad.button[PAD_SELECT])
        {savemodelscale();editorcount=0;};
      }
       break;
       case 2://color
       if (controlpad.button[PAD_L2])
       {
       if (modelvi_tri>0) modelvi_tri--; else modelvi_tri=model_fs[modelvi]-1;}
       else
       if (controlpad.button[PAD_R2])
       {
       if (modelvi_tri<model_fs[modelvi]-1) modelvi_tri++; else modelvi_tri=0;}

      if (controlpad.button[PAD_L1])
      {if (model_vicol>16) model_vicol--;}
      else
      if (controlpad.button[PAD_R1])
      if (model_vicol<255)model_vicol++;
            
      if (controlpad.button[PAD_X])
        f_c[model_f0[modelvi]+modelvi_tri]=model_vicol;
        else
        if (controlpad.button[PAD_Y])
        model_vicol=f_c[model_f0[modelvi]+modelvi_tri];

        if (controlpad.button[PAD_SELECT])
        {SaveColorOverride();editorcount=0;};
        
       break;
       }//switch animationmode
      }
       
     break;//EDITOR_MODEL
     case EDITOR_PALETTE:
      if (controlpad.button[PAD_START]) {fadecount=10;NewGameMode=EDITOR_MENU;editorcount=6;}        
      else
      if (controlpad.button[PAD_SELECT]) 
      {
      SavePalette();
      NewGameMode=EDITOR_MENU;
      }        

      #ifdef GP2X
      if (controlpad.button[PAD_X])
      {
      colorbuf[0]=screen->format->palette->colors[color].r;
      colorbuf[1]=screen->format->palette->colors[color].g;
      colorbuf[2]=screen->format->palette->colors[color].b;
      }
      else
      if (controlpad.button[PAD_Y])
      {
      screen->format->palette->colors[color].r=colorbuf[0];
      screen->format->palette->colors[color].g=colorbuf[1];
      screen->format->palette->colors[color].b=colorbuf[2];
      SDL_SetColors(screen,screen->format->palette->colors,0,256);
      }
      if (controlpad.button[PAD_R1])
       {
      screen->format->palette->colors[color].r++;
      SDL_SetColors(screen,screen->format->palette->colors,0,256);
       }
        else
      if (controlpad.button[PAD_L1])
       {
      screen->format->palette->colors[color].r--;
      SDL_SetColors(screen,screen->format->palette->colors,0,256);
       }      

      if (controlpad.button[PAD_R2])
       {
      screen->format->palette->colors[color].g++;
      SDL_SetColors(screen,screen->format->palette->colors,0,256);
       }
        else
      if (controlpad.button[PAD_L2])
       {
      screen->format->palette->colors[color].g--;
      SDL_SetColors(screen,screen->format->palette->colors,0,256);
       }      
      if (controlpad.button[PAD_B])
       {
      screen->format->palette->colors[color].b++;
      SDL_SetColors(screen,screen->format->palette->colors,0,256);
       }
        else
      if (controlpad.button[PAD_A])
       {
      screen->format->palette->colors[color].b--;
      SDL_SetColors(screen,screen->format->palette->colors,0,256);
       }      
      #endif

      #ifdef PC
      if (controlpad.button[PAD_X])
      {
      colorbuf[0]=ipal[color][0];
      colorbuf[1]=ipal[color][1];
      colorbuf[2]=ipal[color][2];
      }
      else
      if (controlpad.button[PAD_Y])
      {
      ipal[color][0]=colorbuf[0];
      ipal[color][1]=colorbuf[1];
      ipal[color][2]=colorbuf[2];
      }
      if (controlpad.button[PAD_R1])
       {
      ipal[color][0]++;
       }
        else
      if (controlpad.button[PAD_L1])
       {
      ipal[color][0]--;
       }      

      if (controlpad.button[PAD_R2])
       {
      ipal[color][1]++;
       }
        else
      if (controlpad.button[PAD_L2])
       {
      ipal[color][1]--;
       }      
      if (controlpad.button[PAD_B])
       {
      ipal[color][2]++;
       }
        else
      if (controlpad.button[PAD_A])
       {
      ipal[color][2]--;
       }      
      #endif

      switch (controlpad.angle)
      {
             case 0:color-=16;break;
             case 2:color++;break;
             case 4:color+=16;break;
             case 6:color--;break;
      }    
       break;//EDITOR_PALETTE
case EDITOR_TEXTURE:
{
      if (controlpad.button[PAD_START]) {editorcount=6;fadecount=10;NewGameMode=EDITOR_MENU;}
      if (controlpad.button[PAD_L1])
      {
      if (controlpad.button[PAD_SELECT]) {savetiledata();editorcount=5;}
                                    
      switch (controlpad.angle)
             {
             case 0:if (tiledatcur>0)tiledatcur--;break;             case 4:if (tiledatcur<5)tiledatcur++;break;
             case 2://right arrow
                   {
             switch (tiledatcur)
             {
             case 0:tiledata_alpha[CurrentTile]=1;break;
             case 1:tiledata_animated[CurrentTile]=1;break;
             case 2:tiledata_block[CurrentTile]=1;break;
             case 3:tiledata_breakable[CurrentTile]=1;break;
             case 4:tiledata_finalbreak[CurrentTile]=1;break;
             case 5:if (tiledata_sound[CurrentTile]<7)tiledata_sound[CurrentTile]++;break;
             }                 
                   }break;
             case 6://left arrow
                   {
             switch (tiledatcur)
             {
             case 0:tiledata_alpha[CurrentTile]=0;break;
             case 1:tiledata_animated[CurrentTile]=0;break;
             case 2:tiledata_block[CurrentTile]=0;break;
             case 3:tiledata_breakable[CurrentTile]=0;break;
             case 4:tiledata_finalbreak[CurrentTile]=0;break;
             case 5:if (tiledata_sound[CurrentTile]>0)tiledata_sound[CurrentTile]--;break;
             }                 
                   }break;
             
             }                                    
      }
      else
      {
      if (controlpad.button[PAD_L2]) TileSelector=1;

      if (controlpad.button[PAD_R2]) grid=(grid+1)%5;
      
      if (controlpad.button[PAD_A])
      tileedit[ex][ey]=color;
      if (controlpad.button[PAD_Y])
      color=tileedit[ex][ey];
      
      if (controlpad.button[PAD_R1])
      {
      switch (controlpad.angle)
      {
             case 0:color-=16;break;
             case 2:color++;break;
             case 4:color+=16;break;
             case 6:color--;break;
             }    
                                    }
      else 
      switch (controlpad.angle)
      {
             case 0:if (ey==0) ey=15; else ey--;break;
             case 2:ex=(ex+1)%16;break;
             case 4:ey=(ey+1)%16;break;
             case 6:if (ex==0) ex=15; else ex--;break;
             }
      }          
}      
       break;//EDITOR_TEXTURE
case EDITOR_AI:
     if (controlpad.button[PAD_START]) {editorcount=6;fadecount=10;NewGameMode=EDITOR_MENU;}
     if (controlpad.button[PAD_SELECT]) {editorcount=5;SaveAI();}
     if (count%2==0)
      {
     if (controlpad.button[PAD_L1]) if (e_monsteri>0) e_monsteri--;             
     if (controlpad.button[PAD_R1]) if (e_monsteri<31) e_monsteri++;                 

      switch (controlpad.angle)
             {
             case 0:if (e_aiy>0) e_aiy--; break;
             case 2:if (e_aix<4) e_aix++; break;
             case 4:if (e_aiy<7) e_aiy++; break;
             case 6:if (e_aix>0) e_aix--; break;
             }
             
     if (controlpad.button[PAD_L2]) if (t_monster_ai[e_monsteri][e_aix][e_aiy]>0) t_monster_ai[e_monsteri][e_aix][e_aiy]--;             
     if (controlpad.button[PAD_R2]) if (t_monster_ai[e_monsteri][e_aix][e_aiy]<99) t_monster_ai[e_monsteri][e_aix][e_aiy]++;             
              
      }
     break;//EDITOR_AI

};
}
}
