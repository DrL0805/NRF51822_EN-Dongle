#ifndef __MAIN_H
#define	__MAIN_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "sdk_common.h"
#include "nrf_drv_config.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_esb.h"
#include "nrf_error.h"
#include "app_timer.h"
#include "app_util_platform.h"
#include "app_error.h"

#include "my_uart.h"
#include "my_radio.h"
#include "my_timer.h"



// 软件版本 -----------------------------------------------------------
#define 	VERSION_LEVEL_1		(0)		//一级版本号
#define     VERSION_LEVEL_2		(4)		//二级版本号

uint8_t XOR_Cal(uint8_t * dat,uint16_t length);
void gpio_default_init(void);
void clocks_start(void);
uint8_t get_random_number(void);
bool ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len);

#endif 

