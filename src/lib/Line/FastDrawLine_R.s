| C prototype: void FastDrawLine_R (void* plane asm("%a0"),unsigned short x1 asm("%d0"),unsigned short y1 asm("%d1"),unsigned short x2 asm("%d2"),unsigned short y2 asm("%d3"),unsigned short mode) __attribute__ ((__stkparm__));
|
| FastDrawLine_R by Olivier Armand (ExtendeD) <ola.e-ml@wanadoo.fr>
| Small modifications by Lionel Debroux (mainly size optimizations).

.text
.globl FastDrawLine_R
.even

FastDrawLine_R:
    movem.l  %d3/%d4/%d5/%d6/%d7/%a2,-(%sp)
    cmp.w    %d0,%d2
    bhi.s    2f
    exg      %d0,%d2
    exg      %d1,%d3
2:		                            | -> dx will be positive.
    move.w   (4+6*4)(%sp),%d4               | mode

    cmp.w    0f(%pc),%d4
    beq.s    __GetMasks_FDL_R__
| Initialize the code according to the mode.
    lea      2f(%pc),%a1
    lea      1f(%pc),%a2
    tst.w    %d4
    beq.s    __Patch_code_FDL_R__            | A_REVERSE.
    subq.w   #2,%d4
    beq.s    __NextAttrPatchs_FDL_R__        | A_XOR, jump once in the table.
| Other mode (A_NORMAL, A_REPLACE, A_OR), jump twice in the table.
    addq.l   #2,%a2
__NextAttrPatchs_FDL_R__:
    addq.l   #2,%a2
__Patch_code_FDL_R__:
| The comments are for the case A_REVERSE is chosen.
    move.b   (%a2)+,%d4
    move.b   %d4,(%a1)                                        | and.b d6,(a0)
    move.b   %d4,__PutInstr2_FDL_R__-2f(%a1)    | and.b d6,(a0)
    move.b   %d4,__AttrCenter1_FDL_R__-2f(%a1)  | and.b d6,(a0)
    addq.b   #2,%d4
    move.b   %d4,__PutInstr1_FDL_R__+2-2f(%a1)  | and.b d7,(a1)
    move.b   %d4,__PutInstr2_FDL_R__+2-2f(%a1)  | and.b d7,(a1)
    move.b   (%a2),%d4
    move.b   %d4,__RorInstr_FDL_R__+2-2f(%a1)   | bcs.s
    move.b   %d4,__RorInstr_FDL_R__+8-2f(%a1)   | bcs.s
    move.b   %d4,__PutInstr1_FDL_R__+6-2f(%a1)  | bcs.s
    move.b   %d4,__PutInstr1_FDL_R__+12-2f(%a1) | bcs.s

__GetMasks_FDL_R__:
| Find the mask and the address of the leftmost point.
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
__MaskInstr1_FDL_R__:
    moveq    #-128,%d6                      | 0b10000000
    ror.b    %d4,%d6                        | mask

|Find the mask and the address of the rightmost point.	
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
__MaskInstr2_FDL_R__:
    moveq    #-128,%d7                      | 0b10000000
    ror.b    %d4,%d7                        | mask

    tst.w    (4+6*4)(%sp)                   | mode
    bne.s    __No_invert_masks_FDL_R__
    not.b    %d6
    not.b    %d7

__No_invert_masks_FDL_R__:
    lea	     __RorInstr_FDL_R__(%pc),%a2

| Calculate dx and dy.
    sub.w    %d0,%d2                        | dx = x2-x1
    sub.w    %d1,%d3                        | dy = y2-y1
| Check if the line is going up or down and patch the code accordingly.
    bpl.s    __LineGoesDownwards_FDL_R__
    neg.w    %d3                            | -> so as to have dy>=0.

    move.w   #0xE31E,(%a2)                  | rol.b #1,d6
    move.w   #0x5348,4(%a2)                 | subq.w #1,a0
    move.w   #0xE21F,6(%a2)                 | ror.b #1,d7
    move.w   #0x5249,10(%a2)                | addq.w #1,a1
    moveq    #-30,%d4                       | Y-- (previous line).

    bra.s    __FirstDiagonal_FDL_R__

__LineGoesDownwards_FDL_R__:
    move.w   #0xE21E,(%a2)                  | ror.b #1,d6
    move.w   #0x5248,4(%a2)                 | addq.w #1,a0 
    move.w   #0xE31F,6(%a2)                 | rol.b #1,d7
    move.w   #0x5349,10(%a2)                | subq.w #1,a1
    moveq    #30,%d4                        | Y++ (next line).

__FirstDiagonal_FDL_R__:
    cmp.w    %d3,%d2
    bls.s    __ScanY_FDL_R__                | if dy >= dx
| When there is only one point to draw, dx=dy -> see ScanY
| Calculate the index for the dbf and calculate P(0)
    move.w   %d2,%d0
    move.w   %d2,%d1
    lsr.w    #1,%d1                         | dx/2
    subq.w   #1,%d0                         | adjust the dbf for the problem
    lsr.w    #1,%d0                         | with the center of the line.
    scs.b    %d5
    sub.w    %d2,%d1                        | P(0) = dx/2-dx = -dx/2

