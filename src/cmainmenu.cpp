#include <stdlib.h>
#include "pico/stdlib.h"
#include "framebuffer.h"
#include "defines.h"
#include "common.h"
#include "cmainmenu.h"
#include "sound.h"
#include "images/titlescreen_RGB565_BE.h"
#include "images/play1_RGB565_BE.h"
#include "images/play2_RGB565_BE.h"
#include "images/highscores1_RGB565_BE.h"
#include "images/highscores2_RGB565_BE.h"
#include "images/credits1_RGB565_BE.h"
#include "images/credits2_RGB565_BE.h"

// constructor of main menu will Load the graphics and set the current selection to 1 (io newgame)
CMainMenu* CMainMenu_Create()
{
    CMainMenu* Result = (CMainMenu*) malloc(sizeof(CMainMenu));
    Result->Selection = 1;
    return Result;
}

// destructor
void CMainMenu_Destroy(CMainMenu* MainMenu)
{
    free(MainMenu);
    MainMenu = NULL;
}

// return the current selection
int CMainMenu_GetSelection(CMainMenu* MainMenu) 
{
    return MainMenu->Selection;
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu_NextItem(CMainMenu* MainMenu)
{
    MainMenu->Selection++;
    if (MainMenu->Selection == 4)
        MainMenu->Selection = 1;
    playMenuSelectSound();
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu_PreviousItem(CMainMenu* MainMenu)
{
    MainMenu->Selection--;
    if (MainMenu->Selection == 0)
        MainMenu->Selection = 4;
    playMenuSelectSound();
}

// Draw the main menu
void CMainMenu_Draw(CMainMenu* MainMenu)
{
    bufferDrawImage(fb,0,0,titlescreen_data,titlescreen_width,titlescreen_height,false,false,false);
    if (MainMenu->Selection == 1)
    {
        bufferDrawImage(fb,98,73,play2_data,play2_width,play2_height,false,false,false);
    }
    else
    {
        bufferDrawImage(fb,98,73,play1_data,play1_width,play1_height,false,false,false);
    }

    if (MainMenu->Selection == 2)
    {
        bufferDrawImage(fb,98,105,highscores2_data,highscores2_width,highscores2_height,false,false,false);
    }
    else
    {
        bufferDrawImage(fb,98,105,highscores1_data,highscores1_width,highscores1_height,false,false,false);
    }


    if (MainMenu->Selection == 3)
    {
        bufferDrawImage(fb,98,137,credits2_data,credits2_width,credits2_height,false,false,false);
    }
    else
    {
        bufferDrawImage(fb,98,137,credits1_data,credits1_width,credits1_height,false,false,false);
    }
}
