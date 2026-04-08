#include <stdio.h>
#include "global_includes.h"
#include "motor_control.h"
#include "types_dpll.h"
#include "config_sm.h"
#include "App_DPLL.h"

#define EMI_BOARD
//#define ORTHOGONAL_ENABLED

int16_t qAngle = 0;
int16_t count = 0; /* delay for ramping the reference velocity */
int16_t velReq = 0;

#ifndef LOW_VOLTAGE_SCALERS
// Nominal voltage scaling
// U_INV, U_MID and U_GRID Scaling
#define BSP_SETTINGS_ADC_U_INV_SCALING_INV 1151
#define BSP_SETTINGS_ADC_U_MID_SCALING_INV 1151
#define BSP_SETTINGS_ADC_U_GRID_SCALING_INV 694

const int32_t U_Pk_HH=4512;    //100V    100*1.41*32
const int32_t U_Pk_HL=451;     //10V    10*1.41*32
#else	// LOW_VOLTAGE_SCALERS
// U_INV, U_MID and U_GRID Scaling
#define BSP_SETTINGS_ADC_U_INV_SCALING_INV 30892
#define BSP_SETTINGS_ADC_U_MID_SCALING_INV 30892
#define BSP_SETTINGS_ADC_U_GRID_SCALING_INV 20200

const int32_t U_Pk_HH=272;    //6V    6*1.41*32
const int32_t U_Pk_HL=91;     //2V    2*1.41*32
#endif	// LOW_VOLTAGE_SCALERS

//#define ORTO_BUF_SIZE 80
#define ORTO_BUF_SIZE 107		//120deg delay of 50Hz => (20ms/3)*16ks/s
#define MIN_DPLL_PERIOD 305	//(50Hz+5%) = 52.5hz => 19.05ms*16ks/s
#define MAX_DPLL_PERIOD 337 //(50Hz-5%) = 47.5hz => 21.05ms*16ks/s


int16_t U_Pk_Inv_HH;
int16_t U_Pk_Inv_HL;
int16_t U_Pk_Mid_HH;
int16_t U_Pk_Mid_HL; 
int16_t U_Pk_Grid_HH;
int16_t U_Pk_Grid_HL;

const int16_t DPLL_TRESHOLD = 3000;
const int16_t DPLL_PERIOD = 400;  //20ms/period * 20 periods
const int16_t DPLL_ON_STEP = 1;
const int16_t DPLL_OFF_STEP = 5;
const int16_t STEP_VAL = 10;
const int16_t I_GAIN = 0; // that means 2^1 so current gain = 2 

int16_t id_set=685;
int16_t iq_set=0;
int16_t vd_set=0;
int16_t vq_set=0;
//int16_t omegaL=5144;  //3.14*2*50*1E-03 << 14
int16_t omegaL=5000;  //3.14*2*50*1E-03 << 14

Dpll_Mode_t dpll_mode = APP_DPLL_OFF;
Control_Mode_t control_mode = APP_CONTROL_OFF;

static MC_ABC_T vg_in,vg_out;
static MC_ABC_T vg_grid, vg_load,vg_inv;
static MC_ABC_T ig_inv;
static MC_ALPHABETA_T vg_ab, ig_ab,inv_op_out_ab,vg_inv_ab;
static MC_DQ_T vg_dqp,ig_dq_out,vg_inv_dqp;
static MC_DQ_T inv_cp_out_dq;
static int16_t pi_paramout,pi_i_d_paramout, pi_i_q_paramout,pi_u_d_paramout,pi_u_q_paramout;
static MC_PISTATE_T pi_state, integrator_state, pi_i_d_state,pi_i_q_state,pi_u_d_state,pi_u_q_state;
#ifdef ORTHOGONAL_ENABLED     
static MC_ABC_T vg_in_orto_l1,vg_inv_orto_l1,ig_inv_orto_l1;
static MC_ABC_T vg_in_orto_l2,vg_inv_orto_l2,ig_inv_orto_l2;
static MC_ABC_T vg_in_orto_l3,vg_inv_orto_l3,ig_inv_orto_l3;
static MC_ALPHABETA_T vg_ab_orto_l1,vg_inv_ab_orto_l1,ig_ab_orto_l1;
static MC_ALPHABETA_T vg_ab_orto_l2,vg_inv_ab_orto_l2,ig_ab_orto_l2;
static MC_ALPHABETA_T vg_ab_orto_l3,vg_inv_ab_orto_l3,ig_ab_orto_l3;
static MC_DQ_T vg_inv_dqp_orto_l1,vg_dqp_orto_l1,ig_dq_out_orto_l1;
static MC_DQ_T vg_inv_dqp_orto_l2,vg_dqp_orto_l2,ig_dq_out_orto_l2;
static MC_DQ_T vg_inv_dqp_orto_l3,vg_dqp_orto_l3,ig_dq_out_orto_l3;
static int16_t pi_paramout_orto_l1,pi_paramout_orto_l2,pi_paramout_orto_l3;
static int16_t pi_i_d_paramout_orto_l1, pi_i_q_paramout_orto_l1,pi_u_d_paramout_orto_l1,pi_u_q_paramout_orto_l1;
static int16_t pi_i_d_paramout_orto_l2, pi_i_q_paramout_orto_l2,pi_u_d_paramout_orto_l2,pi_u_q_paramout_orto_l2;
static int16_t pi_i_d_paramout_orto_l3, pi_i_q_paramout_orto_l3,pi_u_d_paramout_orto_l3,pi_u_q_paramout_orto_l3;
static MC_PISTATE_T pi_state_orto_l1, integrator_state_orto_l1;
static MC_PISTATE_T pi_state_orto_l2, integrator_state_orto_l2;
static MC_PISTATE_T pi_state_orto_l3, integrator_state_orto_l3;
static MC_PISTATE_T pi_i_d_state_orto_l1,pi_i_q_state_orto_l1,pi_u_d_state_orto_l1,pi_u_q_state_orto_l1;
static MC_PISTATE_T pi_i_d_state_orto_l2,pi_i_q_state_orto_l2,pi_u_d_state_orto_l2,pi_u_q_state_orto_l2;
static MC_PISTATE_T pi_i_d_state_orto_l3,pi_i_q_state_orto_l3,pi_u_d_state_orto_l3,pi_u_q_state_orto_l3;
static MC_SINCOS_T sin_cos_orto_l1,sin_cos_orto_l2,sin_cos_orto_l3;
static int16_t theta_orto_l1,theta_orto_l1_d;
static int16_t theta_orto_l2,theta_orto_l2_d;
static int16_t theta_orto_l3,theta_orto_l3_d;

uint16_t orto_buf_u_in_index_l1;
uint16_t orto_buf_u_inv_index_l1;
uint16_t orto_buf_i_inv_index_l1;
int16_t *orto_buf_u_in_ptr_l1;
int16_t orto_buf_u_in_l1[ORTO_BUF_SIZE];
int16_t *orto_buf_u_inv_ptr_l1;
int16_t orto_buf_u_inv_l1[ORTO_BUF_SIZE];
int16_t *orto_buf_i_inv_ptr_l1;
int16_t orto_buf_i_inv_l1[ORTO_BUF_SIZE];

uint16_t orto_buf_u_in_index_l2;
uint16_t orto_buf_u_inv_index_l2;
uint16_t orto_buf_i_inv_index_l2;
int16_t *orto_buf_u_in_ptr_l2;
int16_t orto_buf_u_in_l2[ORTO_BUF_SIZE];
//int16_t orto_buf_u_in_l2[2];
int16_t *orto_buf_u_inv_ptr_l2;
int16_t orto_buf_u_inv_l2[ORTO_BUF_SIZE];
//int16_t orto_buf_u_inv_l2[2];

int16_t *orto_buf_i_inv_ptr_l2;
int16_t orto_buf_i_inv_l2[ORTO_BUF_SIZE];
//int16_t orto_buf_i_inv_l2[2];


uint16_t orto_buf_u_in_index_l3;
uint16_t orto_buf_u_inv_index_l3;
uint16_t orto_buf_i_inv_index_l3;
int16_t *orto_buf_u_in_ptr_l3;
int16_t orto_buf_u_in_l3[ORTO_BUF_SIZE];
//int16_t orto_buf_u_in_l3[2];
int16_t *orto_buf_u_inv_ptr_l3;
int16_t orto_buf_u_inv_l3[ORTO_BUF_SIZE];
//int16_t orto_buf_u_inv_l3[2];
int16_t *orto_buf_i_inv_ptr_l3;
int16_t orto_buf_i_inv_l3[ORTO_BUF_SIZE];
//int16_t orto_buf_i_inv_l3[2];

#endif

static MC_SINCOS_T sin_cos;
static MC_SINCOS_T sin_cos_in_a;
static MC_SINCOS_T sin_cos_in_b;

static int16_t theta,theta_out,theta_int;
int32_t i,j,cycle_cnt;
int16_t load;
int32_t inv_cp_out_dqd_temp,inv_cp_out_dqq_temp;
static int16_t sampling=205;
int16_t d,q,alpha,beta;
int16_t r_bottom;
    
