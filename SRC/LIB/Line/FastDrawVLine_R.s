| C prototype: void FastDrawVLine_R(register void* plane asm("%a0"),register short x asm("%d0"),register short y1 asm("%d1"),register short y2 asm("%d2"),short mode) __attribute__((__stkparm__));
| Valid values for mode are: A_REVERSE, A_NORMAL, A_XOR, A_REPLACE, A_OR.

|------------------------------------------------------------------------------
| This routine uses a very dirty trick to combine 3 loops into one.
| This trick is called in-memory-patching. Normally each loop has
| to execute one of the following ASM instructions:
|
| bset %d1,(%a0) ... 0x03d0 (0x600 - 0x30)
| bclr %d1,(%a0) ... 0x0390 (0x600 - 0x70)
| bchg %d1,(%a0) ... 0x0350 (0x500 + 0x50)
|
| As you may note the opcodes are almost identical. There is just
| one byte different (the second byte) and depending on the given mode
| the routine will set this byte BEFORE entering the loop.
|------------------------------------------------------------------------------
|
| NOTE: The given mode will not be checked. The routine will assume that mode
|       is A_NORMAL = A_REPLACE = A_OR if it is neither A_REVERSE nor A_XOR.


.text
.globl FastDrawVLine_R
.even
FastDrawVLine_R:
    move.l   %d3,-(%sp)
| -0x70 for AND, +0x50 for XOR, -0x30 for OR.
    moveq    #-0x70,%d3
    tst.w    4+4(%sp)
    beq.s    3f    | (mode == A_REVERSE).
    cmpi.w   #2,4+4(%sp)
    bne.s    4f    | (mode-2 == 0), i.e (mode == A_XOR).
    moveq    #0x50,%d3
    bra.s    3f
4:
    moveq    #-0x30,%d3
3:
    lea      0f(%pc),%a1
    move.b   %d3,(%a1)          | patch memory with corresponding byte.
    cmp.w    %d1,%d2            | swap y values if necessary.
    bge.s    2f
    exg      %d1,%d2
2:
    sub.w    %d1,%d2            | d2 = abs(y1-y2).
    add.w    %d1,%d1            |
    move.w   %d1,%d3            |
    lsl.w    #4,%d1             |
    sub.w    %d3,%d1            | d1 = 2*abs(y1-y2)*16-2*abs(y1-y2) = 30 * height_in_pixels.
    adda.w   %d1,%a0

    move.w   %d0,%d1
    lsr.w    #3,%d0
    adda.w   %d0,%a0
    not.w    %d1
1:
    .byte    0x03               | one of bchg/bclr/bset %d1,(%a0)
0:
    .byte    0xD0               | Any of 0x50, 0x90, 0xD0 is suitable.
    lea      30(%a0),%a0
    dbf      %d2,1b

    move.l   (%sp)+,%d3
    rts
