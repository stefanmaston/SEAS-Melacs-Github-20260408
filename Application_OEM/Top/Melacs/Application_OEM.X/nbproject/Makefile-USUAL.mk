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
ifeq "$(wildcard nbproject/Makefile-local-USUAL.mk)" "nbproject/Makefile-local-USUAL.mk"
include nbproject/Makefile-local-USUAL.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=USUAL
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=oemGSM.c oemInputAcquisition.c oemInputAveraging.c oemLog.c oemMain.c oemOutputControl.c oemSaveReadParameter.c oemSendRecvUsb.c oemCalculations.c oemDisplay.c oemFunctions.c malloc.c setup.c mutex.c mmc.c sd_spi.c configurations.c speedControl.c tcp_server.c tcp_start.c timeDifference.c wrapper.c analogSensor10bit.c analogToPhysical.c buzzer.c common.c display.c melacs_spi.c onBoardADC.c onBoardRTCC.c readConfig.c sensorValueConvertion.c sensors.c hBridge.c logRun.c usb_composite.c threeWayValve.c main.c alarmStrings.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/oemGSM.o ${OBJECTDIR}/oemInputAcquisition.o ${OBJECTDIR}/oemInputAveraging.o ${OBJECTDIR}/oemLog.o ${OBJECTDIR}/oemMain.o ${OBJECTDIR}/oemOutputControl.o ${OBJECTDIR}/oemSaveReadParameter.o ${OBJECTDIR}/oemSendRecvUsb.o ${OBJECTDIR}/oemCalculations.o ${OBJECTDIR}/oemDisplay.o ${OBJECTDIR}/oemFunctions.o ${OBJECTDIR}/malloc.o ${OBJECTDIR}/setup.o ${OBJECTDIR}/mutex.o ${OBJECTDIR}/mmc.o ${OBJECTDIR}/sd_spi.o ${OBJECTDIR}/configurations.o ${OBJECTDIR}/speedControl.o ${OBJECTDIR}/tcp_server.o ${OBJECTDIR}/tcp_start.o ${OBJECTDIR}/timeDifference.o ${OBJECTDIR}/wrapper.o ${OBJECTDIR}/analogSensor10bit.o ${OBJECTDIR}/analogToPhysical.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/common.o ${OBJECTDIR}/display.o ${OBJECTDIR}/melacs_spi.o ${OBJECTDIR}/onBoardADC.o ${OBJECTDIR}/onBoardRTCC.o ${OBJECTDIR}/readConfig.o ${OBJECTDIR}/sensorValueConvertion.o ${OBJECTDIR}/sensors.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/logRun.o ${OBJECTDIR}/usb_composite.o ${OBJECTDIR}/threeWayValve.o ${OBJECTDIR}/main.o ${OBJECTDIR}/alarmStrings.o
POSSIBLE_DEPFILES=${OBJECTDIR}/oemGSM.o.d ${OBJECTDIR}/oemInputAcquisition.o.d ${OBJECTDIR}/oemInputAveraging.o.d ${OBJECTDIR}/oemLog.o.d ${OBJECTDIR}/oemMain.o.d ${OBJECTDIR}/oemOutputControl.o.d ${OBJECTDIR}/oemSaveReadParameter.o.d ${OBJECTDIR}/oemSendRecvUsb.o.d ${OBJECTDIR}/oemCalculations.o.d ${OBJECTDIR}/oemDisplay.o.d ${OBJECTDIR}/oemFunctions.o.d ${OBJECTDIR}/malloc.o.d ${OBJECTDIR}/setup.o.d ${OBJECTDIR}/mutex.o.d ${OBJECTDIR}/mmc.o.d ${OBJECTDIR}/sd_spi.o.d ${OBJECTDIR}/configurations.o.d ${OBJECTDIR}/speedControl.o.d ${OBJECTDIR}/tcp_server.o.d ${OBJECTDIR}/tcp_start.o.d ${OBJECTDIR}/timeDifference.o.d ${OBJECTDIR}/wrapper.o.d ${OBJECTDIR}/analogSensor10bit.o.d ${OBJECTDIR}/analogToPhysical.o.d ${OBJECTDIR}/buzzer.o.d ${OBJECTDIR}/common.o.d ${OBJECTDIR}/display.o.d ${OBJECTDIR}/melacs_spi.o.d ${OBJECTDIR}/onBoardADC.o.d ${OBJECTDIR}/onBoardRTCC.o.d ${OBJECTDIR}/readConfig.o.d ${OBJECTDIR}/sensorValueConvertion.o.d ${OBJECTDIR}/sensors.o.d ${OBJECTDIR}/hBridge.o.d ${OBJECTDIR}/logRun.o.d ${OBJECTDIR}/usb_composite.o.d ${OBJECTDIR}/threeWayValve.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/alarmStrings.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/oemGSM.o ${OBJECTDIR}/oemInputAcquisition.o ${OBJECTDIR}/oemInputAveraging.o ${OBJECTDIR}/oemLog.o ${OBJECTDIR}/oemMain.o ${OBJECTDIR}/oemOutputControl.o ${OBJECTDIR}/oemSaveReadParameter.o ${OBJECTDIR}/oemSendRecvUsb.o ${OBJECTDIR}/oemCalculations.o ${OBJECTDIR}/oemDisplay.o ${OBJECTDIR}/oemFunctions.o ${OBJECTDIR}/malloc.o ${OBJECTDIR}/setup.o ${OBJECTDIR}/mutex.o ${OBJECTDIR}/mmc.o ${OBJECTDIR}/sd_spi.o ${OBJECTDIR}/configurations.o ${OBJECTDIR}/speedControl.o ${OBJECTDIR}/tcp_server.o ${OBJECTDIR}/tcp_start.o ${OBJECTDIR}/timeDifference.o ${OBJECTDIR}/wrapper.o ${OBJECTDIR}/analogSensor10bit.o ${OBJECTDIR}/analogToPhysical.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/common.o ${OBJECTDIR}/display.o ${OBJECTDIR}/melacs_spi.o ${OBJECTDIR}/onBoardADC.o ${OBJECTDIR}/onBoardRTCC.o ${OBJECTDIR}/readConfig.o ${OBJECTDIR}/sensorValueConvertion.o ${OBJECTDIR}/sensors.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/logRun.o ${OBJECTDIR}/usb_composite.o ${OBJECTDIR}/threeWayValve.o ${OBJECTDIR}/main.o ${OBJECTDIR}/alarmStrings.o

