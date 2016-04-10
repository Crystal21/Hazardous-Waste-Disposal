#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void motion_pin_config (void) 
{
 DDRA = DDRA | 0x0F;
 PORTA = PORTA & 0xF0;
 DDRL = DDRL | 0x18;  
 PORTL = PORTL | 0x18;
}


void timer5_init()
{
	TCCR5B = 0x00;	
	TCNT5H = 0xFF;	
	TCNT5L = 0x01;	
	OCR5AH = 0x00;	
	OCR5AL = 0xFF;	
	OCR5BH = 0x00;	
	OCR5BL = 0xFF;	
	OCR5CH = 0x00;	
	OCR5CL = 0xFF;	
	TCCR5A = 0xA9;	
	TCCR5B = 0x0B;	
}

void motion_set (unsigned char Direction)
{
 unsigned char PortARestore = 0;

 Direction &= 0x0F; 			
 PortARestore = PORTA; 			
 PortARestore &= 0xF0; 			
 PortARestore |= Direction; 	
 PORTA = PortARestore; 			
}


void forward (void)
{
  motion_set(0x06);
}

void back (void)
{
  motion_set(0x09);
}

void left (void)
{
  motion_set(0x05);
}

void right (void) 
{
  motion_set(0x0A);
}

void soft_left (void) 
{
 motion_set(0x04);
}
void stop()
{
motion_set(0x00);
}

void soft_right (void) //Left wheel forward, Right wheel is stationary
{
	motion_set(0x02);
}

void soft_left_2 (void) //Left wheel backward, right wheel stationary
{
	motion_set(0x01);
}

void soft_right_2 (void) //Left wheel stationary, Right wheel backward
{
	motion_set(0x08);
}

void velocity (unsigned char left_motor, unsigned char right_motor)
{
	OCR5AL = (unsigned char)left_motor;
	OCR5BL = (unsigned char)right_motor;
}
