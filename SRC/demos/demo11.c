/******************************************************************************
*
* project name:    ExtGraph
* initial date:    03/04/2002
* author:          thomas.nussbaumer@gmx.net
* description:     demonstration of the collision detection function
*                  (balls bouncing around the screen)
*
* $Id: demo11.c,v 1.2 2002/04/05 13:45:40 tnussb Exp $
*
*******************************************************************************/

#define NO_EXIT_SUPPORT
#define OPTIMIZE_ROM_CALLS

#define NO_AMS_CHECK
#define MIN_AMS 100

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
#include "../../lib/extgraph.h"  // NOTE: this path is just for this demo !!
                                 //       if the extgraph library is correctly
                                 //       installed you should use:
                                 //
                                 //       #include <extgraph.h>


//#define BUILD16BIT  // uncomment this if you want to test function TestCollide16()


#if defined(BUILD16BIT)

#define SPRITE_WIDTH             16
#define SPRITE_HEIGHT            16
#define DRAWSPRITE(x,y)          Sprite16_OR_R(x,y,SPRITE_HEIGHT,spritedata,doublebuffer)
#define TESTCOLLIDE(x0,y0,x1,y1) TestCollide16_R(x0,y0,x1,y1,SPRITE_HEIGHT,spritedata,spritedata)

unsigned short spritedata[16] = {
    0b0000011111100000,
    0b0001111111111000,
    0b0011111111111100,
    0b0111111111111110,
    0b0111111111111110,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b0111111111111110,
    0b0111111111111110,
    0b0011111111111100,
    0b0001111111111000,
    0b0000011111100000};

#else

#define SPRITE_WIDTH             8
#define SPRITE_HEIGHT            8
#define DRAWSPRITE(x,y)          Sprite8_OR_R(x,y,SPRITE_HEIGHT,spritedata,doublebuffer)
#define TESTCOLLIDE(x0,y0,x1,y1) TestCollide8_R(x0,y0,x1,y1,SPRITE_HEIGHT,spritedata,spritedata)

unsigned char spritedata[8] = {
    0b00111100,
    0b01111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100};
#endif

//-----------------------------------------------------------------------------
// structure used for each ball in our bouncing balls simulation
//-----------------------------------------------------------------------------
typedef struct {
    short x;     // x position of the ball
    short y;     // y position of the ball
    short dirx;  // increment used for x position
    short diry;  // increment used for y position
    short newx;  // new x position (ONLY temporarily used)
    short newy;  // new y position (ONLY temporarily used)
} BALL_T;


//=============================================================================
// calculate new (temporary) position of ball using x/y and dirx/diry
//=============================================================================
static inline void CalcNewPosition(BALL_T* ball,short max_x,short max_y) {
    short nx,ny; // calculate new x position

    nx = ball->x + ball->dirx;
    ny = ball->y + ball->diry;

    // check nx and modify it if we bounce from the screen border ...
    if (nx>max_x || nx<0) {
        ball->dirx = - ball->dirx;
        nx         = ball->x + ball->dirx; // recalculate nx
    }

    // check nx and modify it if we bounce from the screen border ...
    if (ny>max_y || ny<0) {
        ball->diry = -ball->diry;
        ny         = ball->y + ball->diry; // recalculate ny
    }

    ball->newx=nx;
    ball->newy=ny;
}


//=============================================================================
// returns 1 if ESCAPE is pressed
//=============================================================================
static inline short EscapePressed(void) {
    if (TI89) {
        if (_rowread(~(1<<6)) & (1<<0)) return 1;
    }
    else {
        if (_rowread(~(1<<8)) & (1<<6)) return 1;
    }

    return 0;
}

//=============================================================================
// exchange directions
//=============================================================================
static inline void ExchangeDirections(BALL_T* b1,BALL_T* b2) {
    // collision detected -> exchange dirx/diry of involved balls
    short tmp = b1->dirx;
    b1->dirx  = b2->dirx;
    b2->dirx  = tmp;
    tmp       = b1->diry;
    b1->diry  = b2->diry;
    b2->diry  = tmp;
}


#define NR_BALLS 14
#define STEP     1

