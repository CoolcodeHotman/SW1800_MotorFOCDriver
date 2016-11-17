/****************************************************************************************************************************************** 
* �ļ�����:	SWM1800_flash.c
* ����˵��:	ʹ��оƬ��IAP���ܽ�Ƭ��Flashģ���EEPROM���������ݣ�����󲻶�ʧ
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����: V1.0.0		2016��1��30��
* ������¼: 
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
#include "SWM1800_flash.h"

typedef void (*IAPFunc)(uint32_t faddr, uint32_t raddr, uint32_t cnt, uint32_t cmd);
IAPFunc IAPfunc = (IAPFunc)0x1000601;

/****************************************************************************************************************************************** 
* ��������:	FLASH_Erase()
* ����˵��:	FLASH����������ÿ������4K�ֽ�
* ��    ��: uint32_t addr		Ҫ���������ĵ�ַ������4K���룬��addr%4096 == 0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void FLASH_Erase(uint32_t addr)
{
	__disable_irq();
	
	IAPfunc(addr, 0, 0, 0x51);
	
	__enable_irq();
	
	CACHE_Invalid(addr);
}

/****************************************************************************************************************************************** 
* ��������:	FLASH_Write()
* ����˵��:	FLASH����д��
* ��    ��: uint32_t addr		����Ҫд�뵽Flash�еĵ�ַ���ֶ���
*			uint32_t buff[]		Ҫд��Flash�е�����
*			uint32_t cnt		Ҫд�����ݵĸ���������Ϊ��λ
* ��    ��: ��
* ע������: Ҫд������ݱ���ȫ����ͬһҳ�ڣ���addr/256 == (addr+cnt*4)/256
******************************************************************************************************************************************/
void FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t cnt)
{	
	__disable_irq();
	
	IAPfunc(addr, (uint32_t)buff, cnt*4, 0x52);
	
	__enable_irq();
	
	CACHE_Invalid(addr);
}

/****************************************************************************************************************************************** 
* ��������:	FLASH_Read()
* ����˵��:	FLASH���ݶ�ȡ
* ��    ��: uint32_t addr		Ҫ��ȡ��������Flash�еĵ�ַ���ֶ���
*			uint32_t buff[]		��ȡ�������ݴ���buffָ����ڴ�
*			uint32_t cnt		Ҫ��ȡ�����ݵĸ���������Ϊ��λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void FLASH_Read(uint32_t addr, uint32_t buff[], uint32_t cnt)
{	
	uint32_t i;
	
	while(FLASH->STAT & FLASH_STAT_BUSY_Msk);
	
	FLASH->CR = (1 << FLASH_CR_FFCLR_Pos);			//Clear FIFO
	
	FLASH->CR = (FLASH_CMD_READ_DATA << FLASH_CR_CMD_Pos) |
				(0 << FLASH_CR_LEN_Pos);			//������
	FLASH->ADDR = addr;
	FLASH->START = 1;
	
	for(i = 0; i < cnt; i++)
	{
		while(FLASH->STAT & FLASH_STAT_FE_Msk);		//FIFO Empty
		
		buff[i] = FLASH->DATA;
	}
	
	FLASH->START = 0;
	
	FLASH->CR = (1 << FLASH_CR_FFCLR_Pos);			//Clear FIFO
	FLASH->CR = 0;
}
