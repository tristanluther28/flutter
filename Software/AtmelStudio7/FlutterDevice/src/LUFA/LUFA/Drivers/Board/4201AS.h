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
 *  \brief 4201AS board hardware driver.
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
 *  \defgroup Group_4201ASs 4201AS' Driver - LUFA/Drivers/Board/4201AS.h
 *  \brief LED board hardware driver.
 *
 *  \section Sec_LEDs_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_LEDs_ModDescription Module Description
 *  Hardware 4201AS driver. This provides an easy to use driver for the hardware 4201AS present on many boards. It
 *  provides an interface to configure, test and change the status of the boards 4201AS.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/4201AS.h file in the user project
 *  directory. Otherwise, it will include the appropriate built-in board driver header file. If the BOARD value
 *  is set to \c BOARD_NONE, this driver is silently disabled.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 *
 *  \section Sec_4201AS_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialize the board LED driver before first use
 *      4201AS_Init();
 *
 *      // Turn on each of the four LEDs in turn
 *      LEDs_SetAllLEDs(LEDS_LED1);
 *      Delay_MS(500);
 *      LEDs_SetAllLEDs(LEDS_LED2);
 *      Delay_MS(500);
 *      LEDs_SetAllLEDs(LEDS_LED3);
 *      Delay_MS(500);
 *      LEDs_SetAllLEDs(LEDS_LED4);
 *      Delay_MS(500);
 *
 *      // Turn on all LEDs
 *      LEDs_SetAllLEDs(LEDS_ALL_LEDS);
 *      Delay_MS(1000);
 *
 *      // Turn on LED 1, turn off LED 2, leaving LEDs 3 and 4 in their current state
 *      LEDs_ChangeLEDs((LEDS_LED1 | LEDS_LED2), LEDS_LED1);
 *  \endcode
 *
 *  @{
 */

#ifndef __4201AS_H__
#define __4201AS_H__

	/* Macros: */
		#define __INCLUDE_FROM_4201AS_H

	/* Includes: */
		#include "../../Common/Common.h"

		#if (BOARD == BOARD_NONE)
			static inline void       SS_4201AS_Init(void) {}
			static inline void       SS_4201AS_Disable(void) {}
			static inline void SS_4201AS_WriteByte(uint8_t byteNum) {}
		#elif (BOARD == BOARD_SWALLOWTAIL)
			#include "AVR8/SWALLOWTAIL/4201AS.h"
		#else
			#include "Board/4201AS.h"
		#endif

	/* Preprocessor Checks: */
		#if !defined(__DOXYGEN__)
			#if !defined(NO_BITS)
			#define NO_BITS   0
			#endif

			#if !defined(ALL_BITS)
			#define ALL_BITS  (BIT_A | BIT_B | BIT_C | BIT_D)
			#endif
			
			#if !defined(ALL_EN)
			#define ALL_EN (EN_1 | EN_10)
			#endif
			
			#if !defined(NO_EN)
			#define NO_EN	0
			#endif

			#if !defined(BIT_A)
			#define BIT_A      0
			#endif

			#if !defined(BIT_B)
			#define BIT_B      0
			#endif

			#if !defined(BIT_C)
			#define BIT_C      0
			#endif

			#if !defined(BIT_D)
			#define BIT_D      0
			#endif
			
			#if !defined(EN_1)
			#define EN_1	0
			#endif
			
			#if !defined(EN_10)
			#define EN_10	0
			#endif
		#endif

	/* Pseudo-Functions for Doxygen: */
	#if defined(__DOXYGEN__)
		/** Initializes the board 4201AS driver so that the 4201AS can be controlled. This sets the appropriate port
		 *  I/O pins as outputs, and sets the 4201AS to default to off.
		 *
		 *  This must be called before any 4201AS driver functions are used.
		 */
		static inline void SS_4201AS_Init(void);

		/** Disables the board 4201AS driver, releasing the I/O pins back to their default high-impedance input mode. */
		static inline void SS_4201AS_Disable(void);
		
		/** Write the byte number to the two digit seven segment display. */
		static inline void SS_4201AS_WriteByteHex(uint8_t byteNum);

		/** Write the byte number to the two digit seven segment display. */
		static inline void SS_4201AS_WriteByte(uint8_t byteNum);
		
	#endif

#endif

/** @} */