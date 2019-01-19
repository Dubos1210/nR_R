/*
 * nRF24l01.h
 *
 * Created: 27.12.2018 16:05:41
 *  Author: Vladimir
 */ 


#ifndef NRF24L01_H_
#define NRF24L01_H_

#define nRF_SelectChip()	PORTB &=~ (1<<1)
#define nRF_DeselectChip()	PORTB |= (1<<1)

//Register map
#define nRF_CONFIG		0x00
	#define nRF_MASK_RX_DR	6
	#define nRF_MASK_TX_DS	5
	#define nRF_MASK_MAX_RT	4
	#define nRF_EN_CRC		3
	#define nRF_CRC0		2
	#define nRF_PWR_UP		1
	#define nRF_PRIM_RX		0			
#define nRF_EN_AA		0x01
	#define nRF_ENAA_P5		5
	#define nRF_ENAA_P4		4
	#define nRF_ENAA_P3		3
	#define nRF_ENAA_P2		2
	#define nRF_ENAA_P1		1
	#define nRF_ENAA_P0		0
#define nRF_EN_RXADDR	0x02		
	#define nRF_ERX_P5		5
	#define nRF_ERX_P4		4
	#define nRF_ERX_P3		3
	#define nRF_ERX_P2		2
	#define nRF_ERX_P1		1
	#define nRF_ERX_P0		0
#define nRF_SETUP_AW	0x03
	#define nRF_AW_3		0b00000001
	#define nRF_AW_4		0b00000010
	#define nRF_AW_5		0b00000011
#define nRF_SETUP_RETR	0x04
	#define nRF_ARD_250		0b00000000
	#define nRF_ARD_500		0b00010000
	#define nRF_ARD_750		0b00100000
	#define nRF_ARD_1000	0b00110000
	#define nRF_ARD_1250	0b01000000
	#define nRF_ARD_1500	0b01010000
	#define nRF_ARD_1750	0b01100000
	#define nRF_ARD_2000	0b01110000
	#define nRF_ARD_2250	0b10000000
	#define nRF_ARD_2500	0b10010000
	#define nRF_ARD_2750	0b10100000
	#define nRF_ARD_3000	0b10110000
	#define nRF_ARD_3250	0b11000000
	#define nRF_ARD_3500	0b11010000
	#define nRF_ARD_3750	0b11100000
	#define nRF_ARD_4000	0b11110000
	#define nRF_ARC_0		0b00000000
	#define nRF_ARC_1		0b00000001
	#define nRF_ARC_2		0b00000010
	#define nRF_ARC_3		0b00000011
	#define nRF_ARC_4		0b00000100
	#define nRF_ARC_5		0b00000101
	#define nRF_ARC_6		0b00000110
	#define nRF_ARC_7		0b00000111
	#define nRF_ARC_8		0b00001000
	#define nRF_ARC_9		0b00001001
	#define nRF_ARC_10		0b00001010
	#define nRF_ARC_11		0b00001011
	#define nRF_ARC_12		0b00001100
	#define nRF_ARC_13		0b00001101
	#define nRF_ARC_14		0b00001110
	#define nRF_ARC_15		0b00001111
#define nRF_SETUP_CH	0x05
#define nRF_RF_SETUP	0x06
	#define nRF_CONT_WAVE	7
	#define nRF_RF_DR_LOW	5
	#define nRF_PLL_LOCK	4
	#define nRF_RF_DR_HIGH	3
	#define nRF_PWR			1
		#define nRF_RF_PWR_18	0b00000000
		#define nRF_RF_PWR_12	0b00000001
		#define nRF_RF_PWR_10	0b00000010
		#define nRF_RF_PWR_0	0b00000011
#define nRF_STATUS		0x07
	#define nRF_RX_DR		6
	#define nRF_TX_DS		5
	#define nRF_MAX_RT		4
	#define nRF_RX_P_NO		1
		#define nRF_RX_P0		0b00000000
		#define nRF_RX_P1		0b00000001
		#define nRF_RX_P2		0b00000010
		#define nRF_RX_P3		0b00000011
		#define nRF_RX_P4		0b00000100
		#define nRF_RX_P5		0b00000101
		#define nRF_RX_NU		0b00000110
		#define nRF_RX_EMPTY	0b00000111
	#define nRF_TX_FULL		0
#define nRF_OBSERVE_TX	0x08
	#define nRF_PLOS_CNT	4
	#define nRF_ARC_CNT		0
#define nRF_RPD			0x09
	#define nRF_RPD_RPD		0
#define nRF_RX_ADDR_P0	0x0A
#define nRF_RX_ADDR_P1	0x0B
#define nRF_RX_ADDR_P2	0x0C
#define nRF_RX_ADDR_P3	0x0D
#define nRF_RX_ADDR_P4	0x0E
#define nRF_RX_ADDR_P5	0x0F
#define nRF_TX_ADDR		0x10
#define nRF_RX_PW_P0	0x11
#define nRF_RX_PW_P1	0x12
#define nRF_RX_PW_P2	0x13
#define nRF_RX_PW_P3	0x14
#define nRF_RX_PW_P4	0x15
#define nRF_RX_PW_P5	0x16
#define nRF_FIFO_STATUS	0x17
	#define nRF_TX_REUSE_F	6
	#define nRF_TX_FULL_F	5
	#define nRF_TX_EMPTY_F	4
	#define nRF_RX_FULL_F	1
	#define nRF_RX_EMPTY_F	0	
#define nRF_DYNPD		0x1C
	#define nRF_DPL_P5		5
	#define nRF_DPL_P4		4
	#define nRF_DPL_P3		3
	#define nRF_DPL_P2		2
	#define nRF_DPL_P1		1
	#define nRF_DPL_P0		0
#define nRF_FEATURE		0x1D
	#define nRF_EN_DPL		2
	#define nRF_EN_ACK_PAY	1
	#define nRF_EN_DYN_ACK	0

//Commands
#define nRF_REGISTER_MASK		0b00011111
#define nRF_R_REGISTER			0b00000000
#define nRF_W_REGISTER			0b00100000
#define nRF_R_RX_PAYLOAD		0b01100001
#define nRF_W_TX_PAYLOAD		0b10100000
#define nRF_FLUSH_TX			0b11100001
#define nRF_FLUSH_RX			0b11100010
#define nRF_REUSE_TX_PL			0b11100011
#define nRF_ACTIVATE			0b01010000
#define nRF_R_RX_PL_WID			0b01100000
#define nRF_ACK_PAYLOAD_MASK	0b00000111
#define nRF_W_ACK_PAYLOAD		0b10101000
#define nRF_W_TX_PAYLOAD_NOACK	0b10110000
#define nRF_NOP					0b11111111

void nRF_write(uint8_t reg, uint8_t * data, uint8_t count);
void nRF_read(uint8_t reg, uint8_t * data, uint8_t count);
void nRF_init(void);
uint8_t nRF_send_message(const void *tx_message);
uint8_t nRF_get_message(const void *rx_message);

#endif /* NRF24L01_H_ */