#ifndef __MY_RADIO_H
#define	__MY_RADIO_H

#include "main.h"


#define 	 NRF_MAX_NUMBER_OF_RETRANSMITS		(3)					//����ط�����
//#define		 NRF_RETRANSMIT_DELAY				(280)				//0~255ms���ֵ
#define 	 NRF_PIPE						(0)						//2.4GƵ�㡢
#define		 NRF_ACK_PROTOCOL_LEN			(17)					//�Զ�������ģ��ACKЭ�����ݳ���
#define		 NRF_TOTAL_DATA_LEN				(250)				//2.4G�����ܳ���	
#define		 NRF_USEFUL_DATA_LEN		(NRF_TOTAL_DATA_LEN - NRF_ACK_PROTOCOL_LEN)	//��Ч���ݳ���
#define		 NRF_DATA_IS_USE				(0)
#define      NRF_DATA_IS_ACK				(1)
#define 	 NRF_DATA_NEED_ACK				(1)
#define		 NRF_DATA_NEEDLESS_ACK			(2)
#define 	 NRF_DATA_HEAD					(0x61)
#define      NRF_DATA_END                   (0x21)
#define      NRF_DATA_RESERVE				(0xFF)  //����λĬ��ֵ


#define		 DTQ_MAX_NUM						(50)

typedef struct 
{
	uint8_t 		LastSeqNum;			
	uint8_t 		UID[4];
}DTQ_PARAMETERS_T;

typedef struct
{
	uint8_t 				RxChannal;
	uint8_t					RxBitRate;
	
	// ֡�Ź����߼�
	uint8_t					pLastDtq;			// ��һ���洢������ָ��λ��0~(DTQ_MAX_NUM-1)ѭ��
	DTQ_PARAMETERS_T		DTQ[DTQ_MAX_NUM];	
}RADIO_PARAMETERS_T;


extern nrf_esb_payload_t        tx_payload;
extern nrf_esb_payload_t        rx_payload;
extern RADIO_PARAMETERS_T		 RADIO;

uint32_t my_rx_esb_init(void);
uint32_t RADIO_Init(void);
uint32_t RADIO_Update(void);
void RADIO_RxDataHandler(void);

#endif 

