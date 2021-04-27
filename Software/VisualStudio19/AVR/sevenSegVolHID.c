/*
    sevenSegVolHID.c

    sevenSegVolHID.c - v1.0 is HID firmware for receiving
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

/************* includes ***************/
#include "./sevenSegVolHID.h"

/*********** macros/globals ***********/
//General Purpose string for debugging though terminal/HID
debugString[24];

/*************** functions ************/

// Setup the hardware
void setupHardware(void)
{
	// Disable watchdog if enabled by boot-loader/fuses
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// Disable clock division
	clock_prescale_set(clock_div_1);

	// Hardware Initialization
	debugInitialise();
	LEDs_Init();
    //sevenSegInitialise();
	USB_Init();
}

// USB Device connected event handler
void EVENT_USB_Device_Connect(void)
{
	// Indicate USB enumerating
	sprintf(debugString, "USB Device enumerating");
	debugOut(debugString);
}

// USB Device disconnected event handler
void EVENT_USB_Device_Disconnect(void)
{
	// Indicate USB not ready
	sprintf(debugString, "USB Device disconnected");
	debugOut(debugString);
}

// Event handler for the USB_ConfigurationChanged event
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	// Setup HID Report Endpoints
	ConfigSuccess &= Endpoint_ConfigureEndpoint(GENERIC_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
	                                            GENERIC_EPSIZE, ENDPOINT_BANK_SINGLE);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(GENERIC_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT,
	                                            GENERIC_EPSIZE, ENDPOINT_BANK_SINGLE);

	// Indicate endpoint configuration success or failure
	if (ConfigSuccess)
	{
		sprintf(debugString, "USB endpoint configuration successful");
		debugOut(debugString);
	}		
	else
	{
		sprintf(debugString, "USB endpoint configuration failed");
		debugOut(debugString);
	}		
}

