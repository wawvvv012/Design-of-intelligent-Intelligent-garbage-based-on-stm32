#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include  "oled.h"
#include "tcrt5000.h" 
#include "pwm.h"	  
#include "beep.h"

//外部中断初始化函数
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

	 
  //  GPIOA.3	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   
  //GPIOB.10	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
 
 
   //  GPIOA.1	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能顶部红外传感器所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
 
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能正面红外传感器所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
}

/*判断是否满,满了oled显示字样，蜂鸣器报警*/
void EXTI3_IRQHandler(void)
{
	uint16_t i;
  delay_ms(10);    //消抖			 
  if(GPIO_ReadInputDataBit(TCRT4_GPIO_PORT,TCRT4_GPIO_PIN)  == 0)	
	{
		OLED_ShowString(50,4,"FULLING",16);
		for(i=0;i<=5;i++)					//延时5s关闭盖子
				{	
					GPIO_ResetBits(GPIOA,GPIO_Pin_4);  /*蜂鸣器报警*/
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
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3线路挂起位
}

/*夜晚模式控制*/
void EXTI15_10_IRQHandler(void)
{
  delay_ms(10);    //消抖			 
  if(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)	
	{
		LED0_TOGGLE;
	}
	 EXTI_ClearITPendingBit(EXTI_Line10);  //清除LINE10线路挂起位
}

void EXTI1_IRQHandler(void)
{
 	 delay_ms(10);    //消抖		
  if(GPIO_ReadInputDataBit(TCRT2_GPIO_PORT,TCRT2_GPIO_PIN)  == 0)	
	{
		TIM_Cmd(TIM4, ENABLE);	  //使能tim4
		TIM_SetCompare4(TIM4,10);	//舵机正转90度
		delay_ms(110);	
	}
	else  
	{					 	
		TIM_Cmd(TIM4, ENABLE);	  //使能tim4
		TIM_SetCompare4(TIM4,20);	 //舵机反转180度
		delay_ms(110);
	}
	TIM_Cmd(TIM4, DISABLE);
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE15线路挂起位
}
