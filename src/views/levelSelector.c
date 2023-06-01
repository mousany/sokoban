#include "views/levelSelector.h"

#include <stdio.h>

#include "lcd/bmp.h"
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

  LCD_ShowStringOverlap(36, 10, "Battle City", WHITE);
  LCD_ShowStringOverlap(37, 10, "Battle City", WHITE);
  LCD_ShowStringOverlap(37, 11, "Battle City", RED);
  LCD_ShowStringOverlap(36, 11, "Battle City", WHITE);

  char str[30];
  sprintf(str, "Lvl:  %d", levelSelectorState.currentLevel);
  LCD_ShowBlock(100, 30, arrow_up_bmp);
  LCD_ShowBlock(100, 51, arrow_down_bmp);
  LCD_ShowStringOverlap(52, 35, str, WHITE);

  sprintf(str, "Box:  %d", levelSelectorState.boxNum);
  LCD_ShowBlock(90, 63, arrow_left_bmp);
  LCD_ShowBlock(110, 63, arrow_right_bmp);
  LCD_ShowStringOverlap(52, 58, str, WHITE);
}

void switchToLevelSelector() {
  levelSelectorInit();
  setWindowUpdate(&levelSelectorUpdate);
  setWindowRender(&levelSelectorRender);
}