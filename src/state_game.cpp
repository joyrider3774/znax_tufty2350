#include "pico/time.h"
#include "framebuffer.h"
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "cworldparts.h"
#include "cselector.h"
#include "state_game.h"
#include "sound.h"

void GameInit()
{
    AddToScore = 0;
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
    Time = to_ms_since_boot(get_absolute_time());
    ScoreTimer = 0;
    Selector->CurrentPoint.X = NrOfCols / 2;
    Selector->CurrentPoint.Y = NrOfRows / 2;
    // SelectMusic(musNone, 0);
    // SelectMusic(musStart, 0);
}

void Game()
{
    if (GameState == GSGameInit)
    {
        GameInit();
        GameState = GSGame;
    }
    
    if ((currButtons & BUTTON_A_MASK) && !(prevButtons & BUTTON_A_MASK))
        CSelector_SetPosition(Selector, Selector->CurrentPoint.X -1,Selector->CurrentPoint.Y);
    if ((currButtons & BUTTON_C_MASK) && !(prevButtons & BUTTON_C_MASK))        
        CSelector_SetPosition(Selector, Selector->CurrentPoint.X +1,Selector->CurrentPoint.Y);
    if ((currButtons & BUTTON_UP_MASK) && !(prevButtons & BUTTON_UP_MASK))
        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y-1);
    if ((currButtons & BUTTON_DOWN_MASK) && !(prevButtons & BUTTON_DOWN_MASK))
        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y+1);
    if ((currButtons & BUTTON_HOME_MASK) && !(prevButtons & BUTTON_HOME_MASK))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }
    if ((currButtons & BUTTON_B_MASK) && !(prevButtons & BUTTON_B_MASK))
    {
        AddToScore+= CWorldParts_Select(World, Selector->CurrentPoint.X,Selector->CurrentPoint.Y);
        if(AddToScore != 0)
        {
            ScoreTimer = to_ms_since_boot(get_absolute_time()) + 700;
        }
    }
    CWorldParts_Draw(World);
    CSelector_Draw(Selector);
    if(AddToScore !=0)
    {
        if(ScoreTimer <= to_ms_since_boot(get_absolute_time()))
        {
            ScoreTimer = 0;
            Score +=AddToScore;
            if (GameType == Relative)
                Timer += AddToScore / 400;
            AddToScore = 0;
        }
    }
    DrawStatusBar();
    if (Time +1000 < to_ms_since_boot(get_absolute_time()))
    {
        Timer-= 1;
        switch (Timer)
        {
            case 60*3 :
                SelectMusic(musNone,0);
                SelectMusic(mus5Min,0);
                break;
            case 60:
                SelectMusic(musNone,0);
                SelectMusic(mus3Min,0);
                break;
            case 3 :
                playThreeSound();
                break;
            case 2 :
                playTwoSound();
                break;
            case 1 :
                playOneSound();
                break;
            case 0 :
                if(ScoreTimer != 0)
                {
                    Score += AddToScore;
                    if(GameType == Relative)
                        Timer += AddToScore / 200;
                }
                if(Timer == 0)
                {
                    //if (GlobalSoundEnabled)
                    //    Mix_PlayChannel(-1,Sounds[SND_TIMEOVER],0);
                    GameState = GSTimeOverInit;
                }
                break;
        }
        Time = to_ms_since_boot(get_absolute_time());
    }
}
