#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 2
#define M_PI 3.14159265358979323846
#define rad 6371
#include<string.h>
//#include <cmath>

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
	 
void SystemInit(void);

/* The Main includes the calling of all the functions plus the printing on the LCD. 
Also including part of distance calculations and the function of turning the LED if the distance was greater than or equal 100.*/

int main (void)
{
	
	double prev_lat = 0;
  double prev_lon = 0;
	double lon = 0;
	double lat = 0;
  double distance = 112;
  char  buf[3];
	int distancex = 0;
	int i =0 ;
	
  UART2_Init();
	LCD_INIT();

	
	
	
 while(1) {
				// LCD reading

			UART2_GetData(data, len); //comment
				delay_milli(10);
		  gps_data (data, &lat, &lon);
      if (prev_lat != 0 && prev_lon != 0)
				{
					distance += haversine(prev_lat, prev_lon, lat, lon);
				}
			if (distance >= 100) PORTF_Int(); //Light Red LED ON

      prev_lat = lat;
      prev_lon = lon;

      
      distancex = (int) distance ;
			snprintf(buf, 4, "%d", distancex);
			
				Lcd_command (0x01); //Clear display
			
				Lcd_Data(' ');
				delay_milli(1);
				Lcd_Data('D');
				delay_milli(1);
				Lcd_Data('I');
				delay_milli(1);
				Lcd_Data('S');
				delay_milli(1);
				Lcd_Data('T');
				delay_milli(1);
				Lcd_Data('.');
				delay_milli(5);
				delay_milli(1);
				Lcd_Data(' ');
				delay_milli(1);
				Lcd_Data('=');
				delay_milli(1);
			
		
			Lcd_Data(buf[0]);
			delay_milli(1);
			Lcd_Data(buf[1]);
			delay_milli(1);
			Lcd_Data(buf[2]);
			delay_milli(1);
			Lcd_Data('m');
			delay_milli(1);
			Lcd_Data(' ');
			delay_milli(1);
			delay_milli(500);
		}
	
}

