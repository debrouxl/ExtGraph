/* Generic Sprite Scaling routine
 * by Jim Haskell
 * email: jimhaskell@yahoo.com
 * ICQ: 7448076
 *
 * Copyleft: The usual. This program was released as and should stay open-source.
 *           Feel free to edit/delete/add to these routines as you wish, just give
 *             me credit for the original work. If you do anything spectacular to
 *             increase the speed, please let me know.
 *           If you want to use it to make money, talk to me and get permission.
 *           If this program crashes or other bad things happens to your calculator,
 *             then you are SOL. It's not my fault.
 *
 * [modified and integrated into ExtGraph library by thomas.nussbaumer@gmx.net]
 */
extern const unsigned char bit_table[8];

#define getpixel16(s,x,y)  (*((unsigned char *)(s)+((y)+(y))+((x)>>3)))&bit_table[(x)&7]

void ScaleSprite16_XOR(const unsigned short *sprite,void *dest,short x0,short y0,short sizex,short sizey) {
    short x;//,y;
    unsigned short u,v=0,du=(unsigned short)(16<<8)/(unsigned short)sizex,dv=(unsigned short)(16<<8)/(unsigned short)sizey,pix16,pixscreen,tempv;
    unsigned char *src;
    unsigned char mask,origmask=0x80>>(x0&7);

    dest = ((unsigned char *)(dest))+((((y0)+(y0))<<4)-((y0)+(y0)))+((x0)>>3);
//    for (y = sizey;(y--);) {
    for (sizey = sizey;(sizey--);) {
        u=0;
        mask=origmask;
        tempv=v>>8;
        src = dest;
        for (x = sizex;(x--);) {
            pix16=getpixel16(sprite,u>>8,tempv);
            pixscreen=*src&mask;

            if (pix16&&pixscreen) *src&=~mask;
            else if (!pix16&&!pixscreen) *src&=~mask;
            else *src|=mask;
            asm("ror.b #1,%0;bcc.s 0f;addq.l #1,%1;0:":"=d" (mask),"=g" (src):"0"(mask),"1"(src));
            u+=du;
        }
        v+=dv;

        (unsigned char *)dest += 30;
    }
}