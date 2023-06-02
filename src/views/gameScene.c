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

/**
 * @brief Raise an error on the screen.
 */
#define RAISE_ERROR \
  LCD_Clear(RED);   \
  while (1)         \
    ;

/**
 * @brief Raise an exception on the screen.
 * @param EXCEPTION The exception message.
 */
#define RAISE_EXCEPTION(EXCEPTION)         \
  LCD_Clear(RED);                          \
  LCD_ShowString(10, 15, EXCEPTION, BLUE); \
  while (1)                                \
    ;

/**
 * @brief The game scene state.
 */
struct GameSceneState {
  int player_step;  // The player step count.
  int level;        // The current level.
  int box_num;      // The box number of the current level.

  char gameMap[MAP_HEIGHT][MAP_WIDTH];      // The current game map.
  char lastGameMap[MAP_HEIGHT][MAP_WIDTH];  // The last game map.
  int playerX;                              // The player X position.
  int playerY;                              // The player Y position.
};

/**
 * @brief The game scene state.
 */
struct GameSceneState gameSceneState;

/**
 * @brief Initialize the game scene.
 * @param level The level.
 * @param box_num The box number.
 */
void gameSceneInit(int level, int box_num) {
  gameSceneState.player_step = 0;
  gameSceneState.level = level;
  gameSceneState.box_num = box_num;

  // Initialize the game map.
  gameSceneState.playerX = -1;
  gameSceneState.playerY = -1;

  for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
      gameSceneState.lastGameMap[i][j] = -1;
      gameSceneState.gameMap[i][j] = MAP_EMPTY;
    }
  }

  // Sample boxes and targets.
  int boxCount = 0;
  int targetCount = 0;

  for (int x = 0; x < MAP_HEIGHT; x++) {
    for (int y = 0; y < MAP_WIDTH; y++) {
      // Get the map char.
      char ch = getMapChar(level, y, x);
      if (!isValidMapChar(ch)) {
        STOP_COLOR(RED);
      }
      // Sample the boxes and targets.
      if (ch == MAP_BOX) {
        boxCount++;
        if (boxCount > box_num) ch = MAP_EMPTY;
      } else if (ch == MAP_TARGET) {
        targetCount++;
        if (targetCount > box_num) ch = MAP_EMPTY;
      }
      // Set the map char.
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
  // Check the map.
  if (gameSceneState.playerX == -1) {
    STOP_COLOR(GREEN);
  }
}

/**
 * @brief Check if the game is win.
 * @return If the game is win.
 */
bool gameSceneUpdate(int button_event) {
  int dirX = 0, dirY = 0;

  if (button_event == BUTTON_NONE) {  // No button pressed.
    return FALSE;
  } else if (button_event == JOY_UP) {  // Up button pressed.
    dirX = -1;
  } else if (button_event == JOY_DOWN) {  // Down button pressed.
    dirX = 1;
  } else if (button_event == JOY_LEFT) {  // Left button pressed.
    dirY = -1;
  } else if (button_event == JOY_RIGHT) {  // Right button pressed.
    dirY = 1;
  }
  int nextX = gameSceneState.playerX + dirX;  // The next X position.
  int nextY = gameSceneState.playerY + dirY;  // The next Y position.

  // Check if the next position is valid.
  if (!isPosValid(nextX, nextY) || isWall(nextX, nextY)) return FALSE;

  if (isBox(nextX, nextY)) {
    int nextBoxX = nextX + dirX;
    int nextBoxY = nextY + dirY;

    // Check if the next box position is valid.
    if (!isPosValid(nextBoxX, nextBoxY) || !isEmpty(nextBoxX, nextBoxY))
      return FALSE;

    // Move the box.
    gameSceneState.gameMap[nextBoxX][nextBoxY] =
        moveInBox(gameSceneState.gameMap[nextBoxX][nextBoxY]);

    // Move the box out.
    gameSceneState.gameMap[nextX][nextY] =
        moveOutBox(gameSceneState.gameMap[nextX][nextY]);
  }

  // Move the player.
  gameSceneState
      .gameMap[gameSceneState.playerX][gameSceneState.playerY] = moveOutPlayer(
      gameSceneState.gameMap[gameSceneState.playerX][gameSceneState.playerY]);
  gameSceneState.playerX = nextX;
  gameSceneState.playerY = nextY;
  // Move the player in.
  gameSceneState
      .gameMap[gameSceneState.playerX][gameSceneState.playerY] = moveInPlayer(
      gameSceneState.gameMap[gameSceneState.playerX][gameSceneState.playerY]);

  // Update the step count.
  gameSceneState.player_step++;
  if (gameSceneIsWin()) {  // Check if the game is win.
    switchToScoreBoard(gameSceneState.level, gameSceneState.box_num,
                       gameSceneState.player_step);
  }
  return TRUE;
}

void gameSceneRender(void) {
  for (int x = 0; x < MAP_WIDTH; x++) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      // Check if the block is changed.
      if (gameSceneState.gameMap[y][x] == gameSceneState.lastGameMap[y][x]) {
        continue;
      }
      gameSceneState.lastGameMap[y][x] = gameSceneState.gameMap[y][x];
      renderBlock(x, y, gameSceneState.gameMap[y][x]);
    }
  }
  // Render the step count.
  char str[30];
  sprintf(str, "%d", gameSceneState.level);
  LCD_ShowStringBold(142, 0, "Lv", WHITE);
  LCD_ShowString(150, 18, str, WHITE);
  // Render the box count.
  sprintf(str, "%d", gameSceneState.box_num);
  LCD_ShowStringBold(142, 40, "Bx", WHITE);
  LCD_ShowString(150, 58, str, WHITE);
}

