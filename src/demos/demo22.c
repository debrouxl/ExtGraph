#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS
#define MIN_AMS 100
#define NO_AMS_CHECK

#ifdef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define C89_92V200(x,y) (x)
#else
#undef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define USE_TI92P
#define USE_V200
#define C89_92V200(x,y) (y)
#endif

#include <tigcclib.h>
#include "../../lib/extgraph.h" // NOTE: this path is just for this demo !!
#include "../../lib/tilemap.h"

// IMPORTANT NOTE:
// To get maximum performance for both "always redraw everything" and
// "redraw everything only if necessary" approaches,
// this program writes DIRECTLY in the screen planes. It does NOT:
// * use FastCopyScreen_R;
// * use doublebuffering.
// This works ONLY with a routine that allocates gray planes consecutively,
// like the modified grayscale routine in ExtGraph (../lib/gray.{s,o}).


#define NB_ETAPES 4
#define NB_ANIMS 21
#define MAP_WIDTH 16

// Contains map of tiles.
static const unsigned char map_base[10][MAP_WIDTH]={
{02,03, 8, 8, 8,02,02,04,05,02,11,00,00,00,00,00},
{02,02,02,02, 8,02,02,06,07,02,13,12,12,19,00,00},
{02,02,02,01, 8,02,02,02,02,02,02,02,01,13,19,00},
{05,02, 8, 8, 8, 8,01,02,02,02,02,02,03,02,11,00},
{07,02, 8,02,03, 8, 8, 8,03,02,03,03,02,02,11,00},
{ 8, 8, 8,02,02,02,03, 8, 8, 8, 8, 8, 8,02,11,00},
{02,01, 8,02,04,05,02,02,02,02,02,01,02,02,11,00},
{03, 8, 8,02,06,07,02,02,01,02,02,02,02,01,11,00},
{02, 8,02,02,02,02,02,02,02,02,02,02,02, 9,20,00},
{02, 8,02,02,01,02,02,01,02,02,03,01,02,11,00,00},
};

