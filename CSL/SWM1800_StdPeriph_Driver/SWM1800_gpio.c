/****************************************************************************************************************************************** 
* �ļ�����: SWM1800_gpio.c
* ����˵��:	SWM1800��Ƭ����ͨ�������������������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����: V1.0.0		2016��1��30��
* ������¼: 
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology 
*******************************************************************************************************************************************/
#include "SWM1800.h"
#include "SWM1800_gpio.h"


/****************************************************************************************************************************************** 
* ��������: GPIO_Init()
* ����˵��:	���ų�ʼ�����������ŷ����������衢�������衢��©���
* ��    ��: GPIO_TypeDef * GPIOx	    ָ��GPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		       ָ��GPIO���ţ���Чֵ����PIN0��PIN1��PIN2��... ... PIN14��PIN15
*			uint32_t dir	       ���ŷ���0 ����        1 ���
*			uint32_t pull_up	   �������裬0 �ر�����    1 ��������
*			uint32_t pull_down	   �������裬0 �ر�����    1 ��������
*			uint32_t open_drain	   ��©�����0 �������    1 ��©���
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_Init(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t dir, uint32_t pull_up, uint32_t pull_down, uint32_t open_drain)
{
	PORT_TypeDef * PORTx = PORTA;
	
	switch((uint32_t)GPIOx)
	{
	case ((uint32_t)GPIOA):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOA_Pos);
		
		PORTx = PORTA;
		break;
	
	case ((uint32_t)GPIOB):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOB_Pos);
		
		PORTx = PORTB;
		break;

	case ((uint32_t)GPIOC):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOC_Pos);
		
		PORTx = PORTC;
		break;
		
	case ((uint32_t)GPIOD):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOD_Pos);
		
		PORTx = PORTD;
		break;
		
	case ((uint32_t)GPIOE):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_GPIOE_Pos);
		
		PORTx = PORTE;
		break;
	}
		
	if(dir == 1)
	{
		PORT_Init(PORTx, n, 0, 0);			//PORTP.PINn��������ΪGPIO���ܣ���������ر�
		
		GPIOx->DIR |= (0x01 << n);
	}
	else
	{
		PORT_Init(PORTx, n, 0, 1);			//PORTP.PINn��������ΪGPIO���ܣ��������뿪��
		
		GPIOx->DIR &= ~(0x01 << n);
	}
	
	if(pull_up == 1)
		PORTx->PULLU |= (0x01 << n);
	else
		PORTx->PULLU &= ~(0x01 << n);
	
	if(pull_down == 1)
		PORTx->PULLD |= (0x01 << n);
	else
		PORTx->PULLD &= ~(0x01 << n);
	
	if(open_drain == 1)
		PORTx->OPEND |= (0x01 << n);
	else
		PORTx->OPEND &= ~(0x01 << n);
}

/****************************************************************************************************************************************** 
* ��������: GPIO_SetBit()
* ����˵��:	������ָ�������ŵ�ƽ�ø�
* ��    ��: GPIO_TypeDef * GPIOx	ָʾGPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		ָʾGPIO���ţ���Чֵ����PIN_0��PIN_1��PIN_2��... ... PIN_14��PIN_15
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
	GPIOx->DATA |= (0x01 << n);
}

/****************************************************************************************************************************************** 
* ��������:	GPIO_ClrBit()
* ����˵��:	������ָ�������ŵ�ƽ�õ�
* ��    ��: GPIO_TypeDef * GPIOx	ָʾGPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		ָʾGPIO���ţ���Чֵ����PIN_0��PIN_1��PIN_2��... ... PIN_14��PIN_15
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
	GPIOx->DATA &= ~(0x01 << n);
}

/****************************************************************************************************************************************** 
* ��������: GPIO_InvBit()
* ����˵��:	������ָ�������ŵ�ƽ��ת
* ��    ��: GPIO_TypeDef * GPIOx	ָʾGPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		ָʾGPIO���ţ���Чֵ����PIN_0��PIN_1��PIN_2��... ... PIN_14��PIN_15
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t n)
{
	GPIOx->DATA ^= (0x01 << n);
}

/****************************************************************************************************************************************** 
* ��������:	GPIO_GetBit()
* ����˵��:	��ȡ����ָ�������ŵĵ�ƽ״̬
* ��    ��: GPIO_TypeDef * GPIOx	ָʾGPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		ָʾGPIO���ţ���Чֵ����PIN_0��PIN_1��PIN_2��... ... PIN_14��PIN_15
* ��    ��: ����ָ�������ŵĵ�ƽ״̬	0 �͵�ƽ	1 �ߵ�ƽ
* ע������: ��
******************************************************************************************************************************************/
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t n)
{	
	return ((GPIOx->DATA >> n) & 0x01);
}

