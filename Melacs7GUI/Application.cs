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
        private static System.Timers.Timer myTimerApp;

        private void InitApp()
        {
            myTimerApp = new System.Timers.Timer();
            myTimerApp.Elapsed += new ElapsedEventHandler(myEventApp);
            myTimerApp.Interval = timeInterval;
            myTimerApp.Enabled = false;
        }

        // Take the value from all the melacs and update it periodically. And convert to application specific units.
        private void myEventApp(object source, ElapsedEventArgs e)
        {

            Dispatcher.Invoke(new Action(() =>
            {

                textBoxRefreshTime.Background = Brushes.Red;

                //do task or delete App

                textBoxRefreshTime.Background = Brushes.Green;

            }));

        }

        private void textBox_Hour_KeyDown(object sender, KeyEventArgs e) 
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_Hour = value;
            }
        }

        private void textBox_Hour_LostFocus(object sender, RoutedEventArgs e)
        {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_Hour = value;
        }

        //Pellets On Time to Grams
        double pelletTimeToKW(int time)
        {
            double pelletsKW = 0.0;

            if (0 == time)
            {
                pelletsKW = 0;
            }
            else
            {
                pelletsKW = (4e-7) * time * time * time - 0.0003 * time * time + 0.1103 * time + 2.3496;
            }

            return Math.Round(pelletsKW, 1);
        }

        //Pellets On Time to Grams
        int pelletKWToTime(double pelletsKW)
        {
            int time = 0;
            double tmpPelletKW = 0.0;

            if (0 == pelletsKW)
            {
                time = 0;
            }
            else
            {
                for(time = 0; time < 400; time++)
                {
                    tmpPelletKW = pelletTimeToKW(time);
                    if(tmpPelletKW >= pelletsKW)
                    {
                        break;
                    }
                }

            }

            return time;
        }

        

        private void sliderFeedOnTimeStage4_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_FeedOnTimeStage4 = (int)e.NewValue;
            textBox_FeedOnTimeStage4.Text = variable_FeedOnTimeStage4.ToString();
            variable_InputPelletPowerKW = pelletTimeToKW(variable_FeedOnTimeStage4);
            textBox_InputPelletPowerKW.Text = variable_InputPelletPowerKW.ToString();

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void sliderFeedOnTimeStage3_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_FeedOnTimeStage3 = (int)e.NewValue;
            textBox_FeedOnTimeStage3.Text = variable_FeedOnTimeStage3.ToString();
            variable_InputPelletPowerKWSt3 = pelletTimeToKW(variable_FeedOnTimeStage3);
            textBox_InputPelletPowerKWSt3.Text = variable_InputPelletPowerKWSt3.ToString();

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_InputPelletPowerKW_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_InputPelletPowerKW = value;
            variable_FeedOnTimeStage4 = pelletKWToTime(variable_InputPelletPowerKW);
            sliderFeedOnTimeStage4.Value = variable_FeedOnTimeStage4;
            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void textBox_InputPelletPowerKW_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_InputPelletPowerKW = value;
                variable_FeedOnTimeStage4 = pelletKWToTime(variable_InputPelletPowerKW);
                sliderFeedOnTimeStage4.Value = variable_FeedOnTimeStage4;
                checkBox_UpdatePostCombustionSettings.IsChecked = true;
            }
        }


        private void textBox_InputPelletPowerKWSt3_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_InputPelletPowerKWSt3 = value;
            variable_FeedOnTimeStage3 = pelletKWToTime(variable_InputPelletPowerKWSt3);
            sliderFeedOnTimeStage3.Value = variable_FeedOnTimeStage3;
            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_InputPelletPowerKWSt3_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_InputPelletPowerKWSt3 = value;
                variable_FeedOnTimeStage3 = pelletKWToTime(variable_InputPelletPowerKWSt3);
                sliderFeedOnTimeStage3.Value = variable_FeedOnTimeStage3;
                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void checkBoxSDCardMount_Checked(object sender, RoutedEventArgs e)
        {
            variable_SDCardMount = true;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }
        private void checkBoxSDCardMount_Unchecked(object sender, RoutedEventArgs e)
        {
            variable_SDCardMount = false;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }

        private void checkBoxSaveParaFile_Checked(object sender, RoutedEventArgs e)
        {
            variable_SaveParameterFile = true;
            checkBox_UpdateSDCardLogSettings.IsChecked = true;
        }

        private void checkBoxSaveParaFile_Unchecked(object sender, RoutedEventArgs e)
        {
            variable_SaveParameterFile = false;
            checkBox_UpdateSDCardLogSettings.IsChecked = true;
        }

        private void checkBoxPageChangeEnable_Checked(object sender, RoutedEventArgs e)
        {
            variable_PageChangeEnable = true;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }
        private void checkBoxPageChangeEnable_Unchecked(object sender, RoutedEventArgs e)
        {
            variable_PageChangeEnable = false;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }


        private void checkBoxResetErrorAndWarnings_Checked(object sender, RoutedEventArgs e)
        {
            variable_ResetErrorAndWarnings = true;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }
        private void checkBoxResetErrorAndWarnings_Unchecked(object sender, RoutedEventArgs e)
        {
            variable_ResetErrorAndWarnings = false;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }

        private void textBox_AveragingBurstLength_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_AveragingBurstLength = value;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }

        private void textBox_AveragingBurstLength_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_AveragingBurstLength = value;
                checkBox_UpdatePeripheralSettings.IsChecked = true;
            }
        }

        private void textBox_BurstDelay_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_BurstDelay = value;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }

        private void textBox_BurstDelay_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_BurstDelay = value;
                checkBox_UpdatePeripheralSettings.IsChecked = true;
            }
        }

        private void textBox_BurstPeriod_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_BurstPeriod = value;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }

        private void textBox_BurstPeriod_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_BurstPeriod = value;
                checkBox_UpdatePeripheralSettings.IsChecked = true;
            }
        }

        private void textBox_BurstLength_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_BurstLength = value;
            checkBox_UpdatePeripheralSettings.IsChecked = true;
        }

        private void textBox_BurstLength_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_BurstLength = value;
                checkBox_UpdatePeripheralSettings.IsChecked = true;
            }
        }

        private void textBox_MaxRadiatorFanVoltage_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_MaxRadiatorFanVoltage = value;

            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
        }

        private void textBox_MaxRadiatorFanVoltage_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_MaxRadiatorFanVoltage = value;

                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            }
        }

        private void textBox_MinRadiatorFanVoltage_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_MinRadiatorFanVoltage = value;

            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
        }

        private void textBox_MinRadiatorFanVoltage_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_MinRadiatorFanVoltage = value;

                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            }
        }

        private void textBox_MaxRadiatorFanTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_MaxRadiatorFanTemp = value;

            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
        }

        private void textBox_MaxRadiatorFanTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_MaxRadiatorFanTemp = value;

                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            }
        }

        private void textBox_MinRadiatorFanTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_MinRadiatorFanTemp = value;

            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
        }

        private void textBox_MinRadiatorFanTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_MinRadiatorFanTemp = value;

                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            }
        }

        private void textBox_SwitchOffRadiatorFanTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_SwitchOffRadiatorFanTemp = value;

            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
        }

        private void textBox_SwitchOffRadiatorFanTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_SwitchOffRadiatorFanTemp = value;

                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            }
        }

        private void textBox_MaxValvePosTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_MaxValvePosTemp = value;

            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
        }

        private void textBox_MaxValvePosTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_MaxValvePosTemp = value;

                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            }
        }

        private void textBox_MinValvePosTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_MinValvePosTemp = value;

            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
        }

        private void textBox_MinValvePosTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_MinValvePosTemp = value;

                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            }
        }

        private void textBox_SwitchOffValvePositionTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_SwitchOffValvePositionTemp = value;

            checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
        }

        private void textBox_SwitchOffValvePositionTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_SwitchOffValvePositionTemp = value;

                checkBox_UpdateEngineTemperatureControlSettings.IsChecked = true;
            }
        }

        private void textBox_InitialDoseTime_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_InitialDoseTime = value;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_InitialDoseTime_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_InitialDoseTime = value;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void textBox_ExtraDoseTime_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_ExtraDoseTime = value;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_ExtraDoseTime_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_ExtraDoseTime = value;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void checkBoxExtraDoseEnable_Checked(object sender, RoutedEventArgs e)
        {
            variable_ExtraDoseEnable = true;
            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void checkBoxExtraDoseEnable_Unchecked(object sender, RoutedEventArgs e)
        {
            variable_ExtraDoseEnable = false;
            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_InitialStartBurnerFanDelay_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_InitialStartBurnerFanDelay = value;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_InitialStartBurnerFanDelay_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_InitialStartBurnerFanDelay = value;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void textBox_InitialStartBurnerTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_InitialStartBurnerTemp = value;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_InitialStartBurnerTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_InitialStartBurnerTemp = value;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void textBox_CombustionSuccessTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_CombustionSuccessTemp = value;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_CombustionSuccessTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_CombustionSuccessTemp = value;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }


        private void textBox_CombustionBuildUpTime_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_AfterCombustionBuildUpTime = value;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_CombustionBuildUpTime_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_AfterCombustionBuildUpTime = value;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void textBox_BurnerFanSwitchOffTemperature_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_BurnerFanSwitchOffTemperature = value;

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void textBox_BurnerFanSwitchOffTemperature_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_BurnerFanSwitchOffTemperature = value;

                checkBox_UpdatePostCombustionSettings.IsChecked = true;
            }
        }

        private void textBox_InverterDelayCounter_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_InverterDelayCounter = value;

            checkBox_UpdateInverterSettings.IsChecked = true;
        }

        private void textBox_InverterDelayCounter_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_InverterDelayCounter = value;

                checkBox_UpdateInverterSettings.IsChecked = true;
            }
        }

        private void textBox_ProcessMinHeaterTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_ProcessMinHeaterTemp = value;

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void textBox_ProcessMinHeaterTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_ProcessMinHeaterTemp = value;

                checkBox_UpdatePostCombustionSettings.IsChecked = true;
            }
        }

        private void textBox_ProcessMaxHeaterTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_ProcessMaxHeaterTemp = value;

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void textBox_ProcessMaxHeaterTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_ProcessMaxHeaterTemp = value;

                checkBox_UpdatePostCombustionSettings.IsChecked = true;
            }
        }

        private void textBox_ErrProcTempLowThresh_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_ErrProcTempLowThresh = value;

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void textBox_ErrProcTempLowThresh_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_ErrProcTempLowThresh = value;

                checkBox_UpdatePostCombustionSettings.IsChecked = true;
            }
        }

        private void textBox_FinalFeedRampUpTime_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_FinalFeedRampUpTime = value;

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void textBox_FinalFeedRampUpTime_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_FinalFeedRampUpTime = value;

                checkBox_UpdatePostCombustionSettings.IsChecked = true;
            }
        }

        


        private void sliderBurnerSpeedStage4_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_BurnerSpeedStage4 = e.NewValue;
            textBox_BurnerSpeedStage4.Text = variable_BurnerSpeedStage4.ToString();

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void sliderBurnerSpeedStage3_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_BurnerSpeedStage3 = e.NewValue;
            textBox_BurnerSpeedStage3.Text = variable_BurnerSpeedStage3.ToString();

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void sliderBurnerSpeedStage2_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_BurnerSpeedStage2 = e.NewValue;
            textBox_BurnerSpeedStage2.Text = variable_BurnerSpeedStage2.ToString();

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_LogSamplePeriod_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_LogSamplePeriod = value;

            checkBox_UpdateSDCardLogSettings.IsChecked = true;
        }

        private void textBox_LogSamplePeriod_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_LogSamplePeriod = value;

                checkBox_UpdateSDCardLogSettings.IsChecked = true;
            }
        }

        private void textBox_NumOfSampleInEachLog_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_NumOfSampleInEachLog = value;

            checkBox_UpdateSDCardLogSettings.IsChecked = true;
        }

        private void textBox_NumOfSampleInEachLog_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_NumOfSampleInEachLog = value;

                checkBox_UpdateSDCardLogSettings.IsChecked = true;
            }
        }

        private void textBox_TimeToBurstLog_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_TimeToBurstLog = value;

            checkBox_UpdateSDCardLogSettings.IsChecked = true;
        }

        private void textBox_TimeToBurstLog_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_TimeToBurstLog = value;

                checkBox_UpdateSDCardLogSettings.IsChecked = true;
            }
        }

        private void textBox_NumOfSamplesInBurstLog_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_NumOfSamplesInBurstLog = value;

            checkBox_UpdateSDCardLogSettings.IsChecked = true;
        }

        private void textBox_NumOfSamplesInBurstLog_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_NumOfSamplesInBurstLog = value;

                checkBox_UpdateSDCardLogSettings.IsChecked = true;
            }
        }

        private void checkBoxSynSystemTime_Checked(object sender, RoutedEventArgs e)
        {
            variable_SynSystemTime = true;

            checkBox_UpdateDateTimeSettings.IsChecked = true;
        }

        private void checkBoxSynSystemTime_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_SynSystemTime = false;

            //checkBox_UpdateDateTimeSettings.IsChecked = true;
        }

        private void textBox_Year_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_Year = value;
        }

        private void textBox_Year_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_Year = value;
            }
        }

        private void textBox_Month_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_Month = value;
        }

        private void textBox_Month_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_Month = value;
            }
        }

        private void textBox_Day_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_Day = value;
        }

        private void textBox_Day_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_Day = value;
            }
        }

        private void textBox_Minute_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_Minute = value;
        }

        private void textBox_Minute_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_Minute = value;
            }
        }

        private void textBox_Second_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_Second = value;
        }

        private void textBox_Second_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_Second = value;
            }
        }

        private void textBox_Weekday_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_Weekday = value;
        }

        private void textBox_Weekday_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_Weekday = value;
            }
        }

        private void checkBoxSynManualTime_Checked(object sender, RoutedEventArgs e)
        {
            variable_SynManualTime = true;

            checkBox_UpdateDateTimeSettings.IsChecked = true;
        }

        private void checkBoxSynManualTime_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_SynManualTime = false;
        }

        private void textBox_InverterOnTemperature_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_InverterOnTemperature = value;

            checkBox_UpdateInverterSettings.IsChecked = true;
        }

        private void textBox_InverterOnTemperature_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_InverterOnTemperature = value;

                checkBox_UpdateInverterSettings.IsChecked = true;
            }
        }

        private void textBox_InverterOffTemperature_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_InverterOffTemperature = value;

            checkBox_UpdateInverterSettings.IsChecked = true;
        }

        private void textBox_InverterOffTemperature_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_InverterOffTemperature = value;

                checkBox_UpdateInverterSettings.IsChecked = true;
            }
        }

        private void textBox_BurnerSpeedStage2_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_BurnerSpeedStage2 = value;
                sliderBurnerSpeedStage2.Value = variable_BurnerSpeedStage2;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void textBox_BurnerSpeedStage2_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_BurnerSpeedStage2 = value;
            sliderBurnerSpeedStage2.Value = variable_BurnerSpeedStage2;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_BurnerSpeedStage3_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_BurnerSpeedStage3 = value;
                sliderBurnerSpeedStage3.Value = variable_BurnerSpeedStage3;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void textBox_BurnerSpeedStage3_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_BurnerSpeedStage3 = value;
            sliderBurnerSpeedStage3.Value = variable_BurnerSpeedStage3;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_BurnerSpeedStage4_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_BurnerSpeedStage4 = value;
                sliderBurnerSpeedStage4.Value = variable_BurnerSpeedStage4;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void textBox_BurnerSpeedStage4_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_BurnerSpeedStage4 = value;
            sliderBurnerSpeedStage4.Value = variable_BurnerSpeedStage4;

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void textBox_FeedOnTimeStage3_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_FeedOnTimeStage3 = value;
                sliderFeedOnTimeStage3.Value = variable_FeedOnTimeStage3;

                checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
            }
        }

        private void textBox_FeedOnTimeStage3_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_FeedOnTimeStage3 = value;
            sliderFeedOnTimeStage3.Value = variable_FeedOnTimeStage3;

            checkBox_UpdatePreCombustionSequenceSettings.IsChecked = true;
        }

        private void textBox_FeedOnTimeStage4_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_FeedOnTimeStage4 = value;
                sliderFeedOnTimeStage4.Value = variable_FeedOnTimeStage4;

                checkBox_UpdatePostCombustionSettings.IsChecked = true;
            }
        }

        private void textBox_FeedOnTimeStage4_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_FeedOnTimeStage4 = value;
            sliderFeedOnTimeStage4.Value = variable_FeedOnTimeStage4;

            checkBox_UpdatePostCombustionSettings.IsChecked = true;
        }

        private void checkBoxOverrideBurnerFan_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideBurnerFan = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideBurnerFan_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideBurnerFan = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void sliderOverrideBurnerFan_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideBurnerFan = e.NewValue;
            textBox_OverrideBurnerFan.Text = variable_OverrideBurnerFan.ToString();

            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void textBox_OverrideBurnerFan_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_OverrideBurnerFan = value;
                slider_OverrideBurnerFan.Value = variable_OverrideBurnerFan;

                checkBox_UpdateOverrides.IsChecked = true;
            }
        }

        private void textBox_OverrideBurnerFan_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_OverrideBurnerFan = value;
            slider_OverrideBurnerFan.Value = variable_OverrideBurnerFan;

            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideRadiatorFan_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideRadiatorFan = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideRadiatorFan_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideRadiatorFan = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void sliderOverrideRadiatorFan_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideRadiatorFan = e.NewValue;
            textBox_OverrideRadiatorFan.Text = variable_OverrideRadiatorFan.ToString();

            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void textBox_OverrideRadiatorFan_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                double value = 0;
                var textBox = sender as TextBox;
                Double.TryParse(textBox.Text, out value);
                variable_OverrideRadiatorFan = value;
                slider_OverrideRadiatorFan.Value = variable_OverrideRadiatorFan;

                checkBox_UpdateOverrides.IsChecked = true;
            }
        }

        private void textBox_OverrideRadiatorFan_LostFocus(object sender, RoutedEventArgs e)
        {
            double value = 0;
            var textBox = sender as TextBox;
            Double.TryParse(textBox.Text, out value);
            variable_OverrideRadiatorFan = value;
            slider_OverrideRadiatorFan.Value = variable_OverrideRadiatorFan;

            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideValvePosition_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideValvePosition = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideValvePosition_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideValvePosition = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void sliderOverrideValvePosition_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideValvePosition = (int)e.NewValue;
            textBox_OverrideValvePosition.Text = variable_OverrideValvePosition.ToString();

            checkBox_UpdateOverrides.IsChecked = true;
        }
        
        private void textBox_OverrideValvePosition_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_OverrideValvePosition = value;
                slider_OverrideValvePosition.Value = variable_OverrideValvePosition;

                checkBox_UpdateOverrides.IsChecked = true;
            }
        }

        private void textBox_OverrideValvePosition_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_OverrideValvePosition = value;
            slider_OverrideValvePosition.Value = variable_OverrideValvePosition;

            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void checkBoxOverrideCirculationPump_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideCirculationPump = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideCirculationPump_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideCirculationPump = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void sliderOverrideCirculationPump_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideCirculationPump = (int)e.NewValue;

            if (1 == variable_OverrideCirculationPump)
            {
                textBox_OverrideCirculationPump.Text = "ON";
                slider_OverrideCirculationPump.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                textBox_OverrideCirculationPump.Text = "OFF";
                slider_OverrideCirculationPump.Background = new SolidColorBrush(Colors.Red);
            }

            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void checkBoxOverrideFeeder_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideFeeder = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideFeeder_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideFeeder = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void sliderOverrideFeeder_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideFeeder = (int)e.NewValue;

            if (1 == variable_OverrideFeeder)
            {
                textBox_OverrideFeeder.Text = "ON";
                slider_OverrideFeeder.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                textBox_OverrideFeeder.Text = "OFF";
                slider_OverrideFeeder.Background = new SolidColorBrush(Colors.Red);
            }

            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideIgnitor_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideIgnitor = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideIgnitor_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideIgnitor = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void sliderOverrideIgnitor_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideIgnitor = (int)e.NewValue;

            if (1 == variable_OverrideIgnitor)
            {
                textBox_OverrideIgnitor.Text = "ON";
                slider_OverrideIgnitor.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                textBox_OverrideIgnitor.Text = "OFF";
                slider_OverrideIgnitor.Background = new SolidColorBrush(Colors.Red);
            }

            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void checkBoxOverrideInverter_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideInverter = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideInverter_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideInverter = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void sliderOverrideInverter_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideInverter = (int)e.NewValue;

            if (1 == variable_OverrideInverter)
            {
                textBox_OverrideInverter.Text = "ON";
                slider_OverrideInverter.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                textBox_OverrideInverter.Text = "OFF";
                slider_OverrideInverter.Background = new SolidColorBrush(Colors.Red);
            }

            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void checkBoxOverrideKey_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideKey = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideKey_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideKey = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void sliderOverrideKey_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideKey = (int)e.NewValue;

            if (1 == variable_OverrideKey)
            {
                textBox_OverrideKey.Text = "ON";
                slider_OverrideKey.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                textBox_OverrideKey.Text = "OFF";
                slider_OverrideKey.Background = new SolidColorBrush(Colors.Red);
            }

            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void checkBoxOverrideGas_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableOverrideGas = true;
            checkBox_UpdateOverrides.IsChecked = true;
        }

        private void checkBoxOverrideGas_Unchecked(object sender, RoutedEventArgs e)
        {

            variable_EnableOverrideGas = false;
            checkBox_UpdateOverrides.IsChecked = true;
        }


        private void sliderOverrideGas_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            variable_OverrideGas = (int)e.NewValue;

            if (1 == variable_OverrideGas)
            {
                textBox_OverrideGas.Text = "ON";
                slider_OverrideGas.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                textBox_OverrideGas.Text = "OFF";
                slider_OverrideGas.Background = new SolidColorBrush(Colors.Red);
            }

            checkBox_UpdateOverrides.IsChecked = true;
        }



        private void checkBoxEnableSettingPressure_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableSettingPressure = true;
            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void checkBoxEnableSettingPressure_Unchecked(object sender, RoutedEventArgs e)
        {
            variable_EnableSettingPressure = false;
            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void textBox_SetPressure_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_SetPressure = value;

                checkBox_UpdateEngineSettings.IsChecked = true;
            }
        }

        private void textBox_SetPressure_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_SetPressure = value;

            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void textBox_LowestCoolerTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_LowestCoolerTemp = value;

                checkBox_UpdateEngineSettings.IsChecked = true;
            }
        }

        private void textBox_LowestCoolerTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_LowestCoolerTemp = value;

            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void textBox_HighestCoolerTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_HighestCoolerTemp = value;

                checkBox_UpdateEngineSettings.IsChecked = true;
            }
        }

        private void textBox_HighestCoolerTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_HighestCoolerTemp = value;

            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void textBox_LowestHeaterTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_LowestHeaterTemp = value;

                checkBox_UpdateEngineSettings.IsChecked = true;
            }
        }

        private void textBox_LowestHeaterTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_LowestHeaterTemp = value;

            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void textBox_HighestHeaterTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_HighestHeaterTemp = value;

                checkBox_UpdateEngineSettings.IsChecked = true;
            }
        }

        private void textBox_HighestHeaterTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_HighestHeaterTemp = value;

            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void textBox_LowestGasPressure_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_LowestGasPressure = value;

                checkBox_UpdateEngineSettings.IsChecked = true;
            }
        }

        private void textBox_LowestGasPressure_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_LowestGasPressure = value;

            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void textBox_HighestGasPressure_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_HighestGasPressure = value;

                checkBox_UpdateEngineSettings.IsChecked = true;
            }
        }

        private void textBox_HighestGasPressure_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_HighestGasPressure = value;

            checkBox_UpdateEngineSettings.IsChecked = true;
        }

        private void checkBoxEnableGas_Checked(object sender, RoutedEventArgs e)
        {
            variable_EnableGas = true;
            checkBox_UpdateGasSystem.IsChecked = true;
        }

        private void checkBoxEnableGas_Unchecked(object sender, RoutedEventArgs e)
        {
            variable_EnableGas = false;
            checkBox_UpdateGasSystem.IsChecked = true;
        }

        private void textBox_GasThermostatMinTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_GasThermostatMinTemp = value;

                checkBox_UpdateGasSystem.IsChecked = true;
            }
        }

        private void textBox_GasThermostatMinTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_GasThermostatMinTemp = value;

            checkBox_UpdateGasSystem.IsChecked = true;
        }

        private void textBox_GasThermostatMaxTemp_KeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.Enter) || (e.Key == Key.Tab))
            {
                int value = 0;
                var textBox = sender as TextBox;
                Int32.TryParse(textBox.Text, out value);
                variable_GasThermostatMaxTemp = value;

                checkBox_UpdateGasSystem.IsChecked = true;
            }
        }

        private void textBox_GasThermostatMaxTemp_LostFocus(object sender, RoutedEventArgs e)
        {
            int value = 0;
            var textBox = sender as TextBox;
            Int32.TryParse(textBox.Text, out value);
            variable_GasThermostatMaxTemp = value;

            checkBox_UpdateGasSystem.IsChecked = true;
        }
    }
}
