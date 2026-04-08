#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=null
DEBUGGABLE_SUFFIX=null
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Inresol_Inverter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=null
DEBUGGABLE_SUFFIX=null
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Inresol_Inverter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../app_src/App_ADC.c ../app_src/App_DDS.c ../app_src/App_Debug.c ../app_src/App_PWM.c ../app_src/App_SysTick.c ../app_src/App_Utils.c ../app_src/App_Relay.c ../app_src/App_TempSens.c ../app_src/App_OCP.c ../app_src/App_DataRec.c ../app_src/App_DPLL.c ../app_src/App_SM.c ../app_src/App_MODBUS.c ../app_src/App_NVMemory.c ../bsp_src/BSP_ADC.c ../bsp_src/BSP_IO.c ../bsp_src/BSP_PWM.c ../bsp_src/BSP_System.c ../bsp_src/BSP_Timer.c ../bsp_src/BSP_UART.c ../bsp_src/BSP_Relay.c ../lib_src/EEPROM_Emulation/DEE_Emulation_16-bit.c ../lib_src/EEPROM_Emulation/FlashOperations.s ../lib_src/FreeMODBUS/modbus/ascii/mbascii.c ../lib_src/FreeMODBUS/modbus/functions/mbfunccoils.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncdiag.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncdisc.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncholding.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncinput.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncother.c ../lib_src/FreeMODBUS/modbus/functions/mbutils.c ../lib_src/FreeMODBUS/modbus/rtu/mbcrc.c ../lib_src/FreeMODBUS/modbus/rtu/mbrtu.c ../lib_src/FreeMODBUS/modbus/tcp/mbtcp.c ../lib_src/FreeMODBUS/modbus/mb.c ../lib_src/FreeMODBUS/port/portevent.c ../lib_src/FreeMODBUS/port/portserial.c ../lib_src/FreeMODBUS/port/porttimer.c ../lib_src/pid.s ../lib_src/ring_buffer.c ../lib_src/mc_clarke_dspic.s ../lib_src/mc_filter.s ../lib_src/mc_invclarke_dspic.s ../lib_src/mc_invpark_dspic.s ../lib_src/mc_park_dspic.s ../lib_src/mc_piupdate_dspic.s ../lib_src/mc_sinecos_ram_dspic.s ../lib_src/mc_sinetable_flash_dspic.s ../lib_src/mc_sinetable_ram_dspic.s ../lib_src/mc_svgen_dspic.s ../lib_src/crc.c ../main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1820848503/App_ADC.o ${OBJECTDIR}/_ext/1820848503/App_DDS.o ${OBJECTDIR}/_ext/1820848503/App_Debug.o ${OBJECTDIR}/_ext/1820848503/App_PWM.o ${OBJECTDIR}/_ext/1820848503/App_SysTick.o ${OBJECTDIR}/_ext/1820848503/App_Utils.o ${OBJECTDIR}/_ext/1820848503/App_Relay.o ${OBJECTDIR}/_ext/1820848503/App_TempSens.o ${OBJECTDIR}/_ext/1820848503/App_OCP.o ${OBJECTDIR}/_ext/1820848503/App_DataRec.o ${OBJECTDIR}/_ext/1820848503/App_DPLL.o ${OBJECTDIR}/_ext/1820848503/App_SM.o ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o ${OBJECTDIR}/_ext/1500727659/BSP_IO.o ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o ${OBJECTDIR}/_ext/1500727659/BSP_System.o ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o ${OBJECTDIR}/_ext/1500727659/BSP_UART.o ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o ${OBJECTDIR}/_ext/882496299/FlashOperations.o ${OBJECTDIR}/_ext/292539343/mbascii.o ${OBJECTDIR}/_ext/141222789/mbfunccoils.o ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o ${OBJECTDIR}/_ext/141222789/mbfuncholding.o ${OBJECTDIR}/_ext/141222789/mbfuncinput.o ${OBJECTDIR}/_ext/141222789/mbfuncother.o ${OBJECTDIR}/_ext/141222789/mbutils.o ${OBJECTDIR}/_ext/1675687763/mbcrc.o ${OBJECTDIR}/_ext/1675687763/mbrtu.o ${OBJECTDIR}/_ext/1675689153/mbtcp.o ${OBJECTDIR}/_ext/523702545/mb.o ${OBJECTDIR}/_ext/478666894/portevent.o ${OBJECTDIR}/_ext/478666894/portserial.o ${OBJECTDIR}/_ext/478666894/porttimer.o ${OBJECTDIR}/_ext/1514846245/pid.o ${OBJECTDIR}/_ext/1514846245/ring_buffer.o ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_filter.o ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o ${OBJECTDIR}/_ext/1514846245/crc.o ${OBJECTDIR}/_ext/1472/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1820848503/App_ADC.o.d ${OBJECTDIR}/_ext/1820848503/App_DDS.o.d ${OBJECTDIR}/_ext/1820848503/App_Debug.o.d ${OBJECTDIR}/_ext/1820848503/App_PWM.o.d ${OBJECTDIR}/_ext/1820848503/App_SysTick.o.d ${OBJECTDIR}/_ext/1820848503/App_Utils.o.d ${OBJECTDIR}/_ext/1820848503/App_Relay.o.d ${OBJECTDIR}/_ext/1820848503/App_TempSens.o.d ${OBJECTDIR}/_ext/1820848503/App_OCP.o.d ${OBJECTDIR}/_ext/1820848503/App_DataRec.o.d ${OBJECTDIR}/_ext/1820848503/App_DPLL.o.d ${OBJECTDIR}/_ext/1820848503/App_SM.o.d ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o.d ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o.d ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o.d ${OBJECTDIR}/_ext/1500727659/BSP_IO.o.d ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o.d ${OBJECTDIR}/_ext/1500727659/BSP_System.o.d ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o.d ${OBJECTDIR}/_ext/1500727659/BSP_UART.o.d ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o.d ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o.d ${OBJECTDIR}/_ext/882496299/FlashOperations.o.d ${OBJECTDIR}/_ext/292539343/mbascii.o.d ${OBJECTDIR}/_ext/141222789/mbfunccoils.o.d ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o.d ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o.d ${OBJECTDIR}/_ext/141222789/mbfuncholding.o.d ${OBJECTDIR}/_ext/141222789/mbfuncinput.o.d ${OBJECTDIR}/_ext/141222789/mbfuncother.o.d ${OBJECTDIR}/_ext/141222789/mbutils.o.d ${OBJECTDIR}/_ext/1675687763/mbcrc.o.d ${OBJECTDIR}/_ext/1675687763/mbrtu.o.d ${OBJECTDIR}/_ext/1675689153/mbtcp.o.d ${OBJECTDIR}/_ext/523702545/mb.o.d ${OBJECTDIR}/_ext/478666894/portevent.o.d ${OBJECTDIR}/_ext/478666894/portserial.o.d ${OBJECTDIR}/_ext/478666894/porttimer.o.d ${OBJECTDIR}/_ext/1514846245/pid.o.d ${OBJECTDIR}/_ext/1514846245/ring_buffer.o.d ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o.d ${OBJECTDIR}/_ext/1514846245/mc_filter.o.d ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o.d ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o.d ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o.d ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o.d ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o.d ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o.d ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o.d ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o.d ${OBJECTDIR}/_ext/1514846245/crc.o.d ${OBJECTDIR}/_ext/1472/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1820848503/App_ADC.o ${OBJECTDIR}/_ext/1820848503/App_DDS.o ${OBJECTDIR}/_ext/1820848503/App_Debug.o ${OBJECTDIR}/_ext/1820848503/App_PWM.o ${OBJECTDIR}/_ext/1820848503/App_SysTick.o ${OBJECTDIR}/_ext/1820848503/App_Utils.o ${OBJECTDIR}/_ext/1820848503/App_Relay.o ${OBJECTDIR}/_ext/1820848503/App_TempSens.o ${OBJECTDIR}/_ext/1820848503/App_OCP.o ${OBJECTDIR}/_ext/1820848503/App_DataRec.o ${OBJECTDIR}/_ext/1820848503/App_DPLL.o ${OBJECTDIR}/_ext/1820848503/App_SM.o ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o ${OBJECTDIR}/_ext/1500727659/BSP_IO.o ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o ${OBJECTDIR}/_ext/1500727659/BSP_System.o ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o ${OBJECTDIR}/_ext/1500727659/BSP_UART.o ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o ${OBJECTDIR}/_ext/882496299/FlashOperations.o ${OBJECTDIR}/_ext/292539343/mbascii.o ${OBJECTDIR}/_ext/141222789/mbfunccoils.o ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o ${OBJECTDIR}/_ext/141222789/mbfuncholding.o ${OBJECTDIR}/_ext/141222789/mbfuncinput.o ${OBJECTDIR}/_ext/141222789/mbfuncother.o ${OBJECTDIR}/_ext/141222789/mbutils.o ${OBJECTDIR}/_ext/1675687763/mbcrc.o ${OBJECTDIR}/_ext/1675687763/mbrtu.o ${OBJECTDIR}/_ext/1675689153/mbtcp.o ${OBJECTDIR}/_ext/523702545/mb.o ${OBJECTDIR}/_ext/478666894/portevent.o ${OBJECTDIR}/_ext/478666894/portserial.o ${OBJECTDIR}/_ext/478666894/porttimer.o ${OBJECTDIR}/_ext/1514846245/pid.o ${OBJECTDIR}/_ext/1514846245/ring_buffer.o ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_filter.o ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o ${OBJECTDIR}/_ext/1514846245/crc.o ${OBJECTDIR}/_ext/1472/main.o

