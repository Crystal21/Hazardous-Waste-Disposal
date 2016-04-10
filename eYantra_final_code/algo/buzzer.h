void buzzer_pin_config(){
	
	DDRC = DDRC | 0x08;
	PORTC = PORTC & 0xF7;	
}

void buzzer_on(){
	
	PORTC = 0x08;
}

void buzzer_off(){
	PORTC = 0x00;
}
