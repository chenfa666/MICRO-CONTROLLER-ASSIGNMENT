/*
 * LED_SERIES_PROCESSING.h
 *
 *  Created on: Nov 17, 2022
 *      Author: HP
 */

#ifndef INC_LED_SERIES_PROCESSING_H_
#define INC_LED_SERIES_PROCESSING_H_

#include "main.h"

#define 		NUMBERS_OF_BUFFER				1
#define 		BUFFER_SIZE 					4
#define			BUFFER_GREEN_SIZE				2
#define 		BUFFER_YELLOW_SIZE				2
#define 		TIME_DELAY_FOR_LED_SERIRES 		100
#define 		GREEN							300
#define 		YELLOW							200
#define 		READY_TIME						500

extern int flag;
extern uint32_t value, value2;
extern int index0, index1, index2, green_time, yellow_time;
extern uint32_t counter, another_counter, counter1, counter2;
void resetCounter(void);
void Latch_Enable(void);
void Latch_Disable(int);
void Output_Enable(void);
void Output_Disable(void);
void Clock_ON(int);
void Clock_OFF(int);
void Data_Out(GPIO_PinState);
void turnOffAllLED(void);
void LED_Display(uint32_t, int);
void interruptServiceForDisplayLEDsSeries(void);
void interruptServiceForDisplayGREENLEDsSeries(void);
void interruptServiceForDisplayYELLOWLEDsSeries(void);
#endif /* INC_LED_SERIES_PROCESSING_H_ */