//    short       max_x = LCD_WIDTH-SPRITE_WIDTH-1;
//    short       max_y = LCD_HEIGHT-SPRITE_HEIGHT-1;
#define max_x (LCD_WIDTH-SPRITE_WIDTH-1)
#define max_y (LCD_HEIGHT-SPRITE_HEIGHT-1)

    BALL_T      balls[NR_BALLS] = {{0,0,STEP,STEP,0,0},              // ball in the upper left corner
                                   {0,max_y,STEP,-STEP,0,0},         // ball in the upper right corner
                                   {max_x,0,-STEP,STEP,0,0},         // ball in the lower left corner
                                   {max_x,max_y,-STEP,-STEP,0,0},    // ball in the lower right corner
                                   {max_x/4,0,0,STEP,0,0},
                                   {max_x/4,max_y,0,-STEP,0,0},
                                   {2*max_x/4,0,0,STEP,0,0},
                                   {2*max_x/4,max_y,0,-STEP,0,0},
                                   {3*max_x/4,0,0,STEP,0,0},
                                   {3*max_x/4,max_y,0,-STEP,0,0},
                                   {0,max_y/2,STEP,0,0,0},
                                   {max_x,max_y/2,-STEP,0,0,0},
                                   {max_x/2-SPRITE_WIDTH,max_y/2,-STEP,0,0,0},
                                   {max_x/2+SPRITE_WIDTH,max_y/2,+STEP,0,0,0}};


//=============================================================================
// as usual our main function ...
//=============================================================================
void _main(void) {
    LCD_BUFFER  lcd;
    LCD_BUFFER  doublebuffer;
    short       i;
    short       ball_to_update;
    INT_HANDLER oldint1        = GetIntVec(AUTO_INT_1);  // fetch default interrupt handler
    INT_HANDLER oldint5        = GetIntVec(AUTO_INT_5);  // fetch default interrupt handler

    // save screen
    LCD_save(lcd);

    // install dummy interrupt handlers for AUTO_INT1 and AUTO_INT5
    SetIntVec(AUTO_INT_1,DUMMY_HANDLER);
    SetIntVec(AUTO_INT_5,DUMMY_HANDLER);

    do {
        // clear doublebuffer
        memset(doublebuffer,0,LCD_SIZE);
        for (i=0;i<NR_BALLS;i++) {
            // NOTE: DRAWSPRITE is a macro defined at the beginning of this file!
            DRAWSPRITE(balls[i].x,balls[i].y);
        }


        // copy double buffer to visible screen
        FastCopyScreen_R(doublebuffer,LCD_MEM);

        for (ball_to_update=0;ball_to_update<NR_BALLS;ball_to_update++) {
            // calculate new position of ball which should get updated
            CalcNewPosition(&balls[ball_to_update],max_x,max_y);


            // loop over all possible combinations and check for collision ...
            for (i=0;i<NR_BALLS;i++) {
                if (i==ball_to_update) continue; // don't check against myself

                // NOTE: TESTCOLLIDE is a macro defined at the beginning of this file!
                if (TESTCOLLIDE(balls[ball_to_update].newx,balls[ball_to_update].newy,balls[i].newx,balls[i].newy)) {
                    // collision detected -> exchange dirx/diry of involved balls
                    ExchangeDirections(&balls[ball_to_update],&balls[i]);

                    // recalculate new position of ball which should get updated
                    CalcNewPosition(&balls[ball_to_update],max_x,max_y);

                    // if we still stick together than this opponent then this
                    // is not the right target to change my direction ...
                    if (TESTCOLLIDE(balls[ball_to_update].newx,balls[ball_to_update].newy,balls[i].newx,balls[i].newy)) {
                        ExchangeDirections(&balls[ball_to_update],&balls[i]);
                        CalcNewPosition(&balls[ball_to_update],max_x,max_y);
                    }
                }
            }

            // NOTE: this demo is somewhat sloppy. Normally we should not
            //       proceed if a collision is detected AND we shouldn't do the
            //       VERY simple collision detection routine above.
            //       But I don't care about this. It seems to be good enough
            //       to demonstrate the bouncing balls ...
            balls[ball_to_update].x = balls[ball_to_update].newx;
            balls[ball_to_update].y = balls[ball_to_update].newy;
        }
    }
    while (!EscapePressed());

    // restore old interrupt handlers
    SetIntVec(AUTO_INT_1,oldint1);
    SetIntVec(AUTO_INT_5,oldint5);

    // restore screen
    LCD_restore(lcd);

    // empty the keyboard buffer and write "powered by ..." string
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);

}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log: demo11.c,v $
// Revision 1.2  2002/04/05 13:45:40  tnussb
// final version for distribution v1.00
//
// Revision 1.1  2002/04/03 18:36:21  tnussb
// initial version
//
//
