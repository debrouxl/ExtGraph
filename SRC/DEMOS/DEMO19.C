#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS

#define NO_AMS_CHECK
#define NO_CALC_DETECT
#define MIN_AMS 100

#include <tigcclib.h>         // Include All Header Files
#include "../../lib/extgraph.h"


#define NR_LOOPS         4
#define RANDOM_TRIANGLES 2500
#define RANDOM_CIRCLES 1000


short* x = NULL;
short* y = NULL;

//=============================================================================
// allocate and initialize global points arrays with "random" values
//=============================================================================
static inline short InitArrays(void) {
    unsigned short i;
    short *px, *py;
    x = y = NULL;
    if (!(x = (short*)malloc(RANDOM_TRIANGLES*3*sizeof(short)*2))) return 0;
    y = x+RANDOM_TRIANGLES*3;
//    if (!(y = (short*)malloc(RANDOM_TRIANGLES*3*sizeof(short)))) return 0;

    srand(0x00000000UL); // always start on same seed
    px = &x[0];
    py = &y[0];
    for (i=0;i<RANDOM_TRIANGLES*3;i++) {
       *px++ = (random(150)+5);
       *py++ = random(90)+5;
    }
    return 1;
}


//=============================================================================
// free the allocate global points arrays
//=============================================================================
static inline void CleanupArrays(void) {
    if (x) free(x);
//    if (y) free(y);
}


// Main Function
void _main(void) {
    LCD_BUFFER screen;
    short i,j,k;
    unsigned char tmpstr[100];

    LCD_save(screen);

    // B/W rectangles. Commented out because I find it a bit redundant with the
    // next one, although it shows a difference between FastFillRect_R and
    // FastFilledRect_Invert_R.
/*
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
*/


    // Grayscale filled rectangles.
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

    sprintf(tmpstr,"orig: %lu AI5 ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
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
    sprintf(tmpstr,"opt: %lu AI5 ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    ngetchx();



    // Grayscale outlined rectangles.
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

    sprintf(tmpstr,"orig: %lu AI5 ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
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
    sprintf(tmpstr,"opt: %lu AI5 ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    ngetchx();

    GrayOff();


    // B/W triangles.
    ClrScr();
    if (!InitArrays()) {
        CleanupArrays();
        ST_helpMsg("error: out of mem");
        goto end;
    }
    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,100000*20UL);
    for (j=0;j<NR_LOOPS;j++) {
        for (i=0;i<RANDOM_TRIANGLES*3;i+=3) {
            ClipFilledTriangle_INVERT_R(x[0+i],y[0+i],x[1+i],y[1+i],x[2+i],y[2+i],LCD_MEM);
        }
    }
    sprintf(tmpstr,"opt: %lu AI5 ticks for 10000 triangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    CleanupArrays();
    ST_helpMsg(tmpstr);
    ngetchx();


    // B/W circles.
    ClrScr();
    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,100000*20UL);
    srand(0);
    for (j=0;j<NR_LOOPS;j++) {
        for (i=0;i<RANDOM_CIRCLES*3;i+=3) {
            k = random(15)+20;
            DrawClipEllipse(random(160),random(160),k,k,&(SCR_RECT){{0,0,239,127}},A_NORMAL);
        }
    }
    sprintf(tmpstr,"orig: %lu AI5 ticks for 4000 circles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    ngetchx();

    ClrScr();
    OSTimerRestart(USER_TIMER);
    srand(0);
    for (j=0;j<NR_LOOPS;j++) {
        for (i=0;i<RANDOM_CIRCLES*3;i+=3) {
            k = random(15)+20;
            ClipFastOutlinedCircle_DRAW_R(LCD_MEM,random(160),random(160),k);
        }
    }
    sprintf(tmpstr,"opt: %lu AI5 ticks for 4000 circles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    ngetchx();


    OSFreeTimer(USER_TIMER);

    end:
    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
