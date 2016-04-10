/*
  pick_block(108); //upper waste block
  pick_block(97); //middle waste block
  pick_block(84); //lower waste block
  pick_block(90); //upper weight block
  pick_block(82); //lower weight block
  servo_1(120);
  servo_1(82);
  while(1);
  _delay_ms(2000);
  servo_1_free(); 
  servo_2_free();
  servo_3_free();
*/
#include "buzzer.h"
unsigned char i = 0;
unsigned char grip_switch = 0x40;

void servo1_pin_config (void)
{
 DDRB  = DDRB | 0x20;  //making PORTB 5 pin output
 PORTB = PORTB | 0x20; //setting PORTB 5 pin to logic 1
}

void servo2_pin_config (void)
{
 DDRB  = DDRB | 0x40;  //making PORTB 6 pin output
 PORTB = PORTB | 0x40; //setting PORTB 6 pin to logic 1
 DDRL  = DDRL | 0xBF;  //making PORTL 6 pin input
 PORTL = PORTL | 0x40; //PORTL 6 internal pull-up enabled
}

//TIMER1 initialization in 10 bit fast PWM mode  
//prescale:256
// WGM: 7) PWM 10bit fast, TOP=0x03FF
// actual value: 52.25Hz 
void timer1_init(void)
{
 TCCR1B = 0x00; //stop
 TCNT1H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
 TCNT1L = 0x01;	//Counter low value to which OCR1xH value is to be compared with
 OCR1AH = 0x03;	//Output compare Register high value for servo 1
 OCR1AL = 0xFF;	//Output Compare Register low Value For servo 1
 OCR1BH = 0x03;	//Output compare Register high value for servo 2
 OCR1BL = 0xFF;	//Output Compare Register low Value For servo 2
 OCR1CH = 0x03;	//Output compare Register high value for servo 3
 OCR1CL = 0xFF;	//Output Compare Register low Value For servo 3
 ICR1H  = 0x03;	
 ICR1L  = 0xFF;
 TCCR1A = 0xAB; /*{COM1A1=1, COM1A0=0; COM1B1=1, COM1B0=0; COM1C1=1 COM1C0=0}
 					For Overriding normal port functionality to OCRnA outputs.
				  {WGM11=1, WGM10=1} Along With WGM12 in TCCR1B for Selecting FAST PWM Mode*/
 TCCR1C = 0x00;
 TCCR1B = 0x0C; //WGM12=1; CS12=1, CS11=0, CS10=0 (Prescaler=256)
}

void servo_1(unsigned char degrees)  
{
 float PositionPanServo = 0;
  PositionPanServo = ((float)degrees / 1.86) + 35.0;
 OCR1AH = 0x00;
 OCR1AL = (unsigned char) PositionPanServo;
}

void servo_2(unsigned char degrees)
{
 float PositionTiltServo = 0;
 PositionTiltServo = ((float)degrees / 1.86) + 35.0;
 OCR1BH = 0x00;
 OCR1BL = (unsigned char) PositionTiltServo;
}

//servo_free functions unlocks the servo motors from the any angle 
//and make them free by giving 100% duty cycle at the PWM. This function can be used to 
//reduce the power consumption of the motor if it is holding load against the gravity.

void servo_1_free (void)
{
 OCR1AH = 0x03; 
 OCR1AL = 0xFF; //Servo 1 off
}

void servo_2_free (void)
{
 OCR1BH = 0x03;
 OCR1BL = 0xFF; //Servo 2 off
}

void place_block()
{
	for (i = 160; i > 84; i--)
	{
		servo_1(i);
		_delay_ms(60);
	}
	servo_2(100);
	_delay_ms(500);
	for (i = 84; i < 130; i++)
	{
		servo_1(i);
		_delay_ms(30);
	}
	servo_2(120);
}

void place_to_sort()
{
	for (i = 160; i > 84; i--)
	{
		servo_1(i);
		_delay_ms(30);
	}
	servo_2(85);
	_delay_ms(500);
	for (i = 84; i < 130; i++)
	{
		servo_1(i);
		_delay_ms(30);
	}
}

void pick_block(int angle)
{
	for (i = 130; i > angle; i--)
	{
		servo_1(i);
		_delay_ms(30);
	}
	 i=120;
	 //buzzer_on();
	 while(grip_switch == 0x40)
	 {
		 if (i == 55){
			 buzzer_off();
			break;
		 }			
		 servo_2(i);
		 _delay_ms(45);
		 i--;
		 grip_switch = PINL;
		 grip_switch = grip_switch & 0x40;
		
	 }
	  buzzer_on();
	 _delay_ms(40);
	buzzer_off();
	 //servo_2(i-=2);
	 //_delay_ms(30);
	for (i = angle; i < 160; i++)
	{
		servo_1(i);
		_delay_ms(25);
	}
}

void pick_at_sort()
{
	for (i = 130; i > 86; i--)
	{
		servo_1(i);
		_delay_ms(30);
	}
	i=90;
	//buzzer_on();
	while(grip_switch == 0x40)
	{
		if (i == 55){
			buzzer_off();
			break;
		}
		servo_2(i);
		_delay_ms(45);
		i--;
		grip_switch = PINL;
		grip_switch = grip_switch & 0x40;
		
	}
	buzzer_on();
	_delay_ms(40);
	buzzer_off();
	//servo_2(i-=2);
	//_delay_ms(30);
	for (i = 86; i < 160; i++)
	{
		servo_1(i);
		_delay_ms(25);
	}
}

void drop_weight()
{
	for (i = 120; i > 108; i--)
	{
		servo_1(i);
		_delay_ms(30);
	}
	servo_2(120);
	_delay_ms(100);
	for (i = 108; i < 120; i++)
	{
		servo_1(i);
		_delay_ms(30);
	}
}
