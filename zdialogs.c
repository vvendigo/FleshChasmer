#include <zdialogs.h>
#include <interface.h>
#include <sfont.h>
#include <sound.h>
#include <globalvar.h>

Uint8 messageindex,dialogindex;
/*
01234567890123456789012345678901
*/
Uint8 editor_dialognum=92;
Uint8 keypressed;

Uint8 port[76800];
const char zdialogs[184][48]=
{
"Damn!!",
"There are comes more of them!",
"What have just happend?!!",
"I'm feel so really bad!",
"My stomach!!!",
"Something moving inside my guts!",
"Arghhhh!!!",
"My throat is burning...",
"We are the...",
"... we are the HUNTRESS!..",
"Time to you to die, witch!",
"Come to wherether you came from!",
"Oh! Where that monster?",
"I won't let her live that easily!",
"Huh? Another Spiritual attack?",
"Anyway this forest is not real!",
"Whoether do this did this",
"to stop me...",
"Who are there?!!",
"Name yourself, witch!",
"You know I wasn't asking for memo to",
"be written on your tombstone...heh?",
"Mortal, you was disturbing our",
"progress for a quite long time...",
"This is a time to end our sorrow.",
"Your heart is on fire, but not mind.",
"Keep this for your diary, whore!",
"I gonna put the end to all of you!",

"Get away from him, you pesty spider!",
"",
"...<moans>...",
"... Halobane, it is realy you?..",
"Year, me. I thought you were dead.",
"You look ugly.",
"Are the things really are so bad?",
"",
"Even more ugly than a ratman",
"that squashed by a tank!",
"I have no time for plastic surgery",
"I need to get proper healing fast...",
"You realy can walk?",
"I know no cure nor spell nor item.",
"We will reach the summoning",
"chamber... <cough> ...",
"Ok. I'll try keep monsters at",
"some distance from you.",
"Only chance to get that thing",
"out from me is there...",
"I will summon 'Code88'",
"He is why we all came here.",
"Blessing of cleasing are",
"his prime ability...",
"How we will communicate with",
"this fabled God Of Genocide?",
"I will be ...a host for his",
"spirit...",
"Summoning chamber just behind",
"this corner...",

"...By meditation I usually",//60
"refer to the combat training...",

"I feel the power of this place!",
"... it should be summoning hall!",
"Just will it work or not?",
"I do not believe in that stuff...",
"Here I go!",
"The ocean of flame take mine...",
"Take my flesh...",
"",
"It smells more nasty when cooked...",
"... but I will not eat you...",
"...",
"... he is inside of me...",
"Ahh. This pityfully world again",
"I feel the presence of my enemy",
"...",
"",
"Leave me alone, mortal one!",
"I need time to ... to meditate...",
"As you wish...",
"Take this knife and pistol.",
"I will not dishonour...",//82
"... you as the God Of Genocide!",

"You are alive? I killed you both...",
"You and her! This cannot be!!",
"The truth is you cannot really",
"kill a living creature...",
"You mean I hopeless?",
"I was stupid to bother you...",
"I'm here to finish what",
"you were unable to complete",
"Let's then go!",
"I'll slice this veins to the ground!",
"This is a vein of her sister",
"These witches are both here",
"This path leads to the surface",
"Do not wait for me, farewell!",
"Welcome to the Gobin Trader",//50
"Wares for your war, customer!",

"Yebat v rot moyu mamochku!",//51
"Pizda hana tvoei parashe!",
"Ha-Ha-Ha! You won't get me!",//52
"You stupid russian pigs!",
"Stoi, HueVaffleSos!",//53
"Huyeplet pizda nam vsem",
"Cho esho zo afftor? Nizachot!..",//54
"Telogreika tebe!",
"Hi there! My name is Vurlach",//55
"I'm the Wall Guardian here",
"As I see many walls",//56
"Which one you guarding?",
"Ahh... <giggle>",//57
"The one around this enclave",
"Without nuclear weapons and",//58
"aircraft they are so pathetic",
"There many of them in next cave!",//59
"I hate to have my hands dirty...",
"Take this invisiblity potion",//60
"Then reach my truck outside!",
"Ok. Time to leave this place",//61
"",

"Stop your transport unit here",//62
"It is where I get off",
"I entrust command to you",//63
"As would Tsis Auq do that",
"Besides, what you forgot here?",//64
"Tolkien fans are owe this land!",
"Did you hear about relic",//65
"they worship in their temple?",
"You mean 'Phallos of Elbereth'?",//66
"I do not know so much...",
"It is a great rocket launcher",//67
"I will venture in to obtain it",
"Wait! Take this machine gun!",//68
"It will aid thine quest!",
"This gate requires a key...",//69
"...where could be a one???",
"Hey you! In the name of Elbereth!",//70
"Give us all of your rupees NOW!",
"Yahh! The Lord Of Rockets!",//71
"For virtue ... Come to my hands",
"Taste my lust of genocide!",//72
"Your sister comes next!",

"Ei! Muzjiki! A ya toka chto",//73
"podrachil na fotku prezidenta!",
"Ya konchil emu mezdu glaz!",//74
"Jalko chto chibi-Putin 2 podoh :(",
"<radio>Good Luck! They have big",//75
"amounts of zombie lurking at streets!",
"<radio>SaintTeeth is currently ",//76
"near red square. There many of them!",
"<radio>They moving to your position",//77
"Be careful!",
"I shold really care more...",//78
"...care them to die!",
"<radio> Attention! Hurry up!",//79
"I see many tanks entering the city!",
"<radio> I see her lair from here!",//80
"I will be scouting the sector around!",

"<radio> ...I repeat massive zombie",//81
"movement detected...",
"Ahhh!..",//82
"It... cannot be... WHY?",
"I'm on my path to place where",//83
"you will never get me, whores!",
"You are too content for a eaten man",//84
"...I sense the parasite in you",
"... I ... I just cannot take it",//85
"... anymore...",
"... I ... want evrything",//86
"... to disseapear!..",
"I came to you, bitch!",//87
"Now I will come on you!",
"Your existance is doomed",//88
"I will release myself!!!",
"Now I can go back...",//89
"",
"What the hell just happend???",//90
"",
"It is last time I buying loot",//91
"from you, ugly creature!",
"Shit... game engine prohibites me",//92
"from raising prices...",

};
const Uint8 zdialoga[92]=
{
3,
3,
3,
3,
10,
3,
3,
3,
3,
3,
3,
10,
10,
3,

8,
3,
8,
3,
8,
3,
8,
3,
8,
3,
3,
3,
8,
3,
3,

0,

3,8,3,3,8,3,0,8,0,8,8,

13,0,13,0,13,0,13,

12,18,1,18,18,1,0,1,1,1,1,13,

0,1,1,0,1,0,1,0,19,

0,0,

18,18,1,13,13,0,1,13,


13,13,13,0,8,8,0,0,0,3,0,12
};
const Uint8 zdialogp[92]=
{
0,
0,
0,
0,
1,
0,
0,
0,
0,
0,
0,
1,
1,
0,


2,
1,
2,
1,
2,
1,
2,
1,
2,
1,
1,
1,
2,
1,
1,

4,

1,2,1,1,2,1,4,2,4,2,2,

3,4,3,4,3,4,3,

6,7,5,7,7,5,4,5,5,5,5,3,

4,5,5,4,5,4,5,4,8,

4,4,

7,7,5,3,3,4,5,3,

3,3,3,4,2,2,4,4,4,0,4,6
};

