#ifndef __LEVELSELECTOR_H
#define __LEVELSELECTOR_H

#include "windows.h"

#define MAX_LEVEL_NUM 5
#define MAX_BOX_NUM 3

struct LevelSelectorState;

extern struct LevelSelectorState levelSelectorState;

void levelSelectorInit(void);

bool levelSelectorUpdate(int button_event);

void levelSelectorRender();

void switchToLevelSelector();

#endif