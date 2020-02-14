//PA5
//AHB2
//RCC->AHB2ENR
//GPIOx_MODER
//GPIOx_ODR
#include "stm32l4xx.h"   
void delayMs( int delay); // Device header
int main (void)
{
	RCC->AHB2ENR |=1; //enable GPA clock
	GPIOA->MODER |= 0x400; // 0b 0000 0000 0000 0000 0000 0100 0000 0000
	while(1){
		GPIOA->ODR = 0x20; // 0b 0010 0000
		delayMs(100);
		GPIOA->ODR &= 0x00;
		
	}
}

void delayMs( int delay)
{
	int i;
	for (; delay >0; delay--){
		for (i=0;i <3195;i++);
	}
	
}
