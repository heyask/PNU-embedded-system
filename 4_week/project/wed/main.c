// flash load "C:\Users\Team01\Desktop\Project1\wed\flashclear.axf"
// flash load "C:\Users\Team01\Desktop\Project1\wed\Debug\wed.axf"

#define RCC_APB2_ENR *(volatile unsigned int *)0x40021018 // GPIO ���� Ŭ�� ��� ��������

#define GPIOD_CRL *(volatile unsigned int *)0x40011400 // GPIOD 0~7��Ʈ�� ���� ����� ��� ����(GD2,3,4,7)
#define GPIOD_CRH *(volatile unsigned int *)0x40011404 // GPIOD 8~15��Ʈ�� ���� ����� ��� ����(GD11,12)
#define GPIOD_BSRR *(volatile unsigned int *)0x40011410 // GPIOD�� ���� Bit Set, Reset Write
#define GPIOD_BRR *(volatile unsigned int *)0x40011414 // GPIOD�� ���� Bit Reset ����
#define GPIOD_IDR *(volatile unsigned int *)0x40011408 // GPIOD�� ���� LOW, HIGH�� Read

#define GPIOC_CRL *(volatile unsigned int *)0x40011000 // GPIOC 0~7��Ʈ�� ���� ����� ��� ����
#define GPIOC_CRH *(volatile unsigned int *)0x40011004 // GPIOC 8~15��Ʈ�� ���� ����� ��� ����(GC8,9)
#define GPIOC_BSRR *(volatile unsigned int *)0x40011010 // GPIOC�� ���� Bit Set, Reset Write
#define GPIOC_BRR *(volatile unsigned int *)0x40011014 // GPIOC�� ���� Bit Reset ����
#define GPIOC_IDR *(volatile unsigned int *)0x40011008 // GPIOC�� ���� LOW, HIGH�� Read

#define GPIOB_CRL *(volatile unsigned int *)0x40010C00 // GPIOB 0~7��Ʈ�� ���� ����� ��� ����(GB8)
#define GPIOB_BSRR *(volatile unsigned int *)0x40010C10 // GPIOB�� ���� Bit Set, Reset Write
#define GPIOB_BRR *(volatile unsigned int *)0x40010C14 // GPIOB�� ���� Bit Reset ����
#define GPIOB_IDR *(volatile unsigned int *)0x40010C08 // GPIOB�� ���� LOW, HIGH�� Read

void delay(int n) // ���� �ð���ŭ ��ٸ��� �Լ�, n*0.1��
{
	int i;
	for (i = 0;i < 500000 * n; i++);
}

int main()
{
	RCC_APB2_ENR = 0x3E; // GPIOB,D ���� Ŭ�� ����� ������

	GPIOD_CRL = 0x44444444; // GPIOD reset
	GPIOD_CRH = 0x44444444;
	GPIOC_CRL = 0x44444444; // GPIOC reset
	GPIOC_CRH = 0x44444444;
	GPIOB_CRL = 0x44444444; // GPIOB reset

	GPIOD_CRL = 0x10011100; // LED �κ��� GPIOD2,3,4,7�� output���� ������
	GPIOD_CRH = 0x00044000; // button �κ��� GPIOD11~12�� input���� ������
	GPIOC_CRL = 0x00444400; // button ���� �κ��� GPIOC3~6�� input���� ������
	GPIOC_CRH = 0x00000011; // ������ ��� ��� �κ��� GPIOC8~9�� output���� ������

	GPIOD_BSRR = 0x00000000; // GPIOB bit reset
	GPIOC_BSRR |= 0x300; // GPIOC Relay reset

	//GPIOD_BSRR |=  0x9C; // �����ڵ� : GPIOD2,3,4,7 set
	//GPIOD_BSRR =  0x0; // �����ڵ� : �ƹ��ϵ� �Ͼ�� ����

	int i = 0; // ���� �������� �����ִ����� �����ϴ� ����
	int j = -1; // ���� � ������ ���ư������� �����ϴ� ����

	while (1) // ��� �ݺ�
	{
		int prev = j; // ���� ������ ���ư������� ������

		if(~GPIOC_IDR & 0x20) // ���̽�ƽ�� ���� ������ ��
			j = 1; 
		else if(~GPIOC_IDR & 0x8) // ���̽�ƽ�� ���� ������ ��
			j = 2;
		else if(~GPIOC_IDR & 0x10) // ���̽�ƽ�� ������ ������ ��
			j = 3;
		else // ���̽�ƽ�� �������� �ʾ��� ��
			j = -1;

		if(prev != j){ // ���� ���̽�ƽ ����� ���ؼ� �ٲ� ���¸� ������ ��� ��Ʈ ����
			GPIOC_BSRR |= 0x300; // GPIOC Relay set (��� ����)
			if(j == 1)
				GPIOC_BRR |= 0x300; // GPIOC Relay1,2 reset
			if(j == 2)
				GPIOC_BRR |= 0x100; // GPIOC Relay1 reset
			if(j == 3)
				GPIOC_BRR |= 0x200; // GPIOC Relay2 reset
		}

		if (~GPIOD_IDR & 0x800) // ���� ��ư�� ������ ��, GPIOD11�� 0�� ��
			i = 1; // ���¸� 1�� ����

		if (~GPIOD_IDR & 0x1000) // ������ ��ư�� ������ ��, GPIOD12�� 0�� ��
			i = 2; // ���¸� 2�� ����

		if (~GPIOB_IDR & 0x100) // ���̽�ƽ�� ������ ��, GPIOB8�� 0�� ��
			i = 0; // ���¸� 0���� ����

		switch (i) // ���� ���¿� ���� ���� ����
		{
		case 1: // ���� ��ư�� ������ ��
			GPIOD_BRR |= 0x9C; // GPIOD LED reset
			GPIOD_BSRR |= 0x08; // GPIOD3 set
			delay(1); // ��� ��ٸ�
			GPIOD_BRR |= 0x9C; // GPIOD LED reset
			GPIOD_BSRR |= 0x04; // GPIO2 set
			delay(1); // ��� ��ٸ�
			break;

		case 2:
			GPIOD_BRR |= 0x9C; // GPIOD LED reset
			GPIOD_BSRR |= 0x80; // GPIOD7 set
			delay(1); // ��� ��ٸ�
			GPIOD_BRR |= 0x9C; // GPIOD LED reset
			GPIOD_BSRR |= 0x10; // GPIO4 set
			delay(1); // ��� ��ٸ�
			break;

		case 0:
			GPIOD_BRR |= 0x9C; // GPIOD LED reset
			break;
		}


	}
}