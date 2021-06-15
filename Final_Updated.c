#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 200
#define M_PI 3.14159265358979323846
#define rad 6371
#include <string.h>
#include <stdlib.h>

const int len = 478;
char data[len] = {0};
	
void delay_milli(int n)
	{
		int i,j;
		for(i=0;i<n;i++)
			for(j=0;j<3180;j++){}
  }

void delay_micro(int n)
	{
		int i,j;
		for(i=0;i<n;i++)
			for(j=0;j<3;j++){}
	}
void PORTF_Int(void)
	{
    SYSCTL_RCGCGPIO_R |= 0x20;
    while(!(SYSCTL_PRGPIO_R & 0x20));
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x06;
    GPIO_PORTF_DIR_R |= 0x06;
    GPIO_PORTF_DEN_R |= 0x06;
    GPIO_PORTF_AMSEL_R &= ~0x06;
    GPIO_PORTF_AFSEL_R &= ~0x06;
    GPIO_PORTF_PCTL_R &= ~0xFF0;
    GPIO_PORTF_DATA_R |= 0x04;
	}

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
	
//void UART2_Init(void)
//	{
//    SYSCTL_RCGCUART_R |= 0x04;
////    while((SYSCTL_PRUART_R & 0x04) == 0);
//    SYSCTL_RCGCGPIO_R |= 0x08;
//		while((SYSCTL_PRGPIO_R & 0x08) == 0){};
//		delay_milli(100);
//	
//	  GPIO_PORTD_LOCK_R = 0x4C4F434B;
//	  GPIO_PORTD_CR_R |= 0xFF;
//    GPIO_PORTD_AMSEL_R &= ~0xC0;
//    GPIO_PORTD_AFSEL_R |= 0xC0;
//    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
//    GPIO_PORTD_DEN_R |= 0xC0;
//    
//    UART2_CTL_R &= ~0x00000001;
//    UART2_IBRD_R = 104;
//    UART2_FBRD_R = 11;
//	  UART2_LCRH_R = 0x00000070;
//    UART2_CTL_R |= 0x00000301;
//	}
/////////////////////////// CHANGE THE UART NO. OF THE FN BELOW//////////////////////////////
char UART5_InChar(void)
	{                                              // 7    6    5     4
     while ((UART5_FR_R & 0x00000010) != 0); 		// TXFE RXFF TXFF RXFE
		//PORTF_Int();
		return ((char) (UART5_DR_R & 0xFF));
		
	}

//void UART2_GetData(char *data, int len)
//	{
//     char character;
//	   int i;
//	   for (i = 0; i < len; i++) {
//		     character = UART2_InChar();
//			   data[i] = character;
//		
//		 }
//	}

double deg2rad(double);
double rad2deg(double);

double haversine (double lat1, double lon1, double lat2, double lon2, char unit) {
  double theta, dist;
  if ((lat1 == lat2) && (lon1 == lon2)) {
    return 0;
  }
  else {
    theta = lon1 - lon2;
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    switch(unit) {
      case 'M':
        break;
      case 'K':
        dist = dist * 1.609344;
        break;
      case 'N':
        dist = dist * 0.8684;
        break;
    }
    return (dist * 1000);
  }
}

double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

double rad2deg(double radi) {
  return (radi * 180 / M_PI);}
	

void UART0_INT(void){  // WORKING ON PORT A
	SYSCTL_RCGCUART_R |= 0x01;
	SYSCTL_RCGCGPIO_R |= 0x01;
	                        //           9  8             0
	UART0_CTL_R &= ~0x01;  // CTL       TX RX            EN
	// LET THE BR IS 9600/16MHZ
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	UART0_LCRH_R = 0x70;
	//(UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART0_CTL_R |= 0x301;
	
	GPIO_PORTA_AFSEL_R |= 0x03;   
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= 0x03;
	GPIO_PORTA_DIR_R |= 0x01;
	GPIO_PORTA_AMSEL_R &=~ 0x03;
}

char UART0_READING (void){
	
	while ((UART0_FR_R & 0x00000010) != 0);   // WAIT UNTIL RXFE BE 0
	return (char)(UART0_DR_R & 0x000000FF); 
}

void UART0_WRITING (uint8_t data){
	while ((UART0_FR_R & 0x20) != 0);  // WAIT UNTIL TXFF BE 0
	UART0_DR_R = data;
}

void gps_data2(double *lat, double *lon)
{	
	char lat_degree[4];
	char long_degree[4];
	char lat_min[7];
	char long_min[7];
	double lat_degrees ,long_degrees, lat_minutes, long_minutes;
	int x;
//	do{
//	while(UART2_InChar() != '$')
//	while(UART2_InChar() != 'G')
//	while(UART2_InChar() != 'P')
//	while(UART2_InChar() != 'R')
//	while(UART2_InChar() != 'M')
//	while(UART2_InChar() != 'C')
//	while(UART2_InChar() != ',')
//	while(UART2_InChar() != 'A' || UART2_InChar() != 'V');
// }while(UART2_InChar() == 'V');


//	while(UART2_InChar() != ',')
//	while(UART2_InChar() == ',')
//  UART2_GetData(data , 22);
/////////////////////////CHANGE THE UART NO. OF THE FN BELOW//////////////////////////////
while(1){
	if((UART5_FR_R & 0x00000010) != 0)
    {//PORTF_Int();
    if(UART5_InChar() == '$')
      {UART0_WRITING(UART5_InChar());
       if(UART5_InChar() == 'G')
					{
          if(UART5_InChar() == 'P')
            {
             if(UART5_InChar() == 'R')
               {
                if(UART5_InChar() == 'M')
                   {
										if(UART5_InChar() == 'C')
											{
											 if(UART5_InChar() == ',')
												{  
															for(x=0; x<40; x++)
															{ data[x] = UART5_InChar();
																
																if (data[x] == '\r' || data[x] == '\n' || data[x] == 'V'){
																	break;
}}}}}}}}}}}
	
	lat_degree[0] = data[14];
	lat_degree[1] = data[15];
	lat_min[0] = data[16];
	lat_min[1] = data[17];
	lat_min[2] = data[19];
	lat_min[3] = data[20];
	lat_min[4] = data[21];
	lat_min[5] = data[22];

	long_degree[0] = data[26];
	long_degree[1] = data[27];
	long_degree[2] = data[28];
	long_min[0] = data[29];
	long_min[1] = data[30];
	long_min[2] = data[32];
	long_min[3] = data[33];
	long_min[4] = data[34];
	long_min[5] = data[35];
		
		lat_degrees = atof (lat_degree);
		long_degrees = atof (long_degree);
		lat_minutes = atof (lat_min);
		long_minutes = atof (long_min);
		
		*lat = lat_minutes / (1000 * 60);
		*lon = long_minutes / (1000 * 60);
		*lat = *lat + lat_degrees ; 
		*lon = *lon + long_degrees ; 
}


void Lcd_Data(char data)
{
	GPIO_PORTA_DATA_R = 0x20; //RS(A5)(0--command, 1--data), RW(A6), E(A7) = 0
  GPIO_PORTB_DATA_R = data; //display data
  GPIO_PORTA_DATA_R |= 0x80; //Enable = 1, (else=0)
  GPIO_PORTA_DATA_R |= 0;
}


void Lcd_command(char com)
{
	GPIO_PORTA_DATA_R &=0x1F;
  GPIO_PORTA_DATA_R |=0x80;
  GPIO_PORTB_DATA_R =com;
  delay_milli(1);
}

void LCD_INIT(void)
{
    SYSCTL_RCGCGPIO_R|=0x03;
   while ((SYSCTL_PRGPIO_R&0x03 )==0){}
//  LCD_COMMAND
    GPIO_PORTA_DIR_R=0xE0;
    GPIO_PORTA_DATA_R &=0x1F;
    GPIO_PORTA_AMSEL_R=0;
    GPIO_PORTA_AFSEL_R=0;
    GPIO_PORTA_DEN_R=0xE0;
//  LCD_DATA
    GPIO_PORTB_DIR_R=0xFF;         
    GPIO_PORTB_DATA_R =0;
    GPIO_PORTB_AMSEL_R=0;
    GPIO_PORTB_AFSEL_R=0;
    GPIO_PORTB_DEN_R=0xFF;
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
double lon = 0;
double lat = 0;
volatile double prev_lat = 0;
  volatile double prev_lon = 0;
	
  volatile double distance = 0;

int main (void)
{
  char  buf[3];
	int counter;
	int distancex = 0;
	volatile	int i =0 ;
	
	UART0_INT ();
  UART5_Init();
	LCD_INIT();
	
//	distance = haversine(30.10527,30.10522,31.31637,31.31657,'K');
//	delay_milli(100);

	
while(1) {
				// LCD reading

		  gps_data2 (&lat, &lon);
      if (prev_lat != 0 && prev_lon != 0)
				{
					distance += haversine(prev_lat, prev_lon, lat, lon,'K');
				}
//			if (distance >= 100) PORTF_Int(); //Light Red LED ON

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
}
