//=============================================================================
// scrolls a specific number of lines of a LCD buffer (240x128) 1 column to the
// left (240 pixels get shifted) ...
//
// NOTE: given buffer has to start on an even address otherwise function will
//       crash !!!
//=============================================================================
void __attribute__((__stkparm__)) ScrollLeft240(unsigned short* buffer,unsigned short lines) {
    short* tmpbuffer = buffer;
    short  tmplines  = lines;

    tmpbuffer += (tmplines<<4) - (tmplines);
    tmplines--;

    asm volatile ("0:\n"
        "lsl.w  -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0)\n"
        "roxl.w -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0)\n"
        "roxl.w -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0)\n"
        "dbf %1,0b"
        : "=a" (tmpbuffer), "=d" (tmplines)
        : "0"  (tmpbuffer), "1"  (tmplines));
}
