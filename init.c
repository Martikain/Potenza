/*
 * init.c
 *
 * Created: 4.2.2017 14:24:11
 *  Author: Ossi
 */ 

#include "init.h"
#include "define.h"
#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void init(){
	 
	// Distance sensor
	DDRB |= (1 << DDB0);
	
	init_button_int();
	init_distance_sensor();
	init_steering();
	init_flame_sensor();
	init_i2c();
	 
	// Set LED pin on the circuit as output
	DDRB |= (1 << LED_PIN);
	 
	// Start the counter with prescaler 1024, one pulse length is 64 ns
	// 1 cm distance produces a 59 ns pulse

	TCCR1B |=  (1 << CS12) | (1 << CS10);
	 
	sei();

	init_uart();
}

void init_button_int() {
	// *** Interrupt produced by on-board button
	PORTD |= (1 << PORTD2); // PinD2 inner pull-up
	EICRA |= (1 << ISC01); // Falling edge causes an interrupt
	EIMSK |= (1 << INT0); // INT0 enabled
}

void init_distance_sensor() {
	EICRA |= (1 << ISC11) | (1 << ISC10); // PD3 falling edge causes an interrupt
	EIMSK |= (1 << INT1); // Activates the external interrupt on PD3
}


// Initializes the PWM control for the car's front wheels
void init_steering() {	
	DDRD   |= (1 << DDD6); 
	TCCR0A |= (1 << COM0A1); // Reset OC0A (PD6) on compare match
	TCCR0A |= (1 << WGM01) | (1 << WGM00); // Fast PWM mode
	OCR0A   = 0x80; // Set the bias at 2,5 volts
	TCCR0B  |= (1 << CS00); // No prescaler, starts the counter
}


// Initializes the I2C channel used by the gyroscope
void init_i2c() {
	TWBR = 12; // First of the two prescalers of I2C, final frequency is 400 kHz
	TWAR = 0b11010001; // Set the gyroscope I2C address (ADD pin on the module is low)
}


void init_flame_sensor() {
	
	// ADC

	ADMUX |= (1 << REFS0); // Voltage reference from AVcc pin
	ADMUX |= (1 << ADLAR); //AD Left Adjust Result => 8-bit result from ADCH register
	// ADMUX = 0x00 set ADC input as ADC0 = PC0
	ADCSRA |= (1 << ADEN); // ADC enabled
	ADCSRA |= (1 << ADPS2) | (1 << ADPS0); // Prescaler 64

}