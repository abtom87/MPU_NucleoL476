/*
 * drv_mpu.h
 *
 *  Created on: Sep 15, 2018
 *      Author: abel
 */

#ifndef DRV_MPU_H_
#define DRV_MPU_H_

#include <stm32l4xx_hal.h>
#include <stm32l4xx_hal_cortex.h>

#define IRQ_Type MemoryManagement_IRQn



void configure_MPU(void);
void init_MPU_NVIC(void);

#endif /* DRV_MPU_H_ */
