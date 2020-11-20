#include "tcrt5000.h"  
#include "delay.h" 

void TCRT_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(TCRT1_GPIO_CLK|TCRT2_GPIO_CLK|TCRT3_GPIO_CLK|TCRT4_GPIO_CLK,ENABLE);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = TCRT1_GPIO_PIN; 
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(TCRT1_GPIO_PORT, &GPIO_InitStructure);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = TCRT2_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(TCRT2_GPIO_PORT, &GPIO_InitStructure);	
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = TCRT3_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(TCRT3_GPIO_PORT, &GPIO_InitStructure);	
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = TCRT4_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(TCRT4_GPIO_PORT, &GPIO_InitStructure);	
}


uint8_t TCRT_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有遮挡 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0 )  
	{	 
		/*等待遮挡移除 */
		delay_ms(1000);
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0);   
		return 	0;	 
	}
	else
	{
		return 1;
	}
}

