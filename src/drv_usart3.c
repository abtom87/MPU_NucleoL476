/*
 * drv_usart3.c
 *
 *  Created on: Sep 5, 2018
 *      Author: abel
 */

#include "string.h"
#include "stm32l4xx.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_usart.h"

void init_usart_gpio(void)
{
	/*USART2 Rx--PC11 Tx--PC10 */
	GPIO_InitTypeDef USART_GPIOStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	USART_GPIOStruct.Mode = GPIO_MODE_AF_PP;
	USART_GPIOStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	USART_GPIOStruct.Pull = GPIO_NOPULL;
	USART_GPIOStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	USART_GPIOStruct.Alternate = GPIO_AF7_USART3;

	HAL_GPIO_Init(GPIOC, &USART_GPIOStruct);

}

void init_usart_peripheral(void)
{

	/*USART2 Rx--PC11 Tx--PC10 */

	LL_USART_InitTypeDef USART2_InitStruct;

	__HAL_RCC_USART3_CLK_ENABLE()
	;

	USART2_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART2_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART2_InitStruct.OverSampling = LL_USART_OVERSAMPLING_8;
	USART2_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART2_InitStruct.BaudRate = 115200;
	USART2_InitStruct.Parity = USART_PARITY_NONE;
	USART2_InitStruct.StopBits = USART_STOPBITS_1;

	LL_USART_Init(USART3, &USART2_InitStruct);
	LL_USART_Enable(USART3);

}

void USART_Tx_byte(uint8_t byte)
{

	while ((SET != LL_USART_IsActiveFlag_TXE(USART3)))
		;
	LL_USART_TransmitData8(USART3, byte);
}

void USART_Tx_string(char* str)
{

	int i = 0;
	for (i = 0; i < strlen(str); i++)
		USART_Tx_byte(str[i]);
}

