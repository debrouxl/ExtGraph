/******************************************************************************
*
* project name:    ExtGraph
* initial date:    12/04/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for fast line drawing function
*
* $Id: demo2.c,v 1.5 2002/02/22 15:06:13 tnussb Exp $
*
*******************************************************************************/

#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS

#define NO_CALC_DETECT
#define NO_AMS_CHECK
#define MIN_AMS 100

#include <tigcclib.h>
#include "../../lib/extgraph.h"  // NOTE: this path is just for this demo !!
                                 //       if the extgraph library is correctly
                                 //       installed you should use:
                                 //
                                 //       #include <extgraph.h>


/*===========================================================================*/
/* main routine: where all the fun starts ...                                */
/*===========================================================================*/
void _main(void) {
    short         i,j;
    unsigned long measure_val;
    char          tmpstr[50] = "Measuring, please wait ...";
    short         modes[6]   = { A_REPLACE,A_XOR,A_REVERSE,A_XOR,A_REPLACE,A_REVERSE};
    LCD_BUFFER    screen;

    LCD_save(screen);

    FontSetSys(F_4x6);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);

    ClearScreen();
    DrawStr(0,0,tmpstr,A_REPLACE);

    do {
        //---------------------------------------------------------------------
        // build-in AMS line drawing routine ...
        //---------------------------------------------------------------------
        OSTimerRestart(USER_TIMER);
        for (j=0;j<6 && !kbhit();j++) {
            short used_mode = modes[j];
            for (i=0;  i<160;i++) DrawLine(80,50,i,8,   used_mode);
            for (i=8;  i<100;i++) DrawLine(80,50,159,i, used_mode);
            for (i=159;i>=0; i--) DrawLine(80,50,i,99,  used_mode);
            for (i=99; i>=8; i--) DrawLine(80,50,0,i,   used_mode);
        }
        measure_val = OSTimerCurVal(USER_TIMER);
        sprintf(tmpstr,"OS Routine took %lu ticks",1000-measure_val);
        memset(LCD_MEM,0,30*8);
        DrawStr(0,0,tmpstr,A_REPLACE);

        if (kbhit()) break;

        //---------------------------------------------------------------------
        // new line drawing routine ...
        //---------------------------------------------------------------------
        OSTimerRestart(USER_TIMER);
        for (j=0;j<6 && !kbhit();j++) {
            short used_mode = modes[j];
            for (i=0;  i<160;i++) FastDrawLine_R(LCD_MEM,80,50,i,8,   used_mode);
            for (i=8;  i<100;i++) FastDrawLine_R(LCD_MEM,80,50,159,i, used_mode);
            for (i=159;i>=0; i--) FastDrawLine_R(LCD_MEM,80,50,i,99,  used_mode);
            for (i=99; i>=8; i--) FastDrawLine_R(LCD_MEM,80,50,0,i,   used_mode);
        }
        measure_val = OSTimerCurVal(USER_TIMER);
        sprintf(tmpstr,"Own Routine took %lu ticks",1000-measure_val);
        memset(LCD_MEM,0,30*8);
        DrawStr(0,0,tmpstr,A_REPLACE);
    }
    while (!kbhit());

    ngetchx();
    OSFreeTimer(USER_TIMER);
    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo2.c,v $
// Revision 1.5  2002/02/22 15:06:13  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.4  2002/02/11 10:48:49  tnussb
// missing log added to end of file
//
// Revision 1.3  2002/02/11 10:38:59  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) own saving of original screen removed (Lionel Debroux)
// (3) size of string buffer increased to prevent overflow (Lionel Debroux)
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
