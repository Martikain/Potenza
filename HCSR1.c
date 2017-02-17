/*
 * HCSR1.c
 *
 * HCSR1-etäisyysanturin vaatimat keskeytykset
 *
 *
 *
 * Created: 4.2.2017 14:00:51
 *  Author: Ossi
 */ 

#include "HCSR1.h"
#include "define.h"
#include "UART.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint16_t timer_val1 = 0;
uint16_t timer_val2 = 0;

 // Button interrupt that sends a request to the distance sensor
 ISR(INT0_vect){
	 
	 // Wait for the button press to stop oscillating
	 _delay_ms(50);
	 while(!(PIND & (PIND2))){
		 asm volatile("nop");
	 }
	 _delay_ms(50);


	 // Request for the sensor
	 
	 // Led on (just for debug)
	 PORTB |= (1 << LED_PIN);
	 
	 // Send the request
	 PORTB |= (1 << TRIG_PIN);
	 _delay_ms(10);
	 PORTB &= !(1 << TRIG_PIN);
	 
	 // Turn off the led
	 PORTB &= !(1 << LED_PIN);
	 
	 return;
 }


 // The interrupt notices the echo signal from the sensor and calculates the
 // distance in centimeters and sends it through UART to PC
 ISR(INT1_vect){
	 timer_val1 = COUNTER;
	 while(PIND & (1 << ECHO_PIN));
	 timer_val2 = COUNTER;

	 uint16_t distance = (timer_val2 - timer_val1) * KERROIN;
	 
	 transmit_message("Distance is: ");
	 transmit_number(distance);
	 transmit_message(" cm");
	 transmit('\r');
	 transmit('\n');
 }