#ifndef __SYSTEM_SWM1800_H__
#define __SYSTEM_SWM1800_H__

#ifdef __cplusplus
 extern "C" {
#endif

#define SYS_CLK_24MHz	0	 	//0 �ڲ���Ƶ24MHz RC����
#define SYS_CLK_6MHz	1		//1 �ڲ���Ƶ 6MHz RC����									
#define SYS_CLK_48MHz	2		//2 �ڲ���Ƶ48MHz RC����									
#define SYS_CLK_12MHz	3		//3 �ڲ���Ƶ12MHz RC����									
#define SYS_CLK_32KHz	4		//4 �ڲ���Ƶ32KHz RC����									
#define SYS_CLK_XTAL	5		//5 �ⲿXTAL����������2-30MHz��

#define SYS_CLK   SYS_CLK_48MHz//SYS_CLK_24MHz


#define __HSI		(24000000UL)		//�����ڲ�ʱ��
#define __LSI		(   32000UL)		//�����ڲ�ʱ��
#define __HSE		(24000000UL)		//�����ⲿʱ��


extern uint32_t SystemCoreClock;		// System Clock Frequency (Core Clock)
extern uint32_t CyclesPerUs;			// Cycles per micro second


/* Setup the microcontroller system Initialise GPIO directions and values */
extern void SystemInit(void);


/* Updates the SystemCoreClock with current core Clock retrieved from cpu registers */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif //__SYSTEM_SWM1800_H__
