#ifndef __TCRT_H
#define	__TCRT_H


#include "stm32f10x.h"

//  Òý½Å¶¨Òå
#define    TCRT1_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    TCRT1_GPIO_PORT    GPIOA			   
#define    TCRT1_GPIO_PIN		 GPIO_Pin_0

#define    TCRT2_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    TCRT2_GPIO_PORT    GPIOA		   
#define    TCRT2_GPIO_PIN		  GPIO_Pin_1

#define    TCRT3_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    TCRT3_GPIO_PORT    GPIOA		   
#define    TCRT3_GPIO_PIN		  GPIO_Pin_2

#define    TCRT4_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    TCRT4_GPIO_PORT    GPIOA		   
#define    TCRT4_GPIO_PIN		  GPIO_Pin_3

void TCRT_GPIO_Config(void);
uint8_t TCRT_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
#endif 

