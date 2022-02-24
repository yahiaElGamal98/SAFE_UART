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
EN_ErrorStatus_t UART_receiveChar(void* pvid_val)
{
	EN_ErrorStatus_t EN_loc_error;
	if(NULL_PTR!=pvid_val)
	{
		while(LOW==((UCSRA&(HIGH<<RXC))>>RXC))
		{
			//WAIT FOR RECEIVE COMPLETE FLAG
		}
		*((uint8_t*)pvid_val)=UDR;
		 EN_loc_error=EOK;
	}
	else
	{
		 EN_loc_error=ENOK;
	}
	return  EN_loc_error;
	
}
void UART_sendChar(uint8_t u8_char)
{
	while(LOW==((UCSRA&(HIGH<<UDRE))>>UDRE))
	{
		//WAIT FOR DATA REGISTER EMPTY FLAG
	}
	UDR=u8_char;
}
EN_ErrorStatus_t UART_sendString(const void* pvid_str)
{
	EN_ErrorStatus_t EN_loc_error;
	if(NULL_PTR!=pvid_str)
	{
		uint8_t u8_index=0;
		uint8_t *pu8_str=(uint8_t*)pvid_str;
		//continue sending till you meet any terminating character
		while((NULL!=pu8_str[u8_index])&&(CARRIAGE_RETURN!=pu8_str[u8_index])&&(NEW_LINE!=pu8_str[u8_index]))
		{
			UART_sendChar(pu8_str[u8_index]);
			u8_index++;
		}
		EN_loc_error=EOK;
	}
	else
	{
		EN_loc_error=ENOK;
	}
	return EN_loc_error;
}
EN_ErrorStatus_t UART_receiveString(void* pvid_str)
{
	EN_ErrorStatus_t EN_loc_error;
	if(NULL_PTR!=pvid_str)
	{
		uint8_t u8_index=0;
		uint8_t *pu8_str = (uint8_t*)pvid_str;
		//max length of received string is 255 as per requirements
		while(u8_index<MAX_CHAR)
		{
			UART_receiveChar((void*)(&pu8_str[u8_index]));
			//continue receiving till you meet a terminating character
			if((NULL==pu8_str[u8_index]) ||(NEW_LINE==pu8_str[u8_index]) ||(CARRIAGE_RETURN==pu8_str[u8_index]))
			{
				//replace that character with NULL
				pu8_str[u8_index]=NULL;
				break;
			}
			//force exit and terminate with NULL if MAX SIZE reached
			else if ((MAX_CHAR-1)==u8_index)
			{
				pu8_str[u8_index]=NULL;
				break;
			}
			else
			{
				u8_index++;
			}
		}
		EN_loc_error=EOK;
	}
	else
	{
		EN_loc_error=ENOK;
	}
	return  EN_loc_error;	
}