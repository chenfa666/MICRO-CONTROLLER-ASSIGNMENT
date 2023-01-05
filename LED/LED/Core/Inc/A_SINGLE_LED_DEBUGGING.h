/*
 * A_SINGLE_LED_DEBUGGING.h
 *
 *  Created on: Nov 17, 2022
 *      Author: HP
 */

#ifndef INC_A_SINGLE_LED_DEBUGGING_H_
#define INC_A_SINGLE_LED_DEBUGGING_H_

#include "main.h"

#define			TIME_DELAY_FOR_BLINKING_LED		50

void toggleLED(GPIO_TypeDef* , uint16_t);
void interruptServiceForDisplaySingleLED(void);

#endif /* INC_A_SINGLE_LED_DEBUGGING_H_ */
