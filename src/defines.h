#ifndef DEFINES_H
#define DEFINES_H

#include "framebuffer.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240
#define FPS 30

//gamestates
#define GSQuit 0 
#define GSIntro 1 
#define GSGame 2 
#define GSTitleScreen 3 
#define GSTimeOver 4 
#define GSReadyGo 5 
#define GSCredits 6 
#define GSGameTypeMenu 7 
#define GSShowHighScores 8
#define GSGetHighScoreName 9

#define GSIntroInit 11
#define GSGameInit 12
#define GSTitleScreenInit 13
#define GSTimeOverInit 14
#define GSReadyGoInit 15
#define GSCreditsInit 16
#define GSGameTypeMenuInit 17
#define GSShowHighScoresInit 18
#define GSGetHighScoreNameInit 19

//gametypes
#define Fixed 0
#define Relative 1

#define NrOfRows 10
#define NrOfCols 10
#define NrOfBlockColors 5
#define BlockBlue 0
#define BlockYellow 1
#define BlockOrange 2
#define BlockGreen 3
#define BlockRed 4
#define MaxMusicFiles 26
#define TileWidth 23
#define TileHeight 23

#define COLOR_TRANSPARENT rgb565_be(255,0,255)

#define MAXLENHISCORENAME 8

#define BUTTON_A_MASK (1<<0)
#define BUTTON_B_MASK (1<<1)
#define BUTTON_C_MASK (1<<2)
#define BUTTON_UP_MASK (1<<3)
#define BUTTON_DOWN_MASK (1<<4)
#define BUTTON_HOME_MASK (1<<5)

#define PROGMEM

struct SHighScore
{
    char PName[MAXLENHISCORENAME+1];
    long PScore;
};
typedef struct SHighScore SHighScore;

struct SPoint
{
    int X,Y;
};

typedef struct SPoint SPoint;
#pragma pack(push, 1)
struct SaveData {
    uint16_t magic;  // always first
    SHighScore HighScores[2][10];
    uint8_t crc;
};
#pragma pack(pop)
typedef struct SaveData SaveData;


#endif