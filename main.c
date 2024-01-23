#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "DEV_Config.h"
#include "hardware/irq.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_1in28.h"
#include "QMI8658.h"
#include "hardware/timer.h"
#include "hardware.h"
#include "watch_app.h"
#include "apps.h"
 

UDOUBLE Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
bool awake = 1;
uint8_t timeout = 60;

bool system_tic(repeating_timer_t *rt) 
{
    if(alarm_en) 
    {
        DEV_SET_PWM(100);
        alarm();
        LCD_1IN28_Display(BlackImage);
    }
    else
    {
        if(encoder_state[H_PRESS] & awake) {awake = 0; option = 0; DEV_SET_PWM(0); encoder_state_clear();}
        else if(encoder_state[H_PRESS] & !awake) {awake = 1; option = 0; change_app_num(WatchFace); timeout = 60; encoder_state_clear();}
        //test();
        if (awake)
        {      
            
            if(!option)
            {   if(encoder_state[H_HOLD]) {option = 1;timeout = 60;}
                else if(encoder_state[H_LEFT]) {change_app(true); timeout = 60;}
                else if(encoder_state[H_RIGHT]) {change_app(false); timeout = 60;}
                
            }
            else 
            {
                if(encoder_state[H_HOLD]) {accept = 1;timeout = 60;}
                if(encoder_state[H_LEFT] | encoder_state[H_RIGHT]) {timeout = 60;}
            }
            
            
            app(app_num);
            LCD_1IN28_Display(BlackImage);
            encoder_state_clear();
            DEV_SET_PWM(brightness);
            timeout--;
            if (timeout < 1)
            {
                awake = 0; option = 0; accept = 0; DEV_SET_PWM(0);
            }
            else if(timeout < 20) {DEV_SET_PWM(10);}
        }
    }
    return true;
}


int main(){
    stdio_init_all();
    hardware_init();
    sleep_us(64);
    
    BlackImage = (UWORD *)malloc(Imagesize);
    Paint_white_background(BlackImage);

    while (1) {}

    return 0;
}


