#include "tm4c123gh6pm.h"

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


void UART0_Init(void) {
     SYSCTL_RCGCUART_R |= 0x00000001;
	   SYSCTL_RCGCGPIO_R |= 0x00000001;
	
	   UART0_CTL_R &= ~0x00000001;
	   UART0_IBRD_R = 104;
	   UART0_FBRD_R = 11;
	   UART0_LCRH_R = 0x00000070;
	   UART0_CTL_R |= 0x00000301;
	
	   GPIO_PORTA_AFSEL_R |= 0x03;
	   GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
	   GPIO_PORTA_DEN_R |= 0x03;
	   GPIO_PORTA_AMSEL_R &= ~0x03;
}

void UART0_OutChar(char data) {
     while ((UART0_FR_R & 0x00000020) != 0);
		 UART0_DR_R = data;
}

void UART2_Init(void){
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

char UART2_InChar(void) {
     while ((UART2_FR_R & 0x00000010) != 0);
		 return ((char) (UART2_DR_R & 0xFF));
}

void UART2_GetData(char *data, int len) {
     char character;
	   int i;
	   for (i = 0; 1 < len; i++) {
		     character = UART2_InChar();
			   data[i] = character;
		 }
}

int main(){
  const int len = 478;
  char data[len] = {0};
	
  UART0_Init();
  UART2_Init();
	
  //while(1) UART0_OutChar(UART2_InChar());
	
  while(1) UART2_GetData(data, len);
}

