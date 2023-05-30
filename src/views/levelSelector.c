#include "views/levelSelector.h"

#include <stdio.h>

#include "lcd/lcd.h"
#include "utils.h"
#include "views/gameScene.h"
#include "windows.h"

struct LevelSelectorState {
  int currentLevel;
  int boxNum;
};

struct LevelSelectorState levelSelectorState = {
    .currentLevel = 0,
    .boxNum = 0,
};

void levelSelectorInit(void) {
  levelSelectorState.currentLevel = 1;
  levelSelectorState.boxNum = 1;
}

void incrementValue(int *value, int max) { *value = 1 + (*value) % max; }

void decrementValue(int *value, int max) {
  *value = 1 + (*value - 2 + max) % max;
}

bool levelSelectorUpdate(int button_event) {
  switch (button_event) {
    case BUTTON_NONE:
      return FALSE;
    case JOY_UP:
      incrementValue(&levelSelectorState.currentLevel, MAX_LEVEL_NUM);
      levelSelectorState.boxNum = 1;
      break;
    case JOY_DOWN:
      decrementValue(&levelSelectorState.currentLevel, MAX_LEVEL_NUM);
      levelSelectorState.boxNum = 1;
      break;
    case JOY_LEFT:
      decrementValue(&levelSelectorState.boxNum,
                     levelMaxBoxNum[levelSelectorState.currentLevel - 1]);
      break;
    case JOY_RIGHT:
      incrementValue(&levelSelectorState.boxNum,
                     levelMaxBoxNum[levelSelectorState.currentLevel - 1]);

      break;
    case BUTTON_1:
      switchToGameScene(levelSelectorState.currentLevel,
                        levelSelectorState.boxNum);
      break;
    default:
      return FALSE;
  }
  return TRUE;
}

void levelSelectorRender() {
  LCD_Clear(BLACK);
  char str[30];
  sprintf(str, "Lv: %d", levelSelectorState.currentLevel);
  LCD_ShowString(10, 15, str, BLUE);
  sprintf(str, "Box: %d", levelSelectorState.boxNum);
  LCD_ShowString(10, 30, str, BLUE);
}

void switchToLevelSelector() {
  levelSelectorInit();
  setWindowUpdate(&levelSelectorUpdate);
  setWindowRender(&levelSelectorRender);
}