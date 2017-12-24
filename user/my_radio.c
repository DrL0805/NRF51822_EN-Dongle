#include "my_radio.h"

nrf_esb_payload_t        tx_payload;
nrf_esb_payload_t        rx_payload;
RADIO_PARAMETERS_T		 RADIO;

void nrf_esb_event_handler(nrf_esb_evt_t const * p_event)
{
    switch (p_event->evt_id)
    {
        case NRF_ESB_EVENT_TX_SUCCESS:
            break;
        case NRF_ESB_EVENT_TX_FAILED:
            break;
        case NRF_ESB_EVENT_RX_RECEIVED:
            break;
    }
}


// 包号过滤逻辑， true不过滤（发送给接收器），false过滤 
bool RADIO_PackFilter(uint8_t* UID, uint8_t Seq)
{
	uint8_t PublicUid[4] = {0,0,0,0};
	
	// 包号为0，过滤
	if(Seq == 0)
		return true;
	
	// UID全为0，不过滤
	if(ArrayCmp(PublicUid, UID, 4))
		return true;
	
	// 帧号过滤条件：答题器UID名单中有此答题器，并且帧号相同
	for(uint8_t i=0;i<DTQ_MAX_NUM;i++)
	{ 
		if(ArrayCmp(RADIO.DTQ[i].UID, UID, 4))
		{
			// 帧号相同，过滤；帧号不同，更新帧号并发送给接收器
			if(Seq == RADIO.DTQ[i].LastSeqNum)
			{
				return false;
			}	
			else
			{
				RADIO.DTQ[i].LastSeqNum = Seq;
				return true;
			}
		}
	}
	
	// 新的答题器，存入缓冲
	memcpy(RADIO.DTQ[RADIO.pLastDtq].UID, UID, 4);
	RADIO.DTQ[RADIO.pLastDtq].LastSeqNum = Seq;
	
	if(RADIO.pLastDtq < DTQ_MAX_NUM)
		RADIO.pLastDtq++;
	else
		RADIO.pLastDtq = 0;
	
	return true;
}

void RADIO_RxDataHandler(void)
{
	if(nrf_esb_read_rx_payload(&rx_payload) == NRF_SUCCESS)
	{
	}
}

uint32_t RADIO_Init(void)
{
    ret_code_t err_code;	
	
	RADIO.RxChannal = 52;
	RADIO.RxBitRate = 0;		// 0 1MHz, 1 2MHz, 2 250KHz
	
    err_code = my_rx_esb_init();
    APP_ERROR_CHECK(err_code);
    err_code = nrf_esb_start_rx();
    APP_ERROR_CHECK(err_code);	
	
	return 0;
}

uint32_t RADIO_Update(void)
{
	__disable_irq();
	
	APP_ERROR_CHECK(nrf_esb_flush_rx());
	APP_ERROR_CHECK(nrf_esb_disable());
    APP_ERROR_CHECK(my_rx_esb_init());
    APP_ERROR_CHECK(nrf_esb_start_rx());	
	
	__enable_irq();			
	
	return 0;
}




uint32_t my_rx_esb_init(void)
{
	uint32_t err_code;
	uint8_t base_addr_0[4] = {0xE7, 0xE7, 0xE7, 0xE7};
	uint8_t addr_prefix[8] = {0xE7, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8 };

	nrf_esb_config_t nrf_esb_config         = NRF_ESB_DEFAULT_CONFIG;
	nrf_esb_config.protocol                 = NRF_ESB_PROTOCOL_ESB_DPL;
	nrf_esb_config.retransmit_delay         = 600;
	nrf_esb_config.bitrate                  = (nrf_esb_bitrate_t)RADIO.RxBitRate;
	nrf_esb_config.event_handler            = nrf_esb_event_handler;
	nrf_esb_config.mode                     = NRF_ESB_MODE_PRX;
	nrf_esb_config.selective_auto_ack       = true;	
	nrf_esb_config.payload_length           = 250;

	err_code = nrf_esb_set_rf_channel(RADIO.RxChannal);		
	VERIFY_SUCCESS(err_code);

	err_code = nrf_esb_set_base_address_0(base_addr_0);
	VERIFY_SUCCESS(err_code);

	err_code = nrf_esb_set_prefixes(addr_prefix, 8);
	VERIFY_SUCCESS(err_code);
	
	err_code = nrf_esb_init(&nrf_esb_config);
	VERIFY_SUCCESS(err_code);	

	return err_code;
}















