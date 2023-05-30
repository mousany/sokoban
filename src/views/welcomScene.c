#include <stdint.h>

#include "lcd/lcd.h"
#include "utils.h"
#include "views/levelSelector.h"
#include "views/welcomeScene.h"

struct WelcomeSceneState {
  uint64_t startTime;
  int animationState;
};

struct WelcomeSceneState welcomeSceneState = {
    .startTime = 0,
};

void welcomeSceneInit(void) { welcomeSceneState.startTime = get_timer_value(); }

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
  return FALSE;
}

void welcomeSceneRender(void) {
  LCD_Clear(BLACK);
  LCD_ShowString(10, 15, "Battle City", BLUE);
}

void switchToWelcomeScene(void) {
  welcomeSceneInit();
  setWindowRender(&welcomeSceneRender);
  setWindowUpdate(&welcomeSceneUpdate);
}