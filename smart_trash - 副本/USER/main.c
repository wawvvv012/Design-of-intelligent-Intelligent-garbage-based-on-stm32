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
		delay_init();	    	 //��ʱ������ʼ��	  
		TIM4_PWM_Init();		 //tim4��ʼ��
		LED_Init();		
		OLED_Init();
		TCRT_GPIO_Config(); 	//���⴫������ʼ��
		KEY_GPIO_Config();	
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	 	EXTIX_Init();		//�ⲿ�жϳ�ʼ��
	  BEEP_Init();
	 
	while(1)
	{
			
	/*����������⴫�����ж��Ƿ����ֻӹ������ֻӹ�����*/		
		if  (( ( TCRT_Scan(TCRT1_GPIO_PORT,TCRT1_GPIO_PIN) == 0  )  \
				|| ( TCRT_Scan(TCRT3_GPIO_PORT,TCRT3_GPIO_PIN) == 0  ) \
				) == 1)
		{
			TIM_Cmd(TIM4, ENABLE);	  //ʹ��tim4
			TIM_SetCompare4(TIM4,10);	//�����ת90��
			for(i=0;i<=8;i++)					//��ʱ5s�رո���
				{	
					delay_ms(1000);
					i++;
				}
			TIM_SetCompare4(TIM4,20);	 //�����ת180��
			delay_ms(500);
			TIM_Cmd(TIM4, DISABLE);
		} 
		else
		{
			TIM_Cmd(TIM4, DISABLE);
		}  
		

	}
}
 