void BeginDialog(Uint8 index)
{
dialogcount=1;
dialogindex=index;
keypressed=1;
}


//MESSSSAAAAGGGEESSSS
/*
01234567890123456789012345678901
*/
Uint8 editor_messagenum=24;
const char zmessages[24][64]=
{
"To be concluded",
"Use stick to control character!",
"Use Action Keys to shoot at enemy! They come!",
"You feel yourself ill! Use Medikit to heal wounds.",
"Hold LEFT SHOULDER Button to show quick item panel.",
"Belial Shrine Catacombs",

"Halls Of Summoning",
"Small Cave",
"Entering Upper Catacomb",
"Upper Catacombs",
"Leaving Catacoms",
"Underground Fortress",
"Serpent Cave System",
"You now can SELECT to enter Character's menu.",
"Infested Dungeon",
"The Dream",
"Elven Temple Forest",
"Ruined Elven Temple",

"Entering the City of Infidels",
"The Razed Moscow",
"Aproaching Kremlin",
"Kremlin Citadel Gates",
"Motherland Lair",
"You found famous RED SQUARE!",

};

void BeginMessage(Uint8 index)
{
messagecount=1;
messageindex=index;     
}
void RenderDialog(void)
{
if (dialogcount==1) sPlaySound(37,70,70);

dialogcount++;     

Uint32 x,y;
//if (movie_mode!=1)
//{
for (x=20;x<250;x++)     
for (y=158;y<197;y++)
scrbuf[x+y*320]=16;

for (x=22;x<61;x++)     
for (y=137;y<200;y++)
scrbuf[x+y*320]=17;


Sint32 dp=(zdialogp[dialogindex]%10)*32+(zdialogp[dialogindex]/10)*48;
for (x=0;x<32;x++)     
for (y=0;y<48;y++)
{
scrbuf[25+140*320+x+y*320]=port[dp+x+y*320];
}


l_textstring=sprintf(s_textstring,"%s",t_monster_name[zdialoga[dialogindex]]);
s_drawtext(66,160,22);
s_drawtext(65,160,92);


Uint8 l;
if (dialogcount>8)
if (dialogcount<56)
{
l_textstring=sprintf(s_textstring,"%s",zdialogs[dialogindex*2]);
l=l_textstring;
l_textstring=dialogcount-8;
if (l_textstring>l) 
{l_textstring=l;dialogcount=55;}
s_drawtext(66,172,19);
s_drawtext(65,171,29);
}
else
if (dialogcount<104)
{
l_textstring=sprintf(s_textstring,"%s",zdialogs[dialogindex*2]);
s_drawtext(66,172,19);
s_drawtext(65,171,29);

l_textstring=sprintf(s_textstring,"%s",zdialogs[dialogindex*2+1]);
l=l_textstring;
l_textstring=dialogcount-56;
if (l_textstring>l) {l_textstring=l;dialogcount=103;}
s_drawtext(66,184,19);
s_drawtext(65,183,29);
}
else
if (dialogcount<160)
 {
l_textstring=sprintf(s_textstring,"%s",zdialogs[dialogindex*2]);
s_drawtext(66,172,19);
s_drawtext(65,171,29);
l_textstring=sprintf(s_textstring,"%s",zdialogs[dialogindex*2+1]);
s_drawtext(66,184,19);
s_drawtext(65,183,29);
 }
 else
dialogcount=0;

if (dialogcount>4 & dialogcount<104)
{if (count%4==0) sPlaySound(36,50+dialogcount/2,50+dialogcount/2);}


if (movie_mode==1)
{
if (controlpad.button[PAD_B]|controlpad.button[PAD_A]|controlpad.button[PAD_X]|controlpad.button[PAD_Y])
{
if (keypressed==0)                             
{
 if (dialogcount)
 if (dialogcount<104) 
 {
 dialogcount=104;
sPlaySound(37,120,120);
 }
 else
 if (dialogcount<155)
  dialogcount=155;
}
keypressed=1;
}
else
keypressed=0;
}
}

void RenderMessage(void)
{
Uint8 c;

if (messagecount<10) c=16+messagecount;
else
if (messagecount<45) c=28;
else
c=28-(messagecount-45);

l_textstring=sprintf(s_textstring,"%s",zmessages[messageindex]);
s_drawtext2(160-l_textstring*5,100,16);
s_drawtext2(160-l_textstring*5,98,16);
s_drawtext2(161-l_textstring*5,99,16);
s_drawtext2(159-l_textstring*5,99,16);
s_drawtext2(160-l_textstring*5,99,c);

     
messagecount++;
if (messagecount==56) messagecount=0;
}

void TextMessage(Uint8 index)
{
sprintf(new_message,"%s",zmessages[index]);
NewMessage();
}

void LoadPortraits(void)
{
Sint32 i;
FILE *fp;
fp=fopen("data/portrait.dat","rb");
if (fp)
 {
 for (i=0;i<76800;i++) port[i]=fgetc(fp);
 fclose(fp);       
 }
     
     
}
