#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS

#define NO_AMS_CHECK
#define NO_CALC_DETECT
#define MIN_AMS 100

#include <tigcclib.h>         // Include All Header Files
#include "../../lib/extgraph.h"


// Main Function
void _main(void) {
    LCD_BUFFER screen;
    short i,j,k;
    unsigned char tmpstr[100];

    LCD_save(screen);

    ClrScr();
    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            SCR_RECT s = {{0,0,i,j}};
            ScrRectFill(&s,&(SCR_RECT){{0,0,239,127}},A_XOR);
        }
        k--;
        if (k < 0) break;
    }

    sprintf(tmpstr,"orig: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER))*50);
    ST_helpMsg(tmpstr);
    ngetchx();

    ClrScr();
    OSTimerRestart(USER_TIMER);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            FastFillRect_R(LCD_MEM,0,0,i,j,A_XOR);
        }
        k--;
        if (k < 0) break;
    }
    sprintf(tmpstr,"opt1: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER))*50);
    ST_helpMsg(tmpstr);
    ngetchx();

    ClrScr();
    OSTimerRestart(USER_TIMER);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            FastFilledRect_Invert_R(LCD_MEM,0,0,i,j);
        }
        k--;
        if (k < 0) break;
    }
    sprintf(tmpstr,"opt2: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER))*50);
    ST_helpMsg(tmpstr);
    GKeyFlush();
    ngetchx();



    if(!GrayOn()) goto end;

    GrayClearScreen();
    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            GrayDrawRect(0,0,i,j,random(4),RECT_FILLED);
        }
        k--;
        if (k < 0) break;
    }

    sprintf(tmpstr,"orig: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER))*50);
    ST_helpMsg(tmpstr);
    ngetchx();

    GrayClearScreen();
    OSTimerRestart(USER_TIMER);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            GrayFastFillRect_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),0,0,i,j,random(4));
        }
        k--;
        if (k < 0) break;
    }
    sprintf(tmpstr,"opt: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER))*50);
    ST_helpMsg(tmpstr);
    ngetchx();



    GrayClearScreen();
    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            GrayDrawRect(0,0,i,j,random(4),RECT_EMPTY);
        }
        k--;
        if (k < 0) break;
    }

    sprintf(tmpstr,"orig: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER))*50);
    ST_helpMsg(tmpstr);
    ngetchx();

    GrayClearScreen();
    OSTimerRestart(USER_TIMER);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            GrayFastOutlineRect_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),0,0,i,j,random(4));
        }
        k--;
        if (k < 0) break;
    }
    sprintf(tmpstr,"opt: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER))*50);
    ST_helpMsg(tmpstr);
    ngetchx();

    GrayOff();

    end:
    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
