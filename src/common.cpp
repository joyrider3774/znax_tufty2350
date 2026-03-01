#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "framebuffer.h"
#include "defines.h"
#include "cselector.h"
#include "cgametypemenu.h"
#include "cmainmenu.h"

struct CWorldParts;

bool GlobalSoundEnabled = true;
int Timer = 150, AddToScore = 0;
int GameState = GSIntro;

long int Score;
int GameType = Fixed;
SaveData saveData;
CSelector* Selector;
CGameTypeMenu *MenuGameType;
uint32_t Time;
uint32_t ScoreTimer;
int Counter;
CMainMenu *MainMenu;
uint8_t prevButtons, currButtons;
bool debugMode = false;
Framebuffer fbs;
Framebuffer *fb = &fbs;
int movesLeft = 0;