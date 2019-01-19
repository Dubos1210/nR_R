/*
 * nRF_R.c
 *
 * Created: 19.01.2019 16:03:59
 *  Author: Vladimir
 */ 

#include "settings.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "SPI.h"
#include "nRF24l01.h"

char message[32];
int i = 0;

int main(void)
{
	_delay_ms(100);
	
	DDRB  |= (1<<5)|(0<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);
	PORTB |= (1<<5)|(1<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0);
	DDRC  |= (0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0);
	PORTC |= (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);
	DDRD  |= (0<<7)|(0<<6)|(0<<5)|(1<<4)|(0<<3)|(0<<2)|(1<<1)|(0<<0);
	PORTD |= (1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)|(0<<1)|(1<<0);
	
	UART_init(38400);
	UART_send_string("\r\n");
	UART_send_string("RosCanSat 2.4 GHz receiver\r\n");
	UART_send_string("Made by \"Intellect\" from Feodosia, Crimea\r\n");
	
	//SPI
	SPI_init();
	
	//nRF
	nRF_init();
	
	UART_send_string("Ready...\r\n");
	sei();
	
	_delay_ms(1000);
	LED_OFF();
	
    while(1)
    {
	    while(PIND & (1<<2)) {};
			
		LED_ON();
        nRF_get_message(&message);
		for(i = 0; i < 32; i++) {
			UART_send(message[i]);
		}
		LED_OFF();
    }
}