MC_ABC_T r_grid,r_inv,r_load;
MC_ABC_T rlri,rgrl,rlrgri;
MC_ABC_T i_grid,i_inv,i_load,i_sum;

bool relay_on;

static int32_t temp1,temp2;

static int16_t id_curr,iq_curr,id_step,iq_step;

#define SM_TIMEOUT_VAL 5000;  // 5000ms

static bool timeout_on_v = false;
bool DPLL_Trigger = false;
static bool dpll_locked = false;
static int16_t dpll_lock_cnt_l1, dpll_lock_cnt_l2, dpll_lock_cnt_l3;
/*static*/ SM_Main_t sm_state=SM_PRE_START;
static SM_Main_t sm_error_state= SM_ERROR;
static SM_Main_t next_sm_state;
/*static*/ System_Error_t system_ERROR=ERROR_NONE;
static uint16_t delay_counter=0;
static uint16_t timeout_counter=SM_TIMEOUT_VAL;
static SM_Main_t sm_timeout_state=SM_PRE_START;

static uint16_t l1_period, l1_tmp_period;
static uint16_t l2_period, l2_tmp_period;
static uint16_t l3_period, l3_tmp_period;

void PID_I_Init(void)
{
    pi_i_d_state_orto_l1.integrator=0;
    pi_i_d_state_orto_l1.kc=0;
    pi_i_d_state_orto_l1.kp=1500;
    pi_i_d_state_orto_l1.ki=20;
    pi_i_d_state_orto_l1.outMax=32000;
    pi_i_d_state_orto_l1.outMin=-32000;

    
    pi_i_q_state_orto_l1.integrator=0;
    pi_i_q_state_orto_l1.kc=0;
    pi_i_q_state_orto_l1.kp=1500;
    pi_i_q_state_orto_l1.ki=20;
    pi_i_q_state_orto_l1.outMax=32000;
    pi_i_q_state_orto_l1.outMin=-32000;	
		
    pi_i_d_state_orto_l2.integrator=0;
    pi_i_d_state_orto_l2.kc=0;
    pi_i_d_state_orto_l2.kp=1500;
    pi_i_d_state_orto_l2.ki=20;
    pi_i_d_state_orto_l2.outMax=0x7fff;
    pi_i_d_state_orto_l2.outMin=0x8000;

    
    pi_i_q_state_orto_l2.integrator=0;
    pi_i_q_state_orto_l2.kc=0;
    pi_i_q_state_orto_l2.kp=1500;
    pi_i_q_state_orto_l2.ki=20;
    pi_i_q_state_orto_l2.outMax=0x7fff;
    pi_i_q_state_orto_l2.outMin=0x8000;
		
    pi_i_d_state_orto_l3.integrator=0;
    pi_i_d_state_orto_l3.kc=0;
    pi_i_d_state_orto_l3.kp=1500;
    pi_i_d_state_orto_l3.ki=20;
    pi_i_d_state_orto_l3.outMax=0x7fff;
    pi_i_d_state_orto_l3.outMin=0x8000;

    
    pi_i_q_state_orto_l3.integrator=0;
    pi_i_q_state_orto_l3.kc=0;
    pi_i_q_state_orto_l3.kp=1500;
    pi_i_q_state_orto_l3.ki=20;
    pi_i_q_state_orto_l3.outMax=0x7fff;
    pi_i_q_state_orto_l3.outMin=0x8000;
		
}

void PID_U_Init(void)
{
    pi_u_d_state_orto_l1.integrator=0;
    pi_u_d_state_orto_l1.kc=0;
    pi_u_d_state_orto_l1.kp=1500;
    pi_u_d_state_orto_l1.ki=20;
    pi_u_d_state_orto_l1.outMax=32000;
    pi_u_d_state_orto_l1.outMin=-32000;

    pi_u_q_state_orto_l1.integrator=0;
    pi_u_q_state_orto_l1.kc=0;
    pi_u_q_state_orto_l1.kp=1500;
    pi_u_q_state_orto_l1.ki=20;
    pi_u_q_state_orto_l1.outMax=32000;
    pi_u_q_state_orto_l1.outMin=-32000;
		
    pi_u_d_state_orto_l2.integrator=0;
    pi_u_d_state_orto_l2.kc=0;
    pi_u_d_state_orto_l2.kp=1500;
    pi_u_d_state_orto_l2.ki=20;
    pi_u_d_state_orto_l2.outMax=0x7fff;
    pi_u_d_state_orto_l2.outMin=0x8000;

    pi_u_q_state_orto_l2.integrator=0;
    pi_u_q_state_orto_l2.kc=0;
    pi_u_q_state_orto_l2.kp=1500;
    pi_u_q_state_orto_l2.ki=20;
    pi_u_q_state_orto_l2.outMax=0x7fff;
    pi_u_q_state_orto_l2.outMin=0x8000;
		
    pi_u_d_state_orto_l3.integrator=0;
    pi_u_d_state_orto_l3.kc=0;
    pi_u_d_state_orto_l3.kp=1500;
    pi_u_d_state_orto_l3.ki=20;
    pi_u_d_state_orto_l3.outMax=0x7fff;
    pi_u_d_state_orto_l3.outMin=0x8000;

    pi_u_q_state_orto_l3.integrator=0;
    pi_u_q_state_orto_l3.kc=0;
    pi_u_q_state_orto_l3.kp=1500;
    pi_u_q_state_orto_l3.ki=20;
    pi_u_q_state_orto_l3.outMax=0x7fff;
    pi_u_q_state_orto_l3.outMin=0x8000;
}

void App_DPLL_Init(void *Parameters)
{
    (void)Parameters;
    
#ifdef ORTHOGONAL_ENABLED              
    theta_orto_l1=0;
    
    pi_state_orto_l1.integrator=0;
    pi_state_orto_l1.kc=0;
    pi_state_orto_l1.kp=630;  //Ku=1300
    pi_state_orto_l1.ki=10;
    pi_state_orto_l1.outMax=0x7fff; // +1
    pi_state_orto_l1.outMin=0x8000; // -1

    
    orto_buf_u_in_ptr_l1=orto_buf_u_in_l1;
    orto_buf_u_inv_ptr_l1=orto_buf_u_inv_l1;
    orto_buf_i_inv_ptr_l1=orto_buf_i_inv_l1;
    orto_buf_u_in_index_l1=0;
    orto_buf_u_inv_index_l1=0;
    orto_buf_i_inv_index_l1=0;

    theta_orto_l2=0;
    
    pi_state_orto_l2.integrator=0;
    pi_state_orto_l2.kc=0;
    pi_state_orto_l2.kp=630;  //Ku=1300
    pi_state_orto_l2.ki=10;
    pi_state_orto_l2.outMax=0x7fff; // +1
    pi_state_orto_l2.outMin=0x8000; // -1

    
    orto_buf_u_in_ptr_l2=orto_buf_u_in_l2;
    orto_buf_u_inv_ptr_l2=orto_buf_u_inv_l2;
    orto_buf_i_inv_ptr_l2=orto_buf_i_inv_l2;
    orto_buf_u_in_index_l2=0;
    orto_buf_u_inv_index_l2=0;
    orto_buf_i_inv_index_l2=0;
    
    theta_orto_l3=0;
    
    pi_state_orto_l3.integrator=0;
    pi_state_orto_l3.kc=0;
    pi_state_orto_l3.kp=630;  //Ku=1300
    pi_state_orto_l3.ki=10;
    pi_state_orto_l3.outMax=0x7fff; // +1
    pi_state_orto_l3.outMin=0x8000; // -1
		
    orto_buf_u_in_ptr_l3=orto_buf_u_in_l3;
    orto_buf_u_inv_ptr_l3=orto_buf_u_inv_l3;
    orto_buf_i_inv_ptr_l3=orto_buf_i_inv_l3;
    orto_buf_u_in_index_l3=0;
    orto_buf_u_inv_index_l3=0;
    orto_buf_i_inv_index_l3=0;    
#else
    theta=0;
    theta_out=0;
    theta_int=0;
    load=10;
    sampling=205;
    relay_on=0;
    dpll_locked=false;
    dpll_lock_cnt_l1=0;
		dpll_lock_cnt_l2=0;
		dpll_lock_cnt_l3=0;
    
    pi_state.integrator=0;
    pi_state.kc=0;
    pi_state.kp=630;  //Ku=1300
    pi_state.ki=10;
    pi_state.outMax=0x7fff; // +1
    pi_state.outMin=0x8000; // -1

    pi_i_d_state.integrator=0;
    pi_i_d_state.kc=0;
    pi_i_d_state.kp=1500;
    pi_i_d_state.ki=20;
    pi_i_d_state.outMax=0x7fff;
    pi_i_d_state.outMin=0x8000;

    
    pi_i_q_state.integrator=0;
    pi_i_q_state.kc=0;
    pi_i_q_state.kp=1500;
    pi_i_q_state.ki=20;
    pi_i_q_state.outMax=0x7fff;
    pi_i_q_state.outMin=0x8000;
    
    pi_u_d_state.integrator=0;
    pi_u_d_state.kc=0;
    pi_u_d_state.kp=1500;
    pi_u_d_state.ki=20;
    pi_u_d_state.outMax=0x7fff;
    pi_u_d_state.outMin=0x8000;

    pi_u_q_state.integrator=0;
    pi_u_q_state.kc=0;
    pi_u_q_state.kp=1500;
    pi_u_q_state.ki=20;
    pi_u_q_state.outMax=0x7fff;
    pi_u_q_state.outMin=0x8000;
#endif    
    
		l1_period=0;
		l1_tmp_period=0;
		l2_period=0;
		l2_tmp_period=0;
		l3_period=0;
		l3_tmp_period=0;
		theta_orto_l1=0;
		theta_orto_l1_d=0;
		theta_orto_l2=0;
		theta_orto_l2_d=0;
		theta_orto_l3=0;
		theta_orto_l3_d=0;
    vg_grid.a=0;
    vg_grid.b=0;
    vg_grid.c=0;
    vg_load.a=0;
    vg_load.b=0;
    vg_load.c=0;
    vg_inv.a=0;
    vg_inv.b=0;
    vg_inv.c=0;
    relay_on=0;
}

