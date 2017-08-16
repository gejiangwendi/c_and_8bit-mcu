#ifndef _RXDATA_H_
#define _RXDATA_H_

#include "typedefine.h"


extern bit RX_pack_ok; 
extern u8 RX_data[20];
extern u8 send_data[13];
extern u8 receive_data[13];

extern u8 RX_ptr_buf;
extern u8 send_data_buf;
extern u8 chksum_send;
extern u8 data_ptr;
extern bit In_send;

void	RxData 			(void);


#endif