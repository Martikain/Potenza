/*
 * WiFi_led.c
 *
 * Created: 4.1.2017 12:42:59
 * Author : Ossi
 */ 


 // Etäisyysanturin TRIG-pin = PB0 (alin pisimmästä piikkirimasta)
 // Etäisyysanturin ECHO-pin = PD3 (5. pinni 8-leveyksisestä piikkirimasta)

#include "define.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "WiFi.h"
#include "HCSR1.h"
#include "init.h"


int8_t read_adc();
//***************************** MAIN ******************************************

int main(void)
{
	init();
	uint8_t adc;

    while (1) 
    {

		_delay_ms(1000);
		adc = read_adc();
		transmit_message("ADC = ");
		transmit_number(adc);
		transmit_message("\r\n");

    }
}

//*****************************************************************************

// Reads the 8-bit ADC register
int8_t read_adc(){
	ADCSRA |= (1 << ADSC); //start AD conversion
	while ( ADCSRA & (1 << ADSC) );

	return ADCH;
}
