#ifndef __MY_TIMER_H
#define	__MY_TIMER_H

#include "main.h"



void timers_init(void);
void temp_timeout_start(void);
void temp_timeout_stop(void);
void temp_timer_handler(void * p_context);

void spi_overtime_timer_start(void);
void spi_overtime_timer_stop(void);
void spi_overtime_timer_restart(void);
void spi_overtime_timer_handler(void * p_context);

void watch_dog_timeout_start(void);
void watch_dog_timeout_stop(void);
void watch_dog_timer_handler(void * p_context);

#endif 

