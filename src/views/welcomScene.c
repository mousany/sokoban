#include <stdint.h>

#include "lcd/lcd.h"
#include "utils.h"
#include "views/gameMap.h"
#include "views/gameScene.h"
#include "views/levelSelector.h"
#include "views/welcomeScene.h"

/**
 * @brief The timeout of the welcome scene
 */
struct WelcomeSceneState {
  uint64_t startTime;  // The start time of the welcome scene
  int animationState;  // The animation state
  int boxNum;          // The number of boxes
  char gameMap[MAP_WELCOME_WIDTH * MAP_WELCOME_HEIGHT];  // The game map
  char
      lastGameMap[MAP_WELCOME_WIDTH * MAP_WELCOME_HEIGHT];  // The last game map
};

// The state of the welcome scene
struct WelcomeSceneState welcomeSceneState = {
    .startTime = 0,
    .animationState = 0,
    .boxNum = 0,
};

/**
 * @brief Initialize the welcome scene
 */
void welcomeSceneInit(void) {
  LCD_Clear(0x7bef);
  welcomeSceneState.startTime = get_timer_value();
  // Initialize the game map
  welcomeSceneState.animationState = 0;
  for (int i = 0; i < MAP_WELCOME_WIDTH * MAP_WELCOME_HEIGHT; i++) {
    welcomeSceneState.gameMap[i] = welcomeMap[i];
    welcomeSceneState.lastGameMap[i] = -1;
  }
}

/**
 * @brief Update the welcome scene
 * @param button_event The button event
 * @return Whether the welcome scene is finished
 */
bool welcomeSceneUpdate(int button_event) {
  if (button_event == BUTTON_1) {
    switchToLevelSelector();
    return TRUE;
  }
  // Update the game map
  uint64_t deltaTimeMs = (get_timer_value() - welcomeSceneState.startTime) /
                         (SystemCoreClock / 4000);
  if (deltaTimeMs > WELCOME_TIMEOUT) {
    switchToLevelSelector();
    return TRUE;
  }
  // Update the game map
  if (deltaTimeMs < WELCOME_ANIMATION_START) return FALSE;

  // Update the game map
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
    // Add a box
    if (welcomeSceneState.boxNum < MAX_WELCOME_BOX_NUM &&
        currentAnimationState % 2 == 0) {
      int targetIndex =  // The index of the box
          targetHeight * MAP_WELCOME_WIDTH + MAP_WELCOME_WIDTH - 1;
      welcomeSceneState.gameMap[targetIndex] = MAP_BOX;
      welcomeSceneState.boxNum++;
    }
    return TRUE;
  }
  // Return false if the game map is not updated
  return FALSE;
}

/**
 * @brief Render the welcome scene
 */
void welcomeSceneRender(void) {
  for (int y = 0; y < MAP_WELCOME_HEIGHT; y++) {
    for (int x = 0; x < MAP_WELCOME_WIDTH; x++) {
      if (welcomeSceneState.gameMap[y * MAP_WELCOME_WIDTH + x] ==
          welcomeSceneState
              .lastGameMap[y * MAP_WELCOME_WIDTH + x])  // No change
        continue;
      welcomeSceneState.lastGameMap[y * MAP_WELCOME_WIDTH + x] =
          welcomeSceneState.gameMap[y * MAP_WELCOME_WIDTH + x];
      renderBlock(x, y, welcomeSceneState.gameMap[y * MAP_WELCOME_WIDTH + x]);
    }
  }
  if (welcomeSceneState.animationState == 0) {  // Render the title
    LCD_ShowStringOverlap(36, 30, "Battle City", BLACK);
    LCD_ShowStringOverlap(37, 30, "Battle City", BLACK);
    LCD_ShowStringOverlap(37, 31, "Battle City", BLACK);
    LCD_ShowStringOverlap(36, 31, "Battle City", BLACK);
  }
}

/**
 * @brief Switch to the welcome scene
 */
void switchToWelcomeScene(void) {
  welcomeSceneInit();
  setWindowRender(&welcomeSceneRender);
  setWindowUpdate(&welcomeSceneUpdate);
}