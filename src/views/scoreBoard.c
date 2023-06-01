#include "views/scoreBoard.h"

#include "lcd/lcd.h"
#include "utils.h"
#include "views/gameScene.h"
#include "views/levelSelector.h"
#include "windows.h"

struct ScoreBoardState {
  int level;
  int boxNum;
  int step;
};

struct ScoreBoardState scoreBoardState;

void scoreBoardInit(void) {}

bool scoreBoardUpdate(int button_event) {
  if (button_event == BUTTON_1) {
    switchToLevelSelector();
    return TRUE;
  }
  return FALSE;
}

void scoreBoardRender() {
  LCD_Clear(BLACK);
  char str[30];
  LCD_ShowStringBold(48, 10, "YOU WIN!", WHITE);
  sprintf(str, "Lvl: %d", scoreBoardState.level);
  LCD_ShowStringOverlap(56, 28, str, WHITE);
  sprintf(str, "Box: %d", scoreBoardState.boxNum);
  LCD_ShowStringOverlap(56, 43, str, WHITE);
  sprintf(str, "Stp: %d", scoreBoardState.step);
  LCD_ShowStringOverlap(56, 58, str, WHITE);
}

void switchToScoreBoard(int level, int boxNum, int step) {
  scoreBoardState.level = level;
  scoreBoardState.boxNum = boxNum;
  scoreBoardState.step = step;
  setWindowRender(&scoreBoardRender);
  setWindowUpdate(&scoreBoardUpdate);
}