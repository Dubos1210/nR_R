/*
 * UART.c
 *
 * Created: 04.01.2019 11:17:24
 *  Author: Vladimir
 */

#include "settings.h"
#include <avr/io.h>
#include <stdint.h>
#include "UART.h"

/********************************************************************
 * �������	: ������������� UART
 * ��������	: baudrate (300, 600, 1 200, 2 400, 4 800, 9 600, 19 200,
			  38 400, 57 600, 115 200, 230 400, 460 800, 921 600)
 ********************************************************************/
void UART_init(uint32_t baud) {	
	unsigned int UART_ubrr = F_CPU / 16 / baud - 1;
	UBRR0H = UART_ubrr >> 8;
	UBRR0L = UART_ubrr;
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
}

/********************************************************************
 * �������	: �������� �����
 * ��������	: ���� ��� ��������
 ********************************************************************/
void UART_send(uint8_t s) {
	while(!(UCSR0A & (1<<UDRE0))) {};
	UDR0 = s;
}

/********************************************************************
 * �������	: �������� ������� "������� �������" (0x0D, 0x0A)
 ********************************************************************/
void UART_send_BK(void) {
	UART_send(0x0D);
	UART_send(0x0A);
}

/********************************************************************
 * �������	: �������� ������
 * ��������	: ������ ��� ��������
 ********************************************************************/
void UART_send_string(uint8_t *data) {
	unsigned char c;
	while(( c = *data++ )) {
		UART_send(c);
	}
}

/********************************************************************
 * �������	: �������� ������ �����
 * ��������	: ����� ��� ��������
 ********************************************************************/
void UART_send_long(int32_t data) {
	uint32_t d;	
	uint8_t t;
	if(data < 0) {
		UART_send(0x2D);
		d = data * (-1);
	}
	else {
		UART_send(0x20);
		d = data;
	}
	
	t = d / 100000000000000000;
	d %= 100000000000000000;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	t = d / 1000000000000000;
	d %= 1000000000000000;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	t = d / 10000000000000;
	d %= 10000000000000;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	t = d / 100000000000;
	d %= 100000000000;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	t = d / 1000000000;
	d %= 1000000000;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	t = d / 10000000;
	d %= 10000000;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	t = d / 100000;
	d %= 100000;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	t = d / 1000;
	d %= 1000;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	t = d / 10;
	UART_send((t / 10) + 0x30);
	UART_send((t % 10) + 0x30);
	UART_send((d % 10) + 0x30);
	
}