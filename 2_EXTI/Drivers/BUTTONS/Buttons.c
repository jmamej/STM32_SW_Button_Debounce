/*
 * Buttons.c
 *
 *  Created on: Jul 5, 2024
 *      Author: Juliano
 */
#include "buttons.h"

/* variable definition  */
int button_check_flag;
int button_flag[NUM_OF_BUTTONS];
int button_press_ack[NUM_OF_BUTTONS] = {0, 0, 0, 0};
int button_press_counter[NUM_OF_BUTTONS];
int button_long_press_counter[NUM_OF_BUTTONS];
int button_press_state[NUM_OF_BUTTONS];
int button_press_timer[NUM_OF_BUTTONS];
volatile long press_timer;
GPIO_TypeDef* button_ports[NUM_OF_BUTTONS] = {BUTTON_A_GPIO_Port, BUTTON_B_GPIO_Port, BUTTON_C_GPIO_Port, BUTTON_D_GPIO_Port};
uint16_t button_pins[NUM_OF_BUTTONS] = {BUTTON_A_Pin, BUTTON_B_Pin, BUTTON_C_Pin, BUTTON_D_Pin};

/* External interrupt callback functions - triggers on falling edge*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	buttons_check_falling_edge(GPIO_Pin);
}

/* Function checking for first falling edge on button pin - sets button_check_flag if found */
void buttons_check_falling_edge(uint16_t irq_pin) {
	for (int i = 0; i < NUM_OF_BUTTONS; i++) {
		if (irq_pin == button_pins[i]) {
			button_check_flag = 1;
			if (!button_flag[i]) {
				button_flag[i] = 1;
				button_press_state[i] = 0;
				button_press_timer[i] = 0;
				button_check_flag = 1;
				press_timer = HAL_GetTick();
			}
		}
	}
}

/* Checks for button press or button bounce - if button press time is insufficient, button press will not be acknowledged */
void buttons_resolve_press() {
	for (int i = 0; i < NUM_OF_BUTTONS; i++) {
	  if (button_flag[i]) {
		  HAL_GPIO_ReadPin(button_ports[i], button_pins[i]) ? button_press_state[i]-- : button_press_state[i]++;
		  button_press_timer[i]++;
		  if (button_press_state[i] >= ACK_TIME)	button_press_ack[i] = 1;
		  if (button_press_state[i] > MAX_STATE_THRESHOLD)	button_press_state[i] = MAX_STATE_THRESHOLD;
		  else if (button_press_state[i] < MIN_STATE_THRESHOLD) {
			  if (button_press_ack[i]) {
				  button_press_timer[i] > LONG_PRESS_TIME ? button_long_press_counter[i]++ : button_press_counter[i]++;
				  button_press_ack[i] = 0;
			  }
			  button_flag[i] = 0;
			  button_check_flag = button_flag[0] + button_flag[1] + button_flag[2] + button_flag[3];
			  if (!button_check_flag) {
				  //buttons_debug(i);
				  button_check_flag = 0;
			  }
		  }
	   }
	}
}

/* Debugging function prints name of button pressed and duration it was pressed */
void buttons_debug(int button_num) {
	switch (button_num) {
		  case 0:
			  printf("Button A pressed for %d ms - short_counter: %d - long_counter: %d\n", button_press_timer[button_num], button_press_counter[button_num], button_long_press_counter[button_num]);
			  break;
		  case 1:
			  printf("Button B pressed for %d ms - short_counter: %d - long_counter: %d\n", button_press_timer[button_num], button_press_counter[button_num], button_long_press_counter[button_num]);
			  break;
		  case 2:
			  printf("Button C pressed for %d ms - short_counter: %d - long_counter: %d\n", button_press_timer[button_num], button_press_counter[button_num], button_long_press_counter[button_num]);
			  break;
		  case 3:
			  printf("Button D pressed for %d ms - short_counter: %d - long_counter: %d\n", button_press_timer[button_num], button_press_counter[button_num], button_long_press_counter[button_num]);
			  break;
	  }
}

