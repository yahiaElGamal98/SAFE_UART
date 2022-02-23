/*
 * UART.c
 *
 * Created: 1/24/2022 8:21:18 PM
 *  Author: No. 01
 */ 

#include "../../01-LIB/STD_types.h"
#include "../../01-LIB/Registers.h"

#include "UART_interface.h"
#include "UART_config.h"


#define CARRIAGE_RETURN '\r'
#define NEW_LINE '\n'

#define MAX_CHAR 255

static void (*RxCompleteCallback)(void)=NULL_PTR;

void __vector_13(void)
{
	if(NULL_PTR!=RxCompleteCallback)
	{
		RxCompleteCallback();	
	}
	else
	{
		//do nothing
	}
}

void UART_init()
{
	//set baud rate
	UBRRL=(uint8_t)(BAUD_RATE);
	//select UBRRH and shift right the baud rate to set the remaining bits
	UBRRH_UCSRC= (uint8_t)(BAUD_RATE>> REG_SIZE);
	//enable transmit and receive of UART and receive complete interrupts
	UCSRB= (HIGH<<RXEN) | (HIGH<<TXEN) | (RECEIVE_INTERRUPT<<RXCIE);   
	// select UCSRC register and configure 8 bits of data in a frame with 1 stop bit and user configured parity
	UBRRH_UCSRC = (HIGH<<URSEL) | (PARITY_MODE<<UPM0) | (STOP_MODE<<USBS) | (HIGH<<UCSZ1) | (HIGH <<UCSZ0); 
}
void setRxCompleteCallback(void (*callback)(void))
{
	RxCompleteCallback=callback;
}
void UART_receiveChar(uint8_t* u8_val)
{
	while(LOW==((UCSRA&(HIGH<<RXC))>>RXC))
	{
		//WAIT FOR RECEIVE COMPLETE FLAG
	}
	*u8_val=UDR;
}
void UART_sendChar(uint8_t u8_char)
{
	while(LOW==((UCSRA&(HIGH<<UDRE))>>UDRE))
	{
		//WAIT FOR DATA REGISTER EMPTY FLAG
	}
	UDR=u8_char;
}
void UART_sendString(uint8_t* u8_str)
{
	uint8_t u8_index=0;
	//continue sending till you meet any terminating character
	while((NULL!=u8_str[u8_index])&&(CARRIAGE_RETURN!=u8_str[u8_index])&&(NEW_LINE!=u8_str[u8_index]))
	{
		UART_sendChar(u8_str[u8_index]);
		u8_index++;
	}
}
void UART_receiveString(uint8_t* u8_retStr)
{
	uint8_t u8_index=0;
	//max length of received string is 255 as per requirements
	while(u8_index<MAX_CHAR)
	{
		UART_receiveChar(&u8_retStr[u8_index]);
		//continue receiving till you meet a terminating character
		if(NULL==u8_retStr[u8_index] ||NEW_LINE==u8_retStr[u8_index] ||CARRIAGE_RETURN==u8_retStr[u8_index])
		{
			//replace that character with NULL
			u8_retStr[u8_index]=NULL;
			break;
		}
		//force exit and terminate with NULL if MAX SIZE reached
		else if ((MAX_CHAR-1)==u8_index)
		{
			u8_retStr[u8_index]=NULL;
			break;
		}
		else
		{
			u8_index++;
		}
	}
}