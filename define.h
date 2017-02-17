/*
 * define.h
 *
 * Created: 4.2.2017 14:01:45
 *  Author: Ossi
 */ 

 #ifndef DEFINE_H
 #define DEFINE_H

 #define TRIG_PIN PINB0
 #define ECHO_PIN PIND3
 #define LED_PIN PINB4
 #define COUNTER TCNT1
 #define KERROIN 64/59
 #define BAUD_9600 103
 #define OHJAUS_COUNTER OCR0A

 // I2C
 #define SDA PINC4
 #define SCL PINC5
 #define I2C_DATA TWDR

 #define F_CPU 16000000

 #endif
