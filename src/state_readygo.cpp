#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "framebuffer.h"
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "cworldparts.h"
#include "sound.h"
#include "state_readygo.h"
#include "images/background_RGB565_BE.h"
#include "images/ready_RGB565_BE.h"
#include "images/go_RGB565_BE.h"

void ReadyGoInit()
{
    srand(to_us_since_boot(get_absolute_time()));
    CWorldParts_NewGame(World);
    Score = 0;
    Time = to_ms_since_boot(get_absolute_time());
    Counter=0;
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
}
void ReadyGo()
{
    
    if(GameState == GSReadyGoInit)
    {
        ReadyGoInit();
        GameState = GSReadyGo;
    }
    
    if ((currButtons & BUTTON_HOME_MASK) && !(prevButtons & BUTTON_HOME_MASK))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }

       
    CWorldParts_Draw(World);
    switch(Counter)
    {
        case 1 :
            bufferDrawImageTransparent(fb,(WINDOW_WIDTH-ready_width) >> 1, (WINDOW_HEIGHT - ready_height) >> 1, ready_data, ready_width, ready_height, false, false, false, COLOR_TRANSPARENT);
            break;
        case 2 :
            bufferDrawImageTransparent(fb,(WINDOW_WIDTH-go_width) >> 1, (WINDOW_HEIGHT - go_height) >> 1, go_data, go_width, go_height, false, false, false, COLOR_TRANSPARENT);
            break;
        case 3 :
            GameState = GSGameInit;
            break;
    }
    DrawStatusBar();
    if (Time < to_ms_since_boot(get_absolute_time()))
    {
        Counter++;
        if(Counter == 1)
        {
            SelectMusic(musNone, 0);
            SelectMusic(musReady, 0);
        }
        if (Counter == 2)
        {
            SelectMusic(musNone, 0);
            SelectMusic(musGo, 0);
            Time = to_ms_since_boot(get_absolute_time()) + 400;
        }
        else
            Time = to_ms_since_boot(get_absolute_time()) + 900;
    }

}

