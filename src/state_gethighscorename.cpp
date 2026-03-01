#include <stdio.h>
#include <stdio.h>
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "framebuffer.h"
#include "gamefuncs.h"
#include "defines.h"
#include "common.h"
#include "state_gethighscorename.h"
#include "glcdfont.h"
#include "sound.h"
#include "images/highscores_RGB565_BE.h"

char Name[MAXLENHISCORENAME+1];
bool NameEnd=false,NameSubmitChanges=false;
int NameMaxSelection=0, NameSelection = 0,asci=97;
int ScorePlace;

void GetHighScoreNameInit()
{
	ScorePlace = -1;
	for(int Teller1 =0;Teller1<10;Teller1++)
	{
		if(saveData.HighScores[GameType][Teller1].PScore < Score)
		{
			ScorePlace = Teller1;
			break;          
		}
	}

	if (ScorePlace == -1)
	{
		GameState = GSShowHighScoresInit;
		return;
	}
	SelectMusic(musNone, 0);
    SelectMusic(musWinner, 0);
	NameEnd=false;
	NameSubmitChanges=false;
	NameMaxSelection=0;
	NameSelection = 0;
	asci=97;
	memset(Name, 0, (MAXLENHISCORENAME+1) * sizeof(char));
	NameMaxSelection = 0;
	Name[NameMaxSelection]=chr(asci);
}

void GetHighScoreName()
{
	char NameIn[21];
	if(GameState == GSGetHighScoreNameInit)
	{
		GetHighScoreNameInit();
		if(GameState == GSShowHighScoresInit)
			return;
		GameState = GSGetHighScoreName;
	}
	uint16_t TextColor = rgb565_be(102,115,152);
	uint16_t TextColor1 = rgb565_be(255,115,152);
	char Tekst[100];
	if ((currButtons & BUTTON_A_MASK) && !(prevButtons & BUTTON_A_MASK))
	{
		if (NameSelection > 0)
		{	NameSelection--;
			asci = ord(Name[NameSelection]);
			playMenuBackSound();
		}
	}
	if ((currButtons & BUTTON_C_MASK) && !(prevButtons & BUTTON_C_MASK))
	{
		if (NameSelection < MAXLENHISCORENAME)
		{
			NameSelection++;
			if (NameSelection > NameMaxSelection)
			{
				Name[NameSelection] = chr(97);
				Name[NameSelection+1] = '\0';
				NameMaxSelection=NameSelection;
			}
			asci = ord(Name[NameSelection]);
			playMenuSelectSound();
		}
	}
	if ((currButtons & BUTTON_UP_MASK) && !(prevButtons & BUTTON_UP_MASK))
	{
		asci++;
		if (asci==123)
		{
			asci=32;
		}
		if (asci==33)
		{
			(asci=48);
		}
		if (asci==58)
		{
			asci=97;
		}
		Name[NameSelection] = chr(asci);
		playMenuSelectSound();
	}
	if ((currButtons & BUTTON_DOWN_MASK) && !(prevButtons & BUTTON_DOWN_MASK))
	{
		asci--;
		if(asci==96)
		{
			asci=57;
		}
		if(asci==47)
		{
			asci=32;
		}
		if(asci==31)
		{
			asci=122;
		}
		Name[NameSelection] = chr(asci);
		playMenuSelectSound();
	}
	if ((currButtons & BUTTON_B_MASK) && !(prevButtons & BUTTON_B_MASK))
	{
		playMenuAcknowlege();
		NameEnd = true;
		NameSubmitChanges=true;
	}
	if ((currButtons & BUTTON_HOME_MASK) && !(prevButtons & BUTTON_HOME_MASK))
	{
		playMenuBackSound();
		NameEnd=true;
		NameSubmitChanges=false;
	}
	bufferDrawImage(fb, 0, 0, highscores_data, highscores_width, highscores_height, false, false, false);	
	char Msg[500];
	for(int Teller = 0;Teller<9;Teller++)
	{
		if(Teller < ScorePlace)
		{
			sprintf(Msg,"%2d.%s",Teller+1,saveData.HighScores[GameType][Teller].PName);
			bufferPrint(fb,50,66+Teller*16,Msg,TextColor,TextColor,1, font);
			sprintf(Msg,"%7ld",saveData.HighScores[GameType][Teller].PScore);
			bufferPrint(fb,220,66+Teller*16,Msg,TextColor,TextColor,1, font);
		}
		else
		{
			sprintf(Msg,"%2d.%s",Teller+2,saveData.HighScores[GameType][Teller].PName);
			bufferPrint(fb,50,66+(Teller+1)*16,Msg,TextColor,TextColor,1, font);
			sprintf(Msg,"%7ld",saveData.HighScores[GameType][Teller].PScore);
			bufferPrint(fb,220,66+(Teller+1)*16,Msg,TextColor,TextColor,1, font);
		}
	}
	sprintf(Msg,"%2d.%s",ScorePlace+1,Name);
	bufferPrint(fb,50,66+ScorePlace*16,Msg,TextColor1,TextColor1,1, font);
	sprintf(Msg,"%7ld",Score);
	bufferPrint(fb,220,66+ScorePlace*16,Msg,TextColor1,TextColor1,1, font);

	sprintf(Tekst,"USE UP,DOWN,LEFT,RIGHT B=Ok HOME=Cancel" );
	bufferPrint(fb,(WINDOW_WIDTH - strlen(Tekst)*6) >> 1,230,Tekst,TextColor,TextColor,1, font);

	if(NameEnd)
	{
		GameState = GSShowHighScoresInit;
	}

	if(GameState != GSGetHighScoreName)
	{
		Name[NameMaxSelection+1] = '\0';
		while ((Name[0] == ' ') && (NameMaxSelection>-1))
		{
			for (int Teller=0;Teller<NameMaxSelection;Teller++)
				Name[Teller] = Name[Teller+1];
			NameMaxSelection--;
		}
		if (NameMaxSelection>-1)
			while ((Name[NameMaxSelection] == ' ') && (NameMaxSelection>0))
			{
				Name[NameMaxSelection] = '\0';
				NameMaxSelection--;
			}

		memset(NameIn, 0, (MAXLENHISCORENAME+1) * sizeof(char));
		if (!NameSubmitChanges)
		{
			sprintf(NameIn,"%s"," ");
		}
		else
		{
	        sprintf(NameIn,"%s",Name);
		}

		for(int Teller2=8;Teller2>=ScorePlace;Teller2--)
  			saveData.HighScores[GameType][Teller2+1] = saveData.HighScores[GameType][Teller2];
        if((strcmp(NameIn," ") == 0))
        	sprintf(saveData.HighScores[GameType][ScorePlace].PName,"%s","player");
        else
            sprintf(saveData.HighScores[GameType][ScorePlace].PName,"%s",NameIn);
        saveData.HighScores[GameType][ScorePlace].PScore = Score;
		SaveHighScores();
	}
}
