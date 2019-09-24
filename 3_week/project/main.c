#include <time.h>

#define RCC_APB2_ENR *(volatile unsigned int *)0x40021018

#define GPIOD_CRL *(volatile unsigned int *)0x40011400
#define GPIOD_CRH *(volatile unsigned int *)0x40011404 // switch 8~15
#define GPIOD_BSRR *(volatile unsigned int *)0x40011410
#define GPIOD_BRR *(volatile unsigned int *)0x40011414
#define GPIOD_IDR *(volatile unsigned int *)0x40011408

#define GPIOB_CRL *(volatile unsigned int *)0x40010C00
#define GPIOB_BSRR *(volatile unsigned int *)0x40010C10
#define GPIOB_BRR *(volatile unsigned int *)0x40010C14
#define GPIOB_IDR *(volatile unsigned int *)0x40010C08

void delay(int n)
{
	time_t current = clock();
	while (clock() - current < n)
		;
}

int main()
{
	RCC_APB2_ENR = 0x3E; // clock enable

	GPIOD_CRL = 0x44444444; // GPIOD reset
	GPIOD_CRH = 0x44444444;
	GPIOB_CRL = 0x44444444;

	GPIOD_CRL = 0x10011100; // LED output
	GPIOD_CRH = 0x00044000; // button 1~2 input
	GPIOB_CRL = 0x00000000; // button sel input

	GPIOD_BSRR = 0x00000000; // bit reset

	//GPIOD_BSRR |=  0x9C;			// GPIOD_2 set

	//while(1);
	//GPIOD_BSRR =  0x0;

	//GPIOD_BSRR |= 0x9C;     //10011100

	int i = 0;

	while (1)
	{

		if (~GPIOD_IDR & 0x800)
			i = 1;

		if (~GPIOD_IDR & 0x1000)
			i = 2;

		if (~GPIOB_IDR & 0x100)
			i = 0;

		switch (i)
		{
		case 1:
			GPIOD_BRR |= 0x9C;
			GPIOD_BSRR |= 0x08;
			delay(10);
			GPIOD_BRR |= 0x9C;
			GPIOD_BSRR |= 0x04;
			delay(10);
			break;

		case 2:
			GPIOD_BRR |= 0x9C;
			GPIOD_BSRR |= 0x80;
			delay(10);
			GPIOD_BRR |= 0x9C;
			GPIOD_BSRR |= 0x10;
			delay(10);
			break;

		case 0:
			GPIOD_BRR |= 0xFC;
			break;
		}
	}
}