void App_DPLL_Param_Id_Set(uint16_t Value)
{
	id_set = Value >> 2;
}

uint16_t App_DPLL_Param_Id_Get(void)
{
	return (uint16_t)id_set << 2;
}

void App_DPLL_Param_Iq_Set(uint16_t Value)
{
	iq_set = Value >> 2;
}

uint16_t App_DPLL_Param_Iq_Get(void)
{
	return (uint16_t)iq_set << 2;
}


void App_DPLL_Param_Vd_Set(uint16_t Value)
{
	vd_set = Value >> 1;
}

uint16_t App_DPLL_Param_Vd_Get(void)
{
	return (uint16_t)vd_set << 1;
}

void App_DPLL_Param_Vq_Set(uint16_t Value)
{
	vq_set = Value >> 1;
}

uint16_t App_DPLL_Param_Vq_Get(void)
{
	return (uint16_t)vq_set << 1;
}

void App_DPLL_Param_Omega_Set(uint16_t Value)
{
	omegaL = Value;
}

uint16_t App_DPLL_Param_Omega_Get(void)
{
	return omegaL;
}

int16_t UInt16_to_Int16_Conv(uint16_t Value)
{
	return (int16_t)((int32_t)Value - 32768);
}

uint16_t Int16_to_UInt16_Conv(int16_t Value)
{
	return (uint16_t)((int32_t)Value + 32768);
}

int16_t ADC12_to_Q1_15_Conv(uint16_t Value)
{
	return (int16_t)(((int32_t)Value - 2048) << 4);		// 12bit -> Q1.15 (x * 16)
}

void App_DPLL_Process(void *Parameters)
{
  uint16_t *i;
  i = Parameters;
  if((App_SM_System_Mode != APP_SM_SYSTEM_MODE_TEST)&&(App_SM_System_Mode!=APP_SM_SYSTEM_MODE_IDLE))
  { 
    MC_CalculateSineCosine_Assembly_Ram(theta,&sin_cos);
    if(dpll_mode==APP_DPLL_OFF)
    {  
     MC_CalculateSineCosine_Assembly_Ram(*i,&sin_cos_in_a);
     MC_CalculateSineCosine_Assembly_Ram(*i+0x5555,&sin_cos_in_b);    //+120 deg
     vg_in.a=((int16_t)sin_cos_in_a.sin>>2);
     vg_in.b=((int16_t)sin_cos_in_b.sin>>2);
    }
    else
    {
      vg_in.a=((int16_t)(ADC_L1_U_Mid_Conv)<<4);
      vg_in.b=((int16_t)(ADC_L2_U_Mid_Conv)<<4);
      vg_in.c=((int16_t)(ADC_L3_U_Mid_Conv)<<4);
      
      vg_inv.a=((int16_t)(ADC_L1_U_Inv_Conv)<<4);
      vg_inv.b=((int16_t)(ADC_L2_U_Inv_Conv)<<4);
      vg_inv.c=((int16_t)(ADC_L3_U_Inv_Conv)<<4);
    }
    switch(control_mode)
    {  
      case APP_VCB_ON:
      case APP_CCB_ON:
        MC_TransformClarke_Assembly(&vg_in,&vg_ab);
        MC_TransformPark_Assembly(&vg_ab,&sin_cos,&vg_dqp);
        MC_ControllerPIUpdate_Assembly(0,vg_dqp.q,&pi_state,&pi_paramout);
        theta_out=pi_paramout;
        theta+=theta_out;
        MC_TransformClarke_Assembly(&vg_inv,&vg_inv_ab);
        MC_TransformPark_Assembly(&vg_inv_ab,&sin_cos,&vg_inv_dqp);
      break;
      
      case APP_VCB_ORTO3_ON:
      case APP_CCB_ORTO3_ON:  
			case APP_CONTROL_OFF:
        vg_in_orto_l2.a=vg_in.b;
        *orto_buf_u_in_ptr_l2++=vg_in_orto_l2.a;        
        orto_buf_u_in_index_l2++;
        if(orto_buf_u_in_index_l2==ORTO_BUF_SIZE)
        {
          orto_buf_u_in_index_l2=0;
          orto_buf_u_in_ptr_l2=orto_buf_u_in_l2;
        }
        vg_in_orto_l2.b=*orto_buf_u_in_ptr_l2;
        MC_CalculateSineCosine_Assembly_Ram(theta_orto_l2,&sin_cos_orto_l2);
        MC_TransformClarke_Assembly(&vg_in_orto_l2,&vg_ab_orto_l2);
        MC_TransformPark_Assembly(&vg_ab_orto_l2,&sin_cos_orto_l2,&vg_dqp_orto_l2);
        MC_ControllerPIUpdate_Assembly(0,vg_dqp_orto_l2.q,&pi_state_orto_l2,&pi_paramout_orto_l2);
        theta_orto_l2+=pi_paramout_orto_l2;
				if(theta_orto_l2_d<0 && theta_orto_l2>=0)	//zero crossing
				{
					l2_period=l2_tmp_period;
					l2_tmp_period=0;
				}	
				else
					l2_tmp_period++;
        theta_orto_l2_d=theta_orto_l2;
				
        vg_in_orto_l3.a=vg_in.c;
        *orto_buf_u_in_ptr_l3++=vg_in_orto_l3.a;        
        orto_buf_u_in_index_l3++;
        if(orto_buf_u_in_index_l3==ORTO_BUF_SIZE)
        {
          orto_buf_u_in_index_l3=0;
          orto_buf_u_in_ptr_l3=orto_buf_u_in_l3;
        }
        vg_in_orto_l3.b=*orto_buf_u_in_ptr_l3;
        MC_CalculateSineCosine_Assembly_Ram(theta_orto_l3,&sin_cos_orto_l3);
        MC_TransformClarke_Assembly(&vg_in_orto_l3,&vg_ab_orto_l3);
        MC_TransformPark_Assembly(&vg_ab_orto_l3,&sin_cos_orto_l3,&vg_dqp_orto_l3);
        MC_ControllerPIUpdate_Assembly(0,vg_dqp_orto_l3.q,&pi_state_orto_l3,&pi_paramout_orto_l3);
        theta_orto_l3+=pi_paramout_orto_l3;   
				if(theta_orto_l3_d<0 && theta_orto_l3>=0)	//zero crossing
				{
					l3_period=l3_tmp_period;
					l3_tmp_period=0;
				}	
				else
					l3_tmp_period++;
        theta_orto_l3_d=theta_orto_l3;    
				
        vg_inv_orto_l2.a=vg_inv.b;
        *orto_buf_u_inv_ptr_l2++=vg_inv_orto_l2.a;        
        orto_buf_u_inv_index_l2++;
        if(orto_buf_u_inv_index_l2==ORTO_BUF_SIZE)
        {
          orto_buf_u_inv_index_l2=0;
          orto_buf_u_inv_ptr_l2=orto_buf_u_inv_l2;
        }
        vg_inv_orto_l2.b=*orto_buf_u_inv_ptr_l2;   
        MC_TransformClarke_Assembly(&vg_inv_orto_l2,&vg_inv_ab_orto_l2);
        MC_TransformPark_Assembly(&vg_inv_ab_orto_l2,&sin_cos_orto_l2,&vg_inv_dqp_orto_l2);

        vg_inv_orto_l3.a=vg_inv.c;
        *orto_buf_u_inv_ptr_l3++=vg_inv_orto_l3.a;        
        orto_buf_u_inv_index_l3++;
        if(orto_buf_u_inv_index_l3==ORTO_BUF_SIZE)
        {
          orto_buf_u_inv_index_l3=0;
          orto_buf_u_inv_ptr_l3=orto_buf_u_inv_l3;
        }
        vg_inv_orto_l3.b=*orto_buf_u_inv_ptr_l3;   
        MC_TransformClarke_Assembly(&vg_inv_orto_l3,&vg_inv_ab_orto_l3);
        MC_TransformPark_Assembly(&vg_inv_ab_orto_l3,&sin_cos_orto_l3,&vg_inv_dqp_orto_l3);
        

      case APP_VCB_ORTO1_ON:  
      case APP_CCB_ORTO1_ON:  
        vg_in_orto_l1.a=vg_in.a;
        *orto_buf_u_in_ptr_l1++=vg_in_orto_l1.a;        
        orto_buf_u_in_index_l1++;
        if(orto_buf_u_in_index_l1==ORTO_BUF_SIZE)
        {
          orto_buf_u_in_index_l1=0;
          orto_buf_u_in_ptr_l1=orto_buf_u_in_l1;
        }
        vg_in_orto_l1.b=*orto_buf_u_in_ptr_l1;
        MC_CalculateSineCosine_Assembly_Ram(theta_orto_l1,&sin_cos_orto_l1);
        MC_TransformClarke_Assembly(&vg_in_orto_l1,&vg_ab_orto_l1);
        MC_TransformPark_Assembly(&vg_ab_orto_l1,&sin_cos_orto_l1,&vg_dqp_orto_l1);
        MC_ControllerPIUpdate_Assembly(0,vg_dqp_orto_l1.q,&pi_state_orto_l1,&pi_paramout_orto_l1);
        theta_orto_l1+=pi_paramout_orto_l1;
				if(theta_orto_l1_d<0 && theta_orto_l1>=0)	//zero crossing
				{
					l1_period=l1_tmp_period;
					l1_tmp_period=0;
				}	
				else
					l1_tmp_period++;
				
				
	/*	static uint8_t delay_cnt = 0;
		
		delay_cnt++;
		if(delay_cnt > 32)
			delay_cnt = 0;
		if(DPLL_Trigger && delay_cnt == 0)
		{
	
			App_DataRec_Store_16bit((uint16_t)l1_period);
			App_DataRec_Store_16bit((uint16_t)check_dpll(APP_DPLL_ON_1_PHASE));
			
		}		*/
        theta_orto_l1_d=theta_orto_l1;
        vg_inv_orto_l1.a=vg_inv.a;
        *orto_buf_u_inv_ptr_l1++=vg_inv_orto_l1.a;        
        orto_buf_u_inv_index_l1++;
        if(orto_buf_u_inv_index_l1==ORTO_BUF_SIZE)
        {
          orto_buf_u_inv_index_l1=0;
          orto_buf_u_inv_ptr_l1=orto_buf_u_inv_l1;
        }
        vg_inv_orto_l1.b=*orto_buf_u_inv_ptr_l1;   
        MC_TransformClarke_Assembly(&vg_inv_orto_l1,&vg_inv_ab_orto_l1);
        MC_TransformPark_Assembly(&vg_inv_ab_orto_l1,&sin_cos_orto_l1,&vg_inv_dqp_orto_l1);       
      break;
    }
  }
}

