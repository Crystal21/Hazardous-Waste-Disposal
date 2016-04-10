void lcd_port_config (void)
{
	DDRC = DDRC | 0xF7; 
	PORTC = PORTC & 0x80;
}

void adc_pin_config (void)
{
	DDRF = 0x00;
	PORTF = 0x00;
	DDRK = 0x00;
	PORTK = 0x00;
}

void adc_init()
{
	ADCSRA = 0x00;
	ADCSRB = 0x00;		
	ADMUX = 0x20;		
	ACSR = 0x80;
	ADCSRA = 0x86;		
}

unsigned char ADC_Conversion(unsigned char Ch)
{
	unsigned char a;
	if(Ch>7)
	{
		ADCSRB = 0x08;
	}
	Ch = Ch & 0x07;
	ADMUX= 0x20| Ch;
	ADCSRA = ADCSRA | 0x40;		
	while((ADCSRA&0x10)==0);	
	a=ADCH;
	ADCSRA = ADCSRA|0x10; 
	ADCSRB = 0x00;
	return a;
}