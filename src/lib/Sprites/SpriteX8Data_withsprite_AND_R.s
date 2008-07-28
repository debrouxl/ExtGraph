| C prototype: void SpriteX8Data_withsprite_AND_R(unsigned short h asm("%d2"), unsigned short bytewidth asm("%d1"), const unsigned char *src1 asm("%a0"), const unsigned char *src2 asm("%a2"), unsigned char *dest asm("%a1"));

.text
.globl SpriteX8Data_withsprite_AND_R
.even
SpriteX8Data_withsprite_AND_R:
    .include "Sprites/SpriteX8Data_macros.s"
    WithSpriteMacro and
