// flash load "C:\Users\Team02\Desktop\Thrus\flashclear.axf"
// flash load "C:\Users\Team02\Desktop\Thrus\W4\Debug\W4.axf"

//#include <time.h>

#define RCC_APB2_ENR *(volatile unsigned int*)0x40021018

#define GPIOD_CRL *(volatile unsigned int*)0x40011400
#define GPIOD_CRH *(volatile unsigned int*)0x40011404    // switch 8~15
#define GPIOD_BSRR *(volatile unsigned int*) 0x40011410
#define GPIOD_BRR *(volatile unsigned int*) 0x40011414
#define GPIOD_IDR *(volatile unsigned int*) 0x40011408

#define GPIOB_CRL *(volatile unsigned int*)0x40010C00
#define GPIOB_BSRR *(volatile unsigned int*) 0x40010C10
#define GPIOB_BRR *(volatile unsigned int*) 0x40010C14
#define GPIOB_IDR *(volatile unsigned int*) 0x40010C08

void delay(int n){
	int i;
//	time_t current = clock();
//	while(clock() - current < n);
	for (i = 0;i < 1000000;i++);
}



int main(){
	RCC_APB2_ENR = 0x3E;		// clock enable

	GPIOD_CRL = 0x44444444;		// GPIOD reset
	GPIOD_CRH = 0x44444444;
	GPIOB_CRL = 0x44444444;


	GPIOD_CRL = 0x00010000;     // LED output
	GPIOD_CRH = 0x00004000;     // button 1 input
	GPIOB_CRL = 0x00000000;     // button sel input

	GPIOD_BSRR = 0x00000000;    // bit reset

	int prev = 0;
	int curr = 0;
	int on = 0;

	while(1){

		if(~GPIOD_IDR & 0x800){
			curr = 1;
			delay(10);
		} else {
			curr = 0;
			delay(10);
		}

		if(prev == 0 && curr == 1){
			if(on == 0){
				GPIOD_BSRR |= 0x10;
				on = 1;
			} else {
				GPIOD_BRR |= 0x10;
				on = 0;
			}
		}

		prev = curr;
	}
}

