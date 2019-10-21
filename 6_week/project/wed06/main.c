#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "core_cm3.h"

int statusCode = 3;

void RCC_Configure() {

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/*TODO : APB2PeriphClockEnable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}
void GPIO_Configure() {

	GPIO_InitTypeDef GPIO_InitStructure, GPIO_InitStructure2, GPIO_InitStructure3, GPIO_InitStructure4;
	// LED1234 -> PD2347
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/*TODO: USART1, JoyStick Config */
	// Á¶ÀÌ½ºÆ½ Left, Right -> PC3, PC4
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure2.GPIO_Pin = (GPIO_Pin_3 | GPIO_Pin_4);
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure2);

	// Á¶ÀÌ½ºÆ½ Select -> PB8
	GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure3.GPIO_Pin = (GPIO_Pin_8);
	GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure3);

	// USER S1 -> PD11
	GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure4.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure4);

	// USART RX TX Æ÷Æ® EN
	// TX PA9 OUT
	GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure4.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure4);
	// RX PA10 IN
	GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure4.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure4);
	/*TODO: GPIO EXTILineConfig*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource11);
}

void USART_Configure() {
	/*TODO: USART1 configuration*/
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;

	/*TODO: USART1 cmd ENABLE*/
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	/*TODO: USART1 IT Config*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void EXTI_Configure() {
	/*TODO: EXTI configuration [ mode interrupt ] [Trigger_falling] */

	EXTI_InitTypeDef USER_S1, LEFT, RIGHT, SELECT;
	LEFT.EXTI_Line = EXTI_Line3;
	LEFT.EXTI_LineCmd = ENABLE;
	LEFT.EXTI_Mode = EXTI_Mode_Interrupt;
	LEFT.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&LEFT);

	RIGHT.EXTI_Line = EXTI_Line4;
	RIGHT.EXTI_LineCmd = ENABLE;
	RIGHT.EXTI_Mode = EXTI_Mode_Interrupt;
	RIGHT.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&RIGHT);

	SELECT.EXTI_Line = EXTI_Line8;
	SELECT.EXTI_LineCmd = ENABLE;
	SELECT.EXTI_Mode = EXTI_Mode_Interrupt;
	SELECT.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&SELECT);

	USER_S1.EXTI_Line = EXTI_Line11;
	USER_S1.EXTI_LineCmd = ENABLE;
	USER_S1.EXTI_Mode = EXTI_Mode_Interrupt;
	USER_S1.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&USER_S1);
}

void NVIC_Configure() {
	/*TODO: NVIC_configuration */
	NVIC_InitTypeDef USER_S1, LEFT, RIGHT, SELECT, USART;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	LEFT.NVIC_IRQChannel = EXTI3_IRQn;
	LEFT.NVIC_IRQChannelPreemptionPriority = 0x00;
	LEFT.NVIC_IRQChannelSubPriority = 0x00;
	LEFT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&LEFT);

	RIGHT.NVIC_IRQChannel = EXTI4_IRQn;
	RIGHT.NVIC_IRQChannelPreemptionPriority = 0x01;
	RIGHT.NVIC_IRQChannelSubPriority = 0x00;
	RIGHT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&RIGHT);

	SELECT.NVIC_IRQChannel = EXTI9_5_IRQn;
	SELECT.NVIC_IRQChannelPreemptionPriority = 0x02;
	SELECT.NVIC_IRQChannelSubPriority = 0x00;
	SELECT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&SELECT);

	USER_S1.NVIC_IRQChannel = EXTI15_10_IRQn;
	USER_S1.NVIC_IRQChannelPreemptionPriority = 0x03;
	USER_S1.NVIC_IRQChannelSubPriority = 0x00;
	USER_S1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&USER_S1);

	USART.NVIC_IRQChannel = USART1_IRQn;
	USART.NVIC_IRQChannelPreemptionPriority = 0x04;
	USART.NVIC_IRQChannelSubPriority = 0x00;
	USART.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&USART);
}

