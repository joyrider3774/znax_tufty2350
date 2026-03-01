#include "powman.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <cstring>
#include <malloc.h>
#include "common/pimoroni_bus.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "common.h"
#include "defines.h"
#include "cgametypemenu.h"
#include "cmainmenu.h"
#include "cselector.h"
#include "cworldparts.h"
#include "gamefuncs.h"
#include "state_gametypemenu.h"
#include "state_credits.h"
#include "state_titlescreen.h"
#include "state_timeover.h"
#include "state_readygo.h"
#include "state_intro.h"
#include "state_game.h"
#include "state_showhighscores.h"
#include "state_gethighscorename.h"
#include "gamefuncs.h"
#include "sound.h"
#include "glcdfont.h"
#include "framebuffer.h"

using namespace pimoroni;

const uint16_t timePerFrame =  1000000 / FPS; 
static float frameRate = 0;
static uint32_t currentTime = 0, lastTime = 0, frameTime = 0;
static bool endFrame = true;

ParallelPins parallel_bus = {
    .cs = 27,
    .dc = 28,
    .wr_sck = 30,
    .rd_sck = 31,
    .d0 = 32,
    .bl = 26
};

ST7789 *st7789;
PicoGraphics_PenRGB565 *graphics;

extern "C" char __StackLimit;
extern "C" char __bss_end__;
int getFreeRam()
{
    int totalHeap = &__StackLimit  - &__bss_end__;
    struct mallinfo m = mallinfo();
    int usedHeap = m.uordblks;
    return totalHeap - usedHeap;
}

uint8_t readButtons()
{
  uint8_t ret = 0;
  if (!gpio_get(BW_SWITCH_A))
    ret |= BUTTON_A_MASK;
  if (!gpio_get(BW_SWITCH_B))
    ret |= BUTTON_B_MASK;
  if (!gpio_get(BW_SWITCH_C))
    ret |= BUTTON_C_MASK;

  if (!gpio_get(BW_SWITCH_UP))
    ret |= BUTTON_UP_MASK;
  if (!gpio_get(BW_SWITCH_DOWN))
    ret |= BUTTON_DOWN_MASK;
  if (!gpio_get(BW_SWITCH_HOME))
    ret |= BUTTON_HOME_MASK;
  return ret;
}

void printDebugCpuRamLoad()
{
    if(debugMode)
    {
        int currentFPS = (int)frameRate;
        char debuginfo[80];
        
        int fps_int = (int)frameRate;
        int fps_frac = (int)((frameRate - fps_int) * 100);
        sprintf(debuginfo, "F:%3d.%2d R:%d", fps_int, fps_frac, getFreeRam());
        bufferPrint(&fbs, 0, 0, debuginfo, 0xFFFF,  0x0000, 1, font);
    }
}

int main() {
    stdio_init_all();
    st7789 = new ST7789(WINDOW_WIDTH, WINDOW_HEIGHT, ROTATE_180, parallel_bus);
    graphics = new PicoGraphics_PenRGB565(st7789->width, st7789->height, nullptr);
    graphics->color = 0x0000;
    graphics->clear();
    st7789->update(graphics);
    st7789->set_backlight(200);
    
    fbs.bgr = false;
    fbs.littleEndian = false;
    fbs.height = 240;
    fbs.width = 320;
    fbs.buffer = (uint16_t*)graphics->frame_buffer;
    LoadHighScores();
    initSound();
    initMusic();
    setSoundOn(true);
    setMusicOn(true);
    World = CWorldParts_Create();
    Selector = CSelector_Create(NrOfCols / 2, NrOfRows / 2);
    MenuGameType = CGameTypeMenu_Create();
    MainMenu = CMainMenu_Create();
    currentTime = time_us_32();
    lastTime = 0;
    while (true) 
    {
        currentTime = time_us_32();
        frameTime  = currentTime - lastTime;  
        if((frameTime < timePerFrame) || !endFrame)
            continue;
        endFrame = false;
        frameRate = 1000000.0 / frameTime;
        lastTime = currentTime;
        prevButtons = currButtons;
        currButtons = readButtons();

        if((currButtons & BUTTON_UP_MASK) && (currButtons & BUTTON_DOWN_MASK) && !(prevButtons & BUTTON_DOWN_MASK))
          debugMode = !debugMode;

        switch(GameState)
        {
          case GSGame :
          case GSGameInit:
              Game();
              break;
          case GSTitleScreen:
          case GSTitleScreenInit:
              TitleScreen();
              break;
          case GSIntro :
          case GSIntroInit :
              Intro();
              break;
          case GSReadyGo:
          case GSReadyGoInit:
              ReadyGo();
              break;
          case GSTimeOver:
          case GSTimeOverInit:
              TimeOver();
              break;
          case GSCredits:
          case GSCreditsInit:
              Credits();
              break;
          case GSGameTypeMenu:
          case GSGameTypeMenuInit:
              GameTypeMenu();
              break;
          case GSShowHighScores:
          case GSShowHighScoresInit:
              ShowHighScores();
              break;
          case GSGetHighScoreName:
          case GSGetHighScoreNameInit:
              GetHighScoreName();
              break;
          default :
             break;
        }
        printDebugCpuRamLoad();
        st7789->update(graphics);
        endFrame = true;
    }
    return 0;
}