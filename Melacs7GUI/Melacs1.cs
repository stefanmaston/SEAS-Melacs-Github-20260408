using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Timers;
using System.ComponentModel;

namespace InresolGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //private Thread thrMessagingM1;
        private delegate void UpdateLogCallBackM1(byte[] byteMsg);
        private delegate void UpdateStatusCallBackM1(int bytesReceived);
        private delegate void UpdateDisconnectedCallBackM1();
        private static System.Timers.Timer myTimerM1;
        BackgroundWorker workerConnectM1;
        //BackgroundWorker workerRecvMsgM1;

        String exceptionM1 = "No Exception Yet";

        private int AD7_hex_M1;
        private int AD6_hex_M1;
        private int AD5_hex_M1;
        private int AD4_hex_M1;
        private int AD3_hex_M1;
        private int AD2_hex_M1;
        private int AD1_hex_M1;
        private int AD0_hex_M1;
        private int DIO7_hex_M1;
        private int DIO6_hex_M1;
        private int DIO5_hex_M1;
        private int DIO4_hex_M1;
        private int DIO3_hex_M1;
        private int DIO2_hex_M1;
        private int DIO1_hex_M1;
        private int DIO0_hex_M1;

        private System.ComponentModel.IContainer components = null;
        private System.IO.Ports.SerialPort serialPort1;

        private void InitM1()
        {
            buttonDisconnect_M1.IsHitTestVisible = false;

            // Create a timer
            myTimerM1 = new System.Timers.Timer();
            // Tell the timer what to do when it elapses
            myTimerM1.Elapsed += new ElapsedEventHandler(myEventM1);
            // Set it to go off every five seconds
            myTimerM1.Interval = timeInterval;
            // Don't Start the time yet      
            myTimerM1.Enabled = false;

            workerConnectM1 = new BackgroundWorker();
            workerConnectM1.DoWork += workerConnectM1_DoWork;
            workerConnectM1.RunWorkerCompleted += workerConnectM1_RunWorkerCompleted;

            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            serialPort1.PortName = "COM3";
            serialPort1.BaudRate = 115200;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
        }

        // Implement a call with the right signature for events going off
        private void myEventM1(object source, ElapsedEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                byte[] b = new byte[12];
                //byte[] b = new byte[10];
                Dispatcher.Invoke(new Action(() =>
                {
                    b[0] = (byte)sliderJP19_M1.Value;
                    b[1] = (byte)sliderJP18_M1.Value;
                    b[2] = (byte)(sliderJP10_M1.Value * 10);
                    b[3] = (byte)(sliderJP9_M1.Value * 10);
                    b[4] = (byte)(sliderJP8_M1.Value * 10);
                    b[5] = (byte)(sliderJP7_M1.Value * 10);
                    b[6] = Convert.ToByte(checkBox_JP6_M1.IsChecked.Value);
                    b[7] = Convert.ToByte(checkBox_JP5_M1.IsChecked.Value);
                    b[8] = Convert.ToByte(checkBox_JP4_M1.IsChecked.Value);
                    b[9] = Convert.ToByte(checkBox_JP3_M1.IsChecked.Value);
                    b[10] = (byte)(avgLength >> 8);
                    b[11] = (byte)(avgLength & 0x00FF);

                    serialPort1.Write(b, 0, b.Length);
                    textBoxStatus_M1.Text = "Sent : " + b.Length.ToString() + " bytes";
                }));
            }
            else
            {
                UpdateDisconnectedM1();
            }
        }

        private void UpdateLogM1(byte[] byteMsg)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                AD7_hex_M1 = (byteMsg[0] << 8) | byteMsg[1];
                AD6_hex_M1 = (byteMsg[2] << 8) | byteMsg[3];
                AD5_hex_M1 = (byteMsg[4] << 8) | byteMsg[5];
                AD4_hex_M1 = (byteMsg[6] << 8) | byteMsg[7];
                AD3_hex_M1 = (byteMsg[8] << 8) | byteMsg[9];
                AD2_hex_M1 = (byteMsg[10] << 8) | byteMsg[11];
                AD1_hex_M1 = (byteMsg[12] << 8) | byteMsg[13];
                AD0_hex_M1 = (byteMsg[14] << 8) | byteMsg[15];
                DIO7_hex_M1 = (byteMsg[16] << 8) | byteMsg[17];
                DIO6_hex_M1 = (byteMsg[18] << 8) | byteMsg[19];
                DIO5_hex_M1 = (byteMsg[20] << 8) | byteMsg[21];
                DIO4_hex_M1 = (byteMsg[22] << 8) | byteMsg[23];
                DIO3_hex_M1 = (byteMsg[24] << 8) | byteMsg[25];
                DIO2_hex_M1 = (byteMsg[26] << 8) | byteMsg[27];
                DIO1_hex_M1 = (byteMsg[28] << 8) | byteMsg[29];
                DIO0_hex_M1 = (byteMsg[30] << 8) | byteMsg[31];

                textBox_AD7_M1.Text = AD7_hex_M1.ToString();
                textBox_AD6_M1.Text = AD6_hex_M1.ToString();
                textBox_AD5_M1.Text = AD5_hex_M1.ToString();
                textBox_AD4_M1.Text = AD4_hex_M1.ToString();
                textBox_AD3_M1.Text = AD3_hex_M1.ToString();
                textBox_AD2_M1.Text = AD2_hex_M1.ToString();
                textBox_AD1_M1.Text = AD1_hex_M1.ToString();
                textBox_AD0_M1.Text = AD0_hex_M1.ToString();
                textBox_DIO7_M1.Text = DIO7_hex_M1.ToString();
                textBox_DIO6_M1.Text = DIO6_hex_M1.ToString();
                textBox_DIO5_M1.Text = DIO5_hex_M1.ToString();
                textBox_DIO4_M1.Text = DIO4_hex_M1.ToString();
                textBox_DIO3_M1.Text = DIO3_hex_M1.ToString();
                textBox_DIO2_M1.Text = DIO2_hex_M1.ToString();
                textBox_DIO1_M1.Text = DIO1_hex_M1.ToString();
                textBox_DIO0_M1.Text = DIO0_hex_M1.ToString();
            }));
        }

        private void UpdateStatusM1(int bytesReceived)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                textBoxStatus_M1.Text = "Received : " + bytesReceived.ToString() + " bytes";
            }));
        }

        private void UpdateDisconnectedM1()
        {
            Dispatcher.Invoke(new Action(() =>
            {
                textBoxStatus_M1.Text = "Disconnected";
            }));
        }

        private void workerConnectM1_DoWork(object sender, DoWorkEventArgs e)
        {
            // run all background tasks here
            try
            {
                serialPort1.Open();
            }
            catch (SocketException SE)
            {
                exceptionM1 = SE.ToString();
            }
        }

        private void workerConnectM1_RunWorkerCompleted(object sender,
                                               RunWorkerCompletedEventArgs e)
        {
            //update ui once worker complete his work
            if (null != serialPort1)
            {
                if (serialPort1.IsOpen)
                {
                    buttonDisconnect_M1.IsHitTestVisible = true;
                    textBoxStatus_M1.Text = "Connected..";

                    //thrMessagingM1 = new Thread(new ThreadStart(ReceiveMessagesM1));
                    //thrMessagingM1.Start();
                    //workerRecvMsgM1.RunWorkerAsync();


                    //Start the timer   
                    myTimerM1.Enabled = true;
                }
                else
                {
                    textBoxStatus_M1.Text = "Disconnected : " + exceptionM1;
                    buttonConnect_M1.IsHitTestVisible = true;
                }
            }
        }

        private void buttonConnectM1_Click(object sender, RoutedEventArgs e)
        {
            buttonConnect_M1.IsHitTestVisible = false;


            textBoxStatus_M1.Text = "Connecting..";
            workerConnectM1.RunWorkerAsync();
        }

        private void buttonDisconnectM1_Click(object sender, RoutedEventArgs e)
        {
            buttonConnect_M1.IsHitTestVisible = true;
            buttonDisconnect_M1.IsHitTestVisible = false;
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int bytesReceived = 0;
            byte[] rcv = new byte[100];
            bytesReceived = serialPort1.Read(rcv, 0, 100);

            if (bytesReceived > 0)
            {
                UpdateLogM1(rcv);
                UpdateStatusM1(bytesReceived);
            }
        }

    }
}

