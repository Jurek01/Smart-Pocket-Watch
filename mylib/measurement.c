#include "measurement.h"


float acc[3], gyro[3];
unsigned int tim_count = 0;
uint8_t position[2] = {120, 120};
bool seting_option = 0;
uint16_t brightness_c = RED;
uint16_t rotate_c = BLACK;

void measurement(void)
{
    if(option)
    {
        
        if(!seting_option)
        {
            brightness_c = RED;
            rotate_c = BLACK;
            if(encoder_state[H_LEFT]) {if(brightness > 10)  {brightness = brightness - 10;}}
            else if(encoder_state[H_RIGHT]) {if(brightness < 100) {brightness = brightness + 10;}}
            if(accept) {seting_option = 1; accept = 0;}
        }
        else
        {
            brightness_c = BLACK;
            rotate_c = RED;
            if(encoder_state[H_LEFT]) {rotate_en = 0;}
            else if(encoder_state[H_RIGHT]) {rotate_en = 1;}
            if(accept) {seting_option = 0; accept = 0; option = 0;}
        }
        
        if (rotate_en) {Paint_SetRotate(90*rotate());}
        Paint_Clear(WHITE);
        Paint_DrawString_EN(30, 100, "BRIGHTNESS = ", &Font16, brightness_c, WHITE);
        Paint_DrawString_EN(30, 125, " ROTATE EN = ", &Font16, rotate_c, WHITE);
        Paint_DrawNum(170, 100, brightness, &Font16, 0, brightness_c, WHITE);
        Paint_DrawNum(170, 125, rotate_en, &Font16, 0, rotate_c, WHITE);

    }
    else
    {
        //pomiar napiecia baterii
        const float conversion_factor = 3.3f / (1 << 12) * 2;
        uint16_t result = adc_read();
        float bat_vol = result * conversion_factor;

        //pomiar akcelerometu i żyroskopu
        QMI8658_read_xyz(acc, gyro, &tim_count);
        if (rotate_en) {Paint_SetRotate(90*rotate());}
        Paint_Clear(WHITE);
        
        Paint_DrawString_EN(30, 50, "ACC_X = ", &Font16, BLACK, WHITE);
        Paint_DrawString_EN(30, 75, "ACC_Y = ", &Font16, BLACK, WHITE);
        Paint_DrawString_EN(30, 100, "ACC_Z = ", &Font16, BLACK, WHITE);
        Paint_DrawString_EN(30, 125, "GYR_X = ", &Font16, BLACK, WHITE);
        Paint_DrawString_EN(30, 150, "GYR_Y = ", &Font16, BLACK, WHITE);
        Paint_DrawString_EN(30, 175, "GYR_Z = ", &Font16, BLACK, WHITE);
        Paint_DrawString_EN(30, 175, "GYR_Z = ", &Font16, BLACK, WHITE);
        Paint_DrawNum(120, 50, acc[0] - 40, &Font16, 2, BLACK, WHITE);
        Paint_DrawNum(120, 75, acc[1] -80, &Font16, 2, BLACK, WHITE);
        Paint_DrawNum(120, 100, acc[2] + 35, &Font16, 2, BLACK, WHITE);
        Paint_DrawNum(120, 125, gyro[0], &Font16, 2, BLACK, WHITE);
        Paint_DrawNum(120, 150, gyro[1], &Font16, 2, BLACK, WHITE);
        Paint_DrawNum(120, 175, gyro[2], &Font16, 2, BLACK, WHITE);
        Paint_DrawString_EN(50, 200, "BAT(V)=", &Font16, BLACK, WHITE);
        Paint_DrawNum(130, 200, bat_vol, &Font16, 2, BLACK, WHITE);
    }
}

uint8_t rotate()
{
    QMI8658_read_xyz(acc, gyro, &tim_count);
    if(acc[0] > 800) {return 2;}
    else if(acc[0] < -800) {return 0;}
    else if(acc[1] > 800) {return 3;}
    else if(acc[1] < -800) {return 1;}
    else {return 0;}
}

int8_t move(float acc_value)
{
    if (acc_value < 0) {return (int8_t)(-1*acc_value*acc_value/10000);}
    else {return (int8_t)(1*acc_value*acc_value/10000);}
}

void game()
{
    if(option) {position[0] = 120; position[1] = 120; option = 0;}
    QMI8658_read_xyz(acc, gyro, &tim_count);
    Paint_SetRotate(0);
    Paint_Clear(WHITE);
    position[0] = position[0] + move(acc[1]);
    position[1] = position[1] - move(acc[0]);

    Paint_DrawCircle(position[0], position[1], 10, BLACK, DOT_PIXEL_4X4, DRAW_FILL_FULL);
}





