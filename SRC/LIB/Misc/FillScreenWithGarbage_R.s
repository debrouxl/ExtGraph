| void FillScreenWithGarbage_R(register unsigned long seed asm("%d0"),register unsigned short len asm("%d1"), register void *plane asm("%a0"));

.text
.globl FillScreenWithGarbage_R
.even
FillScreenWithGarbage_R:
    lsr.w    #2,%d1
    subq.w   #1,%d1 | adjust length.

| 32-bit LFSR...
    move.l   #0xA3000000,%d2
0:
    move.l   %d0,(%a0)+
    lsr.l    #1,%d0
    bcc.s    1f
    eor.l    %d2,%d0
1:
    dbf      %d1,0b

    rts
