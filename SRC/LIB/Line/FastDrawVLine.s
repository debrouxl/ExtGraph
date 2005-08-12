| C prototype: void FastDrawVLine(void* plane,short x,short y1,short y2,short mode) __attribute__((__stkparm__));
| Valid values for mode are: A_REVERSE, A_NORMAL, A_XOR, A_REPLACE, A_OR

|------------------------------------------------------------------------------
| This routine uses a very dirty trick to combine 3 loops into one.
| This trick is called in-memory-patching. Normally each loop has
| to execute one of the following ASM instructions:
|
| bset %d2,(%a0) ... 0x05d0 (0x600 - 0x30)
| bclr %d2,(%a0) ... 0x0590 (0x600 - 0x70)
| bchg %d2,(%a0) ... 0x0550 (0x500 + 0x50)
|
| As you may note the opcodes are almost identical. There is just
| one byte different (the second byte) and depending on the given mode
| the routine will set this byte BEFORE entering the loop.
|------------------------------------------------------------------------------
|
| NOTE: The given mode will not be checked. The routine will assume that mode
|       is A_NORMAL = A_REPLACE = A_OR if it is neither A_REVERSE nor A_XOR.


.text
.globl FastDrawVLine
.even
FastDrawVLine:
| -0x70 for AND, +0x50 for XOR, -0x30 for OR.
    moveq    #-0x70,%d0
    move.w   4+10(%sp),%d1
    beq.s    3f                 | (mode == A_REVERSE).
    subq.w   #2,%d1
    bne.s    4f                 | (mode-2 == 0), i.e (mode == A_XOR).
    moveq    #0x50,%d0
    bra.s    3f
4:
    moveq    #-0x30,%d0
3:  
    lea      0f(%pc),%a0
    move.b   %d0,(%a0)          | patch memory with corresponding byte.
    move.w   4+6(%sp),%d0
    move.w   4+8(%sp),%d1
    cmp.w    %d0,%d1            | swap y values if necessary.
    bge.s    2f
    exg      %d0,%d1
2:
    sub.w    %d0,%d1            | d1 = abs(y1-y2).
    add.w    %d0,%d0            |
    move.w   %d0,%d2            |
    lsl.w    #4,%d0             |
    sub.w    %d2,%d0            | d0 = 2*abs(y1-y2)*16-2*abs(y1-y2) = 30 * height_in_pixels.
    movea.l  4+0(%sp),%a0
    adda.w   %d0,%a0
    move.w   4+4(%sp),%d0
    move.w   %d0,%d2
    lsr.w    #3,%d0
    adda.w   %d0,%a0
    not.w    %d2
1:
    .byte    0x05               | one of bchg/bclr/bset %d2,(%a0)
0:
    .byte    0xD0               | Any of 0x50, 0x90, 0xD0 is suitable.
    lea      30(%a0),%a0
    dbf      %d1,1b
    rts
