bool check_me_again () {
	char me_again = UART5_InChar();
	if((UART5_FR_R & 0x00000010) != 0)
    {//PORTF_Int();
        if(me_again == '$')
      {me_again = UART5_InChar();
				
       if(me_again == 'G')
					{me_again = UART5_InChar();

						
          if(me_again == 'P')
            {me_again = UART5_InChar();
							
             if(me_again == 'R')
               {me_again = UART5_InChar();
								 
                if(me_again == 'M')
                   {me_again = UART5_InChar();
										 
										if(me_again == 'C')
											{me_again = UART5_InChar();
												
											 if(me_again == ','){
												 me_again = UART5_InChar();
											 return true;}}}}}}}}
											 
		return false;
}

void gps_data2(double *lat, double *lon)
{	
	 char lat_degree[4];
	 char long_degree[4];
	 char lat_min[7];
	 char long_min[7];
	char me_again = UART5_InChar();
	volatile double lat_degrees ,long_degrees, lat_minutes, long_minutes;
	volatile int x;

	
	char noneed[12];

	
	noneed[0] = UART5_InChar();
	noneed[1] = UART5_InChar();
	noneed[2] = UART5_InChar();
	noneed[3] = UART5_InChar();
	noneed[4] = UART5_InChar();
	noneed[5] = UART5_InChar();
	noneed[6] = UART5_InChar();
	noneed[7] = UART5_InChar();
	noneed[8] = UART5_InChar();
	noneed[9] = UART5_InChar();
	noneed[10] = UART5_InChar();
	noneed[11] = UART5_InChar();
	//if (noneed [11] == 'A' || noneed[11] == 'V' || noneed[11] == ' ' || noneed[11] == ',') PORTF_Int();
	 
//	if (UART5_InChar() /*me_again*/ == 'A'){
//		//me_again = UART5_InChar();
//		PORTF_Int();
//		if (UART5_InChar() == ','){
				for(x=1; x<40; x++)
					{ 
						data[x] = UART5_InChar();
						}
	//PORTF_Int();
	lat_degree[0] = data[3];
	lat_degree[1] = data[4];
	lat_min[0] = data[5];
	lat_min[1] = data[6];
	lat_min[2] = data[8];
	lat_min[3] = data[9];
	lat_min[4] = data[10];
	lat_min[5] = data[11];

	long_degree[0] = data[15];
	long_degree[1] = data[16];
	long_degree[2] = data[17];
	long_min[0] = data[18];
	long_min[1] = data[19];
	long_min[2] = data[21];
	long_min[3] = data[22];
	long_min[4] = data[23];
	long_min[5] = data[24];
	
		lat_degrees = atof (lat_degree);
		long_degrees = atof (long_degree);
		lat_minutes = atof (lat_min);
		long_minutes = atof (long_min);
		
		*lat = lat_minutes / (1000 * 60);
		*lon = long_minutes / (1000 * 60);
		*lat = *lat + lat_degrees ; 
		*lon = *lon + long_degrees ; 
}
