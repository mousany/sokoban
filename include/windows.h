#ifndef __WINDOWS_H
#define __WINDOWS_H

#include <stddef.h>

#include "gd32vf103.h"
typedef struct {
  bool (*windowUpdate)(int);
  void (*windowRender)(void);
  bool windowIsUpdated;
} WindowsHandle;

extern WindowsHandle windowsHandle;

void nextFrame(void);

void windowsStart(void);

void setWindowUpdate(bool (*windowUpdate)(int));

void setWindowRender(void (*windowRender)(void));

#endif