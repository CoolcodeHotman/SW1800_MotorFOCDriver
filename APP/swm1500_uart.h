#ifndef __SWM1500_UART_H__
#define __SWM1500_UART_H__

#include "SWM1500.h"

typedef struct {
	uint32_t baudrate;
	uint8_t data_len;		//0 5λ����λ		1 6λ����λ		2 7λ����λ		3 8λ����λ
	uint8_t stop_len;		//0 1λֹͣλ		1 2λֹͣλ
	uint8_t parity;			//0 ��У��		1 ��У��		2 żУ��
	uint8_t rxfifo;			//0 ��ʹ��FIFO	1 ���Ϊ1�ֽ�	4 ���Ϊ4�ֽ�	8 ���Ϊ8�ֽ�	14 ���Ϊ14�ֽ�
	uint8_t RBR_IE;			//RBR�Ĵ��������ݻ�RX FIFO�����ݵ��ﴥ���ȼ� �ж�ʹ��
	uint8_t THR_IE;			//THR�ջ�TX FIFO�� �ж�ʹ��
	uint8_t LSR_IE;			//֡����У����������Break ָʾ �ж�ʹ��	
} UART_InitStructure;

void UART_Init(UART_T * UARTx,UART_InitStructure * initStruct);		//UART���ڳ�ʼ������������λ���ȡ�ֹͣλ���ȡ�У��λ�������ʡ�FIFO������ȡ��ж�ʹ�ܵȵ�����
void UART_Open(UART_T * UARTx);										//UART����ʹ�ܣ�ʹ����ָ��UARTģ���ṩ����ʱ��
void UART_Close(UART_T * UARTx);									//UART���ڽ��ܣ�������ָ�ж�UARTģ���ʱ�ӹ������Ӷ���С�ܺ�	
void UART_WriteByte(UART_T * UARTx,uint8_t byt);					//����һ���ֽ�����
uint8_t UART_ReadByte(UART_T * UARTx);								//��ȡһ���ֽ�����
void UART_WriteBytes(UART_T * UARTx,char buf[],uint32_t len);	//����len���ֽ�����
uint32_t UART_ReadBytes(UART_T * UARTx,char buf[],uint32_t len);	//��ȡlen���ֽ�����

void UART_SetBaudrate(UART_T * UARTx,uint32_t baudrate);			//���ò�����
uint32_t UART_GetBaudrate(UART_T * UARTx);			 				//��ȡ��ǰʹ�õĲ�����
void UART_SetDataLen(UART_T * UARTx,uint32_t data_len);				//��������λ����
uint32_t UART_GetDataLen(UART_T * UARTx);							//��ȡ��ǰ������λ����
void UART_SetStopLen(UART_T * UARTx,uint32_t stop_len);				//����ֹͣλ����
uint32_t UART_GetStopLen(UART_T * UARTx);			   				//��ȡ��ǰ��ֹͣλ����
void UART_SetParity(UART_T * UARTx,uint32_t parity);  				//����У��λģʽ
uint32_t UART_GetParity(UART_T * UARTx);			  				//��ȡ��ǰУ��λģʽ
void UART_SetRXFIFOTL(UART_T * UARTx,uint32_t level); 				//����RX FIFO Trigger Level����RX FIFO���յ����������ֽں󴥷�RX FIFO���жϣ�
uint32_t UART_GetRXFIFOTL(UART_T * UARTx);		  					//��ȡ���ڵ�ǰ��RX FIFO Trigger Level����RX FIFO���յ����������ֽں󴥷�RX FIFO���жϣ�

void UART_IntRBREn(UART_T * UARTx);	 				//ʹ�ܽ������ݿ��ã���RBR�������ݣ��ж�
void UART_IntRBRDis(UART_T * UARTx);		  		//���ܽ������ݿ��ã���RBR�������ݣ��ж�
void UART_IntTHREn(UART_T * UARTx);					//ʹ�ܷ��ͱ��ּĴ������ж�
void UART_IntTHRDis(UART_T * UARTx);				//���ܷ��ͱ��ּĴ������ж�
void UART_IntLSREn(UART_T * UARTx);					//ʹ����״̬��ָ֡����У����������Break ָʾ���ж�
void UART_IntLSRDis(UART_T * UARTx);				//������״̬��ָ֡����У����������Break ָʾ���ж�
uint32_t UART_IntCurrent(UART_T * UARTx); 			//��ȡ��ǰ���ж�״̬��ȷ����ǰ�������������ж�

uint32_t UART_IsDataAvailable(UART_T * UARTx);		//RBR���Ƿ�����Ч�ֽ�
uint32_t UART_IsRXOverflow(UART_T * UARTx);	  		//RX�Ƿ����������
uint32_t UART_IsParityError(UART_T * UARTx);  		//�Ƿ�����У�����
uint32_t UART_IsFrameError(UART_T * UARTx);	 		//�Ƿ�����֡����
uint32_t UART_HasBreakIndicate(UART_T * UARTx);		//�Ƿ���Break Indicator
uint32_t UART_IsTHREmpty(UART_T * UARTx);	   		//THR��Transmit Hold Register�������ͱ��ּĴ������Ƿ�Ϊ��
uint32_t UART_IsTSREmpty(UART_T * UARTx);	   		//TSR��Transmit Shift Register����������λ�Ĵ������Ƿ�Ϊ��
uint32_t UART_RXFIFOError(UART_T * UARTx);		 	//RX FIFO���Ƿ��д���У�����֡����Break Indicator��


#endif //__SWM1500_UART_H__
