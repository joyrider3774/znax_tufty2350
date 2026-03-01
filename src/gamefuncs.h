#ifndef GAMEFUNCS_H
#define GAMEFUNCS_H

#include "framebuffer.h"

void DrawStatusBar();
void SaveHighScores();
void LoadHighScores();
char chr(int ascii);
int ord(char chr);

#endif