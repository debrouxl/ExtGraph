| C prototype: void DrawSpan_XOR_R(unsigned short x1 asm("%d0"), unsigned short x2 asm("%d1"), unsigned char * addr asm("%a0"));
|
| This routine draws lines from x1 to x2 in line starting at addr, in
| A_XOR mode. It is primarily intended as callback for (Clip)FilledTriangle_R.

.text
.even
.globl DrawSpan_XOR_R
DrawSpan_XOR_R:
/*
cmpi.w #160,%d0
bhi.s 0f
cmpi.w #160,%d1
bhi.s 0f
bra.s 1f

0: bra.s 0b
1:
*/
    cmp.w    %d0,%d1        | if (x1>x2) exchange(x1,x2)
    bge.s    10f
    exg      %d0,%d1
10:
    tst.w    %d0            | if (x1<0) x1=0
    bge.s    10f
    clr.w    %d0
    tst.w    %d1            | if (x2<0) x2=0
    blt.s    0f
10:
    move.w   #239,%d2
    cmp.w    %d2,%d1        | if (x2>239) x2=239
    ble.s    10f
    move.w   %d2,%d1        | if (x1>239) x1=239
    cmp.w    %d2,%d0
    bgt.s    0f            | return immediately: x1 & x2 are both larger than 239!

10:
|-----------------------------------------------------------------
| now %d0.w contains left x value and %d1.w contains right x value
| both clipped to [0-239]
|-----------------------------------------------------------------
    move.w   %d0,%d2
    lsr.w    #4,%d2
    add.w    %d2,%d2
    add.w    %d2,%a0       | p = addr+((x1>>3)&0x1e)) [%a0]
    move.w   %d0,%d2
    andi.w   #15,%d2       | sx = x1 & 0xf [%d2]
    sub.w    %d0,%d1
    addq.w   #1,%d1        | dx = x2-x1+1 [%d1]

|--------------------------------------------------------------------
| if (dx<16) ... very short line ...
|--------------------------------------------------------------------
    cmp.w    #15,%d1       | if (dx<16) {*p^=(ASM_SWAP(table2[dx])) >> sx;return;}
    bgt.s    6f
    moveq    #0,%d0
    move.w   %d1,%d0
    add.w    %d0,%d0
    move.w   (9f,%pc,%d0.w),%d0
    swap     %d0
    lsr.l    %d2,%d0
    eor.l    %d0,(%a0)
0:
    rts
.even

9:
    .word     0,32768,49152,57344,61440,63488,64512,65024
    .word 65280,65408,65472,65504,65520,65528,65532,65534

6:  tst.w    %d2           | if (sx) ...
    beq.s    1f
    move.w   %d2,%d0
    add.w    %d0,%d0
    move.w   (8f,%pc,%d0.w),%d0 | *p++ ^= table1[sx]
    eor.w    %d0,(%a0)+
    add.w    #-16,%d2
    add.w    %d2,%d1       | dx -= 16 - sx <=> dx += sx - 16;
1:
    moveq    #16,%d2
4:
    cmp.w    %d2,%d1       | while (dx >= 16) {*p++ ^= 0xffff;dx-=16;}
    blt.s    2f
    not.w    (%a0)+
    sub.w    %d2,%d1
    bra.s    4b
2:
    tst.w    %d1        | if (dx) *p ^= table2[dx];
    beq.s    3f
    add.w    %d1,%d1
    move.w   (9b,%pc,%d1.w),%d0
    eor.w    %d0,(%a0)
3:
    rts
.even

8:
    .word 65535,32767,16383, 8191, 4095, 2047, 1023,  511
    .word   255,  127,   63,   31,   15,    7,    3,    1
