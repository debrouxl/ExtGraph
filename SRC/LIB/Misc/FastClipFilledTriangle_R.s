| C prototype: void FastClipFilledTriangle_R(
| register unsigned char* plane asm("%a0"),
| unsigned short x1,
| register unsigned short y1 asm("%d0"),
| unsigned short x2,
| register unsigned short y2 asm("%d1"),
| unsigned short x3,
| register unsigned short y3 asm("%d2"),
| unsigned short mode) __attribute__ ((__stkparm__));
/*
.text
.globl FastClipFilledTriangle_R
.even

FastClipFilledTriangle_R:
    movem.l  %d3-%d7/%a2-%a6,-(%sp)

    cmp.w    %d0,%d1
    bhi.s    __NoExg1_FCFT_R__
    exg      %d0,%d1
__NoExg1_FCFT_R__:
    cmp.w    %d0,%d2
    bhi.s    __NoExg2_FCFT_R__
    exg      %d0,%d2
__NoExg2_FCFT_R__:
    cmp.w    %d1,%d2
    bhi.s    __NoExg3_FCFT_R__
    exg      %d1,%d2
__NoExg3_FCFT_R__:
| Now, the endpoints are in the decreasing order.

    
    move.w   (4+5*4)(%sp),%d4               | mode

    cmp.w   __previous_mode_FCFT_R__(%pc),%d4
    beq.s   __GetMasks_FCFT_R__
| Initialize the code according to the mode.
    lea     __Patchs_FCFT_R__(%pc),%a1
    lea     __AttrPatchsTable_FCFT_R__(%pc),%a2
    tst.w    %d4
    beq.s   __Patch_code_FCFT_R__            | A_REVERSE.
    subq.w   #2,%d4
    beq.s   __NextAttrPatchs_FCFT_R__        | A_XOR, jump once in the table.
| Other mode (A_NORMAL, A_REPLACE, A_OR), jump twice in the table.
    addq.l   #2,%a2
__NextAttrPatchs_FCFT_R__:
    addq.l   #2,%a2
__Patch_code_FCFT_R__:
| The comments are for the case A_REVERSE is chosen.
    move.b   (%a2)+,%d4
    move.b   %d4,(%a1)                                        | and.b d6,(a0)
    move.b   %d4,__PutInstr2_FCFT_R__-__Patchs_FCFT_R__(%a1)    | and.b d6,(a0)
    move.b   %d4,__AttrCenter1_FCFT_R__-__Patchs_FCFT_R__(%a1)  | and.b d6,(a0)
    addq.b   #2,%d4
    move.b   %d4,__PutInstr1_FCFT_R__+2-__Patchs_FCFT_R__(%a1)  | and.b d7,(a1)
    move.b   %d4,__PutInstr2_FCFT_R__+2-__Patchs_FCFT_R__(%a1)  | and.b d7,(a1)
    move.b   (%a2),%d4
    move.b   %d4,__RorInstr_FCFT_R__+2-__Patchs_FCFT_R__(%a1)   | bcs.s
    move.b   %d4,__RorInstr_FCFT_R__+8-__Patchs_FCFT_R__(%a1)   | bcs.s
    move.b   %d4,__PutInstr1_FCFT_R__+6-__Patchs_FCFT_R__(%a1)  | bcs.s
    move.b   %d4,__PutInstr1_FCFT_R__+12-__Patchs_FCFT_R__(%a1) | bcs.s

__GetMasks_FCFT_R__:
| Find the mask and the address of the left point.
    move.l   %a0,%a1
    move.w   %d1,%d4
    add.w    %d4,%d4
    move.w   %d4,%d6                        | y1*2
    lsl.w    #4,%d4                         | y1*32
    sub.w    %d6,%d4                        | y1*30
    add.w    %d4,%a0                        | plane+y1*30
    move.w   %d0,%d4
    lsr.w    #3,%d4                         | x1/8
    add.w    %d4,%a0                        | -> address
| Find the mask.
    move.w   %d0,%d4
    and.b    #7,%d4                         | x1%8
__MaskInstr1_FCFT_R__:
    moveq    #-128,%d6                      | 0b10000000
    ror.b    %d4,%d6                        | mask

|Find the mask and the address of the right point. 
    move.w   %d3,%d4
    add.w    %d4,%d4
    move.w   %d4,%d7                        | y2*2
    lsl.w    #4,%d4                         | y2*32
    sub.w    %d7,%d4                        | y2*30
    add.w    %d4,%a1                        | plane+y2*30
    move.w   %d2,%d4
    lsr.w    #3,%d4                         | x2/8
    add.w    %d4,%a1                        | -> address
| Find the mask.
    move.w   %d2,%d4
    and.b    #7,%d4                         | x0%8
__MaskInstr2_FCFT_R__:
    moveq    #-128,%d7                      | 0b10000000
    ror.b    %d4,%d7                        | mask

    tst.w    (4+5*4)(%sp)                   | mode
    bne.s    __No_invert_masks_FCFT_R__
    not.b    %d6
    not.b    %d7

__No_invert_masks_FCFT_R__:
    lea      __RorInstr_FCFT_R__(%pc),%a2

| Calculate dx and dy.
    sub.w    %d0,%d2                        | dx = x2-x1
    sub.w    %d1,%d3                        | dy = y2-y1
| Check if the line is going up or down and patch the code accordingly.
    bpl.s    __LineGoesDownwards_FCFT_R__
    neg.w    %d3                            | -> so as to have dy>=0.

    move.w   #0xE31E,(%a2)                  | rol.b #1,d6
    move.w   #0x5348,4(%a2)                 | subq.w #1,a0
    move.w   #0xE21F,6(%a2)                 | ror.b #1,d7
    move.w   #0x5249,10(%a2)                | addq.w #1,a1
    moveq    #-30,%d4                       | Y-- (previous line).

    bra.s    __FirstDiagonal_FCFT_R__

__LineGoesDownwards_FCFT_R__:
    move.w   #0xE21E,(%a2)                  | ror.b #1,d6
    move.w   #0x5248,4(%a2)                 | addq.w #1,a0 
    move.w   #0xE31F,6(%a2)                 | rol.b #1,d7
    move.w   #0x5349,10(%a2)                | subq.w #1,a1
    moveq    #30,%d4                        | Y++ (next line).

__FirstDiagonal_FCFT_R__:
    cmp.w    %d3,%d2
    bls.s    __ScanY_FCFT_R__                | if dy >= dx
| When there is only one point to draw, dx=dy -> see ScanY
| Calculate the index for the dbf and calculate P(0)
    move.w   %d2,%d0
    move.w   %d2,%d1
    lsr.w    #1,%d1                         | dx/2
    subq.w   #1,%d0                         | adjust the dbf for the problem
    lsr.w    #1,%d0                         | with the center of the line.
    sub.w    %d2,%d1                        | P(0) = dx/2-dx = -dx/2

| Now we have :
| d0.w : dbf (such that the center is not drawn twice when dx is even).
| d1.w : P, test function.
| d2.w : dx.
| d3.w : dy.
| d4.w : 30 or -30, if the line goes up or goes down (delta_y).
| d6.b : mask for the left point \ (X1,Y1).
| d7.b : mask for the right point / (X2,Y2).
| a0.l : address of of the left point \.
| a1.l : address of the right point /.

__Patchs_FCFT_R__:
__ScanYLoop_FCFT_R__:
__PutInstr1_FCFT_R__:
    or.b     %d6,(%a0)                      | PutPxl to the left point.
    or.b     %d7,(%a1)                      | PutPxl to the right point.
    ror.b    #1,%d6                         | X1++
    bcc.s    __Mask1Ok_FCFT_R__
    addq.w   #1,%a0
__Mask1Ok_FCFT_R__:
    rol.b    #1,%d7                         | X2--
    bcc.s    __Mask2Ok_FCFT_R__
    subq.w   #1,%a1
__Mask2Ok_FCFT_R__:
    add.w    %d3,%d1                        |P+=dy
    bmi.s    __SameY_FCFT_R__                |if P < 0
    sub.w    %d2,%d1                        |P-=dx
    add.w    %d4,%a0                        |Y1++ (or --)
    sub.w    %d4,%a1                        |Y2-- (or ++)
__SameY_FCFT_R__:
    dbf      %d0,__ScanYLoop_FCFT_R__
| Prevent the center from being drawn twice.
| This is a problem only in A_XOR mode.
___Draw_center_only_once_FCFT_R__:
    btst     #0,%d2
    bne.s    __Draw_center_only_once_FCFT_R__
__AttrCenter1_FCFT_R__:
    or.b     %d6,(%a0)                      | Draw the center only once.
__Draw_center_only_once_FCFT_R__:
    movem.l  (%sp)+,%d3-%d7/%a2-%a6
    rts

__ScanY_FCFT_R__:                  | The roles of dx and dy are swapped.
    move.w   %d3,%d0
    beq.s    __AttrCenter1_FCFT_R__          |dy = 0 -> only one point.
    move.w   %d3,%d1
    lsr.w    #1,%d1
    subq.w   #1,%d0               | Adjust the dbf to correct the problem with
    lsr.w    #1,%d0               | center of the line.
    sub.w    %d3,%d1                        |P(0) = dy/2-dy = -dy/2

    cmp.l    %a1,%a0
    bls.s    __ScanXLoop_FCFT_R__  | When it is in the correct order (Y1 <= Y2)
    exg      %d6,%d7                        |invert the two points
    move.l   %a0,%d4
    move.l   %a1,%a0
    move.l   %d4,%a1

__ScanXLoop_FCFT_R__:
__PutInstr2_FCFT_R__:
    or.b     %d6,(%a0)                      | PutPxl
    or.b     %d7,(%a1)                      | At the other end.
    lea      30(%a0),%a0                    | Y1++
    lea      -30(%a1),%a1                   | Y2--
    add.w    %d2,%d1                        | P+=dx
    bmi.s    __SameX_FCFT_R__                | if P < 0
    sub.w    %d3,%d1                        | P-=dy
__RorInstr_FCFT_R__:
    ror.b    #1,%d6
    bcc.s    __RorInstr2_FCFT_R__
    addq.w   #1,%a0                         | X1++
__RorInstr2_FCFT_R__:
    rol.b    #1,%d7
    bcc.s    __SameX_FCFT_R__
    subq.w   #1,%a1                         | X2--
__SameX_FCFT_R__:
    dbf      %d0,__ScanXLoop_FCFT_R__
    bra.s    ___Draw_center_only_once_FCFT_R__

.even 
__AttrPatchsTable_FCFT_R__:
|A_REVERSE :
|mask, mask, and.b d6,(a0), and.b d7,(a1), and.b d6,(a0), and.b d7,(a1)
|bcs.s, bcs.s, bcs.s, bcs.s, and.b d6,(a0), and.b d6,(a0)
.byte 0xCD,0x65
| dc.b %01111111,%01111111,$CD,$CF,$CD,$CF,$65,$65,$65,$65,$CD,$CD 
|A_XOR :
|mask, mask, eor.b d6,(a0), eor.b d7,(a1), eor.b d6,(a0), eor.b d7,(a1) 
|bcc.s, bcc.s, bcc.s, bcc.s, eor.b d6,(a0), eor.b d6,(a0)
.byte 0xBD,0x64
| dc.b %10000000,%10000000,$BD,$BF,$BD,$BF,$64,$64,$64,$64,$BD,$BD
|A_NORMAL :
|mask, mask, or.b d6,(a0), or.b d7,(a1), or.b d6,(a0), or.b d7,(a1)
|bcc.s, bcc.s, bcc.s, bcc.s, or.b d6,(a0), or.b d6,(a0)
.byte 0x8D,0x64
| dc.b %10000000,%10000000,$8D,$8F,$8D,$8F,$64,$64,$64,$64,$8D,$8D
.even

__previous_mode_FCFT_R__: .word 0xFFFF
.even




| C prototype: void FastDrawHLine_R(register unsigned char* plane asm("a0"), register short x1 asm("d0"), register short x2 asm("d1"), register short y asm("d2"),short mode) __attribute__((__stkparm__));
| Valid values for mode are: A_REVERSE, A_NORMAL, A_XOR, A_REPLACE, A_OR.

.text
.even
__Beginning_FCFT_R__:
.word 0xFFFF,0x7FFF,0x3FFF,0x1FFF,0x0FFF,0x07FF,0x03FF,0x01FF,0x00FF,0x007F,0x003F,0x001F,0x000F,0x0007,0x0003,0x0001

__End_FCFT_R__:
.word 0x8000,0xC000,0xE000,0xF000,0xF800,0xFC00,0xFE00,0xFF00,0xFF80,0xFFC0,0xFFE0,0xFFF0,0xFFF8,0xFFFC,0xFFFE,0xFFFF

.globl FastDrawHLine_R
FastDrawHLine_R:
    move.l   %d4,-(%sp)                      | d4 mustn't be destroyed.

    cmp.w    %d0,%d1
    bge.s    __Registers_well_ordered_FCFT_R__

    exg      %d0,%d1

__Registers_well_ordered_FCFT_R__:
    move.w   %d2,%d4
    lsl.w    #4,%d2
    sub.w    %d4,%d2
    move.w   %d0,%d4
    lsr.w    #4,%d4
    add.w    %d4,%d2
    add.w    %d2,%d2
    adda.w   %d2,%a0

| d4 = 8 * (x1/16 + x1/16) + 16. We add 1 before shifting instead of adding 16 
| after shifting (gain: 4 clocks and 2 bytes).
    addq.w   #1,%d4                          | d4 = 8 * (x1/16 + x1/16) + 16.
    lsl.w    #4,%d4

    move.w   %d1,%d2                         | x2 is stored in d2.
    andi.w   #0xF,%d0

    add.w    %d0,%d0
    move.w   __Beginning_FCFT_R__(%pc,%d0.w),%d0 | d0 = mask of first pixels.
    andi.w   #0xF,%d1

    add.w    %d1,%d1
    move.w   __End_FCFT_R__(%pc,%d1.w),%d1   | d1 = mask of last pixels.
    cmp.w    %d4,%d2                         | Line less than 16 pixels long ?
    blt.s    __Less_than_16_pixels_FCFT_R__
    sub.w    %d4,%d2                         | d2 = x2 - x.
    moveq.l  #32,%d4
    tst.w    4+4(%sp)
    beq.s    __Reverse_FCFT_R__
    cmpi.w   #2,4+4(%sp)
    beq.s    __Xor_FCFT_R__

__Normal_FCFT_R__:
    or.w     %d0,(%a0)+
    moveq    #-1,%d0
    sub.w    %d4,%d2
    blt.s    __Normal_16_pixels_FCFT_R__
__Normal_32_pixels_FCFT_R__:
    move.l   %d0,(%a0)+
    sub.w    %d4,%d2
    bge.s    __Normal_32_pixels_FCFT_R__
__Normal_16_pixels_FCFT_R__:
    cmpi.w   #-16,%d2
    blt.s    __Normal_lessthan16_pixels_FCFT_R__
    move.w   %d0,(%a0)+
__Normal_lessthan16_pixels_FCFT_R__:
    or.w     %d1,(%a0)
    move.l   (%sp)+,%d4
    rts

__Reverse_FCFT_R__:
    not.w    %d0
    and.w    %d0,(%a0)+
    moveq    #0,%d0
    sub.w    %d4,%d2
    blt.s    __Reverse_16_pixels_FCFT_R__
__Reverse_32_pixels_FCFT_R__:
    move.l   %d0,(%a0)+
    sub.w    %d4,%d2
    bge.s    __Reverse_32_pixels_FCFT_R__
__Reverse_16_pixels_FCFT_R__:
    cmpi.w   #-16,%d2
    blt.s    __Reverse_lessthan16_pixels_FCFT_R__
    move.w   %d0,(%a0)+
__Reverse_lessthan16_pixels_FCFT_R__:
    not.w    %d1
    and.w    %d1,(%a0)
    move.l   (%sp)+,%d4
    rts

__Xor_FCFT_R__:
    eor.w    %d0,(%a0)+
    sub.w    %d4,%d2
    blt.s    __Xor_16_pixels_FCFT_R__
__Xor_32_pixels_FCFT_R__:
    not.l    (%a0)+
    sub.w    %d4,%d2
    bge.s    __Xor_32_pixels_FCFT_R__
__Xor_16_pixels_FCFT_R__:
    cmpi.w   #-16,%d2
    blt.s    __Xor_lessthan16_pixels_FCFT_R__
    not.w    (%a0)+
__Xor_lessthan16_pixels_FCFT_R__:
    eor.w    %d1,(%a0)
    move.l   (%sp)+,%d4
    rts

__Less_than_16_pixels_FCFT_R__:
    move.l   (%sp)+,%d4
    and.w    %d0,%d1
    tst.w    4(%sp)
    beq.s    __Reverse_l16_FCFT_R__
    cmpi.w   #2,4(%sp)
    beq.s    __Xor_l16_FCFT_R__
    or.w     %d1,(%a0)
    rts
__Reverse_l16_FCFT_R__:
    not.w    %d1
    and.w    %d1,(%a0)
    rts
__Xor_l16_FCFT_R__:
    eor.w    %d1,(%a0)
    rts
*/