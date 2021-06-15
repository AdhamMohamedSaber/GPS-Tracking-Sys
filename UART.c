#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 2
#define M_PI 3.14159265358979323846
#define rad 6371
#include<string.h>


void UART5_Init(void)
	{
    SYSCTL_RCGCUART_R |= 0x20;
//    while((SYSCTL_PRUART_R & 0x20) == 0);
    SYSCTL_RCGCGPIO_R |= 0x10;
		while((SYSCTL_PRGPIO_R & 0x10) == 0){};
		delay_milli(100);
	
//	  GPIO_PORTE_LOCK_R = 0x4C4F434B;    // PE4 RX and PE5 TX
	  GPIO_PORTE_CR_R |= 0xFF;
    GPIO_PORTE_AMSEL_R &= ~0x30;
    GPIO_PORTE_AFSEL_R |= 0x30;
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000;
    GPIO_PORTE_DEN_R |= 0x30;
    
    UART5_CTL_R &= ~0x00000001;
    UART5_IBRD_R = 104;
    UART5_FBRD_R = 11;
	  UART5_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART5_CTL_R |= 0x00000301;
	}

char UART5_InChar(void)																																					// volatile
	{                                              // 7    6    5     4
     while ((UART5_FR_R & 0x00000010) != 0); 		// TXFE RXFF TXFF RXFE
		//PORTF_Int();
		return ((char) (UART5_DR_R & 0xFF));
		
	}

void UART2_Init(void)
	{
    SYSCTL_RCGCUART_R |= 0x04;
    while((SYSCTL_PRUART_R & 0x04) == 0);
    SYSCTL_RCGCGPIO_R |= 0x08;
		while((SYSCTL_PRGPIO_R & 0x08) == 0);
	
	  GPIO_PORTD_LOCK_R = 0x4C4F434B;
	  GPIO_PORTD_CR_R |= 0xC0;
    GPIO_PORTD_AMSEL_R &= ~0xC0;
    GPIO_PORTD_AFSEL_R |= 0xC0;
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
    GPIO_PORTD_DEN_R |= 0xC0;
    
    UART2_CTL_R &= ~0x00000001;
    UART2_IBRD_R = 104;
    UART2_FBRD_R = 11;
	  UART2_LCRH_R = 0x00000070;
    UART2_CTL_R |= 0x00000301;
	}

char UART2_InChar(void)
	{
     while ((UART2_FR_R & 0x00000010) != 0);
		 return ((char) (UART2_DR_R & 0xFF));
	}

void UART2_GetData(char *data, int len)
	{
     char character;
	   int i;
	   for (i = 0; 1 < len; i++) {
		     character = UART2_InChar();
			   data[i] = character;
		 }
}
