/*
 * init.h
 *
 * Created: 4.2.2017 14:24:34
 *  Author: Ossi
 */ 


#ifndef INIT_H_
#define INIT_H_

	init_button_int();
	init_distance_sensor();
	init_steering();
	init_flame_sensor();
	init_i2c();

void init();
void init_button_int();
void init_distance_sensor();
void init_steering();
void init_i2c();
void init_flame_sensor();


#endif /* INIT_H_ */