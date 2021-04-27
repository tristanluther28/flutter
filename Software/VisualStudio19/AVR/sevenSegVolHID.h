/*
    sevenSegVolHID.h

    sevenSegVolHID.h - v1.0 is HID firmware for receiving
    the HID data buffer and displaying the data from the 
    sevenSegVol windows application to the HID device.

    Tristan Luther -- 12/17/2019

    Copyright & Usage

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE. 

    Web: http://tristanluther.com
    Email: tristanluther28@gmail.com
*/

#ifndef _SEVENSEGHID_H_
#define _SEVENSEGHID_H_

// Global includes
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

// Local includes
#include "Descriptors.h"
#include "debug.h"
#include "potentiometer.h"

// LUFA includes
#include "LUFA/Version.h"
#include "LUFA/Drivers/Board/LEDs.h"
#include "LUFA/Drivers/Board/Buttons.h"
#include "LUFA/Drivers/USB/USB.h"

// Function Prototypes:
void setupHardware(void);
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

#endif