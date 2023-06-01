// Game scene for sokoban
#include "views/gameScene.h"

#include <stdio.h>

#include "gd32vf103.h"
#include "lcd/bmp.h"
#include "lcd/lcd.h"
#include "utils.h"
#include "views/gameMap.h"
#include "views/scoreBoard.h"

#define STOP_COLOR(COLOR) \
  LCD_Clear(COLOR);       \
  while (1)               \
    ;

#define RAISE_ERROR \
  LCD_Clear(RED);   \
  while (1)         \
    ;

#define RAISE_EXCEPTION(EXCEPTION)         \
  LCD_Clear(RED);                          \
  LCD_ShowString(10, 15, EXCEPTION, BLUE); \
  while (1)                                \
    ;

struct GameSceneState {
  int player_step;
  int level;
  int box_num;

  char gameMap[MAP_HEIGHT][MAP_WIDTH];
  char lastGameMap[MAP_HEIGHT][MAP_WIDTH];
  int playerX;
  int playerY;
};

struct GameSceneState gameSceneState;

void gameSceneInit(int level, int box_num) {
  gameSceneState.player_step = 0;
  gameSceneState.level = level;
  gameSceneState.box_num = box_num;

  gameSceneState.playerX = -1;
  gameSceneState.playerY = -1;

  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      gameSceneState.lastGameMap[i][j] = -1;
      gameSceneState.gameMap[i][j] = MAP_EMPTY;
    }
  }
  int boxCount = 0;
  int targetCount = 0;

  for (int x = 0; x < MAP_HEIGHT; x++) {
    for (int y = 0; y < MAP_WIDTH; y++) {
      char ch = getMapChar(level, y, x);
      if (!isValidMapChar(ch)) {
        STOP_COLOR(RED);
      }
      if (ch == MAP_BOX) {
        boxCount++;
        if (boxCount > box_num) ch = MAP_EMPTY;
      } else if (ch == MAP_TARGET) {
        targetCount++;
        if (targetCount > box_num) ch = MAP_EMPTY;
      }
      gameSceneState.gameMap[x][y] = ch;
      if (gameSceneState.gameMap[x][y] == MAP_PLAYER) {
        if (gameSceneState.playerX != -1) {
          STOP_COLOR(BLUE);
        }
        gameSceneState.playerX = x;
        gameSceneState.playerY = y;
      }
    }
  }
  if (gameSceneState.playerX == -1) {
    STOP_COLOR(GREEN);
  }
}

bool gameSceneUpdate(int button_event) {
  int dirX = 0, dirY = 0;

  if (button_event == BUTTON_NONE) {
    return FALSE;
  } else if (button_event == JOY_UP) {
    dirX = -1;
  } else if (button_event == JOY_DOWN) {
    dirX = 1;
  } else if (button_event == JOY_LEFT) {
    dirY = -1;
  } else if (button_event == JOY_RIGHT) {
    dirY = 1;
  }
  int nextX = gameSceneState.playerX + dirX;
  int nextY = gameSceneState.playerY + dirY;

  if (!isPosValid(nextX, nextY) || isWall(nextX, nextY)) return FALSE;

  if (isBox(nextX, nextY)) {
    int nextBoxX = nextX + dirX;
    int nextBoxY = nextY + dirY;

    if (!isPosValid(nextBoxX, nextBoxY) || !isEmpty(nextBoxX, nextBoxY))
      return FALSE;

    gameSceneState.gameMap[nextBoxX][nextBoxY] =
        moveInBox(gameSceneState.gameMap[nextBoxX][nextBoxY]);

    gameSceneState.gameMap[nextX][nextY] =
        moveOutBox(gameSceneState.gameMap[nextX][nextY]);
  }

  gameSceneState
      .gameMap[gameSceneState.playerX][gameSceneState.playerY] = moveOutPlayer(
      gameSceneState.gameMap[gameSceneState.playerX][gameSceneState.playerY]);
  gameSceneState.playerX = nextX;
  gameSceneState.playerY = nextY;
  gameSceneState
      .gameMap[gameSceneState.playerX][gameSceneState.playerY] = moveInPlayer(
      gameSceneState.gameMap[gameSceneState.playerX][gameSceneState.playerY]);

  gameSceneState.player_step++;
  if (gameSceneIsWin()) {
    switchToScoreBoard(gameSceneState.level, gameSceneState.player_step);
  }
  return TRUE;
}

