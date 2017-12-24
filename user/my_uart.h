#ifndef __MY_UART_H
#define	__MY_UART_H

#include "main.h"

	//���������ڶ���
#define RX_PIN_NUMBER  (11)    // UART RX pin number.
#define TX_PIN_NUMBER  (9)    // UART TX pin number.
#define CTS_PIN_NUMBER (10)  // UART Clear To Send pin number. Not used if HWFC is set to false
#define RTS_PIN_NUMBER (8)    // Not used if HWFC is set to false
#define HWFC           true // UART hardware flow control


typedef enum
{
	UART_RX_IDLE,
	UART_RX_START,
	UART_RX_FINISHED
}UART_RX_STATE_TYPE;

typedef enum
{
	UART_TX_IDLE,
	UART_TX_ING
}UART_TX_STATE_TYPE;

typedef struct _UART_RX_T
{
	UART_RX_STATE_TYPE 		State;		// 0 ��ʼ����1 �յ������ֽڣ�2 �������, 3 ������
	uint32_t 				Cnt;		// ���ռ���
	uint8_t					Buf[1024];
}UART_RX_T;

typedef struct _UART_TX_T
{
	UART_TX_STATE_TYPE		State;	
	uint32_t				Cnt;		// �ѷ��ͼ���
	uint32_t 				Len;		// �����ܳ���
	uint8_t * 				Buf;
}UART_TX_T;

typedef struct _UART_PARAMETERS_T
{
	UART_RX_T		RX;
	UART_TX_T		TX;
}UART_PARAMETERS_T;


extern UART_PARAMETERS_T	UART;

extern uint32_t UART_Init(void);
uint32_t UART_TxBytes(uint8_t* TxBuf, uint32_t TxLen);
extern int fputc(int ch, FILE * p_file);
extern int fgetc(FILE * p_file);

#endif /* __UART_H */
