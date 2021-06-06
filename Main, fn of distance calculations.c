#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 2
#define M_PI 3.14159265358979323846
#define rad 6371
#include<string.h>
//#include <cmath>

//uint16_t total_Distance;
//uint32_t result;

//unsigned char LCD_word[]={'M','A','X','E','R','I','E','N','C','E'};

	 
void SystemInit(void);

/* The Main includes the calling of all the functions plus the printing on the LCD. 
Also including part of distance calculations and the function of turning the LED if the distance was greater than or equal 100.*/

int main (void){
		double prev_lat = 0;
    double prev_lon = 0;
    double lon[ ] = {31.278169737933965, 31.28100215080061};
    double lat[ ] = {30.062523380301965, 30.063484433684938};
    double distance = 0;
		char lcd_chars[50];
		int i =0 ;
		
    PORTF_Int();
		PORTA_INIT();
		PORTB_INIT();
		
		UART0_INT();
		//UART0_WRITING();
		UART0_READING();            // THAT WILL BE DETERMINE ACCORDING TO THE NEXT PHASE 
    
		
		//sendString();
		
		// Distance code
		 
		sprintf(lcd_chars,"%d", (int) distance);
		
    for(i=0; i<no_of_points; i++){
        if (prev_lat != 0 && prev_lon != 0){
            distance += haversine(prev_lat, prev_lon, lat[i], lon[i]);
            }
				
				if (distance >= 100)
            GPIO_PORTF_DATA_R = 0X20;
        
        prev_lat = lat[i];
        prev_lon = lon[i];
        
        printf("%f m. \n", distance);
    }
		
		// LCD reading
		
		Lcd_Data('T');
		delay_milli(1);
		Lcd_Data('O');
		delay_milli(1);
		Lcd_Data('T');
		delay_milli(1);
		Lcd_Data('A');
		delay_milli(1);
		Lcd_Data('L');
		delay_milli(1);
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
		Lcd_Data(lcd_chars[0]);
		delay_milli(1);
		Lcd_Data(lcd_chars[1]);
		delay_milli(1);
		Lcd_Data(lcd_chars[2]);
		delay_milli(1);
		Lcd_Data(' ');
		
		delay_milli(500);
		
		return 0;
}
