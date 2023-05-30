#ifndef __GAMESCENE_H
#define __GAMESCENE_H

#include "gd32vf103_gpio.h"
#include "windows.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 10

#define MAP_EMPTY ' '
#define MAP_WALL '#'
#define MAP_BOX 'O'
#define MAP_PLAYER '@'

struct GameSceneState;

extern struct GameSceneState gameSceneState;

void gameSceneInit(void);

void gameSceneUpdate(int button);

void gameSceneRender(void);

void switchToGameScene();

bool isBox(int x, int y);

bool isWall(int x, int y);

bool isEmpty(int x, int y);

bool isPosValid(int x, int y);

#endif