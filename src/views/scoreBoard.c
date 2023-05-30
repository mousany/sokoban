#include "views/scoreBoard.h"

#include "lcd/lcd.h"
#include "utils.h"
#include "views/gameScene.h"
#include "views/levelSelector.h"
#include "windows.h"

struct ScoreBoardState {
  int level;
  int score;
};

struct ScoreBoardState scoreBoardState;

void scoreBoardInit(void) {}

bool scoreBoardUpdate(int button_event) {
  if (Get_Button(BUTTON_1)) {
    switchToLevelSelector();
    return TRUE;
  }
  return FALSE;
}

void scoreBoardRender() {
  LCD_Clear(BLACK);
  char str[30];
  sprintf(str, "Level: %d", scoreBoardState.level);
  LCD_ShowString(10, 15, str, BLUE);
  sprintf(str, "Score: %d", scoreBoardState.score);
  LCD_ShowString(10, 30, str, BLUE);
}

void switchToScoreBoard(int level, int score) {
  scoreBoardState.level = level;
  scoreBoardState.score = score;
  setWindowRender(&scoreBoardRender);
  setWindowUpdate(&scoreBoardUpdate);
}