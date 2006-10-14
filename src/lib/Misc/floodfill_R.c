//-----------------------------------------------------------------------------
// original code courtesy of Zeljko Juric
//-----------------------------------------------------------------------------
#include "../internal.h"  // for LCD_WIDTH and LCD_HEIGHT

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
  sp++; asm volatile("move.l %0,-(%%sp);"::"g"(*(long*)ENTRY));}}

#define POP(ENTRY) {sp--; asm volatile("move.l (%%sp)+,(%0);"::"a"(&ENTRY));}

void __attribute__((__regparm__(5))) FloodFill_R (short x,
                                                  short y,
                                                  unsigned short shade,
                                                  void* tmpplane,
                                                  void* dest)
{
    short x1,x2,dy,l,i,sp=0;
    short xmax=LCD_WIDTH-1,ymax=LCD_HEIGHT-1;
    unsigned char entry[4],texture[4],*ybase,*addr,mask,tmask;
    long diff;

    if (x<0||x>xmax||y<0||y>ymax||(EXT_GETPIX(dest,x,y))) return;

    memcpy(tmpplane,dest,3840);
    diff=((unsigned char*)dest)-(unsigned char*)tmpplane;

    for (i=3;i>=0;i--) {
        tmask=shade&15;
        shade>>=4;
        texture[i]=tmask+(tmask<<4);
    }

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
        tmask=texture[y&3];
        ybase=((unsigned char*)tmpplane)+((((y)+(y))<<4)-((y)+(y)));
        addr=ybase+(x>>3);
        mask=1<<(~x&7);

        while (x>=0&&!(*addr&mask)) {
            *addr|=mask; *(addr+diff)|=mask&tmask; x--;

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
                *(addr+diff)|=mask&tmask;
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
}

