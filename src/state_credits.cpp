
#include "framebuffer.h"
#include "defines.h"
#include "gamefuncs.h"
#include "common.h"
#include "state_credits.h"
#include "sound.h"
#include "images/titlescreen_RGB565_BE.h"
#include "images/credits_RGB565_BE.h"

void CreditsInit()
{

}

void Credits()
{
    if (GameState == GSCreditsInit)
    {
        CreditsInit();
        GameState = GSCredits;
    }
    
    if((currButtons & BUTTON_B_MASK) && !(prevButtons & BUTTON_B_MASK) ||
        (currButtons & BUTTON_HOME_MASK) && !(prevButtons & BUTTON_HOME_MASK))
    {
        GameState = GSTitleScreenInit;
        playMenuBackSound();
    }
        
    bufferDrawImage(fb,0,0,titlescreen_data,titlescreen_width,titlescreen_height, false, false, false);
    bufferDrawImage(fb,48,76,credits_data,credits_width,credits_height, false, false, false);
}
