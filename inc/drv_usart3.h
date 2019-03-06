/*
 * drv_usart.h
 *
 *  Created on: Sep 4, 2018
 *      Author: abel
 */

#ifndef DRV_USART3_H_
#define DRV_USART3_H_

#include "stdint.h"

void init_usart_gpio(void);
void init_usart_peripheral(void);
void USART_Tx_byte(uint8_t byte);

void USART_Tx_string(char* str);




#endif /* DRV_USART3_H_ */
