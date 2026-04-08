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

        BackgroundWorker workerLog;
        private static System.Timers.Timer myTimerLog;

        private void InitLog()
        {
            // Create a timer
            myTimerLog = new System.Timers.Timer();
            // Tell the timer what to do when it elapses
            myTimerLog.Elapsed += new ElapsedEventHandler(myEventLog);
            // Set it to go off every five seconds
            myTimerLog.Interval = timeInterval;
            // Don't Start the time yet      
            myTimerLog.Enabled = false;

            workerLog = new BackgroundWorker();
            workerLog.DoWork += workerLog_DoWork;

        }

        private void myEventLog(object source, ElapsedEventArgs e)
        {
            if (!workerLog.IsBusy)
                workerLog.RunWorkerAsync();
        }


        private void workerLog_DoWork(object sender, DoWorkEventArgs e)
        {
            do_Logging();
        }

        int logCounter = 0;
        string timeStamp;

        private void do_Logging()
        {
            string tmpStr;
            string tmpLogStr;
            try
            {
                if (0 == logCounter)
                {
                    timeStamp = string.Format("{0:yyyy_MM_dd_hh_mm_ss_tt}", DateTime.Now);
                    logCounter = 0;
                }

                logCounter++;
                if (logCounter > 9999)
                {
                    logCounter = 0;
                }

                if (1 == logCounter)
                {
                    tmpStr = "AD7;AD6;AD5;AD4;AD3;AD2;AD1;AD0;DIO7;DIO6;DIO5;DIO4;DIO3;DIO2;DIO1;DIO0;JP18;JP19;JP3;JP4;JP5;JP6;JP7;JP8;JP9;JP10;M1CUR;M2CUR;BoardTemperature;KeyStatus;HeaterTemperature;EngineTemperature;EnginePressure;MaxTopPressure;MinTopPressure;ValvePosition;RadiatorFan;BurnerFan;FeederStatus;IgnitorStatus;InverterStatus;CompressorStatus;SDCardStatus;Error;ErrorCode;ErrorString;InverterOnCounter;InverterOffCounter;LogReturn;LastLogReturn;Stage;InitialDoseTime;InitialStartBurnerFanDelay;CombustionSuccessTemp;CombustionBuildUpTime;InputPelletPowerKWSt3;BurnerSpeedStage2;BurnerSpeedStage3;FeedOnTimeStage3;BurnerSpeedStage4;FeedOnTimeStage4;BurnerFanSwitchOffTemperature;InputPelletPowerKW;InverterOnTemperature;InverterOffTemperature;InverterDelayCounter;ProcessMinHeaterTemp;ProcessMaxHeaterTemp;ErrProcTempLowThresh;";
                    //Pass the filepath and filename to the StreamWriter Constructor
                    StreamWriter sw1 = new StreamWriter("Log_" + timeStamp + ".txt", true);
                    sw1.WriteLine(tmpStr);
                    sw1.Close();
                }

                Dispatcher.Invoke(new Action(() =>
                {
                    tmpLogStr = textBox_AD7.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_AD6.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_AD5.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_AD4.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_AD3.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_AD2.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_AD1.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_AD0.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_DIO7.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_DIO6.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_DIO5.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_DIO4.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_DIO3.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_DIO2.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_DIO1.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_DIO0.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP18.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP19.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP3.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP4.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP5.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP6.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP7.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP8.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP9.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_JP10.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_M1CUR.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_M2CUR.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_BoardTemperature.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_KeyStatus.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_HeaterTemperature.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_EngineTemperature.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_EnginePressure.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_MaxTopPressure.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_MinTopPressure.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_ValvePosition.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_RadiatorFan.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_BurnerFan.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_FeederStatus.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_IgnitorStatus.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InverterStatus.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_CompressorStatus.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_SDCardStatus.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_Error.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_ErrorCode.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_ErrorString.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InverterOnCounter.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InverterOffCounter.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_LogReturn.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_LastLogReturn.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_Stage.Text + ";";

                    tmpLogStr = tmpLogStr + textBox_InitialDoseTime.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InitialStartBurnerFanDelay.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_CombustionSuccessTemp.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_CombustionBuildUpTime.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InputPelletPowerKWSt3.Text + "; ";
                    tmpLogStr = tmpLogStr + textBox_BurnerSpeedStage2.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_BurnerSpeedStage3.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_FeedOnTimeStage3.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_BurnerSpeedStage4.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_FeedOnTimeStage4.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_BurnerFanSwitchOffTemperature.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InputPelletPowerKW.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InverterOnTemperature.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InverterOffTemperature.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_InverterDelayCounter.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_ProcessMinHeaterTemp.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_ProcessMaxHeaterTemp.Text + ";";
                    tmpLogStr = tmpLogStr + textBox_ErrProcTempLowThresh.Text + ";";

                    StreamWriter sw = new StreamWriter("Log_" + timeStamp + ".txt", true);
                    sw.WriteLine(tmpLogStr);
                    //Close the file
                    sw.Close();
                }));

            }
            catch (Exception ex)
            {
                MessageBoxResult result = MessageBox.Show("Exception: " + ex.Message);
            }
            finally
            {
                Console.WriteLine("Executing finally block.");
            }
        }

    }
}