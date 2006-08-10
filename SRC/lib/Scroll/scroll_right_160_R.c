//=============================================================================
// scrolls a specific number of lines of a LCD buffer (240x128) 1 column to the
// right (160 pixels get shifted) ...
//
// NOTE: given buffer has to start on an even address, otherwise function will
//       crash !!!
//=============================================================================
void __attribute__((__regparm__(2))) ScrollRight160_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) {
    short* tmpbuffer = buffer;
    short  tmplines  = lines;

    tmplines--;

    asm volatile ("0:\n"
        "lsr.w  (%0)+;roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+\n"
        "roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+\n"
        "lea 10(%0),%0\n"
        "dbf %1,0b"
        : "=a" (tmpbuffer), "=d" (tmplines)
        : "0"  (tmpbuffer), "1"  (tmplines));
}
