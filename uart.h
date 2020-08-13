/* 
 * File:   uart.h
 * Author: joship
 *
 * Created on August 1, 2020, 1:15 PM
 */
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <xc.h>
#include <string.h>

#ifndef UART_H
#define	UART_H
//
//#ifdef	__cplusplus
//extern "C" {
//#endif
//
//
//
//
//#ifdef	__cplusplus
//}
//#endif

void UARTInit(const uint32_t baud_rate,const  uint8_t BRGH);
void UARTSendChar(const char c);
void UARTSendString(const  char* str, const uint8_t max_length);
    
#endif	/* UART_H */

