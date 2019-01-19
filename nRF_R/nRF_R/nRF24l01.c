/*
 * nRF24l01.c
 *
 * Created: 27.12.2018 16:05:31
 *  Author: Vladimir
 */ 


#include "settings.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "SPI.h"
#include "nRF24l01.h"

#define nRF_DATALENGTH 32
uint8_t rx_address[5] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 };
uint8_t tx_address[5] = { 0xC2, 0xC2, 0xC2, 0xC2, 0xC2 };
	
uint8_t nRF_data;
uint8_t nRF_counter = 0;

void nRF_write(uint8_t reg, uint8_t * data, uint8_t count) {
	nRF_SelectChip();
	SPI_byteTxRx(nRF_W_REGISTER | reg);
	for (uint8_t i = 0; i < count; i++) {
		SPI_byteTxRx(((uint8_t*) data)[i]);
	}
	nRF_DeselectChip();
}

void nRF_read(uint8_t reg, uint8_t * data, uint8_t count) {
	nRF_SelectChip();
	SPI_byteTxRx(nRF_R_REGISTER | reg);
	for (uint8_t i = 0; i < count; i++) {
		((uint8_t*) data)[i] = SPI_byteTxRx(0xFF);
	}
	nRF_DeselectChip();
}

void nRF_init(void) {
	_delay_ms(150);
			
	nRF_data = (0 << nRF_ENAA_P5) |		//Disable auto acknowledgement data pipe 5
		   (0 << nRF_ENAA_P4) |			//Disable auto acknowledgement data pipe 4
		   (0 << nRF_ENAA_P3) |			//Disable auto acknowledgement data pipe 3
		   (0 << nRF_ENAA_P2) |			//Disable auto acknowledgement data pipe 2
		   (0 << nRF_ENAA_P1) |			//Disable auto acknowledgement data pipe 1
		   (0 << nRF_ENAA_P5);			//Disable auto acknowledgement data pipe 0
	nRF_write(nRF_EN_AA, &nRF_data, 1);
	
	nRF_data = (0 << nRF_ERX_P5) |		//Disable data pipe 5
		   (0 << nRF_ERX_P4) |			//Disable data pipe 4
		   (0 << nRF_ERX_P3) |			//Disable data pipe 3
		   (0 << nRF_ERX_P2) |			//Disable data pipe 2
		   (1 << nRF_ERX_P1) |			//Enable data pipe 1
		   (0 << nRF_ERX_P0);			//Disable data pipe 0
	nRF_write(nRF_EN_RXADDR, &nRF_data, 1);
	
	nRF_data = nRF_AW_3;				//Address field width: 3 bytes
	nRF_write(nRF_SETUP_AW, &nRF_data, 1);
	
	nRF_data = nRF_ARD_250 | nRF_ARC_0;	//250us Auto Retransmit Delay; Disable Re-Transmit on fail of AA
	nRF_write(nRF_SETUP_RETR, &nRF_data, 1);
	
	nRF_data = 3;						//Frequency channel 3
	nRF_write(nRF_SETUP_CH, &nRF_data, 1);
	
	nRF_data = (0 << nRF_CONT_WAVE) |	//Disable continuous carrier transmit
		   (1 << nRF_RF_DR_LOW) |		//See: RF_DR_HIGH
		   (0 << nRF_PLL_LOCK) |		//Disable forsing PLL lock signal
		   (0 << nRF_RF_DR_HIGH) |		//RF Data Rate: 250 kbps
		   (nRF_RF_PWR_18 << nRF_PWR);	//RF output power: -18 dBm
	nRF_write(nRF_RF_SETUP, &nRF_data, 1);
		
	//nRF_write(nRF_RX_ADDR_P0, &rx_address, 5);	//Receive address data pipe 0 
	nRF_write(nRF_RX_ADDR_P1, &tx_address, 5);	//Receive address data pipe 1
	//nRF_write(nRF_RX_ADDR_P2, &data, 5);		//Receive address data pipe 2
	//nRF_write(nRF_RX_ADDR_P3, &data, 5);		//Receive address data pipe 3
	//nRF_write(nRF_RX_ADDR_P4, &data, 5);		//Receive address data pipe 4
	//nRF_write(nRF_RX_ADDR_P5, &data, 5);		//Receive address data pipe 5
	//nRF_write(nRF_TX_ADDR, &tx_address, 5);		//Transmit address
	
	nRF_data = nRF_DATALENGTH;
	nRF_write(nRF_RX_PW_P1, &nRF_data, 1);	//32 bytes in RX payload in data pipe 1
	/*nRF_data = 0;
	nRF_write(nRF_RX_PW_P0, &nRF_data, 1);	//32 bytes in RX payload in data pipe 0
	nRF_write(nRF_RX_PW_P2, &nRF_data, 1);	//0 bytes in RX payload in data pipe 2
	nRF_write(nRF_RX_PW_P3, &nRF_data, 1);	//0 bytes in RX payload in data pipe 3
	nRF_write(nRF_RX_PW_P4, &nRF_data, 1);	//0 bytes in RX payload in data pipe 4
	nRF_write(nRF_RX_PW_P5, &nRF_data, 1);	//0 bytes in RX payload in data pipe 5*/
		
	/*nRF_data = (0 << nRF_DPL_P5) |		//Disable dynamic payload length data pipe 5
		   (0 << nRF_DPL_P4) |			//Disable dynamic payload length data pipe 4
		   (0 << nRF_DPL_P3) |			//Disable dynamic payload length data pipe 3
		   (0 << nRF_DPL_P4) |			//Disable dynamic payload length data pipe 2
		   (0 << nRF_DPL_P1) |			//Disable dynamic payload length data pipe 1
		   (0 << nRF_DPL_P0);			//Disable dynamic payload length data pipe 0
	nRF_write(nRF_DYNPD, &nRF_data, 1);*/
	
	/*nRF_data = (0 << nRF_EN_DPL) |		//Disable dynamic payload length
		   (0 << nRF_EN_ACK_PAY) |		//Disable payload with ACK
		   (0 << nRF_EN_DYN_ACK);		//Disable W_TX_PAYLOAD_NOACK command
	nRF_write(nRF_FEATURE, &nRF_data, 1);*/
		
	nRF_data = (0 << nRF_MASK_RX_DR) |	//Enable RX_DR interrupt
			(1 << nRF_MASK_TX_DS) |		//Disable TX_DS interrupt
			(1 << nRF_MASK_MAX_RT) |	//Disable MAX_RT interrupt
			(1 << nRF_EN_CRC) |			//Enable CRC
			(0 << nRF_CRC0) |			//1 byte of CRC (if enabled)
			(1 << nRF_PWR_UP) |			//Power up
			(1 << nRF_PRIM_RX);			//PRX
	nRF_write(nRF_CONFIG, &nRF_data, 1);
	
	_delay_ms(2);
	//Pull up CE to start monitoring
	PORTB |= (1 << 0);
	_delay_us(150);
	
	nRF_SelectChip();
	nRF_data = SPI_byteTxRx(nRF_NOP);
	nRF_DeselectChip();
	nRF_write(nRF_STATUS, &nRF_data, 1);	
	
}

