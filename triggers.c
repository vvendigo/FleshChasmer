#include <triggers.h>
#include <globalvar.h>
#include <video.h>
#include <camera.h>
#include <items.h>
#include <skills.h>
#include <player.h>
#include <interface.h>
#include <zdialogs.h>
#include <monsters.h>
#include <fields.h>
#include <sound.h>
#include <RPG.h>

Uint8 trig_status[16];
Uint8 trig_c[16];
Uint8 trig_x[16];
Uint8 trig_y[16];
Uint8 trig_z[16];


void ResetTriggers(void)
{
for (Uint8 i=0;i<16;i++)
 {
 trig_status[i]=0;
 trig_c[i]=0;
 }     
}

void ProcTriggers(void)
{
Uint8 m=map[monster_roomi[0]],val0,val1;
Sint32 itrig;
if ((m>=5)and(m<20))
if  (trig_status[m-4]==0)
{
trig_status[m-4]=1;
trig_c[m-4]=0;
trig_x[m-4]=monster_cx[0];
trig_y[m-4]=monster_cy[0];
trig_z[m-4]=monster_cz[0];

map[monster_roomi[0]]=0;

//sprintf(new_message,"Trigger %i activated",m-4);
//NewMessage();

}

for (Uint8 i=0;i<16;i++)
if (trig_status[i])
{
if (trig_status[i]>1)
  trig_status[i]--;
  else
 {
  //proc trigger           
  Uint16 c=i*32+trig_c[i]*2;
  val0=255;
  
  while ((trig_c[i]<16)&(val0))
  {
  val0=trig[c];
  val1=trig[c+1];
if (val0)
{
//sprintf(new_message,"%i %i",val0,val1);
//NewMessage();
}  
  switch (val0)
   {
   case 1: NextMusicTrack(val1);break;      
   case 2: sPlaySound(val1,128,128);break;      
   case 3: AddSkill(val1);break;      
   case 4: 
        if (val1<59)
        AddItem(val1,1);
        else
        AddItem(val1,30);
        break;      
   case 5: trig[i*32]=0;break;      
   case 6: monster_hurt(0,val1,0,16);break;      
   case 7: monster_hurt(0,val1*10,0,16);break;      
   case 8: monster_hurt(0,val1*50,0,16);break;      

   case 9: 
          for (Uint8 k=1;k<16;k++)
           if (monster_ingame[k])
           if (monster_side[k]!=monster_side[0])
           monster_kill(k);
          break;      
   case 10:
          for (Uint8 k=1;k<16;k++)
           if (monster_ingame[k])
           monster_kill(k);
          break;      
   case 11: levelmusictrack=val1;break;      
   case 12: levelwarmusictrack=val1;break;      
   case 13: PlayMovie(val1);break; //All Porn Starts Here
   case 14: trig_status[val1]=1;break;      
   case 15: spawnmonster(trig_x[i],trig_y[i],trig_z[i],val1);break;      

   case 16: trig_x[i]=val1;break;      
   case 17: trig_y[i]=val1;break;      
   case 18: trig_z[i]=val1;break;      
   case 19: break;      
   case 20: trig_status[i]=val1+1;break;      
   case 21: DropItem(val1,trig_x[i],trig_y[i],trig_z[i],16,1);break;      
   case 22: SummonField(val1,trig_x[i],trig_y[i],trig_z[i]);break;      
   case 23: SummonFieldOn(val1,0,16);break;      
   
   case 24: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;mapt0[itrig]=val1; break;      
   case 25: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;mapt1[itrig]=val1; break;      
   case 26: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;mapt2[itrig]=val1; break;      
   case 27: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;mapt3[itrig]=val1; break;      
   case 28: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;mapt4[itrig]=val1; break;      
   case 29: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;mapt5[itrig]=val1; break;      
   case 30: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;mapcam0[itrig]=val1; break;      
   case 31: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;map[itrig]=val1; break;      

   case 32: break;//mesh displace
   case 33: break;//same y      
   case 34: break;//same z      
   case 35: BeginDialog(val1);break;//dialog
   case 36: BeginMessage(val1);break;//message
   case 37: TextMessage(val1);break;//message
   case 38://All gets a piece of cake
          for (Uint8 k=1;k<16;k++)
          monster_hurt(k,10*val1,0,16);
          break;      
   case 39: fogcolor=val1;break;
   case 40: 
  monster_move(0,trig_x[i],trig_y[i],trig_z[i]);
  //movie_mode=0;
        break;
   case 41: levelsight=val1;break;
   case 43: itrig=trig_x[i]+trig_y[i]*128+trig_z[i]*16384;mapobj[itrig]=val1; break;      

   case 44: maxmonsters=val1; break;      
   case 45: 
   dialogcount=0;messagecount=0;
   ResetTriggers();NextLevel();return;
   break;      
   case 46:
   levelmusictrack=val1;
   levelwarmusictrack=val1;
   NextMusicTrack(val1);
   Music_Fade_Count=25;
   break;
   case 47:deathtrigger=val1;
   break; 
   }
   c+=2;
   trig_c[i]++;
  }
  if (trig_c[i]==16) {trig_c[i]=0;trig_status[i]=0;}
  //proc trigger         
 }     
}
}
