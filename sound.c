#include "sound.h"
#include "SDL_Mixer.h"
#include "globalvar.h"
#include "GPU.h"
#include "zmath.h"
Uint8 s_channel=1;Uint8 lastmusicvolume;


//Uint8 sound_cashe_i[4];
//Sint32 sound_cashe_count[4];

void sPlaySound(unsigned int index,unsigned short int left,unsigned short int right)
{
        Uint8 t=right;

//for (Uint8 i=1;i<4;i++)
//if ((index!=sound_cashe_i[i])|((count!=sound_cashe_count[i])))
//{
s_channel++;
if (s_channel==3) s_channel=1;    

switch (SoundMode)
 {
 case 0://NORMAL
        break;      
 case 1://REVERSED
        right=left;
        left=t; 
        break;       
 case 2://MONO
        if (left>right) right=left;else left=right;
        break;       
 }

//sound_cashe_i[s_channel]=index;
//sound_cashe_count[s_channel]=count;
Mix_PlayChannel(s_channel,d_sound[index],0);
#ifdef GP2X
Mix_SetPanning(s_channel,right,left);
#endif
#ifdef WIN32
Mix_SetPanning(s_channel,left,right);
#endif
//}

}
void sPlaySound3D(Sint32 sx,Sint32 sy,Sint32 sz,Uint8 i_sound,Sint32 i_range)
{
Sint32 px,pz,vv;     
Sint32 v0,v1;     
zlpoint(sx,sy,sz);
px=-160+2*vbufferx[zlvertex];
pz=fastrange(rcamera[2]-sz,rcamera[0]-sx);


if (pz>0)
if ((px>-300)&(px<300))
if ((pz<i_range))
 {
if (pz>i_range) 
{
v0=0;v1=0;
}
else
  {
  v0=128;
  v1=128;

  if (px<-20) v1+=(px+20)>>1;
  else
  if (px>20) v0-=(px-20)>>1;


  vv=(64*pz/i_range);
  if (vv>0) {v0-=vv;v1-=vv;}
  }

if (v0<48) v0=0;
if (v1<48) v1=0;
sPlaySound(i_sound,v0,v1);     

 }
else
{
v0=0;
v1=0;
}


}
char trackpath[128];
void OpenMusicTrack(unsigned short int track)
{
Mix_HaltChannel(0);
if (track<50)
{
if (music_loaded[track]==0)
{
music[track] = NULL;
sprintf(trackpath,"data/Track%i%i.wav",track/10,track%10);
music[track] = Mix_LoadWAV(trackpath);
music_loaded[track]=1;                      
}
Mix_PlayChannel(0,music[track],256);
}
}

void SetMusic(unsigned short int track)
{
OpenMusicTrack(track);   
Music_Volume=70;
Music_Fade_Count=0;
Sint16 vol=(Music_Volume*volume)/128;
Mix_Volume(0,vol);               
Next_Music_Track=track;
};
void NextMusicTrack(unsigned short int track)
{
     
if (Music_Track!=track)
 {
                       
Next_Music_Track=track;
Music_Fade_Count=50;
 }
}

void ProcSound(void)
{

if (Music_Fade_Count)
  {
                     
  if (Music_Fade_Count==25)

  {
                           
       OpenMusicTrack(Next_Music_Track);
       Music_Track=Next_Music_Track;
   trackname_delay=30;
  };
  Uint32 vol;                    
  Music_Fade_Count--;
                     
  if (Music_Fade_Count>25) vol=(Music_Fade_Count-25)*4;
  else
  vol=100-Music_Fade_Count*4;
  vol=(vol*volume)/128;
  vol=(vol*Music_Volume)/100;
  Music_Volume_Mix=vol;
  Mix_Volume(0,vol);
  lastmusicvolume=Music_Volume;               
  }
  else
  {
  if (lastmusicvolume!=Music_Volume)
   {
    Music_Fade_Count=1;                                
   }    
  lastmusicvolume=Music_Volume;               
  }
}
