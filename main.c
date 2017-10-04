/*
 * GPS-UART-BUF.c
 *
 * Created: 9/23/2017 5:37:46 PM
 * Author : madiv
 */ 
#define F_CPU 2000000UL 
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AT-SMS.h"

#define FOSC 2000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR (((FOSC / (BAUD * 16UL))) - 1)

static FILE uart0_output = FDEV_SETUP_STREAM(uart0_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE uart1_input = FDEV_SETUP_STREAM(NULL, uart1_getchar, _FDEV_SETUP_READ);
static FILE uart0_input = FDEV_SETUP_STREAM(NULL, uart0_getchar, _FDEV_SETUP_READ);


int main( void )
{
	USART1_Init(MYUBRR);
	USART0_Init(MYUBRR);
	DDRB |= (1<<DDB1); //set PORTB1 as output
	
	stdin = &uart0_input;
	stdout = &uart0_output;

	_delay_ms(2000);
	printf("\r\nHello World\r\n");
	_delay_ms(2000);
	
	int i=0; int y=0;
	sei();

	while (1)
	{
		stdin = &uart0_input;
		stdout = &uart0_output;
		
		for (int x=0; x<200; x++)
		{ PINB |= (1<<PINB1);
			_delay_ms(20);}	
				
		while (i<1000)
		{
			
			i++;
			char c = getchar();
			printf("%c", c);

		}
		 
		fdev_close();
		stdin = &uart1_input;
		stdout = &uart0_output;
		
		for (int x=0; x<200; x++)
		{ PINB |= (1<<PINB1);
		_delay_ms(20);}

		while (y<30)
		{
				
			y++;
			char c = getchar();
			printf("%c", c);
		}
		
 		 y=i=0;
		fdev_close();
	}
	return 0;
}

