| C prototype: void FadeOutToBlack_CCWS1_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

.text
.globl FadeOutToBlack_CCWS1_R
.even
FadeOutToBlack_CCWS1_R:
    lsr.w    #3,%d0
    dbf      %d0,__rest1_of_FOTB_CCWS1_R__
    rts

__rest1_of_FOTB_CCWS1_R__:
    dbf      %d1,__rest2_of_FOTB_CCWS1_R__
    rts

__rest2_of_FOTB_CCWS1_R__:
    movem.l  %d3-%d7/%a2-%a3,-(%sp)
 
    movea.l  %a0,%a2
    movea.l  %a1,%a3
 
    move.w   %d0,%d3
    move.w   %d2,%d4
   
    moveq    #0-1,%d5
    moveq    #8-1,%d7
 
__FOTB_CCWS1_R__:
    move.w   %d7,%d2
__loop1_FOTB_CCWS1_R__:
    addq.w   #1,%d5
 
    bsr.s    __outer_loop_FOTB_CCWS1_R__
    dbf      %d2,__loop1_FOTB_CCWS1_R__
 
 
    subq.w   #1,%d7
    move.w   %d7,%d2
__loop2_FOTB_CCWS1_R__:
    lea      30(%a2),%a2
    lea      30(%a3),%a3
 
    bsr.s    __outer_loop_FOTB_CCWS1_R__
    dbf      %d2,__loop2_FOTB_CCWS1_R__
 
 
    move.w   %d7,%d2
__loop3_FOTB_CCWS1_R__:
    subq.w   #1,%d5
 
    bsr.s    __outer_loop_FOTB_CCWS1_R__
    dbf      %d2,__loop3_FOTB_CCWS1_R__
 
 
    subq.w   #1,%d7
    bmi.s __end_FOTB_CCWS1_R__
    move.w   %d7,%d2
__loop4_FOTB_CCWS1_R__:
    lea      -30(%a2),%a2
    lea      -30(%a3),%a3
 
    bsr.s    __outer_loop_FOTB_CCWS1_R__
    dbf      %d2,__loop4_FOTB_CCWS1_R__
 
    bra.s    __FOTB_CCWS1_R__
 
 
__end_FOTB_CCWS1_R__:
    movem.l  (%sp)+,%d3-%d7/%a2-%a3
    rts
 
 
__outer_loop_FOTB_CCWS1_R__:
    move.w   %d3,%d0
    movea.l  %a2,%a0
    movea.l  %a3,%a1
_outer_loop_FOTB_CCWS1_R__:
    moveq    #30-1,%d6
 
__inner_loop_FOTB_CCWS1_R__:
    bset     %d5,(%a0)+
    bset     %d5,(%a1)+
 
    move.w   %d4,%d1
__wait_loop_FOTB_CCWS1_R__:
    dbf      %d1,__wait_loop_FOTB_CCWS1_R__
 
    dbf      %d6,__inner_loop_FOTB_CCWS1_R__
 
    lea      240-30(%a0),%a0
    lea      240-30(%a1),%a1
 
    dbf      %d0,_outer_loop_FOTB_CCWS1_R__
 
    rts

/*
The number of pixels that have to be drawn is the following:
8,7,7,6; 6,5,5,4; 4,3,3,2; 2,1,1,0.
The correct numbers can be computed in the outermost loop, there's no need
for a lookup table.
*/
