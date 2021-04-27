//-----------------------------------------------------------------------------
//
//  debug.c
//
//  WFF UDB GenericHID Demonstration Firmware (4_0)
//  A demonstration firmware for the WFF GenericHID Communication Library
//
//  Copyright (c) 2011 Simon Inns
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
//  Web:    http://www.waitingforfriday.com
//  Email:  simon.inns@gmail.com
//
//-----------------------------------------------------------------------------

// Global includes
#include <avr/io.h>
#include <string.h>

// Local includes
#include "debug.h"
#include "WFF GenericHID Demo Application 4_0.h"

// Set the size of the debug information buffer in characters
#define DEBUGBUFFERSIZE 256

// Only compile in the global debug variables if debugging is required
#if defined(USB_DEBUG)

	// Buffer pointers
	uint16_t debugBufferStart;
	uint16_t debugBufferEnd;
	uint16_t debugBufferLevel;
	
	// The following array is the cyclic buffer
	uint8_t debugBuffer[DEBUGBUFFERSIZE];

#endif

// Initialize the debugging log functionality
void debugInitialise(void)
{
#if defined(USB_DEBUG)
	// Reset the buffer's pointers
	debugBufferStart = 0;
	debugBufferEnd = 0;
	debugBufferLevel = 0;
#endif
}

// Send debug text to the debug log
void debugOut(char* debugString)
{
#if defined(USB_DEBUG)
	uint8_t charNumber;
	
	// Is there space in the debug buffer?
	if (debugBufferLevel + strlen((const char *)debugString) >= DEBUGBUFFERSIZE - 2)
	{
		// Buffer does not have enough space... silently drop the debug string
	}
	else
	{	
		// Buffer is not full, write the bytes and update the end pointer
		for (charNumber = 0; charNumber < strlen((const char *)debugString); charNumber++)
		{
			debugBuffer[debugBufferEnd] = debugString[charNumber];
			debugBufferEnd = (debugBufferEnd + 1) % DEBUGBUFFERSIZE;
			
			// Increment the buffer level indicator
			debugBufferLevel++;
		}
		
		// Add a return and new line to the end of the string
		debugBuffer[debugBufferEnd] = '\r';
		debugBufferEnd = (debugBufferEnd + 1) % DEBUGBUFFERSIZE;
		debugBufferLevel++;
		debugBuffer[debugBufferEnd] = '\n';
		debugBufferEnd = (debugBufferEnd + 1) % DEBUGBUFFERSIZE;
		debugBufferLevel++;
	}
#endif
}

// Copy 63 bytes of the debug buffer to the USB send buffer
// The first byte is the number of characters transferred
void copyDebugToSendBuffer(char* sendDataBuffer)
{
#if defined(USB_DEBUG)
	uint16_t bytesToSend = 0;
	uint16_t byteCounter;
	
	// Determine the number of bytes to send
	if (debugBufferLevel > GENERIC_REPORT_SIZE-1) bytesToSend = GENERIC_REPORT_SIZE-1;
		else bytesToSend = debugBufferLevel;
	
	// Place the number of sent bytes in byte[0] of the send buffer
	sendDataBuffer[0] = bytesToSend - 1;
	
	if (debugBufferLevel != 0)
	{
		for (byteCounter = 1; byteCounter < bytesToSend; byteCounter++)
		{
			// Send the next byte to the send buffer
			sendDataBuffer[byteCounter] = debugBuffer[debugBufferStart];
			
			// Update the cyclic buffer pointer
			debugBufferStart = (debugBufferStart + 1) % DEBUGBUFFERSIZE;
			
			// Decrement the buffer level indicator
			debugBufferLevel--;
		}
	}
#else
	// Ensure that we indicate there is nothing to send if the host
	// requests debug
	sendDataBuffer[0] = 0;
#endif
}