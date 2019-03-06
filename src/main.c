/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <stm32l4xx_ll_rcc.h>
#include <drv_gpio_led.h>
#include "stm32l4xx.h"

#include <stdlib.h>
#include <stdio.h>

#include <drv_usart3.h>
#include <string.h>
#include <drv_mpu.h>

#define FALSE 0
#define TRUE 1

volatile uint8_t BO_MemFault_Flag = TRUE;

volatile unsigned long msTicks;
void setCrystalClock(uint8_t U8_clk_inMHz);

void print_out(char *, uint32_t);
void print_out_hex(char *buffer, uint32_t arg);

void Delay_ms(unsigned long del_count)
{
	del_count *= 4;
	msTicks = del_count;
	while (msTicks != 0)
		;
}

void SysTick_Init(void)
{
	/****************************************
	 *SystemFrequency/1000      1ms         *
	 *SystemFrequency/100000    10us        *
	 *SystemFrequency/1000000   1us         *
	 *****************************************/

	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	/* Tick every 1 ms*/
	while (SysTick_Config(SystemCoreClock / (1000U)) != 0)
	{
	}

}
void setCrystalClock(uint8_t U8_clk_inMHz)
{
	//LL_RCC_MSI_SetCalibTrimming(255);

	uint8_t clk_freq = U8_clk_inMHz;
	switch (clk_freq)
	{

	case 8:

		LL_RCC_MSI_EnableRangeSelection();
		LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_7);
		break;

	case 16:

		LL_RCC_MSI_EnableRangeSelection();
		LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_8);
		break;

	case 24:

		LL_RCC_MSI_EnableRangeSelection();
		LL_RCC_MSI_SetRange(RCC_CR_MSIRANGE_9);
		break;

	case 32:

		LL_RCC_MSI_EnableRangeSelection();
		LL_RCC_MSI_SetRange(RCC_CR_MSIRANGE_10);
		break;

	case 48:

		LL_RCC_MSI_EnableRangeSelection();
		LL_RCC_MSI_SetRange(RCC_CR_MSIRANGE_11);
		break;

	default:
		LL_RCC_MSI_EnableRangeSelection();
		LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);
	}

}

#define DATALEN 15
void print_out(char *buffer, uint32_t arg)
{
	char buff[DATALEN] = { 0 };

	USART_Tx_string(buffer);
	sprintf(buff, ": %lu\n\r", arg);
	USART_Tx_string(buff);

}

void print_out_hex(char *buffer, uint32_t arg)
{
	char buff[DATALEN] = { 0 };

	USART_Tx_string(buffer);
	sprintf(buff, ": 0x%lX\n\r", arg);
	USART_Tx_string(buff);

}
#define ARR_LEN 3
extern char myArray[ARR_LEN]; /* See linker script */

int main(void)
{

	SystemInit();
	myArray[0] = 0;
	myArray[1] = 0;
	myArray[2] = 0;
	SysTick_Init();
	setCrystalClock(16); /*Set System Clock to 16MHz */

	init_led_gpio();

	/* Initialize USART for debugging */
	init_usart_gpio();
	init_usart_peripheral();

	print_out_hex("Address Variable", (uint32_t) &myArray);
	print_out_hex("Address init_led_gpio", (uint32_t) &init_led_gpio);

	configure_MPU();
	init_MPU_NVIC();

	print_out_hex("RCC->PLLCFGR", (uint32_t) RCC->PLLCFGR);

	Delay_ms(500);
	if (BO_MemFault_Flag == TRUE)
		myArray[0] = 2; /* Violate the RO region */

	while (1)
	{
		Delay_ms(500);
	}
}

void SysTick_Handler(void)
{ /* SysTick interrupt Handler. */

	if (msTicks != 0)
		msTicks--; /* See startup file startup_LPC17xx.s for SysTick vector */
}

void MemManage_Handler(void)
{
	BO_MemFault_Flag = TRUE;
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	print_out("SYSReset", 0);
	/* System reset */
	NVIC_SystemReset();
}
