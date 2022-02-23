/*
 * Registers.h
 *
 * Created: 1/4/2022 7:19:53 PM
 *  Author: No. 01
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

#define UBRRH_UCSRC (*((volatile uint8_t *)(0x40)))
#define UBRRL (*((volatile uint8_t *)(0x29)))
#define UCSRB (*((volatile uint8_t *)(0x2A)))
#define UCSRA (*((volatile uint8_t *)(0x2B)))
#define UDR (*((volatile uint8_t *)(0x2C)))

#define PORTA_DATA (*((volatile uint8_t *)(0x3B)))
#define PORTA_DIR (*((volatile uint8_t *)(0x3A)))
#define PORTA_STATUS (*((volatile uint8_t *)(0x39)))

#define PORTB_DATA (*((volatile uint8_t *)(0x38)))
#define PORTB_DIR (*((volatile uint8_t *)(0x37)))
#define PORTB_STATUS (*((volatile uint8_t *)(0x36)))

#define PORTC_DATA (*((volatile uint8_t *)(0x35)))
#define PORTC_DIR (*((volatile uint8_t *)(0x34)))
#define PORTC_STATUS (*((volatile uint8_t *)(0x33)))

#define PORTD_DATA (*((volatile uint8_t *)(0x32)))
#define PORTD_DIR (*((volatile uint8_t *)(0x31)))
#define PORTD_STATUS (*((volatile uint8_t *)(0x30)))


#define SREG (*((volatile uint8_t*)(0x5F)))
#define TIMSK (*((volatile uint8_t*)(0x59)))


#define TCCR0 (*((volatile uint8_t*)(0x53)))
#define TCNT0 (*((volatile uint8_t*)(0x52)))
#define OCR0 (*((volatile uint8_t*)(0x5C)))

#define TCCR2 (*((volatile uint8_t*)(0x45)))
#define TCNT2 (*((volatile uint8_t*)(0x44)))
#define OCR2 (*((volatile uint8_t*)(0x43)))

#define ADMUX (*((volatile uint8_t*)(0x27)))
#define ADCSRA (*((volatile uint8_t*)(0x26)))
#define ADCH (*((volatile uint8_t*)(0x25)))
#define ADCL (*((volatile uint8_t*)(0x24)))
#endif /* REGISTERS_H_ */