/*
 * drv_gpio_led.c
 *
 *  Created on: Sep 5, 2018
 *      Author: abel
 */




#include <drv_gpio_led.h>

void init_led_gpio()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull   = GPIO_PULLUP;
	GPIO_InitStruct.Speed	=	GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