uint8_t nRF_send_message(const void *tx_message) {
	char temp[32];
	memset(temp, 0, 32);
	strcpy(temp, tx_message);
	
	// Flush TX/RX and clear TX interrupt
	nRF_write(nRF_FLUSH_RX, 0, 0);
	nRF_write(nRF_FLUSH_TX, 0, 0);
	nRF_data = (1 << nRF_TX_DS);
	nRF_write(nRF_STATUS, &nRF_data, 1);
			
	// Start SPI, load message into TX_PAYLOAD
	nRF_SelectChip();
	SPI_byteTxRx(nRF_W_TX_PAYLOAD);
	for(nRF_counter = 0; nRF_counter < nRF_DATALENGTH; nRF_counter++) {
		SPI_byteTxRx(*(uint8_t *) tx_message++);
	}
	nRF_DeselectChip();
			
	// Transmit mode
	nRF_read(nRF_CONFIG, &nRF_data, 1);
	nRF_data &=~ (1 << nRF_PRIM_RX);
	nRF_data |= (1 << nRF_PWR_UP);
	nRF_write(nRF_CONFIG, &nRF_data, 1);
	_delay_ms(2);
		
	// Send message by pulling CE high for more than 10us
	PORTB |= (1 << 0);
	_delay_us(15);
	PORTB &=~ (1 << 0);
	_delay_us(100);
	
	// Wait for message to be sent (TX_DS flag raised)	
	nRF_counter = 0;
	while(PIND & (1 << 2) != 0) {
		if(nRF_counter <= 200) {
			_delay_us(50);			
			nRF_counter++;
		}
		else {
			nRF_counter = 0;			
			break;
		}
	}
	nRF_counter = 0;
	do {
		if(nRF_counter <= 200) {
			nRF_SelectChip();
			nRF_data = SPI_byteTxRx(nRF_NOP);
			nRF_DeselectChip();
			_delay_us(50);
			nRF_counter++;
		}
		else {
			nRF_counter = 0;
			break;
		}
		
	} while(!(nRF_data & (1 << nRF_TX_DS)));
		
	
	nRF_SelectChip();
	nRF_data = SPI_byteTxRx(nRF_STATUS | nRF_W_REGISTER);
	SPI_byteTxRx(nRF_data);
	nRF_DeselectChip();	
		
	return 1;
}

uint8_t nRF_get_message(const void *tx_message) {
	nRF_counter = 0;
	nRF_SelectChip();
	nRF_data = SPI_byteTxRx(nRF_NOP);
	nRF_DeselectChip();	
	if(!(nRF_data & (1 << nRF_RX_DR))) {
		return 0;
	};
	
	//Pull down CE to stop monitoring
	PORTB &=~ (1 << 0);
		
	// Start SPI, load message from RX_PAYLOAD
	nRF_SelectChip();
	SPI_byteTxRx(nRF_R_RX_PAYLOAD);
	for(nRF_counter = 0; nRF_counter < nRF_DATALENGTH; nRF_counter++) {
		*(uint8_t *) tx_message++ = SPI_byteTxRx(nRF_NOP);
	}
	nRF_DeselectChip();
	
	// Flush TX/RX and clear RX interrupt
	nRF_write(nRF_FLUSH_RX, 0, 0);
	nRF_write(nRF_FLUSH_TX, 0, 0);
	
	//Pull up CE to start monitoring
	PORTB |= (1 << 0);
	
	nRF_read(nRF_STATUS, &nRF_data, 1);
	nRF_data |= (1 << nRF_RX_DR);
	nRF_write(nRF_STATUS, &nRF_data, 1);
}