void gameSceneRender(void) {
  for (int x = 0; x < MAP_WIDTH; x++) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      if (gameSceneState.gameMap[y][x] == gameSceneState.lastGameMap[y][x]) {
        continue;
      }
      gameSceneState.lastGameMap[y][x] = gameSceneState.gameMap[y][x];
      renderBlock(x, y, gameSceneState.gameMap[y][x]);
    }
  }
  char str[30];
  sprintf(str, "%d", gameSceneState.level);
  LCD_ShowString(140, 0, "Lv", BLUE);
  LCD_ShowString(142, 18, str, BLUE);
}

bool gameSceneIsWin(void) {
  for (int x = 0; x < MAP_WIDTH; x++) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      if (gameSceneState.gameMap[y][x] == MAP_BOX) return FALSE;
    }
  }
  return TRUE;
}

void switchToGameScene(int level, int box_num) {
  gameSceneInit(level, box_num);
  LCD_Clear(BLACK);
  setWindowUpdate(&gameSceneUpdate);
  setWindowRender(&gameSceneRender);
}

void renderBlock(int x, int y, char ch) {
  switch (ch) {
    case MAP_EMPTY:
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, empty_bmp);
      break;
    case MAP_WALL:
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, wall_bmp);
      break;
    case MAP_TARGET:
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, target_bmp);
      break;
    case MAP_BOX:
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, box_bmp);
      break;
    case MAP_PLAYER:
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, player_bmp);
      break;
    case MAP_BOX_ON_TARGET:
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, boxOnTarget_bmp);
      break;
    case MAP_PLAYER_ON_TARGET:
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE,
                    playerOnTarget_bmp);
      break;
    default:
      RAISE_EXCEPTION("Invalid map char");
  }
}

char moveInBox(char ch) {
  if (ch == MAP_EMPTY) return MAP_BOX;
  if (ch == MAP_TARGET) return MAP_BOX_ON_TARGET;
  RAISE_ERROR;
}

char moveOutBox(char ch) {
  if (ch == MAP_BOX) return MAP_EMPTY;
  if (ch == MAP_BOX_ON_TARGET) return MAP_TARGET;
  RAISE_ERROR;
}

char moveInPlayer(char ch) {
  if (ch == MAP_EMPTY) return MAP_PLAYER;
  if (ch == MAP_TARGET) return MAP_PLAYER_ON_TARGET;
  RAISE_ERROR;
}

char moveOutPlayer(char ch) {
  if (ch == MAP_PLAYER) return MAP_EMPTY;
  if (ch == MAP_PLAYER_ON_TARGET) return MAP_TARGET;
  RAISE_EXCEPTION("MOVE OUT PLAYER ERROR")
}

bool isBox(int x, int y) {
  return gameSceneState.gameMap[x][y] == MAP_BOX ||
         gameSceneState.gameMap[x][y] == MAP_BOX_ON_TARGET;
}
bool isTarget(int x, int y) {
  return gameSceneState.gameMap[x][y] == MAP_TARGET ||
         gameSceneState.gameMap[x][y] == MAP_BOX_ON_TARGET;
}
bool isPlayer(int x, int y) {
  return gameSceneState.gameMap[x][y] == MAP_PLAYER ||
         gameSceneState.gameMap[x][y] == MAP_PLAYER_ON_TARGET;
}

bool isWall(int x, int y) { return gameSceneState.gameMap[x][y] == MAP_WALL; }

bool isEmpty(int x, int y) {
  return gameSceneState.gameMap[x][y] == MAP_EMPTY ||
         gameSceneState.gameMap[x][y] == MAP_TARGET;
}

bool isValidMapChar(char ch) {
  return ch == MAP_EMPTY || ch == MAP_WALL || ch == MAP_TARGET ||
         ch == MAP_PLAYER || ch == MAP_BOX;
}

bool isPosValid(int x, int y) {
  return x >= 0 && x < MAP_HEIGHT && y >= 0 && y < MAP_WIDTH;
}