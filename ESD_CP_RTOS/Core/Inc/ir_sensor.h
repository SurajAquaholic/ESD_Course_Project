#ifndef __IR_SENSOR__
#define __IR_SENSOR__

#include "main.h"
#include "ssd1306.h"
#include "stdbool.h"
#include "timer.h"
//#include "bitmap.h"


void ir_init();
void check_ir_sensor();
bool return_right_status();
bool return_left_status();
bool return_both_status();

#endif /* __IR_SENSOR__ */
