/*
 * FSM_UART.c
 *
 *  Created on: Jan 4, 2023
 *      Author: HP
 */

#include "FSM_UART.h"
#include "LED_SERIES_PROCESSING.h"
#include "stdio.h"
#include "string.h"

char data[1];
uint8_t new_value[2];
uint8_t temp[1];
uint8_t temp1[1];
uint32_t value, value2;
uint8_t running_mode_flag  = 0;
uint8_t string_flag 	   = INIT;
int first_time_pressed 	   = 0;
int green_time, yellow_time;
//use only in this file
UART_HandleTypeDef huart3;

int isEqualToGo(void)
{
	if(data[0] == '0') return 1;
	else return 0;
}

int isEqualToNormal(void)
{
	if (data[0] == '1') return 1;
	else return 0;
}

int isEqualToGreen(void)
{
	if (data[0] == '2') return 1;
	else return 0;
}

int isEqualToYellow(void)
{
	if (data[0] == '3') return 1;
	else return 0;
}

int isEqualToStop(void)
{
	if(data[0] == '4') return 1;
	else return 0;
}

void fsm_communication()
{
	switch(string_flag)
	{
	case INIT:
		// display the mode to the LCD
		Lcd_Goto_XY(0, 1);
		Lcd_Send_String("PRESS 0 TO RUN");

		// check if '0' is pressed
		if (isEqualToGo())
		{
			string_flag = GO;
		}
		else string_flag = INIT;
		data[0] = NULL;
		break;
	case GO:
		string_flag = RUNNING;
		Lcd_Clear_Display();
		data[0] = NULL;
		break;
	case RUNNING:
		string_flag = NORMAL;
		data[0] = NULL;
		break;
	case NORMAL:
		// TODO
		// display the mode to the LCD
		Lcd_Goto_XY(0, 5);
		Lcd_Send_String("NORMAL");

		if(value == 9 || value2 == 9)
		{
			Lcd_Clear_Display();
			Lcd_Goto_XY(0, 5);
			Lcd_Send_String("NORMAL");
			Lcd_Goto_XY(1, 0);
			Lcd_Send_String("TIME");
			Lcd_Goto_XY(1, 6);
			sprintf((char*) temp, "%lu", value);
			Lcd_Send_String(temp);
			Lcd_Goto_XY(1, 10);
			sprintf((char*) temp, "%lu", value2);
			Lcd_Send_String(temp);

		}
		// countdown the remaining time of each green and yellow light
		Lcd_Goto_XY(1, 0);
		Lcd_Send_String("TIME");
		Lcd_Goto_XY(1, 6);
		sprintf((char*) temp, "%lu", value);
		Lcd_Send_String(temp);
		Lcd_Goto_XY(1, 10);
		sprintf((char*) temp, "%lu", value2);
		Lcd_Send_String(temp);
		// check if '2' is pressed
		if (isEqualToGreen())
		{
			data[0] = NULL;
			string_flag = ADJUST_GREEN;
		}
		break;
	case ADJUST_GREEN:
		// TODO
		// display the mode to the LCD
		if (first_time_pressed == 0)
		{
			Lcd_Goto_XY(0, 2);
			Lcd_Send_String("ADJUST GREEN");
			Lcd_Goto_XY(1, 0);
			Lcd_Send_String("ENTER NEW VALUE");
		}
		else
		{
			Lcd_Goto_XY(0, 1);
			Lcd_Send_String("VALUE UPDATED");
		}
		// check if '3' is pressed
		if (isEqualToYellow())
		{
			if (first_time_pressed == 0)
			{
				green_time = (data[0] - (int)48) * 100;
				Lcd_Clear_Display();
				Lcd_Goto_XY(1, 0);
				Lcd_Send_String("NEW VALUE:");
				Lcd_Goto_XY(1, 12);
				sprintf((char*) temp1, "%lu", green_time / 100);
				Lcd_Send_String(temp1);
				first_time_pressed = 1;
			}
			else
			{
				string_flag = ADJUST_YELLOW;
				first_time_pressed = 0;
			}
			data[0] = NULL;
		}
		else
		{
			if (data[0] != NULL)
			{
				green_time = (data[0] - (int)48) * 100;
				Lcd_Clear_Display();
				Lcd_Goto_XY(1, 0);
				Lcd_Send_String("NEW VALUE:");
				Lcd_Goto_XY(1, 12);
				sprintf((char*) temp1, "%lu", green_time / 100);
				Lcd_Send_String(temp1);
				data[0] = NULL;
				first_time_pressed = 1;
			}
		}
		break;
	case ADJUST_YELLOW:
		// TODO
		// display the mode to the LCD
		if (first_time_pressed == 0)
		{
			Lcd_Goto_XY(0, 1);
			Lcd_Send_String("ADJUST YELLOW");
			Lcd_Goto_XY(1, 0);
			Lcd_Send_String("ENTER NEW VALUE");
		}
		else
		{
			Lcd_Goto_XY(0, 1);
			Lcd_Send_String("VALUE UPDATED");
		}
		// check if '4' is pressed
		if (isEqualToStop())
		{
			if (first_time_pressed == 0)
			{
				yellow_time = (data[0] - (int)48) * 100;
				Lcd_Clear_Display();
				Lcd_Goto_XY(1, 0);
				Lcd_Send_String("NEW VALUE:");
				Lcd_Goto_XY(1, 12);
				sprintf((char*) temp1, "%lu", yellow_time / 100);
				Lcd_Send_String(temp1);
				first_time_pressed = 1;
			}
			else
			{
				string_flag = EXIT;
				Lcd_Clear_Display();
				first_time_pressed = 0;
			}
			data[0] = NULL;
		}
		else
		{
			if (data[0] != NULL)
			{
				yellow_time = (data[0] - (int)48) * 100;
				Lcd_Clear_Display();
				Lcd_Goto_XY(1, 0);
				Lcd_Send_String("NEW VALUE:");
				Lcd_Goto_XY(1, 12);
				sprintf((char*) temp1, "%lu", yellow_time / 100);
				Lcd_Send_String(temp1);
				data[0] = NULL;
				first_time_pressed = 1;
			}
		}
		break;
	default:
		// reset all counters
		string_flag = INIT;
		data[0]  = NULL;
		counter  = 500;
		another_counter = 500;
		counter1 = 100;
		counter2 = 100;
		index0   = 0;
		index1   = 0;
		index2   = 0;
		break;
	}
}
