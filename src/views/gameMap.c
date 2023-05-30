#include "views/gameMap.h"

// clang-format off
const char levelMap[MAX_LEVEL_NUM][MAP_WIDTH * MAP_HEIGHT] = {
    "     ##############       x          x       ##############                       @     O  O  O  O                           ##############       x          x       ##############                     ",
    "    #x         #        #          #    #####  #x      #####       ##      O  O @      x#   x##  O             ##   O          ###  O     O #####    x#    #####    #          #        #         x#    ",
    "x                  x  ###  ##  ##  ###      #  #x  x#  #    #####  ######  #####@  O   O    O    O    O     O  O    O   #####  ######  #####    #  #x  x#  #      ###  ##  ##  ###  x                  x"
};

const char levelMaxBoxNum[MAX_LEVEL_NUM] = {
    4, 6, 8
};

// clang-format on

char getMapChar(int level, int x, int y) {
  return levelMap[level - 1][y * MAP_WIDTH + x];
}
