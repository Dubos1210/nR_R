/*
 * SPI.c
 *
 * Created: 25.12.2018 0:10:09
 *  Author: Vladimir
 */ 

#include "settings.h"
#include <avr/io.h>
#include <stdint.h>
#include "SPI.h"

/********************************************
 * Функция	: инициализация SPI
 ********************************************/
void SPI_init(void) {
	SPSR |= (1<<SPIF)|(1<<WCOL)|(0<<SPI2X);
  	SPCR = (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR1)|(0<<SPR0);
  	//SPCR = 0x50;
}

/********************************************
 * Функция		: отправка и прием байта
 * Аргументы	: байт для отправки
 * Ответ		: принятый байт
 ********************************************/
uint8_t SPI_byteTxRx(uint8_t data) {
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	
	return(data);
}