// Event handler for the USB_ControlRequest event
void EVENT_USB_Device_ControlRequest(void)
{
	// Handle HID Class specific requests

	// This is called if the host is waiting for a report from the device.  This functionality is not used
	// in the generic HID framework but is kept for compatibility with LUFA (bulk sending and receiving is
	// an atomic operation dealt with when the initial command packet is received below).
	if (USB_ControlRequest.bRequest == HID_REQ_GetReport)
	{
		if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
		{
			//uint8_t GenericData[GENERIC_REPORT_SIZE];
			//CreateGenericHIDReport(GenericData);

			Endpoint_ClearSETUP();
			
			sprintf(debugString, "Error: USB_ControlRequest.bRequest == HID_REQ_GetReport?");
			debugOut(debugString);

			/* Write the report data to the control endpoint */
			//Endpoint_Write_Control_Stream_LE(&GenericData, sizeof(GenericData));
			Endpoint_ClearOUT();
		}
	}
	
	// Do we have a command request from the host?
	if (USB_ControlRequest.bRequest == HID_REQ_SetReport)
	{		
		// Ensure this is the type of report we are interested in
		if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
		{
			// Note: the endpoints are from the perspective of the host: OUT is 'out from host' and IN is 'in to host'
			
			// Declare our send and receive buffers
			char hidReceiveBuffer[GENERIC_REPORT_SIZE];
			char hidSendBuffer[GENERIC_REPORT_SIZE];

			// Clear the SETUP endpoint
			Endpoint_ClearSETUP();

			// Read the report data from the control endpoint
			Endpoint_Read_Control_Stream_LE(&hidReceiveBuffer, sizeof(hidReceiveBuffer));
			Endpoint_ClearIN();

			// Process GenericHID command packet
			switch(hidReceiveBuffer[0])
			{
				case 0x10:	// Debug information request from host
					// Select the IN end-point
					Endpoint_SelectEndpoint(GENERIC_IN_EPNUM);

					// Send a response to the host
					if (Endpoint_IsINReady())
					{
						// Copy any waiting debug text to the send data buffer
						copyDebugToSendBuffer((char*)&hidSendBuffer[0]);
					
						// Write the return packet data into the report
						Endpoint_Write_Stream_LE(&hidSendBuffer, sizeof(hidSendBuffer), NULL);

						// Finalize the stream transfer to send the last packet
						Endpoint_ClearOUT();
					}
					break;
					
				// Place application specific commands here:
				
				case 0x80:	// Command 0x80 - Get device status
	            	// This command is polled so enabling debug causes a lot of chatter...
					//sprintf(debugString, "** Received command 0x80 (get device status) from host");
					//debugOut(debugString);
					
	            	// We expect no input data for this command
					
					// Assemble the response packet
					
					// Get the LED status
					; // Note: seems to be a compiler bug that you can't have a label as the first part
					// of a case statement... the ';' gets around this...
					uint8_t ledStatus = LEDs_GetLEDs();
					
					if ((ledStatus & LEDS_LED1) == 0) hidSendBuffer[0] = 0; // LED1 status
					else hidSendBuffer[0] = 1;
					if ((ledStatus & LEDS_LED2) == 0) hidSendBuffer[1] = 0; // LED2 status
					else hidSendBuffer[1] = 1;
					if ((ledStatus & LEDS_LED3) == 0) hidSendBuffer[2] = 0; // LED3 status
					else hidSendBuffer[2] = 1;
					if ((ledStatus & LEDS_LED4) == 0) hidSendBuffer[3] = 0; // LED4 status
					else hidSendBuffer[3] = 1;
		            
					// Send the response packet ->
				        
					// Select the IN end-point
					Endpoint_SelectEndpoint(GENERIC_IN_EPNUM);

					// Send a response to the host
					if (Endpoint_IsINReady())
					{

						// Write the return packet data into the report
						Endpoint_Write_Stream_LE(&hidSendBuffer, sizeof(hidSendBuffer), NULL);

						// Finalize the stream transfer to send the last packet
						Endpoint_ClearOUT();
					}
	            	break;
				
				case 0x81:	// Command 0x81 - Set LED status
	            	sprintf(debugString, "** Received command 0x81 (set LED status) from host");
					debugOut(debugString);
					
					// Set the LED status
					if (hidReceiveBuffer[1] == 1) LEDs_TurnOnLEDs(LEDS_LED1); else LEDs_TurnOffLEDs(LEDS_LED1);
					if (hidReceiveBuffer[2] == 1) LEDs_TurnOnLEDs(LEDS_LED2); else LEDs_TurnOffLEDs(LEDS_LED2);
					if (hidReceiveBuffer[3] == 1) LEDs_TurnOnLEDs(LEDS_LED3); else LEDs_TurnOffLEDs(LEDS_LED3);
					if (hidReceiveBuffer[4] == 1) LEDs_TurnOnLEDs(LEDS_LED4); else LEDs_TurnOffLEDs(LEDS_LED4);
					
					// We do not send a response to this command
					
					break;
				
				default:
					// Unknown command received
					sprintf(debugString, "Unknown command received (%x)", hidReceiveBuffer[0]);
					debugOut(debugString);
					break;
			} // switch(hidReceiveBuffer[0])
		}
	}
}

/**************** main ****************/
int main(){

    setupHardware();

    //Default LEDs to zero (off) and set external interrupt
    LEDs_TurnOffLEDs(LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4);
    sei();

    //Output Firmware Info
    sprintf(debugString, "Seven Segment Volume Display Firmware Version 1.0 (ATmega32U4)");
    debugOut(debugString);

    //Output name and web Info
    sprintf(debugString, "2019 Tristan Luther - http://tristanluther.com");
    debugOut(debugString);

    //Output credits to Dean and Simon (couldn't have done it without them!)
    sprintf(debugString,"Thank you to LUFA library by Dean Camera - http://fourwalledcubicle.com");
    debugOut(debugString);
    sprintf(debugString,"& to Simon Inns for his wonderful demo - http://www.waitingforfriday.com");
    debugOut(debugString);

    for(;;){
        //Poll the USB tasks
        USB_USBTask();
    }
    return 0;
}