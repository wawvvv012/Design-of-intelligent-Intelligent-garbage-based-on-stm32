#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
								  
////////////////////////////////////////////////////////////////////////////////// 

#define LED0_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define LED0_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LED0_GPIO_PIN				GPIO_Pin_8			        /* ���ӵ�SCLʱ���ߵ�GPIO */


#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬
#define LED0_TOGGLE		 digitalToggle(LED0_GPIO_PORT,LED0_GPIO_PIN)

void LED_Init(void);//��ʼ��

		 				    
#endif
