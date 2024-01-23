#include "watch_app.h"


uint8_t set_time = 0;
uint16_t hand_hour_c = RED;
uint16_t hand_min_c = RED;
uint16_t hand_sec_c = RED;
uint16_t hand_day_c = RED;
uint16_t hand_month_c = RED;
uint16_t hand_year_c = RED;
uint16_t set_time_c = RED;
uint16_t set_alarm_c = BLACK;

bool alarm_en = 0;
uint8_t set_option = 0;
uint8_t i = 10;

static void rtc_alarm_callback(void) 
{
    alarm_en = 1;
}

void alarm()
{
    if(i > 0)
    {
        Paint_Clear(RED);
        Paint_DrawString_EN(70, 120, "ALARM", &Font24, BLACK, WHITE);
        i--;
    }
    else {alarm_en = 0; i = 10;}   
}

void Set_time(bool face)
{   
    if(set_time == 0)
{
    if(encoder_state[H_LEFT]) 
    {
        if (t.hour < 23) {t.hour++;}
        else {t.hour = 0;}
    }
    else if(encoder_state[H_RIGHT]) 
    {
        if (t.hour > 0) {t.hour--;}
        else {t.hour = 23;}    
    }
    hand_hour_c = BLUE;
}
    else if(set_time == 1)
    {
        if(encoder_state[H_LEFT]) 
        {
            if (t.min < 60) {t.min++;}
            else {t.min = 0;}
        }
        else if(encoder_state[H_RIGHT]) 
        {
            if (t.min > 0) {t.min--;}
            else {t.min = 60;}    
        }
        hand_min_c = BLUE;
    }
    else if(set_time == 2)
    {
        if(encoder_state[H_LEFT]) 
        {
            if (t.sec < 60) {t.sec++;}
            else {t.sec = 0;}
        }
        else if(encoder_state[H_RIGHT]) 
        {
            if (t.sec > 0) {t.sec--;}
            else {t.sec = 60;}    
        }
        hand_sec_c = BLUE;
    }
    else if(set_time == 5)
    {
        if(encoder_state[H_LEFT]) 
        {
            if(t.month == 2) 
            {
                if (t.day < 28) {t.day++;}
                else {t.day = 1;}    
            }
            else if((t.month == 4) | (t.month == 6) | (t.month == 9) | (t.month == 11))
            {
                if (t.day < 30) {t.day++;}
                else {t.day = 1;}
            }
            else 
            {
                if (t.day < 31) {t.day++;}
                else {t.day = 1;}
            }
        }
        else if(encoder_state[H_RIGHT]) 
        {
            if (t.day > 1) {t.day--;}
            else 
            {   
                if(t.month == 2) {t.day = 28;}
                else if((t.month == 4) | (t.month == 6) | (t.month == 9) | (t.month == 11)) {t.day = 30;}
                else {t.day = 31;}
            }    
        }
        hand_day_c = BLUE;
    }
    else if(set_time == 4)
    {
        if(encoder_state[H_LEFT]) 
        {
            if (t.month < 12) {t.month++;}
            else {t.month = 0;}
        }
        else if(encoder_state[H_RIGHT]) 
        {
            if (t.month > 0) {t.month--;}
            else {t.month = 12;}    
        }

        hand_month_c = BLUE;
    }
    else if(set_time == 3)
    {
        if(encoder_state[H_LEFT]) {t.year++;}
        else if(encoder_state[H_RIGHT]) {t.year--;}

        hand_year_c = BLUE;
    }
    if(accept)
    {
        if(face)
        {
            if(set_time < 2) {set_time++; accept = 0;}
            else {set_time = 0; option = 0; accept = 0; set_option = 0;}
        }
        else 
        {
            if(set_time < 5) {set_time++; accept = 0;}
            else {set_time = 0; option = 0; accept = 0; set_option = 0;}
        }
    }
    
}

void Paint_white_background(uint16_t *BlackImage)
{
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
    Paint_SetScale(65);    
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);
}

