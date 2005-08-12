/******************************************************************************
*
* project name:    ExtGraph
* initial date:    13/04/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for fast sprite functions
*
* $Id: demo3.c,v 1.5 2002/02/22 15:06:13 tnussb Exp $
*
*******************************************************************************/

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

unsigned char  spritedata8[8]  = {0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55};
unsigned short spritedata16[8] = {0xaaaa,0x5555,0xaaaa,0x5555,0xaaaa,0x5555,0xaaaa,0x5555};
unsigned long  spritedata32[8] = {0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555,0xaaaaaaaa,0x55555555};


/*===========================================================================*/
/* testing monochrome Sprite8_XXX functions ...                              */
/*===========================================================================*/
static inline short Test8(void) {
    unsigned long  measure_val;
    char           tmpstr[100];
    short          x,y;
    long           count;

    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-8;x++) {
            count++;
            Sprite8(x,y,8,spritedata8,LCD_MEM,SPRT_AND);
            Sprite8(x,y,8,spritedata8,LCD_MEM,SPRT_OR);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"orig8=%lu tics for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;


    //-------------------------------------------------------------------------
    // modified sprite functions using separate and/or
    //-------------------------------------------------------------------------
    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-8;x++) {
            count++;
            Sprite8_AND_R(x,y,8,spritedata8,LCD_MEM);
            Sprite8_OR_R(x,y,8,spritedata8,LCD_MEM);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu tics for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions using just one call
    //-------------------------------------------------------------------------

    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-8;x++) {
            count++;
            Sprite8_MASK_R(x,y,8,spritedata8,spritedata8,LCD_MEM);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu tics for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    return ngetchx();
}


/*===========================================================================*/
/* testing monochrome Sprite16_XXX functions ...                             */
/*===========================================================================*/
static inline short Test16(void) {
    unsigned long  measure_val;
    char           tmpstr[100];
    short          x,y;
    long           count;

    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-16;x++) {
            count++;
            Sprite16(x,y,8,spritedata16,LCD_MEM,SPRT_AND);
            Sprite16(x,y,8,spritedata16,LCD_MEM,SPRT_OR);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"orig16=%lu tics for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;


    //-------------------------------------------------------------------------
    // modified sprite functions using separate and/or
    //-------------------------------------------------------------------------
    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-16;x++) {
            count++;
            Sprite16_AND_R(x,y,8,spritedata16,LCD_MEM);
            Sprite16_OR_R(x,y,8,spritedata16,LCD_MEM);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu tics for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions using just one call
    //-------------------------------------------------------------------------

    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-16;x++) {
            count++;
            Sprite16_MASK_R(x,y,8,spritedata16,spritedata16,LCD_MEM);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu tics for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    return ngetchx();
}


/*===========================================================================*/
/* testing monochrome Sprite32_XXX functions ...                             */
/*===========================================================================*/
static inline short Test32(void) {
    unsigned long  measure_val;
    char           tmpstr[100];
    short          x,y;
    long           count;

    //-------------------------------------------------------------------------
    // original sprite functions
    //-------------------------------------------------------------------------
    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-32;x++) {
            count++;
            Sprite32(x,y,8,spritedata32,LCD_MEM,SPRT_AND);
            Sprite32(x,y,8,spritedata32,LCD_MEM,SPRT_OR);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"orig32=%lu tics for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;


    //-------------------------------------------------------------------------
    // modified sprite functions using separate and/or
    //-------------------------------------------------------------------------
    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-32;x++) {
            count++;
            Sprite32_AND_R(x,y,8,spritedata32,LCD_MEM);
            Sprite32_OR_R(x,y,8,spritedata32,LCD_MEM);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu tics for %ld sprites",(1000-measure_val)*50,count);
    ST_helpMsg(tmpstr);
    if (ngetchx() == KEY_ESC) return KEY_ESC;

    //-------------------------------------------------------------------------
    // modified sprite functions using just one call
    //-------------------------------------------------------------------------

    count = 0;
    memset(LCD_MEM,0,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);
    OSTimerRestart(USER_TIMER);

    for (y=0;y<100-16;y++) {
        for (x=0;x<160-32;x++) {
            count++;
            Sprite32_MASK_R(x,y,8,spritedata32,spritedata32,LCD_MEM);
        }
    }

    measure_val = OSTimerCurVal(USER_TIMER);
    OSFreeTimer(USER_TIMER);
    sprintf(tmpstr,"%lu tics for %ld sprites",(1000-measure_val)*50,count);
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

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo3.c,v $
// Revision 1.5  2002/02/22 15:06:13  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.4  2002/02/11 10:53:11  tnussb
// missing history added to end of file
//
// Revision 1.3  2002/02/11 10:38:59  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) unnecessary backup of original screen removed (Lionel Debroux)
// (3) memsets uses now correct TIGCCLIB defines instead of hardcoded values (Lionel Debroux)
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
