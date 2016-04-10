int sortedFlag[3]= {0};				//temp; assume detected block is green
int index = 0;
int a_flag=0, b_flag = 0, c_flag = 0;
//int valid=0;


int node0_0(int flag, int angle)	//contains code for node_0_1
{
	if (flag==0)					//turn left
	{
		velocity(180,180);
		backward_mm(20);
		left_degrees(67,1);//100/70
		fw_follow_black_line();
		/*
		soft_left();
		_delay_ms(3);*/
		
	}
	else if (flag==1)				//turn right towards sorting zone
	{
		_delay_ms(100);
		velocity(180,180);
		
		forward_mm(60);//100
		/*
		soft_right_2();  
		_delay_ms(2525);//1550 1560 removed*/
		right_degrees(84,0);// 104, 0,80
		//soft_right_2_degrees(180);		//added
		
		
		//soft_right();
		//_delay_ms(10);
		//backward_mm(40);
		
		//_delay_ms(100);// 70
		
		/*
		forward_mm(10);
		pick_block(angle);
		backward_mm(30);
		left_degrees(185,0);
		*/
		fw_follow_black_line();
	}
	else if (flag==2)				//go straight on the bridge
	{
		fw_follow_black_line();
	}
	else if (flag==3)			//turn right and pick weight block
	{
		right_degrees(100,0);
		fw_follow_black_line();
		left_degrees(100,0);
		pick_block(angle);
	}
	else if(flag == 4){
		servo_1(130);
		servo_2(120);
		velocity(180,180);
		left_degrees(169,1); //165,1/164
		//left_degrees(95,0);	//temp
		backward_mm(23);//30
		forward_mm(10);
		backward_mm(15);
		pick_block(107);
		forward_mm(15);
		backward_mm(100);
	}
	else if(flag==5){
		forward_mm(50);
		pick_block(96);
		backward_mm(60);
		right_degrees(88,0);
		fw_follow_black_line();
	}
	else if(flag==6){
		servo_2(120);
		forward_mm(70);
		pick_block(85);
		backward_mm(80);
		right_degrees(88,0);
		backward_mm(50);
		right_degrees(88,0);
		fw_follow_black_line();
	}
}

int node_m1_0(int flag)
{
	if(flag==0)				//turn right and drop weight block
	{
		velocity(180,180);
		right_degrees(85,0);
		backward_mm(20);
		drop_weight();
		left_degrees(100,0);
		fw_follow_black_line();
		stop();
		//return 1;
	}
	if(flag==1)
	{
		velocity(180,180);
		right_degrees(85,0);
		backward_mm(20);
		drop_weight();
		right_degrees(100,0);
		stop();
		return 2;
	}
	if(flag==2)					//go straight
	{
		//_delay_ms(100);
		//fw_follow_black_line();
		velocity(150,200);
		forward_mm(195);
		/*
		soft_left();
		_delay_ms(3);
		*/
		return 1;
	}
	if(flag==3){
		fw_follow_black_line();
		stop();
	}
}

int node_m2_0(int flag)
{
	if (flag == 0) {				//pick weight block
	pick_block(90);
	right_degrees(180,0);
	fw_follow_black_line();
	return 1;
	
} else if (flag == 1) {			//place block in sorting zone
	velocity(180,180);

	right_degrees(76,1);//92/96/100/80/70
	backward_mm(25);
	
	place_to_sort();

	forward_mm(150);//130
	//fw_follow_black_line();
	_delay_ms(1000);
	//forward_mm(4);
	sortedFlag[index] = detect_color();
	index++;
	print_color(sortedFlag[index - 1]);
	velocity(180,165);

	backward_mm(140);//160
	pick_at_sort();
	backward_mm(50);
	right_degrees(73,1);//105/85/78//75
	velocity(190,220);
	backward_mm(30);
	fw_follow_black_line();
	velocity(255,255);
	}	
}

int node_0_1(int flag,int valid)
{

	if (flag==0)				//detect color and place block if color matches
	{
		if(valid){
		//fw_follow_black_line();
		forward_mm(190);
	 	rotate_at_flag();
		b_flag=detect_color();
		print_color(b_flag);
		backward_mm(50);
		stop();
		_delay_ms(500);
		left_degrees(58,1);//60/62
		stop();
		_delay_ms(500);
		velocity(255,195);
		backward_mm(150);//220/160
	
		stop();
		_delay_ms(500);
		soft_right_2();
		_delay_ms(630);
		//bw_follow_black_line();
		velocity(180,180);
		//right_degrees(15,1);//10
		stop();
		_delay_ms(2000);
		}		
		if (b_flag==sortedFlag[1])		//place block and go over bridge
		{
			buzzer_on();
			_delay_ms(200);
			buzzer_off();
			place_block();
			//left_degrees(190,0);
			
		}
		else
		{	
			forward_mm(10);						//turn left
			
			
		}
		/*
		left_degrees(85,1);//50/96/90
		fw_follow_black_line();
		*/
	}
	if (flag==1)			//turn left
	{
		left();
		_delay_ms(1);
		left_degrees(80,0);
		fw_follow_black_line();
	}
	if (flag==2)			//turn right
	{
		right_degrees(67,1);//80
		fw_follow_black_line();
	}
	
}

void node_m1_1(int flag,int valid) {
	if (flag == 0) {			//detect flag color,place if color matches
	right_degrees(93,0);//85 110,0
	
	if(valid){
	//fw_follow_black_line();
	forward_mm(165-50);//165
	rotate_at_flag();
	backward_mm(10);
	c_flag = detect_color();
	print_color(c_flag);
	
	
	backward_mm(50);
	stop();
	_delay_ms(500);
	left_degrees(60,1);
	stop();
	_delay_ms(500);
	velocity(255,195);
	backward_mm(150);//170
	
	stop();
	_delay_ms(500);
	soft_right_2();
	_delay_ms(550);
	//bw_follow_black_line();
	velocity(180,180);
	//right_degrees(15,1);//10
	stop();
	_delay_ms(2000);
	}	
	if (c_flag == sortedFlag[0]) {
		forward_mm(15);
		place_block();
		backward_mm(15);
	}
	backward_mm(35);//20
	right_degrees(100,0);
	velocity(150,150);
	fw_follow_black_line();
} else if (flag == 1) {				//pick weight block

//pick_block();
right_degrees(200,0);
fw_follow_black_line();
	}
}

int node_1_1(int flag)
{
	if(flag==0)				//turn right and drop weight
	{
		velocity(180,180);
		right_degrees(100,0);
		backward_mm(50);
		drop_weight();
		left_degrees(100,0);
		fw_follow_black_line();
		stop();
		//return 1;
	}
	if(flag==1)
	{
		velocity(180,180);
		left_degrees(100,0);
		backward_mm(50);
		drop_weight();
		right_degrees(100,0);
		stop();
		return 2;
	}
	if(flag==2)					//go straight
	{
		fw_follow_black_line();
		return 1;
	}
}

void node_2_1(int flag, int angle)
{
	if(flag==0)						//turn left and place block
	{
		//fw_follow_black_line();
		velocity(180,180);
		left_degrees(128,0);
		backward_mm(50);
		place_block();
		//right_degrees(100,0);
		velocity(180,225);
		//backward_mm(65);
		
		//backward_mm(20);
		//left_degrees(95,0);	--uncomment for generalized
		//fw_follow_black_line();
	}
	if(flag==1)					//pick weight block
	{
		//fw_follow_black_line();
		pick_block(angle);
		right_degrees(190,0);
		fw_follow_black_line();
	}
	/*
	if(flag==2)
	{
		fw_follow_black_line();
	}
	*/
}