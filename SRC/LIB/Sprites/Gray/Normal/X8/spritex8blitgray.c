extern void SpriteX8_BLIT_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned char *sprt asm("%a1"),unsigned char *maskval,register short w asm("%d3"),register void *dest asm("%a0")) __attribute__((__stkparm__));

void __attribute__((__stkparm__)) GraySpriteX8_BLIT(short x,short y,short h,
                       unsigned char* sprite1,
                       unsigned char* sprite2,
                       unsigned char* maskval,
                       short bytewidth,
                       void* dest1,
                       void* dest2)
{
    SpriteX8_BLIT_R(x,y,h,sprite1,maskval,bytewidth,dest1);
    SpriteX8_BLIT_R(x,y,h,sprite2,maskval,bytewidth,dest2);
}
