/*
 * drv_mpu.c
 *
 *  Created on: Sep 15, 2018
 *      Author: abel
 */

#include "drv_mpu.h"


void configure_MPU(void)
{
	MPU_Region_InitTypeDef MPU_initStruct;
	HAL_MPU_Disable();
	MPU_initStruct.BaseAddress      = 0x20005500; /* Address where the arry is located */
	MPU_initStruct.AccessPermission = MPU_REGION_PRIV_RO;
	MPU_initStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;
	MPU_initStruct.Enable           = MPU_REGION_ENABLE;
	MPU_initStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_initStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;
	MPU_initStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
	MPU_initStruct.Number           = MPU_REGION_NUMBER0;
	MPU_initStruct.Size             = MPU_REGION_SIZE_32B;
	MPU_initStruct.TypeExtField     = MPU_TEX_LEVEL0 ;
	MPU_initStruct.SubRegionDisable = 0x00;
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
	HAL_MPU_ConfigRegion(&MPU_initStruct);

}


void init_MPU_NVIC(void)
{
	NVIC_SetPendingIRQ(IRQ_Type);
	NVIC_SetPriority(IRQ_Type,0);
	NVIC_ClearPendingIRQ(IRQ_Type);

}
