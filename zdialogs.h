#include <types.h>
extern const char zdialogs[184][48];
extern const char zmessages[24][64];

extern Uint16 dialogcount,messagecount;
extern Uint8 editor_dialognum,editor_messagenum;

extern void BeginDialog(Uint8 index);
extern void BeginMessage(Uint8 index);
extern void RenderMessage(void);
extern void RenderDialog(void);
extern void TextMessage(Uint8 index);
extern void LoadPortraits(void);
