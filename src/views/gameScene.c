// Game scene for sokoban
#include "views/gameScene.h"

#include <stdio.h>

#include "gd32vf103.h"
#include "lcd/lcd.h"
#include "utils.h"

struct GameSceneState {
  int player_step;
  int time;

  char gameMap[MAP_HEIGHT][MAP_WIDTH];
  int playerX;
  int playerY;
};

struct GameSceneState gameSceneState;

void gameSceneInit(void) {
  gameSceneState.player_step = 0;
  gameSceneState.time = 0;

  gameSceneState.playerX = 0;
  gameSceneState.playerY = 0;

  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      gameSceneState.gameMap[i][j] = MAP_EMPTY;
    }
  }
  gameSceneState.gameMap[gameSceneState.playerX][gameSceneState.playerY] =
      MAP_PLAYER;

  gameSceneState.gameMap[1][1] = MAP_WALL;
  gameSceneState.gameMap[2][2] = MAP_BOX;
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

  if (!isPosValid(nextX, nextY) || isWall(nextX, nextY)) return;

  if (isBox(nextX, nextY)) {
    int nextBoxX = nextX + dirX;
    int nextBoxY = nextY + dirY;

    if (!isPosValid(nextBoxX, nextBoxY) || !isEmpty(nextBoxX, nextBoxY)) return;

    gameSceneState.gameMap[nextBoxX][nextBoxY] = MAP_BOX;
  }

  gameSceneState.gameMap[gameSceneState.playerX][gameSceneState.playerY] =
      MAP_EMPTY;
  gameSceneState.playerX = nextX;
  gameSceneState.playerY = nextY;
  gameSceneState.gameMap[gameSceneState.playerX][gameSceneState.playerY] =
      MAP_PLAYER;

  gameSceneState.player_step++;
  return TRUE;
}

void gameSceneRender(void) {
  for (int x = 0; x < MAP_WIDTH; x++) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      LCD_ShowChar(x * MAP_PIX_WIDTH, y * MAP_PIX_WIDTH,
                   gameSceneState.gameMap[y][x], 1, WHITE);
    }
  }
}

void switchToGameScene(int level, int box_num) {
  gameSceneInit();
  setWindowUpdate(&gameSceneUpdate);
  setWindowRender(&gameSceneRender);
}

bool isBox(int x, int y) { return gameSceneState.gameMap[x][y] == MAP_BOX; }

bool isWall(int x, int y) { return gameSceneState.gameMap[x][y] == MAP_WALL; }

bool isEmpty(int x, int y) { return gameSceneState.gameMap[x][y] == MAP_EMPTY; }

bool isPosValid(int x, int y) {
  return x >= 0 && x < MAP_HEIGHT && y >= 0 && y < MAP_WIDTH;
}