/****************************************************************************************************************************************** 
* ��������: GPIO_SetBits()
* ����˵��: ������ָ���Ĵ�n��ʼ��wλ�������ŵĵ�ƽ�ø�
* ��    ��: GPIO_TypeDef * GPIOx	ָʾGPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		ָʾGPIO���ţ���Чֵ����PIN_0��PIN_1��PIN_2��... ... PIN_14��PIN_15
*			uint32_t w		ָ��Ҫ�����ŵ�ƽ�øߵ����ŵĸ���
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
	uint32_t bits;
	
	bits = 0xFFFF >> (16 - w);
	
	GPIOx->DATA |= (bits << n);
}

/****************************************************************************************************************************************** 
* ��������:	GPIO_ClrBits()
* ����˵��: ������ָ���Ĵ�n��ʼ��wλ�������ŵĵ�ƽ�õ�
* ��    ��: GPIO_TypeDef * GPIOx	ָʾGPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		ָʾGPIO���ţ���Чֵ����PIN_0��PIN_1��PIN_2��... ... PIN_14��PIN_15
*			uint32_t w		ָ��Ҫ�����ŵ�ƽ�õ͵����ŵĸ���
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_ClrBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
	uint32_t bits;
	
	bits = 0xFFFF >> (16 - w);
	
	GPIOx->DATA &= ~(bits << n);
}

/****************************************************************************************************************************************** 
* ��������: GPIO_InvBits()
* ����˵��: ������ָ���Ĵ�n��ʼ��wλ�������ŵĵ�ƽ��ת
* ��    ��: GPIO_TypeDef * GPIOx	ָʾGPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		ָʾGPIO���ţ���Чֵ����PIN_0��PIN_1��PIN_2��... ... PIN_14��PIN_15
*			uint32_t w		ָ��Ҫ�����ŵ�ƽ��ת�����ŵĸ���
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_InvBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
	uint32_t bits;
	
	bits = 0xFFFF >> (16 - w);
	
	GPIOx->DATA ^= (bits << n);
}

/****************************************************************************************************************************************** 
* ��������:	GPIO_GetBits()
* ����˵��: ��ȡ����ָ���Ĵ�n��ʼ��wλ�������ŵĵ�ƽ״̬
* ��    ��: GPIO_TypeDef * GPIOx	ָʾGPIO�˿ڣ���Чֵ����GPIOA��GPIOB��GPIOC��GPIOD��GPIOE	
*			uint32_t n		ָʾGPIO���ţ���Чֵ����PIN_0��PIN_1��PIN_2��... ... PIN_14��PIN_15
*			uint32_t w		ָ��Ҫ�����ŵ�ƽ�øߵ����ŵĸ���
* ��    ��: ����ָ���Ĵ�n��ʼ��wλ�������ŵĵ�ƽ״̬	0 �͵�ƽ	1 �ߵ�ƽ
*			����ֵ�ĵ�0λ��ʾ����n�ĵ�ƽ״̬������ֵ�ĵ�1λ��ʾ����n+1�ĵ�ƽ״̬... ...����ֵ�ĵ�wλ��ʾ����n+w�ĵ�ƽ״̬
* ע������: ��
******************************************************************************************************************************************/
uint32_t GPIO_GetBits(GPIO_TypeDef * GPIOx, uint32_t n, uint32_t w)
{
	uint32_t bits;
	
   	bits = 0xFFFF >> (16 - w);
	
	return ((GPIOx->DATA >> n) & bits);
}