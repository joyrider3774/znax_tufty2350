#include "pico/time.h"
#include "framebuffer.h"
#include "gamefuncs.h"
#include "common.h"
#include "defines.h"
#include "state_timeover.h"
#include "cworldparts.h"
#include "sound.h"
#include "state_gethighscorename.h"
#include "images/timeover_RGB565_BE.h"


void TimeOverInit()
{
    Time = to_ms_since_boot(get_absolute_time()) + 1250;
    Counter=0;    
    Timer = 0;
    CWorldParts_DeSelect(World, false);
}

void TimeOver()
{
    int Teller1,Teller2;
    
    if (GameState == GSTimeOverInit)
    {
        TimeOverInit();
        GameState = GSTimeOver;
    }
    if ((currButtons & BUTTON_HOME_MASK) && !(prevButtons & BUTTON_HOME_MASK))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }

    CWorldParts_Draw(World);
    switch(Counter)
    {
        case 0 :
            bufferDrawImageTransparent(fb,(WINDOW_WIDTH-timeover_width) >> 1, (WINDOW_HEIGHT - timeover_height) >> 1, timeover_data, timeover_width, timeover_height, false, false, false, COLOR_TRANSPARENT);
            break;
    }
    DrawStatusBar();
    if (Time < to_ms_since_boot(get_absolute_time()))
    {
        GameState = GSGetHighScoreNameInit;
    }
}

