#include "watch_app.h"
#include "measurement.h"

#define WatchFace 0
#define WatchNum 1
#define Measurement 2
#define Game 3

extern uint8_t app_num;
extern bool accept;
extern bool option;
extern bool rotate_en;

int app(uint8_t apps);

void change_app(bool left);

void change_app_num(uint8_t app);