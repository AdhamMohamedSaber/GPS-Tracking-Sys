#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 2
#define M_PI 3.14159265358979323846
#define rad 6371
#include<string.h>

//  LCD_DATA
void Lcd_Data(char data)
{
    GPIO_PORTA_DATA_R = 0x20; //RS(A5)(0--command, 1--data), RW(A6), E(A7) = 0
    GPIO_PORTB_DATA_R = data; //display data
    GPIO_PORTA_DATA_R |= 0x80; //Enable = 1, (else=0)
    GPIO_PORTA_DATA_R |= 0;
}

void PORTB_INIT (void){
		SYSCTL_RCGCGPIO_R|=0x03;
    while ((SYSCTL_PRGPIO_R&0x03 )==0);
		GPIO_PORTB_DIR_R = 0xFF;
    GPIO_PORTB_DATA_R = 0;
    GPIO_PORTB_AMSEL_R = 0;
    GPIO_PORTB_CR_R |= 0xFF;
    GPIO_PORTB_AFSEL_R = 0;
    GPIO_PORTB_PUR_R = 0x00;
    GPIO_PORTB_DEN_R = 0xFF;
}