void Paint_watchface(void)
{
    hand_hour_c = RED;
    hand_min_c = RED;
    hand_sec_c = RED;

    if(option)
    {
        Set_time(true);
        rtc_set_datetime(&t);      
    }
    else {rtc_get_datetime(&t);}

    if (rotate_en) {Paint_SetRotate(90*rotate());}

    Paint_Clear(WHITE);
    if (option) {Paint_DrawString_EN(45, 50, "SET TIME", &Font16, BLACK, WHITE);}
    //Numbers
    Paint_DrawNum(171, 15, 1, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(213, 57, 2, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(228, 114, 3, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(213, 171, 4, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(171, 213, 5, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(114, 228, 6, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(57, 213, 7, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(15, 171, 8, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(0, 114, 9, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(15, 60, 10, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(55, 18, 11, &Font16, 0, BLACK, WHITE);
    Paint_DrawNum(108, 0, 12, &Font16, 0, BLACK, WHITE);
    //Hands
    Paint_DrawLine(120, 120, hand_hour_x(t.hour), hand_hour_y(t.hour), hand_hour_c, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(120, 120, hand_min_x(t.min), hand_min_y(t.min), hand_min_c, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    Paint_DrawLine(120, 120, hand_sec_x(t.sec), hand_sec_y(t.sec), hand_sec_c, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    //Centre Circle       
    Paint_DrawCircle(120, 120, 10, BLACK, DOT_PIXEL_4X4, DRAW_FILL_FULL);
}

void Paint_watch_num()
{
    hand_hour_c = BLACK;
    hand_min_c = BLACK;
    hand_sec_c = BLACK;
    hand_day_c = BLACK;
    hand_month_c = BLACK;
    hand_year_c = BLACK;

    if (rotate_en) {Paint_SetRotate(90*rotate());}
    Paint_Clear(WHITE);

    if(option)
    {
        if(encoder_state[H_PRESS]) {set_option = 1; encoder_state_clear(); accept = 0;}
        if (set_option < 2) 
        {
            if(encoder_state[H_LEFT]) 
            {
                set_time_c = RED;
                set_alarm_c = BLACK;
                set_option = 0;
            }
            else if(encoder_state[H_RIGHT]) 
            {
                set_time_c = BLACK;
                set_alarm_c = RED;
                set_option = 1;
            }
            if(accept) {set_option = set_option + 2; accept = 0;}

            Paint_DrawString_EN(45, 50, "SET TIME", &Font16, set_time_c, WHITE);
            Paint_DrawString_EN(45, 65, "SET ALARM", &Font16, set_alarm_c, WHITE);
            
        }
        else if (set_option == 2)
        {
            Set_time(false);
            rtc_set_datetime(&t);   
        }
        else if (set_option == 3)
        {
            Set_time(false);
            rtc_set_alarm(&t, &rtc_alarm_callback);
        }    
        
    }
    else {rtc_get_datetime(&t);}



    //TIME
    if(t.hour > 9) {Paint_DrawNum(50, 102, t.hour, &Font24, 0, hand_hour_c, WHITE);}
    else 
    {
        {Paint_DrawNum(47, 102, 0, &Font24, 0, hand_hour_c, WHITE);}
        {Paint_DrawNum(65, 102, t.hour, &Font24, 0, hand_hour_c, WHITE);}
    }    
    Paint_DrawString_EN(80, 102, ":", &Font24, BLACK, WHITE);
    if(t.min > 9) {Paint_DrawNum(100, 102, t.min, &Font24, 0, hand_min_c, WHITE);}
    else 
    {
        {Paint_DrawNum(97, 102, 0, &Font24, 0, hand_min_c, WHITE);}
        {Paint_DrawNum(115, 102, t.min, &Font24, 0, hand_min_c, WHITE);}
    }
    Paint_DrawString_EN(130, 102, ":", &Font24, BLACK, WHITE);
    if(t.sec > 9) {Paint_DrawNum(150, 102, t.sec, &Font24, 0, hand_sec_c, WHITE);}
    else 
    {
        {Paint_DrawNum(149, 102, 0, &Font24, 0, hand_sec_c, WHITE);}
        {Paint_DrawNum(165, 102, t.sec, &Font24, 0, hand_sec_c, WHITE);}
    }

    //Week day
    if(t.dotw == 0) { Paint_DrawString_EN(30, 140, "Sunday", &Font16, BLACK, WHITE);}
    else if(t.dotw == 1) { Paint_DrawString_EN(30, 140, "Monday", &Font16, BLACK, WHITE);}
    else if(t.dotw == 2) { Paint_DrawString_EN(24, 140, "Tuesday", &Font16, BLACK, WHITE);}
    else if(t.dotw == 3) { Paint_DrawString_EN(10, 140, "Wednesday", &Font16, BLACK, WHITE);}
    else if(t.dotw == 4) { Paint_DrawString_EN(17, 140, "Thrusday", &Font16, BLACK, WHITE);}
    else if(t.dotw == 5) { Paint_DrawString_EN(30, 140, "Friday", &Font16, BLACK, WHITE);}
    else if(t.dotw == 6) { Paint_DrawString_EN(17, 140, "Saturday", &Font16, BLACK, WHITE);}

    //DATE
    if(t.day > 9) {Paint_DrawNum(110, 140, t.day, &Font16, 0, hand_day_c, WHITE);}
    else 
    {
        {Paint_DrawNum(110, 140, 0, &Font16, 0, hand_day_c, WHITE);}
        {Paint_DrawNum(120, 140, t.day, &Font16, 0, hand_day_c, WHITE);}
    } 
    Paint_DrawString_EN(130, 140, ".", &Font16, BLACK, WHITE);
    if(t.month > 9) {Paint_DrawNum(140, 140, t.month, &Font16, 0, hand_month_c, WHITE);}
    else 
    {
        {Paint_DrawNum(140, 140, 0, &Font16, 0, hand_month_c, WHITE);}
        {Paint_DrawNum(150, 140, t.month, &Font16, 0, hand_month_c, WHITE);}
    } 
    Paint_DrawString_EN(160, 140, ".", &Font16, BLACK, WHITE);
    Paint_DrawNum(170, 140, t.year, &Font16, 0, hand_year_c, WHITE);
 
    //Batery
    const float conversion_factor = 3.3f / (1 << 12) * 2;
    uint16_t result = adc_read();
    float bat_vol = result * conversion_factor;
    float bat_vol_precent = (bat_vol - 3.6) * 100 / 0.65;
    Paint_DrawString_EN(80, 160, "BAT: ", &Font16, BLACK, WHITE);
    Paint_DrawNum(125, 160, bat_vol_precent, &Font16, 0, BLACK, WHITE);
    Paint_DrawString_EN(150, 160, "%", &Font16, BLACK, WHITE);
}

