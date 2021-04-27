/*
  Copyright 2020  Tristan Luther | Swallowtail Electronics

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief Rotary Encoder board hardware driver.
 *
 *  This file is the master dispatch header file for the board-specific 4201AS driver, for boards containing user
 *  controllable displays.
 *
 *  User code should include this file, which will in turn include the correct 4201AS driver header file for the
 *  currently selected board.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/4201AS.h file in the user project
 *  directory.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 */

/** \ingroup Group_BoardDrivers
 *  \defgroup Group_RotaryEncoders RotaryEncoder' Driver - LUFA/Drivers/Board/RotaryEncoder.h
 *  \brief LED board hardware driver.
 *
 *  \section Sec_LEDs_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_LEDs_ModDescription Module Description
 *  Hardware Rotary Encoder driver. This provides an easy to use driver for the hardware Rotary Encoder present on many boards.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/4201AS.h file in the user project
 *  directory. Otherwise, it will include the appropriate built-in board driver header file. If the BOARD value
 *  is set to \c BOARD_NONE, this driver is silently disabled.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 *
 *  \section Sec_RotaryEncoder_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *
 *  @{
 */

#ifndef __ROTARYENCODER_H__
#define __ROTARYENCODER_H__

	/* Macros: */
		#define __INCLUDE_FROM_ROTARYENCODER_H

	/* Includes: */
		#include "../../Common/Common.h"

		#if (BOARD == BOARD_NONE)
			static inline void       Rotary_Init(void) {}
			static inline void       Rotary_GetCount(void) {}
			static inline void Rotary_Disable(uint8_t byteNum) {}
		#elif (BOARD == BOARD_SWALLOWTAIL)
			#include "AVR8/SWALLOWTAIL/RotaryEncoder.h"
		#else
			#include "Board/RotaryEncoder.h"
		#endif

	/* Preprocessor Checks: */
		#if !defined(__DOXYGEN__)

		#endif

	/* Pseudo-Functions for Doxygen: */
	#if defined(__DOXYGEN__)
		/** Initializes the board Rotary Encoder driver uses I/O Port D 0 & 1.
		 *
		 *  This must be called before any Rotary Encoder driver functions are used.
		 */
		static inline void Rotary_Init(uint8_t maxCount);

		/** Disables the board Rotary Encoder driver, releasing the I/O pins back to their default high-impedance input mode. */
		static inline void Rotary_Disable(void);
		
		/** Write the byte number to the two digit seven segment display. */
		static inline uint8_t Rotary_GetCount();
		
	#endif

#endif

/** @} */