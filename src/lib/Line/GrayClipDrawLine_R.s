| C prototype: void GrayClipDrawLine_R(short x1 asm("%d0"), short y1 asm("%d1"), short x2 asm("%d2"), short y2 asm("%d3"), unsigned short *clippedcoord asm("%a1"), short color, void *plane0, void *plane, void (__attribute__((__stkparm__)) *)(void* plane0 asm("%a0"), void *plane1 asm("%a1"), unsigned short x1 asm("%d0"), unsigned short y1 asm("%d1"), unsigned short x2 asm("%d2"), unsigned short y2 asm("%d3"), short color)) __attribute__((__stkparm__));

.text
.globl GrayClipDrawLine_R
.even

GrayClipDrawLine_R:
    move.l   %d3,-(%sp)
    move.l   %a2,-(%sp)
    jbsr     _ClipLine_R
    movem.w  %d0-%d3,(%a1)
    cmpa.w   #0,%a0
    beq.s    0f | Nothing to draw.
    lea      4+8(%sp),%a2
    move.w   (%a2)+,-(%sp)
    move.l   (%a2)+,%a0
    move.l   (%a2)+,%a1
    move.l   (%a2)+,%a2
    jsr      (%a2)
    addq.l   #2,%sp
0:
    move.l   (%sp)+,%a2
    move.l   (%sp)+,%d3
    rts
