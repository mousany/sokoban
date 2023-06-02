#include "views/levelSelector.h"

#include <stdio.h>

#include "lcd/bmp.h"
#include "lcd/lcd.h"
#include "utils.h"
#include "views/gameScene.h"
#include "windows.h"

/**
 * @brief The number of levels
 */
struct LevelSelectorState {
  int currentLevel;  // The current level
  int boxNum;        // The number of boxes
};

// The state of the level selector
struct LevelSelectorState levelSelectorState = {
    .currentLevel = 0,
    .boxNum = 0,
};

/**
 * @brief The maximum number of boxes in each level
 */
void levelSelectorInit(void) {
  levelSelectorState.currentLevel = 1;
  levelSelectorState.boxNum = 1;
}

/**
 * @brief The maximum number of boxes in each level
 * @param level The level
 * @param max The maximum number of boxes
 */
void incrementValue(int *value, int max) { *value = 1 + (*value) % max; }

/**
 * @brief The maximum number of boxes in each level
 * @param level The level
 * @param max The maximum number of boxes
 */
void decrementValue(int *value, int max) {
  *value = 1 + (*value - 2 + max) % max;
}

/**
 * @brief The maximum number of boxes in each level
 * @param button_event The button event
 */
bool levelSelectorUpdate(int button_event) {
  switch (button_event) {
    case BUTTON_NONE:  // No button is pressed
      return FALSE;
    case JOY_UP:  // Joystick up
      incrementValue(&levelSelectorState.currentLevel, MAX_LEVEL_NUM);
      levelSelectorState.boxNum = 1;
      break;
    case JOY_DOWN:  // Joystick down
      decrementValue(&levelSelectorState.currentLevel, MAX_LEVEL_NUM);
      levelSelectorState.boxNum = 1;
      break;
    case JOY_LEFT:  // Joystick left
      decrementValue(&levelSelectorState.boxNum,
                     levelMaxBoxNum[levelSelectorState.currentLevel - 1]);
      break;
    case JOY_RIGHT:  // Joystick right
      incrementValue(&levelSelectorState.boxNum,
                     levelMaxBoxNum[levelSelectorState.currentLevel - 1]);

      break;
    case BUTTON_1:  // Button 1
      switchToGameScene(levelSelectorState.currentLevel,
                        levelSelectorState.boxNum);
      break;
    default:  // Other buttons
      return FALSE;
  }
  return TRUE;
}

/**
 * @brief The maximum number of boxes in each level
 */
void levelSelectorRender() {
  LCD_Clear(BLACK);  // Clear the screen

  // Show the title
  LCD_ShowStringOverlap(36, 10, "Battle City", WHITE);
  LCD_ShowStringOverlap(37, 10, "Battle City", WHITE);
  LCD_ShowStringOverlap(37, 11, "Battle City", RED);
  LCD_ShowStringOverlap(36, 11, "Battle City", WHITE);

  char str[30];  // The string buffer
  sprintf(str, "Lvl:  %d", levelSelectorState.currentLevel);
  LCD_ShowBlock(100, 30, arrow_up_bmp);
  LCD_ShowBlock(100, 51, arrow_down_bmp);
  LCD_ShowStringOverlap(52, 35, str, WHITE);

  // Show the box number
  sprintf(str, "Box:  %d", levelSelectorState.boxNum);
  LCD_ShowBlock(90, 63, arrow_left_bmp);
  LCD_ShowBlock(110, 63, arrow_right_bmp);
  LCD_ShowStringOverlap(52, 58, str, WHITE);
}

/**
 * @brief Switch to the level selector
 */
void switchToLevelSelector() {
  levelSelectorInit();
  setWindowUpdate(&levelSelectorUpdate);
  setWindowRender(&levelSelectorRender);
}