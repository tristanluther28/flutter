//-----------------------------------------------------------------------------
//
//  Buttons.h
//
//  Swallowtail ATmega32U4 Seven Segment Volume Device (v1)
//  The Button Interface for Seven Segment Volume Device
//
//  Copyright (c) 2020 Tristan Luther
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

#ifndef __BUTTONS_SWALLOWTAIL_H__
#define __BUTTONS_SWALLOWTAIL_H__

/* Includes: */
#include "../../../../Common/Common.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
	#endif

	/* Preprocessor Checks: */
	#if !defined(__INCLUDE_FROM_BUTTONS_H)
	#error Do not include this file directly. Include LUFA/Drivers/Board/Buttons.h instead.
	#endif

	/* Public Interface - May be used in end-application: */
	/* Macros: */
	/** Button mask for the first button on the board. */
	#define BUTTONS_BUTTON1      (1 << PB0)
	
	/** Button mask for the first button on the board. */
	#define BUTTONS_BUTTON2      (1 << PB1)

	/** Button mask for all the buttons on the board. */
	#define BUTTONS_ALL_BUTTONS    (BUTTONS_BUTTON1 | BUTTONS_BUTTON2)

	/* Inline Functions: */
	#if !defined(__DOXYGEN__)
	static inline void Buttons_Init(void)
	{
		DDRB  &= ~BUTTONS_ALL_BUTTONS;
		PORTB |=  BUTTONS_ALL_BUTTONS;
	}

	static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
	static inline uint8_t Buttons_GetStatus(void)
	{
		return ((PINB & BUTTONS_ALL_BUTTONS) ^ BUTTONS_ALL_BUTTONS);
	}
	#endif

	/* Disable C linkage for C++ Compilers: */
	#if defined(__cplusplus)
}
#endif

#endif

/** @} */