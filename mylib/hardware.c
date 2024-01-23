#include "hardware.h"

//ENCODER

bool wait;
bool encoder_state[4] = {0, 0, 0, 0};
uint8_t brightness = 50;
repeating_timer_t timer;
datetime_t t = 
{
    .year  = 2023,
    .month = 1,
    .day   = 3,
    .dotw  = 4, // 0 is Sunday
    .hour  = 8,
    .min   = 3,
    .sec   = 00
};



void encoder_state_clear()
{
    encoder_state[0] = false; encoder_state[1] = false; encoder_state[2] = false; encoder_state[3] = false;
}

int64_t waiting(alarm_id_t id, void *user_data) {wait = 0; return 0;}

int64_t button_alarm_callback(alarm_id_t id, void *user_data) 
{

    bool C = gpio_get(ENCODER_C_PIN);
    if (!C) {encoder_state[H_PRESS] = false; encoder_state[H_HOLD] = true; }
    else if (C) {encoder_state[H_PRESS] = true; encoder_state[H_HOLD] = false;}
    encoder_state[H_LEFT] = false; encoder_state[H_RIGHT] = false;
    wait = 1;
    add_alarm_in_ms(500, waiting, NULL, false);
    return 0;
}

void encoder_isr(uint gpio, uint32_t events) 
{
    if(!wait)
        {
        bool A = gpio_get(ENCODER_A_PIN);
        bool B = gpio_get(ENCODER_B_PIN);
        bool C = gpio_get(ENCODER_C_PIN);
        if(!A)
        {
            if (B) {encoder_state[H_LEFT] = false; encoder_state[H_RIGHT] = true;}
            else if (!B) {encoder_state[H_LEFT] = true; encoder_state[H_RIGHT] = false;}
            add_alarm_in_ms(250, waiting, NULL, false);
        }
        if(!C) 
        {
            add_alarm_in_ms(500, button_alarm_callback, NULL, false);
            encoder_state[H_LEFT] = false; encoder_state[H_RIGHT] = false;
        }
    }
}

void encoder_init()
{
    gpio_init(ENCODER_A_PIN);
    gpio_set_dir(ENCODER_A_PIN, GPIO_IN);
    gpio_pull_up(ENCODER_A_PIN);

    gpio_init(ENCODER_B_PIN);
    gpio_set_dir(ENCODER_B_PIN, GPIO_IN);
    gpio_pull_up(ENCODER_B_PIN);

    gpio_init(ENCODER_C_PIN);
    gpio_set_dir(ENCODER_C_PIN, GPIO_IN);
    gpio_pull_up(ENCODER_C_PIN);

    
    gpio_set_irq_enabled_with_callback(ENCODER_A_PIN, GPIO_IRQ_EDGE_FALL, true, &encoder_isr);
    gpio_set_irq_enabled(ENCODER_C_PIN, GPIO_IRQ_EDGE_FALL, true);
}


//
void hardware_init()
{
    rtc_init();
    rtc_set_datetime(&t);

    DEV_Module_Init();     
    DEV_SET_PWM(brightness);
    QMI8658_init();

    adc_init();
    adc_gpio_init(29);
    adc_select_input(3);

    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);
    encoder_init();

    add_repeating_timer_us(-500000, system_tic, NULL, &timer);
}


