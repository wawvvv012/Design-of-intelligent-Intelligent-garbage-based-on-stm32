#include "beep.h"

void BEEP_Init(void)
{
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��PA �˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				     //BEEP-->PA.4 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					       //�����趨������ʼ��GPIOA.4
 GPIO_SetBits(GPIOA,GPIO_Pin_4);						           //PA.4 ����ߣ�����
}
