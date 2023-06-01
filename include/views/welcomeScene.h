#ifndef __WELCOMESCENE_H
#define __WELCOMESCENE_H

#include "windows.h"

#define WELCOME_TIMEOUT 12000
#define MAX_WELCOME_BOX_NUM 6
#define WELCOME_ANIMATION_INTERVAL 500
#define WELCOME_ANIMATION_START 1000

struct WelcomeSceneState;

extern struct WelcomeSceneState welcomeSceneState;

void welcomeSceneInit(void);

bool welcomeSceneUpdate(int button_event);

void welcomeSceneRender(void);

void switchToWelcomeScene(void);

#endif  // __WELCOMESCENE_H