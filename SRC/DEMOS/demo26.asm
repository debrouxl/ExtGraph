; Assembler- and linker-side optimization are completely disabled.
; Branches to the ExtGraph routines are relocated jsr.l, like 
; branches to graphlib routines. lea LCD_MEM,a0 is long, too.

; The header in TIGCCLIB.
	INCLUDE "os.h"
; The header in PreOS.
	include "graphlib.h"
; The header in Genlib. I planned on adding Genlib to the bench, but
; the bench would be unfair, as Genlib is nearly grayscale-only...
;	include "genlib.h"
	xdef	_ti89
	xdef	_ti89ti ; Symbol is undefined but used in the documentation of GenLib ?!
	xdef	_ti92plus
	xdef	v200 ; Symbol is undefined but used in the documentation of GenLib ?!
	xdef	_main
_ti89ti
;_ti89
;_ti92plus
v200
_main:
    movem.l  d3-d7/a2-a6,-(sp)
    move.l   $C8,a5

; We need AMS 2.xx due to push_ulong_to_integer, which defacto prevents
; PedroM from running this program, until PpHd implements that function.
    cmpi.l   #push_ulong_to_integer,-4(a5)
    blt      _end
    
;   ClrScr();
    move.l   ClrScr*4(a5),a0
    jsr      (a0)
    
;   OSFreeTimer(USER_TIMER);
    move.w   #6,-(sp)
    move.l   OSFreeTimer*4(a5),a0
    jsr      (a0)
    
;   OSRegisterTimer(USER_TIMER,10000*20UL);
    pea      10000*20
    move.w   #6,-(sp)
    move.l   OSRegisterTimer*4(a5),a0
    jsr      (a0)
    
; Compare generic line functions.
    move.w   #5000,d4
_loop_FastLine_Draw_:
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    lea      LCD_MEM,a0
    jsr.l    FastLine_Draw_R
    
    dbf      d4,_loop_FastLine_Draw_
    
;   t1 = 10000*20UL - OSTimerCurVal(USER_TIMER);
    move.w   #6,(sp)
    move.l   OSTimerCurVal*4(a5),a3
    jsr      (a3)
    move.l   #10000*20,d1
    sub.l    d0,d1
    
    lea      storage(pc),a2
    move.l   d1,(a2)+
    

;   OSTimerRestart(USER_TIMER);
    move.w   #6,(sp)
    move.l   OSTimerRestart*4(a5),a4
    jsr      (a4)
    
    move.w   #5000,d4
_loop_graphlib_line_:
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    lea      LCD_MEM,a0
    jsr.l    graphlib::line
    
    dbf      d4,_loop_graphlib_line_
    
;   t1 = 10000*20UL - OSTimerCurVal(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a3)
    move.l   #10000*20,d1
    sub.l    d0,d1
    
    move.l   d1,(a2)+
    
;   OSTimerRestart(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a4)



; Compare horizontal line functions.
    move.w   #20000,d4
_loop_FastDrawHLine_:
    move.w   #1,(sp)
    moveq    #0,d2
    move.w   #159,d1
    moveq    #0,d0
    lea      LCD_MEM,a0
    jsr.l    FastDrawHLine_R
    
    dbf      d4,_loop_FastDrawHLine_
    
;   t1 = 10000*20UL - OSTimerCurVal(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a3)
    move.l   #10000*20,d1
    sub.l    d0,d1
    
    move.l   d1,(a2)+
    

;   OSTimerRestart(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a4)
    
    move.w   #20000,d5
_loop_graphlib_horiz_:
    moveq    #2,d4
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    lea      LCD_MEM,a0
    jsr.l    graphlib::horiz
    
    dbf      d5,_loop_graphlib_horiz_
    
;   t1 = 10000*20UL - OSTimerCurVal(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a3)
    move.l   #10000*20,d1
    sub.l    d0,d1
    
    move.l   d1,(a2)+

;   OSTimerRestart(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a4)




; Compare vertical line functions.
    move.w   #10000,d4
_loop_FastDrawVLine_:
    move.w   #1,(sp)
    moveq    #99,d2
    move.w   #0,d1
    moveq    #0,d0
    lea      LCD_MEM,a0
    jsr.l    FastDrawVLine_R
    
    dbf      d4,_loop_FastDrawVLine_
    
;   t1 = 10000*20UL - OSTimerCurVal(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a3)
    move.l   #10000*20,d1
    sub.l    d0,d1
    
    move.l   d1,(a2)+
    

;   OSTimerRestart(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a4)
    
    move.w   #10000,d5
_loop_graphlib_vert_:
    moveq    #99,d2
    move.w   #0,d1
    moveq    #0,d0
    lea      LCD_MEM,a0
    jsr.l    graphlib::vert
    
    dbf      d5,_loop_graphlib_vert_
    
;   t1 = 10000*20UL - OSTimerCurVal(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a3)
    move.l   #10000*20,d1
    sub.l    d0,d1
    
    move.l   d1,(a2)+

;   OSTimerRestart(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a4)





; Compare rectangle functions.
    move.w   #1000,d4
_loop_FastFillRect_:
    move.w   #1,(sp)
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    lea      LCD_MEM,a0
    jsr.l    FastFillRect_R
    
    dbf      d4,_loop_FastFillRect_
    
;   t1 = 10000*20UL - OSTimerCurVal(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a3)
    move.l   #10000*20,d1
    sub.l    d0,d1
    
    move.l   d1,(a2)+
    

;   OSTimerRestart(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a4)
    
    move.w   #1000,d5
_loop_graphlib_fill_:
    moveq    #2,d4
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    lea      LCD_MEM,a0
    jsr.l    graphlib::fill
    
    dbf      d5,_loop_graphlib_fill_
    
;   t1 = 10000*20UL - OSTimerCurVal(USER_TIMER);
    move.w   #6,(sp)
    jsr      (a3)
    move.l   #10000*20,d1
    sub.l    d0,d1
    
    move.l   d1,(a2)+
    


;   OSFreeTimer(USER_TIMER);
    move.w   #6,(sp)
    move.l   OSFreeTimer*4(a5),a0
    jsr      (a0)
    
    move.l   push_END_TAG*4(a5),a0
    jsr      (a0)

    move.l   push_ulong_to_integer*4(a5),a3
    moveq    #8-1,d3
_push_values_:
    move.l   -(a2),(sp)
    jsr      (a3)
    dbf      d3,_push_values_
    
    move.l   push_LIST_TAG*4(a5),a0
    jsr      (a0)
    
; Non-standard way to return expressions on the EStack...
    move.l   top_estack*4(a5),a0
    move.l   (a0),_RAM_CALL_F


    addq.l   #8,sp

_end:
    movem.l  (sp)+,d3-d7/a2-a6
    rts
    
    

	xdef storage
storage: ds.b 4*8
;storage: ds.b 4*12
