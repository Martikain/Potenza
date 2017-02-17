/*
 * WiFi.c
 *
 * Created: 4.1.2017 16:22:45
 *  Author: Ossi
 */ 

 #include "UART.h"
 #include "define.h"

 void init_uart() {
	 // UART settings
	 UBRR0 = BAUD_9600; // Set baud rate 
	 UCSR0B |= (1 << RXEN0); // enable RX
	 UCSR0B |= (1 << TXEN0); // enable TX
	 UCSR0B |= (1 << RXCIE0); // enable RX complete interrupt
	 //UCSRnC |= (1 << UMSEL01) | (1 << UMSEL00); Asynchronous USART mode
	 UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); //Character size 8-bit
	 // 1 stop bit
	 // Sent data is updated on rising edge, received data is sampled on the falling edge
 }
 

// Send a char with UART
 void transmit(char c) {
	 // Wait for the flag to say we're good to write to the data register.
	 while(!(UCSR0A & (1 << UDRE0)));
	 UDR0 = c;
 }
 
 

// Sends a string
 void transmit_message(char message[]){

	uint8_t len = strlen(message);
	uint8_t i;
	for (i = 0; i < len; i++){
		transmit(message[i]);
	}
 }

 
// Receiving a byte interrupt
void ISR(USART_RX_vect){

	 char status, resl;
	 status = UCSR0A;
	 resl = UDR0;

	 PORTB ^= (1 << PORTB4);

	 // Virhetarkastus
	 if(status & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))){
		 return;
		 } else {
		 transmit(resl);
	 }
 }


 void transmit_number(uint16_t number) {

	char buf[6];
	sprintf(buf, "%u", number);

	transmit_message(buf);

 }