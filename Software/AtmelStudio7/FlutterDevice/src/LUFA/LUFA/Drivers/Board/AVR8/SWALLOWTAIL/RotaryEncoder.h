//-----------------------------------------------------------------------------
//
//  RotaryEncoder.h
//
//  Swallowtail ATmega32U4 Seven Segment Volume Device (v1)
//  The Interface for Rotary Encoder
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
 *  \brief Board specific Rotary Encoder driver header for the Swallowtail ATmega32u4.
 *  \copydetails Group_ROTARYENCODER_SWALLOWTAIL
 *
 *  \note This file should not be included directly. It is automatically included as needed by the driver
 *        dispatch header located in LUFA/Drivers/Board/RotaryEncoder.h.
 */

/** \ingroup Group_RotaryEncoder
 *  \defgroup Group_RotaryEncoder_SWALLOWTAIL SWALLOWTAIL
 *  \brief Board specific driver header for the Swallowtail ATmega32u4.
 *
 *  Board specific driver header for the Swallowtail ATmega32u4.
 *
 *  @{
 */

#ifndef __ROTARYENCODER_SWALLOWTAIL_H__
#define __ROTARYENCODER_SWALLOWTAIL_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include <avr/sfr_defs.h>
		#include <avr/interrupt.h>
		#include <util/delay.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_ROTARYENCODER_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/RotaryEncoder.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
	
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Bit mask for the first Bit to communicate on the board. */
			#define DT        (1 << PB3)

			/** Bit mask for the second Bit to communicate on the board. */
			#define CLK        (1 << PB2)

			/** Bit mask for all the bits on the board. */
			#define ROTARY_BITS    (DT | CLK)

			/** Bit mask for none of the board bits. */
			#define NO_BITS     0
			
			
		/* Global Variables */
		uint8_t max = 0;
		uint8_t count = 0;
		uint8_t i = 0;
		
		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Rotary_Init(uint8_t maxCount)
			{
				//I/O Port Configuration
				DDRB  &= ~ROTARY_BITS;
				PORTB |=  ROTARY_BITS;
				max = maxCount;
			}
			
			static inline void Rotary_GetCount(uint8_t* mode)
			{
				if (i == 0)
				{
					//If any Encoder pins show falling edge execute loop
					if ((bit_is_clear(PINB,2)) || (bit_is_clear(PINB,3)))
					{
						i = 1;
						_delay_ms(10);
						//If DT is second to go LOW
						if (bit_is_clear(PINB,2))
						{
							// Increment binary count if count is less than the max value
							if (count < max)
							{
								count++;
							}
						}
						//If CLK is second to go LOW
						if (bit_is_clear(PINB,3))
						{
							//If binary count is greater than 0 decrease count by 1
							if (count > 0)
							{
								count--;
							}
						}
					}
				}
				//*mode = count;
				//Wait till shaft position reset
				if ((bit_is_set(PINB,2)) && (bit_is_set(PINB,3) ))
				{
					i = 0;
				}
				return;
			}
			
			/* Interrupt Service Routines */
			
			
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */