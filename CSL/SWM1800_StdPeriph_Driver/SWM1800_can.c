/****************************************************************************************************************************************** 
* �ļ�����: SWM1800_can.c
* ����˵��:	SWM1800��Ƭ����WDT���Ź�����������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����:	V1.0.0		2016��1��30��
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
#include "SWM1800_can.h"

/****************************************************************************************************************************************** 
* ��������:	CAN_Init()
* ����˵��:	CAN�ӿڳ�ʼ��
* ��    ��: CAN_TypeDef * CANx	ָ��Ҫ�����õ�CAN�ӿڣ���Чֵ����CAN
*			CAN_InitStructure * initStruct    ����CAN�ӿ�����趨ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void CAN_Init(CAN_TypeDef * CANx, CAN_InitStructure * initStruct)
{	
	switch((uint32_t)CANx)
	{
	case ((uint32_t)CAN):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_CAN_Pos);
		break;
	}
	
	CAN_Close(CANx);	//һЩ�ؼ��Ĵ���ֻ����CAN�ر�ʱ����
	
	CANx->CR &= ~(CAN_CR_LOM_Msk | CAN_CR_STM_Msk | CAN_CR_AFM_Msk);
	CANx->CR |= (initStruct->Mode << CAN_CR_LOM_Pos) |
				(initStruct->FilterMode << CAN_CR_AFM_Pos);
	
	CANx->FILTER.AMR[0] = initStruct->FilterMask32b & 0xFF;
	CANx->FILTER.AMR[1] = (initStruct->FilterMask32b >>  8) & 0xFF;
	CANx->FILTER.AMR[2] = (initStruct->FilterMask32b >> 16) & 0xFF;
	CANx->FILTER.AMR[3] = (initStruct->FilterMask32b >> 24) & 0xFF;
	
	CANx->FILTER.ACR[0] = initStruct->FilterCheck32b & 0xFF;
	CANx->FILTER.ACR[1] = (initStruct->FilterCheck32b >>  8) & 0xFF;
	CANx->FILTER.ACR[2] = (initStruct->FilterCheck32b >> 16) & 0xFF;
	CANx->FILTER.ACR[3] = (initStruct->FilterCheck32b >> 24) & 0xFF;
	
	CANx->BT1 = (0 << CAN_BT1_SAM_Pos) |
				(initStruct->CAN_BS1 << CAN_BT1_TSEG1_Pos) |
				(initStruct->CAN_BS2 << CAN_BT1_TSEG2_Pos);
	
	CANx->BT0 = (initStruct->CAN_SJW << CAN_BT0_SJW_Pos) |
				((SystemCoreClock/2/initStruct->Baudrate/(1 + initStruct->CAN_BS1 + initStruct->CAN_BS2) - 1) << CAN_BT0_BRP_Pos);
	
	CANx->RXERR = 0;	//ֻ���ڸ�λģʽ�����
	CANx->TXERR = 0;
	
	CANx->IE = (initStruct->RXNotEmptyIEn << CAN_IE_RXDA_Pos)  |
			   (initStruct->TXNotFullIEn  << CAN_IE_TXRDY_Pos) |
			   (initStruct->ErrorWarnIEn  << CAN_IE_ERR_Pos)   |
			   (initStruct->ArbitLostIEn  << CAN_IE_ARBLOST_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	CAN_Open()
* ����˵��:	CAN�ӿڴ�
* ��    ��: CAN_TypeDef * CANx	ָ��Ҫ�����õ�CAN�ӿڣ���Чֵ����CAN
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void CAN_Open(CAN_TypeDef * CANx)
{
	CANx->CR &= ~(0x01 << CAN_CR_RST_Pos);	//�˳���λģʽ�����빤��ģʽ
}

/****************************************************************************************************************************************** 
* ��������:	CAN_Close()
* ����˵��:	CAN�ӿڹر�
* ��    ��: CAN_TypeDef * CANx	ָ��Ҫ�����õ�CAN�ӿڣ���Чֵ����CAN
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void CAN_Close(CAN_TypeDef * CANx)
{
	CANx->CR |= (0x01 << CAN_CR_RST_Pos);	//���븴λģʽ�����ܷ��ͺͽ�������
}

/****************************************************************************************************************************************** 
* ��������:	CAN_Transmit()
* ����˵��:	CAN��������
* ��    ��: CAN_TypeDef * CANx	ָ��Ҫ�����õ�CAN�ӿڣ���Чֵ����CAN
*			uint32_t format		CAN_FRAME_STD ��׼֡    CAN_FRAME_EXT ��չ֡
*			uint32_t id
*			uint8_t data[]		Ҫ���͵�����
*			uint32_t size		Ҫ���͵����ݵĸ���
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void CAN_Transmit(CAN_TypeDef * CANx, uint32_t format, uint32_t id, uint8_t data[], uint32_t size)
{
	uint32_t i;
	
	if(format == CAN_FRAME_STD)
	{
		CANx->TXFRAME.INFO = (CAN_FRAME_STD << CAN_INFO_FF_Pos) |
							 (0 << CAN_INFO_RTR_Pos)            |
							 (size << CAN_INFO_DLC_Pos);
		
		CANx->TXFRAME.DATA[0] = id >> 3;
		CANx->TXFRAME.DATA[1] = id << 5;
		
		for(i = 0; i < size; i++)
		{
			CANx->TXFRAME.DATA[i+2] = data[i];
		}
	}
	else //if(format == CAN_FRAME_EXT)
	{
		CANx->TXFRAME.INFO = (CAN_FRAME_EXT << CAN_INFO_FF_Pos) |
							 (0 << CAN_INFO_RTR_Pos)            |
							 (size << CAN_INFO_DLC_Pos);
		
		CANx->TXFRAME.DATA[0] = id >> 21;
		CANx->TXFRAME.DATA[1] = id >> 13;
		CANx->TXFRAME.DATA[2] = id >>  5;
		CANx->TXFRAME.DATA[3] = id <<  3;
		
		for(i = 0; i < size; i++)
		{
			CANx->TXFRAME.DATA[i+4] = data[i];
		}
	}
	
	if(CANx->CR & CAN_CR_STM_Msk)
		CANx->CMD = (1 << CAN_CMD_SRR_Pos);
	else
		CANx->CMD = (1 << CAN_CMD_TXREQ_Pos);
}
