/******************************************************************************
*
* project name:    ExtGraph
* initial date:    29/05/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for floodfill functions
*
* $Id: demo8.c,v 1.4 2002/02/22 15:06:14 tnussb Exp $
*
*******************************************************************************/
#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS

#define NO_CALC_DETECT
#define NO_AMS_CHECK
#define MIN_AMS 100


#include <tigcclib.h>
// NOTE: this path is just for this demo !!
//       if the extgraph library is correctly
//       installed you should use:
//
//       #include <extgraph.h>
#include "..\..\lib\extgraph.h"


/*===========================================================================*/
/* main routine: where all the fun starts ...                                */
/*===========================================================================*/
void _main(void) {
    void*          tmpplane = malloc(LCD_SIZE);
    char           buffer[40];
    unsigned short shade;
    WIN_RECT       wrect;
    LCD_BUFFER     lcd;

    if (!tmpplane) { // out of memory check
        ST_helpMsg("Not enough memory!");
        return;
    }

    LCD_save(lcd);

    wrect.x0 = 16;
    wrect.y0 = 16;
    wrect.x1 = LCD_WIDTH-16;
    wrect.y1 = LCD_HEIGHT-16;

    ClrScr();

    do {
        shade = random(256) | (((unsigned short)random(256))<<8);
        sprintf(buffer,"shade=0x%04x (key for next fill)",shade);
        ClrScr();
        DrawClipRect(&wrect,&(SCR_RECT){{0, 0, 239, 127}}, A_NORMAL);
        FloodFill_R(wrect.x0+1,wrect.y0+1,shade,tmpplane,LCD_MEM);
        ST_helpMsg(buffer);
    }
    while (ngetchx()!=KEY_ESC);

    free(tmpplane);
    LCD_restore(lcd);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo8.c,v $
// Revision 1.4  2002/02/22 15:06:14  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.3  2002/02/11 11:38:54  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) SAVE_SCREEN directive replaced by own save/restore of screen,
//     otherwise out-of-mem message wouldn't be displayed (Lionel Debroux)
// (3) missing history added to end of file
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
