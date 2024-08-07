# Button debounce - software approach


## 1. EXTI + TIM


This software approach uses both external and timer interrupt.

Buttons are initialized as GPIO_EXTI. Remember PA8 and PC8 will be interpreted by CPU as the same interrupt source.

![image](https://github.com/jmamej/STM32_SW_Button_Debounce/assets/57408600/8a96b4e6-e363-4197-a60d-13623c60a64d)

From datasheet read which buss is connected with timer that you are going to use.

![image](https://github.com/jmamej/STM32_SW_Button_Debounce/assets/57408600/180c77f1-726e-4b2a-98b2-87b50c230dbb)

*Part of datasheet block diagram*

Set timer accordingly (for 64 MHz clock)

![image](https://github.com/jmamej/STM32_SW_Button_Debounce/assets/57408600/fef3a27b-bb06-4fdb-b590-ca5f8062c9a1)


![image](https://github.com/jmamej/STM32_SW_Button_Debounce/assets/57408600/a0f63624-e285-4871-806d-faae9b21458e)


![image](https://github.com/jmamej/STM32_SW_Button_Debounce/assets/57408600/09820add-8d8f-434c-8df1-77f45ee49b3e)

*Prescaler and counter period are by default incremented by 1*


in main.c place HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) 
```
HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  if(GPIO_Pin == BUTTON_X_Pin){
    if(!button_flag[x]){
      button_flag[x] = 1;
      button_press_state[x] = 0;
      button_press_timer[x] = 0;
    }
  }
  .
  .
  .
  HAL_TIM_Base_Start_IT(&htim2);
}
```


External interrupt awaits falling edge (internal pullup) on pin connected to button.

When falling edge occurs timer interrupt is started.

Every millisecond button pin state is being checked, if its pressed for some ammount of time button press is acknowledged, when its released for some time length of butone press will determine if button_press_counter or button_long_press counter is being incrermented

For more information please review code or this simple diagram:

![image](https://github.com/jmamej/STM32_SW_Button_Debounce/assets/57408600/42b844fd-a67f-41fe-9980-e3eeb56ed15e)

*Block diagram*

## 2. EXTI


This software approach uses only external interrupt.

Initiate buttons os above.


```
#include "Buttons.h"

long current_time, button_check_timer;

int main() {
  while (1) {
	  current_time = HAL_GetTick();		/* check current time */
	  if (button_check_flag && current_time >= button_check_timer) {
		  buttons_resolve_press();
		  button_check_timer = current_time + 1;
	  }	
  }
}
```

button_check_flag is set when HAL_GPIO_EXTI_Callback detects falling edge:

```
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
```
Files for following approach are in X folder.
