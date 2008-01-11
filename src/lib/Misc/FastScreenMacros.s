.macro FastScreenMacro op
    move.w   #((3840/16)-1),%d0

0:  move.l   (%a0)+,%d1
    \op.l    %d1,(%a1)+
    move.l   (%a0)+,%d1
    \op.l    %d1,(%a1)+
    move.l   (%a0)+,%d1
    \op.l    %d1,(%a1)+
    move.l   (%a0)+,%d1
    \op.l    %d1,(%a1)+
    dbf      %d0,0b

    rts
.endm
