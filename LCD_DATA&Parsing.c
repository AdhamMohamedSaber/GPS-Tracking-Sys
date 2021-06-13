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
#ifndef STRING_H
#define STRING_H
#endif STRING_H

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


void gps_data (char* data, double* lat, double* lon)
	{
		char cursor = '$';
		int i = 0;
		char lat_degree[4];
		char long_degree[4];
		char lat_min[7];
		char long_min[7];
		
		const char *str ;
		double x ;
		//printf ("lat_degree = %f\n", x);
		const char *str1 ;
		double y ;
		//printf ("long_degree = %f\n", y);
		const char *str2 ;
		double z ;
		//printf ("lat_min = %f\n", z);
		const char *str3;
		double a;
		//printf ("long_min = %f\n", a);
		
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

						long_degree[0] = data[i + 26];
						long_degree[1] = data[i + 27];
						long_degree[2] = data[i + 28];
						long_min[0] = data[i + 29];
						long_min[1] = data[i + 30];
						long_min[2] = data[i + 32];
						long_min[3] = data[i + 33];
						long_min[4] = data[i + 34];
						long_min[5] = data[i + 35];
						break;
					}
					cursor = data[i];
					i++;
			}
		str = lat_degree;
		x = strtod (str, NULL);
		//printf ("lat_degree = %f\n", x);
		str1 = long_degree;
		y = strtod (str1, NULL);
		//printf ("long_degree = %f\n", y);
		str2 = lat_min;
		z = strtod (str2, NULL);
		//printf ("lat_min = %f\n", z);
		str3 = long_min;
		a = strtod (str3, NULL);
		//printf ("long_min = %f\n", a);
  
		*lat = z / (1000 * 60);
		*lon = a / (1000 * 60);
		*lat = *lat + x ; //may cause error (try removing *)
		*lon = *lon + y ; 
		//printf("lat is %f\n ", lat);
		//printf("lon is %f\n ", lon);
			}
