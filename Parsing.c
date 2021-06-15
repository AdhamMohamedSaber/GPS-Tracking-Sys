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
