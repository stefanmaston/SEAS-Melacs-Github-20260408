/*
 *  File name: App_DPLL.h
 *
 *  Description: High level function declarations for DPLL processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_DPLL_H
#define APP_DPLL_H

#include "types_dpll.h"

extern bool DPLL_Trigger;

extern SM_Main_t sm_state;
extern System_Error_t system_ERROR;

extern int16_t sine[];

void App_DPLL_Init(void *Parameters);
void App_DPLL_Process(void *Parameters);
void App_DPLL_Process_Control(void);
void App_DPLL_Param_Id_Set(uint16_t Value);
void App_DPLL_Param_Iq_Set(uint16_t Value);
void App_DPLL_Param_Vd_Set(uint16_t Value);
void App_DPLL_Param_Vq_Set(uint16_t Value);
void App_DPLL_Param_Omega_Set(uint16_t Value);
uint16_t App_DPLL_Param_Id_Get(void);
uint16_t App_DPLL_Param_Iq_Get(void);
uint16_t App_DPLL_Param_Vd_Get(void);
uint16_t App_DPLL_Param_Vq_Get(void);
uint16_t App_DPLL_Param_Omega_Get(void);
bool check_voltage(V_Meas_t node);
void SM_Delayed_Jump(uint16_t val, SM_Main_t next_state);
bool check_dpll(Dpll_Mode_t mode);
void main_state_machine(void);
void App_Main_SM_Init(void);
void timeout_on(void);
void timeout_off(void);

#endif // APP_DPLL_H
