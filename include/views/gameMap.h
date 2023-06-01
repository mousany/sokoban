#ifndef __GAMEMAP_H
#define __GAMEMAP_H

#define MAX_LEVEL_NUM 3
#define MAP_WIDTH 20
#define MAP_HEIGHT 10
#define MAP_WELCOME_WIDTH 22
#define MAP_WELCOME_HEIGHT 11

extern const char levelMap[MAX_LEVEL_NUM][MAP_WIDTH * MAP_HEIGHT];
extern const char levelMaxBoxNum[MAX_LEVEL_NUM];
extern const char welcomeMap[MAP_WELCOME_WIDTH * MAP_WELCOME_HEIGHT];

char getMapChar(int level, int x, int y);

#endif  // __GAMEMAP_H