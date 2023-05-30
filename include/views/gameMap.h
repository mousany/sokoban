#ifndef __GAMEMAP_H
#define __GAMEMAP_H

#define MAX_LEVEL_NUM 3
#define MAX_BOX_NUM 2
#define MAP_WIDTH 20
#define MAP_HEIGHT 10

extern const char levelMap[MAX_LEVEL_NUM][MAP_WIDTH * MAP_HEIGHT];

char getMapChar(int level, int x, int y);

#endif  // __GAMEMAP_H