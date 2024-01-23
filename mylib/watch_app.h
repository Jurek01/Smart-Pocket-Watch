#ifndef _CLOCK_APP
#define _CLOCK_APP

#include "pico/stdlib.h"
#include "LCD_1in28.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "GUI_Paint.h"
#include "hardware.h"
#include "measurement.h"
#include "apps.h"

//Hands and numbers position
#define hand_sec_x(x) (120 + cos_x[x]*1.1)
#define hand_sec_y(x) (120 + sin_x[x]*1.1)
#define hand_min_x(x) (120 + cos_x[x]*0.9)
#define hand_min_y(x) (120 + sin_x[x]*0.9)
#define hand_hour_x(x) (120 + cos_x[x*5]*0.7)
#define hand_hour_y(x) (120 + sin_x[x*5]*0.7)
#define num_x(x) (120 + cos_x[x*5]*1.2)
#define num_y(x) (120 + sin_x[x*5]*1.2)
 
extern datetime_t t;
extern bool alarm_en;
//LUT sin and cos
static int8_t sin_x[120] = 
{
-100,-99,-98,-95,-91,-87,-81,-74,-67,-59,-50,-41,-31,-21,-10,0,10,21,31,41,50,59,67,74,81,87,91,95,98,99,
100,99,98,95,91,87,81,74,67,59,50,41,31,21,10,0,-10,-21,-31,-41,-50,-59,-67,-74,-81,-87,-91,-95,-98,-99,
-100,-99,-98,-95,-91,-87,-81,-74,-67,-59,-50,-41,-31,-21,-10,0,10,21,31,41,50,59,67,74,81,87,91,95,98,99,
100,99,98,95,91,87,81,74,67,59,50,41,31,21,10,0,-10,-21,-31,-41,-50,-59,-67,-74,-81,-87,-91,-95,-98,-99,
};

static int8_t cos_x[120] = 
{
0,10,21,31,41,50,59,67,74,81,87,91,95,98,99,100,99,98,95,91,87,81,74,67,59,50,41,31,21,10,0,
-10,-21,-31,-41,-50,-59,-67,-74,-81,-87,-91,-95,-98,-99,-100,-99,-98,-95,-91,-87,-81,-74,-67,-59,-50,-41,-31,-21,-10,
0,10,21,31,41,50,59,67,74,81,87,91,95,98,99,100,99,98,95,91,87,81,74,67,59,50,41,31,21,10,0,
-10,-21,-31,-41,-50,-59,-67,-74,-81,-87,-91,-95,-98,-99,-100,-99,-98,-95,-91,-87,-81,-74,-67,-59,-50,-41,-31,-21,-10
};

void alarm();
void Paint_watchface(void);
void Paint_watch_num();
void Paint_white_background(uint16_t *BlackImage);


#endif