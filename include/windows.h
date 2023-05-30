#ifndef __WINDOWS_H
#define __WINDOWS_H

#include <stddef.h>

typedef struct {
  void (*windowUpdate)(int);
  void (*windowRender)(void);
  int state;
} WindowsHandle;

extern WindowsHandle windowsHandle;

void nextFrame(void);

void windowsStart(void);

void setWindowUpdate(void (*windowUpdate)(int));

void setWindowRender(void (*windowRender)(void));

#endif