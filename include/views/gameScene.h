#ifndef __GAMESCENE_H
#define __GAMESCENE_H

#include "gd32vf103.h"
#include "views/gameMap.h"
#include "windows.h"

#define MAP_PIX_WIDTH 7

#define MAP_EMPTY ' '
#define MAP_WALL '#'
#define MAP_BOX 'O'
#define MAP_PLAYER '@'
#define MAP_TARGET 'x'
#define MAP_BOX_ON_TARGET 'X'
#define MAP_PLAYER_ON_TARGET '+'

struct GameSceneState;

extern struct GameSceneState gameSceneState;

void gameSceneInit(int level, int box_num);

bool gameSceneUpdate(int button_event);

void gameSceneRender(void);

void switchToGameScene(int level, int box_num);

char moveInBox(char ch);

char moveOutBox(char ch);

char moveInPlayer(char ch);

char moveOutPlayer(char ch);

bool isBox(int x, int y);

bool isWall(int x, int y);

bool isEmpty(int x, int y);

bool isPosValid(int x, int y);

bool isValidMapChar(char ch);

#endif