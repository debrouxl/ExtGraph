// Generic Sprite Scaling routine by Julien Richard-Foy.
// Significantly faster than the routine by Jim Haskell, Julien allowed me
// to relicense his routines under the LGPL, and I cannot reach Jim
// Haskell to ask him for the same thing.

void __attribute__((__stkparm__)) ScaleSprite8_OR(unsigned char *sprite,void *dest,short x0,short y0,short sizex,short sizey)
{
	short dx,dy;
	unsigned char maskorig,mask;
	unsigned char masksrc;
	char *tmpdest;

	(unsigned char *)dest+=((((y0)+(y0))<<4)-((y0)+(y0)))+((x0)>>3);
	maskorig=(0x80)>>(x0&7);

	dy=8/1-sizey;

	for(y0=sizey;y0--;)
	{
		if(dy>=0) {
			do
			{
				dy-=sizey, sprite++;
			} while(dy>0);
                }

		tmpdest=dest;
		masksrc=0x80;
		mask=maskorig;
		dx=8/1-sizex;
		for(x0=sizex;x0--;)
		{
			if(dx>=0) {
				do
				{
					dx-=sizex;
					masksrc>>=1;
				} while(dx>0);
                        }

			if(*sprite & masksrc) {
				*tmpdest ^= mask;
                        }
			asm("ror.b #1,%0;bcc.s 0f;addq.l #1,%1;0:":"=d" (mask),"=g" (tmpdest):"0"(mask),"1"(tmpdest));
			dx+=8;
		}
		(unsigned char *)dest+=30;
		dy+=8;
	}
}
