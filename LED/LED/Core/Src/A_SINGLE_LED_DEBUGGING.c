/*
 * A_SINGLE_LED_DEBUGGING.c
 *
 *  Created on: Nov 17, 2022
 *      Author: HP
 */

#include "A_SINGLE_LED_DEBUGGING.h"
#include "PINS_AND_PORTS.h"

int counter_led = TIME_DELAY_FOR_BLINKING_LED;

void toggleLED(GPIO_TypeDef *PORT, uint16_t PIN)
{
	HAL_GPIO_TogglePin(PORT, PIN);
}

void interruptServiceForDisplaySingleLED()
{
	if (counter_led > 0)
	{
		counter_led--;
		if (counter_led <= 0)
		{
			counter_led = TIME_DELAY_FOR_BLINKING_LED;
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_PIN);
		}
	}
}

