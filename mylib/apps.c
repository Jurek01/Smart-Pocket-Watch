#include "apps.h"


uint8_t app_num = 0;
uint8_t app_count = 3;
bool accept = 0;
bool option = 0;
bool rotate_en = 1;

void change_app(bool left)
{
    if(left) 
    {
        if(app_num > 0) {app_num--;}
        else {app_num = app_count;}
    }
    else
    {
        if(app_num < app_count) {app_num++;}
        else {app_num = 0;}
    } 
    
}

void change_app_num(uint8_t app)
{
    app_num = app;
}

int app(uint8_t app)
{
    
    if(app == WatchFace) 
    {
        Paint_watchface();
    }
    else if(app == WatchNum) {Paint_watch_num();}
    else if(app == Measurement) {measurement();}
    else if(app == Game) {game();}
    return 0;
}