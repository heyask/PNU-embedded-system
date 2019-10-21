#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "core_cm3.h"

int sw_state = 0;
int ua_state = 0;
int i, j;
char data[8] = {'T', 'E', 'A', 'M', '0', '1', '\r', '\n'};

void delay(){
   for(j=0; j<1000000; ++j);
}


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

   GPIO_InitTypeDef GPIO_InitStructure_LED;
   GPIO_InitTypeDef GPIO_InitStructure_USART1TX;
   GPIO_InitTypeDef GPIO_InitStructure_USART1RX;
   GPIO_InitTypeDef GPIO_InitStructure_JOY;
   GPIO_InitTypeDef GPIO_InitStructure_JOYS;
   GPIO_InitTypeDef GPIO_InitStructure_BUTTON;

   // LED 세팅
   GPIO_InitStructure_LED.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure_LED.GPIO_Pin = (GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7);
   GPIO_InitStructure_LED.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure_LED);

   /*TODO: USART1, JoyStick Config */

   // USART1 TX 세팅
   GPIO_InitStructure_USART1TX.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure_USART1TX.GPIO_Pin = (GPIO_Pin_9);
   GPIO_InitStructure_USART1TX.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure_USART1TX);

   // USART1 RX 세팅
   GPIO_InitStructure_USART1RX.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_InitStructure_USART1RX.GPIO_Pin = (GPIO_Pin_10);
   GPIO_InitStructure_USART1RX.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure_USART1RX);

   // 조이스틱 좌우 세팅
   GPIO_InitStructure_JOY.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_InitStructure_JOY.GPIO_Pin = (GPIO_Pin_3 | GPIO_Pin_4);
   GPIO_InitStructure_JOY.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure_JOY);

   // 조이스틱 선택 세팅
   GPIO_InitStructure_JOYS.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_InitStructure_JOYS.GPIO_Pin = (GPIO_Pin_8);
   GPIO_InitStructure_JOYS.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure_JOYS);

   // 버튼 세팅
   GPIO_InitStructure_BUTTON.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_InitStructure_BUTTON.GPIO_Pin = (GPIO_Pin_11);
   GPIO_InitStructure_BUTTON.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure_BUTTON);

   /*TODO: GPIO EXTILineConfig*/
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
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

   USART_Init(USART1, &USART_InitStructure);

   /*TODO: USART1 cmd ENABLE*/
   USART_Cmd(USART1, ENABLE);

   /*TODO: USART1 IT Config*/
   USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void EXTI_Configure() {
   /*TODO: EXTI configuration [ mode interrupt ] [Trigger_falling] */
   EXTI_InitTypeDef EXTI_InitStructure_LEFT;
   EXTI_InitTypeDef EXTI_InitStructure_RIGH;
   EXTI_InitTypeDef EXTI_InitStructure_SELE;
   EXTI_InitTypeDef EXTI_InitStructure_BUTT;

   EXTI_InitStructure_LEFT.EXTI_Line = EXTI_Line3;  // 왼쪽
   EXTI_InitStructure_LEFT.EXTI_LineCmd = ENABLE;
   EXTI_InitStructure_LEFT.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure_LEFT.EXTI_Trigger = EXTI_Trigger_Falling;
   EXTI_Init(&EXTI_InitStructure_LEFT);

   EXTI_InitStructure_RIGH.EXTI_Line = EXTI_Line4; // 오른쪽
   EXTI_InitStructure_RIGH.EXTI_LineCmd = ENABLE;
   EXTI_InitStructure_RIGH.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure_RIGH.EXTI_Trigger = EXTI_Trigger_Falling;
   EXTI_Init(&EXTI_InitStructure_RIGH);

   EXTI_InitStructure_SELE.EXTI_Line = EXTI_Line8; // 선택
   EXTI_InitStructure_SELE.EXTI_LineCmd = ENABLE;
   EXTI_InitStructure_SELE.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure_SELE.EXTI_Trigger = EXTI_Trigger_Falling;
   EXTI_Init(&EXTI_InitStructure_SELE);

   EXTI_InitStructure_BUTT.EXTI_Line = EXTI_Line11; // 버튼
   EXTI_InitStructure_BUTT.EXTI_LineCmd = ENABLE;
   EXTI_InitStructure_BUTT.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure_BUTT.EXTI_Trigger = EXTI_Trigger_Falling;
   EXTI_Init(&EXTI_InitStructure_BUTT);
}

