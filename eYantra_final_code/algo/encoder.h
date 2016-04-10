

#include "velocity.h"
#include "line.h"

volatile unsigned long int ShaftCountLeft = 0; //to keep track of left position encoder
volatile unsigned long int ShaftCountRight = 0; //to keep track of right position encoder
volatile unsigned int Degrees; //to accept angle in degrees for turning
int left_dir = -1, right_dir = 1;


void init_devices()
{
	cli(); //Clears the global interrupt
	port_init();  //Initializes all the ports
	left_position_encoder_interrupt_init();
	right_position_encoder_interrupt_init();
	sei();   // Enables the global interrupt
}

void left_encoder_pin_config (void)
{
	DDRE  = DDRE & 0xEF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x10; //Enable internal pull-up for PORTE 4 pin
}

//Function to configure INT5 (PORTE 5) pin as input for the right position encoder
void right_encoder_pin_config (void)
{
	DDRE  = DDRE & 0xDF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x20; //Enable internal pull-up for PORTE 4 pin
}

//Function to initialize ports
void port_init()
{
	motion_pin_config(); //robot motion pins config
	left_encoder_pin_config(); //left encoder pin config
	right_encoder_pin_config(); //right encoder pin config
}

void left_position_encoder_interrupt_init (void) //Interrupt 4 enable
{
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x02; // INT4 is set to trigger with falling edge
	EIMSK = EIMSK | 0x10; // Enable Interrupt INT4 for left position encoder
	sei();   // Enables the global interrupt
}

void right_position_encoder_interrupt_init (void) //Interrupt 5 enable
{
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x08; // INT5 is set to trigger with falling edge
	EIMSK = EIMSK | 0x20; // Enable Interrupt INT5 for right position encoder
	sei();   // Enables the global interrupt
}

//ISR for right position encoder
ISR(INT5_vect)
{
	ShaftCountRight++;  //increment right shaft position count
}


//ISR for left position encoder
ISR(INT4_vect)
{
	ShaftCountLeft++;  //increment left shaft position count
}

void linear_distance_mm(unsigned int DistanceInMM)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = DistanceInMM / 5.338; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
	
	ShaftCountRight = 0;
	while(1)
	{
		if(ShaftCountRight > ReqdShaftCountInt)
		{
			break;
		}
	}
	stop(); //Stop robot
}

void right_angle()
{
	forward_mm(20);
	right();
	angle_rotate(90);
	while(Left_white_line > 20)
	{
		left();
		_delay_ms(50);
		break;
	}
	stop();
}

void left_angle()
{
	left();
	angle_rotate(88);
	while(Right_white_line > 30)
	{
		right();
		_delay_ms(50);
		break;
	}
	stop();
}

void forward_mm(unsigned int DistanceInMM)
{
	forward();
	linear_distance_mm(DistanceInMM);
}

void backward_mm(unsigned int DistanceInMM) {
	back();
	linear_distance_mm(DistanceInMM);
}
//Function used for turning robot by specified degrees
void angle_rotate(unsigned int Degrees,int k)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = (float) Degrees/ 4.090; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
	ShaftCountRight = 0;
	ShaftCountLeft = 0;

	while (1)
	{
		
		if((ShaftCountRight >= ReqdShaftCountInt) | (ShaftCountLeft >= ReqdShaftCountInt) | ADC_Conversion(k) > 46)
		break;
	}


	stop(); //Stop robot
}

void flag_angle_rotate(unsigned int Degrees)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = (float) Degrees/ 4.090; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
	ShaftCountRight = 0;
	ShaftCountLeft = 0;

	while (1)
	{
		if((ShaftCountRight >= ReqdShaftCountInt) | (ShaftCountLeft >= ReqdShaftCountInt))
		break;
	}


	stop(); //Stop robot
}

void left_degrees(unsigned int Degrees,int flag)
{
	
	forward_mm(40);
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	left(); //Turn left
	_delay_ms(300);
	
	if(flag==0){
		angle_rotate(Degrees,3);		//normal rotation
	}
	else{
		flag_angle_rotate(Degrees);		//rotation at flag
	}
	
	buzzer_on();
	_delay_ms(50);
	buzzer_off();

	//adjust_bot(Left_white_line,Center_white_line,Right_white_line);

}
void right_degrees(unsigned int Degrees,int flag)
{
	
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	forward_mm(50);
	right(); //Turn left
	_delay_ms(300);
	if(flag==0){
		angle_rotate(Degrees,1);		//normal rotation
	}
	else{
		flag_angle_rotate(Degrees);		//rotation at flag
	}
	buzzer_on();
	_delay_ms(50);
	buzzer_off();


	//adjust_bot(Left_white_line,Center_white_line,Right_white_line);

}
void rotate_at_flag() {
	left_degrees(88,1);//105
	forward_mm(20);//30
	right_degrees(179,1);//195/178
	forward_mm(5);//19
	_delay_ms(500);
	stop();
	velocity(255,255);
	
}
void soft_left_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_left(); //Turn soft left
	Degrees=Degrees*2;
	angle_rotate(Degrees,3);
}

void soft_right_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_right(); //Turn soft right
	Degrees=Degrees*2;
	angle_rotate(Degrees,1);
}

void soft_left_2_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_left_2(); //Turn reverse soft left
	Degrees=Degrees*2;
	angle_rotate(Degrees,3);
}

void soft_right_2_degrees(unsigned int Degrees)
{
	// 176 pulses for 360 degrees rotation 2.045 degrees per count
	soft_right_2(); //Turn reverse soft right
	Degrees=Degrees*2;
	angle_rotate(Degrees,1);
}