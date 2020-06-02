

#ifndef __SERIALLOG__
#define __SERIALLOG__

#define RX_BUFFER_LENGTH 1024

typedef struct
{
    uint8_t receive_flag:1;
    uint8_t dmaSend_flag:1;
    uint16_t rx_len;
    uint8_t usart_DMA_RX_Buffer[RX_BUFFER_LENGTH];

}USART_DMA_REC_TYPE;

void send_data_dma()

#endif