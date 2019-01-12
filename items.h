#include <types.h>
extern Sint16 weapon_points[12];

extern const char item_s[128][32];

extern void ProcLoot(void);

extern void LoseGold(Sint32 i);
extern void LoseItem(unsigned short int i);
extern void UseItem(unsigned short int i);
extern void AddItem(unsigned short int i,unsigned short int i);
extern void DropItem(Uint8 index,Uint8 x,Uint8 y,Uint8 z,Uint8 owner,Uint8 many);

extern void WearItem(Uint8 i,Uint8 puton);
