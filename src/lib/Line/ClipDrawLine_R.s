| C prototype: void ClipDrawLine_R(short x1 asm("%d0"), short y1 asm("%d1"), short x2 asm("%d2"), short y2 asm("%d3"), unsigned short *clippedcoord asm("%a1"), short mode, void *plane asm("%a0"), void (__attribute__((__stkparm__)) *)(void* plane asm("%a0"), unsigned short x1 asm("%d0"), unsigned short y1 asm("%d1"), unsigned short x2 asm("%d2"), unsigned short y2 asm("%d3"), short mode)) __attribute__((__stkparm__));

.text
.globl ClipDrawLine_R
.even

ClipDrawLine_R:
    move.l   %d3,-(%sp)
    move.l   %a0,-(%sp)
    jbsr     _ClipLine_R
    movem.w  %d0-%d3,(%a1)
    cmpa.w   #0,%a0
    beq.s    0f
| Something to draw.
    move.l   (%sp),%a0
    move.w   4+4+4(%sp),(%sp)
    move.l   4+4+6(%sp),%a1
    jsr      (%a1)
0:
    addq.l   #4,%sp
    move.l   (%sp)+,%d3
    rts