// Contains sprites for tile map. Taken from xtile by Scott Noveck.
static const short sprts[][32] = {
// 0 : Water
{0xFFFF,0x0000,0xCFCF,0x0000,0x8383,0x0000,0x3838,0x0000,0xFFFF,0x0000,0x1F1F,0x0000,0x4C4C,0x0000,0xE1E1,0x0000,0xFFFF,0x0000,0xCFCF,0x0000,0x8383,0x0000,0x3838,0x0000,0xFFFF,0x0000,0x1F1F,0x0000,0x4C4C,0x0000,0xE1E1,0x0000},	//Water1
// 4 : Flower
{0x3800,0x0000,0x3810,0x0000,0xC654,0x0000,0xC628,0x0000,0xC600,0x0000,0x3800,0x0000,0x3800,0x0000,0x0000,0x0000,0x0000,0x0000,0x1038,0x0000,0x5438,0x0000,0x28C6,0x0000,0x00C6,0x0000,0x00C6,0x0000,0x0038,0x0000,0x0038,0x0000},	//Flower1
// 8 : Grass
{0x0000,0x0000,0x1000,0x0000,0x5400,0x0000,0x2800,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0010,0x0000,0x0054,0x0000,0x0028,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},	//Grass2
// 9 : Plant
{0x0000,0x0000,0x0180,0x0180,0x63C6,0x6246,0x77EE,0x542A,0x7FFE,0x4DB2,0x6FF6,0x566A,0x77EE,0x4A52,0x3BDC,0x2664,0x1E78,0x1FF8,0x3BDC,0x27E4,0x774E,0x4AF2,0x7F7E,0x44A2,0x7FFE,0x7C3E,0x07E0,0x0420,0x03C0,0x03C0,0x0000,0x0000},	//Plant1
// 10 : Tree
{0x01FF,0x00FF,0x077F,0x0380,0x0DF8,0x0E00,0x17B0,0x1840,0x2F30,0x30C0,0x6E38,0x31C0,0x5C3F,0x63C0,0xDC1F,0x63E0,0x9C07,0xE3F8,0x9E00,0xE1FF,0x9F00,0xE0FF,0x9FC0,0xE03F,0x8FF0,0xF00F,0x8FF8,0xF007,0x83FF,0xFC00,0x80FF,0xFF00},	//Tree1
{0xFF80,0xFF00,0xE0E0,0x1FC0,0xF330,0x0CF0,0x79C8,0x0638,0x78E4,0x071C,0xF866,0x079C,0xF872,0x078E,0xF073,0x0F8E,0xE071,0x1F8F,0x00F1,0xFF0F,0x01F1,0xFE0F,0x07F1,0xF80F,0x0FF1,0xF00F,0x1FE1,0xE01F,0xFFC1,0x003F,0xFF01,0x00FF},	//Tree2
{0x803F,0xFFC0,0xC01F,0x7FE0,0xC007,0x7FF8,0xE000,0xBFFF,0xF000,0x9FFF,0xBC00,0xCFFF,0xE3E0,0x7FFF,0xFFD0,0x1C3F,0x79F8,0x080F,0x71FF,0x1007,0x33B8,0x2060,0x3778,0x20F0,0x3D94,0x23F8,0x3E0F,0x1FF8,0x0787,0x007C,0x003F,0x0003},	//Tree3
{0xFC01,0x03FF,0xF803,0x07FE,0xF003,0x0FFE,0x0007,0xFFFD,0x000F,0xFFF9,0x003D,0xFFF3,0x07C7,0xFFFE,0x0BFF,0xFC38,0x1F3E,0xF010,0xFF1E,0xE008,0xFD8C,0x0604,0xFECC,0x0F04,0xE9BC,0x1FC4,0xF07C,0x1FF8,0xE1C0,0x3E00,0xFC00,0xC000},	//Tree4
// 14 : Road
{0x7E7E,0x0000,0xFFFF,0x0000,0xF7F7,0x0000,0xFFFF,0x0000,0xBFBF,0x0000,0xFBFB,0x0000,0xFFFF,0x0000,0x7E7E,0x0000,0x7E7E,0x0000,0xFFFF,0x0000,0xF7F7,0x0000,0xFFFF,0x0000,0xBFBF,0x0000,0xFBFB,0x0000,0xFFFF,0x0000,0x7E7E,0x0000},	//Road1
// 15 : Edge
{0x0BFF,0x07FF,0x2C00,0x1FFF,0x57FF,0x3800,0x3804,0x6000,0xD040,0x6000,0x71FF,0xC000,0xA200,0xC1FF,0xA5FF,0xC3FF,0xA57F,0xC380,0xA5FF,0xC300,0xB5F8,0xC31F,0xA5CC,0xC33F,0xA5C6,0xC33F,0xA5C7,0xC33F,0xADC3,0xC33F,0xA5C3,0xC33F},	//Edge1
{0xFFFF,0xFFFF,0x0000,0xFFFF,0xFFFF,0x0000,0x0404,0x0000,0x4040,0x0000,0xFFFF,0x0000,0x0000,0xFFFF,0xFFFF,0xFFFF,0x1FF8,0xE007,0xF81F,0x07E0,0xE047,0x1FF8,0x0040,0xFFBF,0x2000,0xFFFF,0x0000,0xFFFF,0x07E0,0xFFFF,0xFFFF,0xFFFF},	//Edge2
{0xA5C3,0xC33F,0xA5C3,0xC33F,0xB583,0xC37F,0xA583,0xC37F,0xA583,0xC37F,0xA5C7,0xC33F,0xADC7,0xC33F,0xA5C7,0xC33F,0xA5C3,0xC33F,0xA5C3,0xC33F,0xB583,0xC37F,0xA583,0xC37F,0xA583,0xC37F,0xA5C7,0xC33F,0xADC7,0xC33F,0xA5C7,0xC33F},	//Edge3
{0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x0C0C,0xFFFF,0x0000,0xFFFF,0x4040,0xFFFF,0x0000,0xFFFF,0xC7C7,0x3838,0xFFFF,0x0000,0xFFFF,0xFFFF,0x0000,0xFFFF,0xFFFF,0x0000,0x0404,0x0000,0x4040,0x0000,0xFFFF,0x0000,0x0000,0xFFFF,0xFFFF,0xFFFF},	//Edge4
{0xA5C7,0xC33F,0xA5CF,0xC33F,0xB5DC,0xC33F,0xA5D0,0xC33F,0xA5C0,0xC33F,0xA5E0,0xC31F,0xAD7F,0xC380,0xA5BF,0xC3C0,0xA5FF,0xC3FF,0xA200,0xC1FF,0xB1FF,0xC000,0x9804,0xE000,0xCE40,0xF000,0x63FF,0xFC00,0xB000,0x7FFF,0x6FFF,0x1FFF},	//Edge5
// 20
{0xFFD0,0xFFE0,0x0034,0xFFF8,0xFFEA,0x001C,0x041C,0x0006,0x400B,0x0006,0xFF8E,0x0003,0x0045,0xFF83,0xFFA5,0xFFC3,0xFEA5,0x01C3,0xFFA5,0x00C3,0x1BB5,0xFCC3,0x33A5,0xFCC3,0x63A5,0xFCC3,0xE3A5,0xFCC3,0xC3AD,0xFCC3,0xC3A5,0xFCC3},	//Edge6
{0xC3A5,0xFCC3,0xC3A5,0xFCC3,0xC1B5,0xFEC3,0xC1A5,0xFEC3,0xC1A5,0xFEC3,0xE3A5,0xFCC3,0xE3AD,0xFCC3,0xE3A5,0xFCC3,0xC3A5,0xFCC3,0xC3A5,0xFCC3,0xC1B5,0xFEC3,0xC1A5,0xFEC3,0xC1A5,0xFEC3,0xE3A5,0xFCC3,0xE3AD,0xFCC3,0xE3A5,0xFCC3},	//Edge7
{0xC3A5,0xFCC3,0xC3A2,0xFCC1,0xC1B1,0xFEC0,0xC198,0xFEE0,0xC1CE,0xFEF0,0xE363,0xFCFC,0xE3B0,0xFC7F,0xE36F,0xFC1F,0xC1F8,0xFE07,0xC01F,0xFFE0,0xC047,0xFFF8,0xC040,0xFFBF,0xC000,0xFFFF,0xE000,0x7FFF,0x78E0,0x3FFF,0xBFFF,0x1FFF},	//Edge8
{0xE3A5,0xFCC3,0xF3A5,0xFCC3,0x3BB5,0xFCC3,0x0BA5,0xFCC3,0x03A5,0xFCC3,0x07A5,0xF8C3,0xFEAD,0x01C3,0xFDA5,0x03C3,0xFFA5,0xFFC3,0x0045,0xFF83,0xFF8D,0x0003,0x0419,0x0007,0x4073,0x000F,0xFFC6,0x003F,0x000D,0xFFFE,0xFFF6,0xFFF8},	//Edge9
{0x8FFF,0x1FFF,0x3FFF,0x3FFF,0x7C0C,0x7FFF,0x7000,0xFFFF,0xE040,0xFFFF,0xE300,0xFCFF,0xC7C7,0xF838,0xC7FF,0xF800,0xC37F,0xFCFF,0xC3E0,0xFCFF,0xC1CF,0xFEF0,0xC190,0xFEE0,0xC1A0,0xFEC0,0xE3A3,0xFCC0,0xE3A6,0xFCC1,0xE3A5,0xFCC3},	//Edge17
// 25
{0xFFF1,0xFFF8,0xFFFC,0xFFFC,0x0C3E,0xFFFE,0x000E,0xFFFF,0x4007,0xFFFF,0x00C7,0xFF3F,0xC7E3,0x381F,0xFFE3,0x001F,0xFEC3,0xFF3F,0x03C3,0xFF3F,0xF983,0x077F,0x0D83,0x037F,0x0583,0x037F,0xC5C7,0x033F,0x65C7,0x833F,0xA5C7,0xC33F},	//Edge19
{0xA5C3,0xC33F,0x45C3,0x833F,0x8D83,0x037F,0x1983,0x077F,0x7383,0x0F7F,0xC6C7,0x3F3F,0x0DC7,0xFE3F,0xF6C7,0xF83F,0x1F83,0xE07F,0xF803,0x07FF,0xE003,0x1FFF,0x0003,0xFFFF,0x2003,0xFFFF,0x0007,0xFFFE,0x071E,0xFFFC,0xFFFD,0xFFF8},	//Edge20
};

