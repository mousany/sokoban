#include "utils.h"

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

int Get_Event(void) {
  if (Get_Button(JOY_LEFT)) return JOY_LEFT;
  if (Get_Button(JOY_DOWN)) return JOY_DOWN;
  if (Get_Button(JOY_RIGHT)) return JOY_RIGHT;
  if (Get_Button(JOY_UP)) return JOY_UP;
  if (Get_Button(JOY_CTR)) return JOY_CTR;
  if (Get_Button(BUTTON_1)) return BUTTON_1;
  if (Get_Button(BUTTON_2)) return BUTTON_2;
  return BUTTON_NONE;
}

/* -----------------------------
 Description: Return 1 if button BOOT0 ch is pressed
                          Return 0 otherwise
----------------------------- */
int Get_BOOT0(void) { return (int)(gpio_input_bit_get(GPIOA, GPIO_PIN_8)); }