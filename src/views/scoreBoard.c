#include "views/scoreBoard.h"

#include "lcd/lcd.h"
#include "views/gameScene.h"
#include "windows.h"

struct ScoreBoardState {
  int level;
  int score;
};

struct ScoreBoardState scoreBoardState;

void scoreBoardInit(void) {}

bool scoreBoardUpdate(int button_event) { return FALSE; }

void scoreBoardRender() {
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