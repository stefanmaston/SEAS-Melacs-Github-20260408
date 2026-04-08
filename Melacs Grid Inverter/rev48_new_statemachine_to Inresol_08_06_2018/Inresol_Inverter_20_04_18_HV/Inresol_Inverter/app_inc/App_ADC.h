/*
 *  File name: App_ADC.h
 *
 *  Description: High level function declarations for ADC processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_ADC_H
#define APP_ADC_H

extern uint16_t ADC_P_U_DC_RAW;
extern uint16_t ADC_P_U_DC_Mean;
extern uint16_t ADC_P_U_DC_PkPk;
extern uint16_t ADC_P_U_DC_RMS;
extern uint16_t ADC_N_U_DC_RAW;
extern uint16_t ADC_N_U_DC_Mean;
extern uint16_t ADC_N_U_DC_PkPk;
extern uint16_t ADC_N_U_DC_RMS;
extern uint16_t ADC_L1_U_Inv_RAW;
extern  int16_t ADC_L1_U_Inv_Conv;
extern  int16_t ADC_L1_U_Inv_Mean;
extern  int16_t ADC_L1_U_Inv_PkPk;
extern  int16_t ADC_L1_U_Inv_Pk_L;
extern  int16_t ADC_L1_U_Inv_Pk_H;
extern  int16_t ADC_L1_U_Inv_RMS;
extern uint16_t ADC_L1_I_Inv_RAW;
extern  int16_t ADC_L1_I_Inv_Conv;
extern  int16_t ADC_L1_I_Inv_Mean;
extern  int16_t ADC_L1_I_Inv_PkPk;
extern  int16_t ADC_L1_I_Inv_RMS;
extern uint16_t ADC_L2_U_Inv_RAW;
extern  int16_t ADC_L2_U_Inv_Conv;
extern  int16_t ADC_L2_U_Inv_Mean;
extern  int16_t ADC_L2_U_Inv_PkPk;
extern  int16_t ADC_L2_U_Inv_Pk_L;
extern  int16_t ADC_L2_U_Inv_Pk_H;
extern  int16_t ADC_L2_U_Inv_RMS;
extern uint16_t ADC_L2_I_Inv_RAW;
extern  int16_t ADC_L2_I_Inv_Conv;
extern  int16_t ADC_L2_I_Inv_Mean;
extern  int16_t ADC_L2_I_Inv_PkPk;
extern  int16_t ADC_L2_I_Inv_RMS;
extern uint16_t ADC_L3_U_Inv_RAW;
extern  int16_t ADC_L3_U_Inv_Conv;
extern  int16_t ADC_L3_U_Inv_Mean;
extern  int16_t ADC_L3_U_Inv_PkPk;
extern  int16_t ADC_L3_U_Inv_Pk_L;
extern  int16_t ADC_L3_U_Inv_Pk_H;
extern  int16_t ADC_L3_U_Inv_RMS;
extern uint16_t ADC_L3_I_Inv_RAW;
extern  int16_t ADC_L3_I_Inv_Conv;
extern  int16_t ADC_L3_I_Inv_Mean;
extern  int16_t ADC_L3_I_Inv_PkPk;
extern  int16_t ADC_L3_I_Inv_RMS;
extern uint16_t ADC_L1_U_Mid_RAW;
extern  int16_t ADC_L1_U_Mid_Conv;
extern  int16_t ADC_L1_U_Mid_Mean;
extern  int16_t ADC_L1_U_Mid_PkPk;
extern  int16_t ADC_L1_U_Mid_Pk_L;
extern  int16_t ADC_L1_U_Mid_Pk_H;
extern  int16_t ADC_L1_U_Mid_RMS;
extern uint16_t ADC_L2_U_Mid_RAW;
extern  int16_t ADC_L2_U_Mid_Conv;
extern  int16_t ADC_L2_U_Mid_Mean;
extern  int16_t ADC_L2_U_Mid_PkPk;
extern  int16_t ADC_L2_U_Mid_Pk_L;
extern  int16_t ADC_L2_U_Mid_Pk_H;
extern  int16_t ADC_L2_U_Mid_RMS;
extern uint16_t ADC_L3_U_Mid_RAW;
extern  int16_t ADC_L3_U_Mid_Conv;
extern  int16_t ADC_L3_U_Mid_Mean;
extern  int16_t ADC_L3_U_Mid_PkPk;
extern  int16_t ADC_L3_U_Mid_Pk_L;
extern  int16_t ADC_L3_U_Mid_Pk_H;
extern  int16_t ADC_L3_U_Mid_RMS;
extern uint16_t ADC_L1_U_Grid_RAW;
extern  int16_t ADC_L1_U_Grid_Conv;
extern  int16_t ADC_L1_U_Grid_Mean;
extern  int16_t ADC_L1_U_Grid_PkPk;
extern  int16_t ADC_L1_U_Grid_Pk_L;
extern  int16_t ADC_L1_U_Grid_Pk_H;
extern  int16_t ADC_L1_U_Grid_RMS;
extern uint16_t ADC_L1_I_Grid_RAW;
extern  int16_t ADC_L1_I_Grid_Conv;
extern  int16_t ADC_L1_I_Grid_Mean;
extern  int16_t ADC_L1_I_Grid_PkPk;
extern  int16_t ADC_L1_I_Grid_RMS;
extern uint16_t ADC_L2_U_Grid_RAW;
extern  int16_t ADC_L2_U_Grid_Conv;
extern  int16_t ADC_L2_U_Grid_Mean;
extern  int16_t ADC_L2_U_Grid_PkPk;
extern  int16_t ADC_L2_U_Grid_Pk_L;
extern  int16_t ADC_L2_U_Grid_Pk_H;
extern  int16_t ADC_L2_U_Grid_RMS;
extern uint16_t ADC_L2_I_Grid_RAW;
extern  int16_t ADC_L2_I_Grid_Conv;
extern  int16_t ADC_L2_I_Grid_Mean;
extern  int16_t ADC_L2_I_Grid_PkPk;
extern  int16_t ADC_L2_I_Grid_RMS;
extern uint16_t ADC_L3_U_Grid_RAW;
extern  int16_t ADC_L3_U_Grid_Conv;
extern  int16_t ADC_L3_U_Grid_Mean;
extern  int16_t ADC_L3_U_Grid_PkPk;
extern  int16_t ADC_L3_U_Grid_Pk_L;
extern  int16_t ADC_L3_U_Grid_Pk_H;
extern  int16_t ADC_L3_U_Grid_RMS;
extern uint16_t ADC_L3_I_Grid_RAW;
extern  int16_t ADC_L3_I_Grid_Conv;
extern  int16_t ADC_L3_I_Grid_Mean;
extern  int16_t ADC_L3_I_Grid_PkPk;
extern  int16_t ADC_L3_I_Grid_RMS;
extern uint16_t ADC_T1_RAW;
extern uint16_t ADC_T1_Mean;
extern uint16_t ADC_T2_RAW;
extern uint16_t ADC_T2_Mean;
extern uint16_t ADC_T3_RAW;
extern uint16_t ADC_T3_Mean;
extern uint16_t ADC_AUX4_RAW;
extern uint16_t ADC_AUX4_Mean;
extern bool     ADC_Ready;
extern bool     ADC_Calib;

void App_ADC_Init(void *Parameters);
inline void App_ADC_Process_IRQ(void);
void App_ADC_Process_IDLE(void *Parameters);

#endif // APP_ADC_H