| Now we have :
| d0.w : dbf (such that the center is not drawn twice when dx is even).
| d1.w : P, test function.
| d2.w : dx.
| d3.w : dy.
| d4.w : 30 or -30, if the line goes up or goes down (delta_y).
| d6.b : mask for the left point \ (X1,Y1).
| d7.b : mask for the right point / (X2,Y2).
| a0.l : address of the left point \.
| a1.l : address of the right point /.

2:
__ScanYLoop_FDL_R__:
__PutInstr1_FDL_R__:
    or.b     %d6,(%a0)                      | PutPxl to the left point.
    or.b     %d7,(%a1)                      | PutPxl to the right point.
    ror.b    #1,%d6                         | X1++
    bcc.s    __Mask1Ok_FDL_R__
    addq.w   #1,%a0
__Mask1Ok_FDL_R__:
    rol.b    #1,%d7                         | X2--
    bcc.s    __Mask2Ok_FDL_R__
    subq.w   #1,%a1
__Mask2Ok_FDL_R__:
    add.w    %d3,%d1                        |P+=dy
    bmi.s    __SameY_FDL_R__                |if P < 0
    sub.w    %d2,%d1                        |P-=dx
    add.w    %d4,%a0                        |Y1++ (or --)
    sub.w    %d4,%a1                        |Y2-- (or ++)
__SameY_FDL_R__:
    dbf      %d0,__ScanYLoop_FDL_R__
| Prevent the center from being drawn twice.
| This is a problem only in A_XOR mode.
3:
    tst.b    %d5
    beq.s    4f
__AttrCenter1_FDL_R__:
    or.b     %d6,(%a0)                      | Draw the center only once.
4:
    movem.l  (%sp)+,%d3/%d4/%d5/%d6/%d7/%a2
    rts

__ScanY_FDL_R__:                  | The roles of dx and dy are swapped.
    move.w   %d3,%d0
    beq.s    __AttrCenter1_FDL_R__          |dy = 0 -> only one point.
    move.w   %d3,%d1
    lsr.w    #1,%d1
    subq.w   #1,%d0               | Adjust the dbf to correct the problem with
    lsr.w    #1,%d0               | center of the line.
    scs.b    %d5
    sub.w    %d3,%d1                        |P(0) = dy/2-dy = -dy/2

    cmp.l    %a1,%a0
    bls.s    __ScanXLoop_FDL_R__  | When it is in the correct order (Y1 <= Y2)
    exg      %d6,%d7                        |invert the two points
    exg      %a0,%a1
|    move.l   %a0,%d4
|    move.l   %a1,%a0
|    move.l   %d4,%a1
	 
__ScanXLoop_FDL_R__:
__PutInstr2_FDL_R__:
    or.b     %d6,(%a0)                      | PutPxl
    or.b     %d7,(%a1)                      | At the other end.
    lea      30(%a0),%a0                    | Y1++
    lea      -30(%a1),%a1                   | Y2--
    add.w    %d2,%d1                        | P+=dx
    bmi.s    __SameX_FDL_R__                | if P < 0
    sub.w    %d3,%d1                        | P-=dy
__RorInstr_FDL_R__:
    ror.b    #1,%d6
    bcc.s    __RorInstr2_FDL_R__
    addq.w   #1,%a0                         | X1++
__RorInstr2_FDL_R__:
    rol.b    #1,%d7
    bcc.s    __SameX_FDL_R__
    subq.w   #1,%a1                         | X2--
__SameX_FDL_R__:
    dbf      %d0,__ScanXLoop_FDL_R__
    bra.s    3b

.even	
1:
|A_REVERSE :
|mask, mask, and.b d6,(a0), and.b d7,(a1), and.b d6,(a0), and.b d7,(a1)
|bcs.s, bcs.s, bcs.s, bcs.s, and.b d6,(a0), and.b d6,(a0)
.byte	0xCD,0x65
|	dc.b	%01111111,%01111111,$CD,$CF,$CD,$CF,$65,$65,$65,$65,$CD,$CD	
|A_XOR :
|mask, mask, eor.b d6,(a0), eor.b d7,(a1), eor.b d6,(a0), eor.b d7,(a1)	
|bcc.s, bcc.s, bcc.s, bcc.s, eor.b d6,(a0), eor.b d6,(a0)
.byte	0xBD,0x64
|	dc.b	%10000000,%10000000,$BD,$BF,$BD,$BF,$64,$64,$64,$64,$BD,$BD
|A_NORMAL :
|mask, mask, or.b d6,(a0), or.b d7,(a1), or.b d6,(a0), or.b d7,(a1)
|bcc.s, bcc.s, bcc.s, bcc.s, or.b d6,(a0), or.b d6,(a0)
.byte	0x8D,0x64
|	dc.b	%10000000,%10000000,$8D,$8F,$8D,$8F,$64,$64,$64,$64,$8D,$8D
.even

0: .word 0xFFFF
.even
