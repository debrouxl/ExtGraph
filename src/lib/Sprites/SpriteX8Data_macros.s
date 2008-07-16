.macro WithMaskMacro op
    move.w   %d3,-(%sp)
    move.w   %d4,-(%sp)
    subq.w   #1,%d2 | height
    subq.w   #1,%d1 | bytewidth
    move.w   %d1,%d0

0:  move.b   (%a0)+,%d3
    move.b   (%a2)+,%d4
    \op.b    %d4,%d3
    move.b   %d3,(%a1)+
    dbf      %d1,0b

    suba.w   %d0,%a2
    subq.w   #1,%a2
    move.w   %d0,%d1
    dbf      %d2,0b

    move.w   (%sp)+,%d4
    move.w   (%sp)+,%d3
    rts
.endm


.macro WithSpriteMacro op
    move.w   %d3,-(%sp)

    mulu.w   %d1,%d2
    subq.w   #1,%d2 | height*bytewidth-1

0:  move.b   (%a0)+,%d0
    move.b   (%a2)+,%d3
    \op.b    %d3,%d0
    move.b   %d0,(%a1)+
    dbf      %d2,0b

    move.w   (%sp)+,%d3
    rts
.endm
