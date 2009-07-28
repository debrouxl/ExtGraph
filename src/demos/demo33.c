/******************************************************************************
*
* project name:    ExtGraph
* initial date:    12/04/2001
* author:          thomas.nussbaumer@gmx.net
* description:     test program for GrayClipLine and GrayStr functions
*
* $Id: demo33.c,v 1.4 2002/02/22 15:06:14 tnussb Exp $
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

#define INITIAL_TIMER_VALUE (100000*20UL)

/*===========================================================================*/
/* main routine: where all the fun starts ...                                */
/*===========================================================================*/
void _main(void) {
    short         i,j;
    unsigned long measure_val;
    char          tmpstr[50] = "Measuring, please wait ...";
    static const short modes[4] = {COLOR_LIGHTGRAY,COLOR_DARKGRAY,COLOR_BLACK,COLOR_WHITE};
    unsigned short clippedcoord[4];
    LCD_BUFFER    screen;

    LCD_save(screen);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,INITIAL_TIMER_VALUE);

    if (!GrayOn()) goto end;

    //---------------------------------------------------------------------
    // built-in OS line drawing routine ...
    //---------------------------------------------------------------------
    GrayClearScreen_R();
    OSTimerRestart(USER_TIMER);
    for (j=0;j<4;j++) {
        short used_color = modes[j];
        for (i=-40;  i<280;i++) GrayDrawClipLine(120,64,i,-40,used_color);
        for (i=-40;  i<168;i++) GrayDrawClipLine(120,64,280,i,used_color);
        for (i=280;i>=-40; i--) GrayDrawClipLine(120,64,i,168,used_color);
        for (i=168;i>=-40; i--) GrayDrawClipLine(120,64,-40,i,used_color);
    }
    measure_val = OSTimerCurVal(USER_TIMER);
    sprintf(tmpstr,"OS routine took %lu ticks",INITIAL_TIMER_VALUE-measure_val);
    GrayDrawRect(0,0,239,7,COLOR_WHITE,RECT_FILLED);
    GrayDrawStrExt(0,0,tmpstr,A_NORMAL | A_CENTERED | A_SHADOWED,F_4x6);

    if (ngetchx() == KEY_ESC) goto end;

    
    //---------------------------------------------------------------------
    // new line drawing routine ...
    //---------------------------------------------------------------------
    GrayClearScreen_R();
    OSTimerRestart(USER_TIMER);
    for (j=0;j<4;j++) {
        short used_color = modes[j];
        for (i=-40;  i<280;i++) GrayClipDrawLine_R(120,64,i,-40,clippedcoord,used_color,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),GrayFastDrawLine2B_R);
        for (i=-40;  i<280;i++) GrayClipDrawLine_R(120,64,280,i,clippedcoord,used_color,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),GrayFastDrawLine2B_R);
        for (i=280;i>=-40; i--) GrayClipDrawLine_R(120,64,i,168,clippedcoord,used_color,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),GrayFastDrawLine2B_R);
        for (i=168;i>=-40; i--) GrayClipDrawLine_R(120,64,-40,i,clippedcoord,used_color,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),GrayFastDrawLine2B_R);
    }
    measure_val = OSTimerCurVal(USER_TIMER);
    sprintf(tmpstr,"Own routine took %lu ticks",INITIAL_TIMER_VALUE-measure_val);
    GrayDrawRect(0,0,239,7,COLOR_WHITE,RECT_FILLED);
    GrayDrawStrExt(0,0,tmpstr,A_NORMAL | A_CENTERED | A_SHADOWED,F_4x6);

    if (ngetchx() == KEY_ESC) goto end;


    GrayOff();
    ClrScr();
    //---------------------------------------------------------------------
    // built-in OS line drawing routine ...
    //---------------------------------------------------------------------
    OSTimerRestart(USER_TIMER);
    for (j=0;j<4;j++) {
        WIN_RECT rect = {120, 64, 0, -40};
        for (i=-40;  i<280;i++) {rect.x1 = i; DrawClipLine(&rect,&(SCR_RECT){{0, 0, 239, 127}},A_XOR); }
        for (i=-40;  i<168;i++) {rect.y1 = i; DrawClipLine(&rect,&(SCR_RECT){{0, 0, 239, 127}},A_XOR); }
        for (i=280;i>=-40; i--) {rect.x1 = i; DrawClipLine(&rect,&(SCR_RECT){{0, 0, 239, 127}},A_XOR); }
        for (i=168;i>=-40; i--) {rect.y1 = i; DrawClipLine(&rect,&(SCR_RECT){{0, 0, 239, 127}},A_XOR); }
    }
    measure_val = OSTimerCurVal(USER_TIMER);
    sprintf(tmpstr,"OS routine took %lu ticks",INITIAL_TIMER_VALUE-measure_val);
    GrayDrawRect2B(0,0,239,7,COLOR_WHITE,RECT_FILLED,LCD_MEM,LCD_MEM);
    GrayDrawStrExt2B(0,0,tmpstr,A_NORMAL | A_CENTERED,F_4x6,LCD_MEM,LCD_MEM);

    if (ngetchx() == KEY_ESC) goto end;

    //---------------------------------------------------------------------
    // new line drawing routine ...
    //---------------------------------------------------------------------
    ClrScr();
    OSTimerRestart(USER_TIMER);
    for (j=0;j<4;j++) {
        for (i=-40;  i<280;i++) ClipDrawLine_R(120,64,i,-40,clippedcoord,A_XOR,LCD_MEM,FastDrawLine_R);
        for (i=-40;  i<280;i++) ClipDrawLine_R(120,64,280,i,clippedcoord,A_XOR,LCD_MEM,FastDrawLine_R);
        for (i=280;i>=-40; i--) ClipDrawLine_R(120,64,i,168,clippedcoord,A_XOR,LCD_MEM,FastDrawLine_R);
        for (i=168;i>=-40; i--) ClipDrawLine_R(120,64,-40,i,clippedcoord,A_XOR,LCD_MEM,FastDrawLine_R);
    }
    measure_val = OSTimerCurVal(USER_TIMER);
    sprintf(tmpstr,"Own routine took %lu ticks",INITIAL_TIMER_VALUE-measure_val);
    GrayDrawRect2B(0,0,239,7,COLOR_WHITE,RECT_FILLED,LCD_MEM,LCD_MEM);
    GrayDrawStrExt2B(0,0,tmpstr,A_NORMAL | A_CENTERED,F_4x6,LCD_MEM,LCD_MEM);

    ngetchx();

    end:
    OSFreeTimer(USER_TIMER);
    GrayOff();
    LCD_restore(screen);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo7.c,v $
// Revision 1.4  2002/02/22 15:06:14  tnussb
// outputs now the "powered by ExtGraph" string at the end of the program
//
// Revision 1.3  2002/02/11 11:33:09  tnussb
// (1) uses now USE_TI89/USE_TI92P directives (Lionel Debroux)
// (2) unnecessary saving/restoring of original screen removed (Lionel Debroux)
// (3) missing history added to end of file
//
// Revision 1.2  2002/02/11 10:14:26  tnussb
// compiler directives NO_EXIT_SUPPORT and OPTIMIZE_ROM_CALLS added
//
// Revision 1.1  2001/06/20 21:50:19  tnussb
// initial check-in
//
