#include "tcrt5000.h"  
#include "delay.h" 

void TCRT_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(TCRT1_GPIO_CLK|TCRT2_GPIO_CLK|TCRT3_GPIO_CLK|TCRT4_GPIO_CLK,ENABLE);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = TCRT1_GPIO_PIN; 
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(TCRT1_GPIO_PORT, &GPIO_InitStructure);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = TCRT2_GPIO_PIN; 
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(TCRT2_GPIO_PORT, &GPIO_InitStructure);	
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = TCRT3_GPIO_PIN; 
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(TCRT3_GPIO_PORT, &GPIO_InitStructure);	
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = TCRT4_GPIO_PIN; 
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(TCRT4_GPIO_PORT, &GPIO_InitStructure);	
}


uint8_t TCRT_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ����ڵ� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0 )  
	{	 
		/*�ȴ��ڵ��Ƴ� */
		delay_ms(1000);
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0);   
		return 	0;	 
	}
	else
	{
		return 1;
	}
}

