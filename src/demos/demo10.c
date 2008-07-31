/******************************************************************************
*
* project name:    ExtGraph
* initial date:    31/05/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for fastcopyscreen function
*
* $Id: demo10.c,v 1.5 2002/02/22 15:06:13 tnussb Exp $
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


void Draw_Str(short y, const char *buffer) {
    DrawStr(0,y,buffer,A_NORMAL);
}

void _main(void) {
    LCD_BUFFER lcd;
    unsigned char *orig=(unsigned char *)malloc(2*LCD_SIZE);
    unsigned char *blank;

    if (!orig) {
        ST_helpMsg("Not enough memory.");
        return;
    }
    blank=orig+LCD_SIZE;

    LCD_save(lcd);

    memset(blank,0,LCD_SIZE);

    OSSetSR(0x0200);

    Draw_Str(0,"Stupid demo which flips");
    Draw_Str(10,"between the normal screen");
    Draw_Str(20,"and an almost blank screen.");
    Draw_Str(30,"You should see fast");
    Draw_Str(40,"flickers.");

    LCD_save(orig);
    PortSet(blank,239,127);

    Draw_Str(0,"Stupid demo which flips");
    Draw_Str(10,"between the normal screen");
    Draw_Str(20,"and an almost blank screen.");
    Draw_Str(30,"You should see fast");
    Draw_Str(40,"flickers.");

    PortRestore();

    do {
        FastCopyScreen_R(blank,LCD_MEM);
        FastCopyScreen(orig,LCD_MEM);
    }
    while (!(_rowread(0xF000)&0xFF));
    OSSetSR(0);

    free(orig);
    LCD_restore(lcd);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo10.c,v $
// Revision 1.5  2002/02/22 15:06:13  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.4  2002/02/22 13:14:54  tnussb
// (1) bug fix: invalid rowread (doesn't work on TI92P) fixed (Lionel Debroux)
// (2) trap 12 usage replaced by safe OSSetSR()
//
// Revision 1.3  2002/02/11 11:49:52  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) uses now dynamic memory allocation instead of stack (Lionel Debroux)
// (3) missing history added to end of file
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