static const unsigned char sprite_8[2*8] = {0x81,0x55,0x43,0xAA,0x27,0x55,0x1F,0xAA,0x1F,0x55,0x3E,0xAA,0x7C,0x54,0xF8,0xA8};

static const unsigned short sprite_16[2*16] =
{
0b0000011111100000,0b0000011111100000,
0b0001100000011000,0b0001111111111000,
0b0010000000000100,0b0011111111111100,
0b0100000000000010,0b0111111111111110,
0b0100000000000010,0b0111101111011110,
0b1000000000000001,0b1111010110101111,
0b1000000000000001,0b1111111111111111,
0b1000000000000001,0b1111111111111111,
0b1000000000000001,0b1111111001111111,
0b1000000000000001,0b1110011111100111,
0b1000000000000001,0b1110101111010111,
0b0100000000000010,0b0111010000101110,
0b0100000000000010,0b0111101111011110,
0b0010000000000100,0b0011110000111100,
0b0001100000011000,0b0001111111111000,
0b0000011111100000,0b0000011111100000
};

static const unsigned long sprite_32[2*32]  = {0x80000001,0x55555555,0x40000003,0xAAAAAAAA,0x20000007,0x55555555,0x1000000F,0xAAAAAAAA,0x0000001F,0x55555555,0x0000003F,0xAAAAAAAA,0x0000007F,0x55555555,0x000000FF,0xAAAAAAAA,0x000001FF,0x55555555,0x000003FF,0xAAAAAAAA,0x000007FF,0x55555555,0x00000FFF,0xAAAAAAAA,0x00001FFF,0x55555555,0x00003FFF,0xAAAAAAAA,0x00007FFF,0x55555555,0x0000FFFF,0xAAAAAAAA,0x0001FFFF,0x55555555,0x0003FFFF,0xAAAAAAAA,0x0007FFFF,0x55555555,0x000FFFFF,0xAAAAAAAA,0x001FFFFF,0x55555555,0x003FFFFF,0xAAAAAAAA,0x007FFFFF,0x55555555,0x00FFFFFF,0xAAAAAAAA,0x01FFFFFF,0x55555555,0x03FFFFFF,0xAAAAAAAA,0x07FFFFFF,0x55555555,0x0FFFFFFF,0xAAAAAAAA,0x1FFFFFFF,0x55555555,0x3FFFFFFE,0xAAAAAAAA,0x7FFFFFFC,0x55555554,0xFFFFFFF8,0xAAAAAAA8};


