void InitMonsterTable(void);
void spawnmonster(unsigned short int x,unsigned short int y,unsigned short int z,unsigned short int index);


void monster_newpain(unsigned short int i);
void monster_newmelee(unsigned short int i);
void monster_newwarmode(unsigned short int i);

void monster_attack(unsigned short int i);
#include <types.h>
extern void monster_kill(Uint8 i);
extern void monster_shoot(Uint8 i);
extern void monster_move(Uint8 i,Uint8 x,Uint8 y,Uint8 z);
extern void monster_step(Uint8 i,Sint32 angle,Sint32 speed);

extern void Monster_Cast(Uint8 i,Uint8 target);
