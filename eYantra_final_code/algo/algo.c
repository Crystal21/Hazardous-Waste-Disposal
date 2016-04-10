/*
 * algo.c
 *
 * Created: 2/12/2016 4:57:50 PM
 *  Author: Om
 */ 

#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "adc.h"
//#include "buzzer.h"
#include "colorsensor.h"
#include "encoder.h"
#include "lcd.h"
#include "servo.h"
#include "node.h"
//#include "velocity.h"

int detect_third_waste(){
	if (sortedFlag[0] == 1 && sortedFlag[1] == 2) {
		return 3;
	} else if (sortedFlag[0] == 2 && sortedFlag[1] == 3) {
		return 1;
	} else 
		return 2;	
}


int main(void)
{
	init_devices_color();
	lcd_set_4bit();
	color_sensor_scaling();
	init_devices();
	lcd_port_config ();
	lcd_init();
	buzzer_pin_config();
	motion_pin_config ();
	timer5_init();
	adc_pin_config ();
	adc_init();
	servo1_pin_config();
	servo2_pin_config();
	timer1_init();
	//servo_1(120);
	//servo_2(90);
	/*
	fw_follow_black_line();
	//while(1);
	stop();
	_delay_ms(10000);
	fw_follow_black_line();*/
	
	_delay_ms(100);
	/************************FIRST RUN*******************************/

	node0_0(4,90);		//initial 180 degrees turn
	node0_0(1,90);
	node_m1_0(2);		//goes forward
	node_m2_0(1);	
	node_m1_0(3);
	
	forward_mm(30);		
	
	node0_0(0,90);
	velocity(180,180);
	//fw_follow_black_line();
	node_0_1(0,1);
	node_0_1(1,0);
	node_m1_1(0,1);
	node_0_1(2,0);			//comes back

	/**********************************************************************************/
	
	/************************SECOND RUN**********************************/
	
	//fw_follow_black_line();
		
		node0_0(5,90);		
		//node0_0(1,90);
		node_m1_0(2);		//goes forward
		node_m2_0(1);
		node_m1_0(3);
		node0_0(0,90);
	
		if(sortedFlag[1] == b_flag){
			buzzer_on();
			_delay_ms(200);
			buzzer_off();
			node_0_1(0,0);
			left_degrees(176,1);
			fw_follow_black_line();	
		}
		else if(sortedFlag[1] == c_flag){
			node_0_1(1,0);
			node_m1_1(0,0);
			node_0_1(2,0);
		}
		else{
			node_0_1(2,0);
			node_1_1(2);
			node_2_1(0,90);
			node_0_1(2,0);			//comes back
		}
	
	//node_0_1(2);			//comes back
	
	/**********************************************************************************/
	/************************THIRD RUN**********************************************/
	//fw_follow_black_line();
	node0_0(6,90);
	
		if(detect_third_waste() == b_flag){
			buzzer_on();
			_delay_ms(200);
			buzzer_off();
			node_0_1(0,0);
			//left_degrees(160,1);
			//fw_follow_black_line();
		}
		else if(detect_third_waste() == c_flag){
			node_0_1(1,0);
			node_m1_1(0,0);
			//node_0_1(2,0);
		}
		else{
			node_0_1(2,0);
			node_1_1(2);
			node_2_1(0,90);
			//node_0_1(2,0);			//comes back
		}
		buzzer_on();
		_delay_ms(6000);
		buzzer_off();
	
	/**********************************************************************************/
	return 0;
}