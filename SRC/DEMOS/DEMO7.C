/******************************************************************************
*
* project name:    ExtGraph
* initial date:    12/04/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for GrayLine and GrayStr functions
*
* $Id: demo7.c,v 1.4 2002/02/22 15:06:14 tnussb Exp $
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


#define PLANE1 GetPlane(LIGHT_PLANE)
#define PLANE2 GetPlane(DARK_PLANE)

/*===========================================================================*/
/* main routine: where all the fun starts ...                                */
/*===========================================================================*/
void _main(void) {
    short         i,j;
    unsigned long measure_val;
    char          tmpstr[50] = "Measuring, please wait ...";
    short         modes[4]   = {COLOR_LIGHTGRAY,COLOR_DARKGRAY,COLOR_BLACK,COLOR_WHITE};
    LCD_BUFFER    screen;

    LCD_save(screen);
    if (!GrayOn()) return;

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000);

    GrayClearScreen_R();

    GrayDrawStrExt(0,0,tmpstr,A_REPLACE|A_CENTERED|A_SHADOWED,F_4x6);

    do {
        //---------------------------------------------------------------------
        // build-in AMS line drawing routine ...
        //---------------------------------------------------------------------
        OSTimerRestart(USER_TIMER);
        for (j=0;j<4 && !kbhit();j++) {
            short used_color = modes[j];
            for (i=0;  i<160;i++) GrayDrawLine(80,50,i,8,   used_color);
            for (i=8;  i<100;i++) GrayDrawLine(80,50,159,i, used_color);
            for (i=159;i>=0; i--) GrayDrawLine(80,50,i,99,  used_color);
            for (i=99; i>=8; i--) GrayDrawLine(80,50,0,i,   used_color);
        }
        measure_val = OSTimerCurVal(USER_TIMER);
        sprintf(tmpstr,"OS routine took %lu time units",(1000-measure_val)*50);

        GrayDrawRect(0,0,239,7,COLOR_WHITE,RECT_FILLED);
        GrayDrawStrExt(0,0,tmpstr,A_REPLACE | A_CENTERED | A_SHADOWED,F_4x6);

        if (kbhit()) break;

        //---------------------------------------------------------------------
        // new line drawing routine ...
        //---------------------------------------------------------------------
        OSTimerRestart(USER_TIMER);
        for (j=0;j<4 && !kbhit();j++) {
            short used_color = modes[j];
            for (i=0;  i<160;i++) GrayFastDrawLine(80,50,i,8,   used_color);
            for (i=8;  i<100;i++) GrayFastDrawLine(80,50,159,i, used_color);
            for (i=159;i>=0; i--) GrayFastDrawLine(80,50,i,99,  used_color);
            for (i=99; i>=8; i--) GrayFastDrawLine(80,50,0,i,   used_color);
        }
        measure_val = OSTimerCurVal(USER_TIMER);
        sprintf(tmpstr,"Own routine took %lu time units",(1000-measure_val)*50);
        GrayDrawRect(0,0,239,8,COLOR_WHITE,RECT_FILLED);
        GrayDrawStrExt(0,0,tmpstr,A_REPLACE | A_CENTERED | A_SHADOWED,F_4x6);
    }
    while (!kbhit());

    ngetchx();
    OSFreeTimer(USER_TIMER);

    GrayOff();
    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo7.c,v $
// Revision 1.4  2002/02/22 15:06:14  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.3  2002/02/11 11:33:09  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) unnecessary saving/restoring of original screen removed (Lionel Debroux)
// (3) missing history added to end of file
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
