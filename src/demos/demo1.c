/******************************************************************************
*
* project name:    ExtGraph
* initial date:    12/04/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for scrolling functions
*
* $Id: demo1.c,v 1.6 2002/02/25 20:43:00 tnussb Exp $
*
*******************************************************************************/
#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS
#define NO_AMS_CHECK
#define MIN_AMS 100

#ifdef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define C89_92V200(x,y) (x)
#else
#undef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define USE_TI92P
#define USE_V200
#define C89_92V200(x,y) (y)
#endif

#include <tigcclib.h>

// NOTE: this path is just for this demo !!
//       if the extgraph library is correctly
//       installed you should use:
//
//       #include <extgraph.h>
#include "../../lib/extgraph.h"

//=============================================================================
// simple demo program which demonstrates an earthquake effect
//
// can you screenshot this effect ??? ;-)
//=============================================================================
void _main(void) {
    LCD_BUFFER screen;
    short      old_random = 0;
    short      new_random = 0;

    LCD_save(screen);

    OSSetSR(0x0200);

    // Waiting loop so as to cut rebounds on key. It replaces a
    // bigger block of code that uses OS timer functions.
    asm("move.l #0x27FFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

    do {
        old_random = new_random;
        do {
            new_random = random(4);
        }
        while (new_random == old_random);


        //---------------------------------------------------------------------
        // if/else if/else chain produces smaller code than case !!
        //---------------------------------------------------------------------

#ifdef USE_TI89
        if (!new_random)        ScrollLeft160_R(LCD_MEM,100);
        else if (new_random==1) ScrollRight160_R(LCD_MEM,100);
        else if (new_random==2) ScrollUp160_R(LCD_MEM,100);
        else                    ScrollDown160_R(LCD_MEM,100);
#else
        if (!new_random)        ScrollLeft240_R(LCD_MEM,128);
        else if (new_random==1) ScrollRight240_R(LCD_MEM,128);
        else if (new_random==2) ScrollUp240_R(LCD_MEM,128);
        else                    ScrollDown240_R(LCD_MEM,128);
#endif
    }
    while (!(_rowread(0xF000)&0xFF));

    OSSetSR(0x0000);

    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}


//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo1.c,v $
// Revision 2.1  2004/
// * now using OSSetSR(0x0200) instead of OSSetSR(0x0700), because 0x0700 (in
// fact any value above 0x300) stops the clock on AMS 2.07+.
//
// Revision 1.6  2002/02/25 20:43:00  tnussb
// is built now for each calctype separately to reduce size (Lionel Debroux)
//
// Revision 1.5  2002/02/22 15:06:13  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.4  2002/02/22 13:04:24  tnussb
// (1) Bugfix: bad _rowread ! (doesn't suit on a TI-92P) (Lionel Debroux)
// (2) trap 12 usage replaced again with safe OSSetSR()
//
// Revision 1.3  2002/02/11 10:30:42  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) disables all interrupts for speed + direct keyboard testing (Lionel Debroux)
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  Thomas Nussbaumer
// initial check-in

