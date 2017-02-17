/*
 * WiFi.h
 *
 * Created: 4.1.2017 16:23:02
 *  Author: Ossi
 */ 


#ifndef UART_H_
#define UART_H_

 #include <avr/io.h>
 #include <stdio.h>
 #include <string.h>
 

void init_uart();
void transmit(char c);
void transmit_message(char message[]);
void transmit_number(uint16_t number);

#endif /* UART_H_ */