void App_DPLL_Process_Control(void)
{
    if((App_SM_System_Mode != APP_SM_SYSTEM_MODE_TEST)&&(App_SM_System_Mode != APP_SM_SYSTEM_MODE_IDLE))
    {      
          ig_inv.a=-((int16_t)((ADC_L1_I_Inv_Conv)<<5))>>I_GAIN; //4+1
          ig_inv.b=-((int16_t)((ADC_L2_I_Inv_Conv)<<5))>>I_GAIN; 
          ig_inv.c=-((int16_t)((ADC_L3_I_Inv_Conv)<<5))>>I_GAIN;
          

  switch(control_mode)
  {
    case APP_CONTROL_OFF:

    break; 
    
    case APP_VCB_ON:      
      MC_ControllerPIUpdate_Assembly(vg_dqp.d,vg_inv_dqp.d,&pi_u_d_state,&pi_u_d_paramout);
      MC_ControllerPIUpdate_Assembly(vg_dqp.q,vg_inv_dqp.q,&pi_u_q_state,&pi_u_q_paramout);
    break;
    
    case APP_VCB_ORTO3_ON:
      MC_ControllerPIUpdate_Assembly(vg_dqp_orto_l2.d,vg_inv_dqp_orto_l2.d,&pi_u_d_state_orto_l2,&pi_u_d_paramout_orto_l2);
      MC_ControllerPIUpdate_Assembly(vg_dqp_orto_l2.q,vg_inv_dqp_orto_l2.q,&pi_u_q_state_orto_l2,&pi_u_q_paramout_orto_l2);
   
      MC_ControllerPIUpdate_Assembly(vg_dqp_orto_l3.d,vg_inv_dqp_orto_l3.d,&pi_u_d_state_orto_l3,&pi_u_d_paramout_orto_l3);
      MC_ControllerPIUpdate_Assembly(vg_dqp_orto_l3.q,vg_inv_dqp_orto_l3.q,&pi_u_q_state_orto_l3,&pi_u_q_paramout_orto_l3);
      
    case APP_VCB_ORTO1_ON:
      MC_ControllerPIUpdate_Assembly(vg_dqp_orto_l1.d,vg_inv_dqp_orto_l1.d,&pi_u_d_state_orto_l1,&pi_u_d_paramout_orto_l1);
      MC_ControllerPIUpdate_Assembly(vg_dqp_orto_l1.q,vg_inv_dqp_orto_l1.q,&pi_u_q_state_orto_l1,&pi_u_q_paramout_orto_l1);
    break;
    
    case APP_CCB_ON:
      MC_TransformClarke_Assembly(&ig_inv,&ig_ab);
      MC_TransformPark_Assembly(&ig_ab,&sin_cos,&ig_dq_out);     
      MC_ControllerPIUpdate_Assembly(-id_curr>>1,ig_dq_out.d,&pi_i_d_state,&pi_i_d_paramout);
      MC_ControllerPIUpdate_Assembly(-iq_curr>>1,ig_dq_out.q,&pi_i_q_state,&pi_i_q_paramout);       
    break;  
    
    case APP_CCB_ORTO3_ON:
      MC_ControllerPIUpdate_Assembly(-id_curr>>1,ig_dq_out_orto_l2.d,&pi_i_d_state_orto_l2,&pi_i_d_paramout_orto_l2);
      MC_ControllerPIUpdate_Assembly(-iq_curr>>1,ig_dq_out_orto_l2.q,&pi_i_q_state_orto_l2,&pi_i_q_paramout_orto_l2);
      MC_ControllerPIUpdate_Assembly(-id_curr>>1,ig_dq_out_orto_l3.d,&pi_i_d_state_orto_l3,&pi_i_d_paramout_orto_l3);
      MC_ControllerPIUpdate_Assembly(-iq_curr>>1,ig_dq_out_orto_l3.q,&pi_i_q_state_orto_l3,&pi_i_q_paramout_orto_l3); 
      
    case APP_CCB_ORTO1_ON:  
      MC_ControllerPIUpdate_Assembly(-id_curr>>1,ig_dq_out_orto_l1.d,&pi_i_d_state_orto_l1,&pi_i_d_paramout_orto_l1);
      MC_ControllerPIUpdate_Assembly(-iq_curr>>1,ig_dq_out_orto_l1.q,&pi_i_q_state_orto_l1,&pi_i_q_paramout_orto_l1);
    break;           
  }
               
        switch(control_mode)
        {
            case APP_CONTROL_OFF:
                inv_cp_out_dq.q= vq_set;
                inv_cp_out_dq.d= vd_set;               
            break; 
            
            case APP_VCB_ON: 
              temp1=(int32_t)vg_dqp.d+(int32_t)pi_u_d_paramout+(int32_t)pi_i_d_paramout;
              temp2=(int32_t)vg_dqp.q+(int32_t)pi_u_q_paramout+(int32_t)pi_i_q_paramout;
              if(temp1>32000)
                temp1=32000;
              if(temp1 <-32000)
                temp1=-32000;
              if(temp2>32000)
                temp2=32000;
              if(temp2 <-32000)
                temp2=-32000;
              inv_cp_out_dq.d= (int16_t)temp1;
              inv_cp_out_dq.q= (int16_t)temp2;
              MC_TransformParkInverse_InlineC(&inv_cp_out_dq,&sin_cos,&inv_op_out_ab);
              break;
      
            case APP_CCB_ON:
              temp1=(int32_t)(((int32_t)omegaL*(int32_t)ig_dq_out.q)>>15);
              temp1+=(int32_t)vg_dqp.d +(int32_t)pi_i_d_paramout+(int32_t)pi_u_d_paramout; 
              temp2=-(int32_t)(((int32_t)omegaL*(int32_t)ig_dq_out.d)>>15);
              temp2+=(int32_t)vg_dqp.q +(int32_t)pi_i_q_paramout+(int32_t)pi_u_q_paramout;
              if(temp1>32000)
                temp1=32000;
              if(temp1 <-32000)
                temp1=-32000;
              if(temp2>32000)
                temp2=32000;
              if(temp2 <-32000)
                temp2=-32000;
              inv_cp_out_dq.d= (int16_t)temp1;
              inv_cp_out_dq.q= (int16_t)temp2;
              MC_TransformParkInverse_InlineC(&inv_cp_out_dq,&sin_cos,&inv_op_out_ab);
            break;        
              
            case APP_VCB_ORTO3_ON: 
                temp1=(int32_t)vg_inv_dqp_orto_l2.d+(int32_t)pi_u_d_paramout_orto_l2+(int32_t)pi_i_d_paramout_orto_l2;
		temp2=(int32_t)vg_inv_dqp_orto_l2.q+(int32_t)pi_u_q_paramout_orto_l2+(int32_t)pi_i_q_paramout_orto_l2;
                if(temp1>32000)
                    temp1=32000;
                if(temp1 <-32000)
                    temp1=-32000;
                if(temp2>32000)
                    temp2=32000;
                if(temp2 <-32000)
                    temp2=-32000;
                inv_cp_out_dq.d= (int16_t)temp1;
                inv_cp_out_dq.q= (int16_t)temp2;
                MC_TransformParkInverse_InlineC(&inv_cp_out_dq,&sin_cos_orto_l2,&inv_op_out_ab);
                alpha=inv_op_out_ab.alpha;
                beta=inv_op_out_ab.beta;
                inv_op_out_ab.alpha=beta;
                inv_op_out_ab.beta=alpha;
                MC_TransformClarkeInverseSwappedInput_Assembly(&inv_op_out_ab,&vg_out);  
		BSP_PWM_Channel_2_Set_DutyCycle(Int16_to_UInt16_Conv(vg_out.a));
                
                temp1=(int32_t)vg_inv_dqp_orto_l3.d+(int32_t)pi_u_d_paramout_orto_l3+(int32_t)pi_i_d_paramout_orto_l3;
		temp2=(int32_t)vg_inv_dqp_orto_l3.q+(int32_t)pi_u_q_paramout_orto_l3+(int32_t)pi_i_q_paramout_orto_l3;
                if(temp1>32000)
                    temp1=32000;
                if(temp1 <-32000)
                    temp1=-32000;
                if(temp2>32000)
                    temp2=32000;
                if(temp2 <-32000)
                    temp2=-32000;
                inv_cp_out_dq.d= (int16_t)temp1;
                inv_cp_out_dq.q= (int16_t)temp2;
                MC_TransformParkInverse_InlineC(&inv_cp_out_dq,&sin_cos_orto_l3,&inv_op_out_ab);
                alpha=inv_op_out_ab.alpha;
                beta=inv_op_out_ab.beta;
                inv_op_out_ab.alpha=beta;
                inv_op_out_ab.beta=alpha;
                MC_TransformClarkeInverseSwappedInput_Assembly(&inv_op_out_ab,&vg_out);  
		BSP_PWM_Channel_3_Set_DutyCycle(Int16_to_UInt16_Conv(vg_out.a)); 
                
            case APP_VCB_ORTO1_ON:   
		temp1=(int32_t)vg_inv_dqp_orto_l1.d+(int32_t)pi_u_d_paramout_orto_l1+(int32_t)pi_i_d_paramout_orto_l1;
		temp2=(int32_t)vg_inv_dqp_orto_l1.q+(int32_t)pi_u_q_paramout_orto_l1+(int32_t)pi_i_q_paramout_orto_l1;
                if(temp1>32000)
                    temp1=32000;
                if(temp1 <-32000)
                    temp1=-32000;
                if(temp2>32000)
                    temp2=32000;
                if(temp2 <-32000)
                    temp2=-32000;
                inv_cp_out_dq.d= (int16_t)temp1;
                inv_cp_out_dq.q= (int16_t)temp2;
                MC_TransformParkInverse_InlineC(&inv_cp_out_dq,&sin_cos_orto_l1,&inv_op_out_ab);
                alpha=inv_op_out_ab.alpha;
                beta=inv_op_out_ab.beta;
                inv_op_out_ab.alpha=beta;
                inv_op_out_ab.beta=alpha;
                MC_TransformClarkeInverseSwappedInput_Assembly(&inv_op_out_ab,&vg_out);  
		BSP_PWM_Channel_1_Set_DutyCycle(Int16_to_UInt16_Conv(vg_out.a));
            break;
                    
            case APP_CCB_ORTO3_ON:
                ig_inv_orto_l2.a=ig_inv.b;
                *orto_buf_i_inv_ptr_l2++=ig_inv_orto_l2.a;
                orto_buf_i_inv_index_l2++;
                if(orto_buf_i_inv_index_l2==ORTO_BUF_SIZE)
                {
                  orto_buf_i_inv_index_l2=0;
                  orto_buf_i_inv_ptr_l2=orto_buf_i_inv_l2;
                }
                ig_inv_orto_l2.b=*orto_buf_i_inv_ptr_l2;
                MC_TransformClarke_Assembly(&ig_inv_orto_l2,&ig_ab_orto_l2);
                MC_TransformPark_Assembly(&ig_ab_orto_l2,&sin_cos_orto_l2,&ig_dq_out_orto_l2);
                
                temp1=(int32_t)(((int32_t)omegaL*(int32_t)ig_dq_out_orto_l2.q)>>15); 
                temp1+=(int32_t)vg_dqp_orto_l2.d+(int32_t)pi_i_d_paramout_orto_l2+(int32_t)pi_u_d_paramout_orto_l2;
                temp2=-(int32_t)(((int32_t)omegaL*(int32_t)ig_dq_out_orto_l2.d)>>15);
                temp2+=(int32_t)vg_dqp_orto_l2.q+(int32_t)pi_i_q_paramout_orto_l2+(int32_t)pi_u_q_paramout_orto_l2;
                if(temp1>32000)
                    temp1=32000;
                if(temp1 <-32000)
                    temp1=-32000;
                if(temp2>32000)
                    temp2=32000;
                if(temp2 <-32000)
                    temp2=-32000;
                inv_cp_out_dq.d= (int16_t)temp1;
                inv_cp_out_dq.q= (int16_t)temp2;
                MC_TransformParkInverse_InlineC(&inv_cp_out_dq,&sin_cos_orto_l2,&inv_op_out_ab);  
                alpha=inv_op_out_ab.alpha;
                beta=inv_op_out_ab.beta;
                inv_op_out_ab.alpha=beta;
                inv_op_out_ab.beta=alpha;
                MC_TransformClarkeInverseSwappedInput_Assembly(&inv_op_out_ab,&vg_out);  
		BSP_PWM_Channel_2_Set_DutyCycle(Int16_to_UInt16_Conv(vg_out.a));
                //App_DataRec_Store_16bit((uint16_t)vg_out.a);
                ig_inv_orto_l3.a=ig_inv.c;
                *orto_buf_i_inv_ptr_l3++=ig_inv_orto_l3.a;     
                orto_buf_i_inv_index_l3++;
                if(orto_buf_i_inv_index_l3==ORTO_BUF_SIZE)
                {
                  orto_buf_i_inv_index_l3=0;
                  orto_buf_i_inv_ptr_l3=orto_buf_i_inv_l3;
                }
                ig_inv_orto_l3.b=*orto_buf_i_inv_ptr_l3;
                MC_TransformClarke_Assembly(&ig_inv_orto_l3,&ig_ab_orto_l3);
                MC_TransformPark_Assembly(&ig_ab_orto_l3,&sin_cos_orto_l3,&ig_dq_out_orto_l3);    
                              
                temp1=(int32_t)(((int32_t)omegaL*(int32_t)ig_dq_out_orto_l3.q)>>15); 
                temp1+=(int32_t)vg_dqp_orto_l3.d+(int32_t)pi_i_d_paramout_orto_l3+(int32_t)pi_u_d_paramout_orto_l3;
                temp2=-(int32_t)(((int32_t)omegaL*(int32_t)ig_dq_out_orto_l3.d)>>15);
                temp2+=(int32_t)vg_dqp_orto_l3.q+(int32_t)pi_i_q_paramout_orto_l3+(int32_t)pi_u_q_paramout_orto_l3;
                if(temp1>32000)
                    temp1=32000;
                if(temp1 <-32000)
                    temp1=-32000;
                if(temp2>32000)
                    temp2=32000;
                if(temp2 <-32000)
                    temp2=-32000;
                inv_cp_out_dq.d= (int16_t)temp1;
                inv_cp_out_dq.q= (int16_t)temp2;
                MC_TransformParkInverse_InlineC(&inv_cp_out_dq,&sin_cos_orto_l3,&inv_op_out_ab);	
                alpha=inv_op_out_ab.alpha;
                beta=inv_op_out_ab.beta;
                inv_op_out_ab.alpha=beta;
                inv_op_out_ab.beta=alpha;
                MC_TransformClarkeInverseSwappedInput_Assembly(&inv_op_out_ab,&vg_out);  
		BSP_PWM_Channel_3_Set_DutyCycle(Int16_to_UInt16_Conv(vg_out.a));
            //App_DataRec_Store_16bit((uint16_t)vg_out.a);    
            case APP_CCB_ORTO1_ON:
                ig_inv_orto_l1.a=ig_inv.a;
                *orto_buf_i_inv_ptr_l1++=ig_inv_orto_l1.a;     
                orto_buf_i_inv_index_l1++;
                if(orto_buf_i_inv_index_l1==ORTO_BUF_SIZE)
                {
                  orto_buf_i_inv_index_l1=0;
                  orto_buf_i_inv_ptr_l1=orto_buf_i_inv_l1;
                }
                ig_inv_orto_l1.b=*orto_buf_i_inv_ptr_l1;
                MC_TransformClarke_Assembly(&ig_inv_orto_l1,&ig_ab_orto_l1);
                MC_TransformPark_Assembly(&ig_ab_orto_l1,&sin_cos_orto_l1,&ig_dq_out_orto_l1);
                temp1=(int32_t)(((int32_t)omegaL*(int32_t)ig_dq_out_orto_l1.q)>>15); 
                temp1+=(int32_t)vg_dqp_orto_l1.d+(int32_t)pi_i_d_paramout_orto_l1+(int32_t)pi_u_d_paramout_orto_l1;
                temp2=-(int32_t)(((int32_t)omegaL*(int32_t)ig_dq_out_orto_l1.d)>>15);
                temp2+=(int32_t)vg_dqp_orto_l1.q+(int32_t)pi_i_q_paramout_orto_l1+(int32_t)pi_u_q_paramout_orto_l1;
                if(temp1>32000)
                    temp1=32000;
                if(temp1 <-32000)
                    temp1=-32000;
                if(temp2>32000)
                    temp2=32000;
                if(temp2 <-32000)
                    temp2=-32000;
                inv_cp_out_dq.d= (int16_t)temp1;      
                inv_cp_out_dq.q= (int16_t)temp2;
                MC_TransformParkInverse_InlineC(&inv_cp_out_dq,&sin_cos_orto_l1,&inv_op_out_ab);
                alpha=inv_op_out_ab.alpha;
                beta=inv_op_out_ab.beta;
                inv_op_out_ab.alpha=beta;
                inv_op_out_ab.beta=alpha;
                MC_TransformClarkeInverseSwappedInput_Assembly(&inv_op_out_ab,&vg_out);  
		BSP_PWM_Channel_1_Set_DutyCycle(Int16_to_UInt16_Conv(vg_out.a));
            break;           
        }

 
                 

#ifdef APP_DATAREC_ENABLED
		//App_DataRec_Store_16bit((uint16_t)(ADC_L1_U_Mid_Conv<<4));
		//App_DataRec_Store_16bit((uint16_t)(ADC_L1_I_Inv_Conv<<5));
		
		//App_DataRec_Store_16bit((uint16_t)PDC1);
		//App_DataRec_Store_16bit((uint16_t)PDC2);
		//App_DataRec_Store_16bit((uint16_t)PDC3);
#endif	// APP_DATAREC_ENABLED
    
#ifdef ORTHOGONAL_ENABLED
/*		static uint8_t delay_cnt = 0;
		
		delay_cnt++;
		if(delay_cnt > 32)
			delay_cnt = 0;
		if(DPLL_Trigger && delay_cnt == 0)
		{
			App_DataRec_Store_16bit((uint16_t)pi_i_d_paramout_orto_l1);
			App_DataRec_Store_16bit((uint16_t)pi_u_d_paramout_orto_l1);
			//App_DataRec_Store_16bit((uint16_t)pi_i_q_paramout_orto_l1);
			//App_DataRec_Store_16bit((uint16_t)pi_u_q_paramout_orto_l1);
			App_DataRec_Store_16bit((uint16_t)inv_cp_out_dq.d);
			App_DataRec_Store_16bit((uint16_t)inv_cp_out_dq.q);*/
		}
/*
  App_DataRec_Store_16bit((uint16_t)(vg_in.a));
  App_DataRec_Store_16bit((uint16_t)(vg_dqp_orto_l1.d));
  App_DataRec_Store_16bit((uint16_t)(vg_inv_orto_l1.a));
  App_DataRec_Store_16bit((uint16_t)(theta_orto_l1));
 */
   
//	static uint16_t test_data = 0;
//	App_DataRec_Store_16bit((uint16_t)(test_data));
//	test_data++;
#endif  
}

