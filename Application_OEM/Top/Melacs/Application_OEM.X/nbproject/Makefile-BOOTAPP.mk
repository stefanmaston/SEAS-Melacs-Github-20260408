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
ifeq "$(wildcard nbproject/Makefile-local-BOOTAPP.mk)" "nbproject/Makefile-local-BOOTAPP.mk"
include nbproject/Makefile-local-BOOTAPP.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=BOOTAPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=oemGSM.c oemInputAcquisition.c oemInputAveraging.c oemLog.c oemMain.c oemOutputControl.c oemSaveReadParameter.c oemSendRecvUsb.c oemCalculations.c oemDisplay.c oemFunctions.c oemMainThread.c malloc.c setup.c mutex.c mmc.c sd_spi.c configurations.c speedControl.c tcp_start.c timeDifference.c wrapper.c analogSensor10bit.c analogToPhysical.c buzzer.c common.c display.c melacs_spi.c onBoardADC.c onBoardRTCC.c readConfig.c sensorValueConvertion.c sensors.c firmwareRecoveryUpdate.c hBridge.c logRun.c usb_composite.c threeWayValve.c main.c alarmStrings.c modbus.c delay.c checksum.c modbus_client.c uart.c tcpserverstream.c ether.c queuehandler.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/oemGSM.o ${OBJECTDIR}/oemInputAcquisition.o ${OBJECTDIR}/oemInputAveraging.o ${OBJECTDIR}/oemLog.o ${OBJECTDIR}/oemMain.o ${OBJECTDIR}/oemOutputControl.o ${OBJECTDIR}/oemSaveReadParameter.o ${OBJECTDIR}/oemSendRecvUsb.o ${OBJECTDIR}/oemCalculations.o ${OBJECTDIR}/oemDisplay.o ${OBJECTDIR}/oemFunctions.o ${OBJECTDIR}/oemMainThread.o ${OBJECTDIR}/malloc.o ${OBJECTDIR}/setup.o ${OBJECTDIR}/mutex.o ${OBJECTDIR}/mmc.o ${OBJECTDIR}/sd_spi.o ${OBJECTDIR}/configurations.o ${OBJECTDIR}/speedControl.o ${OBJECTDIR}/tcp_start.o ${OBJECTDIR}/timeDifference.o ${OBJECTDIR}/wrapper.o ${OBJECTDIR}/analogSensor10bit.o ${OBJECTDIR}/analogToPhysical.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/common.o ${OBJECTDIR}/display.o ${OBJECTDIR}/melacs_spi.o ${OBJECTDIR}/onBoardADC.o ${OBJECTDIR}/onBoardRTCC.o ${OBJECTDIR}/readConfig.o ${OBJECTDIR}/sensorValueConvertion.o ${OBJECTDIR}/sensors.o ${OBJECTDIR}/firmwareRecoveryUpdate.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/logRun.o ${OBJECTDIR}/usb_composite.o ${OBJECTDIR}/threeWayValve.o ${OBJECTDIR}/main.o ${OBJECTDIR}/alarmStrings.o ${OBJECTDIR}/modbus.o ${OBJECTDIR}/delay.o ${OBJECTDIR}/checksum.o ${OBJECTDIR}/modbus_client.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/tcpserverstream.o ${OBJECTDIR}/ether.o ${OBJECTDIR}/queuehandler.o
POSSIBLE_DEPFILES=${OBJECTDIR}/oemGSM.o.d ${OBJECTDIR}/oemInputAcquisition.o.d ${OBJECTDIR}/oemInputAveraging.o.d ${OBJECTDIR}/oemLog.o.d ${OBJECTDIR}/oemMain.o.d ${OBJECTDIR}/oemOutputControl.o.d ${OBJECTDIR}/oemSaveReadParameter.o.d ${OBJECTDIR}/oemSendRecvUsb.o.d ${OBJECTDIR}/oemCalculations.o.d ${OBJECTDIR}/oemDisplay.o.d ${OBJECTDIR}/oemFunctions.o.d ${OBJECTDIR}/oemMainThread.o.d ${OBJECTDIR}/malloc.o.d ${OBJECTDIR}/setup.o.d ${OBJECTDIR}/mutex.o.d ${OBJECTDIR}/mmc.o.d ${OBJECTDIR}/sd_spi.o.d ${OBJECTDIR}/configurations.o.d ${OBJECTDIR}/speedControl.o.d ${OBJECTDIR}/tcp_start.o.d ${OBJECTDIR}/timeDifference.o.d ${OBJECTDIR}/wrapper.o.d ${OBJECTDIR}/analogSensor10bit.o.d ${OBJECTDIR}/analogToPhysical.o.d ${OBJECTDIR}/buzzer.o.d ${OBJECTDIR}/common.o.d ${OBJECTDIR}/display.o.d ${OBJECTDIR}/melacs_spi.o.d ${OBJECTDIR}/onBoardADC.o.d ${OBJECTDIR}/onBoardRTCC.o.d ${OBJECTDIR}/readConfig.o.d ${OBJECTDIR}/sensorValueConvertion.o.d ${OBJECTDIR}/sensors.o.d ${OBJECTDIR}/firmwareRecoveryUpdate.o.d ${OBJECTDIR}/hBridge.o.d ${OBJECTDIR}/logRun.o.d ${OBJECTDIR}/usb_composite.o.d ${OBJECTDIR}/threeWayValve.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/alarmStrings.o.d ${OBJECTDIR}/modbus.o.d ${OBJECTDIR}/delay.o.d ${OBJECTDIR}/checksum.o.d ${OBJECTDIR}/modbus_client.o.d ${OBJECTDIR}/uart.o.d ${OBJECTDIR}/tcpserverstream.o.d ${OBJECTDIR}/ether.o.d ${OBJECTDIR}/queuehandler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/oemGSM.o ${OBJECTDIR}/oemInputAcquisition.o ${OBJECTDIR}/oemInputAveraging.o ${OBJECTDIR}/oemLog.o ${OBJECTDIR}/oemMain.o ${OBJECTDIR}/oemOutputControl.o ${OBJECTDIR}/oemSaveReadParameter.o ${OBJECTDIR}/oemSendRecvUsb.o ${OBJECTDIR}/oemCalculations.o ${OBJECTDIR}/oemDisplay.o ${OBJECTDIR}/oemFunctions.o ${OBJECTDIR}/oemMainThread.o ${OBJECTDIR}/malloc.o ${OBJECTDIR}/setup.o ${OBJECTDIR}/mutex.o ${OBJECTDIR}/mmc.o ${OBJECTDIR}/sd_spi.o ${OBJECTDIR}/configurations.o ${OBJECTDIR}/speedControl.o ${OBJECTDIR}/tcp_start.o ${OBJECTDIR}/timeDifference.o ${OBJECTDIR}/wrapper.o ${OBJECTDIR}/analogSensor10bit.o ${OBJECTDIR}/analogToPhysical.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/common.o ${OBJECTDIR}/display.o ${OBJECTDIR}/melacs_spi.o ${OBJECTDIR}/onBoardADC.o ${OBJECTDIR}/onBoardRTCC.o ${OBJECTDIR}/readConfig.o ${OBJECTDIR}/sensorValueConvertion.o ${OBJECTDIR}/sensors.o ${OBJECTDIR}/firmwareRecoveryUpdate.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/logRun.o ${OBJECTDIR}/usb_composite.o ${OBJECTDIR}/threeWayValve.o ${OBJECTDIR}/main.o ${OBJECTDIR}/alarmStrings.o ${OBJECTDIR}/modbus.o ${OBJECTDIR}/delay.o ${OBJECTDIR}/checksum.o ${OBJECTDIR}/modbus_client.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/tcpserverstream.o ${OBJECTDIR}/ether.o ${OBJECTDIR}/queuehandler.o

