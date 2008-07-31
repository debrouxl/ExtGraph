#define NO_EXIT_SUPPORT
#define MIN_AMS 100
#define NO_AMS_CHECK
#define NO_CALC_DETECT
#include <tigcclib.h>         // Include All Header Files
#include "../../lib/extgraph.h"

static const unsigned char sprite_8[8]        = {0x81,0x43,0x27,0x1F,0x1F,0x3F,0x7F,0xFF};
static const unsigned char sprite2_8[8]       = {0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA};
static const unsigned char mask_8[8]          = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8};

static const unsigned char msprite_8[3*8]     = {0xFF,0x81,0x55,0xFF,0x43,0xAA,0xFF,0x27,0x55,0xFF,0x1F,0xAA,0xFF,0x1F,0x55,0xFE,0x3F,0xAA,0xFC,0x7F,0x55,0xF8,0xFF,0xAA};

    
static const unsigned short sprite_16[16]     = {0x8001,0x4003,0x2007,0x100F,0x001F,0x003F,0x007F,0x00FF,0x01FF,0x03FF,0x07FF,0x0FFF,0x1FFF,0x3FFF,0x7FFF,0xFFFF};
static const unsigned short sprite2_16[16]    = {0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA};
static const unsigned short mask_16[16]        = {0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFE,0xFFFC,0xFFF8};

static const unsigned short msprite_16[3*16]  = {0xFFFF,0x8001,0x5555,0xFFFF,0x4003,0xAAAA,0xFFFF,0x2007,0x5555,0xFFFF,0x100F,0xAAAA,0xFFFF,0x001F,0x5555,0xFFFF,0x003F,0xAAAA,0xFFFF,0x007F,0x5555,0xFFFF,0x00FF,0xAAAA,0xFFFF,0x01FF,0x5555,0xFFFF,0x03FF,0xAAAA,0xFFFF,0x07FF,0x5555,0xFFFF,0x0FFF,0xAAAA,0xFFFF,0x1FFF,0x5555,0xFFFE,0x3FFF,0xAAAA,0xFFFC,0x7FFF,0x5555,0xFFF8,0xFFFF,0xAAAA};


