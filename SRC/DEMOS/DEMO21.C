#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS

#define NO_AMS_CHECK
#define NO_CALC_DETECT
#define MIN_AMS 100

#include <tigcclib.h>
#include "../../lib/extgraph.h"  // NOTE: this path is just for this demo !!
                                 //       if the extgraph library is correctly
                                 //       installed you should use:
                                 //
                                 //       #include <extgraph.h>
#include "../../lib/preshift.h"

#define isprite_16 \
((unsigned short[2*16]){0x1,0x1,0x3,0x3,0x7,0x7,0xF,0xF,0x1F,0x1F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0x1FF,0x1FF,0x3FF,0x3FF,0x7FF,0x7FF,0xFFF,0xFFF,0x1FFF,0x1FFF,0x3FFF,0x3FFF,0x7FFF,0x7FFF,0xFFFF,0xFFFF})

static const unsigned short sprite_16[16] =
{
0b0000011111100000,
0b0001111111111000,
0b0011111111111100,
0b0111111111111110,
0b0111101111011110,
0b1111010110101111,
0b1111111111111111,
0b1111111111111111,
0b1111111001111111,
0b1110011111100111,
0b1110101111010111,
0b0111010000101110,
0b0111101111011110,
0b0011110000111100,
0b0001111111111000,
0b0000011111100000};



/*===========================================================================*/
/* just a simple demo program to measure the performance gain ...            */
/*===========================================================================*/
void _main(void) {
    LCD_BUFFER     screen;
    unsigned long  measure_val;
    unsigned char  tmpstr[100];
    short          x,y,i;
    long           count;
    unsigned long  preshiftbuf[256];

    LCD_save(screen);

    // Grayscale.
    PreshiftGrayISprite16x16(isprite_16,preshiftbuf);

    if(!GrayOn()) goto end;
    count = 0;

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);

    for (i=2;(i--);) {
        GrayClearScreen_R();
        for (y=0;y<=100-16;y++) {
            for (x=0;x<=160-8;x++) {
                count++;
                GrayPSprite16x16_OR_R(x,y,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
            }
        }
    }

    GrayOff();
    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu ticks for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) goto end;


    if(!GrayOn()) goto end;
    count = 0;

    OSRegisterTimer(USER_TIMER,1000);

    for (i=2;(i--);) {
        GrayClearScreen_R();
        for (y=0;y<=100-16;y++) {
            for (x=0;x<=160-8;x++) {
                count++;
                GrayClipISprite16_OR_R(x,y,16,isprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
            }
        }
    }

    GrayOff();
    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu ticks for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    ngetchx();


    // B/W.
    PreshiftSprite16x16(sprite_16,preshiftbuf);

    count = 0;

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);

    for (i=2;(i--);) {
        ClrScr();
        for (y=0;y<=100-16;y++) {
            for (x=0;x<=160-8;x++) {
                count++;
                PSprite16x16_OR_R(x,y,preshiftbuf,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu ticks for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) goto end;


    count = 0;

    OSRegisterTimer(USER_TIMER,1000);

    for (i=2;(i--);) {
        ClrScr();
        for (y=0;y<=100-16;y++) {
            for (x=0;x<=160-8;x++) {
                count++;
                Sprite16_OR_R(x,y,16,sprite_16,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu ticks for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    ngetchx();


    end:
    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
