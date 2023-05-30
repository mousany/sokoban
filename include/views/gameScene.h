#ifndef __GAMESCENE_H
#define __GAMESCENE_H

#include "gd32vf103.h"
#include "windows.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 10

#define MAP_PIX_WIDTH 7

#define MAP_EMPTY ' '
#define MAP_WALL '#'
#define MAP_BOX 'O'
#define MAP_PLAYER '@'

struct GameSceneState;

extern struct GameSceneState gameSceneState;

void gameSceneInit(void);

bool gameSceneUpdate(int button_event);

void gameSceneRender(void);

void switchToGameScene(int level, int box_num);

bool isBox(int x, int y);

bool isWall(int x, int y);

bool isEmpty(int x, int y);

bool isPosValid(int x, int y);

#endif