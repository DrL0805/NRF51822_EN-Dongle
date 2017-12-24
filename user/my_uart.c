#include "my_uart.h"

UART_PARAMETERS_T	UART;	

void UART0_IRQHandler(void)
{
	if(NRF_UART0->EVENTS_RXDRDY)
	{
		// �ڶ�ȡRXD����ǰ���������RXDRDY��־λ
		NRF_UART0->EVENTS_RXDRDY = 0;
		
		switch(UART.RX.State)
		{
			case UART_RX_IDLE:
				UART.RX.Cnt= 0;
				UART.RX.Buf[UART.RX.Cnt++] = NRF_UART0->RXD;	// ��ȡ����
				spi_overtime_timer_start();						// �������ճ�ʱ��ʱ��
				UART.RX.State = UART_RX_START;
				break;
			case UART_RX_START:
				UART.RX.Buf[UART.RX.Cnt++] = NRF_UART0->RXD;	// ��ȡ����
				spi_overtime_timer_restart();					// ���ý��ճ�ʱ��ʱ��
				break;
			default:
				
				break;
		}
		
//		NRF_UART0->TASKS_STARTRX = 1;					// �������մ�������
		
	}
	
	if(NRF_UART0->EVENTS_TXDRDY)
	{
		NRF_UART0->EVENTS_TXDRDY = 0;
		
		if(UART.TX.Cnt < UART.TX.Len)
		{
			NRF_UART0->TXD = UART.TX.Buf[UART.TX.Cnt++];
		}
		else
		{
			UART.TX.State = UART_TX_IDLE;		// ���ݷ������
		}
	}	
	
	if(NRF_UART0->EVENTS_ERROR)
	{
		NRF_UART0->EVENTS_ERROR = 0;
		
		NRF_UART0->TASKS_STARTTX = 1;
		NRF_UART0->TASKS_STARTRX = 1;
		NRF_UART0->EVENTS_RXDRDY = 0;
		NRF_UART0->EVENTS_TXDRDY = 0;		
	}	
}

uint32_t UART_Config(uint8_t txd_pin_number, uint8_t rxd_pin_number)
{
    nrf_gpio_cfg_output(txd_pin_number);
    nrf_gpio_cfg_input(rxd_pin_number, NRF_GPIO_PIN_NOPULL);

    NRF_UART0->PSELTXD = txd_pin_number;
    NRF_UART0->PSELRXD = rxd_pin_number;
	
    NRF_UART0->BAUDRATE      = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);

    NRF_UART0->ENABLE        = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);   
    
	NRF_UART0->INTENSET = ( UART_INTENSET_TXDRDY_Enabled << UART_INTENSET_TXDRDY_Pos) |
						  ( UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos) |
						  ( UART_INTENSET_ERROR_Enabled << UART_INTENSET_ERROR_Pos);
	
	NRF_UART0->TASKS_STARTTX = 1;
    NRF_UART0->TASKS_STARTRX = 1;
    NRF_UART0->EVENTS_RXDRDY = 0;
	NRF_UART0->EVENTS_TXDRDY = 0;
	
    NVIC_SetPriority(UART0_IRQn, 0x03);
	NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
	
	return 0;
}

uint32_t UART_TxBytes(uint8_t* TxBuf, uint32_t TxLen)
{
	if(0 == TxLen)
		return 1;
	
	switch(UART.TX.State)
	{
		case UART_TX_IDLE:
			UART.TX.State = UART_TX_ING;
			UART.TX.Cnt = 0;
			UART.TX.Len = TxLen;
			UART.TX.Buf = TxBuf;
			NRF_UART0->EVENTS_TXDRDY = 0;					// ��������¼�
			NRF_UART0->TXD = UART.TX.Buf[UART.TX.Cnt++];	// ���͵�һ���ֽ�
			break;
		case UART_TX_ING:
			break;
		default:
			break;
	}
	
	return 0;
}


uint32_t UART_Init(void)
{
	UART_Config(9, 11);
	
	UART.RX.State = UART_RX_IDLE;
	UART.TX.State = UART_TX_IDLE;
	
	return 0;
}

int fputc(int ch, FILE * p_file)
{

    return ch;
}

int fgetc(FILE * p_file)
{
	uint8_t input;
	
    return input;
}






