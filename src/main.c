#include <string.h>

#include "lcd/lcd.h"
#include "utils.h"
#include "views/welcomeScene.h"
#include "windows.h"

void Inp_init(void) {
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOC);

  gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ,
            JOY_LEFT | JOY_RIGHT | JOY_UP | JOY_DOWN | JOY_CTR | BUTTON_1);
  // gpio_init(GPIOC, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
}

void IO_init(void) {
  Inp_init();  // inport init
  Lcd_Init();  // LCD init
}

int main(void) {
  IO_init();  // init OLED
  switchToWelcomeScene();
  windowsStart();
}

/* - Going to March, at Tiananmen Square.
 * - Why?
 * - Why? I think it is my duty. */