/*TODO: IRQHandler */
void EXTI3_IRQHandler(void) { // left
	if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
		statusCode = 1;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void) { // right
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		statusCode = 2;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI9_5_IRQHandler(void) { // select
	if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
		statusCode = 3;
	}
	EXTI_ClearITPendingBit(EXTI_Line8);
}

void EXTI15_10_IRQHandler(void) { // users1
	if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
		statusCode = 4;
	}
	EXTI_ClearITPendingBit(EXTI_Line11);
}
int beforeU = 0;
int beforeD = 0;

void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		unsigned char c = (unsigned char) USART_ReceiveData(USART1);

		if (c == 'u') {
			beforeU = 1;
			beforeD = 0;
		}
		else if (c == 'd') {
			beforeD = 1;
			beforeU = 0;
		}
		else if (beforeU == 1 && c == 'p') {
			statusCode = 5;
			beforeU = 0;
		}
		else if (beforeD == 1 && c == 'n') {
			statusCode = 6;
			beforeD = 0;
		}
		else {
			beforeD = 0;
			beforeU = 0;
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

int main() {

	SystemInit();
	RCC_Configure();
	GPIO_Configure();
	USART_Configure();
	EXTI_Configure();
	NVIC_Configure();
	while(1) {
//		GPIO_SetBits(GPIOD, GPIO_Pin_7);
//		for(int i = 0; i < 1000000; i++);
//		GPIO_ResetBits(GPIOD, GPIO_Pin_7);
//		for(int i = 0; i < 1000000; i++);

		int i = 0;
		switch(statusCode) {
		case 1:
			GPIO_SetBits(GPIOD, GPIO_Pin_7);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_7);
			for(i = 0; i < 1000000; i++);
			break;
		case 2:
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
			for(i = 0; i < 1000000; i++);
			break;
		case 3:
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
			GPIO_ResetBits(GPIOD, GPIO_Pin_7);
			break;
		case 4:
			for(i = 0; i < 1000000; i++);
			USART_SendData(USART1, 'T');
			for(i = 0; i < 1000000; i++);
			USART_SendData(USART1, 'E');
			for(i = 0; i < 1000000; i++);
			USART_SendData(USART1, 'A');
			for(i = 0; i < 1000000; i++);
			USART_SendData(USART1, 'M');
			for(i = 0; i < 1000000; i++);
			USART_SendData(USART1, '1');
			for(i = 0; i < 1000000; i++);
			USART_SendData(USART1, '0');
			for(i = 0; i < 1000000; i++);
			USART_SendData(USART1, '\r');
			for(i = 0; i < 1000000; i++);
			USART_SendData(USART1, '\n');
			for(i = 0; i < 1000000; i++);
			statusCode = 0;
			break;
		case 5:
			GPIO_SetBits(GPIOD, GPIO_Pin_7);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_7);
			for(i = 0; i < 1000000; i++);
			GPIO_SetBits(GPIOD, GPIO_Pin_4);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_4);
			for(i = 0; i < 1000000; i++);
			GPIO_SetBits(GPIOD, GPIO_Pin_3);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_3);
			for(i = 0; i < 1000000; i++);
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
			for(i = 0; i < 1000000; i++);
			break;
		case 6:
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
			for(i = 0; i < 1000000; i++);
			GPIO_SetBits(GPIOD, GPIO_Pin_3);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_3);
			for(i = 0; i < 1000000; i++);
			GPIO_SetBits(GPIOD, GPIO_Pin_4);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_4);
			for(i = 0; i < 1000000; i++);
			GPIO_SetBits(GPIOD, GPIO_Pin_7);
			for(i = 0; i < 1000000; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_7);
			for(i = 0; i < 1000000; i++);
			break;
	}
	}
}

// flash load "C:\Users\Team03\Documents\DS-5 Workspace\wed44444\flashclear.axf"
// flash load "C:\Users\Team03\Documents\DS-5 Workspace\wed44444\Debug\wed44444.axf"
