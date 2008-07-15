/******************************************************************************
*
* project name:    ExtGraph
* initial date:    15/07/2008
* author:          lionel_debroux@yahoo.fr
* description:     test program for clipped sprite get functions
*
*******************************************************************************/

#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS

#define NO_CALC_DETECT
#define MIN_AMS 100

#include <tigcclib.h>
#include "../../lib/extgraph.h" // NOTE: this path is just for this demo !!
//#include "extgraph.h" // NOTE: this path is just for this demo !!
                                  //       if the extgraph library is correctly
                                  //       installed you should use:
                                  //
                                  //       #include <extgraph.h>

void _main(void) {
    LCD_BUFFER backbuffer;
    unsigned char buffer[100*38];
    short i;
    unsigned short j;

    LCD_save(backbuffer);

    ST_helpMsg("ClipSprite8Get_R() Demo - Press Key");
    ngetchx();

    for (j=0;j<64;j++) {
        for (i=0;i<20;i++) {
            ClipSprite8Get_R(j+(i<<3),0,100,backbuffer,((unsigned char*)buffer)+100*i);
        }
        ClrScr();
        for (i=0;i<20;i++) {
            ClipSprite8_OR_R(i<<3,0,100,((unsigned char*)buffer)+100*i,LCD_MEM);
        }
    }

    ST_helpMsg("ClipSprite16Get_R() Demo - Press Key");
    ngetchx();

    for (j=0;j<64;j++) {
        for (i=0;i<10;i++) {
            ClipSprite16Get_R(j+(i<<4),0,100,backbuffer,((unsigned short*)buffer)+100*i);
        }
        ClrScr();
        for (i=0;i<10;i++) {
            ClipSprite16_OR_R(i<<4,0,100,((unsigned short*)buffer)+100*i,LCD_MEM);
        }
    }

    ST_helpMsg("ClipSprite32Get_R() Demo - Press Key");
    ngetchx();

    for (j=0;j<64;j++) {
        for (i=0;i<5;i++) {
            ClipSprite32Get_R(j+(i<<5),0,100,backbuffer,((unsigned long*)buffer)+100*i);
        }
        ClrScr();
        for (i=0;i<5;i++) {
            ClipSprite32_OR_R(i<<5,0,100,((unsigned long*)buffer)+100*i,LCD_MEM);
        }
    }

    LCD_restore(backbuffer);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo4.c,v $
// Revision 2.1  2004/
// Update to ExtGraph 2.00RC1: now using __attribute__((__regparm__))
// functions, it's significantly smaller and a bit faster.
// Directives NO_CALC_DETECT and MIN_AMS 100 added.
// demo4 is now below 1000 bytes, 25% smaller than it was before.
//
// Revision 1.4  2002/02/22 15:06:13  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.3  2002/02/11 11:02:22  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) unnecessary SAVE_SCREEN directive removed (Lionel Debroux)
// (3) speed improvements by using shifting instead of multiplications (Lionel Debroux)
// (4) missing history added to end of file
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
