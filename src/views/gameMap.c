#include "views/gameMap.h"

// clang-format off
const char levelMap[MAX_LEVEL_NUM][MAP_WIDTH * MAP_HEIGHT] = {
    "                         @                  x                                                                      O         #                                                                          ",
    "                         @                  x                                                                      O         #                                                                          ",
    "                         @                  x                                                                      O         #                                                                          "
};
// clang-format on

char getMapChar(int level, int x, int y) {
  return levelMap[level - 1][y * MAP_WIDTH + x];
}
