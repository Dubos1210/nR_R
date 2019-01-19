/*
 * SPI.h
 *
 * Created: 25.12.2018 0:10:19
 *  Author: Vladimir
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void SPI_init(void);
uint8_t SPI_byteTxRx(uint8_t data);

#endif /* SPI_H_ */