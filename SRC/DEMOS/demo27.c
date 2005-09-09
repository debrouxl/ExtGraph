// Demo for sprite rotating functions (X8).


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
#define bsize (100*20+4) // Size of a bitmap for a 160x100 screen.
    int i;
    LCD_BUFFER lcd;
    static SCR_RECT theScreen = {{0,0,159,99}};
    unsigned char sscreen[bsize];
    unsigned char sscreen2[bsize];

    LCD_save(lcd);

    BitmapGet(&theScreen,sscreen);
    memset(sscreen2,0,bsize);
    ((BITMAP*)sscreen2)->NumRows=((BITMAP*)sscreen)->NumRows;
    ((BITMAP*)sscreen2)->NumCols=((BITMAP*)sscreen)->NumCols;
    GKeyFlush();
    for (i = 0; (i <= 360) && (!kbhit()); i++)
    {
        RotateSpriteX8_R(((BITMAP*)sscreen)->Data,((BITMAP*)sscreen2)->Data,160,100,80,50,i);
        ClrScr();
        FastCopyScreen160to240_R(100,((BITMAP*)sscreen2)->Data,LCD_MEM);
    }

    LCD_restore(lcd);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
#undef bsize
}
