#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define no_of_points 200
#define M_PI 3.14159265358979323846
#define rad 6371
 
double lon = 0;
double lat = 0;
volatile double prev_lat = 0;
  volatile double prev_lon = 0;
	
  volatile double distance = 0;

int main (void)
{
	bool test_me = true;
  char  buf[3];
	int counter;
	int distancex = 0;
	volatile	int i =0 ;
	
  UART5_Init();
	LCD_INIT();
	

	delay_milli(4000);

	
while(1) {
	
 test_me = check_me_again();
	
if (test_me == true)
{
		  gps_data2 (&lat, &lon);
      if (prev_lat != 0 && prev_lon != 0)
				{
					distance += haversine(prev_lat, prev_lon, lat, lon,'K');
				}
			if (distance >= 100) PORTF_Int(); //Light Blue LED ON

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
			
	for(counter= 0; counter < 3; counter++){		
			Lcd_Data(buf[counter]);
			delay_milli(1);
	}
			Lcd_Data('m');
			delay_milli(1);
			Lcd_Data('.');
			delay_milli(1);
			Lcd_Data('.');
			delay_milli(1);
			delay_milli(500);
	}
else
		continue;	
}
}
