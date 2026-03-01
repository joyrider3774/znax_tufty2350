#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "framebuffer.h"
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "sound.h"
#include "glcdfont.h"
#include "state_showhighscores.h"
#include "images/highscores_RGB565_BE.h"


int ScoreType;
    
void ShowHighScoresInit()
{
    ScoreType = GameType;
}

void ShowHighScores()
{
    if (GameState == GSShowHighScoresInit)
    {
        ShowHighScoresInit();
        GameState = GSShowHighScores;
    }

    uint16_t TextColor = rgb565_be(102,115,152);
    int Teller = 0;
    char Text[250];
    if ((currButtons & BUTTON_B_MASK) && !(prevButtons & BUTTON_B_MASK))
    {
        
        if (ScoreType == Fixed)
        {
            playMenuAcknowlege();
            ScoreType = Relative;
        }
        else
        {
            playMenuBackSound();
            GameState = GSTitleScreenInit;
        }
    }
    if ((currButtons & BUTTON_HOME_MASK) && !(prevButtons & BUTTON_HOME_MASK))
    {
        playMenuBackSound();
        GameState = GSTitleScreenInit;
    }
        
    bufferDrawImage(fb, 0, 0, highscores_data, highscores_width, highscores_height, false, false, false);	
    switch(ScoreType)
    {
        case Fixed :
            sprintf(Text,"Fixed Timer" );
            break;
        case Relative :
            sprintf(Text,"Relative Timer" );
            break;
    }

    bufferPrint(fb, (WINDOW_WIDTH - (strlen(Text)*6)) >> 1,230,Text,TextColor,TextColor,1, font);
    
    for(Teller = 0;Teller<10;Teller++)
    {
        sprintf(Text,"%2d.%s",Teller+1,saveData.HighScores[ScoreType][Teller].PName);
	    bufferPrint(fb,50,66+Teller*16,Text,TextColor,TextColor,1, font);
	    sprintf(Text,"%7ld",saveData.HighScores[ScoreType][Teller].PScore);
	    bufferPrint(fb,220,66+Teller*16,Text,TextColor,TextColor,1, font);
    }
}
