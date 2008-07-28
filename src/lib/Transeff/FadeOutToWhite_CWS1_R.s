| C prototype: void FadeOutToWhite_CWS1_R(void* lightplane asm("%a0"), void* darkplane asm("%a1"), unsigned short height asm("%d0"), unsigned short bytewidth asm("%d1"), short wait asm("%d2"));

.text
.globl FadeOutToWhite_CWS1_R
.even
FadeOutToWhite_CWS1_R:
    lsr.w    #3,%d0
    subq.w   #1,%d0
    blt.s    0f
    subq.w   #1,%d1
    blt.s    0f

    movem.l  %d3-%d7/%a2-%a3,-(%sp)

    movea.l  %a0,%a2
    movea.l  %a1,%a3

    move.w   %d0,%d3
    move.w   %d2,%d4
   
    moveq    #7+1,%d5
    moveq    #8-1,%d7

3:
    move.w   %d7,%d2
1:
    subq.w   #1,%d5

    bsr.s    4f
    dbf      %d2,1b


    subq.w   #1,%d7
    move.w   %d7,%d2
1:
    lea      30(%a2),%a2
    lea      30(%a3),%a3

    bsr.s    4f
    dbf      %d2,1b


    move.w   %d7,%d2
1:
    addq.w   #1,%d5

    bsr.s    4f
    dbf      %d2,1b


    subq.w   #1,%d7
    bmi.s    10f
    move.w   %d7,%d2
1:
    lea      -30(%a2),%a2
    lea      -30(%a3),%a3

    bsr.s    4f
    dbf      %d2,1b

    bra.s    3b


10:
    movem.l  (%sp)+,%d3-%d7/%a2-%a3
0:
    rts


4:
    move.w   %d3,%d0
    movea.l  %a2,%a0
    movea.l  %a3,%a1
5:
    moveq    #30-1,%d6

6:
    bclr     %d5,(%a0)+
    bclr     %d5,(%a1)+

    move.w   %d4,%d1
7:
    dbf      %d1,7b

    dbf      %d6,6b

    lea      240-30(%a0),%a0
    lea      240-30(%a1),%a1

    dbf      %d0,5b

    rts

/*
The number of pixels that have to be drawn is the following:
8,7,7,6; 6,5,5,4; 4,3,3,2; 2,1,1,0.
The correct numbers can be computed in the outermost loop, there's no need
for a lookup table.
*/
