#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 2
#define M_PI 3.14159265358979323846
#define rad 6371
#include <string.h>
#include <stdlib.h>
//#include <cmath>

//uint16_t total_Distance;
//uint32_t result;

//unsigned char LCD_word[]={'M','A','X','E','R','I','E','N','C','E'};

void delay_milli(int n){
		int i,j;
		for(i=0;i<n;i++)
			for(j=0;j<3180;j++){}
}

void delay_micro(int n){
		int i,j;
		for(i=0;i<n;i++)
			for(j=0;j<3;j++){}
}
void PORTF_Int(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20;
    while(!(SYSCTL_PRGPIO_R & 0x20));
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x02;
    GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DEN_R |= 0x02;
    GPIO_PORTF_AMSEL_R &= ~0x02;
    GPIO_PORTF_AFSEL_R &= ~0x02;
    GPIO_PORTF_PCTL_R &= ~0xF0;
    GPIO_PORTF_DATA_R |= 0x02;
}

//void SystemInit(void);

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

static double haversine(double lat1, double lon1, double lat2, double lon2)
    {
				double a, c, z;
        // distance between latitudes
        // and longitudes
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;
 
        // convert to radians
        lat1 = (lat1) * M_PI / 180.0;
        lat2 = (lat2) * M_PI / 180.0;
 
        // apply formulae
        a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
        c = 2 * asin(sqrt(a));
        
				z = rad* c* pow(10,3);
				
				return z;
    }


void gps_data (char * data, double * lat, double * lon){
    
  //double lon, lat;
  char cursor = '$';
  int i = 0;
  char lat_degree[4];
  char long_degree[4];
  char lat_min[7];
  char long_min[7];

  while (1)
    {
      if (cursor == 'C')
	{
	  lat_degree[0] = data[i + 14];
	  lat_degree[1] = data[i + 15];
	  lat_min[0] = data[i + 16];
	  lat_min[1] = data[i + 17];
	  lat_min[2] = data[i + 19];
	  lat_min[3] = data[i + 20];
	  lat_min[4] = data[i + 21];
	  lat_min[5] = data[i + 22];
// 	  lat_min[6] = data[i + 23];

	  long_degree[0] = data[i + 26];
	  long_degree[1] = data[i + 27];
	  long_degree[2] = data[i + 28];
	  long_min[0] = data[i + 29];
	  long_min[1] = data[i + 30];
	  long_min[2] = data[i + 32];
	  long_min[3] = data[i + 33];
	  long_min[4] = data[i + 34];
	  long_min[5] = data[i + 35];
// 	  long_min[6] = data[i + 36];

	  break;
	}
      cursor = data[i];
      i++;
    }

  const char *str = lat_degree;
  double x = strtod (str, NULL);
  //printf ("lat_degree = %f\n", x);
  const char *str1 = long_degree;
  double y = strtod (str1, NULL);
  //printf ("long_degree = %f\n", y);
  const char *str2 = lat_min;
  double z = strtod (str2, NULL);
  //printf ("lat_min = %f\n", z);
  const char *str3 = long_min;
  double a = strtod (str3, NULL);
  //printf ("long_min = %f\n", a);
  
  *lat = z / (1000 * 60);
  *lon = a / (1000 * 60);
  *lat = *lat + x ; //may cause error (try removing *)
  *lon = *lon + y ; 
  //printf("lat is %f\n ", lat);
  //printf("lon is %f\n ", lon);
}
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



int main (void){
	const int len = 478;
  char data[len] = {0};
	double prev_lat = 0;
  double prev_lon = 0;
	double lon = 0;
	double lat = 0;
  double distance = 0;
  char  buf[3];
	int distancex = 0;
	int i =0 ;
	
  UART0_Init();
  UART2_Init();
	
  while(1) {
// LCD reading

		for(i=0; i < no_of_points; i++){
			UART2_GetData(data, len); //comment
		  gps_data (data, &lat, &lon);
       if (prev_lat != 0 && prev_lon != 0){
            distance += haversine(prev_lat, prev_lon, lat, lon);
				}
			 if (distance >= 100) GPIO_PORTF_DATA_R = 0X20;

        prev_lat = lat;
        prev_lon = lon;

        //printf("%f m. \n", distance);
        distancex = (int) distance ;
				snprintf(buf, 4, "%d", distancex);
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
		
		Lcd_Data(buf[0]);
		delay_milli(1);
		Lcd_Data(buf[1]);
		delay_milli(1);
		Lcd_Data(buf[2]);
		delay_milli(1);
		delay_milli(500);
    }
	}
	return 0;
}