bool check_dpll(Dpll_Mode_t mode)
{
	//return(true);
	/*App_DataRec_Store_16bit((uint16_t)mode);
	App_DataRec_Store_16bit((uint16_t)dpll_lock_cnt_l1);
	App_DataRec_Store_16bit((uint16_t)dpll_lock_cnt_l2);
	App_DataRec_Store_16bit((uint16_t)dpll_lock_cnt_l3);*/
  switch(mode)
  {
		case APP_DPLL_OFF:
			return(true);
		break;
		case APP_DPLL_ON_3_PHASE:
			if((l2_period>MIN_DPLL_PERIOD) && (l2_period<MAX_DPLL_PERIOD))
			{
				if (dpll_lock_cnt_l2 < DPLL_PERIOD)
					dpll_lock_cnt_l2 += DPLL_ON_STEP;
			}
			else
			{    
				if (dpll_lock_cnt_l2 > 0)
					dpll_lock_cnt_l2 -= DPLL_OFF_STEP;
			}
			if(dpll_lock_cnt_l2 >= DPLL_PERIOD)
				dpll_lock_cnt_l2 = DPLL_PERIOD;
			if(dpll_lock_cnt_l2 <= 0)
			{
				dpll_lock_cnt_l2 = 0;
				break;
			}
			if((l3_period>MIN_DPLL_PERIOD) && (l3_period<MAX_DPLL_PERIOD))
			{
				if (dpll_lock_cnt_l3 < DPLL_PERIOD)
					dpll_lock_cnt_l3 += DPLL_ON_STEP;
			}
			else
			{    
				if (dpll_lock_cnt_l3 > 0)
					dpll_lock_cnt_l3 -= DPLL_OFF_STEP;
			}
			if(dpll_lock_cnt_l3 >= DPLL_PERIOD)
				dpll_lock_cnt_l3 = DPLL_PERIOD;
			if(dpll_lock_cnt_l3 <= 0)
			{
				dpll_lock_cnt_l3 = 0;
				break;
			}
		case APP_DPLL_ON_1_PHASE:
			if((l1_period>MIN_DPLL_PERIOD) && (l1_period<MAX_DPLL_PERIOD))
			{
				if (dpll_lock_cnt_l1 < DPLL_PERIOD)
				dpll_lock_cnt_l1 += DPLL_ON_STEP;
			}
			else
			{    
				if (dpll_lock_cnt_l1 > 0)
					dpll_lock_cnt_l1 -= DPLL_OFF_STEP;
			}
			if(dpll_lock_cnt_l1 >= DPLL_PERIOD)
			{ 
				dpll_lock_cnt_l1 = DPLL_PERIOD;
				return(true);
			}
			if(dpll_lock_cnt_l1 <= 0)
			{
				dpll_lock_cnt_l1 = 0;
				break;
			}
		break;
		default: break;
	}
	return(false);
}

