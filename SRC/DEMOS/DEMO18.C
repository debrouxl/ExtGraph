#define NO_EXIT_SUPPORT
#define MIN_AMS 100
#define NO_AMS_CHECK
#define NO_CALC_DETECT
#include <tigcclib.h>         // Include All Header Files
#include "..\..\lib\extgraph.h"


// Main Function
void _main(void) {
    LCD_BUFFER backbuffer;

    LCD_save(backbuffer);

    if(GrayOn()) {
        FadeOutToBlack_CWS1_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_CCWS1_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_CCWS1_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_CWS1_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_LR_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_RL_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_RL_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_LR_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_TB_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,200);

        FadeOutToWhite_BT_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,200);

        FadeOutToBlack_BT_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,200);

        FadeOutToWhite_TB_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,200);

        FadeOutToBlack_RL18_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_LR18_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_LR18_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_RL18_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FillScreenWithGarbage_R(0x978FC6AB,LCD_SIZE,GetPlane(LIGHT_PLANE));
        FillScreenWithGarbage_R(0x45DA1328,LCD_SIZE,GetPlane(DARK_PLANE));

        FadeOutToBlack_RL28_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToWhite_LR28_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FadeOutToBlack_LR28_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

        FillScreenWithGarbage_R(0x978FC6AB,LCD_SIZE,GetPlane(LIGHT_PLANE));
        FillScreenWithGarbage_R(0x45DA1328,LCD_SIZE,GetPlane(DARK_PLANE));

        FadeOutToWhite_RL28_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);
    }

    GrayOff();
    LCD_restore(backbuffer);
    GKeyFlush();
    ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
