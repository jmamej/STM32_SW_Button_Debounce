/*
 * Buttons.h
 *
 *  Created on: Jul 5, 2024
 *      Author: Juliano
 */
#ifndef BUTTONS_BUTTONS_H_
#define BUTTONS_BUTTONS_H_

#include "stdio.h"
#include "stdint.h"
#include "main.h"

#define NUM_OF_BUTTONS 4
#define MAX_STATE_THRESHOLD 7
#define MIN_STATE_THRESHOLD -3
#define ACK_TIME 3
#define LONG_PRESS_TIME 800

/* Declare variables as extern */
extern int button_check_flag;
extern int button_flag[NUM_OF_BUTTONS];
extern int button_press_ack[NUM_OF_BUTTONS];
extern int button_press_counter[NUM_OF_BUTTONS];
extern int button_long_press_counter[NUM_OF_BUTTONS];
extern int button_press_state[NUM_OF_BUTTONS];
extern int button_press_timer[NUM_OF_BUTTONS];

extern GPIO_TypeDef* button_ports[NUM_OF_BUTTONS];
extern uint16_t button_pins[NUM_OF_BUTTONS];

/* Function prototypes */
void buttons_check_falling_edge(uint16_t irq_pin);
void buttons_resolve_press(void);
void buttons_debug(int button_num);

#endif /* BUTTONS_BUTTONS_H_ */
