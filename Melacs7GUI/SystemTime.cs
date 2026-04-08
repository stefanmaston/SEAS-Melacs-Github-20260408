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
using System.IO.Ports;

namespace InresolGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static System.Timers.Timer myTimerSysTime;

        private void InitSysTime()
        {
            myTimerSysTime = new System.Timers.Timer();
            myTimerSysTime.Elapsed += new ElapsedEventHandler(myEventSysTime);
            myTimerSysTime.Interval = timeInterval;
            myTimerSysTime.Enabled = true;
        }

        // Take the value from all the melacs and update it periodically. And convert to application specific units.
        private void myEventSysTime(object source, ElapsedEventArgs e)
        {

            Dispatcher.Invoke(new Action(() =>
            {
                do_SystemTime();

                do_ComPortUpdate();

            }));

        }

        private void do_SystemTime()
        {
            textBoxSystemTime.Text = string.Format("{0:yyyy:MM:dd hh:mm:ss tt }", DateTime.Now) + (DateTime.Now.DayOfWeek).ToString();//((int)DateTime.Now.DayOfWeek).ToString();
            variable_SystemYear = DateTime.Now.Year;
            variable_SystemMonth = DateTime.Now.Month;
            variable_SystemDay = DateTime.Now.Day;
            variable_SystemHour = DateTime.Now.Hour;
            variable_SystemMinute = DateTime.Now.Minute;
            variable_SystemSecond = DateTime.Now.Second;
            variable_SystemWeekday = (int)DateTime.Now.DayOfWeek;
        }


        private void do_ComPortUpdate()
        {
            // ... A List.
            List<string> data = new List<string>();
            // Get a list of serial port names.
            string[] ports = SerialPort.GetPortNames();
            // Display each port name to the console.
            foreach (string port in ports)
            {
                data.Add(port);
            }

            // ... Assign the ItemsSource to the List.
            comboBoxComPorts.ItemsSource = data;

            // ... Make the first item selected.
            //comboBoxComPorts.SelectedIndex = 0;
        }
    }
}
