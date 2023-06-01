#include <stdint.h>

#include "lcd/lcd.h"
#include "utils.h"
#include "views/gameMap.h"
#include "views/gameScene.h"
#include "views/levelSelector.h"
#include "views/welcomeScene.h"

struct WelcomeSceneState {
  uint64_t startTime;
  int animationState;
  int boxNum;
  char gameMap[MAP_WELCOME_WIDTH * MAP_WELCOME_HEIGHT];
  char lastGameMap[MAP_WELCOME_WIDTH * MAP_WELCOME_HEIGHT];
};

struct WelcomeSceneState welcomeSceneState = {
    .startTime = 0,
    .animationState = 0,
    .boxNum = 0,
};

void welcomeSceneInit(void) {
  LCD_Clear(0x7bef);
  welcomeSceneState.startTime = get_timer_value();
  welcomeSceneState.animationState = 0;
  for (int i = 0; i < MAP_WELCOME_WIDTH * MAP_WELCOME_HEIGHT; i++) {
    welcomeSceneState.gameMap[i] = welcomeMap[i];
    welcomeSceneState.lastGameMap[i] = -1;
  }
}

bool welcomeSceneUpdate(int button_event) {
  if (button_event == BUTTON_1) {
    switchToLevelSelector();
    return TRUE;
  }
  uint64_t deltaTimeMs = (get_timer_value() - welcomeSceneState.startTime) /
                         (SystemCoreClock / 4000);
  if (deltaTimeMs > WELCOME_TIMEOUT) {
    switchToLevelSelector();
    return TRUE;
  }
  if (deltaTimeMs < WELCOME_ANIMATION_START) return FALSE;

  int currentAnimationState =
      (deltaTimeMs - WELCOME_ANIMATION_START) / WELCOME_ANIMATION_INTERVAL;
  if (currentAnimationState != welcomeSceneState.animationState) {
    welcomeSceneState.animationState = currentAnimationState;

    const int targetHeight = 5;
    for (int x = 0; x < MAP_WELCOME_WIDTH; ++x) {
      // Rolling the line of targetHeight left a step
      int currentIndex = targetHeight * MAP_WELCOME_WIDTH + x;
      welcomeSceneState.gameMap[currentIndex] =
          welcomeSceneState.gameMap[currentIndex + 1];
    }
    if (welcomeSceneState.boxNum < MAX_WELCOME_BOX_NUM &&
        currentAnimationState % 2 == 0) {
      int targetIndex =
          targetHeight * MAP_WELCOME_WIDTH + MAP_WELCOME_WIDTH - 1;
      welcomeSceneState.gameMap[targetIndex] = MAP_BOX;
      welcomeSceneState.boxNum++;
    }
    return TRUE;
  }

  return FALSE;
}

void welcomeSceneRender(void) {
  for (int y = 0; y < MAP_WELCOME_HEIGHT; y++) {
    for (int x = 0; x < MAP_WELCOME_WIDTH; x++) {
      if (welcomeSceneState.gameMap[y * MAP_WELCOME_WIDTH + x] ==
          welcomeSceneState.lastGameMap[y * MAP_WELCOME_WIDTH + x])
        continue;
      welcomeSceneState.lastGameMap[y * MAP_WELCOME_WIDTH + x] =
          welcomeSceneState.gameMap[y * MAP_WELCOME_WIDTH + x];
      renderBlock(x, y, welcomeSceneState.gameMap[y * MAP_WELCOME_WIDTH + x]);
    }
  }
  if (welcomeSceneState.animationState == 0) {
    LCD_ShowStringOverlap(36, 30, "Battle City", BLACK);
    LCD_ShowStringOverlap(37, 30, "Battle City", BLACK);
    LCD_ShowStringOverlap(37, 31, "Battle City", BLACK);
    LCD_ShowStringOverlap(36, 31, "Battle City", BLACK);
  }
}

void switchToWelcomeScene(void) {
  welcomeSceneInit();
  setWindowRender(&welcomeSceneRender);
  setWindowUpdate(&welcomeSceneUpdate);
}