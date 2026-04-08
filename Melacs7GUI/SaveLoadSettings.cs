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

namespace InresolGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private void saveControlParameters()
        {
            try
            {

                //Pass the filepath and filename to the StreamWriter Constructor
                StreamWriter sw = new StreamWriter("control_parameters.txt");

                //Write a line of text
                sw.WriteLine(textBoxRefreshTime.Text.ToString());
                sw.WriteLine(checkBoxSDCardMount.IsChecked.ToString());
                sw.WriteLine(checkBoxPageChangeEnable.IsChecked.ToString());
                sw.WriteLine(textBox_BurstPeriod.Text.ToString());
                sw.WriteLine(textBox_BurstLength.Text.ToString());
                sw.WriteLine(textBox_AveragingBurstLength.Text.ToString());
                sw.WriteLine(textBox_BurstDelay.Text.ToString());

                sw.WriteLine(textBox_MaxRadiatorFanVoltage.Text.ToString());
                sw.WriteLine(textBox_MinRadiatorFanVoltage.Text.ToString());
                sw.WriteLine(textBox_MaxRadiatorFanTemp.Text.ToString());
                sw.WriteLine(textBox_MinRadiatorFanTemp.Text.ToString());
                sw.WriteLine(textBox_SwitchOffRadiatorFanTemp.Text.ToString());
                sw.WriteLine(textBox_MaxValvePosTemp.Text.ToString());
                sw.WriteLine(textBox_MinValvePosTemp.Text.ToString());
                sw.WriteLine(textBox_SwitchOffValvePositionTemp.Text.ToString());

                sw.WriteLine(textBox_InitialDoseTime.Text.ToString());
                sw.WriteLine(textBox_ExtraDoseTime.Text.ToString());
                sw.WriteLine(checkBox_ExtraDoseEnable.IsChecked.ToString());
                sw.WriteLine(textBoxAfterTime.Text.ToString());
                sw.WriteLine(textBox_InitialStartBurnerFanDelay.Text.ToString());
                sw.WriteLine(textBox_InitialStartBurnerTemp.Text.ToString());
                sw.WriteLine(textBox_CombustionSuccessTemp.Text.ToString());
                sw.WriteLine(textBox_CombustionBuildUpTime.Text.ToString());
                sw.WriteLine(sliderBurnerSpeedStage2.Value.ToString());
                sw.WriteLine(sliderBurnerSpeedStage3.Value.ToString());
                sw.WriteLine(sliderFeedOnTimeStage3.Value.ToString());

                sw.WriteLine(textBox_BurnerFanSwitchOffTemperature.Text.ToString());
                sw.WriteLine(textBox_InputPelletPowerKW.Text.ToString());
                sw.WriteLine(textBox_ProcessMinHeaterTemp.Text.ToString());
                sw.WriteLine(textBox_ProcessMaxHeaterTemp.Text.ToString());
                sw.WriteLine(textBox_ErrProcTempLowThresh.Text.ToString());
                sw.WriteLine(textBox_FinalFeedRampUpTime.Text.ToString());
                sw.WriteLine(sliderBurnerSpeedStage4.Value.ToString());
                sw.WriteLine(sliderFeedOnTimeStage4.Value.ToString());

                sw.WriteLine(textBox_LogSamplePeriod.Text.ToString());
                sw.WriteLine(textBox_NumOfSampleInEachLog.Text.ToString());
                sw.WriteLine(textBox_TimeToBurstLog.Text.ToString());
                sw.WriteLine(textBox_NumOfSamplesInBurstLog.Text.ToString());

                sw.WriteLine(textBox_Year.Text.ToString());
                sw.WriteLine(textBox_Month.Text.ToString());
                sw.WriteLine(textBox_Day.Text.ToString());
                sw.WriteLine(textBox_Hour.Text.ToString());
                sw.WriteLine(textBox_Minute.Text.ToString());
                sw.WriteLine(textBox_Second.Text.ToString());
                sw.WriteLine(textBox_Weekday.Text.ToString());

                sw.WriteLine(slider_OverrideBurnerFan.Value.ToString());
                sw.WriteLine(textBox_OverrideBurnerFan.Text.ToString());
                sw.WriteLine(checkBox_OverrideBurnerFan.IsChecked.ToString());
                sw.WriteLine(slider_OverrideRadiatorFan.Value.ToString());
                sw.WriteLine(textBox_OverrideRadiatorFan.Text.ToString());
                sw.WriteLine(checkBox_OverrideRadiatorFan.IsChecked.ToString());
                sw.WriteLine(slider_OverrideValvePosition.Value.ToString());
                sw.WriteLine(textBox_OverrideValvePosition.Text.ToString());
                sw.WriteLine(checkBox_OverrideValvePosition.IsChecked.ToString());
                sw.WriteLine(slider_OverrideCirculationPump.Value.ToString());
                sw.WriteLine(checkBox_EnableOverrideCirculationPump.IsChecked.ToString());
                sw.WriteLine(textBox_OverrideCirculationPump.Text.ToString());
                sw.WriteLine(slider_OverrideFeeder.Value.ToString());
                sw.WriteLine(checkBox_EnableOverrideFeeder.IsChecked.ToString());
                sw.WriteLine(textBox_OverrideFeeder.Text.ToString());
                sw.WriteLine(slider_OverrideIgnitor.Value.ToString());
                sw.WriteLine(checkBox_EnableOverrideIgnitor.IsChecked.ToString());
                sw.WriteLine(textBox_OverrideIgnitor.Text.ToString());
                sw.WriteLine(slider_OverrideInverter.Value.ToString());
                sw.WriteLine(checkBox_EnableOverrideInverter.IsChecked.ToString());
                sw.WriteLine(textBox_OverrideInverter.Text.ToString());
                sw.WriteLine(slider_OverrideKey.Value.ToString());
                sw.WriteLine(checkBox_EnableOverrideKey.IsChecked.ToString());
                sw.WriteLine(textBox_OverrideKey.Text.ToString());
                sw.WriteLine(slider_OverrideGas.Value.ToString());
                sw.WriteLine(checkBox_EnableOverrideGas.IsChecked.ToString());
                sw.WriteLine(textBox_OverrideGas.Text.ToString());

                sw.WriteLine(textBox_SetPressure.Text.ToString());
                sw.WriteLine(checkBoxEnableSettingPressure.IsChecked.ToString());
                sw.WriteLine(textBox_LowestCoolerTemp.Text.ToString());
                sw.WriteLine(textBox_HighestCoolerTemp.Text.ToString());
                sw.WriteLine(textBox_LowestHeaterTemp.Text.ToString());
                sw.WriteLine(textBox_HighestHeaterTemp.Text.ToString());
                sw.WriteLine(textBox_LowestGasPressure.Text.ToString());
                sw.WriteLine(textBox_HighestGasPressure.Text.ToString());

                sw.WriteLine(checkBoxEnableGas.IsChecked.ToString());
                sw.WriteLine(textBox_GasThermostatMinTemp.Text.ToString());
                sw.WriteLine(textBox_GasThermostatMaxTemp.Text.ToString());

                sw.WriteLine(textBox_InverterOnTemperature.Text.ToString());
                sw.WriteLine(textBox_InverterOffTemperature.Text.ToString());
                sw.WriteLine(textBox_InverterDelayCounter.Text.ToString());

                //Close the file
                sw.Close();

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

        private void loadControlParameters()
        {
            String line;
            double parsedValue = 0;
            int intValue = 0;
            double doubleValue = 0.0;

            try
            {
                //Pass the file path and file name to the StreamReader constructor
                StreamReader sr = new StreamReader("control_parameters.txt");

                //Read the first line of text
                
                line = sr.ReadLine();
                if (line != null)
                {
                    textBoxRefreshTime.Text = line;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBoxSDCardMount.IsChecked = Convert.ToBoolean(line);
                    variable_SDCardMount = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBoxPageChangeEnable.IsChecked = Convert.ToBoolean(line);
                    variable_PageChangeEnable = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_BurstPeriod.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_BurstPeriod = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_BurstLength.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_BurstLength = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_AveragingBurstLength.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_AveragingBurstLength = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_BurstDelay.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_BurstDelay = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_MaxRadiatorFanVoltage.Text = line;
                    Double.TryParse(line, out doubleValue);
                    variable_MaxRadiatorFanVoltage = doubleValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_MinRadiatorFanVoltage.Text = line;
                    Double.TryParse(line, out doubleValue);
                    variable_MinRadiatorFanVoltage = doubleValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_MaxRadiatorFanTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_MaxRadiatorFanTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_MinRadiatorFanTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_MinRadiatorFanTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_SwitchOffRadiatorFanTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_SwitchOffRadiatorFanTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_MaxValvePosTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_MaxValvePosTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_MinValvePosTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_MinValvePosTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_SwitchOffValvePositionTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_SwitchOffValvePositionTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_InitialDoseTime.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_InitialDoseTime = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_ExtraDoseTime.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_ExtraDoseTime = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_ExtraDoseEnable.IsChecked = Convert.ToBoolean(line);
                    variable_ExtraDoseEnable = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBoxAfterTime.Text = line;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_InitialStartBurnerFanDelay.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_InitialStartBurnerFanDelay = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_InitialStartBurnerTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_InitialStartBurnerTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_CombustionSuccessTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_CombustionSuccessTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_CombustionBuildUpTime.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_AfterCombustionBuildUpTime = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    sliderBurnerSpeedStage2.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    sliderBurnerSpeedStage3.Value = parsedValue; }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    sliderFeedOnTimeStage3.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_BurnerFanSwitchOffTemperature.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_BurnerFanSwitchOffTemperature = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_InputPelletPowerKW.Text = line;
                    Double.TryParse(line, out doubleValue);
                    variable_InputPelletPowerKW = doubleValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_ProcessMinHeaterTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_ProcessMinHeaterTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_ProcessMaxHeaterTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_ProcessMaxHeaterTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_ErrProcTempLowThresh.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_ErrProcTempLowThresh = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_FinalFeedRampUpTime.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_FinalFeedRampUpTime = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    sliderBurnerSpeedStage4.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    sliderFeedOnTimeStage4.Value = parsedValue;
                } else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_LogSamplePeriod.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_LogSamplePeriod = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_NumOfSampleInEachLog.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_NumOfSampleInEachLog = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_TimeToBurstLog.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_TimeToBurstLog = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_NumOfSamplesInBurstLog.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_NumOfSamplesInBurstLog = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_Year.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_Year = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_Month.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_Month = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_Day.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_Day = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_Hour.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_Hour = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_Minute.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_Minute = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_Second.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_Second = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_Weekday.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_Weekday = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideBurnerFan.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideBurnerFan.Text = line;
                    Double.TryParse(line, out doubleValue);
                    variable_OverrideBurnerFan = doubleValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_OverrideBurnerFan.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideBurnerFan = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }


                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideRadiatorFan.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideRadiatorFan.Text = line;
                    Double.TryParse(line, out doubleValue);
                    variable_OverrideRadiatorFan = doubleValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_OverrideRadiatorFan.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideValvePosition = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }


                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideValvePosition.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideValvePosition.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_OverrideValvePosition = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_OverrideValvePosition.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideValvePosition = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideCirculationPump.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_EnableOverrideCirculationPump.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideCirculationPump = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideCirculationPump.Text = line;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideFeeder.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_EnableOverrideFeeder.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideFeeder = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideFeeder.Text = line;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }


                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideIgnitor.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_EnableOverrideIgnitor.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideIgnitor = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideIgnitor.Text = line;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideInverter.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_EnableOverrideInverter.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideInverter = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideInverter.Text = line;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }


                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideKey.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_EnableOverrideKey.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideKey = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideKey.Text = line;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    Double.TryParse(line, out parsedValue);
                    slider_OverrideGas.Value = parsedValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBox_EnableOverrideGas.IsChecked = Convert.ToBoolean(line);
                    variable_EnableOverrideGas = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_OverrideGas.Text = line;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_SetPressure.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_SetPressure = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBoxEnableSettingPressure.IsChecked = Convert.ToBoolean(line);
                    variable_EnableSettingPressure = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_LowestCoolerTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_LowestCoolerTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_HighestCoolerTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_HighestCoolerTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_LowestHeaterTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_LowestHeaterTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_HighestHeaterTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_HighestHeaterTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_LowestGasPressure.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_LowestGasPressure = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_HighestGasPressure.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_HighestGasPressure = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    checkBoxEnableGas.IsChecked = Convert.ToBoolean(line);
                    variable_EnableGas = Convert.ToBoolean(line);
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_GasThermostatMinTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_GasThermostatMinTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_GasThermostatMaxTemp.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_GasThermostatMaxTemp = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }


                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_InverterOnTemperature.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_InverterOnTemperature = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }


                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_InverterOffTemperature.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_InverterOffTemperature = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }

                line = sr.ReadLine();
                if (line != null)
                {
                    textBox_InverterDelayCounter.Text = line;
                    Int32.TryParse(line, out intValue);
                    variable_InverterDelayCounter = intValue;
                }
                else
                {
                    goto LOAD_CONTROL_PARA_END;
                }


                LOAD_CONTROL_PARA_END:
                //close the file
                sr.Close();
                Console.ReadLine();
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

        private void buttonSaveSettings_Click(object sender, RoutedEventArgs e)
        {
            saveControlParameters();
            MessageBoxResult result = MessageBox.Show("Settings Saved!");
        }

        private void buttonLoadSettings_Click(object sender, RoutedEventArgs e)
        {
            loadControlParameters();
            MessageBoxResult result = MessageBox.Show("Settings Loaded!");
        }
    }
}