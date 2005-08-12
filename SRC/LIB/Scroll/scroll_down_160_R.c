//=============================================================================
// scrolls a specific number of lines of a LCD buffer (240x128) 1 line
// downwards (160 pixels get moved) ...
//
// NOTE: given buffer has to start on an even address, otherwise function will
//       crash !!!
//=============================================================================
void __attribute__((__regparm__(2))) ScrollDown160_R(unsigned short* buffer,unsigned short lines) {
    register short* dest = buffer;
    register short* src;
    register short  tmplines  = lines;

    dest += (tmplines<<4) - (tmplines) - 5;
    src   = dest - 15;

    tmplines -= 2;

    asm volatile ("0:\n"
        "move.l -(%0),-(%1);move.l -(%0),-(%1);move.l -(%0),-(%1)\n"
        "move.l -(%0),-(%1);move.l -(%0),-(%1)\n"
        "lea -10(%0),%0\n"
        "lea -10(%1),%1\n"
        "dbf %2,0b\n"
        "clr.l -(%1);clr.l -(%1);clr.l -(%1);clr.l -(%1);clr.l -(%1)"
        : "=a" (src), "=a" (dest), "=d" (tmplines)
        : "0"  (src), "1"  (dest), "2"  (tmplines));
}
