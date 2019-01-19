/*
 * settings.h
 *
 * Created: 21.12.2018 15:33:56
 *  Author: Vladimir
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_

#define F_CPU 8000000UL

#define LED_ON() PORTD |= (1<<4)
#define LED_OFF() PORTD &=~ (1<<4)

#endif /* SETTINGS_H_ */