extern const unsigned char sprite_24[3*24];
asm("
.even
.byte 0x00
| Aligned to an odd boundary by intention.
sprite_24:
.word 0x8000
.byte 0x01
.word 0x4000
.byte 0x03
.word 0x2000
.byte 0x07
.word 0x1000
.byte 0x0F
.word 0x0000
.byte 0x1F
.word 0x0000
.byte 0x3F
.word 0x0000
.byte 0x7F
.word 0x0000
.byte 0xFF
.word 0x0001
.byte 0xFF
.word 0x0003
.byte 0xFF
.word 0x0007
.byte 0xFF
.word 0x000F
.byte 0xFF
.word 0x001F
.byte 0xFF
.word 0x003F
.byte 0xFF
.word 0x007F
.byte 0xFF
.word 0x00FF
.byte 0xFF
.word 0x01FF
.byte 0xFF
.word 0x03FF
.byte 0xFF
.word 0x07FF
.byte 0xFF
.word 0x0FFF
.byte 0xFF
.word 0x1FFF
.byte 0xFF
.word 0x3FFF
.byte 0xFF
.word 0x7FFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.even
");

extern const unsigned char sprite2_24[3*24];
asm("
.even
.byte 0x00
| Aligned to an odd boundary by intention.
sprite2_24:
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.word 0x5555
.byte 0x55
.word 0xAAAA
.byte 0xAA
.even
");

extern const unsigned char mask_24[3*24];
asm("
.even
.byte 0x00
| Aligned to an odd boundary by intention.
mask_24:
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFF
.word 0xFFFF
.byte 0xFE
.word 0xFFFF
.byte 0xFC
.word 0xFFFF
.byte 0xF8
.even
");



extern const unsigned char isprite_24[3*3*24];
asm("
.even
.byte 0x00
| Aligned to an odd boundary by intention.
isprite_24:
.word 0xFFFF
.byte 0xFF
.word 0x8000
.byte 0x01
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x4000
.byte 0x03
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x2000
.byte 0x07
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x1000
.byte 0x0F
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x0000
.byte 0x1F
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x0000
.byte 0x3F
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x0000
.byte 0x7F
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x0000
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x0001
.byte 0xFF
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x0003
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x0007
.byte 0xFF
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x000F
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x001F
.byte 0xFF
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x003F
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x007F
.byte 0xFF
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x00FF
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x01FF
.byte 0xFF
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x03FF
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x07FF
.byte 0xFF
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFF
.word 0x0FFF
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFF
.word 0x1FFF
.byte 0xFF
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xFE
.word 0x3FFF
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.word 0xFFFF
.byte 0xFC
.word 0x7FFF
.byte 0xFF
.word 0x5555
.byte 0x55
.word 0xFFFF
.byte 0xF8
.word 0xFFFF
.byte 0xFF
.word 0xAAAA
.byte 0xAA
.even
");


static const unsigned long sprite_32[32]      = {0x80000001,0x40000003,0x20000007,0x1000000F,0x0000001F,0x0000003F,0x0000007F,0x000000FF,0x000001FF,0x000003FF,0x000007FF,0x00000FFF,0x00001FFF,0x00003FFF,0x00007FFF,0x0000FFFF,0x0001FFFF,0x0003FFFF,0x0007FFFF,0x000FFFFF,0x001FFFFF,0x003FFFFF,0x007FFFFF,0x00FFFFFF,0x01FFFFFF,0x03FFFFFF,0x07FFFFFF,0x0FFFFFFF,0x1FFFFFFF,0x3FFFFFFF,0x7FFFFFFF,0xFFFFFFFF};
static const unsigned long sprite2_32[32]     = {0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA};
static const unsigned long mask_32[32]        = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFE,0xFFFFFFFC,0xFFFFFFF8};

static const unsigned long msprite_32[3*32]   = {0xFFFFFFFF,0x80000001,0x55555555,0xFFFFFFFF,0x40000003,0xAAAAAAAA,0xFFFFFFFF,0x20000007,0x55555555,0xFFFFFFFF,0x1000000F,0xAAAAAAAA,0xFFFFFFFF,0x0000001F,0x55555555,0xFFFFFFFF,0x0000003F,0xAAAAAAAA,0xFFFFFFFF,0x0000007F,0x55555555,0xFFFFFFFF,0x000000FF,0xAAAAAAAA,0xFFFFFFFF,0x000001FF,0x55555555,0xFFFFFFFF,0x000003FF,0xAAAAAAAA,0xFFFFFFFF,0x000007FF,0x55555555,0xFFFFFFFF,0x00000FFF,0xAAAAAAAA,0xFFFFFFFF,0x00001FFF,0x55555555,0xFFFFFFFF,0x00003FFF,0xAAAAAAAA,0xFFFFFFFF,0x00007FFF,0x55555555,0xFFFFFFFF,0x0000FFFF,0xAAAAAAAA,0xFFFFFFFF,0x0001FFFF,0x55555555,0xFFFFFFFF,0x0003FFFF,0xAAAAAAAA,0xFFFFFFFF,0x0007FFFF,0x55555555,0xFFFFFFFF,0x000FFFFF,0xAAAAAAAA,0xFFFFFFFF,0x001FFFFF,0x55555555,0xFFFFFFFF,0x003FFFFF,0xAAAAAAAA,0xFFFFFFFF,0x007FFFFF,0x55555555,0xFFFFFFFF,0x00FFFFFF,0xAAAAAAAA,0xFFFFFFFF,0x01FFFFFF,0x55555555,0xFFFFFFFF,0x03FFFFFF,0xAAAAAAAA,0xFFFFFFFF,0x07FFFFFF,0x55555555,0xFFFFFFFF,0x0FFFFFFF,0xAAAAAAAA,0xFFFFFFFF,0x1FFFFFFF,0x55555555,0xFFFFFFFE,0x3FFFFFFF,0xAAAAAAAA,0xFFFFFFFC,0x7FFFFFFF,0x55555555,0xFFFFFFF8,0xFFFFFFFF,0xAAAAAAAA};


    
static unsigned char dest_8[3*3*8]            = {0};
static unsigned short dest_16[3*3*16]         = {0};
static unsigned long dest_32[3*3*32]          = {0};

static unsigned char mask[32*4]               = {0};
    
// Main Function
void _main(void) {
    LCD_BUFFER backbuffer;

    LCD_save(backbuffer);
    memset(mask,0xFF,sizeof(mask));

    if(GrayOn()) {
        FontSetSys(F_6x8);

        // CreateSprite(I)Shadow8
        GrayClearScreen_R();
        GrayDrawStr(0, 0,"Original",A_NORMAL);
        GrayDrawStr(0,10,"Darkened",A_NORMAL);
        GrayDrawStr(0,20,"Lightened",A_NORMAL);
        GraySpriteX8_OR(10*6,0,8,sprite_8,sprite2_8,1,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateSpriteShadow8_R(8,sprite_8,sprite2_8,mask,dest_8,dest_8+8);
        GraySpriteX8_OR(10*6,10,8,dest_8,dest_8+8,1,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateSpriteIShadow8_R(8,sprite_8,sprite2_8,mask,dest_8,dest_8+8);
        GraySpriteX8_OR(10*6,20,8,dest_8,dest_8+8,1,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        ngetchx();

        // CreateSprite(I)Shadow16
        GrayClearScreen_R();
        GrayDrawStr(0, 0,"Original",A_NORMAL);
        GrayDrawStr(0,20,"Darkened",A_NORMAL);
        GrayDrawStr(0,40,"Lightened",A_NORMAL);
        GraySpriteX8_OR(10*6,0,16,(unsigned char*)sprite_16,(unsigned char*)sprite2_16,2,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateSpriteShadow16_R(16,sprite_16,sprite2_16,(unsigned short *)mask,dest_16,dest_16+16);
        GraySpriteX8_OR(10*6,20,16,(unsigned char*)dest_16,(unsigned char*)(dest_16+16),2,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateSpriteIShadow16_R(16,sprite_16,sprite2_16,(unsigned short *)mask,dest_16,dest_16+16);
        GraySpriteX8_OR(10*6,40,16,(unsigned char*)dest_16,(unsigned char*)(dest_16+16),2,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        ngetchx();

        // CreateSprite(I)Shadow32
        GrayClearScreen_R();
        GrayDrawStr(0, 0,"Original",A_NORMAL);
        GrayDrawStr(0,20,"Darkened",A_NORMAL);
        GrayDrawStr(0,40,"Lightened",A_NORMAL);
        GraySpriteX8_OR(10*6,0,32,(unsigned char*)sprite_32,(unsigned char*)sprite2_32,4,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateSpriteShadow32_R(32,sprite_32,sprite2_32,(unsigned long *)mask,dest_32,dest_32+32);
        GraySpriteX8_OR(10*6+40,20,32,(unsigned char*)dest_32,(unsigned char*)(dest_32+32),4,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateSpriteIShadow32_R(32,sprite_32,sprite2_32,(unsigned long *)mask,dest_32,dest_32+32);
        GraySpriteX8_OR(10*6,40,32,(unsigned char*)dest_32,(unsigned char*)(dest_32+32),4,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        ngetchx();

        // CreateSprite(I)ShadowX8
        GrayClearScreen_R();
        GrayDrawStr(0, 0,"Original",A_NORMAL);
        GrayDrawStr(0,30,"Darkened",A_NORMAL);
        GrayDrawStr(0,60,"Lightened",A_NORMAL);
        GraySpriteX8_OR(10*6,0,24,(unsigned char*)sprite_24,(unsigned char*)sprite2_24,3,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateSpriteShadowX8_R(24,3,sprite_24,sprite2_24,mask,(unsigned char*)dest_32,(unsigned char*)(dest_32+32));
        GraySpriteX8_OR(10*6,30,24,(unsigned char*)dest_32,(unsigned char*)(dest_32+32),3,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateSpriteIShadowX8_R(24,3,sprite_24,sprite2_24,mask,(unsigned char*)dest_32,(unsigned char*)(dest_32+32));
        GraySpriteX8_OR(10*6,60,24,(unsigned char*)dest_32,(unsigned char*)(dest_32+32),3,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        ngetchx();



        // CreateISprite(I)Shadow8
        GrayClearScreen_R();
        GrayDrawStr(0, 0,"Original",A_NORMAL);
        GrayDrawStr(0,10,"Darkened",A_NORMAL);
        GrayDrawStr(0,20,"Lightened",A_NORMAL);
        GrayClipISprite8_MASK_R(10*6,0,8,msprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateISpriteShadow8_R(8,msprite_8,dest_8);
        GrayClipISprite8_MASK_R(10*6,10,8,dest_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateISpriteIShadow8_R(8,msprite_8,dest_8);
        GrayClipISprite8_MASK_R(10*6,20,8,dest_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        ngetchx();

        // CreateISprite(I)Shadow16
        GrayClearScreen_R();
        GrayDrawStr(0, 0,"Original",A_NORMAL);
        GrayDrawStr(0,20,"Darkened",A_NORMAL);
        GrayDrawStr(0,40,"Lightened",A_NORMAL);
        GrayClipISprite16_MASK_R(10*6,0,16,msprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateISpriteShadow16_R(16,msprite_16,dest_16);
        GrayClipISprite16_MASK_R(10*6,20,16,dest_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateISpriteIShadow16_R(16,msprite_16,dest_16);
        GrayClipISprite16_MASK_R(10*6,40,16,dest_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        ngetchx();

        // CreateISprite(I)Shadow32
        GrayClearScreen_R();
        GrayDrawStr(0, 0,"Original",A_NORMAL);
        GrayDrawStr(0,20,"Darkened",A_NORMAL);
        GrayDrawStr(0,40,"Lightened",A_NORMAL);
        GrayClipISprite32_MASK_R(10*6,0,32,msprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateISpriteShadow32_R(32,msprite_32,dest_32);
        GrayClipISprite32_MASK_R(10*6+40,20,32,dest_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        CreateISpriteIShadow32_R(32,msprite_32,dest_32);
        GrayClipISprite32_MASK_R(10*6,40,32,dest_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        ngetchx();
    }

    GrayOff();
    LCD_restore(backbuffer);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
