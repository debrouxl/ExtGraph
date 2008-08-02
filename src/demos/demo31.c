/******************************************************************************
*
* project name:    ExtGraph
* initial date:    16/05/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for plane scaling/copy routines
*
* $Id: demo31.c,v 1.6 2002/02/22 16:35:39 tnussb Exp $
*
*******************************************************************************/

#define MIN_AMS 100
#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS
#define NO_AMS_CHECK

#ifdef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define C89_92V200(x,y) x
#else
#undef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define USE_TI92P
#define USE_V200
#define C89_92V200(x,y) y
#endif

#include <tigcclib.h>
#include "../../lib/extgraph.h"  // NOTE: this path is just for this demo !!
                                 //       if the extgraph library is correctly
                                 //       installed you should use:
                                 //
                                 //       #include <extgraph.h>



void _main(void) {
#define bsize (100*20+4) // Size of a bitmap for a 160x100 screen.
    unsigned short i = 0;
    LCD_BUFFER lcd, lcd2;
    static unsigned char tmpstr[100];
    static const SCR_RECT theScreen = {{0,0,159,99}};
    unsigned char sscreen[bsize];

    LCD_save(lcd);

    BitmapGet(&theScreen,sscreen);
    memset(lcd2,0x00,LCD_SIZE);

    ST_busy(ST_CLEAR);
    OSSetSR(0x0200);

    
    // Scale from calculator actual screen size.
    ST_helpMsg("Benchmarking...");
    OSRegisterTimer(USER_TIMER,100000*20UL);
    for (i = 0; i < 3000; i++) {
        C89_92V200(Scale1Plane160to240_R(lcd, lcd2),
                   Scale1Plane240to160_R(lcd, lcd2));
    }
    LCD_restore(lcd2);
    C89_92V200(sprintf(tmpstr,"%lu ticks for 3000 160->240 scaling",(100000*20UL-OSTimerCurVal(USER_TIMER))),
               sprintf(tmpstr,"%lu ticks for 3000 240->160 scaling",(100000*20UL-OSTimerCurVal(USER_TIMER))));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;


    // Scale to calculator actual screen size.
    ClrScr();
    ST_helpMsg("Benchmarking...");
    OSRegisterTimer(USER_TIMER,100000*20UL);
    for (i = 0; i < 3000; i++) {
        C89_92V200(Scale1Plane240to160_R(lcd2, LCD_MEM),
                   Scale1Plane160to240_R(lcd2, LCD_MEM));
    }
    C89_92V200(sprintf(tmpstr,"%lu ticks for 3000 160->240 scaling",(100000*20UL-OSTimerCurVal(USER_TIMER))),
               sprintf(tmpstr,"%lu ticks for 3000 240->160 scaling",(100000*20UL-OSTimerCurVal(USER_TIMER))));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    ngetchx();

    
    // Copy 160x100 screen to the upper-left corner of the 240x128 screen.
    ClrScr();
    ST_helpMsg("Benchmarking...");
    OSRegisterTimer(USER_TIMER,100000*20UL);
    for (i = 0; i < 3000; i++) {
        FastCopyScreen160to240_R(100, &sscreen[4], LCD_MEM);
    }
    sprintf(tmpstr,"%lu ticks for 3000 160->240 copying",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    ngetchx();

    
    // Copy 160x100 screen near the center of the 240x128 screen.
    ClrScr();
    ST_helpMsg("Benchmarking...");
    OSRegisterTimer(USER_TIMER,100000*20UL);
    for (i = 0; i < 3000; i++) {
        FastCopyScreen160to240NC_R(100, &sscreen[4], LCD_MEM);
    }
    sprintf(tmpstr,"%lu ticks for 3000 160->240 copying",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    ngetchx();


    end:
    OSSetSR(0);
    LCD_restore(lcd);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
#undef bsize
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo6.c,v $
// Revision 1.6  2002/02/22 16:35:39  tnussb
// checking for desired calculator type added ...
//
// Revision 1.5  2002/02/22 15:06:14  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.4  2002/02/22 13:10:59  tnussb
// (1) TI92+ support fixed (Lionel Debroux)
// (2) replaced trap 12 usage by save OSSetSR
//
// Revision 1.3  2002/02/11 11:29:31  tnussb
// (1) complete new demo done by Lionel Debroux
// (2) size optimizations and sourcecode reformatted to fit
//     TICT-style by tnussb
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
