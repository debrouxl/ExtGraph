/******************************************************************************
*
* project name:    ExtGraph
* initial date:    30/05/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for spriteX8 mirror functions
*
* $Id: demo9.c,v 1.4 2002/02/22 15:06:14 tnussb Exp $
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


void _main(void) {
    unsigned char* dest;
    unsigned char* orig;
    unsigned char* blitmask;
    LCD_BUFFER     lcd;

    if (!(dest=(unsigned char *)malloc(LCD_SIZE+LCD_SIZE+LCD_WIDTH/8))) {
        ST_helpMsg("Not enough memory !");
        return;
    }

    LCD_save(lcd);
    orig     = dest + LCD_SIZE;
    blitmask = orig + LCD_SIZE;

    memset(blitmask,0,LCD_WIDTH/8);

    SpriteX8Get_R(0,0,LCD_HEIGHT,LCD_MEM,orig,LCD_WIDTH/8);

    ST_helpMsg("[press key for 1st vertical mirror]");
    ngetchx();
    SpriteX8_MIRROR_V_R(LCD_HEIGHT,orig,LCD_WIDTH/8,dest);
    SpriteX8_BLIT_R(0,0,LCD_HEIGHT,dest,blitmask,LCD_WIDTH/8,LCD_MEM);

    ST_helpMsg("[press key for 2nd vertical mirror]");
    ngetchx();
    SpriteX8_MIRROR_V(LCD_HEIGHT,dest,LCD_WIDTH/8,orig);
    SpriteX8_BLIT_R(0,0,LCD_HEIGHT,orig,blitmask,LCD_WIDTH/8,LCD_MEM);

    ST_helpMsg("[press key for 1st horizontal mirror]");
    ngetchx();
    SpriteX8_MIRROR_H_R(LCD_HEIGHT,orig,LCD_WIDTH/8,dest);
    SpriteX8_BLIT_R(0,0,LCD_HEIGHT,dest,blitmask,LCD_WIDTH/8,LCD_MEM);

    ST_helpMsg("[press key for 2nd horizontal mirror]");
    ngetchx();
    SpriteX8_MIRROR_H(LCD_HEIGHT,dest,LCD_WIDTH/8,orig);
    SpriteX8_BLIT_R(0,0,LCD_HEIGHT,orig,blitmask,LCD_WIDTH/8,LCD_MEM);
    ST_helpMsg("[press key to exit]");
    ngetchx();

    LCD_restore(lcd);
    free(dest);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo9.c,v $
// Revision 1.4  2002/02/22 15:06:14  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.3  2002/02/11 11:45:24  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) SAVE_SCREEN replaced by own backup/restore (Lionel Debroux)
// (3) invalid memset (TI89 version) fixed  (Lionel Debroux)
// (4) using now dynamic memory allocation instead of stack (Lionel Debroux)
// (5) missing history added to end of file
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
