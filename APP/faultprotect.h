#ifndef _FAULTPROTECT_H
#define _FAULTPROTECT_H

#include "general.h"
#include "UserParms.h"
#include "Park.h"
#include "SWM1800.h"
#include "MeasCurr.h"
#include "Pi.h"

#define DELTA_VALUE 20		//
#define IPM_FO_LOW_TIMES    20  //������⵽FO��������͵�ƽ����
#define OVER_TEMPERATURE_TIMES  20  //������⵽���´���
#define UNNORMAL_SPEED_TIMES    1   //������⵽ת�ٲ��Դ���

#define R_VBUS_RATIO		121     //ĸ�ߵ�ѹ�����ѹ����
#define DCbus_OVERVOLTAGE 320	//��λΪV
#define DCbus_UNDERVOLTAGE 280	//ĸ�ߵ�ѹ���250VΪǷѹ
#define DCbus_OVERVOLTAGE_ADVAL (DCbus_OVERVOLTAGE*4095/(R_VBUS_RATIO*VDD))  //4000	// 3.2v���ҹ�ѹ�����㣬ĸ�ߵ�ѹ���400V ,��Ҫ�޸ĵ�·�ĵ����ѹ
#define DCbus_UNDERVOLTAGE_ADVAL (DCbus_UNDERVOLTAGE*4095/(R_VBUS_RATIO*VDD))   //ǷѹADֵ

#define PHASE_CURRENT_DEVIATION_RATIO   10  //�����ƫ��ֵ����
#define PHASE_CURRENT_AD_DEVIATION_RATIO   10  //�����ADƫ��ֵ����

#define PHASE_OVERCURRENT_VALUE 0.8	//������������λΪA
#define CALCULATE_PHASE_CURRENT(x) ((x*RSHUNT*DIFFAMPGAIN*4095)/VDD)
#define PHASE_OVERCURRENT (CALCULATE_PHASE_CURRENT(PHASE_OVERCURRENT_VALUE))      // �������Ӧ��ADֵ

#define PHASE_MINCURRENT_VALUE 0.2		//�޵��ʱ���������λΪA
#define PHASE_MINCURRENT_VALUE_TURN_AD (CALCULATE_PHASE_CURRENT(PHASE_MINCURRENT_VALUE)) 
#define PHASECURRENT_NEAR_ZERO_ADVALUE (0.25*PHASE_MINCURRENT_VALUE_TURN_AD)

#define MOTOR_MINROTATE 300
#define ELECTRIC_TIMER_ADSAMPLE_NUMBER (PWMFREQUENCY*60/(MOTOR_MINROTATE*POLEPAIRS)) 

/***********************���¼���������************************/
#define RESISTOR_DEG25		47000	    //IPM�¶�25��ʱ������Ϊ47k
#define RESISTOR_DEG100	    2900		//IPM�¶�100��ʱ������Ϊ2.9k
#define RESISTOR_PULLUP		8200		//IPM������������
#define OVER_TEMPERATURE    95		    //����IPM���±�������λΪ��
#define ADVALUE_DEG25		RESISTOR_DEG25*4095/(RESISTOR_DEG25+RESISTOR_PULLUP)	//25��ʱ��Ӧ��ADֵ
#define ADVALUE_DEG100		RESISTOR_DEG100*4095/(RESISTOR_DEG100+RESISTOR_PULLUP)  //100��ʱ��Ӧ��ADֵ
#define RESISTOR_DEGOVERTEMP ((OVER_TEMPERATURE-25)*(RESISTOR_DEG100-RESISTOR_DEG25)/(100-25)+RESISTOR_DEG25)	//����ʱIPM����
#define ADVALUE_OVER_TEMPERATUR	    RESISTOR_DEGOVERTEMP*4095/(RESISTOR_DEGOVERTEMP+RESISTOR_PULLUP)	//����ʱ��Ӧ��ADֵ
/****************************************************************************/


