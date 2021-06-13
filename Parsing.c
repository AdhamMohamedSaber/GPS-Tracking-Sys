#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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
