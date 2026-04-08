//*  HISTORY: Mainwindow.xaml
//*  Modified Rolf Blixt P1A V001 2011-11-23 in "Header"
//*  MELACS7 Names and logos, Rev state added on top left corner */

//*  HISTORY: Mainwindow.xaml.cs


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
using System.IO.Ports;

namespace InresolGUI
{

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private int timeInterval = 2000;
        private int timeShutdownDelay = 1200000;
        private int timeDelayApp = 400;
        private int timeDelayLog = 300;
        const string Version = "Version : 1";

        public MainWindow()
        {
            InitializeComponent();
            InitM1();
            InitApp();
            InitSysTime();
            InitLog();
        }

        private void buttonSetRefreshTime_Click(object sender, RoutedEventArgs e)
        {
            timeInterval = Int32.Parse(textBoxRefreshTime.Text);
            myTimer.Interval = timeInterval;
            timeDelayApp = (timeInterval * 4)/ 10;
            timeDelayLog = (timeInterval * 3) / 10;

            MessageBoxResult result = MessageBox.Show("Refresh Time is Set!");
        }

        private void comboBoxComPorts_Loaded(object sender, RoutedEventArgs e)
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


            // ... Get the ComboBox reference.
            var comboBox = sender as ComboBox;

            // ... Assign the ItemsSource to the List.
            comboBox.ItemsSource = data;

            // ... Make the first item selected.
            comboBox.SelectedIndex = 0;
        }

    }
}
