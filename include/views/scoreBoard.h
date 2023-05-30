#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H

#include "gd32vf103.h"
#include "windows.h"

struct ScoreBoardState;

extern struct ScoreBoardState scoreBoardState;

void scoreBoardInit(void);

bool scoreBoardUpdate(int button_event);

void scoreBoardRender();

void switchToScoreBoard(int level, int score);

#endif  // __SCOREBOARD_H