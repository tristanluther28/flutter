//-----------------------------------------------------------------------------
//
//  4201AS.h
//
//  Swallowtail ATmega32U4 Seven Segment Volume Device (v1)
//  The LED Interface for Seven Segment Volume Device
//
//  Copyright (c) 2020 Swallowtail Electronics
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//  Web:    http://tristanluther.com
//  Email:  tristanluther28@gmail.com
//
//-----------------------------------------------------------------------------

/** \file
 *  \brief Board specific 4201AS driver header for the Swallowtail ATmega32u4.
 *  \copydetails Group_4201AS_SWALLOWTAIL
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/4201AS.h.
 */

/** \ingroup Group_4201AS
 *  \defgroup Group_4201AS_SWALLOWTAIL SWALLOWTAIL
 *  \brief Board specific LED driver header for the Swallowtail ATmega32u4.
 *
 *  Board specific LED driver header for the Swallowtail ATmega32u4.
 *
 *  @{
 */

#ifndef __4201AS_SWALLOWTAIL_H__
#define __4201AS_SWALLOWTAIL_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include <avr/interrupt.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_4201AS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/4201AS.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define BITS_PORTF       (BIT_A | BIT_B | BIT_C | BIT_D)
			#define EN_PORTB		 (EN_1 | EN_10)
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Bit mask for the first Bit to communicate on the board. */
			#define BIT_A        (1 << PF4)

			/** Bit mask for the second Bit to communicate on the board. */
			#define BIT_B        (1 << PF5)
			
			/** Bit mask for the third Bit to communicate on the board. */
			#define BIT_C        (1 << PF6)

			/** Bit mask for the fourth Bit to communicate on the board. */
			#define BIT_D        (1 << PF7)
			
			/** Enable bit mask for the one's place segment. */
			#define EN_1		(1 << PB5)
			
			/** Enable bit mask for the ten's place segment. */
			#define EN_10		(1 << PB4)

			/** Bit mask for all the bits on the board. */
			#define ALL_BITS    (BIT_A | BIT_B | BIT_C | BIT_D)

			/** Bit mask for none of the board bits. */
			#define NO_BITS     0
			
			/** Enable bit mask for all the segment enables. */
			#define ALL_EN		(EN_1 | EN_10)
			
			/** Enable bit mask for none of the segment enables. */
			#define NO_EN		0
			
			/** Control Register A Set-up */
			#define CCRA		(0b00000000)
			
			/** Control Register B Set-up */
			#define CCRB		(0b00000101) //clk/1024 prescaler 
			
			/** Interrupt Mask */
			#define TMSK		(0b00000010) //Trigger every overflow (~0.01632sec)
			
			/** Compare Value */
			#define CMP_VAL		(250)
			
		/* Global Variables */
		uint8_t buffer = 0; //Holds the number to be written
		uint8_t ones = 0; //Ones place of the number
		uint8_t tens = 0; //Tens place of the number
		uint8_t sw = 0; //Switching between tens & ones place
		
		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void SS_4201AS_Init(void)
			{
				//I/O Port Configuration
				DDRB  |=  ALL_EN;
				DDRF  |= ALL_BITS;
				PORTB &= ~ALL_EN;
				PORTF &= ~ALL_BITS;
				//Timer/Counter0 Configuration
				TCCR0A = CCRA;
				TCCR0B = CCRB;
				TIMSK0 = TMSK;
				OCR0A = CMP_VAL;
			}
			
			static inline void SS_4201AS_WriteByteHex(uint8_t byteNum){
				if(sw == 1){
					/* Write the low byte of the incoming byte to the first segment
					This requires the Enable for the first segment (EN_1) to be low
					and the second segment (EN_10) to be high. */
					//Enable the first segment, disable the second
					PORTB = ~EN_1;
					PORTB = EN_10;
					//Loop though the input and assign the lower byte to the portf
					buffer = (byteNum & 0xFF) << 4;
					PORTF = buffer;
					//_delay_ms(5);
				}
				else if(sw == 0){
					/*Write the high byte of the incoming byte to the second segment
					This requires the Enable for the second segment (EN_10) to be low
					and the first segment (EN_1) to be high. */
					//Enable the second segment, disable the first
					PORTB = EN_1;
					PORTB = ~EN_10;
					//Loop though the input and assign the higher byte to the portf
					buffer = byteNum;
					PORTF = buffer;
					//_delay_ms(5);
				}
				//Switch the segment we are on
				if(sw == 0){
					sw = 1;
				}
				else{
					sw = 0;
				}
			}
			
			static inline void SS_4201AS_SetNum(uint8_t byteNum){
				//Sets the global to be sent out the display
				buffer = byteNum; //Holds the number to be written
				ones = byteNum%10; //Ones place of the number
				tens = (byteNum/10)%10; //Tens place of the number
			}
			
			static inline void SS_4201AS_WriteByte(){
				if(sw == 1){
					/* Write the low byte of the incoming byte to the first segment
					This requires the Enable for the first segment (EN_1) to be low
					and the second segment (EN_10) to be high. */
					//Enable the first segment, disable the second
					PORTB = ~EN_1;
					PORTB = EN_10;
					//Loop though the input and assign the lower byte to the portf
					buffer = (ones & 0xFF) << 4;
					PORTF = buffer;
					//_delay_ms(5);
				}
				else if(sw == 0){
					/* Write the high byte of the incoming byte to the second segment
					This requires the Enable for the second segment (EN_10) to be low
					and the first segment (EN_1) to be high. 
					//Enable the second segment, disable the first*/
					PORTB = EN_1;
					PORTB = ~EN_10;
					//Loop though the input and assign the higher byte to the portf
					buffer = (tens & 0xFF) << 4;;
					PORTF = buffer;
					//_delay_ms(5);
				}
				//Switch the segment we are on
				if(sw == 0){
					sw = 1;
				}
				else{
					sw = 0;
				}
			}
			
			/* Interrupt Service Routines */
			//Triggers once the timer has elapsed 20ms (~50Hz refresh rate)
			ISR(TIMER0_COMPA_vect){
				//Display the value of the buffer
				SS_4201AS_WriteByte();
			}
			
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
