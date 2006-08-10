#define xstr(s) str(s)
#define str(s) #s

#define EG_VERSION_MAIN 2
#define EG_VERSION_SUB  00
#define EG_VERSION_REV  5

#define EG_VERSION_STRING "ExtGraph v" xstr(EG_VERSION_MAIN) "." xstr(EG_VERSION_SUB)"ß" xstr(EG_VERSION_REV)
#define EG_VERSION_STRING_POWERED "powered by " EG_VERSION_STRING

enum Attrs {A_REVERSE,A_NORMAL,A_XOR,A_SHADED,A_REPLACE,A_OR,A_AND,A_THICK1,
            A_SHADE_V,A_SHADE_H,A_SHADE_NS,A_SHADE_PS};

enum FillAttrs  {RECT_EMPTY=0,RECT_FILLED=1};
enum GrayPlanes {LIGHT_PLANE=0,DARK_PLANE=1};
enum GrayColors {COLOR_WHITE=0,COLOR_LIGHTGRAY=1,COLOR_DARKGRAY=2,COLOR_BLACK=3};
enum ExtAttrs   {A_CENTERED=0x40,A_SHADOWED=0x80};

typedef union {
    struct {
        unsigned char x0,y0,x1,y1;
    } xy;
    unsigned long l;
} SCR_RECT;


typedef struct {
    short x0,y0,x1,y1;
} WIN_RECT;


extern void FastDrawLine(void* plane,short x1,short y1,short x2,short y2,short mode) __attribute__((__stkparm__));
extern void FastDrawLine_R(void* plane asm("%a0"),short x1 asm("%d0"), short y1 asm("%d1"), short x2 asm("%d2"), short y2 asm("%d3"),short mode) __attribute__((__stkparm__));

extern void FastDrawHLine(void* plane,short x1,short x2,short y,short mode) __attribute__((__stkparm__));
extern void FastDrawHLine_R(void* plane asm("a0"),  short x1 asm("d0"),  short x2 asm("d1"),  short y asm("d2"),short mode) __attribute__((__stkparm__));

extern void FastDrawVLine(void* plane,short x,short y1,short y2,short mode) __attribute__((__stkparm__));
extern void FastDrawVLine_R(void* plane asm("%a0"), short x asm("%d0"), short y1 asm("%d1"), short y2 asm("%d2"),short mode) __attribute__((__stkparm__));

extern void FastFillRect_R(void* plane asm("%a0"), short x1 asm("%d0"), short y1 asm("%d1"), short x2 asm("%d2"), short y2 asm("%d3"),short mode) __attribute__((__stkparm__));

//#define _rom_call(type,args,ind) (*(type(**)args)(*(long*)0xC8+0x##ind*4))
#define ScrRectFill  _rom_call(void,(SCR_RECT*,SCR_RECT*,short),189)
#define DrawClipRect _rom_call(void,(WIN_RECT*,SCR_RECT*,short),195)
#define TIOSDrawLine _rom_call(void,(short,short,short,short,short),1A7)
#define DrawStr      _rom_call(void,(short,short,char*,short),1A9)
#define DrawChar     _rom_call(void,(short,short,char,short),1A4)
#define FontGetSys   _rom_call(unsigned char,(void),18E)
#define FontSetSys   _rom_call(unsigned char,(short),18F)
#define DrawStrWidth _rom_call(short,(char*,short),197)
#define PortSet      _rom_call(void,(void*,long),1A2)
#define malloc       _rom_call(void*,(long),A2)
#define free         _rom_call(void,(void*),A3)
#define memset       _rom_call(void*,(void*,short,long),27C)
#define memcpy       _rom_call(void*,(void*,const void*,long),26A)
#define FULLSCREEN  &(SCR_RECT){{0, 0, 239, 127}}

#include <compat.h>
#include <default.h>

