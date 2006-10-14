//-----------------------------------------------------------------------------
// original code courtesy of Zeljko Juric
//-----------------------------------------------------------------------------
#include "../internal.h"  // for LCD_WIDTH and LCD_HEIGHT
//#include "stdio.h"

#define EXT_PIXOFFSET(x,y)  ((((y)+(y))<<4)-((y)+(y))+((x)>>3))
#define EXT_PIXADDR(p,x,y)  (((unsigned char*)(p))+EXT_PIXOFFSET(x,y))
#define EXT_PIXMASK(x)      ((unsigned char)(0x80 >> ((x)&7)))
#define EXT_GETPIX_AM(a,m)  (*(a) & (m))
#define EXT_GETPIX(p,x,y)   EXT_GETPIX_AM(EXT_PIXADDR(p,x,y),EXT_PIXMASK(x))

#define EXT_PIXLEFT_AM(a,m)   asm("rol.b  #1,%0;bcc.s  0f;subq.l #1,%1;0:"\
                                  : "=d" (m), "=g" (a) : "0" (m), "1" (a))
#define EXT_PIXRIGHT_AM(a,m)  asm("ror.b  #1,%0;bcc.s  0f;addq.l #1,%1;0:"\
                                  : "=d" (m), "=g" (a) : "0" (m), "1" (a))


#define STACKBORDER 1500    // stack shouldn't go down lower than this


#define PUSH(ENTRY) { unsigned long spvalue; \
  asm ("move.l %%sp,%0":"=g"(spvalue)); if(spvalue>STACKBORDER) { \
  sp++; /*if (sp > maxsp) {maxsp = sp;};*/ asm volatile("move.l %0,-(%%sp);"::"g"(*(long*)ENTRY));}}

#define POP(ENTRY) {sp--; asm volatile("move.l (%%sp)+,(%0);"::"a"(&ENTRY));}


void __attribute__((__regparm__(3))) FloodFillMF_noshade_R(short x,
                                                   short y,
                                                   void* dest)
{
    short x1,x2,dy,l,sp=0/*,maxsp=0*/;
    short xmax=LCD_WIDTH-1,ymax=LCD_HEIGHT-1;
    unsigned char entry[4],*ybase,*addr,mask;
    long diff;
    void* tmpplane;

    if (x<0||x>xmax||y<0||y>ymax||(EXT_GETPIX(dest,x,y))) return;

    if (!(tmpplane = malloc(3840))) return;

    memcpy(tmpplane,dest,3840);
    diff=((unsigned char*)dest)-(unsigned char*)tmpplane;

    entry[0]=y;
    entry[1]=entry[2]=x;
    entry[3]=1;
    if(y<ymax) PUSH(entry);
    entry[0]++;
    entry[3]=-1;
    PUSH(entry);

    while (sp) {
        POP(entry);
        y=entry[0]+(dy=(signed char)entry[3]);
        x=x1=entry[1];
        x2=entry[2];
        entry[0]=y;
        ybase=((unsigned char*)tmpplane)+((((y)+(y))<<4)-((y)+(y)));
        addr=ybase+(x>>3);
        mask=1<<(~x&7);

        while (x>=0&&!(*addr&mask)) {
            *addr|=mask; *(addr+diff)|=mask; x--;
            EXT_PIXLEFT_AM(addr,mask);
        }
        if (x>=x1) goto skip;
        l=x+1;
        if(l<x1&&y-dy>=0&&y-dy<=ymax) {
            entry[1]=l; entry[2]=x1-1; entry[3]=-dy;
            PUSH(entry);
        }

        x=x1+1;
        do {
            addr=ybase+(x>>3);
            mask=1<<(~x&7);
            while (x<=xmax&&!(*addr&mask)) {
                *addr|=mask;
                *(addr+diff)|=mask;
                x++;
                EXT_PIXRIGHT_AM(addr,mask);
            }
            entry[1]=l;
            entry[2]=x-1;
            entry[3]=dy;
            if (y+dy>=0&&y+dy<=ymax) PUSH(entry);
            if (x>x2+1&&y-dy>=0&&y-dy<=ymax) {
                entry[1]=x2+1; entry[3]=-dy;
                PUSH(entry);
            }
skip:       x++;
            addr=ybase+(x>>3);
            mask=1<<(~x&7);

            while(x<=x2&&*addr&mask) {
                x++;
                EXT_PIXRIGHT_AM(addr,mask);
            }
            l=x;
        }
        while(x<=x2);
    }

    free(tmpplane);
    //printf_xy(0,0,"%hd",maxsp);
}