void SM_Delayed_Jump(uint16_t val, SM_Main_t next_state)
{
    next_sm_state=next_state;      
    delay_counter=val;         
    sm_state=SM_DELAY;
} 

void system_error(System_Error_t err)
{
  sm_error_state=sm_state;
  sm_state=SM_ERROR;
  system_ERROR=err;
  App_LED_HB_Delay=100;
  id_curr=0;
  iq_curr=0;
  App_SM_System_Mode = APP_SM_SYSTEM_MODE_IDLE;
  //App_DPLL_Init(NULL);
  switch(err)
  {
    case ERROR_NO_DPLL_LOCK:
      App_Relay_Off(APP_RELAY_INV_PHASE);
      App_Relay_Off(APP_RELAY_INV_NEUTRAL);      
      break;
    case ERROR_INV_VOLTAGE:
      App_Relay_Off(APP_RELAY_INV_PHASE);
      App_Relay_Off(APP_RELAY_INV_NEUTRAL);      
      break;
    case ERROR_MID_VOLTAGE:
      App_Relay_Off(APP_RELAY_GRID_PHASE);
      App_Relay_Off(APP_RELAY_GRID_NEUTRAL);
      break;    
    case ERROR_GRID_VOLTAGE:
      App_Relay_Off(APP_RELAY_GRID_PHASE);
      App_Relay_Off(APP_RELAY_GRID_NEUTRAL);
      break;
  }          
}

System_Error_t check_for_errors(void)
{
  
  
  return ERROR_NONE;
}

