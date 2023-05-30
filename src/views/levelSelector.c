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
  levelSelectorState.currentLevel = 0;
  levelSelectorState.boxNum = 0;
}

bool levelSelectorUpdate(int button_event) {
  switch (button_event) {
    case BUTTON_NONE:
      return FALSE;
    case JOY_UP:
      levelSelectorState.currentLevel =
          1 + (levelSelectorState.currentLevel) % MAX_LEVEL_NUM;
      break;
    case JOY_DOWN:
      levelSelectorState.currentLevel =
          1 +
          (levelSelectorState.currentLevel - 2 + MAX_LEVEL_NUM) % MAX_LEVEL_NUM;
      break;
    case JOY_LEFT:
      levelSelectorState.boxNum =
          1 + (levelSelectorState.boxNum - 2 + MAX_BOX_NUM) % MAX_BOX_NUM;
      break;
    case JOY_RIGHT:
      levelSelectorState.boxNum = 1 + (levelSelectorState.boxNum) % MAX_BOX_NUM;
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
  char str[30];
  sprintf(str, "Lvl: %d", levelSelectorState.currentLevel);
  LCD_ShowString(10, 15, str, BLUE);
  sprintf(str, "Box: %d", levelSelectorState.boxNum);
  LCD_ShowString(10, 30, str, BLUE);
}

void switchToLevelSelector() {
  levelSelectorInit();
  setWindowUpdate(&levelSelectorUpdate);
  setWindowRender(&levelSelectorRender);
}