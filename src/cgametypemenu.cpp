#include <stdlib.h>
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "framebuffer.h"
#include "common.h"
#include "defines.h"
#include "cgametypemenu.h"
#include "sound.h"
#include "images/titlescreen_RGB565_BE.h"
#include "images/selectgame_RGB565_BE.h"
#include "images/fixedtimer1_RGB565_BE.h"
#include "images/fixedtimer2_RGB565_BE.h"
#include "images/relativetimer1_RGB565_BE.h"
#include "images/relativetimer2_RGB565_BE.h"

// constructor of main menu will Load the graphics and set the current selection to 1 (io newgame)
CGameTypeMenu* CGameTypeMenu_Create()
{
    CGameTypeMenu* Result = (CGameTypeMenu*) malloc(sizeof(CGameTypeMenu));
    Result->Selection = Fixed;
    return Result;
}

// return the current selection
int CGameTypeMenu_GetSelection(CGameTypeMenu* GameTypeMenu) 
{
    return GameTypeMenu->Selection;
}

// Destructor will free the surface images
void CGameTypeMenu_Destroy(CGameTypeMenu* GameTypeMenu)
{
    free(GameTypeMenu);
    GameTypeMenu = NULL;
}

// Increase the selection if it goes to far set i to the first selection
void CGameTypeMenu_NextItem(CGameTypeMenu* GameTypeMenu)
{
    GameTypeMenu->Selection++;
    if (GameTypeMenu->Selection == 2)
        GameTypeMenu->Selection = 0;
    playMenuSelectSound();
}

// decrease the selection if it goes to low set it to the last selection
void CGameTypeMenu_PreviousItem(CGameTypeMenu* GameTypeMenu)
{
    GameTypeMenu->Selection--;
    if (GameTypeMenu->Selection == -1)
        GameTypeMenu->Selection = 1;
    playMenuSelectSound();
}

// Draw the main menu
void CGameTypeMenu_Draw(CGameTypeMenu* GameTypeMenu)
{
    bufferDrawImage(fb,0,0,titlescreen_data,titlescreen_width,titlescreen_height,false,true,false);
    bufferDrawImage(fb,68,77,selectgame_data,selectgame_width,selectgame_height,false,false,false);

    if (GameTypeMenu->Selection == Fixed)
    {
        bufferDrawImage(fb,68,114,fixedtimer2_data,fixedtimer2_width,fixedtimer2_height,false,false,false);
    }
    else
    {
        bufferDrawImage(fb,68,114,fixedtimer1_data,fixedtimer1_width,fixedtimer1_height,false,false,false);
    }

    if (GameTypeMenu->Selection == Relative)
    {
        bufferDrawImage(fb,68, 151,relativetimer2_data,relativetimer2_width,relativetimer2_height,false,false,false);
    }
    else
    {
        bufferDrawImage(fb,68, 151,relativetimer1_data,relativetimer1_width,relativetimer1_height,false,false,false);
    }
}
