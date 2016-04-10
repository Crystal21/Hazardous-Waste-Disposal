//l=11 centr=8 r=13 ; for speed=200 kp=10,ki=0.2,kd=0.45 with offset of 20 at 8:20pm also with kp=10 ki=0.2 and kd=0.45 for day timeKp=8,Ki=0.18,Kd=0.4;
unsigned char Left_white_line = 0;
unsigned char Center_white_line = 0;
unsigned char Right_white_line = 0;
float Kp=10,Ki=0.205,Kd=0.4;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int initial_motor_speed=200,left_motor_speed,right_motor_speed;

void print_sensor(char row, char coloumn,unsigned char channel)
{
	
	int ADC_Value = ADC_Conversion(channel);
	lcd_print(row, coloumn, ADC_Value, 3);
}

void fw_control_motor_speed()
{
	left_motor_speed = initial_motor_speed + PID_value;
	right_motor_speed = initial_motor_speed - PID_value + 20;
	if(left_motor_speed<=0)
	{
		left_motor_speed=0;
	}
	if (right_motor_speed<=0)
	{
		right_motor_speed=0;
	}
	if(left_motor_speed>=255)
	{
		left_motor_speed=255;
	}
	if (right_motor_speed>=255)
	{
		right_motor_speed=255;
	}
	forward();
	velocity(left_motor_speed,right_motor_speed);
}
void bw_control_motor_speed()
{
	left_motor_speed = initial_motor_speed + PID_value;
	right_motor_speed = initial_motor_speed - PID_value;
	if(left_motor_speed<=0)
	{
		left_motor_speed=0;
	}
	if (right_motor_speed<=0)
	{
		right_motor_speed=0;
	}
	if(left_motor_speed>=255)
	{
		left_motor_speed=255;
	}
	if (right_motor_speed>=255)
	{
		right_motor_speed=255;
	}
	back();
	velocity(left_motor_speed,right_motor_speed);
}

void black_line()
{
	Left_white_line = ADC_Conversion(3);
	Center_white_line = ADC_Conversion(2);
	Right_white_line = ADC_Conversion(1);
	print_sensor(1,1,3);	//Prints value of White Line Sensor1
	print_sensor(1,5,2);	//Prints Value of White Line Sensor2
	print_sensor(1,9,1);	//Prints Value of White Line Sensor3
	
	if(Left_white_line<=45 && Center_white_line<=16 && Right_white_line>46)
	{
		error=2;
	}
	else if(Left_white_line<=45 && Center_white_line>46 && Right_white_line>46)
	{
		error=1;
	}
	else if(Left_white_line<=45 && Center_white_line>46 && Right_white_line<=45)
	{
		error=0;
	}
	else if(Left_white_line>46 && Center_white_line>46 && Right_white_line<=45)
	{
		error=-1;
	}
	else if(Left_white_line>46 && Center_white_line<=45 && Right_white_line<=45)
	{
		error=-2;
	}
	else if(Left_white_line<=45 && Center_white_line<=45 && Right_white_line<=45)
	{
		{
			if(error==-2)
			{
				error=-3;
			}
			else
			{
				error=3;
			}

		}
	}
}
void calculate_pid()
{
	P = error;
	I = I + previous_I;
	D = error - previous_error;
	
	PID_value = (Kp*P) + (Ki*I) + (Kd*D);
	
	previous_I=I;
	previous_error=error;
}
void fw_follow_black_line() {
		while(1)
		{				
			black_line();
			calculate_pid();
			fw_control_motor_speed();
			if ((Left_white_line+Right_white_line+Center_white_line) >= 228) {/*		//240 added
				//buzzer_on();
				stop();
				_delay_ms(200);
				if(Left_white_line>90 && Center_white_line>90 || Right_white_line<25)
				{
					soft_left_degrees(4);
					_delay_ms(50);
				}
				else if(Left_white_line<25 || Center_white_line>90 && Right_white_line>90)
				{
					soft_right_degrees(4);
					_delay_ms(50);
				}*/
			buzzer_on();
			_delay_ms(30);
			buzzer_off();
				break;
			}
		}
		stop();
		
}
void bw_follow_black_line() {
	while(1)
	{
		
		black_line();
		calculate_pid();
		bw_control_motor_speed();
		if ((Left_white_line+Right_white_line+Center_white_line) >= 240) {
			break;
		}
	}
	stop();
}