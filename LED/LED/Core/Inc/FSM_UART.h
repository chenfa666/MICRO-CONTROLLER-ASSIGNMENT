/*
 * FSM_UART.h
 *
 *  Created on: Jan 5, 2023
 *      Author: nguye
 */

#ifndef INC_FSM_UART_H_
#define INC_FSM_UART_H_
#include "main.h"

#define INIT 			0
#define READING 		1
#define GO 				2
#define	RUNNING			3
#define	NORMAL			4
#define ADJUST_GREEN	5
#define ADJUST_YELLOW	6
#define EXIT 			7
extern char data[1];
extern uint8_t string_flag;
extern uint8_t temp[1], temp1[1];

void fsm_communication();
void fsm_running_mode();
int isEqualToGo(void);
int isEqualToStop(void);
int isEqualToGreen(void);
int isEqualToYellow(void);
int isEqualToNormal(void);

#endif /* INC_FSM_UART_H_ */
