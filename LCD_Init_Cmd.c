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

void Lcd_command(char com)
{
        GPIO_PORTA_DATA_R &=0x1F;
        GPIO_PORTA_DATA_R |=0x80;
        GPIO_PORTB_DATA_R =com;
        delay_milli(1);
}

void PORTA_INIT(void)
{
    SYSCTL_RCGCGPIO_R|=0x03;
    while ((SYSCTL_PRGPIO_R&0x03 )==0);

	//  LCD_COMMAND
    GPIO_PORTA_DIR_R=0xE0;
    GPIO_PORTA_DATA_R &=0x1F;
    GPIO_PORTA_AMSEL_R=0;
    GPIO_PORTA_CR_R |=0xE0;
    GPIO_PORTA_AFSEL_R=0;
    GPIO_PORTA_PUR_R=0x00;
    GPIO_PORTA_DEN_R=0xE0;

	// LCD_COMMAND_init
    Lcd_command(0x30);
    delay_micro(40);
    Lcd_command(0x01);
    delay_micro(1640);
    Lcd_command(0x80);
    delay_micro(40);
    Lcd_command(0x0F);
    delay_micro(40);
    Lcd_command(0x06);
    delay_micro(40);
    Lcd_command(0x38);
    delay_micro(40);
}
