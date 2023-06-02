#include "views/gameMap.h"

// clang-format off
// levelMap[level - 1][y * MAP_WIDTH + x]
const char levelMap[MAX_LEVEL_NUM][MAP_WIDTH * MAP_HEIGHT] = {
    "     ##############       x          x       ##############                       @     O  O  O  O                           ##############       x          x       ##############                     ",
    "    #x         #        #          #    #####  #x      #####       ##      O  O @      x#   x##  O             ##   O          ###  O     O #####    x#    #####    #          #        #         x#    ",
    "x                  x  ###  ##  ##  ###      #  #x  x#  #    #####  ######  #####@  O   O    O    O    O     O  O    O   #####  ######  #####    #  #x  x#  #      ###  ##  ##  ###  x                  x"
};

// Welcome map.
const char welcomeMap[MAP_WELCOME_WIDTH * MAP_WELCOME_HEIGHT] = {
    "             X          x    ##############         x          x       X ############## X                                                                      X ##############         x        X x         ##############                     X "
};

const char levelMaxBoxNum[MAX_LEVEL_NUM] = {
    4, 6, 8
};

// clang-format on

// Get the map char at (x, y) in level.
char getMapChar(int level, int x, int y) {
  return levelMap[level - 1][y * MAP_WIDTH + x];
}
