#ifndef __U4C6_H_
#define __U4C6_H_

#define BUTTON_A      5
#define BUTTON_B      6

#define LED_R         13
#define LED_G         11
#define LED_B         12

#define DEBOUNCE_MS   100

#include "hardware/i2c.h"
#include "display/ssd1306.h"
#include "neopixel/neopixel.h"

void init_gpio();
uint64_t handle_btn_a(alarm_id_t id, void *user_data);
uint64_t handle_btn_b(alarm_id_t id, void *user_data);
static void debounce(uint gpio, uint32_t events);

#endif