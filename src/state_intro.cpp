#include "pico/time.h"
#include "framebuffer.h"
#include "gamefuncs.h"
#include "common.h"
#include "defines.h"
#include "state_intro.h"
#include "images/intro1_RGB565_BE.h"
#include "images/intro2_RGB565_BE.h"

int IntroScreenNr;

void IntroInit()
{
    IntroScreenNr = 1;
    Time = to_ms_since_boot(get_absolute_time());
}

void Intro()
{
    if(GameState == GSIntroInit)
    {
        IntroInit();
        GameState = GSIntro;
    }
    if((currButtons & BUTTON_B_MASK) && !(prevButtons & BUTTON_B_MASK) ||
        (currButtons & BUTTON_HOME_MASK) && !(prevButtons & BUTTON_HOME_MASK))
    {
        GameState = GSTitleScreenInit;
    }

     
    switch(IntroScreenNr)
    {
        case 1 :
            bufferDrawImage(fb,0,0,intro1_data, intro1_width, intro1_height, false, false, false);
            break;
        case 2 :
            bufferDrawImage(fb,0,0,intro2_data, intro2_width, intro2_height, false, false, false);
            break;
    }

    if(Time + 3700 < to_ms_since_boot(get_absolute_time()))
    {
        IntroScreenNr++;
        if(IntroScreenNr > 2)
            GameState = GSTitleScreenInit;
        Time = to_ms_since_boot(get_absolute_time());
    }

}