# Source Files
SOURCEFILES=oemGSM.c oemInputAcquisition.c oemInputAveraging.c oemLog.c oemMain.c oemOutputControl.c oemSaveReadParameter.c oemSendRecvUsb.c oemCalculations.c oemDisplay.c oemFunctions.c oemMainThread.c malloc.c setup.c mutex.c mmc.c sd_spi.c configurations.c speedControl.c tcp_start.c timeDifference.c wrapper.c analogSensor10bit.c analogToPhysical.c buzzer.c common.c display.c melacs_spi.c onBoardADC.c onBoardRTCC.c readConfig.c sensorValueConvertion.c sensors.c firmwareRecoveryUpdate.c hBridge.c logRun.c usb_composite.c threeWayValve.c main.c alarmStrings.c modbus.c delay.c checksum.c modbus_client.c uart.c tcpserverstream.c ether.c queuehandler.c



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
	${MAKE}  -f nbproject/Makefile-BOOTAPP.mk ${DISTDIR}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/oemGSM.o: oemGSM.c  .generated_files/flags/BOOTAPP/1dd9c008b2f048a312338bd72bed2b7f69d8f03a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemGSM.o.d 
	@${RM} ${OBJECTDIR}/oemGSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemGSM.o.d" -o ${OBJECTDIR}/oemGSM.o oemGSM.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemInputAcquisition.o: oemInputAcquisition.c  .generated_files/flags/BOOTAPP/10d4ae9e0415d70d345c4a4f81aff4c9952f5654 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o.d 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemInputAcquisition.o.d" -o ${OBJECTDIR}/oemInputAcquisition.o oemInputAcquisition.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemInputAveraging.o: oemInputAveraging.c  .generated_files/flags/BOOTAPP/df2317fb228fe598c487da49ac47041034398851 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o.d 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemInputAveraging.o.d" -o ${OBJECTDIR}/oemInputAveraging.o oemInputAveraging.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemLog.o: oemLog.c  .generated_files/flags/BOOTAPP/86f6ee265f3827642ad5ccb4f24d62f0339f200c .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemLog.o.d 
	@${RM} ${OBJECTDIR}/oemLog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemLog.o.d" -o ${OBJECTDIR}/oemLog.o oemLog.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemMain.o: oemMain.c  .generated_files/flags/BOOTAPP/1afb2ca870b631513c57d8e7dc0fb01a2fe4e22b .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemMain.o.d 
	@${RM} ${OBJECTDIR}/oemMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemMain.o.d" -o ${OBJECTDIR}/oemMain.o oemMain.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemOutputControl.o: oemOutputControl.c  .generated_files/flags/BOOTAPP/3b0cb18188f90d24f2bc30f3363e791e0d38b5b7 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemOutputControl.o.d 
	@${RM} ${OBJECTDIR}/oemOutputControl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemOutputControl.o.d" -o ${OBJECTDIR}/oemOutputControl.o oemOutputControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemSaveReadParameter.o: oemSaveReadParameter.c  .generated_files/flags/BOOTAPP/bec6408c77644685fcca04e6ce26d6e969dbd1e6 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o.d 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemSaveReadParameter.o.d" -o ${OBJECTDIR}/oemSaveReadParameter.o oemSaveReadParameter.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemSendRecvUsb.o: oemSendRecvUsb.c  .generated_files/flags/BOOTAPP/3bd84187965815fffb3c8699f983b1ac7f74909c .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o.d 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemSendRecvUsb.o.d" -o ${OBJECTDIR}/oemSendRecvUsb.o oemSendRecvUsb.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemCalculations.o: oemCalculations.c  .generated_files/flags/BOOTAPP/24f640896833690031aee8225e39651130a5a27d .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemCalculations.o.d 
	@${RM} ${OBJECTDIR}/oemCalculations.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemCalculations.o.d" -o ${OBJECTDIR}/oemCalculations.o oemCalculations.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemDisplay.o: oemDisplay.c  .generated_files/flags/BOOTAPP/ddd9a764c3107fea620669fcd636362d5fbaebc8 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemDisplay.o.d 
	@${RM} ${OBJECTDIR}/oemDisplay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemDisplay.o.d" -o ${OBJECTDIR}/oemDisplay.o oemDisplay.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemFunctions.o: oemFunctions.c  .generated_files/flags/BOOTAPP/31be0fc5a8fdcb6236327c193b682385bfa43c6e .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemFunctions.o.d 
	@${RM} ${OBJECTDIR}/oemFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemFunctions.o.d" -o ${OBJECTDIR}/oemFunctions.o oemFunctions.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemMainThread.o: oemMainThread.c  .generated_files/flags/BOOTAPP/f40e982eac5d97a0766125fb839b638244362c0a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemMainThread.o.d 
	@${RM} ${OBJECTDIR}/oemMainThread.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemMainThread.o.d" -o ${OBJECTDIR}/oemMainThread.o oemMainThread.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/malloc.o: malloc.c  .generated_files/flags/BOOTAPP/de35fcad1498d0f5fc4aea8a0d33ab8cdf046c90 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/malloc.o.d 
	@${RM} ${OBJECTDIR}/malloc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/malloc.o.d" -o ${OBJECTDIR}/malloc.o malloc.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/setup.o: setup.c  .generated_files/flags/BOOTAPP/8191034f545354bf5b3f7413aa47c3b665b3a18a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/setup.o.d 
	@${RM} ${OBJECTDIR}/setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/setup.o.d" -o ${OBJECTDIR}/setup.o setup.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mutex.o: mutex.c  .generated_files/flags/BOOTAPP/bdcbba934065fbe466813498e8b0aa19f34b574a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mutex.o.d 
	@${RM} ${OBJECTDIR}/mutex.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/mutex.o.d" -o ${OBJECTDIR}/mutex.o mutex.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mmc.o: mmc.c  .generated_files/flags/BOOTAPP/1bd10a476770cf26c033f6794d13c7316dde1295 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc.o.d 
	@${RM} ${OBJECTDIR}/mmc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/mmc.o.d" -o ${OBJECTDIR}/mmc.o mmc.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sd_spi.o: sd_spi.c  .generated_files/flags/BOOTAPP/4d1e4033700f167a3dd8cf9659b39a019d10c814 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/sd_spi.o.d" -o ${OBJECTDIR}/sd_spi.o sd_spi.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/configurations.o: configurations.c  .generated_files/flags/BOOTAPP/d39742e054d2a4e57f75402ca6f87ef047aa94f2 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configurations.o.d 
	@${RM} ${OBJECTDIR}/configurations.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/configurations.o.d" -o ${OBJECTDIR}/configurations.o configurations.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/speedControl.o: speedControl.c  .generated_files/flags/BOOTAPP/c924504cf1787bf27139e16ea7b83cb10b0ef126 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/speedControl.o.d 
	@${RM} ${OBJECTDIR}/speedControl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/speedControl.o.d" -o ${OBJECTDIR}/speedControl.o speedControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/tcp_start.o: tcp_start.c  .generated_files/flags/BOOTAPP/ff12c5f86874bc05ea5ce8673310262e00d802d3 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_start.o.d 
	@${RM} ${OBJECTDIR}/tcp_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/tcp_start.o.d" -o ${OBJECTDIR}/tcp_start.o tcp_start.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/timeDifference.o: timeDifference.c  .generated_files/flags/BOOTAPP/4044e78fbc5004a0c251d554ec630c3f9f51fb5 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timeDifference.o.d 
	@${RM} ${OBJECTDIR}/timeDifference.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/timeDifference.o.d" -o ${OBJECTDIR}/timeDifference.o timeDifference.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/wrapper.o: wrapper.c  .generated_files/flags/BOOTAPP/e13031b9260bf24842c5e18773b9cef1c876f6fb .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wrapper.o.d 
	@${RM} ${OBJECTDIR}/wrapper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/wrapper.o.d" -o ${OBJECTDIR}/wrapper.o wrapper.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/analogSensor10bit.o: analogSensor10bit.c  .generated_files/flags/BOOTAPP/64bd71b5f4a280bff14cccc3eaff6befa9874bba .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o.d 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/analogSensor10bit.o.d" -o ${OBJECTDIR}/analogSensor10bit.o analogSensor10bit.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/analogToPhysical.o: analogToPhysical.c  .generated_files/flags/BOOTAPP/c7123b1ef861949a98e587ed1672d0f364f1de56 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogToPhysical.o.d 
	@${RM} ${OBJECTDIR}/analogToPhysical.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/analogToPhysical.o.d" -o ${OBJECTDIR}/analogToPhysical.o analogToPhysical.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buzzer.o: buzzer.c  .generated_files/flags/BOOTAPP/5704feb189aab39fae9b57e30a113c29e336c88 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/buzzer.o.d" -o ${OBJECTDIR}/buzzer.o buzzer.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/common.o: common.c  .generated_files/flags/BOOTAPP/473eea112b3680c378fbfdec95f1b3a808d80794 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/common.o.d 
	@${RM} ${OBJECTDIR}/common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/common.o.d" -o ${OBJECTDIR}/common.o common.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/display.o: display.c  .generated_files/flags/BOOTAPP/93550f2b535d26cc2bf7baef7ca1721d0b24e22a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/display.o.d" -o ${OBJECTDIR}/display.o display.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/melacs_spi.o: melacs_spi.c  .generated_files/flags/BOOTAPP/fb9344e170ea1a5167917a5a3d2a1aa9819b2ea .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/melacs_spi.o.d 
	@${RM} ${OBJECTDIR}/melacs_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/melacs_spi.o.d" -o ${OBJECTDIR}/melacs_spi.o melacs_spi.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/onBoardADC.o: onBoardADC.c  .generated_files/flags/BOOTAPP/ae8fd711f43f8805e3f96898955e468ea38aa6e1 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardADC.o.d 
	@${RM} ${OBJECTDIR}/onBoardADC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/onBoardADC.o.d" -o ${OBJECTDIR}/onBoardADC.o onBoardADC.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/onBoardRTCC.o: onBoardRTCC.c  .generated_files/flags/BOOTAPP/83163afaf4a808bac2a62a74ffa16a311a97bb3f .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o.d 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/onBoardRTCC.o.d" -o ${OBJECTDIR}/onBoardRTCC.o onBoardRTCC.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/readConfig.o: readConfig.c  .generated_files/flags/BOOTAPP/7ecf5f7c512aff695f8c586f50ee41958807561c .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/readConfig.o.d 
	@${RM} ${OBJECTDIR}/readConfig.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/readConfig.o.d" -o ${OBJECTDIR}/readConfig.o readConfig.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorValueConvertion.o: sensorValueConvertion.c  .generated_files/flags/BOOTAPP/7429ed58db35c58bbaef7746829a6312c1d580f .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o.d 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/sensorValueConvertion.o.d" -o ${OBJECTDIR}/sensorValueConvertion.o sensorValueConvertion.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensors.o: sensors.c  .generated_files/flags/BOOTAPP/d5fbd8e3c724f3469fdb362149db75a5eeaeaa2d .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensors.o.d 
	@${RM} ${OBJECTDIR}/sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/sensors.o.d" -o ${OBJECTDIR}/sensors.o sensors.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/firmwareRecoveryUpdate.o: firmwareRecoveryUpdate.c  .generated_files/flags/BOOTAPP/117dcb50439b42f084ecddec1434c43347315701 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/firmwareRecoveryUpdate.o.d 
	@${RM} ${OBJECTDIR}/firmwareRecoveryUpdate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/firmwareRecoveryUpdate.o.d" -o ${OBJECTDIR}/firmwareRecoveryUpdate.o firmwareRecoveryUpdate.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/hBridge.o: hBridge.c  .generated_files/flags/BOOTAPP/7ce0f2d6a9f2658693bb3ab3dfcd7d7738e238da .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/hBridge.o.d" -o ${OBJECTDIR}/hBridge.o hBridge.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/logRun.o: logRun.c  .generated_files/flags/BOOTAPP/9648af41c4808c3b33cbc19c9ddd2750e76bd46d .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/logRun.o.d 
	@${RM} ${OBJECTDIR}/logRun.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/logRun.o.d" -o ${OBJECTDIR}/logRun.o logRun.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb_composite.o: usb_composite.c  .generated_files/flags/BOOTAPP/3e6aa0ce703299aaf243dc77598d1c21c2bc56e8 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_composite.o.d 
	@${RM} ${OBJECTDIR}/usb_composite.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/usb_composite.o.d" -o ${OBJECTDIR}/usb_composite.o usb_composite.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/threeWayValve.o: threeWayValve.c  .generated_files/flags/BOOTAPP/1c2c6ecea4d6e109e5362a18494e1009043ba1b1 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/threeWayValve.o.d 
	@${RM} ${OBJECTDIR}/threeWayValve.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/threeWayValve.o.d" -o ${OBJECTDIR}/threeWayValve.o threeWayValve.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/BOOTAPP/afcfa6474d37a50c8f99226c892883c247f31179 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/alarmStrings.o: alarmStrings.c  .generated_files/flags/BOOTAPP/9d6c73fa82b2291502b13dee3f75dbea1e53621 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/alarmStrings.o.d 
	@${RM} ${OBJECTDIR}/alarmStrings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/alarmStrings.o.d" -o ${OBJECTDIR}/alarmStrings.o alarmStrings.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/modbus.o: modbus.c  .generated_files/flags/BOOTAPP/c243860575da743a08d2b6f06776074f2092c14a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/modbus.o.d 
	@${RM} ${OBJECTDIR}/modbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/modbus.o.d" -o ${OBJECTDIR}/modbus.o modbus.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/delay.o: delay.c  .generated_files/flags/BOOTAPP/f0350b285f341d683f327fe3e38ef4505044bb68 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/delay.o.d 
	@${RM} ${OBJECTDIR}/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/delay.o.d" -o ${OBJECTDIR}/delay.o delay.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/checksum.o: checksum.c  .generated_files/flags/BOOTAPP/eb4e924e735af46ef70870660e92c956ca59799 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/checksum.o.d 
	@${RM} ${OBJECTDIR}/checksum.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/checksum.o.d" -o ${OBJECTDIR}/checksum.o checksum.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/modbus_client.o: modbus_client.c  .generated_files/flags/BOOTAPP/ced01f908924e4d5179c577fdcfa442e36012811 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/modbus_client.o.d 
	@${RM} ${OBJECTDIR}/modbus_client.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/modbus_client.o.d" -o ${OBJECTDIR}/modbus_client.o modbus_client.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/BOOTAPP/4742ad549a26d585c350c5b3936f2d98d5312f9a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/uart.o.d" -o ${OBJECTDIR}/uart.o uart.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/tcpserverstream.o: tcpserverstream.c  .generated_files/flags/BOOTAPP/6b5008419d093a93c1cff4964c86673fb53e9a74 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcpserverstream.o.d 
	@${RM} ${OBJECTDIR}/tcpserverstream.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/tcpserverstream.o.d" -o ${OBJECTDIR}/tcpserverstream.o tcpserverstream.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ether.o: ether.c  .generated_files/flags/BOOTAPP/7053891e4cefc53a6a5c860e2f1dcc5bfc7d4011 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ether.o.d 
	@${RM} ${OBJECTDIR}/ether.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/ether.o.d" -o ${OBJECTDIR}/ether.o ether.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/queuehandler.o: queuehandler.c  .generated_files/flags/BOOTAPP/a54886d6d8fad16b57825224d1577041d989d95f .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queuehandler.o.d 
	@${RM} ${OBJECTDIR}/queuehandler.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/queuehandler.o.d" -o ${OBJECTDIR}/queuehandler.o queuehandler.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/oemGSM.o: oemGSM.c  .generated_files/flags/BOOTAPP/3ec8b7685d49e70f8002eae0d5da983d2c13a487 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemGSM.o.d 
	@${RM} ${OBJECTDIR}/oemGSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemGSM.o.d" -o ${OBJECTDIR}/oemGSM.o oemGSM.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemInputAcquisition.o: oemInputAcquisition.c  .generated_files/flags/BOOTAPP/8c5c341e52bc0d665cb118b2409c4b9f7a23882c .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o.d 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemInputAcquisition.o.d" -o ${OBJECTDIR}/oemInputAcquisition.o oemInputAcquisition.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemInputAveraging.o: oemInputAveraging.c  .generated_files/flags/BOOTAPP/2e125a14a5d2dc6c3cfa0e5d47f9370869561940 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o.d 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemInputAveraging.o.d" -o ${OBJECTDIR}/oemInputAveraging.o oemInputAveraging.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemLog.o: oemLog.c  .generated_files/flags/BOOTAPP/db940dea4c79236b3b9c8542734bd15c655041b5 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemLog.o.d 
	@${RM} ${OBJECTDIR}/oemLog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemLog.o.d" -o ${OBJECTDIR}/oemLog.o oemLog.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemMain.o: oemMain.c  .generated_files/flags/BOOTAPP/7751aaa3ea30da2ff128a8113960a250cc3fc42 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemMain.o.d 
	@${RM} ${OBJECTDIR}/oemMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemMain.o.d" -o ${OBJECTDIR}/oemMain.o oemMain.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemOutputControl.o: oemOutputControl.c  .generated_files/flags/BOOTAPP/3a5a268306c9963d008862f712a3dab4f9010c38 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemOutputControl.o.d 
	@${RM} ${OBJECTDIR}/oemOutputControl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemOutputControl.o.d" -o ${OBJECTDIR}/oemOutputControl.o oemOutputControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemSaveReadParameter.o: oemSaveReadParameter.c  .generated_files/flags/BOOTAPP/3ac48ca80a8a566a9e1d24bb3b7630dbcc8bc0fd .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o.d 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemSaveReadParameter.o.d" -o ${OBJECTDIR}/oemSaveReadParameter.o oemSaveReadParameter.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemSendRecvUsb.o: oemSendRecvUsb.c  .generated_files/flags/BOOTAPP/7b4f36c291cbcdc685dc33f35b0b60ec285ed561 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o.d 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemSendRecvUsb.o.d" -o ${OBJECTDIR}/oemSendRecvUsb.o oemSendRecvUsb.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemCalculations.o: oemCalculations.c  .generated_files/flags/BOOTAPP/cda6f271660c4f0276a62007e04e50d18498025a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemCalculations.o.d 
	@${RM} ${OBJECTDIR}/oemCalculations.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemCalculations.o.d" -o ${OBJECTDIR}/oemCalculations.o oemCalculations.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemDisplay.o: oemDisplay.c  .generated_files/flags/BOOTAPP/8cae046672a38fde01e038c0cf2b1fcee339c374 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemDisplay.o.d 
	@${RM} ${OBJECTDIR}/oemDisplay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemDisplay.o.d" -o ${OBJECTDIR}/oemDisplay.o oemDisplay.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemFunctions.o: oemFunctions.c  .generated_files/flags/BOOTAPP/ae44d80d4087d377616de70a199d7f6c6cd7800 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemFunctions.o.d 
	@${RM} ${OBJECTDIR}/oemFunctions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemFunctions.o.d" -o ${OBJECTDIR}/oemFunctions.o oemFunctions.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/oemMainThread.o: oemMainThread.c  .generated_files/flags/BOOTAPP/2aa16fc3ba535f3edf47b60dedb7ab1da051fc9d .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemMainThread.o.d 
	@${RM} ${OBJECTDIR}/oemMainThread.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/oemMainThread.o.d" -o ${OBJECTDIR}/oemMainThread.o oemMainThread.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/malloc.o: malloc.c  .generated_files/flags/BOOTAPP/c656dd0c16cdd83960c5bacab843e61c5a2a1ec0 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/malloc.o.d 
	@${RM} ${OBJECTDIR}/malloc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/malloc.o.d" -o ${OBJECTDIR}/malloc.o malloc.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/setup.o: setup.c  .generated_files/flags/BOOTAPP/abdcfed4b92c5cd345ad4901ee19e1bebfab7f24 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/setup.o.d 
	@${RM} ${OBJECTDIR}/setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/setup.o.d" -o ${OBJECTDIR}/setup.o setup.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mutex.o: mutex.c  .generated_files/flags/BOOTAPP/a2f5e8de7bf54101dd0a7beaeef18d7fe50ff69d .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mutex.o.d 
	@${RM} ${OBJECTDIR}/mutex.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/mutex.o.d" -o ${OBJECTDIR}/mutex.o mutex.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/mmc.o: mmc.c  .generated_files/flags/BOOTAPP/24fcec38b8f13e158df0ff805aeba40a5a96dbc9 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc.o.d 
	@${RM} ${OBJECTDIR}/mmc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/mmc.o.d" -o ${OBJECTDIR}/mmc.o mmc.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sd_spi.o: sd_spi.c  .generated_files/flags/BOOTAPP/7ae4d54d486645e73e51b1262210b815e35410b1 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/sd_spi.o.d" -o ${OBJECTDIR}/sd_spi.o sd_spi.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/configurations.o: configurations.c  .generated_files/flags/BOOTAPP/85a78f7f6a6b07004d072eeb0a65848d31112f20 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configurations.o.d 
	@${RM} ${OBJECTDIR}/configurations.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/configurations.o.d" -o ${OBJECTDIR}/configurations.o configurations.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/speedControl.o: speedControl.c  .generated_files/flags/BOOTAPP/109672071d6c8d7578df86dc2406884e19799e6 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/speedControl.o.d 
	@${RM} ${OBJECTDIR}/speedControl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/speedControl.o.d" -o ${OBJECTDIR}/speedControl.o speedControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/tcp_start.o: tcp_start.c  .generated_files/flags/BOOTAPP/783e4a9e3a9ee74a8e886ed12fe609aa375410f4 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_start.o.d 
	@${RM} ${OBJECTDIR}/tcp_start.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/tcp_start.o.d" -o ${OBJECTDIR}/tcp_start.o tcp_start.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/timeDifference.o: timeDifference.c  .generated_files/flags/BOOTAPP/c3a5a012fffc9f856e1c1c089bdbccf93bc906d8 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timeDifference.o.d 
	@${RM} ${OBJECTDIR}/timeDifference.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/timeDifference.o.d" -o ${OBJECTDIR}/timeDifference.o timeDifference.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/wrapper.o: wrapper.c  .generated_files/flags/BOOTAPP/a4d821b77b2879dd08d87717164c8492b3d41dad .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wrapper.o.d 
	@${RM} ${OBJECTDIR}/wrapper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/wrapper.o.d" -o ${OBJECTDIR}/wrapper.o wrapper.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/analogSensor10bit.o: analogSensor10bit.c  .generated_files/flags/BOOTAPP/f1de22b3fa7bbd135e202882a4f567740c401d99 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o.d 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/analogSensor10bit.o.d" -o ${OBJECTDIR}/analogSensor10bit.o analogSensor10bit.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/analogToPhysical.o: analogToPhysical.c  .generated_files/flags/BOOTAPP/9f224464c41897592ba7511da0067afb0cf17345 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogToPhysical.o.d 
	@${RM} ${OBJECTDIR}/analogToPhysical.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/analogToPhysical.o.d" -o ${OBJECTDIR}/analogToPhysical.o analogToPhysical.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/buzzer.o: buzzer.c  .generated_files/flags/BOOTAPP/7cd9a7ad7de1ce6006e749024b4479517ac16794 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/buzzer.o.d" -o ${OBJECTDIR}/buzzer.o buzzer.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/common.o: common.c  .generated_files/flags/BOOTAPP/7228998c343269eaa7dd95d9fd17a9fb1f6dd195 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/common.o.d 
	@${RM} ${OBJECTDIR}/common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/common.o.d" -o ${OBJECTDIR}/common.o common.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/display.o: display.c  .generated_files/flags/BOOTAPP/2f140a30576f933e80ae5b0a69d08feed581f0d3 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/display.o.d" -o ${OBJECTDIR}/display.o display.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/melacs_spi.o: melacs_spi.c  .generated_files/flags/BOOTAPP/63c3eae023ac277c38cc9ab7fcb6a15f1591fef .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/melacs_spi.o.d 
	@${RM} ${OBJECTDIR}/melacs_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/melacs_spi.o.d" -o ${OBJECTDIR}/melacs_spi.o melacs_spi.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/onBoardADC.o: onBoardADC.c  .generated_files/flags/BOOTAPP/b01d38f0dae5efbf238c18f5fa3fdf2badc192dc .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardADC.o.d 
	@${RM} ${OBJECTDIR}/onBoardADC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/onBoardADC.o.d" -o ${OBJECTDIR}/onBoardADC.o onBoardADC.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/onBoardRTCC.o: onBoardRTCC.c  .generated_files/flags/BOOTAPP/ca86b3b969feff73daf605293862259044ceca0a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o.d 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/onBoardRTCC.o.d" -o ${OBJECTDIR}/onBoardRTCC.o onBoardRTCC.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/readConfig.o: readConfig.c  .generated_files/flags/BOOTAPP/1673581c1292a43c8cacdde458c691f5f5facf9e .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/readConfig.o.d 
	@${RM} ${OBJECTDIR}/readConfig.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/readConfig.o.d" -o ${OBJECTDIR}/readConfig.o readConfig.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorValueConvertion.o: sensorValueConvertion.c  .generated_files/flags/BOOTAPP/c7ee6b8623b8b16876810020329e3e460042ef11 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o.d 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/sensorValueConvertion.o.d" -o ${OBJECTDIR}/sensorValueConvertion.o sensorValueConvertion.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensors.o: sensors.c  .generated_files/flags/BOOTAPP/d0a4a7328f53f442ff0cf80ca8ccaaf4fafc719d .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensors.o.d 
	@${RM} ${OBJECTDIR}/sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/sensors.o.d" -o ${OBJECTDIR}/sensors.o sensors.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/firmwareRecoveryUpdate.o: firmwareRecoveryUpdate.c  .generated_files/flags/BOOTAPP/9a22be3c4d3b030a24dd89efc5bcc215358d399e .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/firmwareRecoveryUpdate.o.d 
	@${RM} ${OBJECTDIR}/firmwareRecoveryUpdate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/firmwareRecoveryUpdate.o.d" -o ${OBJECTDIR}/firmwareRecoveryUpdate.o firmwareRecoveryUpdate.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/hBridge.o: hBridge.c  .generated_files/flags/BOOTAPP/ebdf803f90024233ba884e048f5b528a67123490 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/hBridge.o.d" -o ${OBJECTDIR}/hBridge.o hBridge.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/logRun.o: logRun.c  .generated_files/flags/BOOTAPP/995bce882ded5ac2cb28d1b441bdbb2d124df00c .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/logRun.o.d 
	@${RM} ${OBJECTDIR}/logRun.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/logRun.o.d" -o ${OBJECTDIR}/logRun.o logRun.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb_composite.o: usb_composite.c  .generated_files/flags/BOOTAPP/4ee90083a2ed4032269430e801a1bae57941e0a .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_composite.o.d 
	@${RM} ${OBJECTDIR}/usb_composite.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/usb_composite.o.d" -o ${OBJECTDIR}/usb_composite.o usb_composite.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/threeWayValve.o: threeWayValve.c  .generated_files/flags/BOOTAPP/f61bd530f96b6e1e2f07ef2502f16836f2faa71e .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/threeWayValve.o.d 
	@${RM} ${OBJECTDIR}/threeWayValve.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/threeWayValve.o.d" -o ${OBJECTDIR}/threeWayValve.o threeWayValve.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/BOOTAPP/4bf941c9eb7456795ff7cdc36ceae14348d148fe .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/alarmStrings.o: alarmStrings.c  .generated_files/flags/BOOTAPP/20826ceb2ef972d7e90034d25905eb57667c9416 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/alarmStrings.o.d 
	@${RM} ${OBJECTDIR}/alarmStrings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/alarmStrings.o.d" -o ${OBJECTDIR}/alarmStrings.o alarmStrings.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/modbus.o: modbus.c  .generated_files/flags/BOOTAPP/f143c7a831bc3b5573528b8aea6f7c143104036 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/modbus.o.d 
	@${RM} ${OBJECTDIR}/modbus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/modbus.o.d" -o ${OBJECTDIR}/modbus.o modbus.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/delay.o: delay.c  .generated_files/flags/BOOTAPP/43d41a16529fc81ff80f0e1edba6f2bc9debf6d3 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/delay.o.d 
	@${RM} ${OBJECTDIR}/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/delay.o.d" -o ${OBJECTDIR}/delay.o delay.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/checksum.o: checksum.c  .generated_files/flags/BOOTAPP/3e8d0f11b9ae1d513423a323c13caea624091a22 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/checksum.o.d 
	@${RM} ${OBJECTDIR}/checksum.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/checksum.o.d" -o ${OBJECTDIR}/checksum.o checksum.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/modbus_client.o: modbus_client.c  .generated_files/flags/BOOTAPP/9308e1ed76150237fd56bb27e6f820ff209dcaff .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/modbus_client.o.d 
	@${RM} ${OBJECTDIR}/modbus_client.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/modbus_client.o.d" -o ${OBJECTDIR}/modbus_client.o modbus_client.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/BOOTAPP/b6f668aa9718c4a2d4cf3115e49a0f1e37c26ce9 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/uart.o.d" -o ${OBJECTDIR}/uart.o uart.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/tcpserverstream.o: tcpserverstream.c  .generated_files/flags/BOOTAPP/bf5cb2f91ffb07edfe5a84dc29167146eca30c59 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcpserverstream.o.d 
	@${RM} ${OBJECTDIR}/tcpserverstream.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/tcpserverstream.o.d" -o ${OBJECTDIR}/tcpserverstream.o tcpserverstream.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ether.o: ether.c  .generated_files/flags/BOOTAPP/16e87cd1f5a7c53f39002990951777a2b6f2bb6d .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ether.o.d 
	@${RM} ${OBJECTDIR}/ether.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/ether.o.d" -o ${OBJECTDIR}/ether.o ether.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/queuehandler.o: queuehandler.c  .generated_files/flags/BOOTAPP/61d01666ccc776b790aed6067416ee56c6713123 .generated_files/flags/BOOTAPP/87483c345429186c5999dcd95309ab66555f8ca8
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queuehandler.o.d 
	@${RM} ${OBJECTDIR}/queuehandler.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MP -MMD -MF "${OBJECTDIR}/queuehandler.o.d" -o ${OBJECTDIR}/queuehandler.o queuehandler.c    -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -msmart-io=0 -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../servers/fsys-fatfs/fsys-fatfs.a ../../iolib/iolib.a ../../servers/usb/usb_server/usb_server.a ../../servers/usb/device/usbd_core/usbd_core.a ../../servers/usb/device/usbd_pic32x_port/usbd_pic32x_port.a ../../servers/_ipv6/tcp6/ENC424J600_v6/ENC424J600_v6.a ../../servers/_ipv6/tcp6/server6/tcp_dual.a ../../servers/usb/device/usbd_msc_driver/usbd_msc_driver.a ../../servers/usb/device/usbd_cdc_serial_driver/usbd_cdc_serial_driver.a ../../kernel/Unison.a ../../servers/tty/tty.a ../../stdio/stdiolib.a  app_32MX795F512L.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\servers\fsys-fatfs\fsys-fatfs.a ..\..\iolib\iolib.a ..\..\servers\usb\usb_server\usb_server.a ..\..\servers\usb\device\usbd_core\usbd_core.a ..\..\servers\usb\device\usbd_pic32x_port\usbd_pic32x_port.a ..\..\servers\_ipv6\tcp6\ENC424J600_v6\ENC424J600_v6.a ..\..\servers\_ipv6\tcp6\server6\tcp_dual.a ..\..\servers\usb\device\usbd_msc_driver\usbd_msc_driver.a ..\..\servers\usb\device\usbd_cdc_serial_driver\usbd_cdc_serial_driver.a ..\..\kernel\Unison.a ..\..\servers\tty\tty.a ..\..\stdio\stdiolib.a      -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--cref,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Application_OEM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../servers/fsys-fatfs/fsys-fatfs.a ../../iolib/iolib.a ../../servers/usb/usb_server/usb_server.a ../../servers/usb/device/usbd_core/usbd_core.a ../../servers/usb/device/usbd_pic32x_port/usbd_pic32x_port.a ../../servers/_ipv6/tcp6/ENC424J600_v6/ENC424J600_v6.a ../../servers/_ipv6/tcp6/server6/tcp_dual.a ../../servers/usb/device/usbd_msc_driver/usbd_msc_driver.a ../../servers/usb/device/usbd_cdc_serial_driver/usbd_cdc_serial_driver.a ../../kernel/Unison.a ../../servers/tty/tty.a ../../stdio/stdiolib.a app_32MX795F512L.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Application_OEM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\servers\fsys-fatfs\fsys-fatfs.a ..\..\iolib\iolib.a ..\..\servers\usb\usb_server\usb_server.a ..\..\servers\usb\device\usbd_core\usbd_core.a ..\..\servers\usb\device\usbd_pic32x_port\usbd_pic32x_port.a ..\..\servers\_ipv6\tcp6\ENC424J600_v6\ENC424J600_v6.a ..\..\servers\_ipv6\tcp6\server6\tcp_dual.a ..\..\servers\usb\device\usbd_msc_driver\usbd_msc_driver.a ..\..\servers\usb\device\usbd_cdc_serial_driver\usbd_cdc_serial_driver.a ..\..\kernel\Unison.a ..\..\servers\tty\tty.a ..\..\stdio\stdiolib.a      -DXPRJ_BOOTAPP=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--cref,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Application_OEM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
