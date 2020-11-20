#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "tcrt5000.h" 
#include "oled.h"
#include "exti.h" 
#include "key.h"
#include "beep.h"

 int main(void)
 {	 
		uint16_t i;
		delay_init();	    	 //延时函数初始化	  
		TIM4_PWM_Init();		 //tim4初始化
		LED_Init();		
		OLED_Init();
		TCRT_GPIO_Config(); 	//红外传感器初始化
		KEY_GPIO_Config();	
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	 	EXTIX_Init();		//外部中断初始化
	  BEEP_Init();
	 
	while(1)
	{
			
	/*两个侧面红外传感器判断是否有手挥过，有手挥过开盖*/		
		if  (( ( TCRT_Scan(TCRT1_GPIO_PORT,TCRT1_GPIO_PIN) == 0  )  \
				|| ( TCRT_Scan(TCRT3_GPIO_PORT,TCRT3_GPIO_PIN) == 0  ) \
				) == 1)
		{
			TIM_Cmd(TIM4, ENABLE);	  //使能tim4
			TIM_SetCompare4(TIM4,10);	//舵机正转90度
			for(i=0;i<=8;i++)					//延时5s关闭盖子
				{	
					delay_ms(1000);
					i++;
				}
			TIM_SetCompare4(TIM4,20);	 //舵机反转180度
			delay_ms(500);
			TIM_Cmd(TIM4, DISABLE);
		} 
		else
		{
			TIM_Cmd(TIM4, DISABLE);
		}  
		

	}
}
 
