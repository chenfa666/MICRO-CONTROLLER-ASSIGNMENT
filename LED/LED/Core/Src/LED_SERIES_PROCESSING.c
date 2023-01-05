/*
 * LED_SERIRES_PROCESSING.c
 *
 *  Created on: Nov 17, 2022
 *      Author: HP
 */

#include "stdio.h"
#include "main.h"
#include "LED_SERIES_PROCESSING.h"
#include "FSM_UART.h"
static int status 	= 0;
int index0 	   		= 0,
	index1 			= 0,
	index2 			= 0,
	flag 	   		= 0;
uint32_t value 		= 0,
		value2 		= 0,
	another_counter = READY_TIME,
		 counter 	= READY_TIME,
		 counter1   = TIME_DELAY_FOR_LED_SERIRES,
		 counter2	= TIME_DELAY_FOR_LED_SERIRES;
int 	green_time  = GREEN,
		yellow_time = YELLOW;

// Buffers for LEDs animations
uint32_t LEDsBuffer[BUFFER_SIZE] = {0x80100, 0x80C00, 0x06000, 0x32000},
		 GREEN_LEDs[2] 			 = {0x04100, 0x00000},
		 YELLOW_LEDs[2] 		 = {0x30C00, 0x00000};
static uint32_t baseComparator 	 =  0x80000;
void resetCounter(void)
{
	switch (index0)
	{
	case 0:
		another_counter = green_time + yellow_time;
		counter = green_time;
		break;
	case 1:
		counter = yellow_time;
		break;
	case 2:
		counter = green_time + yellow_time;
		another_counter = green_time;
		break;
	case 3:
		another_counter = yellow_time;
		break;
	default: break;
	}
}

void Latch_Enable(void)
{
	HAL_GPIO_WritePin(LE_GPIO_Port, LE_Pin, RESET);
}

void Latch_Disable(int counter)
{
	if (counter <= 0) return;
		while (counter-- != 0) {
			HAL_GPIO_WritePin(LE_GPIO_Port, LE_Pin, GPIO_PIN_SET);
		}
}

void Output_Enable(void)
{
	HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, SET);
}

void Output_Disable(void)
{
	HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, RESET);
}

void CLock_ON(int counter)
{
	if (counter <= 0) return;
			while (counter-- != 0) {
				HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, RESET);
			}
}

void CLock_OFF(int counter)
{
	if (counter <= 0) return;
			while (counter-- != 0) {
				HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, SET);
			}
}

void Data_Out(GPIO_PinState state)
{
	HAL_GPIO_WritePin(SDI_GPIO_Port, SDI_Pin, state);
}

void turnOffAllLED()
{
	uint8_t i;
	Latch_Disable(1);
	for (i = 0; i <= 19; i++)
	{
		CLock_OFF(1);
		Data_Out(0);
		CLock_ON(10);
	}
	Latch_Enable();
}

void LED_Display(uint32_t data, int size)
{
	uint8_t i;
	Latch_Disable(1);
	for (i = 0; i < 20; i++)
	{
		CLock_OFF(1);
		Data_Out((data & baseComparator) == baseComparator);
		data = data << 1;
		CLock_ON(10);
	}
	Latch_Enable();
}

void interruptServiceForDisplayLEDsSeries()
{
/*	if (counter > 0)
	{
		if (counter % TIME_DELAY_FOR_LED_SERIRES == 0)
		{
			flag = 1;
			value = (counter / TIME_DELAY_FOR_LED_SERIRES);
		}
		counter--;
		if (counter <= 0)
		{
			resetCounter();
			LED_Display(LEDsBuffer[index0], BUFFER_SIZE);
			index0++;
			if (index0 == BUFFER_SIZE)
			{
				index0 = 0;
			}
		}
	}*/
	if (counter > 0 || another_counter > 0)
	{
		if (counter % TIME_DELAY_FOR_LED_SERIRES == 0 ||
			another_counter % TIME_DELAY_FOR_LED_SERIRES ==0)
		{
			if (status % 2 == 1)
			{
				value  = (counter / TIME_DELAY_FOR_LED_SERIRES);
				value2 = (another_counter / TIME_DELAY_FOR_LED_SERIRES);
			}
			else
			{
				value2 = (another_counter / TIME_DELAY_FOR_LED_SERIRES);
				value = (counter / TIME_DELAY_FOR_LED_SERIRES);
			}
		}
		if (counter > 0)
		{
			counter--;
		}
		if (another_counter>0)
		{
			another_counter--;
		}
		if (counter <= 0 || another_counter <= 0)
		{
			resetCounter();
			if (index0 == 0 || index0 == 2)
			{
				status++;
			}
			LED_Display(LEDsBuffer[index0], BUFFER_SIZE);
			index0++;
			if (index0 == BUFFER_SIZE)
			{
				index0 = 0;
			}
		}
	}
}

void interruptServiceForDisplayGREENLEDsSeries()
{
	if (counter1 > 0)
	{
		counter1--;
		if (counter1 <= 0)
		{
			counter1 = 100;
			LED_Display(GREEN_LEDs[index1], 2);
			index1++;
			if (index1 == BUFFER_GREEN_SIZE)
			{
				index1 = 0;
			}
		}
	}
}

void interruptServiceForDisplayYELLOWLEDsSeries()
{
	if (counter2 > 0)
	{
		counter2--;
		if (counter2 <= 0)
		{
			counter2 = 100;
			LED_Display(YELLOW_LEDs[index2], 2);
			index2++;
			if (index2 == BUFFER_YELLOW_SIZE)
			{
				index2 = 0;
			}
		}
	}
}
