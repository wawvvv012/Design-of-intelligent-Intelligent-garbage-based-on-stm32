#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
								  
////////////////////////////////////////////////////////////////////////////////// 

#define LED0_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define LED0_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED0_GPIO_PIN				GPIO_Pin_8			        /* 连接到SCL时钟线的GPIO */


#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态
#define LED0_TOGGLE		 digitalToggle(LED0_GPIO_PORT,LED0_GPIO_PIN)

void LED_Init(void);//初始化

		 				    
#endif
