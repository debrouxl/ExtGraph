#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS

#define NO_AMS_CHECK
#define MIN_AMS 100

#include <tigcclib.h>
#include "../../lib/extgraph.h"  // NOTE: this path is just for this demo !!
                                 //       if the extgraph library is correctly
                                 //       installed you should use:
                                 //
                                 //       #include <extgraph.h>

static const unsigned char spritedata8[8]  = {0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55};
static const unsigned short spritedata16[16] = {
0xaaaa,0x5555,0xaaaa,0x5555,
0xaaaa,0x5555,0xaaaa,0x5555,
0xaaaa,0x5555,0xaaaa,0x5555,
0xaaaa,0x5555,0xaaaa,0x5555};
static const unsigned long spritedata32[32] = {
0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,
0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555};


/*===========================================================================*/
/* testing monochrome Tile8x8_XXX functions ...                              */
/*===========================================================================*/
static inline short Test8(void) {
    unsigned long  measure_val;
    char           tmpstr[100];
    short          x,y,i;
    long           count;

    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-16;y++) {
            for (x=0;x<=160-8;x+=8) {
                count++;
                Sprite8(x,y,8,spritedata8,LCD_MEM,SPRT_AND);
                Sprite8(x,y,8,spritedata8,LCD_MEM,SPRT_OR);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"TIGCCLIB AND+OR: %lu ticks for %ld sprites",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;


    //-------------------------------------------------------------------------
    // modified sprite functions using separate and/or
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-16;y++) {
            for (x=0;x<20;x++) {
                count++;
                Tile8x8_AND_R(x,y,spritedata8,LCD_MEM);
                Tile8x8_OR_R(x,y,spritedata8,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph AND+OR: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (mask the sprite with itself)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-16;y++) {
            for (x=0;x<20;x++) {
                count++;
                Tile8x8_MASK_R(x,y,spritedata8,spritedata8,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph MASK: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (blit tile with one-liner mask)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-16;y++) {
            for (x=0;x<20;x++) {
                count++;
                Tile8x8_BLIT_R(x,y,spritedata8,0x00,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph BLIT: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (replace the tile)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-16;y++) {
            for (x=0;x<20;x++) {
                count++;
                Tile8x8_RPLC_R(x,y,spritedata8,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph RPLC: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;


    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-16;y++) {
            for (x=0;x<=160-8;x+=8) {
                count++;
                Sprite8(x,y,8,spritedata8,LCD_MEM,SPRT_XOR);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"TIGCCLIB XOR: %lu ticks for %ld sprites",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (XOR the tile)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-16;y++) {
            for (x=0;x<20;x++) {
                count++;
                Tile8x8_XOR_R(x,y,spritedata8,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph XOR: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    return ngetchx();
}


/*===========================================================================*/
/* testing monochrome Tile16x16_XXX functions ...                            */
/*===========================================================================*/
static inline short Test16(void) {
    unsigned long  measure_val;
    char           tmpstr[100];
    short          x,y,i;
    long           count;

    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-24;y++) {
            for (x=0;x<=160-16;x+=16) {
                count++;
                Sprite16(x,y,16,spritedata16,LCD_MEM,SPRT_AND);
                Sprite16(x,y,16,spritedata16,LCD_MEM,SPRT_OR);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"TIGCCLIB AND+OR: %lu ticks for %ld sprites",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;


    //-------------------------------------------------------------------------
    // modified sprite functions using separate and/or
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-24;y++) {
            for (x=0;x<10;x++) {
                count++;
                Tile16x16_AND_R(x,y,spritedata16,LCD_MEM);
                Tile16x16_OR_R(x,y,spritedata16,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph AND+OR: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (mask the sprite with itself)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-24;y++) {
            for (x=0;x<10;x++) {
                count++;
                Tile16x16_MASK_R(x,y,spritedata16,spritedata16,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph MASK: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (blit tile with one-liner mask)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-24;y++) {
            for (x=0;x<10;x++) {
                count++;
                Tile16x16_BLIT_R(x,y,spritedata16,0x0000,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph BLIT: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (replace the sprite)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-24;y++) {
            for (x=0;x<10;x++) {
                count++;
                Tile16x16_RPLC_R(x,y,spritedata16,LCD_MEM);
            }
        }
    }
    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph RPLC: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    return ngetchx();

    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-24;y++) {
            for (x=0;x<=160-16;x+=16) {
                count++;
                Sprite16(x,y,16,spritedata16,LCD_MEM,SPRT_XOR);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"TIGCCLIB XOR: %lu ticks for %ld sprites",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (XOR the sprite)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-24;y++) {
            for (x=0;x<10;x++) {
                count++;
                Tile16x16_XOR_R(x,y,spritedata16,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph XOR: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

}


/*===========================================================================*/
/* testing monochrome Tile32_XXX functions ...                               */
/*===========================================================================*/
static inline short Test32(void) {
    unsigned long  measure_val;
    char           tmpstr[100];
    short          x,y,i;
    long           count;

    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-40;y++) {
            for (x=0;x<=160-32;x+=16) {
                count++;
                Sprite32(x,y,32,spritedata32,LCD_MEM,SPRT_AND);
                Sprite32(x,y,32,spritedata32,LCD_MEM,SPRT_OR);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"TIGCCLIB AND+OR: %lu ticks for %ld sprites",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;


    //-------------------------------------------------------------------------
    // modified sprite functions using separate and/or
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-40;y++) {
            for (x=0;x<9;x++) {
                count++;
                Tile32x32_AND_R(x,y,spritedata32,LCD_MEM);
                Tile32x32_OR_R(x,y,spritedata32,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph AND+OR: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (mask the sprite with itself)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-40;y++) {
            for (x=0;x<9;x++) {
                count++;
                Tile32x32_MASK_R(x,y,spritedata32,spritedata32,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph MASK: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (blit tile with one-liner mask)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-40;y++) {
            for (x=0;x<9;x++) {
                count++;
                Tile32x32_BLIT_R(x,y,spritedata32,0x00000000,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph BLIT: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (replace the sprite)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-40;y++) {
            for (x=0;x<9;x++) {
                count++;
                Tile32x32_RPLC_R(x,y,spritedata32,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph RPLC: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;


    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-40;y++) {
            for (x=0;x<=160-32;x+=16) {
                count++;
                Sprite32(x,y,32,spritedata32,LCD_MEM,SPRT_XOR);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"TIGCCLIB XOR: %lu ticks for %ld sprites",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions (XOR the sprite)
    //-------------------------------------------------------------------------
    count = 0;
    ClrScr();

    OSRegisterTimer(USER_TIMER,1000);

    for (i=5;(i--);) {
        for (y=0;y<=100-40;y++) {
            for (x=0;x<9;x++) {
                count++;
                Tile32x32_XOR_R(x,y,spritedata32,LCD_MEM);
            }
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"ExtGraph XOR: %lu ticks for %ld tiles",1000-measure_val,count);
    ST_helpMsg(tmpstr);
    return ngetchx();
}


/*===========================================================================*/
/* just a simple demo program to measure the performance gain ...            */
/*===========================================================================*/
void _main(void) {
    LCD_BUFFER screen;
    short      retval;

    LCD_save(screen);

    retval = Test8();
    if (retval != KEY_ESC) retval=Test16();
    if (retval != KEY_ESC) retval=Test32();

    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
