#define NO_EXIT_SUPPORT
#define MIN_AMS 100
#define NO_AMS_CHECK
#define NO_CALC_DETECT
#include <tigcclib.h>         // Include All Header Files
#include "../../lib/extgraph.h"

static const unsigned char mask[30] = {0};
#define WAIT {asm volatile("move.l #0x8FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");}

// Main Function
void _main(void) {
    LCD_BUFFER backbuffer;

    LCD_save(backbuffer);

    if(GrayOn()) {
        unsigned short j;
        unsigned char val;
        // Test miscellanous functions.
        FadeOutToBlack_CWS1_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_CCWS1_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_CCWS1_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_CWS1_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_LR_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_RL_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_RL_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_LR_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_TB_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,200);

        FadeOutToWhite_BT_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,200);

        FadeOutToBlack_BT_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,200);

        FadeOutToWhite_TB_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,200);

        FadeOutToBlack_RL18_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_LR18_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_LR18_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_RL18_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FillScreenWithGarbage_R(0x978FC6AB,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
        FillScreenWithGarbage_R(0x45DA1328,LCD_SIZE,GrayGetPlane(DARK_PLANE));

        FadeOutToBlack_RL28_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_LR28_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_LR28_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FillScreenWithGarbage_R(0x978FC6AB,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
        FillScreenWithGarbage_R(0x45DA1328,LCD_SIZE,GrayGetPlane(DARK_PLANE));

        FadeOutToWhite_RL28_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,30,20);

        FillScreenWithGarbage_R(0x978FC6AB,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
        FillScreenWithGarbage_R(0x45DA1328,LCD_SIZE,GrayGetPlane(DARK_PLANE));


        // Test *ShadowPlanes functions
        WAIT

        GrayIShadowPlanes240_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128); WAIT
        GrayShadowPlanes240_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128); WAIT

        GrayShadowPlanesX16_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,15); WAIT
        GrayIShadowPlanesX16_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,15);
        
        WAIT

        FillScreenWithGarbage_R(0x978FC6AB,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
        FillScreenWithGarbage_R(0x45DA1328,LCD_SIZE,GrayGetPlane(DARK_PLANE));

        WAIT

        GrayShadowPlanes160_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128);
        WAIT
        GrayIShadowPlanes160_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128);
        WAIT

        GrayIShadowPlanesTo_R(GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE), GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE));
        WAIT
        GrayShadowPlanesTo_R(GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE), GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE));


        // Test Clear/FillScreen functions
        WAIT

        FastFillScreen_R(GrayGetPlane(DARK_PLANE));
        FastFillScreen_R(GrayGetPlane(LIGHT_PLANE));
        WAIT

        FastClearScreen_R(GrayGetPlane(DARK_PLANE));
        WAIT

        FastFillScreen_R(GrayGetPlane(DARK_PLANE));
        FastClearScreen_R(GrayGetPlane(LIGHT_PLANE));
        WAIT

        FastClearScreen_R(GrayGetPlane(LIGHT_PLANE));
        WAIT


        // Test SpriteX8Data_withmask_* functions
        FastFillScreen_R(GrayGetPlane(DARK_PLANE));
        FastFillScreen_R(GrayGetPlane(LIGHT_PLANE));
        WAIT
        val = 0x01;
        for (j = 0; j < 4; j++) {
            memset((void *)mask, ~val, sizeof(mask));
            SpriteX8Data_withmask_AND_R(128, 30, GrayGetPlane(DARK_PLANE), mask, GrayGetPlane(DARK_PLANE));
            WAIT
            val <<= 2;
        }
        val = 0x02;
        for (j = 0; j < 4; j++) {
            memset((void *)mask, ~val, sizeof(mask));
            SpriteX8Data_withmask_AND_R(128, 30, GrayGetPlane(LIGHT_PLANE), mask, GrayGetPlane(LIGHT_PLANE));
            WAIT
            val <<= 2;
        }

        val = 0x01;
        for (j = 0; j < 4; j++) {
            memset((void *)mask, val, sizeof(mask));
            SpriteX8Data_withmask_OR_R(128, 30, GrayGetPlane(DARK_PLANE), mask, GrayGetPlane(DARK_PLANE));
            WAIT
            val <<= 2;
        }
        val = 0x02;
        for (j = 0; j < 4; j++) {
            memset((void *)mask, val, sizeof(mask));
            SpriteX8Data_withmask_OR_R(128, 30, GrayGetPlane(LIGHT_PLANE), mask, GrayGetPlane(LIGHT_PLANE));
            WAIT
            val <<= 2;
        }

        val = 0x01;
        for (j = 0; j < 4; j++) {
            memset((void *)mask, val, sizeof(mask));
            SpriteX8Data_withmask_XOR_R(128, 30, GrayGetPlane(LIGHT_PLANE), mask, GrayGetPlane(LIGHT_PLANE));
            WAIT
            val <<= 2;
        }
        val = 0x02;
        for (j = 0; j < 4; j++) {
            memset((void *)mask, val, sizeof(mask));
            SpriteX8Data_withmask_XOR_R(128, 30, GrayGetPlane(DARK_PLANE), mask, GrayGetPlane(DARK_PLANE));
            WAIT
            val <<= 2;
        }
    }

    GrayOff();

    // Test Fast(AND|OR|XOR)Screen_R functions
    LCD_restore(backbuffer);
    WAIT WAIT
    FastXORScreen_R(backbuffer, LCD_MEM+2);
    WAIT WAIT
    FastXORScreen_R(backbuffer, LCD_MEM);
    WAIT WAIT
    FastORScreen_R(backbuffer, LCD_MEM+2);
    WAIT WAIT
    FastORScreen_R(backbuffer, LCD_MEM);
    WAIT WAIT
    FastXORScreen_R(backbuffer, LCD_MEM+2);
    WAIT WAIT WAIT
    FastFillScreen_R(LCD_MEM);
    FastInvertScreen_R(backbuffer);
    WAIT WAIT
    FastANDScreen_R(backbuffer, LCD_MEM);
    WAIT WAIT
    
    FastInvertScreen_R(backbuffer);
    LCD_restore(backbuffer);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
