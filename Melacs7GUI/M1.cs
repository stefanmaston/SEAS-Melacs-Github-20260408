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
        private static System.Timers.Timer myTimer;
        private static System.Timers.Timer shutDownTimer;
        BackgroundWorker workerConnectM1;
        //BackgroundWorker workerRecvMsgM1;

        String exceptionM1 = "No Exception Yet";

        //Receive Data
        private bool variable_NewData;
        private int variable_AD7;
        private int variable_AD6;
        private int variable_AD5;
        private int variable_AD4;
        private int variable_AD3;
        private int variable_AD2;
        private int variable_AD1;
        private int variable_AD0;
        private int variable_DIO7;
        private int variable_DIO6;
        private int variable_DIO5;
        private int variable_DIO4;
        private int variable_DIO3;
        private int variable_DIO2;
        private int variable_DIO1;
        private int variable_DIO0;
        private double variable_JP18;
        private double variable_JP19;
        private int variable_JP3;
        private int variable_JP4;
        private int variable_JP5;
        private int variable_JP6;
        private int variable_JP7;
        private int variable_JP8;
        private int variable_JP9;
        private int variable_JP10;
        private double variable_M1CUR;
        private double variable_M2CUR;
        private int variable_BoardTemperature;
        private bool variable_KeyStatus;
        private int variable_HeaterTemperature;
        private int variable_EngineTemperature;
        private int variable_EnginePressure;
        private int variable_MaxTopPressure;
        private int variable_MinTopPressure;
        private int variable_ValvePosition;
        private double variable_RadiatorFan;
        private double variable_BurnerFan;
        private bool variable_FeederStatus;
        private bool variable_IgnitorStatus;
        private bool variable_InverterStatus;
        private bool variable_CompressorStatus;
        private bool variable_SDCardStatus;
        private int variable_Error;
        private int variable_ErrorCode;
        private string variable_ErrorString;
        private int variable_InverterOnCounter;
        private int variable_InverterOffCounter;
        private int variable_LogReturn;
        private int variable_LastLogReturn;
        private int variable_Stage;
        private bool variable_SystemStatus;
        private double variable_PelletFeedKW;

        //Send Data
        private bool variable_SendShutdown;
        private bool variable_SDCardMount;
        private bool variable_PageChangeEnable;
        private bool variable_ResetErrorAndWarnings;
        private int variable_BurstPeriod;
        private int variable_BurstLength;
        private int variable_AveragingBurstLength;
        private int variable_BurstDelay;
        private double variable_MaxRadiatorFanVoltage;
        private double variable_MinRadiatorFanVoltage;
        private int variable_MaxRadiatorFanTemp;
        private int variable_MinRadiatorFanTemp;
        private int variable_SwitchOffRadiatorFanTemp;
        private int variable_MaxValvePosTemp;
        private int variable_MinValvePosTemp;
        private int variable_SwitchOffValvePositionTemp;
        private int variable_InitialDoseTime;
        private int variable_ExtraDoseTime;
        private bool variable_ExtraDoseEnable;
        private int variable_InitialStartBurnerFanDelay;
        private int variable_InitialStartBurnerTemp;
        private int variable_CombustionSuccessTemp;
        private int variable_AfterCombustionBuildUpTime;
        private double variable_InputPelletPowerKWSt3;
        private double variable_BurnerSpeedStage2;
        private double variable_BurnerSpeedStage3;
        private int variable_FeedOnTimeStage3;
        private int variable_BurnerFanSwitchOffTemperature;
        private double variable_InputPelletPowerKW;
        private int variable_InverterOnTemperature;
        private int variable_InverterOffTemperature;
        private int variable_InverterDelayCounter;
        private int variable_ProcessMinHeaterTemp;
        private int variable_ProcessMaxHeaterTemp;
        private int variable_ErrProcTempLowThresh;
        private int variable_FinalFeedRampUpTime;
        private double variable_BurnerSpeedStage4;
        private int variable_FeedOnTimeStage4;
        private bool variable_SaveParameterFile;
        private int variable_LogSamplePeriod;
        private int variable_NumOfSampleInEachLog;
        private int variable_TimeToBurstLog;
        private int variable_NumOfSamplesInBurstLog;
        private string variable_SystemTime;
        private bool variable_SynSystemTime;
        private int variable_SystemYear;
        private int variable_SystemMonth;
        private int variable_SystemDay;
        private int variable_SystemHour;
        private int variable_SystemMinute;
        private int variable_SystemSecond;
        private int variable_SystemWeekday;
        private bool variable_SynManualTime;
        private int variable_Year;
        private int variable_Month;
        private int variable_Day;
        private int variable_Hour;
        private int variable_Minute;
        private int variable_Second;
        private int variable_Weekday;

        private bool variable_EnableOverrideBurnerFan;
        private double variable_OverrideBurnerFan;
        private bool variable_EnableOverrideRadiatorFan;
        private double variable_OverrideRadiatorFan;
        private bool variable_EnableOverrideValvePosition;
        private int variable_OverrideValvePosition;

        private bool variable_EnableOverrideCirculationPump;
        private int variable_OverrideCirculationPump;

        private bool variable_EnableOverrideFeeder;
        private int variable_OverrideFeeder;

        private bool variable_EnableOverrideIgnitor;
        private int variable_OverrideIgnitor;

        private bool variable_EnableOverrideInverter;
        private int variable_OverrideInverter;

        private bool variable_EnableOverrideKey;
        private int variable_OverrideKey;

        private bool variable_EnableOverrideGas;
        private int variable_OverrideGas;

        private bool variable_EnableSettingPressure;
        private int variable_SetPressure;
        private int variable_LowestCoolerTemp;
        private int variable_HighestCoolerTemp;
        private int variable_LowestHeaterTemp;
        private int variable_HighestHeaterTemp;
        private int variable_LowestGasPressure;
        private int variable_HighestGasPressure;

        private bool variable_EnableGas;
        private int variable_GasThermostatMinTemp;
        private int variable_GasThermostatMaxTemp;

        private System.ComponentModel.IContainer components = null;
        private System.IO.Ports.SerialPort serialPort1;

        const int ERROR_IN_COMBUSTION = 101;
        const int ERROR_OVERCURRENT_RADIATORFAN = 102;
        const int ERROR_OVERCURRENT_BURNERFAN = 103;
        const int ERROR_SD_CORRUPTION = 104;

        const int UNUSUAL_PRESSURE_VALUE = 111;
        const int UNUSUAL_ENGINE_TEMPERATURE = 112;
        const int UNUSUAL_HEATER_TEMPERATURE = 113;

        Dictionary<int, string> errorDict;

        private void InitM1()
        {
            buttonDisconnect.IsHitTestVisible = false;
            buttonShutdown.IsHitTestVisible = false;

            // Create a timer
            myTimer = new System.Timers.Timer();
            // Tell the timer what to do when it elapses
            myTimer.Elapsed += new ElapsedEventHandler(myEventM1);
            // Set it to go off every five seconds
            myTimer.Interval = timeInterval;
            // Don't Start the time yet      
            myTimer.Enabled = false;

            shutDownTimer = new System.Timers.Timer();
            // Tell the timer what to do when it elapses
            shutDownTimer.Elapsed += new ElapsedEventHandler(shutdownEvent);
            // Set it to go off every five seconds
            shutDownTimer.Interval = timeShutdownDelay;
            // Don't Start the time yet      
            shutDownTimer.Enabled = false;

            workerConnectM1 = new BackgroundWorker();
            workerConnectM1.DoWork += workerConnectM1_DoWork;
            workerConnectM1.RunWorkerCompleted += workerConnectM1_RunWorkerCompleted;

            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            serialPort1.PortName = "COM3";
            serialPort1.BaudRate = 115200;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);

            errorDict = new Dictionary<int, string>();

            errorDict.Add(1, "General alarm on \"engine fault\"");
            errorDict.Add(2, "Cooler temperature too low");
            errorDict.Add(3, "Cooler temperature too high");
            errorDict.Add(4, "Cooler flow too low");
            errorDict.Add(5, "Cooler flow too high");
            errorDict.Add(6, "Heater temperature too low");
            errorDict.Add(7, "Heater temperature too high");
            errorDict.Add(8, "Working gas pressure too low");
            errorDict.Add(9, "Working gas pressure too high");
            errorDict.Add(10, "Working gas leakage possible");
            errorDict.Add(11, "Inverter frequency too low");
            errorDict.Add(12, "Inverter frequency too high");
            errorDict.Add(13, "Inverter voltage too low");
            errorDict.Add(14, "Inverter voltage too high");
            errorDict.Add(15, "Inverter current too high");
            errorDict.Add(16, "Inverter temperature too high");
            errorDict.Add(17, "Inverter cosinus out of spec.");
            errorDict.Add(18, "Inverter power circuit fault");
            errorDict.Add(19, "Inverter DC-bus voltage too low");
            errorDict.Add(20, "Inverter DC-bus voltage too high.");
            errorDict.Add(21, "Inverter bypass relay not responding.");
            errorDict.Add(22, "Power supply 3,3v fault");
            errorDict.Add(23, "Power supply 5v fault");
            errorDict.Add(24, "Power supply 12v fault");
            errorDict.Add(25, "Power supply 24v fault A25");
            errorDict.Add(26, "Power supply for \"sleep mode\" fault");
            errorDict.Add(27, "Battery voltage too low");
            errorDict.Add(28, "Battery voltage too high");
            errorDict.Add(29, "Battery current too high");
            errorDict.Add(30, "Battery temperature to high");
            errorDict.Add(31, "Battery cell fault A31");
            errorDict.Add(32, "Battery main switch fault");
            errorDict.Add(33, "Battery data bus not responding");
            errorDict.Add(34, "Inclinometer fault.");
            errorDict.Add(35, "Vibrations out of spec");
            errorDict.Add(36, "Balancing out of spec");
            errorDict.Add(37, "Generator voltage too low");
            errorDict.Add(38, "Generator phase show zero voltage");
            errorDict.Add(39, "Generator starter function fault A39.");
            errorDict.Add(40, "Generator current too high");
            errorDict.Add(41, "Generator current too low");
            errorDict.Add(42, "Solar input MMP voltage out of spec");
            errorDict.Add(43, "Solar input MMP current out of spec");
            errorDict.Add(44, "Fuel level low");
            errorDict.Add(45, "Coolant level low");
            errorDict.Add(46, "Coolant leakage possible");
            errorDict.Add(47, "Ash tray need to be emptied");
            errorDict.Add(48, "Generator operating time > 20 000 hour");

            errorDict.Add(ERROR_IN_COMBUSTION, "Error in Combustion");
            errorDict.Add(ERROR_OVERCURRENT_RADIATORFAN, "Overcurrent in Radiator Fan");
            errorDict.Add(ERROR_OVERCURRENT_BURNERFAN, "Overcurrent in Burner Fan");
            errorDict.Add(ERROR_SD_CORRUPTION, "Most Probably SD card corruption");

            errorDict.Add(UNUSUAL_PRESSURE_VALUE, "Usual Pressure Sensor Value, Chances that Pressure Sensor Not Connected");
            errorDict.Add(UNUSUAL_ENGINE_TEMPERATURE, "Usual Engine Temperature, Chances that Temperature Sensor Not Connected");
            errorDict.Add(UNUSUAL_HEATER_TEMPERATURE, "Usual Heater Temperature, Chances that Heater Thermocouple Not Connected");

            InitParameters();
        }

        private void InitParameters()
        {
            variable_SendShutdown = false;
            variable_SystemStatus = true;
            variable_SDCardMount = true;
            checkBoxSDCardMount.IsChecked = variable_SDCardMount;
            variable_PageChangeEnable = false;
            checkBoxPageChangeEnable.IsChecked = variable_PageChangeEnable;
            variable_ResetErrorAndWarnings = false;
            checkBoxResetErrorAndWarnings.IsChecked = variable_ResetErrorAndWarnings;
            variable_BurstPeriod = 5;
            textBox_BurstPeriod.Text = variable_BurstPeriod.ToString();
            variable_BurstLength = 700;
            textBox_BurstLength.Text = variable_BurstLength.ToString();
            variable_AveragingBurstLength = 100;
            textBox_AveragingBurstLength.Text = variable_AveragingBurstLength.ToString();
            variable_BurstDelay = 100;
            textBox_BurstDelay.Text = variable_BurstDelay.ToString();
            variable_MaxRadiatorFanVoltage = 8;
            textBox_MaxRadiatorFanVoltage.Text = variable_MaxRadiatorFanVoltage.ToString();
            variable_MinRadiatorFanVoltage = 2.4;
            textBox_MinRadiatorFanVoltage.Text = variable_MinRadiatorFanVoltage.ToString();
            variable_MaxRadiatorFanTemp = 85;
            textBox_MaxRadiatorFanTemp.Text = variable_MaxRadiatorFanTemp.ToString();
            variable_MinRadiatorFanTemp = 75;
            textBox_MinRadiatorFanTemp.Text = variable_MinRadiatorFanTemp.ToString();
            variable_SwitchOffRadiatorFanTemp = 50;
            textBox_SwitchOffRadiatorFanTemp.Text = variable_SwitchOffRadiatorFanTemp.ToString();
            variable_MaxValvePosTemp = 85;
            textBox_MaxValvePosTemp.Text = variable_MaxValvePosTemp.ToString();
            variable_MinValvePosTemp = 75;
            textBox_MinValvePosTemp.Text = variable_MinValvePosTemp.ToString();
            variable_SwitchOffValvePositionTemp = 65;
            textBox_SwitchOffValvePositionTemp.Text = variable_SwitchOffValvePositionTemp.ToString();
            variable_InitialDoseTime = 15;
            textBox_InitialDoseTime.Text = variable_InitialDoseTime.ToString();
            variable_ExtraDoseTime = 10;
            textBox_ExtraDoseTime.Text = variable_ExtraDoseTime.ToString();
            variable_InitialStartBurnerFanDelay = 180;
            textBox_InitialStartBurnerFanDelay.Text = variable_InitialStartBurnerFanDelay.ToString();
            variable_InitialStartBurnerTemp = 40;
            textBox_InitialStartBurnerTemp.Text = variable_InitialStartBurnerTemp.ToString();
            variable_CombustionSuccessTemp = 50;
            textBox_CombustionSuccessTemp.Text = variable_CombustionSuccessTemp.ToString();
            variable_AfterCombustionBuildUpTime = 120;
            textBox_CombustionBuildUpTime.Text = variable_AfterCombustionBuildUpTime.ToString();
            variable_BurnerSpeedStage2 = 4.2;
            sliderBurnerSpeedStage2.Value = variable_BurnerSpeedStage2;
            textBox_CombustionSuccessTemp.Text = variable_CombustionSuccessTemp.ToString();
            variable_BurnerSpeedStage3 = 6;
            sliderBurnerSpeedStage3.Value = variable_BurnerSpeedStage3;
            variable_FeedOnTimeStage3 = 5;
            sliderFeedOnTimeStage3.Value = variable_FeedOnTimeStage3;
            variable_BurnerFanSwitchOffTemperature = 50;
            textBox_BurnerFanSwitchOffTemperature.Text = variable_BurnerFanSwitchOffTemperature.ToString();
            variable_InputPelletPowerKW =3.423;
            textBox_InputPelletPowerKW.Text = variable_InputPelletPowerKW.ToString();
            variable_ProcessMinHeaterTemp = 300;
            textBox_ProcessMinHeaterTemp.Text = variable_ProcessMinHeaterTemp.ToString();
            variable_ProcessMaxHeaterTemp = 1100;
            textBox_ProcessMaxHeaterTemp.Text = variable_ProcessMaxHeaterTemp.ToString();
            variable_ErrProcTempLowThresh = 200;
            textBox_ErrProcTempLowThresh.Text = variable_ErrProcTempLowThresh.ToString();
            variable_FinalFeedRampUpTime = 1200;
            textBox_FinalFeedRampUpTime.Text = variable_FinalFeedRampUpTime.ToString();
            variable_BurnerSpeedStage4 = 11;
            sliderBurnerSpeedStage4.Value = variable_BurnerSpeedStage4;
            variable_FeedOnTimeStage4 = 10;
            sliderFeedOnTimeStage4.Value = variable_FeedOnTimeStage4;
            variable_SaveParameterFile = true;
            checkBoxSaveParaFile.IsChecked = variable_SaveParameterFile;
            variable_LogSamplePeriod = 10;
            textBox_LogSamplePeriod.Text = variable_LogSamplePeriod.ToString();
            variable_NumOfSampleInEachLog = 36;
            textBox_NumOfSampleInEachLog.Text = variable_NumOfSampleInEachLog.ToString();
            variable_TimeToBurstLog = 360;
            textBox_TimeToBurstLog.Text = variable_TimeToBurstLog.ToString();
            variable_NumOfSamplesInBurstLog = 100;
            textBox_NumOfSamplesInBurstLog.Text = variable_NumOfSamplesInBurstLog.ToString();
            variable_SystemTime = string.Format("{0:yyyy:MM:dd hh:mm:ss tt }", DateTime.Now) + (DateTime.Now.DayOfWeek).ToString();
            textBoxSystemTime.Text = variable_SystemTime;
            variable_SynSystemTime = true;
            checkBoxSynSystemTime.IsChecked = variable_SynSystemTime;
            variable_SystemYear = DateTime.Now.Year;
            variable_SystemMonth = DateTime.Now.Month;
            variable_SystemDay = DateTime.Now.Day;
            variable_SystemHour = DateTime.Now.Hour;
            variable_SystemMinute = DateTime.Now.Minute;
            variable_SystemSecond = DateTime.Now.Second;
            variable_SystemWeekday = (int)DateTime.Now.DayOfWeek;
            variable_SynManualTime = false;
            checkBoxSynManualTime.IsChecked = variable_SynManualTime;
            variable_Year = DateTime.Now.Year;
            textBox_Year.Text = variable_Year.ToString();
            variable_Month = DateTime.Now.Month;
            textBox_Month.Text = variable_Month.ToString();
            variable_Day = DateTime.Now.Day;
            textBox_Day.Text = variable_Day.ToString();
            variable_Hour = DateTime.Now.Hour;
            textBox_Hour.Text = variable_Hour.ToString();
            variable_Minute = DateTime.Now.Minute;
            textBox_Minute.Text = variable_Minute.ToString();
            variable_Second = DateTime.Now.Second;
            textBox_Second.Text = variable_Second.ToString();
            variable_Weekday = (int)DateTime.Now.DayOfWeek;
            textBox_Weekday.Text = variable_Weekday.ToString();
            
            variable_SetPressure = 10;
            textBox_SetPressure.Text = variable_SetPressure.ToString();
            variable_LowestCoolerTemp = 5;
            textBox_LowestCoolerTemp.Text = variable_LowestCoolerTemp.ToString();
            variable_HighestCoolerTemp = 95;
            textBox_HighestCoolerTemp.Text = variable_HighestCoolerTemp.ToString();
            variable_LowestHeaterTemp = 0;
            textBox_LowestHeaterTemp.Text = variable_LowestHeaterTemp.ToString();
            variable_HighestHeaterTemp = 1050;
            textBox_HighestHeaterTemp.Text = variable_HighestHeaterTemp.ToString();
            variable_LowestGasPressure = 6;
            textBox_LowestGasPressure.Text = variable_LowestGasPressure.ToString();
            variable_HighestGasPressure = 50;
            textBox_HighestGasPressure.Text = variable_HighestGasPressure.ToString();

            variable_GasThermostatMinTemp = 600;
            textBox_GasThermostatMinTemp.Text = variable_GasThermostatMinTemp.ToString();
            variable_GasThermostatMaxTemp = 900;
            textBox_GasThermostatMaxTemp.Text = variable_GasThermostatMaxTemp.ToString();

            variable_InverterOnTemperature = 600;
            textBox_InverterOnTemperature.Text = variable_InverterOnTemperature.ToString();
            variable_InverterOffTemperature = 500;
            textBox_InverterOffTemperature.Text = variable_InverterOffTemperature.ToString();
            variable_InverterDelayCounter = 100;
            textBox_InverterDelayCounter.Text = variable_InverterDelayCounter.ToString();

            slider_OverrideCirculationPump.Background = new SolidColorBrush(Colors.Red);
            slider_OverrideFeeder.Background = new SolidColorBrush(Colors.Red);
            slider_OverrideIgnitor.Background = new SolidColorBrush(Colors.Red);
            slider_OverrideInverter.Background = new SolidColorBrush(Colors.Red);
            slider_OverrideKey.Background = new SolidColorBrush(Colors.Red);
            slider_OverrideGas.Background = new SolidColorBrush(Colors.Red);


            loadControlParameters();

            checkBox_UpdatePeripheralSettings.IsChecked = true;
            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            checkBox_UpdatePostCombustionSettings.IsChecked = true;
            checkBox_UpdateSDCardLogSettings.IsChecked = true;
            checkBox_UpdateDateTimeSettings.IsChecked = true;
            checkBox_UpdateOverrides.IsChecked = true;
            checkBox_UpdateGasSystem.IsChecked = true;
            checkBox_UpdateInverterSettings.IsChecked = true;
            checkBox_UpdateEngineSettings.IsChecked = true;

            textBox_ErrorString.Background = new SolidColorBrush(Colors.Transparent);

            /*
            slider_OverrideBurnerFan.Visibility = Visibility.Hidden;
            textBox_OverrideBurnerFan.Visibility = Visibility.Hidden;
            label_OverrideBurnerFan.Visibility = Visibility.Hidden;
            checkBox_OverrideBurnerFan.Visibility = Visibility.Hidden;
            slider_OverrideRadiatorFan.Visibility = Visibility.Hidden;
            textBox_OverrideRadiatorFan.Visibility = Visibility.Hidden;
            label_OverrideRadiatorFan.Visibility = Visibility.Hidden;
            checkBox_OverrideRadiatorFan.Visibility = Visibility.Hidden;
            slider_OverrideValvePosition.Visibility = Visibility.Hidden;
            textBox_OverrideValvePosition.Visibility = Visibility.Hidden;
            label_OverrideValvePosition.Visibility = Visibility.Hidden;
            checkBox_OverrideValvePosition.Visibility = Visibility.Hidden;
            label_OverrideCirculationPump.Visibility = Visibility.Hidden;
            slider_OverrideCirculationPump.Visibility = Visibility.Hidden;
            checkBox_EnableOverrideCirculationPump.Visibility = Visibility.Hidden;
            textBox_OverrideCirculationPump.Visibility = Visibility.Hidden;
            label_OverrideFeeder.Visibility = Visibility.Hidden;
            slider_OverrideFeeder.Visibility = Visibility.Hidden;
            checkBox_EnableOverrideFeeder.Visibility = Visibility.Hidden;
            textBox_OverrideFeeder.Visibility = Visibility.Hidden;
            label_OverrideIgnitor.Visibility = Visibility.Hidden;
            slider_OverrideIgnitor.Visibility = Visibility.Hidden;
            checkBox_EnableOverrideIgnitor.Visibility = Visibility.Hidden;
            textBox_OverrideIgnitor.Visibility = Visibility.Hidden;
            label_OverrideInverter.Visibility = Visibility.Hidden;
            slider_OverrideInverter.Visibility = Visibility.Hidden;
            checkBox_EnableOverrideInverter.Visibility = Visibility.Hidden;
            textBox_OverrideInverter.Visibility = Visibility.Hidden;
            label_OverrideKey.Visibility = Visibility.Hidden;
            slider_OverrideKey.Visibility = Visibility.Hidden;
            checkBox_EnableOverrideKey.Visibility = Visibility.Hidden;
            textBox_OverrideKey.Visibility = Visibility.Hidden;
            label_OverrideGas.Visibility = Visibility.Hidden;
            slider_OverrideGas.Visibility = Visibility.Hidden;
            checkBox_EnableOverrideGas.Visibility = Visibility.Hidden;
            textBox_OverrideGas.Visibility = Visibility.Hidden;
            textBox_GasThermostatMinTemp.Visibility = Visibility.Hidden;
            textBox_GasThermoStatMaxTemp.Visibility = Visibility.Hidden;
            checkBoxEnableGas.Visibility = Visibility.Hidden;
            LabelSetPressure.Visibility = Visibility.Hidden;
            textBox_SetPressure.Visibility = Visibility.Hidden;
            checkBoxEnableSettingPressure.Visibility = Visibility.Hidden;
            LabelOverrides.Visibility = Visibility.Hidden;
            LabelEngineSettings.Visibility = Visibility.Hidden;
            LabelGasSystems.Visibility = Visibility.Hidden;
            checkBox_UpdateOverrides.Visibility = Visibility.Hidden;
            checkBox_UpdateGasSystem.Visibility = Visibility.Hidden;
            checkBox_UpdateEngineSettings.Visibility = Visibility.Hidden;
            Label_GasThermostatMinTemp.Visibility = Visibility.Hidden;
            Label_GasThermostatMaxTemp.Visibility = Visibility.Hidden;
            LabelLowestCoolerTemp.Visibility = Visibility.Hidden;
            textBox_LowestCoolerTemp.Visibility = Visibility.Hidden;
            LabelHighestCoolerTemp.Visibility = Visibility.Hidden;
            textBox_HighestCoolerTemp.Visibility = Visibility.Hidden;
            LabelLowestHeaterTemp.Visibility = Visibility.Hidden;
            textBox_LowestHeaterTemp.Visibility = Visibility.Hidden;
            LabelHighestHeaterTemp.Visibility = Visibility.Hidden;
            textBox_HighestHeaterTemp.Visibility = Visibility.Hidden;
            LabelLowestGasPressure.Visibility = Visibility.Hidden;
            textBox_LowestGasPressure.Visibility = Visibility.Hidden;
            LabelHighestGasPressure.Visibility = Visibility.Hidden;
            textBox_HighestGasPressure.Visibility = Visibility.Hidden;
            */
        }

        int countMsgType = 0;
        // Implement a call with the right signature for events going off
        private void myEventM1(object source, ElapsedEventArgs e)
        {
            int sendLength = 100;
            string sendString;

            int i = 0;
            if (serialPort1.IsOpen)
            {
                byte[] b = new byte[sendLength];

                Dispatcher.Invoke(new Action(() =>
                {   //60 bytes
                    b[i++] = (byte)0xFF;
                    b[i++] = (byte)1;//send the first byte as one

                    while(true)
                    {
                        if (10 == countMsgType)
                        {
                            countMsgType = 0;
                        }

                        if (0 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdatePeripheralSettings.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;
                                b[i++] = variable_SDCardMount ? (byte)1 : (byte)0;
                                b[i++] = variable_PageChangeEnable ? (byte)1 : (byte)0;
                                b[i++] = variable_ResetErrorAndWarnings ? (byte)1 : (byte)0;
                                b[i++] = (byte)variable_BurstPeriod;
                                b[i++] = (byte)(variable_BurstLength / 100);
                                b[i++] = (byte)variable_AveragingBurstLength;
                                b[i++] = (byte)(variable_BurstDelay >> 8);
                                b[i++] = (byte)(variable_BurstDelay & 0x00FF);
                                checkBox_UpdatePeripheralSettings.IsChecked = false;
                                checkBoxResetErrorAndWarnings.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (1 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdateEngineTemperatureControlSettings.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;
                                b[i++] = (byte)(variable_MaxRadiatorFanVoltage * 10);
                                b[i++] = (byte)(variable_MinRadiatorFanVoltage * 10);
                                b[i++] = (byte)variable_MaxRadiatorFanTemp;
                                b[i++] = (byte)variable_MinRadiatorFanTemp;
                                b[i++] = (byte)variable_SwitchOffRadiatorFanTemp;
                                b[i++] = (byte)variable_MaxValvePosTemp;
                                b[i++] = (byte)variable_MinValvePosTemp;
                                b[i++] = (byte)variable_SwitchOffValvePositionTemp;
                                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (2 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdatePreCombustionSequenceSettings.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;
                                if (true == variable_ExtraDoseEnable)
                                {
                                    b[i++] = (byte)(variable_InitialDoseTime + variable_ExtraDoseTime);
                                }
                                else
                                {
                                    b[i++] = (byte)variable_InitialDoseTime;
                                }
                                b[i++] = (byte)(variable_InitialStartBurnerFanDelay/10);
                                b[i++] = (byte)(variable_InitialStartBurnerTemp / 5);
                                b[i++] = (byte)(variable_CombustionSuccessTemp/10);
                                b[i++] = (byte)(variable_AfterCombustionBuildUpTime / 10);
                                b[i++] = (byte)(variable_BurnerSpeedStage2 * 10);
                                b[i++] = (byte)(variable_BurnerSpeedStage3 * 10);
                                b[i++] = (byte)(variable_FeedOnTimeStage3 >> 8);
                                b[i++] = (byte)(variable_FeedOnTimeStage3 & 0x00FF);

                                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (3 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdatePostCombustionSettings.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;
                                b[i++] = (byte)variable_BurnerFanSwitchOffTemperature;
                                //b[i++] = (byte)variable_InputPelletPowerKW;
                                b[i++] = (byte)(variable_ProcessMinHeaterTemp/10);
                                b[i++] = (byte)(variable_ProcessMaxHeaterTemp/10);
                                b[i++] = (byte)(variable_ErrProcTempLowThresh/10);
                                b[i++] = (byte)(variable_FinalFeedRampUpTime >> 8);
                                b[i++] = (byte)(variable_FinalFeedRampUpTime & 0x00FF);
                                b[i++] = (byte)(variable_BurnerSpeedStage4 * 10);
                                b[i++] = (byte)(variable_FeedOnTimeStage4 >> 8);
                                b[i++] = (byte)(variable_FeedOnTimeStage4 & 0x00FF);

                                checkBox_UpdatePostCombustionSettings.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (4 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdateSDCardLogSettings.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;
                                b[i++] =  variable_SaveParameterFile ? (byte)1 : (byte)0;
                                b[i++] = (byte)variable_LogSamplePeriod;
                                b[i++] = (byte)variable_NumOfSampleInEachLog;
                                b[i++] = (byte)(variable_TimeToBurstLog/10);
                                b[i++] = (byte)(variable_NumOfSamplesInBurstLog/100);

                                checkBoxSaveParaFile.IsChecked = false;
                                checkBox_UpdateSDCardLogSettings.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (5 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdateDateTimeSettings.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;
                                if (true == variable_SynManualTime)
                                {
                                    b[i++] = variable_SynManualTime ? (byte)1 : (byte)0;
                                    b[i++] = (byte)(variable_Year - 2000);
                                    b[i++] = (byte)variable_Month;
                                    b[i++] = (byte)variable_Day;
                                    b[i++] = (byte)variable_Hour;
                                    b[i++] = (byte)variable_Minute;
                                    b[i++] = (byte)variable_Second;
                                    b[i++] = (byte)variable_Weekday;
                                }
                                else
                                {
                                    b[i++] = variable_SynSystemTime ? (byte)1 : (byte)0;
                                    b[i++] = (byte)(variable_SystemYear - 2000);
                                    b[i++] = (byte)variable_SystemMonth;
                                    b[i++] = (byte)variable_SystemDay;
                                    b[i++] = (byte)variable_SystemHour;
                                    b[i++] = (byte)variable_SystemMinute;
                                    b[i++] = (byte)variable_SystemSecond;
                                    b[i++] = (byte)variable_SystemWeekday;
                                }

                                checkBoxSynSystemTime.IsChecked = false;
                                checkBox_UpdateDateTimeSettings.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (6 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdateOverrides.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;

                                if (false == variable_EnableOverrideBurnerFan)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)(variable_OverrideBurnerFan*10);
                                }

                                if (false == variable_EnableOverrideRadiatorFan)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)(variable_OverrideRadiatorFan * 10);
                                }

                                if (false == variable_EnableOverrideValvePosition)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)variable_OverrideValvePosition;
                                }

                                if (false == variable_EnableOverrideCirculationPump)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)variable_OverrideCirculationPump;
                                }


                                if (false == variable_EnableOverrideFeeder)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)variable_OverrideFeeder;
                                }

                                if (false == variable_EnableOverrideIgnitor)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)variable_OverrideIgnitor;
                                }

                                if (false == variable_EnableOverrideInverter)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)variable_OverrideInverter;
                                }

                                if (false == variable_EnableOverrideKey)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)variable_OverrideKey;
                                }

                                if (false == variable_EnableOverrideGas)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)variable_OverrideGas;
                                }

                                checkBox_UpdateOverrides.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (7 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdateEngineSettings.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;

                                if (false == variable_EnableSettingPressure)
                                {
                                    b[i++] = 0xFF;
                                }
                                else
                                {
                                    b[i++] = (byte)variable_SetPressure;
                                }

                                b[i++] = (byte)variable_LowestCoolerTemp;
                                b[i++] = (byte)variable_HighestCoolerTemp;                                
                                b[i++] = (byte)(variable_LowestHeaterTemp / 10);
                                b[i++] = (byte)(variable_HighestHeaterTemp / 10);
                                b[i++] = (byte)variable_LowestGasPressure;
                                b[i++] = (byte)variable_HighestGasPressure;

                                checkBox_UpdateEngineSettings.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (8 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdateGasSystem.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;
                                b[i++] = variable_EnableGas ? (byte)1 : (byte)0;
                                b[i++] = (byte)(variable_GasThermostatMinTemp / 10);
                                b[i++] = (byte)(variable_GasThermostatMaxTemp / 10);

                                checkBox_UpdateGasSystem.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if (9 == countMsgType)
                        {
                            countMsgType++;
                            if (true == checkBox_UpdateInverterSettings.IsChecked)
                            {
                                b[i++] = (byte)countMsgType;
                                b[i++] = (byte)(variable_InverterOnTemperature / 10);
                                b[i++] = (byte)(variable_InverterOffTemperature / 10);
                                b[i++] = (byte)(variable_InverterDelayCounter / 10);

                                checkBox_UpdateInverterSettings.IsChecked = false;
                                goto MSG_SENT;
                            }
                        }

                        if ((false == checkBox_UpdatePeripheralSettings.IsChecked)
                        && (false == checkBox_UpdateEngineTemperatureControlSettings.IsChecked)
                        && (false == checkBox_UpdatePreCombustionSequenceSettings.IsChecked)
                        && (false == checkBox_UpdatePostCombustionSettings.IsChecked)
                        && (false == checkBox_UpdateSDCardLogSettings.IsChecked)
                        && (false == checkBox_UpdateDateTimeSettings.IsChecked)
                        && (false == checkBox_UpdateOverrides.IsChecked)
                        && (false == checkBox_UpdateEngineSettings.IsChecked)
                        && (false == checkBox_UpdateGasSystem.IsChecked)
                        && (false == checkBox_UpdateInverterSettings.IsChecked))
                        {
                            b[i++] = 0;
                            b[i++] = variable_SendShutdown ? (byte)1 : (byte)0;
                            //variable_SendShutdown = false;
                            goto MSG_SENT;
                        }
                    }

MSG_SENT:
                    sendString = b[0].ToString() + " ";
                    for (int j = 1; j < i; j++)
                    {
                        sendString = sendString + b[j].ToString() + " ";
                    }

                    serialPort1.Write(b, 0, i);
                    if(true == variable_SystemStatus)
                    { 
                        textBoxStatus.Text = "Sent : " + i.ToString() + " bytes \n" + sendString.ToString();
                    }
                }));
            }
            else
            {
                UpdateDisconnectedM1();
            }
        }

        const int RCV_SIZE = 80;

        private void UpdateLogM1(byte[] byteMsg, int bytesReceived)
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                string rcvString;
                int i = 0;
                //Ignore the first byte, reserved for future use. 72 bytes
                if(0xFF == byteMsg[i])
                {
                    i++;
                }

                variable_NewData = byteMsg[i++] > 0 ? true : false;
                if (true == variable_NewData)
                {
                    variable_NewData = false;
                    variable_AD7 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_AD6 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_AD5 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_AD4 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_AD3 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_AD2 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_AD1 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_AD0 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_DIO7 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_DIO6 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_DIO5 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_DIO4 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_DIO3 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_DIO2 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_DIO1 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_DIO0 = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_JP18 = byteMsg[i++];
                    variable_JP19 = byteMsg[i++];
                    variable_JP3 = byteMsg[i++];
                    variable_JP4 = byteMsg[i++];
                    variable_JP5 = byteMsg[i++];
                    variable_JP6 = byteMsg[i++];
                    variable_JP7 = byteMsg[i++];
                    variable_JP8 = byteMsg[i++];
                    variable_JP9 = byteMsg[i++];
                    variable_JP10 = byteMsg[i++];
                    variable_M1CUR = ((double)byteMsg[i++] / 10.0);
                    variable_M2CUR = ((double)byteMsg[i++] / 10.0);
                    variable_BoardTemperature = byteMsg[i++];
                    variable_KeyStatus = byteMsg[i++] > 0 ? true : false;
                    variable_HeaterTemperature = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_EngineTemperature = byteMsg[i++];
                    variable_EnginePressure = byteMsg[i++];
                    variable_MaxTopPressure = byteMsg[i++];
                    variable_MinTopPressure = byteMsg[i++];
                    variable_ValvePosition = byteMsg[i++];
                    variable_RadiatorFan = ((double)byteMsg[i++] / 10.0);
                    variable_BurnerFan = ((double)byteMsg[i++] / 10.0);
                    variable_FeederStatus = byteMsg[i++] > 0 ? true : false;
                    variable_IgnitorStatus = byteMsg[i++] > 0 ? true : false;
                    variable_InverterStatus = byteMsg[i++] > 0 ? true : false;
                    variable_CompressorStatus = byteMsg[i++] > 0 ? true : false;
                    variable_SDCardStatus = byteMsg[i++] > 0 ? true : false;
                    variable_Error = byteMsg[i++];
                    variable_ErrorCode = byteMsg[i++];
                    variable_InverterOnCounter = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_InverterOffCounter = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_LogReturn = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_LastLogReturn = (byteMsg[i] << 8) | byteMsg[i + 1]; i += 2;
                    variable_Stage = byteMsg[i++];
                    variable_SystemStatus = byteMsg[i++] > 0 ? true : false;
                    variable_PelletFeedKW = ((double)byteMsg[i++] / 10.0);
                }

                rcvString = byteMsg[0].ToString() + " ";
                for (int j = 1; j < i; j++)
                {
                    rcvString = rcvString + byteMsg[j].ToString() + " ";
                }

                textBoxStatus.Text = "Received : " + bytesReceived.ToString() + " bytes \n" + rcvString.ToString();

                textBox_AD7.Text = variable_AD7.ToString();
                textBox_AD6.Text = variable_AD6.ToString();
                textBox_AD5.Text = variable_AD5.ToString();
                textBox_AD4.Text = variable_AD4.ToString();
                textBox_AD3.Text = variable_AD3.ToString();
                textBox_AD2.Text = variable_AD2.ToString();
                textBox_AD1.Text = variable_AD1.ToString();
                textBox_AD0.Text = variable_AD0.ToString();
                textBox_DIO7.Text = variable_DIO7.ToString();
                textBox_DIO6.Text = variable_DIO6.ToString();
                textBox_DIO5.Text = variable_DIO5.ToString();
                textBox_DIO4.Text = variable_DIO4.ToString();
                textBox_DIO3.Text = variable_DIO3.ToString();
                textBox_DIO2.Text = variable_DIO2.ToString();
                textBox_DIO1.Text = variable_DIO1.ToString();
                textBox_DIO0.Text = variable_DIO0.ToString();
                textBox_JP18.Text = variable_JP18.ToString();
                textBox_JP19.Text = variable_JP19.ToString();
                textBox_JP3.Text = variable_JP3.ToString();
                textBox_JP4.Text = variable_JP4.ToString();
                textBox_JP5.Text = variable_JP5.ToString();
                textBox_JP6.Text = variable_JP6.ToString();
                textBox_JP7.Text = variable_JP7.ToString();
                textBox_JP8.Text = variable_JP8.ToString();
                textBox_JP9.Text = variable_JP9.ToString();
                textBox_JP10.Text = variable_JP10.ToString();
                textBox_M1CUR.Text = variable_M1CUR.ToString();
                textBox_M2CUR.Text = variable_M2CUR.ToString();
                textBox_BoardTemperature.Text = variable_BoardTemperature.ToString();
                textBox_KeyStatus.Text = variable_KeyStatus.ToString();
                textBox_HeaterTemperature.Text = variable_HeaterTemperature.ToString();
                textBox_EngineTemperature.Text = variable_EngineTemperature.ToString();
                textBox_EnginePressure.Text = variable_EnginePressure.ToString();
                textBox_MaxTopPressure.Text = variable_MaxTopPressure.ToString();
                textBox_MinTopPressure.Text = variable_MinTopPressure.ToString();
                textBox_ValvePosition.Text = variable_ValvePosition.ToString();
                textBox_RadiatorFan.Text = variable_RadiatorFan.ToString();
                textBox_BurnerFan.Text = variable_BurnerFan.ToString();
                textBox_FeederStatus.Text = variable_FeederStatus.ToString();
                textBox_IgnitorStatus.Text = variable_IgnitorStatus.ToString();
                textBox_InverterStatus.Text = variable_InverterStatus.ToString();
                textBox_CompressorStatus.Text = variable_CompressorStatus.ToString();
                textBox_SDCardStatus.Text = variable_SDCardStatus.ToString();
                textBox_Error.Text = variable_Error.ToString();
                textBox_ErrorCode.Text = variable_ErrorCode.ToString();
                textBox_PelletFeedKW.Text = variable_PelletFeedKW.ToString();

                if (ERROR_IN_COMBUSTION == variable_ErrorCode)
                {
                    variable_ErrorString = "Error in Combustion";
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Red);
                }
                else if (ERROR_OVERCURRENT_RADIATORFAN == variable_ErrorCode)
                {
                    variable_ErrorString = "Overcurrent in Radiator Fan";
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Red);
                }
                else if (ERROR_OVERCURRENT_BURNERFAN == variable_ErrorCode)
                {
                    variable_ErrorString = "Overcurrent in Burner Fan";
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Red);
                }
                else if (ERROR_SD_CORRUPTION == variable_ErrorCode)
                {
                    variable_ErrorString = "Most Probably SD card corruption";
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Orange);
                }
                else if (UNUSUAL_PRESSURE_VALUE == variable_ErrorCode)
                {
                    variable_ErrorString = "Usual Pressure Sensor Value, Chances that Pressure Sensor Not Connected";
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Orange);
                }
                else if (UNUSUAL_ENGINE_TEMPERATURE == variable_ErrorCode)
                {
                    variable_ErrorString = "Usual Engine Temperature, Chances that Temperature Sensor Not Connected";
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Orange);
                }
                else if (UNUSUAL_HEATER_TEMPERATURE == variable_ErrorCode)
                {
                    variable_ErrorString = "Usual Heater Temperature, Chances that Heater Thermocouple Not Connected";
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Orange);
                }
                else if (variable_ErrorCode > 0)
                {
                    variable_ErrorString = "ALARM : A" + variable_ErrorCode.ToString() + "\n" + errorDict[variable_ErrorCode];                    
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Red);
                }
                else
                {
                    textBox_ErrorString.Background = new SolidColorBrush(Colors.Transparent);
                    variable_ErrorString = "";
                }

                textBox_ErrorString.Text = variable_ErrorString;

                textBox_InverterOnCounter.Text = variable_InverterOnCounter.ToString();
                textBox_InverterOffCounter.Text = variable_InverterOffCounter.ToString();
                textBox_LogReturn.Text = variable_LogReturn.ToString();
                textBox_LastLogReturn.Text = variable_LastLogReturn.ToString();
                if(0xFFFF == variable_LastLogReturn)
                textBox_Stage.Text = variable_Stage.ToString();
                textBox_SystemStatus.Text = variable_SystemStatus.ToString();

                if (2 == variable_Stage)
                {
                    LabelStage2.Background = new SolidColorBrush(Colors.Blue);
                }
                else
                {
                    LabelStage2.Background = new SolidColorBrush(Colors.Transparent);
                }

                if (3 == variable_Stage)
                {
                    LabelStage3.Background = new SolidColorBrush(Colors.Blue);
                }
                else
                {
                    LabelStage3.Background = new SolidColorBrush(Colors.Transparent);
                }

                if (4 == variable_Stage)
                {
                    LabelStage4.Background = new SolidColorBrush(Colors.Blue);
                }
                else
                {
                    LabelStage4.Background = new SolidColorBrush(Colors.Transparent);
                }

                if (false == variable_SystemStatus)
                {
                    Disconnect();
                }

            }));
        }

        private void UpdateStatusM1(int bytesReceived)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                textBoxStatus.Text = "Received : " + bytesReceived.ToString() + " bytes";
            }));
        }

        private void UpdateDisconnectedM1()
        {
            Dispatcher.Invoke(new Action(() =>
            {
                textBoxStatus.Text = "Disconnected";
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
                    buttonDisconnect.IsHitTestVisible = true;
                    buttonShutdown.IsHitTestVisible = true;
                    textBoxStatus.Text = "Connected..";

                    //thrMessagingM1 = new Thread(new ThreadStart(ReceiveMessagesM1));
                    //thrMessagingM1.Start();
                    //workerRecvMsgM1.RunWorkerAsync();


                    //Start the timer   
                    myTimer.Enabled = true;

                    //Start the App Task After 1 second, To Avoid trafic at the same time as receiving message
                    Task.Delay(timeDelayApp).ContinueWith(_ =>
                    {
                        myTimerApp.Enabled = true;
                    }
                    );

                    Task.Delay(timeDelayLog).ContinueWith(_ =>
                    {
                        myTimerLog.Enabled = true;
                    }
                    );
                }
                else
                {
                    textBoxStatus.Text = "Disconnected : " + exceptionM1;
                    buttonConnect.IsHitTestVisible = true;
                }
            }
        }

        private void buttonConnect_Click(object sender, RoutedEventArgs e)
        {
            variable_SendShutdown = false;
            buttonConnect.IsHitTestVisible = false;
            textBoxStatus.Text = "Connecting..";
            serialPort1.PortName = comboBoxComPorts.Text;
            workerConnectM1.RunWorkerAsync();
        }

        private void Disconnect()
        {

            myTimerApp.Enabled = false;
            myTimerLog.Enabled = false;
            buttonConnect.IsHitTestVisible = true;
            buttonDisconnect.IsHitTestVisible = false;
            buttonShutdown.IsHitTestVisible = false;

            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Close();
                }
                catch (SocketException SE)
                {
                    exceptionM1 = SE.ToString();
                }
            }
        }

        private void buttonDisconnect_Click(object sender, RoutedEventArgs e)
        {
            Disconnect();
        }

        private void shutdownEvent(object source, ElapsedEventArgs e)
        {
            variable_SendShutdown = true;
            shutDownTimer.Enabled = false;
        }

        private void buttonShutdown_Click(object sender, RoutedEventArgs e)
        {
            timeShutdownDelay = Int32.Parse(textBoxAfterTime.Text);
            if (0 == timeShutdownDelay)
            {
                timeShutdownDelay = 1;
            }
            shutDownTimer.Interval = timeShutdownDelay * 1000;
            shutDownTimer.Enabled = true;
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int bytesReceived = 0;
            byte[] rcv = new byte[RCV_SIZE];
            try
            {
                bytesReceived = serialPort1.Read(rcv, 0, RCV_SIZE);
            }
            catch (IOException IOE)
            {
                exceptionM1 = IOE.ToString();
            }


            if (bytesReceived > 0)
            {
                UpdateLogM1(rcv, bytesReceived);
                //UpdateStatusM1(bytesReceived);
            }
        }

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            myTimerSysTime.Enabled = false;
        }
    }
}

