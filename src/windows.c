#include "windows.h"

#include <stddef.h>

#include "lcd/lcd.h"
#include "systick.h"
#include "utils.h"

WindowsHandle windowsHandle = {NULL, NULL, 0};

void nextFrame(void) {
  if (windowsHandle.windowUpdate != NULL) {
    (*windowsHandle.windowUpdate)(Get_Event());
  }
  if (windowsHandle.windowRender != NULL) {
    (*windowsHandle.windowRender)();
  }
}

void windowsInit(void) {
  windowsHandle.windowUpdate = NULL;
  windowsHandle.windowRender = NULL;
  windowsHandle.state = 0;
}

void windowsStart(void) {
  while (1) {
    nextFrame();
    LCD_Clear(BLACK);
    // delay_1ms(30);
  }
}

void setWindowUpdate(void (*windowUpdate)(int)) {
  windowsHandle.windowUpdate = windowUpdate;
}

void setWindowRender(void (*windowRender)(void)) {
  windowsHandle.windowRender = windowRender;
}