/***********************************ϵͳ״̬*************************************************/
#define SYSTATUS_STANDBY                1       //����
#define SYSTATUS_NORMAL                 2       //����
#define SYSTATUS_OVERVOL                3       //��ѹ
#define SYSTATUS_LOWVOL                 4       //Ƿѹ
#define SYSTATUS_OVERPHASECURRENT       5       //���������
#define SYSTATUS_LOSESTEP               6       //ʧ��
#define SYSTATUS_SPEEDUNNORMAL          7       //ת�ٲ���
#define SYSTATUS_CURRENTDEVIATION       8       //����ƫ�����
#define SYSTATUS_IPM_FO                 9       //FO�������
#define SYSTATUS_ADDEVIATION            10      //AD�쳣
#define SYSTATUS_OVERTEMPERATURE        11      //����
/***************************************************************************************************/

/***********************************����LED����ʱ��*************************************************/
#define STANDBY_ONTIME      10      //����LED��ʱ�䣬10*100ms
#define STANDBY_OFFTIME     (STANDBY_ONTIME+10)      //����LED��ʱ�䣬10*100ms
#define NORMAL_ONTIME       6       //����LED��ʱ�䣬3*100ms
#define NORMAL_OFFTIME      (NORMAL_ONTIME+6)       //����LED��ʱ�䣬3*100ms
#define FAULT_TWINKLETIME        2       //����LED��˸ʱ�䣬3*100ms
#define FAULT_OFFTIME       (15-FAULT_TWINKLETIME)      //����LED��ʱ�䣬15*100ms
/***************************************************************************************************/

/***********************************����LED��˸����*************************************************/
#define OVER_VOL_TWINKLETIMES                   1   //ֱ��ĸ�������ѹ
#define LOW_VOL_TWINKLETIMES                    2   //ֱ��ĸ�������ѹǷѹ
#define OVER_PHASECURRENT_TWINKLETIMES          3   //��������������
#define LOSE_STEP_TWINKLETIMES                  4   //ʧ�����(�޵����ȱ��)
#define SPEED_UNNORMAL_TWINKLETIMES             5   //3�����ȱ��(ת�ٲ���)
#define CURRENT_DEVIATION_TWINKLETIMES          6   //3�����ȱ��(������ƫ�����)
#define IPM_FO_TWINKLETIMES                     7   //�����IPM_FO����
#define AD_DEVIATION_TWINKLETIMES               8   //AD�쳣������(���������ƽƫ�����)
#define OVER_TEMPERATURE_TWINKLETIMES           9   //�¶ȱ���(ģ����±���)
/***************************************************************************************************/

#define GET_IPM_FO_STATUS ((GPIOE->DATA >> PIN3) & 0x01)    //��ȡIPM_FO���ŵ�ƽ

typedef struct
{
	u32 Ad_Temperature_total;
	u32 Ad_Temperature_times;
	u32 Ad_Temperature_value;
}IPM;

typedef struct
{
	u8 Systemstatus;	//ϵͳ״̬��1=������2=������ת��>=3����
	u32 Timernumcount;	//��ʱ��ʱ���ۼ���
	u32 Twinkletimes;	//��˸����
}LED_INDICATE;

typedef struct
{
	s16 Ia_max; 	//A�����AD���ֵ
	s16 Ia_min;
	s16 Ib_max; 	//B�����AD���ֵ
	s16 Ib_min;
	u32 Adsample_times; 	//ADȡ����ֵ
	u16 Phase_current_check_flag;	//�������ֵ�����ɱ�־, 0=δ��ɣ�1�����
}PHASE_CURRENT;



typedef struct 
{

	u32 fault_code;

	IPM *IPM_module;

	LED_INDICATE *Led_indicate;

	PHASE_CURRENT *Phase_current_detect;
	
}MOTOR_FAULT;

extern s16 TargetDCbus;
extern s16 CorrADC0;
extern s16 CorrADC1;
extern u32 fg_outfrequence;
extern s16 View_Variable1,View_Variable2,View_Variable3,View_Variable4;


void phase_current_max_check(MOTOR_FAULT*pmotor_fault);
    
void motor_fault_detect(MOTOR_FAULT*pmotor_fault);

void SysLed_Twinkle(MOTOR_FAULT*pmotor_fault);

void motor_fault_init(MOTOR_FAULT *pmotor_fault);


#endif
