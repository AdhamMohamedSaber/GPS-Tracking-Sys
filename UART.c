#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 2
#define M_PI 3.14159265358979323846
#define rad 6371
#include<string.h>

void UART0_INT(void){  // WORKING ON PORT A
	SYSCTL_RCGCUART_R |= 0x01;
	SYSCTL_RCGCGPIO_R |= 0x01;
	
	UART0_CTL_R &= ~0x01;
	// LET THE BR IS 9600/16MHZ
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	UART0_LCRH_R = 0x70;
	//(UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART0_CTL_R |= 0x301;
	
	GPIO_PORTA_AFSEL_R |= 0x03;   
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= 0x03;
	GPIO_PORTA_AMSEL_R &=~ 0x03;
}

uint8_t UART0_READING (void){
	while ((UART0_FR_R & 0x10) != 0);   // WAIT UNTIL RXFE BE 0
	return (uint8_t)(UART0_DR_R & 0xFF); 
}

void UART0_WRITING (uint8_t data){
	while ((UART0_FR_R & 0x20) != 0);  // WAIT UNTIL TXFF BE 0
	UART0_DR_R = data;
}