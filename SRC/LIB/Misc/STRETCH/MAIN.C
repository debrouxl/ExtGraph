// C Source File
// Created 02/01/2004; 21:51:17

#include <tigcclib.h>
#include "splash.h"

void screen_stretch(void *dst asm("%a3"), const void *src asm("%a4"));

unsigned char sprite[] = { 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18 };

volatile long ticks = 0, frames = 0;

DEFINE_INT_HANDLER (MyInt5) {
	ticks++;
}

// Main Function
void _main(void)
{
	BOOL bLoop = TRUE;
	int x = 120, y = 50;
	void *vplane1 = malloc(LCD_SIZE * 2), *vplane2 = vplane1 + LCD_SIZE;
	void *src1 = splash_layer1, *src2 = splash_layer2, *dst1 = vplane1, *dst2 = vplane2;
	void *plane1, *plane2;
	int i;
	
	INT_HANDLER OldInt1 = GetIntVec(AUTO_INT_1);
	INT_HANDLER OldInt2 = GetIntVec(AUTO_INT_2);
	INT_HANDLER OldInt5 = GetIntVec(AUTO_INT_5);
	SetIntVec(AUTO_INT_1, DUMMY_HANDLER);
	SetIntVec(AUTO_INT_2, DUMMY_HANDLER);
	SetIntVec(AUTO_INT_5, MyInt5);
	if (!GrayOn())
	{
		free(vplane1);
		return;
	}
	plane1 = GrayGetPlane(LIGHT_PLANE);
	plane2 = GrayGetPlane(DARK_PLANE);
	for (i = 0; i < LCD_HEIGHT; i++, dst1 += 30, dst2 += 30, src1 += 20, src2 += 20)
	{
		memcpy(dst1, src1, 20);
		memcpy(dst2, src2, 20);
	}
	Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
	Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
	while (bLoop) {
		if (_keytest(RR_LEFT)) {
			Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
			Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
			if (x > 0) x--;
			Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
			Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
		}
		if (_keytest(RR_UP)) {
			Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
			Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
			if (y > 0) y--;
			Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
			Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
		}
		if (_keytest(RR_RIGHT)) {
			Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
			Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
			if (x < 151) x++;
			Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
			Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
		}
		if (_keytest(RR_DOWN)) {
			Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
			Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
			if (y < 91) y++;
			Sprite8(x, y, 8, sprite, vplane1, SPRT_XOR);
			Sprite8(x, y, 8, sprite, vplane2, SPRT_XOR);
		}
		if (_keytest(RR_ESC)) {
			bLoop = FALSE;
		}
		if (TI89)
		{
			memcpy(plane1, vplane1, LCD_SIZE);
			memcpy(plane2, vplane2, LCD_SIZE);
		}
		else
		{
			screen_stretch(plane1, vplane1);
			screen_stretch(plane2, vplane2);
		}
		frames++;
	}
	PortRestore();
	SetIntVec(AUTO_INT_1, OldInt1);
	SetIntVec(AUTO_INT_2, OldInt2);
	SetIntVec(AUTO_INT_5, OldInt5);
	free(vplane1);
	ClrScr();
	MoveTo(0, 0);
	printf("%.2f", (float)frames * (float)20 / (float)ticks);
	GKeyFlush();
	while (ngetchx() != KEY_ENTER);
	GKeyFlush();
}