#ifndef COMMON_H
#define COMMON_H

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include <inttypes.h>
#include "framebuffer.h"
#include "defines.h"
#include "cworldparts.h"
#include "cselector.h"
#include "cgametypemenu.h"
#include "cmainmenu.h"


extern bool GlobalSoundEnabled;
extern int Timer, AddToScore;
extern int GameState;
extern long int Score;
extern int GameType;
extern SaveData saveData;
extern CSelector* Selector;
extern CGameTypeMenu *MenuGameType;
extern uint32_t Time;
extern uint32_t ScoreTimer;
extern int Counter;
extern CMainMenu *MainMenu;
extern Framebuffer fbs;
extern Framebuffer *fb;
extern uint8_t prevButtons, currButtons;
extern bool debugMode;
extern int movesLeft;
#endif