# Source Files
SOURCEFILES=oemGSM.c oemInputAcquisition.c oemInputAveraging.c oemLog.c oemMain.c oemOutputControl.c oemSaveReadParameter.c oemSendRecvUsb.c oemCalculations.c oemDisplay.c oemFunctions.c malloc.c setup.c mutex.c mmc.c sd_spi.c configurations.c speedControl.c tcp_server.c tcp_start.c timeDifference.c wrapper.c analogSensor10bit.c analogToPhysical.c buzzer.c common.c display.c melacs_spi.c onBoardADC.c onBoardRTCC.c readConfig.c sensorValueConvertion.c sensors.c hBridge.c logRun.c usb_composite.c threeWayValve.c main.c alarmStrings.c



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
	${MAKE}  -f nbproject/Makefile-USUAL.mk dist/${CND_CONF}/${IMAGE_TYPE}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="app_32MX795F512L.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/oemGSM.o: oemGSM.c  .generated_files/2ca7e40c04162a11729464f614af50de7dc86348.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemGSM.o.d 
	@${RM} ${OBJECTDIR}/oemGSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemGSM.o.d" -o ${OBJECTDIR}/oemGSM.o oemGSM.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemInputAcquisition.o: oemInputAcquisition.c  .generated_files/a50b3d77fa78e66778d0e1e14c043358d7d558f3.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o.d 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemInputAcquisition.o.d" -o ${OBJECTDIR}/oemInputAcquisition.o oemInputAcquisition.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemInputAveraging.o: oemInputAveraging.c  .generated_files/d97a06693efb02d18967ff051cf97b0fc1db1b78.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o.d 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemInputAveraging.o.d" -o ${OBJECTDIR}/oemInputAveraging.o oemInputAveraging.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemLog.o: oemLog.c  .generated_files/7ed6a71e1ecc40d76eedb6c447c94f0dca3b90d4.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemLog.o.d 
	@${RM} ${OBJECTDIR}/oemLog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemLog.o.d" -o ${OBJECTDIR}/oemLog.o oemLog.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemMain.o: oemMain.c  .generated_files/9a653d26edc659f78d8aa58134f4c10825a4aff6.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemMain.o.d 
	@${RM} ${OBJECTDIR}/oemMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemMain.o.d" -o ${OBJECTDIR}/oemMain.o oemMain.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemOutputControl.o: oemOutputControl.c  .generated_files/eab9b4eaae93f4692978de2540603836aa768c9.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemOutputControl.o.d 
	@${RM} ${OBJECTDIR}/oemOutputControl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemOutputControl.o.d" -o ${OBJECTDIR}/oemOutputControl.o oemOutputControl.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemSaveReadParameter.o: oemSaveReadParameter.c  .generated_files/c7e01c657d62a035cce270ca646e130dcfa74c48.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o.d 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemSaveReadParameter.o.d" -o ${OBJECTDIR}/oemSaveReadParameter.o oemSaveReadParameter.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemSendRecvUsb.o: oemSendRecvUsb.c  .generated_files/11528a8634fa6b4b917873b4031998a76d999715.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o.d 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemSendRecvUsb.o.d" -o ${OBJECTDIR}/oemSendRecvUsb.o oemSendRecvUsb.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemCalculations.o: oemCalculations.c  .generated_files/e9a711c4dd9b76dce6eb5f433a4638492402b2bb.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemCalculations.o.d 
	@${RM} ${OBJECTDIR}/oemCalculations.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemCalculations.o.d" -o ${OBJECTDIR}/oemCalculations.o oemCalculations.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemDisplay.o: oemDisplay.c  .generated_files/5a0ba18e7f25019a69df4e1e93892db6e8c203b0.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemDisplay.o.d 
	@${RM} ${OBJECTDIR}/oemDisplay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemDisplay.o.d" -o ${OBJECTDIR}/oemDisplay.o oemDisplay.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemFunctions.o: oemFunctions.c  .generated_files/6a6726939f994288f8c900c605855f6f8a7fbe77.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemFunctions.o.d 
	@${RM} ${OBJECTDIR}/oemFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemFunctions.o.d" -o ${OBJECTDIR}/oemFunctions.o oemFunctions.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/malloc.o: malloc.c  .generated_files/a1b32479dcef021b50b877b1319a24a0578448d8.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/malloc.o.d 
	@${RM} ${OBJECTDIR}/malloc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/malloc.o.d" -o ${OBJECTDIR}/malloc.o malloc.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/setup.o: setup.c  .generated_files/a7967332707ebf1d6f4d29fa4e0786034b4de30f.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/setup.o.d 
	@${RM} ${OBJECTDIR}/setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/setup.o.d" -o ${OBJECTDIR}/setup.o setup.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mutex.o: mutex.c  .generated_files/f928e99a8477e260d60778c9a60a925e25a6e428.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mutex.o.d 
	@${RM} ${OBJECTDIR}/mutex.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/mutex.o.d" -o ${OBJECTDIR}/mutex.o mutex.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mmc.o: mmc.c  .generated_files/9dc050a660d5b96c5a63380d745e1a6a5a8f85d3.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc.o.d 
	@${RM} ${OBJECTDIR}/mmc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/mmc.o.d" -o ${OBJECTDIR}/mmc.o mmc.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sd_spi.o: sd_spi.c  .generated_files/6edc5ffa42c5a905adbbf4f76c7d6f4f811f4984.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/sd_spi.o.d" -o ${OBJECTDIR}/sd_spi.o sd_spi.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/configurations.o: configurations.c  .generated_files/8ce445fa96faa7b1d86199870e73ff684d7cfe24.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configurations.o.d 
	@${RM} ${OBJECTDIR}/configurations.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/configurations.o.d" -o ${OBJECTDIR}/configurations.o configurations.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/speedControl.o: speedControl.c  .generated_files/b020635dd6cfb405fa71f4b0c333ab21b6d13fcd.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/speedControl.o.d 
	@${RM} ${OBJECTDIR}/speedControl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/speedControl.o.d" -o ${OBJECTDIR}/speedControl.o speedControl.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/tcp_server.o: tcp_server.c  .generated_files/262b1351a1d09b8caf04d1731873110167821276.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_server.o.d 
	@${RM} ${OBJECTDIR}/tcp_server.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/tcp_server.o.d" -o ${OBJECTDIR}/tcp_server.o tcp_server.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/tcp_start.o: tcp_start.c  .generated_files/e105e2f21a4b9b8a03fc595ad20bc5d17e3d7afa.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_start.o.d 
	@${RM} ${OBJECTDIR}/tcp_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/tcp_start.o.d" -o ${OBJECTDIR}/tcp_start.o tcp_start.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/timeDifference.o: timeDifference.c  .generated_files/1107071caf7a68fa6c173ec8f3c516e27a4a77fb.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timeDifference.o.d 
	@${RM} ${OBJECTDIR}/timeDifference.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/timeDifference.o.d" -o ${OBJECTDIR}/timeDifference.o timeDifference.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/wrapper.o: wrapper.c  .generated_files/b9eb277a409fe1f45ed42df648c0ad899aae40d9.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wrapper.o.d 
	@${RM} ${OBJECTDIR}/wrapper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/wrapper.o.d" -o ${OBJECTDIR}/wrapper.o wrapper.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/analogSensor10bit.o: analogSensor10bit.c  .generated_files/6751911c9ae18f842bc81d144efe2f8de451c49f.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o.d 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/analogSensor10bit.o.d" -o ${OBJECTDIR}/analogSensor10bit.o analogSensor10bit.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/analogToPhysical.o: analogToPhysical.c  .generated_files/a13a766bf4df32ea2df4a7296f7bb57716e6b2cc.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogToPhysical.o.d 
	@${RM} ${OBJECTDIR}/analogToPhysical.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/analogToPhysical.o.d" -o ${OBJECTDIR}/analogToPhysical.o analogToPhysical.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buzzer.o: buzzer.c  .generated_files/a2d0cbdca76203dc3be79fd6db849531760f4760.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/buzzer.o.d" -o ${OBJECTDIR}/buzzer.o buzzer.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/common.o: common.c  .generated_files/3e00b1fab2cf846668ad4ccbbbc8b47010ae11bb.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/common.o.d 
	@${RM} ${OBJECTDIR}/common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/common.o.d" -o ${OBJECTDIR}/common.o common.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/display.o: display.c  .generated_files/154f1ed61f75eaa6b5744643a44ad75d64146487.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/display.o.d" -o ${OBJECTDIR}/display.o display.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/melacs_spi.o: melacs_spi.c  .generated_files/3f28c3dfe399c44575a35281523286a0be119a08.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/melacs_spi.o.d 
	@${RM} ${OBJECTDIR}/melacs_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/melacs_spi.o.d" -o ${OBJECTDIR}/melacs_spi.o melacs_spi.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/onBoardADC.o: onBoardADC.c  .generated_files/a9716c29df5eb3f5734590f096bbd168f4fa860d.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardADC.o.d 
	@${RM} ${OBJECTDIR}/onBoardADC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/onBoardADC.o.d" -o ${OBJECTDIR}/onBoardADC.o onBoardADC.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/onBoardRTCC.o: onBoardRTCC.c  .generated_files/6ed2b3c0c730ac260018b72580fc93716ce29d2d.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o.d 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/onBoardRTCC.o.d" -o ${OBJECTDIR}/onBoardRTCC.o onBoardRTCC.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/readConfig.o: readConfig.c  .generated_files/ee7524fcb4cbd5967159d11b9a2db59b2ca22789.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/readConfig.o.d 
	@${RM} ${OBJECTDIR}/readConfig.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/readConfig.o.d" -o ${OBJECTDIR}/readConfig.o readConfig.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorValueConvertion.o: sensorValueConvertion.c  .generated_files/65749831fc4a68f1da27b79969328813f48c1f66.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o.d 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/sensorValueConvertion.o.d" -o ${OBJECTDIR}/sensorValueConvertion.o sensorValueConvertion.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensors.o: sensors.c  .generated_files/bc33810182a4528940b276a43c94521e83a5b01d.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensors.o.d 
	@${RM} ${OBJECTDIR}/sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/sensors.o.d" -o ${OBJECTDIR}/sensors.o sensors.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/hBridge.o: hBridge.c  .generated_files/4eff2086742399ed514106661ca0b383e1c115f2.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/hBridge.o.d" -o ${OBJECTDIR}/hBridge.o hBridge.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/logRun.o: logRun.c  .generated_files/7b73d11eb1baa18bab543a090d53042086e6aa00.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/logRun.o.d 
	@${RM} ${OBJECTDIR}/logRun.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/logRun.o.d" -o ${OBJECTDIR}/logRun.o logRun.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb_composite.o: usb_composite.c  .generated_files/13817cf2182aae4c378b901092a86171c9e4d9c9.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_composite.o.d 
	@${RM} ${OBJECTDIR}/usb_composite.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/usb_composite.o.d" -o ${OBJECTDIR}/usb_composite.o usb_composite.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/threeWayValve.o: threeWayValve.c  .generated_files/de7b2aef05cfbef97e31511708a55775acc109af.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/threeWayValve.o.d 
	@${RM} ${OBJECTDIR}/threeWayValve.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/threeWayValve.o.d" -o ${OBJECTDIR}/threeWayValve.o threeWayValve.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/112be801dcf3a45aecd02f3f66c220512a7a43b.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/alarmStrings.o: alarmStrings.c  .generated_files/ef22010873c4d3e147d155e4c206ad712dbc2a3b.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/alarmStrings.o.d 
	@${RM} ${OBJECTDIR}/alarmStrings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/alarmStrings.o.d" -o ${OBJECTDIR}/alarmStrings.o alarmStrings.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/oemGSM.o: oemGSM.c  .generated_files/a5e8d227beefd1b9e8fcae5059edf05ffc9af340.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemGSM.o.d 
	@${RM} ${OBJECTDIR}/oemGSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemGSM.o.d" -o ${OBJECTDIR}/oemGSM.o oemGSM.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemInputAcquisition.o: oemInputAcquisition.c  .generated_files/ae000ee32534c9a69444e093c878d1264f2aec2.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o.d 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemInputAcquisition.o.d" -o ${OBJECTDIR}/oemInputAcquisition.o oemInputAcquisition.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemInputAveraging.o: oemInputAveraging.c  .generated_files/ce2149dff87cd8ea243b1682c32db766cc280992.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o.d 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemInputAveraging.o.d" -o ${OBJECTDIR}/oemInputAveraging.o oemInputAveraging.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemLog.o: oemLog.c  .generated_files/f61cc0719c79b57b415fefb97cd63f5ec9f43803.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemLog.o.d 
	@${RM} ${OBJECTDIR}/oemLog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemLog.o.d" -o ${OBJECTDIR}/oemLog.o oemLog.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemMain.o: oemMain.c  .generated_files/f2c2cac3b48afc187cb92e4810d56253ecf3c2a3.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemMain.o.d 
	@${RM} ${OBJECTDIR}/oemMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemMain.o.d" -o ${OBJECTDIR}/oemMain.o oemMain.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemOutputControl.o: oemOutputControl.c  .generated_files/2f24add1d3a25687470772c94b00c2dba21b5706.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemOutputControl.o.d 
	@${RM} ${OBJECTDIR}/oemOutputControl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemOutputControl.o.d" -o ${OBJECTDIR}/oemOutputControl.o oemOutputControl.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemSaveReadParameter.o: oemSaveReadParameter.c  .generated_files/ea3c01ad01b0637662757176b6d840c81135d95d.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o.d 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemSaveReadParameter.o.d" -o ${OBJECTDIR}/oemSaveReadParameter.o oemSaveReadParameter.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemSendRecvUsb.o: oemSendRecvUsb.c  .generated_files/10eacf9b0452267caec7262e2b045b4ae70e6d66.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o.d 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemSendRecvUsb.o.d" -o ${OBJECTDIR}/oemSendRecvUsb.o oemSendRecvUsb.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemCalculations.o: oemCalculations.c  .generated_files/a4127d54cb5d2bcd8c0ed940887c1a15c797ae35.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemCalculations.o.d 
	@${RM} ${OBJECTDIR}/oemCalculations.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemCalculations.o.d" -o ${OBJECTDIR}/oemCalculations.o oemCalculations.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemDisplay.o: oemDisplay.c  .generated_files/dd47d331ddff4e8569aae23960aaf96621b03850.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemDisplay.o.d 
	@${RM} ${OBJECTDIR}/oemDisplay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemDisplay.o.d" -o ${OBJECTDIR}/oemDisplay.o oemDisplay.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemFunctions.o: oemFunctions.c  .generated_files/9290813336396f39f9a888c530abc54a3125fb6b.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemFunctions.o.d 
	@${RM} ${OBJECTDIR}/oemFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/oemFunctions.o.d" -o ${OBJECTDIR}/oemFunctions.o oemFunctions.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/malloc.o: malloc.c  .generated_files/7f8e4512d0e3858181609087a79b6dea4972f642.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/malloc.o.d 
	@${RM} ${OBJECTDIR}/malloc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/malloc.o.d" -o ${OBJECTDIR}/malloc.o malloc.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/setup.o: setup.c  .generated_files/aab60914eb0ee9c010ab8e4b51c120e5f0763d21.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/setup.o.d 
	@${RM} ${OBJECTDIR}/setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/setup.o.d" -o ${OBJECTDIR}/setup.o setup.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mutex.o: mutex.c  .generated_files/f9351ff88f65eb84bdc0950e3303c09f9d3d561.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mutex.o.d 
	@${RM} ${OBJECTDIR}/mutex.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/mutex.o.d" -o ${OBJECTDIR}/mutex.o mutex.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mmc.o: mmc.c  .generated_files/1dcd6fc90440297fe99cdb9b7c32ada326a28fa6.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc.o.d 
	@${RM} ${OBJECTDIR}/mmc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/mmc.o.d" -o ${OBJECTDIR}/mmc.o mmc.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sd_spi.o: sd_spi.c  .generated_files/261ffe01129e2b4e9ab5640d79c723583fe01e51.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/sd_spi.o.d" -o ${OBJECTDIR}/sd_spi.o sd_spi.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/configurations.o: configurations.c  .generated_files/4f8aa2623fb3dffe0060b970096a891d4d795b6.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configurations.o.d 
	@${RM} ${OBJECTDIR}/configurations.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/configurations.o.d" -o ${OBJECTDIR}/configurations.o configurations.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/speedControl.o: speedControl.c  .generated_files/a1b80a7fda5dc005b4fccd063a10a5eb4b05c222.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/speedControl.o.d 
	@${RM} ${OBJECTDIR}/speedControl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/speedControl.o.d" -o ${OBJECTDIR}/speedControl.o speedControl.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/tcp_server.o: tcp_server.c  .generated_files/6097af6e712ca38c2f8e9beb4e35e21df5344daf.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_server.o.d 
	@${RM} ${OBJECTDIR}/tcp_server.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/tcp_server.o.d" -o ${OBJECTDIR}/tcp_server.o tcp_server.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/tcp_start.o: tcp_start.c  .generated_files/9e3f89f9ce9fcf0bc9fc80b4f0e01cc07c76974e.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_start.o.d 
	@${RM} ${OBJECTDIR}/tcp_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/tcp_start.o.d" -o ${OBJECTDIR}/tcp_start.o tcp_start.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/timeDifference.o: timeDifference.c  .generated_files/2a8436e9aefdb59980924f32010c224c88757489.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timeDifference.o.d 
	@${RM} ${OBJECTDIR}/timeDifference.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/timeDifference.o.d" -o ${OBJECTDIR}/timeDifference.o timeDifference.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/wrapper.o: wrapper.c  .generated_files/fd4c87e82107b1f9e2eb349921b6ae8ae9c56b7.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wrapper.o.d 
	@${RM} ${OBJECTDIR}/wrapper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/wrapper.o.d" -o ${OBJECTDIR}/wrapper.o wrapper.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/analogSensor10bit.o: analogSensor10bit.c  .generated_files/937a26bd373e494ae4d9292eaa559ae778408e91.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o.d 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/analogSensor10bit.o.d" -o ${OBJECTDIR}/analogSensor10bit.o analogSensor10bit.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/analogToPhysical.o: analogToPhysical.c  .generated_files/5c78e3d58d2c28d350f0c1f512f7675abd98f6e0.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogToPhysical.o.d 
	@${RM} ${OBJECTDIR}/analogToPhysical.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/analogToPhysical.o.d" -o ${OBJECTDIR}/analogToPhysical.o analogToPhysical.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buzzer.o: buzzer.c  .generated_files/90cb6762d1c46c95b2c763d22799e56667d03974.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/buzzer.o.d" -o ${OBJECTDIR}/buzzer.o buzzer.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/common.o: common.c  .generated_files/f49588a9c57f9567ade85db3154256ac561070da.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/common.o.d 
	@${RM} ${OBJECTDIR}/common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/common.o.d" -o ${OBJECTDIR}/common.o common.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/display.o: display.c  .generated_files/61c290abbf0f7fd8528ca892df4f47b348d2bdcb.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/display.o.d" -o ${OBJECTDIR}/display.o display.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/melacs_spi.o: melacs_spi.c  .generated_files/6eecd7f9369ead55a94fd3ca914d282b642fac13.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/melacs_spi.o.d 
	@${RM} ${OBJECTDIR}/melacs_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/melacs_spi.o.d" -o ${OBJECTDIR}/melacs_spi.o melacs_spi.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/onBoardADC.o: onBoardADC.c  .generated_files/e6a2520929fe861745e0c28d24f2776310491e53.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardADC.o.d 
	@${RM} ${OBJECTDIR}/onBoardADC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/onBoardADC.o.d" -o ${OBJECTDIR}/onBoardADC.o onBoardADC.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/onBoardRTCC.o: onBoardRTCC.c  .generated_files/254465c8725b53c59ffee93980c0c56f1c2f8bcc.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o.d 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/onBoardRTCC.o.d" -o ${OBJECTDIR}/onBoardRTCC.o onBoardRTCC.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/readConfig.o: readConfig.c  .generated_files/f520e88c7479be3a7a222f4e576f8011fab1013d.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/readConfig.o.d 
	@${RM} ${OBJECTDIR}/readConfig.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/readConfig.o.d" -o ${OBJECTDIR}/readConfig.o readConfig.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorValueConvertion.o: sensorValueConvertion.c  .generated_files/c0005527a8feb3b3df0fb9851c47aaf60a808d2.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o.d 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/sensorValueConvertion.o.d" -o ${OBJECTDIR}/sensorValueConvertion.o sensorValueConvertion.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensors.o: sensors.c  .generated_files/1b46111446eceff4d356ec2d7a511676a8ae5389.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensors.o.d 
	@${RM} ${OBJECTDIR}/sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/sensors.o.d" -o ${OBJECTDIR}/sensors.o sensors.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/hBridge.o: hBridge.c  .generated_files/f470f8bcd2517ba1ae203ed49d892bd6507aae32.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/hBridge.o.d" -o ${OBJECTDIR}/hBridge.o hBridge.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/logRun.o: logRun.c  .generated_files/e1b4e7c887bd6384c4a4964ea37236a5ba1a54d2.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/logRun.o.d 
	@${RM} ${OBJECTDIR}/logRun.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/logRun.o.d" -o ${OBJECTDIR}/logRun.o logRun.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb_composite.o: usb_composite.c  .generated_files/3bd7e2349bd0ea186a85fb3a0fdf8d700ce10595.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_composite.o.d 
	@${RM} ${OBJECTDIR}/usb_composite.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/usb_composite.o.d" -o ${OBJECTDIR}/usb_composite.o usb_composite.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/threeWayValve.o: threeWayValve.c  .generated_files/8c09318c3781ce451ed3b9715530c151d91beb0.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/threeWayValve.o.d 
	@${RM} ${OBJECTDIR}/threeWayValve.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/threeWayValve.o.d" -o ${OBJECTDIR}/threeWayValve.o threeWayValve.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/ec6e39ab055e75f12bb2cdc155f1383b75027e1e.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/alarmStrings.o: alarmStrings.c  .generated_files/8e355e3ecbb90d4ba0b744e92a170c9cb07ae40d.flag .generated_files/6ad3d15ab281b8743593921d6aad8b7591cde64f.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/alarmStrings.o.d 
	@${RM} ${OBJECTDIR}/alarmStrings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -I"../../include" -I"../../stdio" -I"." -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/alarmStrings.o.d" -o ${OBJECTDIR}/alarmStrings.o alarmStrings.c    -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../servers/fsys-fatfs/fsys-fatfs.a ../../iolib/iolib.a ../../servers/usb/usb_server/usb_server.a ../../servers/usb/device/usbd_core/usbd_core.a ../../servers/usb/device/usbd_pic32x_port/usbd_pic32x_port.a ../../servers/_ipv6/tcp6/ENC424J600_v6/ENC424J600_v6.a ../../servers/_ipv6/tcp6/server6/tcp_dual.a ../../servers/usb/device/usbd_msc_driver/usbd_msc_driver.a ../../servers/usb/device/usbd_cdc_serial_driver/usbd_cdc_serial_driver.a ../../kernel/Unison.a ../../servers/tty/tty.a ../../stdio/stdiolib.a  app_32MX795F512L.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\servers\fsys-fatfs\fsys-fatfs.a ..\..\iolib\iolib.a ..\..\servers\usb\usb_server\usb_server.a ..\..\servers\usb\device\usbd_core\usbd_core.a ..\..\servers\usb\device\usbd_pic32x_port\usbd_pic32x_port.a ..\..\servers\_ipv6\tcp6\ENC424J600_v6\ENC424J600_v6.a ..\..\servers\_ipv6\tcp6\server6\tcp_dual.a ..\..\servers\usb\device\usbd_msc_driver\usbd_msc_driver.a ..\..\servers\usb\device\usbd_cdc_serial_driver\usbd_cdc_serial_driver.a ..\..\kernel\Unison.a ..\..\servers\tty\tty.a ..\..\stdio\stdiolib.a      -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../servers/fsys-fatfs/fsys-fatfs.a ../../iolib/iolib.a ../../servers/usb/usb_server/usb_server.a ../../servers/usb/device/usbd_core/usbd_core.a ../../servers/usb/device/usbd_pic32x_port/usbd_pic32x_port.a ../../servers/_ipv6/tcp6/ENC424J600_v6/ENC424J600_v6.a ../../servers/_ipv6/tcp6/server6/tcp_dual.a ../../servers/usb/device/usbd_msc_driver/usbd_msc_driver.a ../../servers/usb/device/usbd_cdc_serial_driver/usbd_cdc_serial_driver.a ../../kernel/Unison.a ../../servers/tty/tty.a ../../stdio/stdiolib.a app_32MX795F512L.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Application_OEM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\servers\fsys-fatfs\fsys-fatfs.a ..\..\iolib\iolib.a ..\..\servers\usb\usb_server\usb_server.a ..\..\servers\usb\device\usbd_core\usbd_core.a ..\..\servers\usb\device\usbd_pic32x_port\usbd_pic32x_port.a ..\..\servers\_ipv6\tcp6\ENC424J600_v6\ENC424J600_v6.a ..\..\servers\_ipv6\tcp6\server6\tcp_dual.a ..\..\servers\usb\device\usbd_msc_driver\usbd_msc_driver.a ..\..\servers\usb\device\usbd_cdc_serial_driver\usbd_cdc_serial_driver.a ..\..\kernel\Unison.a ..\..\servers\tty\tty.a ..\..\stdio\stdiolib.a      -DXPRJ_USUAL=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Application_OEM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/USUAL
	${RM} -r dist/USUAL

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
