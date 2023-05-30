#ifndef __LEVELSELECTOR_H
#define __LEVELSELECTOR_H

#include "windows.h"
#include "views/gameMap.h"

struct LevelSelectorState;

extern struct LevelSelectorState levelSelectorState;

void levelSelectorInit(void);

bool levelSelectorUpdate(int button_event);

void levelSelectorRender();

void switchToLevelSelector();

#endif