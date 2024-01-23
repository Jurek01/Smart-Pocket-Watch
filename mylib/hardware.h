#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/rtc.h"
#include "DEV_Config.h"
#include "LCD_1in28.h"
#include "GUI_Paint.h"
#include "QMI8658.h"
#include "hardware/sync.h"
#include "hardware/timer.h"
#include "watch_app.h"

#define ENCODER_A_PIN 16  
#define ENCODER_B_PIN 19
#define ENCODER_C_PIN 5

#define H_LEFT 0 
#define H_RIGHT 1
#define H_PRESS 2
#define H_HOLD 3
//left, right, press, hold

extern bool encoder_state[4];
extern repeating_timer_t timer;
extern uint8_t brightness;
bool system_tic(repeating_timer_t *rt);

void encoder_state_clear();

int64_t button_alarm_callback(alarm_id_t id, void *user_data); 

void encoder_isr(uint gpio, uint32_t events); 


void encoder_init();

void hardware_init();

