#include "windows.h"

#include <stddef.h>

#include "lcd/lcd.h"
#include "systick.h"
#include "utils.h"

WindowsHandle windowsHandle = {NULL, NULL};

void nextFrame(void) {
  if (windowsHandle.windowRender != NULL && windowsHandle.windowIsUpdated) {
    (*windowsHandle.windowRender)();
    windowsHandle.windowIsUpdated = FALSE;
  }
  if (windowsHandle.windowUpdate != NULL) {
    windowsHandle.windowIsUpdated = (*windowsHandle.windowUpdate)(Get_Event());
  }
}

void windowsInit(void) {
  windowsHandle.windowUpdate = NULL;
  windowsHandle.windowRender = NULL;
  windowsHandle.windowIsUpdated = TRUE;
}

void windowsStart(void) {
  while (1) {
    nextFrame();
    // delay_1ms(30);
  }
}

void setWindowUpdate(bool (*windowUpdate)(int)) {
  windowsHandle.windowUpdate = windowUpdate;
  windowsHandle.windowIsUpdated = TRUE;
}

void setWindowRender(void (*windowRender)(void)) {
  windowsHandle.windowRender = windowRender;
  windowsHandle.windowIsUpdated = TRUE;
}