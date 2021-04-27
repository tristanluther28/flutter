using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace segmentVolumeDevice
{
    using usbGenericHidCommunications;

    class segmentVolumeDevice : usbGenericHidCommunication
    {
        // Class constructor - place any initialisation here
        public segmentVolumeDevice(int vid, int pid) : base(vid, pid)
        {
        
            //Start at zero, may change later...
            numberDisplayed = 0;
            levelNumber = 0;
            
        }

        //byte for the number to be displayed
        private byte numberDisplayed;

        //byte for the level to be displayed
        private byte levelNumber;

        // Method to set the LED brightness levels
        public void setNumber(byte num)
        {
            // Here we just update the byte, we don't write then to the device
            numberDisplayed = num;
        }

        //Method to set the level
        public void setLevel(byte num)
        {
            //Here we just update the byte, we don't write to the device
            levelNumber = num;
        }

        // Method to write the LED brightness values to the device
        public void writeVolume()
        {
            // Declare our output buffer
            Byte[] outputBuffer = new Byte[9];

            // Byte 0 must be set to 0
            outputBuffer[0] = 0;

            // Byte 1 must be set to our command
            outputBuffer[1] = 0x80;

            // Fill the rest of the buffer with the display number data
            outputBuffer[2] = numberDisplayed;
            outputBuffer[3] = levelNumber;

            // Perform the write command
            writeRawReportToDevice(outputBuffer);

        }
        //Method to write to the LED Bargraph
        public void writeLevel()
        {
            // Declare our output buffer
            Byte[] outputBuffer = new Byte[9];

            // Byte 0 must be set to 0
            outputBuffer[0] = 0;

            // Byte 1 must be set to our command
            outputBuffer[1] = 0x81;

            // Fill the rest of the buffer with the display number data
            outputBuffer[2] = levelNumber;

            // Perform the write command
            writeRawReportToDevice(outputBuffer);
        }
    }
}