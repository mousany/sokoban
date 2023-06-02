#include "views/scoreBoard.h"

#include "lcd/lcd.h"
#include "utils.h"
#include "views/gameScene.h"
#include "views/levelSelector.h"
#include "windows.h"

// The state of the score board
struct ScoreBoardState {
  int level;
  int boxNum;
  int step;
};

// The state of the score board
struct ScoreBoardState scoreBoardState;

/**
 * @brief Initialize the score board
 */
void scoreBoardInit(void) {}

/**
 * @brief
 * @param button_event
 * @return
 */
bool scoreBoardUpdate(int button_event) {
  if (button_event == BUTTON_1) {
    switchToLevelSelector();
    return TRUE;
  }
  return FALSE;
}

/**
 * @brief Render the score board
 */
void scoreBoardRender() {
  LCD_Clear(BLACK);
  char str[30];
  // Show the title
  LCD_ShowStringBold(48, 10, "YOU WIN!", WHITE);
  sprintf(str, "Lvl: %d", scoreBoardState.level);
  // Show the level, box number and step
  LCD_ShowStringOverlap(56, 28, str, WHITE);
  sprintf(str, "Box: %d", scoreBoardState.boxNum);
  // Show the level, box number and step
  LCD_ShowStringOverlap(56, 43, str, WHITE);
  sprintf(str, "Stp: %d", scoreBoardState.step);
  // Show the level, box number and step
  LCD_ShowStringOverlap(56, 58, str, WHITE);
}

/**
 * @brief Switch to the score board
 * @param level The level
 * @param boxNum The number of boxes
 * @param step The number of steps
 */
void switchToScoreBoard(int level, int boxNum, int step) {
  scoreBoardState.level = level;
  scoreBoardState.boxNum = boxNum;
  scoreBoardState.step = step;
  setWindowRender(&scoreBoardRender);
  setWindowUpdate(&scoreBoardUpdate);
}