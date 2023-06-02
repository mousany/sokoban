#ifndef __GAMESCENE_H
#define __GAMESCENE_H

#include "gd32vf103.h"
#include "views/gameMap.h"
#include "windows.h"

#define MAP_EMPTY ' '
#define MAP_WALL '#'
#define MAP_BOX 'O'
#define MAP_PLAYER '@'
#define MAP_TARGET 'x'
#define MAP_BOX_ON_TARGET 'X'
#define MAP_PLAYER_ON_TARGET '+'

struct GameSceneState;

// The state of the game scene
extern struct GameSceneState gameSceneState;

// Initialize the game scene
void gameSceneInit(int level, int box_num);

// Update the game scene
bool gameSceneUpdate(int button_event);

// Render the game scene
void gameSceneRender(void);

// Whether the game scene is win
bool gameSceneIsWin();

// Switch to the game scene
void switchToGameScene(int level, int box_num);

// Render the block
void renderBlock(int x, int y, char ch);

// Move in the box
char moveInBox(char ch);

// Move out the box
char moveOutBox(char ch);

// Move in the player
char moveInPlayer(char ch);

// Move out the player
char moveOutPlayer(char ch);

// Whether the position is a box
bool isBox(int x, int y);

// Whether the position is a wall
bool isWall(int x, int y);

// Whether the position is empty
bool isEmpty(int x, int y);

// Whether the position is valid
bool isPosValid(int x, int y);

// Whether the character is a valid map character
bool isValidMapChar(char ch);

#endif