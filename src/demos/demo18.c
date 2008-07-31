#define NO_EXIT_SUPPORT
#define MIN_AMS 100
#define NO_AMS_CHECK
#define NO_CALC_DETECT
#include <tigcclib.h>         // Include All Header Files
#include "../../lib/extgraph.h"


// Main Function
void _main(void) {
    LCD_BUFFER backbuffer;

    LCD_save(backbuffer);

    if(GrayOn()) {
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

        asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        GrayIShadowPlanes240_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128); asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");
        GrayShadowPlanes240_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128); asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        GrayShadowPlanesX16_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,15); asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");
        GrayIShadowPlanesX16_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128,15);
        
        asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        FillScreenWithGarbage_R(0x978FC6AB,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
        FillScreenWithGarbage_R(0x45DA1328,LCD_SIZE,GrayGetPlane(DARK_PLANE));

        asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        GrayShadowPlanes160_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128); asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");
        GrayIShadowPlanes160_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),128); asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        GrayIShadowPlanesTo_R(GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE), GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE)); asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");
        GrayShadowPlanesTo_R(GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE), GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE));

        asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        FastFillScreen_R(GrayGetPlane(DARK_PLANE));
        FastFillScreen_R(GrayGetPlane(LIGHT_PLANE));
        asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        FastClearScreen_R(GrayGetPlane(DARK_PLANE));
        asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        FastFillScreen_R(GrayGetPlane(DARK_PLANE));
        FastClearScreen_R(GrayGetPlane(LIGHT_PLANE));
        asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");

        FastClearScreen_R(GrayGetPlane(LIGHT_PLANE));
        asm volatile("move.l #0x4FFFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");
    }

    GrayOff();
    LCD_restore(backbuffer);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
