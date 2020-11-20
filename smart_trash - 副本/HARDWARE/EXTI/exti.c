#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include  "oled.h"
#include "tcrt5000.h" 
#include "pwm.h"	  
#include "beep.h"

//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	 
  //  GPIOA.3	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   
  //GPIOB.10	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
 
 
   //  GPIOA.1	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܶ������⴫�������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
 
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ��������⴫�������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
}

/*�ж��Ƿ���,����oled��ʾ����������������*/
void EXTI3_IRQHandler(void)
{
	uint16_t i;
  delay_ms(10);    //����			 
  if(GPIO_ReadInputDataBit(TCRT4_GPIO_PORT,TCRT4_GPIO_PIN)  == 0)	
	{
		OLED_ShowString(50,4,"FULLING",16);
		for(i=0;i<=5;i++)					//��ʱ5s�رո���
				{	
					GPIO_ResetBits(GPIOA,GPIO_Pin_4);  /*����������*/
					delay_ms(100);
					GPIO_SetBits(GPIOA,GPIO_Pin_4);
					delay_ms(100);
					i++;
				}
	}
	else
		{
			OLED_Clear();	
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
		
		}
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3��·����λ
}

/*ҹ��ģʽ����*/
void EXTI15_10_IRQHandler(void)
{
  delay_ms(10);    //����			 
  if(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)	
	{
		LED0_TOGGLE;
	}
	 EXTI_ClearITPendingBit(EXTI_Line10);  //���LINE10��·����λ
}

void EXTI1_IRQHandler(void)
{
 	 delay_ms(10);    //����		
  if(GPIO_ReadInputDataBit(TCRT2_GPIO_PORT,TCRT2_GPIO_PIN)  == 0)	
	{
		TIM_Cmd(TIM4, ENABLE);	  //ʹ��tim4
		TIM_SetCompare4(TIM4,10);	//�����ת90��
		delay_ms(110);	
	}
	else  
	{					 	
		TIM_Cmd(TIM4, ENABLE);	  //ʹ��tim4
		TIM_SetCompare4(TIM4,20);	 //�����ת180��
		delay_ms(110);
	}
	TIM_Cmd(TIM4, DISABLE);
	EXTI_ClearITPendingBit(EXTI_Line1);  //���LINE15��·����λ
}
