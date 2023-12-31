#include "utils.h"

#include "gd32vf103.h"
#include "gd32vf103_libopt.h"

/* -----------------------------
 Description: Return 1 if button number ch is pressed
                          Return 0 otherwise
----------------------------- */
int Get_Button(int ch) {
  /* hack for new board*/
  if (ch != GPIO_PIN_13)
    return (int)(gpio_input_bit_get(GPIOA, ch));
  else
    return (int)(gpio_input_bit_get(GPIOC, ch));
}

int Get_Raw_Event(void) {                       // Get the raw event
  if (Get_Button(JOY_LEFT)) return JOY_LEFT;    // Joystick left
  if (Get_Button(JOY_DOWN)) return JOY_DOWN;    // Joystick down
  if (Get_Button(JOY_RIGHT)) return JOY_RIGHT;  // Joystick right
  if (Get_Button(JOY_UP)) return JOY_UP;        // Joystick up
  if (Get_Button(JOY_CTR)) return JOY_CTR;      // Joystick center
  if (Get_Button(BUTTON_1)) return BUTTON_1;    // Button 1
  if (Get_Button(BUTTON_2)) return BUTTON_2;    // Button 2
  return BUTTON_NONE;
}

// Debounce the button
int Get_Event(void) {
  static int lastEvent = BUTTON_NONE;
  static uint64_t lastTime = 0;

  // Get the raw event
  int event = Get_Raw_Event();
  if (event == BUTTON_NONE) {
    lastEvent = BUTTON_NONE;
    return BUTTON_NONE;
  }

  uint64_t currentTime = get_timer_value();
  uint64_t deltaTimeMs = (currentTime - lastTime) / (SystemCoreClock / 4000);

  // Debounce
  if (event == lastEvent) {
    if (deltaTimeMs > BUTTON_DEBOUNCE_MS) {  // Debounce time
      lastTime = currentTime;
      return event;
    }
  } else {  // New event
    lastEvent = event;
    lastTime = currentTime;
    return event;
  }
  return BUTTON_NONE;
}

/* -----------------------------
 Description: Return 1 if button BOOT0 ch is pressed
                          Return 0 otherwise
----------------------------- */
int Get_BOOT0(void) { return (int)(gpio_input_bit_get(GPIOA, GPIO_PIN_8)); }