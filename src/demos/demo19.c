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

extern void * __gray_used_mem;

//=============================================================================
// allocate and initialize global points arrays with "random" values
//=============================================================================
static inline short InitArrays(void) {
    unsigned short i;
    short *px, *py;
    x = y = NULL;
    if (!(x = (short*)malloc(RANDOM_TRIANGLES*3*sizeof(short)*2))) return 0;
    y = x+RANDOM_TRIANGLES*3;

    srand(0x00000000UL); // always start on same seed
    px = &x[0];
    py = &y[0];
    for (i=0;i<RANDOM_TRIANGLES*3;i++) {
       *px++ = random(150)+5;
       *py++ = random(90)+5;
    }
    return 1;
}


//=============================================================================
// free the allocate global points arrays
//=============================================================================
static inline void CleanupArrays(void) {
    free(x);
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

    sprintf(tmpstr,"AMS: %lu ticks for 4371 rectangles",100000*20UL-OSTimerCurVal(USER_TIMER));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;

    ClrScr();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            FastFillRect_R(LCD_MEM,0,0,i,j,A_XOR);
        }
        k--;
        if (k < 0) break;
    }
    sprintf(tmpstr,"ExtGraph1: %lu ticks for 4371 rectangles",100000*20UL-OSTimerCurVal(USER_TIMER));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;

    ClrScr();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            FastFilledRect_Invert_R(LCD_MEM,0,0,i,j);
        }
        k--;
        if (k < 0) break;
    }
    sprintf(tmpstr,"ExtGraph2: %lu ticks for 4371 rectangles",100000*20UL-OSTimerCurVal(USER_TIMER));
    ST_helpMsg(tmpstr);
    GKeyFlush();
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;
*/

    // Grayscale filled rectangles.
    if(!GrayOn()) goto end;

    GrayClearScreen();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            GrayDrawRect(0,0,i,j,random(4),RECT_FILLED);
        }
        k--;
        if (k < 0) break;
    }

    GrayOff();
    sprintf(tmpstr,"AMS: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;

    if(!GrayOn()) goto end;
    GrayClearScreen();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            GrayFastFillRect_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),0,0,i,j,random(4));
        }
        k--;
        if (k < 0) break;
    }
    GrayOff();
    sprintf(tmpstr,"ExtGraph1: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;



    // Grayscale outlined rectangles.
    if(!GrayOn()) goto end;
    GrayClearScreen();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            GrayDrawRect(0,0,i,j,random(4),RECT_EMPTY);
        }
        k--;
        if (k < 0) break;
    }

    GrayOff();
    sprintf(tmpstr,"AMS: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;

    if(!GrayOn()) goto end;
    GrayClearScreen();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    k = 92;
    for (i = 159-0+1; (i--);) {
        for (j = k-0+1; (j--);) {
            GrayFastOutlineRect_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),0,0,i,j,random(4));
        }
        k--;
        if (k < 0) break;
    }
    GrayOff();
    sprintf(tmpstr,"ExtGraph: %lu ticks for 4371 rectangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;



    // B/W triangles.
    ClrScr();
    if (!InitArrays()) {
        CleanupArrays();
        ST_helpMsg("error: out of mem");
        goto end;
    }
    OSRegisterTimer(USER_TIMER,100000*20UL);
    for (j=0;j<NR_LOOPS;j++) {
        for (i=0;i<RANDOM_TRIANGLES*3;i+=3) {
            FilledTriangle_R(x[0+i],y[0+i],x[1+i],y[1+i],x[2+i],y[2+i],LCD_MEM,DrawSpan_XOR_R);
        }
    }
    sprintf(tmpstr,"ExtGraph: %lu ticks for 2500 triangles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    CleanupArrays();
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;



    // B/W outlined circles.
    ClrScr();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    srand(0);
    for (i=0;i<RANDOM_CIRCLES*3;i++) {
        k = random(15)+20;
        DrawClipEllipse(random(240),random(128),k,k,&(SCR_RECT){{0,0,239,127}},A_XOR);
    }
    sprintf(tmpstr,"AMS: %lu ticks for 750 circles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    if (ngetchx() == KEY_ESC) goto end;

    ClrScr();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    srand(0);
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        ClipFastOutlinedCircle_INVERT_R(LCD_MEM,random(240),random(128),k);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        ClipFastOutlinedCircle_DRAW_R(LCD_MEM,random(240),random(128),k);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        ClipFastOutlinedCircle_ERASE_R(LCD_MEM,random(240),random(128),k);
    }
    sprintf(tmpstr,"ExtGraph: %lu ticks for 750 circles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    ngetchx();



    // B/W filled circles.
    ClrScr();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    srand(0);
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        ClipFastFilledCircle_R(LCD_MEM,random(240),random(128),k,DrawSpan_XOR_R);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        ClipFastFilledCircle_R(LCD_MEM,random(240),random(128),k,DrawSpan_OR_R);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        ClipFastFilledCircle_R(LCD_MEM,random(240),random(128),k,DrawSpan_REVERSE_R);
    }
    sprintf(tmpstr,"ExtGraph: %lu ticks for 750 circles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    ngetchx();



    // Grayscale outlined circles.
    if(!GrayOn()) goto end;

    GrayClearScreen_R();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    srand(0);
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastOutlinedCircle_INVERT_R(__gray_used_mem,random(240),random(128),k);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastOutlinedCircle_WHITE_R(__gray_used_mem,random(240),random(128),k);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastOutlinedCircle_LGRAY_R(__gray_used_mem,random(240),random(128),k);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastOutlinedCircle_DGRAY_R(__gray_used_mem,random(240),random(128),k);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastOutlinedCircle_BLACK_R(__gray_used_mem,random(240),random(128),k);
    }
    GrayOff();
    sprintf(tmpstr,"ExtGraph: %lu ticks for 1250 circles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    ngetchx();



    // Grayscale filled circles.
    if(!GrayOn()) goto end;
    GrayClearScreen();
    OSRegisterTimer(USER_TIMER,100000*20UL);
    srand(0);
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastFilledCircle_R(__gray_used_mem,random(240),random(128),k,GrayDrawSpan_INVERT_R);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastFilledCircle_R(__gray_used_mem,random(240),random(128),k,GrayDrawSpan_WHITE_R);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastFilledCircle_R(__gray_used_mem,random(240),random(128),k,GrayDrawSpan_LGRAY_R);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastFilledCircle_R(__gray_used_mem,random(240),random(128),k,GrayDrawSpan_DGRAY_R);
    }
    for (i=0;i<RANDOM_CIRCLES;i++) {
        k = random(15)+20;
        GrayClipFastFilledCircle_R(__gray_used_mem,random(240),random(128),k,GrayDrawSpan_BLACK_R);
    }
    GrayOff();
    sprintf(tmpstr,"ExtGraph: %lu ticks for 1250 circles",(100000*20UL-OSTimerCurVal(USER_TIMER)));
    ST_helpMsg(tmpstr);
    OSFreeTimer(USER_TIMER);
    ngetchx();


    end:
    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
