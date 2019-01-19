/*
 * UART.h
 *
 * Created: 04.01.2019 11:17:34
 *  Author: Vladimir
 */

/* UART Library for Atmel AVR v0.4
 *  UART_init(9600);           //������������� UART �� �������� 9600 ���
 *  UART_send(0x**);           //�������� ����� 0x**
 *  UART_send_BK();            //�������� ������� "������� �������" (0x0D 0x0A)
 *  UART_send_string("Hello"); //�������� ������ Hello
 */

#ifndef UART_H_
#define UART_H_

void UART_init(uint32_t baud);
void UART_send(uint8_t s);
void UART_send_BK(void);
void UART_send_string(uint8_t *data);
void UART_send_long(int32_t data);

#endif /* UART_H_ */