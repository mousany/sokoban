#ifndef __WELCOMESCENE_H
#define __WELCOMESCENE_H

#include "windows.h"

#define WELCOME_TIMEOUT 3000

struct WelcomeSceneState;

extern struct WelcomeSceneState welcomeSceneState;

void welcomeSceneInit(void);

bool welcomeSceneUpdate(int button_event);

void welcomeSceneRender(void);

void switchToWelcomeScene(void);

#endif  // __WELCOMESCENE_H