bool check_voltage(V_Meas_t node)
{
  return true;
  switch(node)
  {
    case APP_V_INV_3:
      if((ADC_L2_U_Inv_Pk_H > U_Pk_Inv_HH) || (ADC_L2_U_Inv_Pk_H < U_Pk_Inv_HL) || (ADC_L2_U_Inv_Pk_L < -U_Pk_Inv_HH) || (ADC_L2_U_Inv_Pk_L > -U_Pk_Inv_HL))
        return false;
      if((ADC_L3_U_Inv_Pk_H>U_Pk_Inv_HH) || (ADC_L3_U_Inv_Pk_H<U_Pk_Inv_HL)
      || (ADC_L3_U_Inv_Pk_L<-U_Pk_Inv_HH) || (ADC_L3_U_Inv_Pk_L>-U_Pk_Inv_HL))
        return false;
    case APP_V_INV_1:
      if((ADC_L1_U_Inv_Pk_H>U_Pk_Inv_HH) || (ADC_L1_U_Inv_Pk_H<U_Pk_Inv_HL)
      || (ADC_L1_U_Inv_Pk_L<-U_Pk_Inv_HH) || (ADC_L1_U_Inv_Pk_L>-U_Pk_Inv_HL))
        return false;
      break;
    case APP_V_MID_3:
      if((ADC_L2_U_Mid_Pk_H>U_Pk_Mid_HH) || (ADC_L2_U_Mid_Pk_H<U_Pk_Mid_HL)
      || (ADC_L2_U_Mid_Pk_L<-U_Pk_Mid_HH) || (ADC_L2_U_Mid_Pk_L>-U_Pk_Mid_HL))
        return false;
      if((ADC_L3_U_Mid_Pk_H>U_Pk_Mid_HH) || (ADC_L3_U_Mid_Pk_H<U_Pk_Mid_HL)
      || (ADC_L3_U_Mid_Pk_L<-U_Pk_Mid_HH) || (ADC_L3_U_Mid_Pk_L>-U_Pk_Mid_HL))
        return false;
    case APP_V_MID_1:
      if((ADC_L1_U_Mid_Pk_H>U_Pk_Mid_HH) || (ADC_L1_U_Mid_Pk_H<U_Pk_Mid_HL)
      || (ADC_L1_U_Mid_Pk_L<-U_Pk_Mid_HH) || (ADC_L1_U_Mid_Pk_L>-U_Pk_Mid_HL))
        return false;
      break;
    case APP_V_GRID_3:
      if((ADC_L2_U_Grid_Pk_H>U_Pk_Grid_HH) || (ADC_L2_U_Grid_Pk_H<U_Pk_Grid_HL)
      || (ADC_L2_U_Grid_Pk_L<-U_Pk_Grid_HH) || (ADC_L2_U_Grid_Pk_L>-U_Pk_Grid_HL))
        return false;
      if((ADC_L3_U_Grid_Pk_H>U_Pk_Grid_HH) || (ADC_L3_U_Grid_Pk_H<U_Pk_Grid_HL)
      || (ADC_L3_U_Grid_Pk_L<-U_Pk_Grid_HH) || (ADC_L3_U_Grid_Pk_L>-U_Pk_Grid_HL))
        return false;
    case APP_V_GRID_1:
      if((ADC_L1_U_Grid_Pk_H>U_Pk_Grid_HH) || (ADC_L1_U_Grid_Pk_H<U_Pk_Grid_HL)
      || (ADC_L1_U_Grid_Pk_L<-U_Pk_Grid_HH) || (ADC_L1_U_Grid_Pk_L>-U_Pk_Grid_HL))
        return false;
      break;  
  }
  return true;
}

void delay(uint16_t val)
{
  
}

void App_Main_SM_Init(void)
{
  sm_state=SM_PRE_START;
  system_ERROR=ERROR_NONE;
  App_LED_HB_Delay=500;
  timeout_off();
  App_Relay_Off(APP_RELAY_GRID_PHASE);
  App_Relay_Off(APP_RELAY_GRID_NEUTRAL);
  id_curr=id_set;
  iq_curr=iq_set;
  id_step=0;
  iq_step=0;
  
  U_Pk_Inv_HH = (int16_t)((U_Pk_HH * BSP_SETTINGS_ADC_U_INV_SCALING_INV)>>13);
  U_Pk_Inv_HL = (int16_t)((U_Pk_HL * BSP_SETTINGS_ADC_U_INV_SCALING_INV)>>13);
  /*
  U_Pk_Mid_HH = (int16_t)((BSP_SETTINGS_ADC_U_MID_SCALING_INV*U_Pk_HH)>>13);
  U_Pk_Mid_HL = (int16_t)((BSP_SETTINGS_ADC_U_MID_SCALING_INV*U_Pk_HL)>>13);
  U_Pk_Grid_HH = (int16_t)((BSP_SETTINGS_ADC_U_GRID_SCALING_INV*U_Pk_HH)>>13);
  U_Pk_Grid_HL = (int16_t)((BSP_SETTINGS_ADC_U_GRID_SCALING_INV*U_Pk_HL)>>13);
  */
  //U_Pk_Inv_HH = 20000;
  //U_Pk_Inv_HL = 4000;
  U_Pk_Mid_HH = (int16_t)((BSP_SETTINGS_ADC_U_MID_SCALING_INV*U_Pk_HH)>>13);
  U_Pk_Mid_HL = (int16_t)((BSP_SETTINGS_ADC_U_MID_SCALING_INV*U_Pk_HL)>>13);
  U_Pk_Grid_HH = (int16_t)((BSP_SETTINGS_ADC_U_GRID_SCALING_INV*U_Pk_HH)>>13);
  U_Pk_Grid_HL = (int16_t)((BSP_SETTINGS_ADC_U_GRID_SCALING_INV*U_Pk_HL)>>13);
	
	//App_PWM_All_IGBTs_Off(true);
}

void timeout_on(void)
{
  timeout_counter=SM_TIMEOUT_VAL;
  timeout_on_v = true;
}

void timeout_off(void)
{
  timeout_on_v = false;
}

bool id_set_change(int16_t id_set)
{
  if(id_set!=id_curr)
  {
    if(id_set>id_curr)
      id_step=STEP_VAL;
    else
      id_step=-STEP_VAL;
    return(true);
  }
  return(false);
}

void id_ramp(void)
{
  id_curr+=id_step;
  if(id_step>0 && id_curr>=id_set)
    id_curr=id_set;
  else
    if(id_step<0 && id_curr<=id_set)
      id_curr=id_set;
}

bool iq_set_change(int16_t id_set)
{
  if(iq_set!=id_curr)
  {
    if(iq_set>id_curr)
      iq_step=STEP_VAL;
    else
      iq_step=-STEP_VAL;
    return(true);
  }
  return(false);
}

void iq_ramp(void)
{
  iq_curr+=iq_step;
  if(iq_step>0 && iq_curr>=iq_set)
    iq_curr=iq_set;
  else
    if(iq_step<0 && iq_curr<=iq_set)
      iq_curr=iq_set;
}