static unsigned short mode = 0;


#define HEIGHT 128
#define WIDTH  240

// #define NR_SPRITES 16
#define NR_SPRITES 12

static void DrawSprites(register const unsigned short sx asm("%d3"), register const unsigned short sy asm("%d4")) {
  short i;
  if (!mode) {
    for (i = 0; i < 3; i++) {
      GrayClipISprite8_TRANW_R(sx,sy+32*i,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite8_TRANB_R(sx+40,sy+32*i,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite8_OR_R(sx+80,sy+32*i,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite8_XOR_R(sx+120,sy+32*i,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    }
  }
  else if (mode == 1) {
    for (i = 0; i < 3; i++) {
      GrayClipISprite16_TRANW_R(sx,sy+32*i,16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite16_TRANB_R(sx+40,sy+32*i,16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite16_OR_R(sx+80,sy+32*i,16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite16_XOR_R(sx+120,sy+32*i,16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    }
  }
  else {
    for (i = 0; i < 3; i++) {
      GrayClipISprite32_TRANW_R(sx,sy+32*i,32,sprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite32_TRANB_R(sx+40,sy+32*i,32,sprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite32_OR_R(sx+80,sy+32*i,32,sprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayClipISprite32_OR_R(sx+120,sy+32*i,32,sprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    }
  }
}

static void RestoreBackground(register unsigned short * const savebackground asm("%a3")) {
  short i;
  if (!mode) {
    for (i = 0; i < 3; i++) {
      GrayFastPutBkgrnd8_R(&savebackground[i*FGBKGRND8_BUFSIZE(8)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd8_R(&savebackground[(i+3)*FGBKGRND8_BUFSIZE(8)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd8_R(&savebackground[(i+6)*FGBKGRND8_BUFSIZE(8)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd8_R(&savebackground[(i+9)*FGBKGRND8_BUFSIZE(8)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    }
  }
  else if (mode == 1) {
    for (i = 0; i < 3; i++) {
      GrayFastPutBkgrnd16_R(&savebackground[i*FGBKGRND16_BUFSIZE(16)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd16_R(&savebackground[(i+3)*FGBKGRND16_BUFSIZE(16)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd16_R(&savebackground[(i+6)*FGBKGRND16_BUFSIZE(16)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd16_R(&savebackground[(i+9)*FGBKGRND16_BUFSIZE(16)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    }
  }
  else {
    for (i = 0; i < 3; i++) {
      GrayFastPutBkgrnd32_R(&savebackground[i*FGBKGRND32_BUFSIZE(32)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd32_R(&savebackground[(i+3)*FGBKGRND32_BUFSIZE(32)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd32_R(&savebackground[(i+6)*FGBKGRND32_BUFSIZE(32)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
      GrayFastPutBkgrnd32_R(&savebackground[(i+9)*FGBKGRND32_BUFSIZE(32)/2],GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    }
  }
}

static void SaveBackground(register const unsigned short sx asm("%d3"), register const unsigned short sy asm("%d4"), register unsigned short * const savebackground asm("%a3")) {
  short i = 0;
  // Save background.
  if (!mode) {
    for (i = 0; i < 3; i++) {
      GrayFastGetBkgrnd8_R(sx,sy+32*i,8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[i*FGBKGRND8_BUFSIZE(8)/2]);
      GrayFastGetBkgrnd8_R(sx+40,sy+32*i,8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+3)*FGBKGRND8_BUFSIZE(8)/2]);
      GrayFastGetBkgrnd8_R(sx+80,sy+32*i,8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+6)*FGBKGRND8_BUFSIZE(8)/2]);
      GrayFastGetBkgrnd8_R(sx+120,sy+32*i,8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+9)*FGBKGRND8_BUFSIZE(8)/2]);
    }
  }
  else if (mode == 1) {
    for (i = 0; i < 3; i++) {
      GrayFastGetBkgrnd16_R(sx,sy+32*i,16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[i*FGBKGRND16_BUFSIZE(16)/2]);
      GrayFastGetBkgrnd16_R(sx+40,sy+32*i,16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+3)*FGBKGRND16_BUFSIZE(16)/2]);
      GrayFastGetBkgrnd16_R(sx+80,sy+32*i,16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+6)*FGBKGRND16_BUFSIZE(16)/2]);
      GrayFastGetBkgrnd16_R(sx+120,sy+32*i,16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+9)*FGBKGRND16_BUFSIZE(16)/2]);
    }
  }
  else {
    for (i = 0; i < 3; i++) {
      GrayFastGetBkgrnd32_R(sx,sy+32*i,32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[i*FGBKGRND32_BUFSIZE(32)/2]);
      GrayFastGetBkgrnd32_R(sx+40,sy+32*i,32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+3)*FGBKGRND32_BUFSIZE(32)/2]);
      GrayFastGetBkgrnd32_R(sx+80,sy+32*i,32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+6)*FGBKGRND32_BUFSIZE(32)/2]);
      GrayFastGetBkgrnd32_R(sx+120,sy+32*i,32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),&savebackground[(i+9)*FGBKGRND32_BUFSIZE(32)/2]);
    }
  }
}

// If behaviour == 0, always redraw everything.
// If behaviour != 0, redraw everything only if necessary.
static short RenderMap(Plane *plane, void *dest, short behaviour) {
  unsigned short x=0,y=0,seq=0,count=0;
  register unsigned short sx asm("%d3") = 8;
  register unsigned short sy asm("%d4") = 8;
  unsigned short mov=0;
  unsigned short savebackground[NR_SPRITES*FGBKGRND32_BUFSIZE(32)/2];
  register unsigned short *pSavebackground asm("%a3") = savebackground;

  DrawPlane(x,y,plane,dest,TM_GRPLC,TM_G16B);
  SaveBackground(sx,sy,pSavebackground);

  OSFreeTimer(USER_TIMER);
  OSRegisterTimer(USER_TIMER,2); // ~100 ms with default settings.
  OSFreeTimer(1);
  OSRegisterTimer(1,300); // ~15 s with default settings.

  do {
    if (OSTimerExpired(USER_TIMER)) {
      // Timer has expired, so we have to move the background.
      if (mov == 0) {
        if (x < 16*16-WIDTH-1) x++;
        else mov++;
      }
      else if (mov == 1) {
        if (y < 16*10-HEIGHT-1) y++;
        else mov++;
      }
      else if (mov == 2) {
        if (x > 0) x--;
        else mov++;
      }
      else if (mov == 3) {
        if (y > 0) y--;
        else mov = 0;
      }

      OSTimerRestart(USER_TIMER);
      // Don't forget to reinitialize the buffers !
      if (behaviour) {
        DrawPlane(x,y,plane,dest,TM_GRPLC,TM_G16B);
        SaveBackground(sx,sy,pSavebackground);
      }
      continue;
    }
    
    if (!behaviour) {
      DrawPlane(x,y,plane,dest,TM_GRPLC,TM_G16B);
    }
    else {
      RestoreBackground(pSavebackground);
    }

    // Move sprites.
    switch (seq) {
      case 0: sx++;       break;
      case 1: sy++;       break;
      case 2: sx--;       break;
      case 3: sx--;       break;
      case 4: sy--;       break;
      case 5: sy--;       break;
      case 6: sx++;       break;
      case 7: sx++;       break;
      case 8: sy++, sx--; break;
    }

    if (behaviour) { // Don't save if just moved
      SaveBackground(sx,sy,pSavebackground);
    }

    DrawSprites(sx,sy);

    (++seq==9)?seq=0:seq;
    count++;

  } while (!(OSTimerExpired(1)));
  OSFreeTimer(USER_TIMER);
  OSFreeTimer(1);
  return count;
}


void _main(void) {
  INT_HANDLER ai1;
  char *block=malloc(BIG_VSCREEN_SIZE*2); // Two big_vscreens.
  short frame1=0, frame2=0;
  char s[50];
  Plane plane;
  LCD_BUFFER backbuffer;

  LCD_save(backbuffer);

  if(!block)
    return;

// Initialisation du plane
  plane.matrix=map_base;
  plane.width=16;
  plane.sprites=sprts;
  plane.big_vscreen=block;
  plane.force_update=1;

  ai1=GetIntVec(AUTO_INT_1);

  SetIntVec(AUTO_INT_1,DUMMY_HANDLER);

  // Test "8", "16" and "32" drawing functions.
  for (mode = 0; mode < 3; mode++) {
    if (GrayOn())
    {
      frame1 = RenderMap(&plane,GrayGetPlane(DARK_PLANE),0);

      frame2 = RenderMap(&plane,GrayGetPlane(DARK_PLANE),1);
      GrayOff();

      SetIntVec(AUTO_INT_1,ai1);

      sprintf(s,"redraw:%d save&restore:%d (higher=faster)",frame1,frame2);
      ClrScr();
    }
    else {
      strcpy(s,"Grayscale init failed");
    }
    ST_helpMsg(s);
    while (!(_rowread(0xF000)&0xFF));
    asm("move.l #0x17FFF,%%d0; 0: subq.l #1,%%d0; bpl.s 0b" : : : "d0","cc");
  }

  free(block);
  GKeyFlush();
  LCD_restore(backbuffer);
  GKeyFlush();
  ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
