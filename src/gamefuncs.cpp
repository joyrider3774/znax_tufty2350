#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "framebuffer.h"
#include "common.h"
#include "defines.h"
#include "glcdfont.h"
#include "EEPROM.h"


#define SAVE_MAGIC 0xDADA

uint8_t calcCRC(void *data, size_t len) {
  uint8_t crc = 0;
  uint8_t *ptr = (uint8_t *)data;
  for (size_t i = 0; i < len; i++) {
    crc ^= ptr[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x80)
        crc = (crc << 1) ^ 0x07;
      else
        crc <<= 1;
    }
  }
  return crc;
}

void LoadHighScores()
{
    EEPROM.begin(sizeof(SaveData));
    EEPROM.get(0, saveData);
    //needs to be -uint8t size because of crc not included in calculation
    uint8_t crc = calcCRC(&saveData, sizeof(SaveData) - sizeof(uint8_t));
    if (saveData.magic != SAVE_MAGIC || saveData.crc != crc) 
    {
        memset(&saveData, 0, sizeof(SaveData));
        saveData.magic = SAVE_MAGIC;

        for (int Teller = 0;Teller<10;Teller++)
 	    {
 	        sprintf(saveData.HighScores[Fixed][Teller].PName,"%s","joyrider");
 	        sprintf(saveData.HighScores[Relative][Teller].PName,"%s","joyrider");
 	        saveData.HighScores[Fixed][Teller].PScore = 0;
 	        saveData.HighScores[Relative][Teller].PScore = 0;
 	    }
    }
}

void SaveHighScores()
{
    saveData.crc = calcCRC(&saveData, sizeof(SaveData) - sizeof(uint8_t));
    EEPROM.begin(sizeof(SaveData));
    EEPROM.put(0, saveData);
    bool ok = EEPROM.commit();
}

void DrawStatusBar()
{
    char Text[200];
    if(AddToScore == 0)
        sprintf(Text,"TIME:\n%02d:%02d\n     \n\nSCORE:\n%d\n\nLEFT:\n%d",Timer/60,Timer%60,Score, movesLeft);
    else
    {
        if(GameType == Relative)
            sprintf(Text,"TIME:\n%02d:%02d\n+%03d\n\nSCORE:\n%d\n+%d\n\nLEFT:\n%d",Timer/60,Timer%60,AddToScore/400,Score, AddToScore, movesLeft);
        else
            sprintf(Text,"TIME:\n%02d:%02d\n     \n\nSCORE:\n%d\n+%d\n\nLEFT:\n%d",Timer/60,Timer%60,Score, AddToScore, movesLeft);
    }

    bufferPrint(fb,247,10, Text, rgb565_be(255,255,255), rgb565_be(255,255,255), 1, font);
}

char chr(int ascii)
{
	return((char)ascii);
}

int ord(char chr)
{
	return((int)chr);
}

