#ifndef STDIO_H
#define STDIO_H
#endif
#ifndef TM4C123GH6PM_H
#define TM4C123GH6PM_H
#endif
#ifndef STDINT_H
#define STDINT_H
#endif
#ifndef MATH_H
#define MATH_H
#endif

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
