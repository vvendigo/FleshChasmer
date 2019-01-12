#include <video.h>
#include <fields.h>
#include <zdialogs.h>
#include <game.h>

#include <camera.h>
#include <zmath.h>
#include <interface.h>
#include <player.h>
#include <triggers.h>
#include <sound.h>
#include <globalvar.h>
//global
Uint8 movie_num_layers[16],movie_layer_nodes[16][8],movie_control_nodes[16],movie_type[16];
Uint16 movie_length[16];
Sint32 movie_node[16][64][8][6];//[64 node per movie][layer][coords]
Uint8 movie_control_node[16][128][3];//128 per movie:layer-index,command,param
Uint16 movie_node_pos[16][64][8],movie_control_node_pos[16][128];


//current (for Render)
Sint32 c_movie_layer[8][6];
Uint32 c_movie_object[8][3];//model/frame/animated
Uint16 c_movie_step,c_movie_lstep;
Uint8 movie_playing=16;

void MovieStep(void)
{
Uint8 mp=movie_playing,c;
if (movie_playing<16)
 {
 if (movie_type[mp]==0) screenborder=40; else screenborder=0;
//Controls
if (c_movie_step!=c_movie_lstep)
if (movie_control_nodes[mp])
for (Uint16 i=0;i<movie_control_nodes[mp];i++)
if (movie_control_node_pos[mp][i]==c_movie_step)
{
Uint8 v[3];
v[0]=movie_control_node[mp][i][0];
v[1]=movie_control_node[mp][i][1];
v[2]=movie_control_node[mp][i][2];
switch (v[0])
{
case 1:c_movie_object[v[1]][0]=v[2];break;//set model
case 2:c_movie_object[v[1]][1]=v[2];break;//set frame
case 3:c_movie_object[v[1]][2]=v[2];break;//set anim

case 4:NextMusicTrack(v[1]);Music_Fade_Count=25;break;     
case 5:sPlaySound(v[1],128,128);break;//Sound
case 6:
     if (GameMode==GAME)
     NextLevel();
     break;//EndLevel
case 7:trig_status[v[1]]=1;break;//Trigger
case 8:BeginDialog(v[1]);break;//Dialog
case 9:
SpawnField0(
c_movie_layer[v[1]][0],
c_movie_layer[v[1]][2],
c_movie_layer[v[1]][1]+15000,v[2]);
break;//Not a Dialog
case 10://rename
if (GameMode==GAME)PlayerReName();
break;
}
}

//Layerc
 for (Uint8 l=0;l<8;l++)
  if (movie_layer_nodes[mp][l])
  {
   c=0;
   
if (movie_layer_nodes[mp][l])
{
while
(
(movie_node_pos[mp][c][l]<c_movie_step)
&
(c<movie_layer_nodes[mp][l])
)
 {c++;}
}
   
   if (c==0)
   {
   c_movie_layer[l][0]=movie_node[mp][c][l][0];         
   c_movie_layer[l][1]=movie_node[mp][c][l][1];         
   c_movie_layer[l][2]=movie_node[mp][c][l][2];         
   c_movie_layer[l][3]=movie_node[mp][c][l][3];         
   c_movie_layer[l][4]=movie_node[mp][c][l][4];         
   c_movie_layer[l][5]=movie_node[mp][c][l][5];         
   }
    else
    if(c==movie_layer_nodes[mp][l])
    {
   c_movie_layer[l][0]=movie_node[mp][c-1][l][0];         
   c_movie_layer[l][1]=movie_node[mp][c-1][l][1];         
   c_movie_layer[l][2]=movie_node[mp][c-1][l][2];         
   c_movie_layer[l][3]=movie_node[mp][c-1][l][3];         
   c_movie_layer[l][4]=movie_node[mp][c-1][l][4];         
   c_movie_layer[l][5]=movie_node[mp][c-1][l][5];         
    }         
    else
    {
    Sint32 s=movie_node_pos[mp][c][l]-movie_node_pos[mp][c-1][l];
    Sint32 s0=(c_movie_step-movie_node_pos[mp][c-1][l]);
    
//    debugval0=s0;
//    debugval1=s;
   for (Uint8 i=0;i<3;i++)
   c_movie_layer[l][i]=movie_node[mp][c-1][l][i]+s0*(movie_node[mp][c][l][i]-movie_node[mp][c-1][l][i])/s;
   for (Uint8 i=3;i<6;i++)
   c_movie_layer[l][i]=SuperAngle(movie_node[mp][c-1][l][i]+s0*calcturn(movie_node[mp][c-1][l][i],movie_node[mp][c][l][i])/s);
        
    }
  }
 }    
  if (movie_layer_nodes[mp][0])
  {
  camera[0]=c_movie_layer[0][0];                  
  camera[1]=c_movie_layer[0][1];
  camera[2]=c_movie_layer[0][2];
  camera[3]=c_movie_layer[0][3];
  camera[4]=c_movie_layer[0][4];
  camera[5]=c_movie_layer[0][5];
  camsync();
  }
  
c_movie_lstep=c_movie_step;
}

void ProcMovie(void)
{
if (movie_playing<16)
 {
 
 if (movie_type[movie_playing]==1 | dialogcount==0)
 {
 MovieStep(); 
 c_movie_step++;
 }
 if (c_movie_step>movie_length[movie_playing]) 
  {
  camset(monster_x[0]/65536,monster_y[0]/65536,monster_z[0]/65536);
  camsync();movie_mode=0;
  movie_playing=16;
  lastcamdelay=0;
  }
 }
}

void ClearMovie(void)
{
for (Uint8 i=0;i<16;i++)
 {
 movie_length[i]=0;          
 movie_num_layers[i]=0;          
 movie_control_nodes[i]=0;          

for (Uint8 n=0;n<16;n++)
 movie_layer_nodes[i][n]=0;          
 
 }    
     
}

void PlayMovie(Uint8 i)
{
if (i<16)
if (movie_length[i])
  {
   c_movie_object[1][0]=0;
   c_movie_object[2][0]=0;
   c_movie_object[3][0]=0;
   c_movie_object[4][0]=0;
   c_movie_object[5][0]=0;
   c_movie_object[6][0]=0;
   c_movie_object[7][0]=0;

   c_movie_object[1][1]=0;
   c_movie_object[2][1]=0;
   c_movie_object[3][1]=0;
   c_movie_object[4][1]=0;
   c_movie_object[5][1]=0;
   c_movie_object[6][1]=0;
   c_movie_object[7][1]=0;
   c_movie_object[1][2]=0;
   c_movie_object[2][2]=0;
   c_movie_object[3][2]=0;
   c_movie_object[4][2]=0;
   c_movie_object[5][2]=0;
   c_movie_object[6][2]=0;
   c_movie_object[7][2]=0;
   dialogcount=0;
   c_movie_step=0;c_movie_lstep=1;
   movie_playing=i;    
  lastcamdelay=0;
 if (movie_type[movie_playing]==1)
  ClearIndicators();
  }
  
}
