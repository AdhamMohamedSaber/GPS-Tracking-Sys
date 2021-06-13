#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 2
#define M_PI 3.14159265358979323846
#define rad 6371
#include<string.h>

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

void PORTF_Int(void){
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
