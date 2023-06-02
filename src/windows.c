#include "windows.h"

#include <stddef.h>

#include "lcd/lcd.h"
#include "systick.h"
#include "utils.h"

// Windows handle instance.
WindowsHandle windowsHandle = {NULL, NULL};

/**
 * @brief Render the next frame.
 */
void nextFrame(void) {
  // Render the next frame.
  if (windowsHandle.windowRender != NULL && windowsHandle.windowIsUpdated) {
    (*windowsHandle.windowRender)();
    windowsHandle.windowIsUpdated = FALSE;
  }
  // Update the window.
  if (windowsHandle.windowUpdate != NULL) {
    windowsHandle.windowIsUpdated = (*windowsHandle.windowUpdate)(Get_Event());
  }
}

/**
 * @brief Initialize the windows.
 */
void windowsInit(void) {
  windowsHandle.windowUpdate = NULL;
  windowsHandle.windowRender = NULL;
  windowsHandle.windowIsUpdated = TRUE;
}

/**
 * @brief Start the windows.
 */
void windowsStart(void) {
  while (1) {
    nextFrame();
    // delay_1ms(30);
  }
}

/**
 * @brief Set the window update function.
 * @param windowUpdate The window update function.
 */
void setWindowUpdate(bool (*windowUpdate)(int)) {
  windowsHandle.windowUpdate = windowUpdate;
  windowsHandle.windowIsUpdated = TRUE;
}

/**
 * @brief Set the window render function.
 * @param windowRender The window render function.
 */
void setWindowRender(void (*windowRender)(void)) {
  windowsHandle.windowRender = windowRender;
  windowsHandle.windowIsUpdated = TRUE;
}