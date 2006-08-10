| void GrayDrawChar2B(short x,short y,char c,short attr,void* lightplane,void* darkplane) __attribute__((__stkparm__)); // C prototype
|
| This code is not the best programming practice ever, although it could be
| coded in a much worse way...
| Equivalent C code:
/*
    PortSet(lightplane,239,127);
    DrawChar(x,y,c,attr);
    PortSet(darkplane,239,127);
    DrawChar(x,y,c,attr);
*/

.text
.globl GrayDrawChar2B
.even
GrayDrawChar2B:
        pea      (%a2)
        move.l   0xC8.w,%a2
        movea.l  0x1A2*4(%a2),%a0 | PortSet.
        pea      0x00EF007F | 239, 127.
        move.l   4+4+8+4(%sp),-(%sp)
        jsr      (%a0)
        movea.l  0x1A4*4(%a2),%a0 | DrawChar.
        move.l   4+4+4+8(%sp),-(%sp) | c, attr.
        move.l   4+4+0+12(%sp),-(%sp) | x, y.
        jsr      (%a0)

        movea.l  0x1A2*4(%a2),%a0 | PortSet.
        pea      0x00EF007F | 239, 127.
        move.l   4+4+12+20(%sp),-(%sp)
        jsr      (%a0)
        movea.l  0x1A4*4(%a2),%a0 | DrawChar.
        move.l   4+4+4+24(%sp),-(%sp) | c, attr.
        move.l   4+4+0+28(%sp),-(%sp) | x, y.
        jsr      (%a0)

        lea      32(%sp),%sp
        move.l   (%sp)+,%a2
        rts
