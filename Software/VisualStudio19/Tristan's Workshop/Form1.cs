using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CoreAudioApi;

namespace segmentVolumeDevice
{
    public partial class Form1 : Form
    {
        // Create an instance of the USB device
        private segmentVolumeDevice theSegmentVolDevice;

        // Create an instance of the default audio device
        private MMDevice defaultDevice;
        public Form1()
        {
            InitializeComponent();

            //Inital Device Status Text
            usbToolStripStatusLabel.Text = "Volume Level Device Detached";

            // Create the USB reference device object (passing VID and PID)
            theSegmentVolDevice = new segmentVolumeDevice(0x2341, 0x8036);

            // Register for device change notifications
            theSegmentVolDevice.registerForDeviceNotifications(this.Handle);

            // Add a listener for usb events
            theSegmentVolDevice.usbEvent += new segmentVolumeDevice.usbEventsHandler(usbEvent_receiver);

            // Perform an initial search for the target device
            theSegmentVolDevice.findTargetDevice();

            // Initialize the core audio API
            MMDeviceEnumerator devEnum = new MMDeviceEnumerator();
            defaultDevice = devEnum.GetDefaultAudioEndpoint(EDataFlow.eRender, ERole.eMultimedia);
        }

        // Callback method for WndProc
        protected override void WndProc(ref Message m)
        {
            // Pass the message to our message handler
            theSegmentVolDevice.handleDeviceNotificationMessages(m);

            // Pass the message on to the base WndProc
            base.WndProc(ref m);
        }

        // Listener for USB events
        private void usbEvent_receiver(object o, EventArgs e)
        {
            // Check the status of the USB device and update the form accordingly
            if (theSegmentVolDevice.isDeviceAttached)
            {
                // Device is attached, do tasks here
                this.usbToolStripStatusLabel.Text = "Volume Level Device Attached";
            }
            else
            {
                // Device is detached, do tasks here
                this.usbToolStripStatusLabel.Text = "Volume Level Device Detached";
            }
        }

        private Int64 GetVol()
        {
            // Variables for storing the volume level percentages
            Int64 leftVolumeLevelPercent;
            Int64 rightVolumeLevelPercent;
            Int64 averageVolumeLevelPercent;

            // Read the current volume levels
            leftVolumeLevelPercent = Convert.ToInt64(defaultDevice.AudioMeterInformation.PeakValues[0] * 100);
            rightVolumeLevelPercent = Convert.ToInt64(defaultDevice.AudioMeterInformation.PeakValues[1] * 100);

            // Calculate the average
            averageVolumeLevelPercent = (leftVolumeLevelPercent + rightVolumeLevelPercent) / 2;

            return averageVolumeLevelPercent;
        }

        private double dBToDecWin(float db)
        {
            double temp = (Math.Pow(10.0, db / 33.7549)) * 100;
            if(temp < 11)
            {
                temp--;
            }
            return temp;
        }

        private double decWinToDb(byte volume)
        {
            double temp = 33.7549 * (Math.Log10(((double)volume / 100)));
            return temp;
        }

        private void displayUpdate_tick(object sender, EventArgs e)
        {
            //Collect the system volume level
            this.dBBar.Value = (int) GetVol();

            //Collect the system volume 
            this.volLvl.Text = Math.Round(dBToDecWin(defaultDevice.AudioEndpointVolume.MasterVolumeLevel)).ToString() + "%";

            byte volume = Convert.ToByte(Math.Round(dBToDecWin(defaultDevice.AudioEndpointVolume.MasterVolumeLevel)));

            // Update the volume value for the device
            theSegmentVolDevice.setNumber(volume);

            // Update the level value for the device
            theSegmentVolDevice.setLevel((byte)GetVol());

            //Check if the device is attached
            if (theSegmentVolDevice.isDeviceAttached)
            {
                //Send the USB command to the device
                theSegmentVolDevice.writeVolume();
            }
        }

        // The main form is closing, clear the segement display
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Update the volume/level value for the device
            theSegmentVolDevice.setNumber(0);
            theSegmentVolDevice.setLevel(0);

            // Send the USB command to the device
            theSegmentVolDevice.writeVolume();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }
    }
}