/**
 * @brief Check if the game is win.
 * @return If the game is win.
 */
bool gameSceneIsWin(void) {
  for (int x = 0; x < MAP_WIDTH; x++) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      if (gameSceneState.gameMap[y][x] == MAP_BOX) return FALSE;
    }
  }
  return TRUE;
}

/**
 * @brief Switch to the game scene.
 * @param level The level of the game.
 * @param box_num The number of the boxes.
 */
void switchToGameScene(int level, int box_num) {
  gameSceneInit(level, box_num);
  LCD_Clear(BLACK);
  setWindowUpdate(&gameSceneUpdate);
  setWindowRender(&gameSceneRender);
}

/**
 * @brief Render a block.
 * @param x The X position of the block.
 * @param y The Y position of the block.
 * @param ch The char of the block.
 */
void renderBlock(int x, int y, char ch) {
  switch (ch) {
    case MAP_EMPTY:  // Empty block.
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, empty_bmp);
      break;
    case MAP_WALL:  // Wall block.
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, wall_bmp);
      break;
    case MAP_TARGET:  // Target block.
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, target_bmp);
      break;
    case MAP_BOX:  // Box block.
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, box_bmp);
      break;
    case MAP_PLAYER:  // Player block.
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, player_bmp);
      break;
    case MAP_BOX_ON_TARGET:  // Box on target block.
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE, boxOnTarget_bmp);
      break;
    case MAP_PLAYER_ON_TARGET:  // Player on target block.
      LCD_ShowBlock(x * GAME_BLOCK_SIZE, y * GAME_BLOCK_SIZE,
                    playerOnTarget_bmp);
      break;
    default:  // Invalid block.
      RAISE_EXCEPTION("Invalid map char");
  }
}

/**
 * @brief Check if the position is valid.
 * @param x The X position.
 * @param y The Y position.
 * @return If the position is valid.
 */
char moveInBox(char ch) {
  if (ch == MAP_EMPTY) return MAP_BOX;
  if (ch == MAP_TARGET) return MAP_BOX_ON_TARGET;
  RAISE_ERROR;
}

/**
 * @brief Move the box out.
 * @param ch The char of the block.
 * @return The char of the block after moving out.
 */
char moveOutBox(char ch) {
  if (ch == MAP_BOX) return MAP_EMPTY;
  if (ch == MAP_BOX_ON_TARGET) return MAP_TARGET;
  RAISE_ERROR;
}

/**
 * @brief Move the player in.
 * @param ch The char of the block.
 * @return The char of the block after moving in.
 */
char moveInPlayer(char ch) {
  if (ch == MAP_EMPTY) return MAP_PLAYER;
  if (ch == MAP_TARGET) return MAP_PLAYER_ON_TARGET;
  RAISE_ERROR;
}

/**
 * @brief Move the player out.
 * @param ch The char of the block.
 * @return The char of the block after moving out.
 */
char moveOutPlayer(char ch) {
  if (ch == MAP_PLAYER) return MAP_EMPTY;
  if (ch == MAP_PLAYER_ON_TARGET) return MAP_TARGET;
  RAISE_EXCEPTION("MOVE OUT PLAYER ERROR")
}

/**
 * @brief Check if the position is valid.
 * @param x The X position.
 * @param y The Y position.
 * @return If the position is valid.
 */
bool isBox(int x, int y) {
  return gameSceneState.gameMap[x][y] == MAP_BOX ||
         gameSceneState.gameMap[x][y] == MAP_BOX_ON_TARGET;
}

/**
 * @brief Check if the position is valid.
 * @param x The X position.
 * @param y The Y position.
 * @return If the position is valid.
 */
bool isTarget(int x, int y) {
  return gameSceneState.gameMap[x][y] == MAP_TARGET ||
         gameSceneState.gameMap[x][y] == MAP_BOX_ON_TARGET;
}

/**
 * @brief Check if the position is valid.
 * @param x The X position.
 * @param y The Y position.
 * @return If the position is valid.
 */
bool isPlayer(int x, int y) {
  return gameSceneState.gameMap[x][y] == MAP_PLAYER ||
         gameSceneState.gameMap[x][y] == MAP_PLAYER_ON_TARGET;
}

/**
 * @brief Check if the position is valid.
 * @param x The X position.
 * @param y The Y position.
 * @return If the position is valid.
 */
bool isWall(int x, int y) { return gameSceneState.gameMap[x][y] == MAP_WALL; }

/**
 * @brief Check if the position is valid.
 * @param x The X position.
 * @param y The Y position.
 * @return If the position is valid.
 */
bool isEmpty(int x, int y) {
  return gameSceneState.gameMap[x][y] == MAP_EMPTY ||
         gameSceneState.gameMap[x][y] == MAP_TARGET;
}

/**
 * @brief Check if the position is valid.
 * @param x The X position.
 * @param y The Y position.
 * @return If the position is valid.
 */
bool isValidMapChar(char ch) {
  return ch == MAP_EMPTY || ch == MAP_WALL || ch == MAP_TARGET ||
         ch == MAP_PLAYER || ch == MAP_BOX;
}

/**
 * @brief Check if the position is valid.
 * @param x The X position.
 * @param y The Y position.
 * @return If the position is valid.
 */
bool isPosValid(int x, int y) {
  return x >= 0 && x < MAP_HEIGHT && y >= 0 && y < MAP_WIDTH;
}