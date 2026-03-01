
#include "framebuffer.h"
#include "gamefuncs.h"
#include "common.h"
#include "defines.h"
#include "cmainmenu.h"
#include "state_titlescreen.h"
#include "sound.h"


void TitleScreenInit()
{

}

void TitleScreen()
{    
    if (GameState == GSTitleScreenInit)
    {
        TitleScreenInit();
        GameState = GSTitleScreen;
    }
    
    if ((currButtons & BUTTON_UP_MASK) && !(prevButtons & BUTTON_UP_MASK))
        CMainMenu_PreviousItem(MainMenu);
    if ((currButtons & BUTTON_DOWN_MASK) && !(prevButtons & BUTTON_DOWN_MASK))  
        CMainMenu_NextItem(MainMenu);
    if ((currButtons & BUTTON_B_MASK) && !(prevButtons & BUTTON_B_MASK))
    {      
        playMenuAcknowlege();
        switch(CMainMenu_GetSelection(MainMenu))
        {
            case 1:
                GameState = GSGameTypeMenuInit;
                break;
            case 2:
                //so that it shows both gameplay modes
                GameType = Fixed;
                GameState = GSShowHighScoresInit;
                break;
            case 3:
                GameState = GSCreditsInit;
                break;
            default:
                break;
        }
    }
    CMainMenu_Draw(MainMenu);
}
