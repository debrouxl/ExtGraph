; Assembler- and linker-side optimization are not enabled.
; Branches to the ExtGraph routines are therefore
; relocated jsr.l, like branches to graphlib routines.

;	INCLUDE "os.h"
; The header in PreOS, recommended for kernel-based programming by PpHd ("os.h is outdated").
; I don't care whether it is supported by Kevin or not.
	INCLUDE "tios.h"
; The header in PreOS.
	include "graphlib.h"
; The header in Genlib.
	include "genlib.h"
	xdef	_ti89
	xdef	_ti89ti
	xdef	_ti92plus
	xdef	_v200
	xdef	_main

TIMER_VALUE equ 100*20
NR_GENERIC_LINES equ 5000
NR_HORIZ_LINES equ 20000
NR_FILLED_RECT equ 1000
NR_FILLED_TRIA equ 1000
NR_RESULTS equ 4

FreeTimer:
;   OSFreeTimer(USER_TIMER);
    move.w   #6,-(sp)
    move.l   $F1*4(a5),a0
    jsr      (a0)
    addq.l   #2,sp
    rts

TimerCurVal:
;   t1 = TIMER_VALUE - OSTimerCurVal(USER_TIMER);
    move.w   #6,-(sp)
    jsr      (a3)
    move.l   #TIMER_VALUE,d1
    sub.l    d0,d1
    move.l   d1,(a2)+
    addq.l   #2,sp
    rts

TimerRestart:
;   OSTimerRestart(USER_TIMER);
    move.w   #6,-(sp)
    jsr      (a4)
    addq.l   #2,sp
    rts

_main:
    movem.l  d3-d7/a2-a6,-(sp)
    move.l   $C8,a5

; We need AMS 2.xx due to push_ulong_to_integer, which defacto prevents
; PedroM from running this program, until PpHd implements that function.
    cmpi.l   #$4E4,-4(a5)
    blt      _end
    tst.l    $4E4*4(a5)
    beq      _end

    lea      _storage(pc),a2
    move.l   $F2*4(a5),a3
    move.l   $F4*4(a5),a4

    bsr      FreeTimer

;   OSRegisterTimer(USER_TIMER,TIMER_VALUE);
    pea      TIMER_VALUE
    move.w   #6,-(sp)
    move.l   $F0*4(a5),a0
    jsr      (a0)
    addq.l   #6,sp


; Test parameter.
    move.l   $109*4(a5),a0 ; top_estack
    move.l   (a0),a0
    cmpi.b   #$E5,(a0)
    beq      _bench_ExtGraph ; Bench ExtGraph if nothing is passed.
    cmpi.b   #$1F,(a0)
    beq      _test_1F        ; Test the integer value.
    cmpi.b   #$20,(a0)
    bne      _bench_ExtGraph ; Bench ExtGraph if anything else than an integer is passed.
    bra      _bench_Graphlib ; Bench Graphlib if a negative integer is passed.
_test_1F:
    tst.b    -(a0)
    beq      _bench_ExtGraph ; Bench ExtGraph if passed integer 0
    bra      _bench_Genlib   ; Bench Genlib if a strictly positive integer is passed.
        
_bench_ExtGraph:
    jsr.l    GrayOn
    tst.w    d0
    beq      _bench_end


; Clear both planes.
    move.l   __L_plane,a0
    move.l   __D_plane,a1
    jsr      GrayClearScreen2B_R


; Generic line function.
    move.w   #NR_GENERIC_LINES,d5
_loop_GFDL2B_R_:
    move.w   #3,(sp)
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    moveq    #0,d0
    move.l   __L_plane,a0
    move.l   __D_plane,a1
    jsr.l    GrayFastDrawLine2B_R
    
    dbf      d5,_loop_GFDL2B_R_

    bsr      TimerCurVal
    bsr      TimerRestart


; Horizontal line function.
    move.w   #NR_HORIZ_LINES,d5
_loop_GFDHL2B_R_:
    move.w   #3,(sp)
    moveq    #0,d2
    move.w   #159,d1
    moveq    #0,d0
    movea.l  __L_plane,a0
    movea.l  __D_plane,a1
    jsr.l    GrayFastDrawHLine2B_R
    
    dbf      d5,_loop_GFDHL2B_R_
    
    bsr      TimerCurVal
    bsr      TimerRestart


; Rectangle filling function.
    move.w   #NR_FILLED_RECT,d5
_loop_GFFR_R_:
    move.w   #3,(sp)
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    movea.l  __L_plane,a0
    movea.l  __D_plane,a1
    jsr.l    GrayFastFillRect_R
    
    dbf      d5,_loop_GFFR_R_
    
    bsr      TimerCurVal
    bsr      TimerRestart


; Triangle filling function.
;    move.w   #NR_FILLED_TRIA,d5
;_loop_GFFR_R_:
;    move.w   #3,(sp)
;    moveq    #99,d3
;    move.w   #159,d2
;    moveq    #0,d1
;    move.l   d1,d0
;    movea.l  __L_plane,a0
;    movea.l  __D_plane,a1
;    jsr.l    GrayFastFillRect_R
    