# Source Files
SOURCEFILES=../app_src/App_ADC.c ../app_src/App_DDS.c ../app_src/App_Debug.c ../app_src/App_PWM.c ../app_src/App_SysTick.c ../app_src/App_Utils.c ../app_src/App_Relay.c ../app_src/App_TempSens.c ../app_src/App_OCP.c ../app_src/App_DataRec.c ../app_src/App_DPLL.c ../app_src/App_SM.c ../app_src/App_MODBUS.c ../app_src/App_NVMemory.c ../bsp_src/BSP_ADC.c ../bsp_src/BSP_IO.c ../bsp_src/BSP_PWM.c ../bsp_src/BSP_System.c ../bsp_src/BSP_Timer.c ../bsp_src/BSP_UART.c ../bsp_src/BSP_Relay.c ../lib_src/EEPROM_Emulation/DEE_Emulation_16-bit.c ../lib_src/EEPROM_Emulation/FlashOperations.s ../lib_src/FreeMODBUS/modbus/ascii/mbascii.c ../lib_src/FreeMODBUS/modbus/functions/mbfunccoils.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncdiag.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncdisc.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncholding.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncinput.c ../lib_src/FreeMODBUS/modbus/functions/mbfuncother.c ../lib_src/FreeMODBUS/modbus/functions/mbutils.c ../lib_src/FreeMODBUS/modbus/rtu/mbcrc.c ../lib_src/FreeMODBUS/modbus/rtu/mbrtu.c ../lib_src/FreeMODBUS/modbus/tcp/mbtcp.c ../lib_src/FreeMODBUS/modbus/mb.c ../lib_src/FreeMODBUS/port/portevent.c ../lib_src/FreeMODBUS/port/portserial.c ../lib_src/FreeMODBUS/port/porttimer.c ../lib_src/pid.s ../lib_src/ring_buffer.c ../lib_src/mc_clarke_dspic.s ../lib_src/mc_filter.s ../lib_src/mc_invclarke_dspic.s ../lib_src/mc_invpark_dspic.s ../lib_src/mc_park_dspic.s ../lib_src/mc_piupdate_dspic.s ../lib_src/mc_sinecos_ram_dspic.s ../lib_src/mc_sinetable_flash_dspic.s ../lib_src/mc_sinetable_ram_dspic.s ../lib_src/mc_svgen_dspic.s ../lib_src/crc.c ../main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Inresol_Inverter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP128GS706
MP_LINKER_FILE_OPTION=,--script=p33EP128GS706.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1820848503/App_ADC.o: ../app_src/App_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_ADC.c  -o ${OBJECTDIR}/_ext/1820848503/App_ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_DDS.o: ../app_src/App_DDS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DDS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DDS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_DDS.c  -o ${OBJECTDIR}/_ext/1820848503/App_DDS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_DDS.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_DDS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_Debug.o: ../app_src/App_Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_Debug.c  -o ${OBJECTDIR}/_ext/1820848503/App_Debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_Debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_Debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_PWM.o: ../app_src/App_PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_PWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_PWM.c  -o ${OBJECTDIR}/_ext/1820848503/App_PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_PWM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_SysTick.o: ../app_src/App_SysTick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_SysTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_SysTick.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_SysTick.c  -o ${OBJECTDIR}/_ext/1820848503/App_SysTick.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_SysTick.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_SysTick.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_Utils.o: ../app_src/App_Utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_Utils.c  -o ${OBJECTDIR}/_ext/1820848503/App_Utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_Utils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_Utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_Relay.o: ../app_src/App_Relay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Relay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Relay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_Relay.c  -o ${OBJECTDIR}/_ext/1820848503/App_Relay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_Relay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_Relay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_TempSens.o: ../app_src/App_TempSens.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_TempSens.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_TempSens.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_TempSens.c  -o ${OBJECTDIR}/_ext/1820848503/App_TempSens.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_TempSens.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_TempSens.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_OCP.o: ../app_src/App_OCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_OCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_OCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_OCP.c  -o ${OBJECTDIR}/_ext/1820848503/App_OCP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_OCP.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_OCP.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_DataRec.o: ../app_src/App_DataRec.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DataRec.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DataRec.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_DataRec.c  -o ${OBJECTDIR}/_ext/1820848503/App_DataRec.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_DataRec.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_DataRec.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_DPLL.o: ../app_src/App_DPLL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DPLL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DPLL.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_DPLL.c  -o ${OBJECTDIR}/_ext/1820848503/App_DPLL.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_DPLL.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_DPLL.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_SM.o: ../app_src/App_SM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_SM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_SM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_SM.c  -o ${OBJECTDIR}/_ext/1820848503/App_SM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_SM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_SM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_MODBUS.o: ../app_src/App_MODBUS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_MODBUS.c  -o ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_MODBUS.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_MODBUS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_NVMemory.o: ../app_src/App_NVMemory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_NVMemory.c  -o ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_NVMemory.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_NVMemory.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_ADC.o: ../bsp_src/BSP_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_ADC.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_IO.o: ../bsp_src/BSP_IO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_IO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_IO.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_IO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_IO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_PWM.o: ../bsp_src/BSP_PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_PWM.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_PWM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_System.o: ../bsp_src/BSP_System.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_System.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_System.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_System.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_System.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_System.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_Timer.o: ../bsp_src/BSP_Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_Timer.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_Timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_Timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_UART.o: ../bsp_src/BSP_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_UART.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_UART.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_UART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_Relay.o: ../bsp_src/BSP_Relay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_Relay.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_Relay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_Relay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o: ../lib_src/EEPROM_Emulation/DEE_Emulation_16-bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/882496299" 
	@${RM} ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o.d 
	@${RM} ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/EEPROM_Emulation/DEE_Emulation_16-bit.c  -o ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/292539343/mbascii.o: ../lib_src/FreeMODBUS/modbus/ascii/mbascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/292539343" 
	@${RM} ${OBJECTDIR}/_ext/292539343/mbascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/292539343/mbascii.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/ascii/mbascii.c  -o ${OBJECTDIR}/_ext/292539343/mbascii.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/292539343/mbascii.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/292539343/mbascii.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfunccoils.o: ../lib_src/FreeMODBUS/modbus/functions/mbfunccoils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfunccoils.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfunccoils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfunccoils.c  -o ${OBJECTDIR}/_ext/141222789/mbfunccoils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfunccoils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfunccoils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncdiag.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncdiag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncdiag.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncdiag.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncdiag.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncdisc.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncdisc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncdisc.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncdisc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncdisc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncholding.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncholding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncholding.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncholding.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncholding.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncholding.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncholding.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncholding.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncinput.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncinput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncinput.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncinput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncinput.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncinput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncinput.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncinput.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncother.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncother.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncother.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncother.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncother.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncother.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncother.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncother.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbutils.o: ../lib_src/FreeMODBUS/modbus/functions/mbutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbutils.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbutils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbutils.c  -o ${OBJECTDIR}/_ext/141222789/mbutils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbutils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbutils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1675687763/mbcrc.o: ../lib_src/FreeMODBUS/modbus/rtu/mbcrc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1675687763" 
	@${RM} ${OBJECTDIR}/_ext/1675687763/mbcrc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1675687763/mbcrc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/rtu/mbcrc.c  -o ${OBJECTDIR}/_ext/1675687763/mbcrc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1675687763/mbcrc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1675687763/mbcrc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1675687763/mbrtu.o: ../lib_src/FreeMODBUS/modbus/rtu/mbrtu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1675687763" 
	@${RM} ${OBJECTDIR}/_ext/1675687763/mbrtu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1675687763/mbrtu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/rtu/mbrtu.c  -o ${OBJECTDIR}/_ext/1675687763/mbrtu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1675687763/mbrtu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1675687763/mbrtu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1675689153/mbtcp.o: ../lib_src/FreeMODBUS/modbus/tcp/mbtcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1675689153" 
	@${RM} ${OBJECTDIR}/_ext/1675689153/mbtcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1675689153/mbtcp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/tcp/mbtcp.c  -o ${OBJECTDIR}/_ext/1675689153/mbtcp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1675689153/mbtcp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1675689153/mbtcp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/523702545/mb.o: ../lib_src/FreeMODBUS/modbus/mb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/523702545" 
	@${RM} ${OBJECTDIR}/_ext/523702545/mb.o.d 
	@${RM} ${OBJECTDIR}/_ext/523702545/mb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/mb.c  -o ${OBJECTDIR}/_ext/523702545/mb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/523702545/mb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/523702545/mb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/478666894/portevent.o: ../lib_src/FreeMODBUS/port/portevent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/478666894" 
	@${RM} ${OBJECTDIR}/_ext/478666894/portevent.o.d 
	@${RM} ${OBJECTDIR}/_ext/478666894/portevent.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/port/portevent.c  -o ${OBJECTDIR}/_ext/478666894/portevent.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/478666894/portevent.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478666894/portevent.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/478666894/portserial.o: ../lib_src/FreeMODBUS/port/portserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/478666894" 
	@${RM} ${OBJECTDIR}/_ext/478666894/portserial.o.d 
	@${RM} ${OBJECTDIR}/_ext/478666894/portserial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/port/portserial.c  -o ${OBJECTDIR}/_ext/478666894/portserial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/478666894/portserial.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478666894/portserial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/478666894/porttimer.o: ../lib_src/FreeMODBUS/port/porttimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/478666894" 
	@${RM} ${OBJECTDIR}/_ext/478666894/porttimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/478666894/porttimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/port/porttimer.c  -o ${OBJECTDIR}/_ext/478666894/porttimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/478666894/porttimer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478666894/porttimer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1514846245/ring_buffer.o: ../lib_src/ring_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/ring_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/ring_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/ring_buffer.c  -o ${OBJECTDIR}/_ext/1514846245/ring_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1514846245/ring_buffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/ring_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1514846245/crc.o: ../lib_src/crc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/crc.c  -o ${OBJECTDIR}/_ext/1514846245/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1514846245/crc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/crc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1820848503/App_ADC.o: ../app_src/App_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_ADC.c  -o ${OBJECTDIR}/_ext/1820848503/App_ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_ADC.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_DDS.o: ../app_src/App_DDS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DDS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DDS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_DDS.c  -o ${OBJECTDIR}/_ext/1820848503/App_DDS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_DDS.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_DDS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_Debug.o: ../app_src/App_Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_Debug.c  -o ${OBJECTDIR}/_ext/1820848503/App_Debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_Debug.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_Debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_PWM.o: ../app_src/App_PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_PWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_PWM.c  -o ${OBJECTDIR}/_ext/1820848503/App_PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_PWM.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_SysTick.o: ../app_src/App_SysTick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_SysTick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_SysTick.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_SysTick.c  -o ${OBJECTDIR}/_ext/1820848503/App_SysTick.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_SysTick.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_SysTick.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_Utils.o: ../app_src/App_Utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_Utils.c  -o ${OBJECTDIR}/_ext/1820848503/App_Utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_Utils.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_Utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_Relay.o: ../app_src/App_Relay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Relay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_Relay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_Relay.c  -o ${OBJECTDIR}/_ext/1820848503/App_Relay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_Relay.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_Relay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_TempSens.o: ../app_src/App_TempSens.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_TempSens.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_TempSens.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_TempSens.c  -o ${OBJECTDIR}/_ext/1820848503/App_TempSens.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_TempSens.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_TempSens.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_OCP.o: ../app_src/App_OCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_OCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_OCP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_OCP.c  -o ${OBJECTDIR}/_ext/1820848503/App_OCP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_OCP.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_OCP.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_DataRec.o: ../app_src/App_DataRec.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DataRec.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DataRec.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_DataRec.c  -o ${OBJECTDIR}/_ext/1820848503/App_DataRec.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_DataRec.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_DataRec.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_DPLL.o: ../app_src/App_DPLL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DPLL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_DPLL.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_DPLL.c  -o ${OBJECTDIR}/_ext/1820848503/App_DPLL.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_DPLL.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_DPLL.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_SM.o: ../app_src/App_SM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_SM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_SM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_SM.c  -o ${OBJECTDIR}/_ext/1820848503/App_SM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_SM.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_SM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_MODBUS.o: ../app_src/App_MODBUS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_MODBUS.c  -o ${OBJECTDIR}/_ext/1820848503/App_MODBUS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_MODBUS.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_MODBUS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1820848503/App_NVMemory.o: ../app_src/App_NVMemory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1820848503" 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../app_src/App_NVMemory.c  -o ${OBJECTDIR}/_ext/1820848503/App_NVMemory.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1820848503/App_NVMemory.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1820848503/App_NVMemory.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_ADC.o: ../bsp_src/BSP_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_ADC.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_ADC.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_IO.o: ../bsp_src/BSP_IO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_IO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_IO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_IO.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_IO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_IO.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_IO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_PWM.o: ../bsp_src/BSP_PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_PWM.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_PWM.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_System.o: ../bsp_src/BSP_System.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_System.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_System.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_System.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_System.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_System.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_Timer.o: ../bsp_src/BSP_Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_Timer.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_Timer.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_Timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_UART.o: ../bsp_src/BSP_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_UART.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_UART.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_UART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1500727659/BSP_Relay.o: ../bsp_src/BSP_Relay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1500727659" 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bsp_src/BSP_Relay.c  -o ${OBJECTDIR}/_ext/1500727659/BSP_Relay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1500727659/BSP_Relay.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1500727659/BSP_Relay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o: ../lib_src/EEPROM_Emulation/DEE_Emulation_16-bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/882496299" 
	@${RM} ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o.d 
	@${RM} ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/EEPROM_Emulation/DEE_Emulation_16-bit.c  -o ${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/882496299/DEE_Emulation_16-bit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/292539343/mbascii.o: ../lib_src/FreeMODBUS/modbus/ascii/mbascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/292539343" 
	@${RM} ${OBJECTDIR}/_ext/292539343/mbascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/292539343/mbascii.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/ascii/mbascii.c  -o ${OBJECTDIR}/_ext/292539343/mbascii.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/292539343/mbascii.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/292539343/mbascii.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfunccoils.o: ../lib_src/FreeMODBUS/modbus/functions/mbfunccoils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfunccoils.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfunccoils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfunccoils.c  -o ${OBJECTDIR}/_ext/141222789/mbfunccoils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfunccoils.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfunccoils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncdiag.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncdiag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncdiag.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncdiag.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncdiag.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncdiag.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncdisc.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncdisc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncdisc.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncdisc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncdisc.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncdisc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncholding.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncholding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncholding.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncholding.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncholding.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncholding.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncholding.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncholding.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncinput.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncinput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncinput.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncinput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncinput.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncinput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncinput.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncinput.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbfuncother.o: ../lib_src/FreeMODBUS/modbus/functions/mbfuncother.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncother.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbfuncother.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbfuncother.c  -o ${OBJECTDIR}/_ext/141222789/mbfuncother.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbfuncother.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbfuncother.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/141222789/mbutils.o: ../lib_src/FreeMODBUS/modbus/functions/mbutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/141222789" 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbutils.o.d 
	@${RM} ${OBJECTDIR}/_ext/141222789/mbutils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/functions/mbutils.c  -o ${OBJECTDIR}/_ext/141222789/mbutils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/141222789/mbutils.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/141222789/mbutils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1675687763/mbcrc.o: ../lib_src/FreeMODBUS/modbus/rtu/mbcrc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1675687763" 
	@${RM} ${OBJECTDIR}/_ext/1675687763/mbcrc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1675687763/mbcrc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/rtu/mbcrc.c  -o ${OBJECTDIR}/_ext/1675687763/mbcrc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1675687763/mbcrc.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1675687763/mbcrc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1675687763/mbrtu.o: ../lib_src/FreeMODBUS/modbus/rtu/mbrtu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1675687763" 
	@${RM} ${OBJECTDIR}/_ext/1675687763/mbrtu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1675687763/mbrtu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/rtu/mbrtu.c  -o ${OBJECTDIR}/_ext/1675687763/mbrtu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1675687763/mbrtu.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1675687763/mbrtu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1675689153/mbtcp.o: ../lib_src/FreeMODBUS/modbus/tcp/mbtcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1675689153" 
	@${RM} ${OBJECTDIR}/_ext/1675689153/mbtcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1675689153/mbtcp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/tcp/mbtcp.c  -o ${OBJECTDIR}/_ext/1675689153/mbtcp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1675689153/mbtcp.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1675689153/mbtcp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/523702545/mb.o: ../lib_src/FreeMODBUS/modbus/mb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/523702545" 
	@${RM} ${OBJECTDIR}/_ext/523702545/mb.o.d 
	@${RM} ${OBJECTDIR}/_ext/523702545/mb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/modbus/mb.c  -o ${OBJECTDIR}/_ext/523702545/mb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/523702545/mb.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/523702545/mb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/478666894/portevent.o: ../lib_src/FreeMODBUS/port/portevent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/478666894" 
	@${RM} ${OBJECTDIR}/_ext/478666894/portevent.o.d 
	@${RM} ${OBJECTDIR}/_ext/478666894/portevent.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/port/portevent.c  -o ${OBJECTDIR}/_ext/478666894/portevent.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/478666894/portevent.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478666894/portevent.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/478666894/portserial.o: ../lib_src/FreeMODBUS/port/portserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/478666894" 
	@${RM} ${OBJECTDIR}/_ext/478666894/portserial.o.d 
	@${RM} ${OBJECTDIR}/_ext/478666894/portserial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/port/portserial.c  -o ${OBJECTDIR}/_ext/478666894/portserial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/478666894/portserial.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478666894/portserial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/478666894/porttimer.o: ../lib_src/FreeMODBUS/port/porttimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/478666894" 
	@${RM} ${OBJECTDIR}/_ext/478666894/porttimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/478666894/porttimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/FreeMODBUS/port/porttimer.c  -o ${OBJECTDIR}/_ext/478666894/porttimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/478666894/porttimer.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/478666894/porttimer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1514846245/ring_buffer.o: ../lib_src/ring_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/ring_buffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/ring_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/ring_buffer.c  -o ${OBJECTDIR}/_ext/1514846245/ring_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1514846245/ring_buffer.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/ring_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1514846245/crc.o: ../lib_src/crc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../lib_src/crc.c  -o ${OBJECTDIR}/_ext/1514846245/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1514846245/crc.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/crc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -mno-eds-warn  -g -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -O0 -msmart-io=1 -Wall -msfr-warn=off -finline 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/882496299/FlashOperations.o: ../lib_src/EEPROM_Emulation/FlashOperations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/882496299" 
	@${RM} ${OBJECTDIR}/_ext/882496299/FlashOperations.o.d 
	@${RM} ${OBJECTDIR}/_ext/882496299/FlashOperations.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/EEPROM_Emulation/FlashOperations.s  -o ${OBJECTDIR}/_ext/882496299/FlashOperations.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/882496299/FlashOperations.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/882496299/FlashOperations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/pid.o: ../lib_src/pid.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/pid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/pid.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/pid.s  -o ${OBJECTDIR}/_ext/1514846245/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/pid.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/pid.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o: ../lib_src/mc_clarke_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_clarke_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_filter.o: ../lib_src/mc_filter.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_filter.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_filter.s  -o ${OBJECTDIR}/_ext/1514846245/mc_filter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_filter.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_filter.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o: ../lib_src/mc_invclarke_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_invclarke_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o: ../lib_src/mc_invpark_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_invpark_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o: ../lib_src/mc_park_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_park_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o: ../lib_src/mc_piupdate_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_piupdate_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o: ../lib_src/mc_sinecos_ram_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_sinecos_ram_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o: ../lib_src/mc_sinetable_flash_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_sinetable_flash_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o: ../lib_src/mc_sinetable_ram_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_sinetable_ram_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o: ../lib_src/mc_svgen_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_svgen_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/882496299/FlashOperations.o: ../lib_src/EEPROM_Emulation/FlashOperations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/882496299" 
	@${RM} ${OBJECTDIR}/_ext/882496299/FlashOperations.o.d 
	@${RM} ${OBJECTDIR}/_ext/882496299/FlashOperations.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/EEPROM_Emulation/FlashOperations.s  -o ${OBJECTDIR}/_ext/882496299/FlashOperations.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/882496299/FlashOperations.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/882496299/FlashOperations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/pid.o: ../lib_src/pid.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/pid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/pid.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/pid.s  -o ${OBJECTDIR}/_ext/1514846245/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/pid.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/pid.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o: ../lib_src/mc_clarke_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_clarke_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_clarke_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_filter.o: ../lib_src/mc_filter.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_filter.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_filter.s  -o ${OBJECTDIR}/_ext/1514846245/mc_filter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_filter.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_filter.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o: ../lib_src/mc_invclarke_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_invclarke_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_invclarke_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o: ../lib_src/mc_invpark_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_invpark_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_invpark_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o: ../lib_src/mc_park_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_park_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_park_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o: ../lib_src/mc_piupdate_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_piupdate_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_piupdate_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o: ../lib_src/mc_sinecos_ram_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_sinecos_ram_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_sinecos_ram_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o: ../lib_src/mc_sinetable_flash_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_sinetable_flash_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_sinetable_flash_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o: ../lib_src/mc_sinetable_ram_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_sinetable_ram_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_sinetable_ram_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o: ../lib_src/mc_svgen_dspic.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1514846245" 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../lib_src/mc_svgen_dspic.s  -o ${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wa,-MD,"${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1514846245/mc_svgen_dspic.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Inresol_Inverter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Inresol_Inverter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F"  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,$(MP_LINKER_FILE_OPTION),--stack=64,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=64,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.28Pin_Starter_Board_RTDM.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Inresol_Inverter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Inresol_Inverter.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -D__dsPIC33E__ -DFULL_SPEED -DnotEVAL_BOARD -DnotPINS28_STARTER_BOARD -DnotHARDWARE_VERSION_1 -DHARDWARE_VERSION_2 -DnotDEBUG_ON_RS485 -DLOW_VOLTAGE_SCALERS -DADC_TIME_SHIFT_ENABLED -DnotU_GRID_AS_HIRES -DORTHOGONAL_ENABLED -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"../types" -I"../config" -I"../bsp_inc" -I"../app_inc" -I"../lib_src" -I"../lib_inc" -I"../lib_inc/Free_MODBUS/port" -I"../lib_inc/Free_MODBUS/modbus/ascii" -I"../lib_inc/Free_MODBUS/modbus/include" -I"../lib_inc/Free_MODBUS/modbus/rtu" -I"../lib_inc/Free_MODBUS/modbus/tcp" -I"../lib_inc/EEPROM_Emulation" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/h" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/dsPIC33E/inc" -I"C:/Projects/Tools/Microchip/xc16/v1.32/support/peripheral_30F_24H_33F" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=64,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=64,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.28Pin_Starter_Board_RTDM.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Inresol_Inverter.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