void NVIC_Configure() {
   /*TODO: NVIC_configuration */
   NVIC_InitTypeDef NVIC_InitStructure_LEFT;
   NVIC_InitTypeDef NVIC_InitStructure_RIGH;
   NVIC_InitTypeDef NVIC_InitStructure_SELE;
   NVIC_InitTypeDef NVIC_InitStructure_BUTT;
   NVIC_InitTypeDef NVIC_InitStructure_UART;

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

   NVIC_InitStructure_LEFT.NVIC_IRQChannel = EXTI3_IRQn;
   NVIC_InitStructure_LEFT.NVIC_IRQChannelCmd = ENABLE;
   NVIC_InitStructure_LEFT.NVIC_IRQChannelPreemptionPriority = 0x00;
   NVIC_InitStructure_LEFT.NVIC_IRQChannelSubPriority = 0x00;
   NVIC_Init(&NVIC_InitStructure_LEFT);

   NVIC_InitStructure_RIGH.NVIC_IRQChannel = EXTI4_IRQn;
   NVIC_InitStructure_RIGH.NVIC_IRQChannelCmd = ENABLE;
   NVIC_InitStructure_RIGH.NVIC_IRQChannelPreemptionPriority = 0x01;
   NVIC_InitStructure_RIGH.NVIC_IRQChannelSubPriority = 0x00;
   NVIC_Init(&NVIC_InitStructure_RIGH);

   NVIC_InitStructure_SELE.NVIC_IRQChannel = EXTI9_5_IRQn;
   NVIC_InitStructure_SELE.NVIC_IRQChannelCmd = ENABLE;
   NVIC_InitStructure_SELE.NVIC_IRQChannelPreemptionPriority = 0x02;
   NVIC_InitStructure_SELE.NVIC_IRQChannelSubPriority = 0x00;
   NVIC_Init(&NVIC_InitStructure_SELE);

   NVIC_InitStructure_BUTT.NVIC_IRQChannel = EXTI15_10_IRQn;
   NVIC_InitStructure_BUTT.NVIC_IRQChannelCmd = ENABLE;
   NVIC_InitStructure_BUTT.NVIC_IRQChannelPreemptionPriority = 0x03;
   NVIC_InitStructure_BUTT.NVIC_IRQChannelSubPriority = 0x00;
   NVIC_Init(&NVIC_InitStructure_BUTT);

   NVIC_InitStructure_UART.NVIC_IRQChannel = USART1_IRQn;
   NVIC_InitStructure_UART.NVIC_IRQChannelCmd = ENABLE;
   NVIC_InitStructure_UART.NVIC_IRQChannelPreemptionPriority = 0x01;
   NVIC_InitStructure_UART.NVIC_IRQChannelSubPriority = 0x00;
   NVIC_Init(&NVIC_InitStructure_UART);

}


/*TODO: IRQHandler */
void EXTI3_IRQHandler(){
   if(EXTI_GetITStatus(EXTI_Line3) != RESET){
      sw_state = 1;
      EXTI_ClearITPendingBit(EXTI_Line3);
   }
}

void EXTI4_IRQHandler(){
   if(EXTI_GetITStatus(EXTI_Line4) != RESET){
      sw_state = 2;
      EXTI_ClearITPendingBit(EXTI_Line4);
   }
}

void EXTI9_5_IRQHandler(){
   if(EXTI_GetITStatus(EXTI_Line8) != RESET){
      sw_state = 0;
      EXTI_ClearITPendingBit(EXTI_Line8);
   }
}

void EXTI15_10_IRQHandler(){
   if(EXTI_GetITStatus(EXTI_Line11) != RESET){
      sw_state = -1;
      EXTI_ClearITPendingBit(EXTI_Line11);
   }
}

void USART1_IRQHandler(){
   char c;
   if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
      c = USART_ReceiveData(USART1);

      switch(c){
      case 'u':
         if(ua_state == 0) ua_state = 1;
         else ua_state = 0;
         break;
      case 'p':
         if(ua_state == 1)
            sw_state = 3;
         ua_state = 0;
         break;
      case 'd':
         if(ua_state == 0) ua_state = 2;
         else ua_state = 0;
         break;
      case 'n':
         if(ua_state == 2)
            sw_state = 4;
         ua_state = 0;
         break;
      default:
         ua_state = 0;
      }
   }
}


int main() {
   SystemInit();
   RCC_Configure();
   GPIO_Configure();
   USART_Configure();
   EXTI_Configure();
   NVIC_Configure();

   //GPIO_SetBits(GPIOD, GPIO_Pin_2);
   //GPIO_SetBits(GPIOD, GPIO_Pin_7);
   while(1){
      switch(sw_state){
      case 0: // 선택
         break;

      case 1: // 왼쪽
         GPIO_SetBits(GPIOD, GPIO_Pin_2);
         delay();
         GPIO_ResetBits(GPIOD, GPIO_Pin_2);
         delay();
         break;

      case 2: // 오른쪽
         GPIO_SetBits(GPIOD, GPIO_Pin_7);
         delay();
         GPIO_ResetBits(GPIOD, GPIO_Pin_7);
         delay();
         break;

      case -1: // TX 보내기
         for(i=0; i!=8; ++i){  // 버튼
            USART_SendData(USART1, data[i]);
            delay();
         }
         sw_state = 0;
         break;

      case 3:
         GPIO_ResetBits(GPIOD, GPIO_Pin_7);
         GPIO_SetBits(GPIOD, GPIO_Pin_2);
         delay();

         GPIO_ResetBits(GPIOD, GPIO_Pin_2);
         GPIO_SetBits(GPIOD, GPIO_Pin_3);
         delay();

         GPIO_ResetBits(GPIOD, GPIO_Pin_3);
         GPIO_SetBits(GPIOD, GPIO_Pin_4);
         delay();

         GPIO_ResetBits(GPIOD, GPIO_Pin_4);
         GPIO_SetBits(GPIOD, GPIO_Pin_7);
         delay();
         break;

      case 4:
         GPIO_ResetBits(GPIOD, GPIO_Pin_2);
         GPIO_SetBits(GPIOD, GPIO_Pin_7);
         delay();

         GPIO_ResetBits(GPIOD, GPIO_Pin_7);
         GPIO_SetBits(GPIOD, GPIO_Pin_4);
         delay();

         GPIO_ResetBits(GPIOD, GPIO_Pin_4);
         GPIO_SetBits(GPIOD, GPIO_Pin_3);
         delay();

         GPIO_ResetBits(GPIOD, GPIO_Pin_3);
         GPIO_SetBits(GPIOD, GPIO_Pin_2);
         delay();
         break;
      }

   }
}
