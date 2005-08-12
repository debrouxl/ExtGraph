//=============================================================================
// scrolls a specific number of lines of a LCD buffer (240x128) 1 line upwards
// (160 pixels gets moved) ...
//
// NOTE: given buffer have to start on an even address otherwise function will
//       crash !!!
//=============================================================================
void __attribute__((__stkparm__)) ScrollUp160(unsigned short* buffer,unsigned short lines) {
    register short* dest = buffer;
    register short* src  = dest + 15;
    register short  tmplines = lines;

    tmplines -= 2;

    asm volatile ("0:\n"
        "move.l (%0)+,(%1)+;move.l (%0)+,(%1)+;move.l (%0)+,(%1)+\n"
        "move.l (%0)+,(%1)+;move.l (%0)+,(%1)+\n"
        "lea 10(%0),%0\n"
        "lea 10(%1),%1\n"
        "dbf %2,0b\n"
        "clr.l (%1)+;clr.l (%1)+;clr.l (%1)+;clr.l (%1)+;clr.l (%1)+"
        : "=a" (src), "=a" (dest), "=d" (tmplines)
        : "0"  (src),  "1" (dest), "2"  (tmplines));
}