;    dbf      d5,_loop_GFFR_R_
    
;    bsr      TimerCurVal


    jsr.l    GrayOff

    bra      ReturnResults




_bench_Graphlib:
    jsr.l    graphlib::gray4
    tst.w    d0
    beq      _bench_end

    move.w   #1,graphlib::choosescreen

; Generic line function.
    move.w   #NR_GENERIC_LINES,d5
_loop_graphlib_line_:
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    movea.l  graphlib::plane0,a0
    jsr.l    graphlib::line

    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    movea.l  graphlib::plane1,a0
    jsr.l    graphlib::line
    
    dbf      d5,_loop_graphlib_line_
    
    bsr      TimerCurVal
    bsr      TimerRestart


; Horizontal line function.
    move.w   #NR_HORIZ_LINES,d5
_loop_graphlib_horiz_:
    moveq    #2,d4
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    movea.l  graphlib::plane0,a1
    jsr.l    graphlib::horiz

    moveq    #2,d4
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    movea.l  graphlib::plane1,a1
    jsr.l    graphlib::horiz
    
    dbf      d5,_loop_graphlib_horiz_
    
    bsr      TimerCurVal
    bsr      TimerRestart

    
; Rectangle filling function.
    move.w   #NR_FILLED_RECT,d5
_loop_graphlib_fill_:
    moveq    #2,d4
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    movea.l  graphlib::plane0,a1
    jsr.l    graphlib::fill

    moveq    #2,d4
    moveq    #99,d3
    move.w   #159,d2
    moveq    #0,d1
    move.l   d1,d0
    movea.l  graphlib::plane1,a1
    jsr.l    graphlib::fill
    
    dbf      d5,_loop_graphlib_fill_
    
    bsr      TimerCurVal

; No triangle filling function in graphlib.
    moveq    #-1,d0
    move.l   d0,(a2)+

    bra      ReturnResults




_bench_Genlib:
    nop
;jsr genlib::init ; Initialization of genlib
;; Allocate a DScreen on the stack
;genlib::PUSH_DSCREEN d0 ;
;move.l d0,DScr1 ; Save it.
;jsr genlib::set_dscreen_function ; D0.l = DScreen’s addr
;jsr genlib::set_dscreen_int ; D0.l = DScreen’s addr
;jsr genlib::cls ; Clear current DScreen
;; Alloc another DScreen (Heap)
;jsr genlib::init_dscreen
;tst.w d0
;beq.s \quit
;jsr genlib::push_hd ; Push the handle
;move.l a0,DScr2 ; Save the other DScreen
;; Main Function


;jsr genlib::free_hd ; Free all the allocated handles
;\quit genlib::POP_DSCREEN ; Pop DScreen
;;jsr tios::PortRestore ; If we have called PortSet (Ti-92+ / Ti-89 only !)
;jmp genlib::quit ; End of program

;DScr1 dc.l 0 ; DScreen 1
;DScr2 dc.l 0 ; DScreen 2
;ts dc.w 0 ; Temps





ReturnResults:
    move.l   $263*4(a5),a0 ; push_END_TAG
    jsr      (a0)

    move.l   $4E4*4(a5),a3 ; push_ulong_to_integer
    moveq    #NR_RESULTS-1,d3
_push_values_:
    move.l   -(a2),(sp)
    jsr      (a3)
    dbf      d3,_push_values_
    
    move.l   $264*4(a5),a0 ; push_LIST_TAG
    jsr      (a0)
    
; Non-standard way to return expressions on the EStack...
    move.l   $109*4(a5),a0 ; top_estack
    move.l   (a0),_RAM_CALL_F

_bench_end:
    bsr      FreeTimer

_end:
    movem.l  (sp)+,d3-d7/a2-a6
    rts
    
    

	xdef _storage
_storage: ds.b NR_RESULTS*4

_comment dc.b "ExtGraph/Graphlib/GenLib bench",0


;; Vertical line function.
;    move.w   #10000,d4
;_loop_FastDrawVLine_:
;    move.w   #1,(sp)
;    moveq    #99,d2
;    move.w   #0,d1
;    moveq    #0,d0
;    lea      LCD_MEM,a0
;    jsr.l    FastDrawVLine_R
;
;    dbf      d4,_loop_FastDrawVLine_
;    
;    jbsr     TimerCurVal
;
;    jbsr     TimerRestart

;; Vertical line function.
;    move.w   #10000,d5
;_loop_graphlib_vert_:
;    moveq    #99,d2
;    move.w   #0,d1
;    moveq    #0,d0
;    lea      LCD_MEM,a0
;    jsr.l    graphlib::vert
;    
;    dbf      d5,_loop_graphlib_vert_
;    
;    jbsr     TimerCurVal
;
;    jbsr     TimerRestart
