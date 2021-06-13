unsigned char data[] =
  "$GPGGA,021514.000,2232.1799,N,11401.1823,E,1,6,1.25,84.0,M,-2.2,M,,*74$GPGLL,2232.1799,N,11401.1824,E,021513.000,A,A*50$GPGSA,A,3,26,05,18,15,27,29,,,,,,,1.52,1.25,0.87*0F$GPGSV,3,1,12,15,79,333,42,42,50,127,,29,45,263,44,02,36,124,30*7E$GPGSV,3,2,12,26,36,226,34,05,35,046,22,27,33,161,29,21,16,319,*7D$GPGSV,3,3,12,10,15,066,31,18,14,285,45,24,12,319,15,08,09,047,18*7E$GPRMC,023345.000,A,2232.1767,N,11411.1953,E,0.18,151.55,100410,,,A*6B$GPVTG,148.81,T,,M,0.13,N,0.24,K,A*3D";

void gps_data (){
    
  double lon, lat;
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
  
  lat = z / (1000 * 60);
  lon = a / (1000 * 60);
  lat = lat + x ;
  lon = lon + y ;
  //printf("lat is %f\n ", lat);
  //printf("lon is %f\n ", lon);
}

/*int main ()
{
  gps_data ();
}*/