void main_state_machine(void)
{
  if((App_SM_System_Mode != APP_SM_SYSTEM_MODE_TEST)&&(App_SM_System_Mode != APP_SM_SYSTEM_MODE_IDLE))
  {
		if(timeout_on_v)
		{
			if(timeout_counter>0)
				timeout_counter--;
			else
				system_error(ERROR_TIMEOUT);
		}
		switch(sm_state)
		{
			case SM_PRE_START:
				if (ADC_Ready)
					sm_state=SM_START;
				break;
			case SM_START:
				App_DPLL_Init(NULL);
				PID_I_Init();
				PID_U_Init();
				switch (App_SM_System_Mode)
				{
					case APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE:		//1 phase grid connected mode
						dpll_mode=APP_DPLL_ON_1_PHASE;
						control_mode=APP_CONTROL_OFF;
						App_PWM_All_IGBTs_Off(true);	//switch all IGBTs
					break;
					case APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES:		//3 phases grid connected mode
						dpll_mode=APP_DPLL_ON_3_PHASE;
						control_mode=APP_CONTROL_OFF;
						App_PWM_All_IGBTs_Off(true);	//switch all IGBTs
					break;  
					case APP_SM_SYSTEM_MODE_IDLE:
						dpll_mode=APP_DPLL_OFF;
						control_mode=APP_CONTROL_OFF;
						App_PWM_All_IGBTs_Off(true);	//switch all IGBTs
					break;  
					case APP_SM_SYSTEM_MODE_STANDALONE_1_PHASE: 
						dpll_mode=APP_DPLL_OFF;
						control_mode=APP_VCB_ON;
					break;
					case APP_SM_SYSTEM_MODE_STANDALONE_3_PHASES:
						dpll_mode=APP_DPLL_OFF;
						control_mode=APP_VCB_ON;
						//control_mode=APP_CONTROL_OFF;
					break;
					case APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE_NO_BAT:		//1 phase grid connected mode, no BAT, IGBTs switched off
						//pll_mode=APP_DPLL_OFF;
						dpll_mode=APP_DPLL_ON_1_PHASE;
						control_mode=APP_CONTROL_OFF;
						App_PWM_All_IGBTs_Off(true);	//switch all IGBTs
					break;
					case APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES_NO_BAT:	//3 phases grid connected mode, no BAT, IGBTs switched off
						dpll_mode=APP_DPLL_ON_3_PHASE;
						control_mode=APP_CONTROL_OFF;
						App_PWM_All_IGBTs_Off(true);	//switch all IGBTs
						break;
					default: break;
				}
				//dpll_mode=APP_DPLL_ON_3_PHASE;
				//control_mode=APP_VCB_ON;
				//dpll_locked=check_dpll();
				//dpll_mode=APP_DPLL_ON_3_PHASE;
				//control_mode=APP_CCB_ON;
				App_LED_HB_Delay=100;
				App_Relay_On(APP_RELAY_GRID_NEUTRAL);
				App_Relay_On(APP_RELAY_INV_NEUTRAL);
				SM_Delayed_Jump(500,SM_IDLE);
				break;
			case SM_IDLE:
	/*      if(!check_voltage(APP_V_GRID_3))
					system_error(ERROR_GRID_VOLTAGE);
				else*/
				{
					// close GRID Relays

					App_Relay_On(APP_RELAY_GRID_PHASE);
					SM_Delayed_Jump(500,SM_GRID_RLY_CLOSE);
				}
				break;
			case SM_GRID_RLY_CLOSE:

				//App_Relay_On(APP_RELAY_INV_PHASE);
			/*  if(!check_voltage(APP_V_GRID_3))
				{
					system_error(ERROR_GRID_VOLTAGE);
					break;
				}*/
	/*     if(!check_voltage(APP_V_MID_3))
			 { 
				 system_error(ERROR_MID_VOLTAGE);
					break;
				}*/
				//App_Relay_On(APP_RELAY_INV_NEUTRAL);
				//App_DPLL_Init(NULL);
				timeout_on();
				//system_error(ERROR_NO_DPLL_LOCK);
				//sm_state= SM_DPLL_INIT; 
				//SM_Delayed_Jump(1000,SM_DPLL_INIT);
				sm_state=SM_DPLL_INIT;
				break;
			case SM_DPLL_INIT:   
				if(check_dpll(dpll_mode))
				{ 
					//control_mode=APP_CCB_ON;  //switch to current control
					timeout_off();		
					switch (App_SM_System_Mode)
					{
						case APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE:		//1 phase grid connected mode
							control_mode=APP_VCB_ORTO1_ON;
							App_PWM_All_IGBTs_On(false);	//switch CH1 IGBTs on
						break;
						case APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES:		//3 phases grid connected mode
							control_mode=APP_VCB_ORTO3_ON;
							App_PWM_All_IGBTs_On(true);	//switch all channels IGBTs on
						break;  
						case APP_SM_SYSTEM_MODE_IDLE:

						break;  
						case APP_SM_SYSTEM_MODE_STANDALONE_1_PHASE: 
							App_PWM_All_IGBTs_On(false);
						break;
						case APP_SM_SYSTEM_MODE_STANDALONE_3_PHASES:
							App_PWM_All_IGBTs_On(true);
						break;
						case APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE_NO_BAT:		//1 phase grid connected mode, no BAT, IGBTs switched off
							control_mode=APP_VCB_ORTO1_ON;
							App_Relay_On(APP_RELAY_INV_PHASE);
						break;
						case APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES_NO_BAT:	//3 phases grid connected mode, no BAT, IGBTs switched off
							control_mode=APP_VCB_ORTO3_ON;
							App_Relay_On(APP_RELAY_INV_PHASE);
							break;
						default: break;
					}
					SM_Delayed_Jump(10000,SM_DPLL_LOCKED); 
				}
				break;
			case SM_DPLL_LOCKED:
			switch (App_SM_System_Mode)
				{
					case APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE:		//1 phase grid connected mode
						control_mode=APP_CCB_ORTO1_ON;
						App_Relay_On(APP_RELAY_INV_PHASE);
					break;
					case APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES:		//3 phases grid connected mode
						control_mode=APP_CCB_ORTO3_ON;
						App_Relay_On(APP_RELAY_INV_PHASE);
					break;  
					case APP_SM_SYSTEM_MODE_IDLE:

					break;  
					case APP_SM_SYSTEM_MODE_STANDALONE_1_PHASE: 
						App_Relay_On(APP_RELAY_INV_PHASE);
					break;
					case APP_SM_SYSTEM_MODE_STANDALONE_3_PHASES:
						App_Relay_On(APP_RELAY_INV_PHASE);
					break;
					case APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE_NO_BAT:		//1 phase grid connected mode, no BAT, IGBTs switched off
						App_PWM_All_IGBTs_On(false);	//switch CH1 IGBTs
						control_mode=APP_CCB_ORTO1_ON;
					break;
					case APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES_NO_BAT:	//3 phases grid connected mode, no BAT, IGBTs switched off
						control_mode=APP_CCB_ORTO3_ON;
						App_PWM_All_IGBTs_On(true);	//switch all channels IGBTs on
						break;
					default: break;
				}
				//App_Relay_On(APP_RELAY_INV_PHASE);
				DPLL_Trigger=true;
				SM_Delayed_Jump(200,SM_PRE_INV_RLY);
				break;
			case SM_PRE_INV_RLY: 
				//PID_I_Init();
	/*			switch(control_mode)
				{
					case APP_VCB_ORTO3_ON:
						//BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_2, 3);
						//BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_3, 3);
						//BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_1, 3);
						App_PWM_All_IGBTs_On(true);
						control_mode=APP_CCB_ORTO3_ON;
						break;
					case APP_VCB_ORTO1_ON:
						//BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_1, 3);
						App_PWM_All_IGBTs_On(false);
						control_mode=APP_CCB_ORTO1_ON;
						break;
				}*/
	 /*     switch(control_mode)
				{
					case APP_VCB_ORTO3_ON:
						control_mode=APP_CCB_ORTO3_ON;
						break;
					case APP_VCB_ORTO1_ON:
						control_mode=APP_CCB_ORTO1_ON;
						break;
				}*/
				SM_Delayed_Jump(25,SM_INV_RLY_CLOSE);
				break;  
			case SM_INV_RLY_CLOSE:

				if(!check_dpll(dpll_mode)) // dpll out of sync - disconnect inverter
				{  
					system_error(ERROR_NO_DPLL_LOCK);
					break;
				}
				if(!check_voltage(APP_V_INV_3))  
				{
					system_error(ERROR_INV_VOLTAGE);
					break;
				}
	/*      if(!check_voltage(APP_V_GRID_3))  // GRID failure !!!
				{     
					//system_error(ERROR_GRID_VOLTAGE);
					dpll_mode=APP_DPLL_OFF;   // 
					control_mode=APP_VCB_ON;  //switch back to standalone
					sm_state=SM_ISLAND_MODE;
					break;
				}*/
				if(id_set_change(id_set))
					id_ramp();
				if(iq_set_change(iq_set))
					iq_ramp();
				break;
			case SM_ISLAND_MODE:
				if(!check_voltage(APP_V_INV_3))  
				{
					system_error(ERROR_INV_VOLTAGE);
					break;
				}
				if(check_voltage(APP_V_GRID_3))  // GRID is back !!!
				{
					//dpll_mode=APP_DPLL_ON_GRID_3_PHASE; // synchronize to the grid low sample rate signal
					//App_DPLL_Init(NULL);
					timeout_on();
					sm_state=SM_ANTY_ISLANDING;   
					//SM_Delayed_Jump(500,SM_ANTY_ISLANDING);
					break;
				}
				break;
			case SM_ANTY_ISLANDING:
				if(check_dpll(dpll_mode))
				{        
					dpll_mode=APP_DPLL_ON_3_PHASE; // switch back to mid signal synchro
					control_mode=APP_CCB_ON;  //switch to current control
					timeout_off();       
				}
				else
					break;
				if(!check_voltage(APP_V_GRID_3))
					system_error(ERROR_GRID_VOLTAGE);
				else
				{
					// close GRID Relays
					App_Relay_On(APP_RELAY_GRID_PHASE);
					SM_Delayed_Jump(500,SM_INV_RLY_CLOSE);
				}
				break;
			case SM_DELAY:
				//check_dpll(dpll_mode);
				if(delay_counter>0)
					delay_counter--;
				else
					sm_state=next_sm_state;
				break;
			case SM_TIMEOUT:
				system_error(ERROR_TIMEOUT);
				break;
			case SM_ERROR:
				sm_state=SM_WAIT_FOR_REINIT;
				break;
			case SM_WAIT_FOR_REINIT:
				// wait    
				break;
		}
	}
	else
		sm_state=SM_PRE_START;
}


