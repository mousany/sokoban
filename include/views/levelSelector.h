#ifndef __LEVELSELECTOR_H
#define __LEVELSELECTOR_H

#include "windows.h"

struct LevelSelectorState {};

void levelSelectorInit(void);

void levelSelectorUpdate();

void levelSelectorRender();

void switchToLevelSelector();

#endif