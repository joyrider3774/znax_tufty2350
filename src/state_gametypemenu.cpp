
#include "framebuffer.h"
#include "cgametypemenu.h"
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "sound.h"
#include "state_gametypemenu.h"


void GameTypeMenuInit()
{
    GameType = Fixed;
}
void GameTypeMenu()
{
    if (GameState == GSGameTypeMenuInit)
    {
        GameTypeMenuInit();
        GameState = GSGameTypeMenu;
    }
    if ((currButtons & BUTTON_UP_MASK) && !(prevButtons & BUTTON_UP_MASK))
        CGameTypeMenu_NextItem(MenuGameType);
    if ((currButtons & BUTTON_DOWN_MASK) && !(prevButtons & BUTTON_DOWN_MASK))    
        CGameTypeMenu_PreviousItem(MenuGameType);
    if ((currButtons & BUTTON_B_MASK) && !(prevButtons & BUTTON_B_MASK))
    {
        playMenuAcknowlege();
        switch(CGameTypeMenu_GetSelection(MenuGameType))
        {
            case Fixed:
                GameType = Fixed;
                break;
            case Relative:
                GameType = Relative;
                break;
        }
        GameState = GSReadyGoInit;
    }
    if ((currButtons & BUTTON_HOME_MASK) && !(prevButtons & BUTTON_HOME_MASK))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }
    CGameTypeMenu_Draw(MenuGameType);
}

