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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/InresolMain_20Jan2017.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/InresolMain_20Jan2017.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=oemMain.c oemDisplay.c oemLog.c oemGSM.c oemFunctions.c oemOutputControl.c oemInputAcquisition.c oemCalculations.c oemInputAveraging.c oemSaveReadParameter.c oemSendRecvUsb.c portableInputAcquisition.c portableInputAveraging.c portableCalculations.c portableDisplay.c portableGSM.c portableLog.c portableMain.c portableOutputControl.c portableSaveReadParameter.c portableSendRecvUsb.c appAutomation.c appAutomation1.c appEngineLongRun.c applicationGeneral.c applicationGeneral1.c appPullDownTest.c appFeederTest.c appPelletFeed.c appSipMotorControl.c appOnlySensorRead.c appStatorRead.c appAutomationEthernet2.c appAutomationEthernet1.c appAutomationEthernet.c appTestRigMelacs2.c appTestRigMelacs1.c appTestRigMelac2Ethernet_2.c appTestRigMelac2Ethernet_1.c appTestRigMelac1Ethernet_1.c appTestRig1.c appTestRig.c appPulseGen.c appInjectorTest.c appValveControl.c appAutomation2.c appOEM_1.c appAutomation4.c appAutomation4USB.c appAutomation4USB_1.c appAutomation5USB_1.c appAutomation5USB_2.c appAutomation5USB_3.c appAutomation5USB_5.c appAutomation3.c appCurrentSensing.c appCurrentLimiter.c appAutomation3Ethernet.c appTestRigMelac1USB.c.c appAutomation5USB_BurstDelayAdded.c appAutomation5USB_BeforeFeedRamp.c appAutomation5USB_BeforeFanRamp_SlowDose.c appAutomation5USB_BeforeSetPressureCheck.c appTestRigMelac1Ethernet_2.c appTestRigMelac2Ethernet_3.c appTestRigMelac2Ethernet_4.c appGSMtest.c appSpiSlave.c appSpiMaster.c appOEM.c appAutomationWrapped.c wrapperUnitTest.c appTestRigMelac1Ethernet.c appTestRigMelac2Ethernet.c appEmpty.c appAutomation5USB.c appAutomationEthernetandSD.c appPeakEcoEthernet.c appPressureCurveCalibration.c appPressureFillRelease.c GSMFiles/board.c GSMFiles/cloudindustries_api.c GSMFiles/fifo_buffer.c GSMFiles/ublox_lisa_u230.c main.c malloc.c sd_spi.c mmc.c logRun.c display.c common.c gsm_main.c configurations.c onBoardADC.c onBoardRTCC.c sensors.c sensorValueConvertion.c readConfig.c melacs_spi.c buzzer.c setup.c ../_startup_ESK_EXP16/boot_app/appheader.c firmwareRecoveryUpdate.c wrapper.c tcp_start.c tcp_server.c mutex.c speedControl.c threeWayValve.c hBridge.c analogToPhysical.c timeDifference.c analogSensor10bit.c usb_composite.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/oemMain.o ${OBJECTDIR}/oemDisplay.o ${OBJECTDIR}/oemLog.o ${OBJECTDIR}/oemGSM.o ${OBJECTDIR}/oemFunctions.o ${OBJECTDIR}/oemOutputControl.o ${OBJECTDIR}/oemInputAcquisition.o ${OBJECTDIR}/oemCalculations.o ${OBJECTDIR}/oemInputAveraging.o ${OBJECTDIR}/oemSaveReadParameter.o ${OBJECTDIR}/oemSendRecvUsb.o ${OBJECTDIR}/portableInputAcquisition.o ${OBJECTDIR}/portableInputAveraging.o ${OBJECTDIR}/portableCalculations.o ${OBJECTDIR}/portableDisplay.o ${OBJECTDIR}/portableGSM.o ${OBJECTDIR}/portableLog.o ${OBJECTDIR}/portableMain.o ${OBJECTDIR}/portableOutputControl.o ${OBJECTDIR}/portableSaveReadParameter.o ${OBJECTDIR}/portableSendRecvUsb.o ${OBJECTDIR}/appAutomation.o ${OBJECTDIR}/appAutomation1.o ${OBJECTDIR}/appEngineLongRun.o ${OBJECTDIR}/applicationGeneral.o ${OBJECTDIR}/applicationGeneral1.o ${OBJECTDIR}/appPullDownTest.o ${OBJECTDIR}/appFeederTest.o ${OBJECTDIR}/appPelletFeed.o ${OBJECTDIR}/appSipMotorControl.o ${OBJECTDIR}/appOnlySensorRead.o ${OBJECTDIR}/appStatorRead.o ${OBJECTDIR}/appAutomationEthernet2.o ${OBJECTDIR}/appAutomationEthernet1.o ${OBJECTDIR}/appAutomationEthernet.o ${OBJECTDIR}/appTestRigMelacs2.o ${OBJECTDIR}/appTestRigMelacs1.o ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o ${OBJECTDIR}/appTestRig1.o ${OBJECTDIR}/appTestRig.o ${OBJECTDIR}/appPulseGen.o ${OBJECTDIR}/appInjectorTest.o ${OBJECTDIR}/appValveControl.o ${OBJECTDIR}/appAutomation2.o ${OBJECTDIR}/appOEM_1.o ${OBJECTDIR}/appAutomation4.o ${OBJECTDIR}/appAutomation4USB.o ${OBJECTDIR}/appAutomation4USB_1.o ${OBJECTDIR}/appAutomation5USB_1.o ${OBJECTDIR}/appAutomation5USB_2.o ${OBJECTDIR}/appAutomation5USB_3.o ${OBJECTDIR}/appAutomation5USB_5.o ${OBJECTDIR}/appAutomation3.o ${OBJECTDIR}/appCurrentSensing.o ${OBJECTDIR}/appCurrentLimiter.o ${OBJECTDIR}/appAutomation3Ethernet.o ${OBJECTDIR}/appTestRigMelac1USB.c.o ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o ${OBJECTDIR}/appGSMtest.o ${OBJECTDIR}/appSpiSlave.o ${OBJECTDIR}/appSpiMaster.o ${OBJECTDIR}/appOEM.o ${OBJECTDIR}/appAutomationWrapped.o ${OBJECTDIR}/wrapperUnitTest.o ${OBJECTDIR}/appTestRigMelac1Ethernet.o ${OBJECTDIR}/appTestRigMelac2Ethernet.o ${OBJECTDIR}/appEmpty.o ${OBJECTDIR}/appAutomation5USB.o ${OBJECTDIR}/appAutomationEthernetandSD.o ${OBJECTDIR}/appPeakEcoEthernet.o ${OBJECTDIR}/appPressureCurveCalibration.o ${OBJECTDIR}/appPressureFillRelease.o ${OBJECTDIR}/GSMFiles/board.o ${OBJECTDIR}/GSMFiles/cloudindustries_api.o ${OBJECTDIR}/GSMFiles/fifo_buffer.o ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o ${OBJECTDIR}/main.o ${OBJECTDIR}/malloc.o ${OBJECTDIR}/sd_spi.o ${OBJECTDIR}/mmc.o ${OBJECTDIR}/logRun.o ${OBJECTDIR}/display.o ${OBJECTDIR}/common.o ${OBJECTDIR}/gsm_main.o ${OBJECTDIR}/configurations.o ${OBJECTDIR}/onBoardADC.o ${OBJECTDIR}/onBoardRTCC.o ${OBJECTDIR}/sensors.o ${OBJECTDIR}/sensorValueConvertion.o ${OBJECTDIR}/readConfig.o ${OBJECTDIR}/melacs_spi.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/setup.o ${OBJECTDIR}/_ext/893916629/appheader.o ${OBJECTDIR}/firmwareRecoveryUpdate.o ${OBJECTDIR}/wrapper.o ${OBJECTDIR}/tcp_start.o ${OBJECTDIR}/tcp_server.o ${OBJECTDIR}/mutex.o ${OBJECTDIR}/speedControl.o ${OBJECTDIR}/threeWayValve.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/analogToPhysical.o ${OBJECTDIR}/timeDifference.o ${OBJECTDIR}/analogSensor10bit.o ${OBJECTDIR}/usb_composite.o
POSSIBLE_DEPFILES=${OBJECTDIR}/oemMain.o.d ${OBJECTDIR}/oemDisplay.o.d ${OBJECTDIR}/oemLog.o.d ${OBJECTDIR}/oemGSM.o.d ${OBJECTDIR}/oemFunctions.o.d ${OBJECTDIR}/oemOutputControl.o.d ${OBJECTDIR}/oemInputAcquisition.o.d ${OBJECTDIR}/oemCalculations.o.d ${OBJECTDIR}/oemInputAveraging.o.d ${OBJECTDIR}/oemSaveReadParameter.o.d ${OBJECTDIR}/oemSendRecvUsb.o.d ${OBJECTDIR}/portableInputAcquisition.o.d ${OBJECTDIR}/portableInputAveraging.o.d ${OBJECTDIR}/portableCalculations.o.d ${OBJECTDIR}/portableDisplay.o.d ${OBJECTDIR}/portableGSM.o.d ${OBJECTDIR}/portableLog.o.d ${OBJECTDIR}/portableMain.o.d ${OBJECTDIR}/portableOutputControl.o.d ${OBJECTDIR}/portableSaveReadParameter.o.d ${OBJECTDIR}/portableSendRecvUsb.o.d ${OBJECTDIR}/appAutomation.o.d ${OBJECTDIR}/appAutomation1.o.d ${OBJECTDIR}/appEngineLongRun.o.d ${OBJECTDIR}/applicationGeneral.o.d ${OBJECTDIR}/applicationGeneral1.o.d ${OBJECTDIR}/appPullDownTest.o.d ${OBJECTDIR}/appFeederTest.o.d ${OBJECTDIR}/appPelletFeed.o.d ${OBJECTDIR}/appSipMotorControl.o.d ${OBJECTDIR}/appOnlySensorRead.o.d ${OBJECTDIR}/appStatorRead.o.d ${OBJECTDIR}/appAutomationEthernet2.o.d ${OBJECTDIR}/appAutomationEthernet1.o.d ${OBJECTDIR}/appAutomationEthernet.o.d ${OBJECTDIR}/appTestRigMelacs2.o.d ${OBJECTDIR}/appTestRigMelacs1.o.d ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o.d ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o.d ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o.d ${OBJECTDIR}/appTestRig1.o.d ${OBJECTDIR}/appTestRig.o.d ${OBJECTDIR}/appPulseGen.o.d ${OBJECTDIR}/appInjectorTest.o.d ${OBJECTDIR}/appValveControl.o.d ${OBJECTDIR}/appAutomation2.o.d ${OBJECTDIR}/appOEM_1.o.d ${OBJECTDIR}/appAutomation4.o.d ${OBJECTDIR}/appAutomation4USB.o.d ${OBJECTDIR}/appAutomation4USB_1.o.d ${OBJECTDIR}/appAutomation5USB_1.o.d ${OBJECTDIR}/appAutomation5USB_2.o.d ${OBJECTDIR}/appAutomation5USB_3.o.d ${OBJECTDIR}/appAutomation5USB_5.o.d ${OBJECTDIR}/appAutomation3.o.d ${OBJECTDIR}/appCurrentSensing.o.d ${OBJECTDIR}/appCurrentLimiter.o.d ${OBJECTDIR}/appAutomation3Ethernet.o.d ${OBJECTDIR}/appTestRigMelac1USB.c.o.d ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o.d ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o.d ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o.d ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o.d ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o.d ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o.d ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o.d ${OBJECTDIR}/appGSMtest.o.d ${OBJECTDIR}/appSpiSlave.o.d ${OBJECTDIR}/appSpiMaster.o.d ${OBJECTDIR}/appOEM.o.d ${OBJECTDIR}/appAutomationWrapped.o.d ${OBJECTDIR}/wrapperUnitTest.o.d ${OBJECTDIR}/appTestRigMelac1Ethernet.o.d ${OBJECTDIR}/appTestRigMelac2Ethernet.o.d ${OBJECTDIR}/appEmpty.o.d ${OBJECTDIR}/appAutomation5USB.o.d ${OBJECTDIR}/appAutomationEthernetandSD.o.d ${OBJECTDIR}/appPeakEcoEthernet.o.d ${OBJECTDIR}/appPressureCurveCalibration.o.d ${OBJECTDIR}/appPressureFillRelease.o.d ${OBJECTDIR}/GSMFiles/board.o.d ${OBJECTDIR}/GSMFiles/cloudindustries_api.o.d ${OBJECTDIR}/GSMFiles/fifo_buffer.o.d ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/malloc.o.d ${OBJECTDIR}/sd_spi.o.d ${OBJECTDIR}/mmc.o.d ${OBJECTDIR}/logRun.o.d ${OBJECTDIR}/display.o.d ${OBJECTDIR}/common.o.d ${OBJECTDIR}/gsm_main.o.d ${OBJECTDIR}/configurations.o.d ${OBJECTDIR}/onBoardADC.o.d ${OBJECTDIR}/onBoardRTCC.o.d ${OBJECTDIR}/sensors.o.d ${OBJECTDIR}/sensorValueConvertion.o.d ${OBJECTDIR}/readConfig.o.d ${OBJECTDIR}/melacs_spi.o.d ${OBJECTDIR}/buzzer.o.d ${OBJECTDIR}/setup.o.d ${OBJECTDIR}/_ext/893916629/appheader.o.d ${OBJECTDIR}/firmwareRecoveryUpdate.o.d ${OBJECTDIR}/wrapper.o.d ${OBJECTDIR}/tcp_start.o.d ${OBJECTDIR}/tcp_server.o.d ${OBJECTDIR}/mutex.o.d ${OBJECTDIR}/speedControl.o.d ${OBJECTDIR}/threeWayValve.o.d ${OBJECTDIR}/hBridge.o.d ${OBJECTDIR}/analogToPhysical.o.d ${OBJECTDIR}/timeDifference.o.d ${OBJECTDIR}/analogSensor10bit.o.d ${OBJECTDIR}/usb_composite.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/oemMain.o ${OBJECTDIR}/oemDisplay.o ${OBJECTDIR}/oemLog.o ${OBJECTDIR}/oemGSM.o ${OBJECTDIR}/oemFunctions.o ${OBJECTDIR}/oemOutputControl.o ${OBJECTDIR}/oemInputAcquisition.o ${OBJECTDIR}/oemCalculations.o ${OBJECTDIR}/oemInputAveraging.o ${OBJECTDIR}/oemSaveReadParameter.o ${OBJECTDIR}/oemSendRecvUsb.o ${OBJECTDIR}/portableInputAcquisition.o ${OBJECTDIR}/portableInputAveraging.o ${OBJECTDIR}/portableCalculations.o ${OBJECTDIR}/portableDisplay.o ${OBJECTDIR}/portableGSM.o ${OBJECTDIR}/portableLog.o ${OBJECTDIR}/portableMain.o ${OBJECTDIR}/portableOutputControl.o ${OBJECTDIR}/portableSaveReadParameter.o ${OBJECTDIR}/portableSendRecvUsb.o ${OBJECTDIR}/appAutomation.o ${OBJECTDIR}/appAutomation1.o ${OBJECTDIR}/appEngineLongRun.o ${OBJECTDIR}/applicationGeneral.o ${OBJECTDIR}/applicationGeneral1.o ${OBJECTDIR}/appPullDownTest.o ${OBJECTDIR}/appFeederTest.o ${OBJECTDIR}/appPelletFeed.o ${OBJECTDIR}/appSipMotorControl.o ${OBJECTDIR}/appOnlySensorRead.o ${OBJECTDIR}/appStatorRead.o ${OBJECTDIR}/appAutomationEthernet2.o ${OBJECTDIR}/appAutomationEthernet1.o ${OBJECTDIR}/appAutomationEthernet.o ${OBJECTDIR}/appTestRigMelacs2.o ${OBJECTDIR}/appTestRigMelacs1.o ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o ${OBJECTDIR}/appTestRig1.o ${OBJECTDIR}/appTestRig.o ${OBJECTDIR}/appPulseGen.o ${OBJECTDIR}/appInjectorTest.o ${OBJECTDIR}/appValveControl.o ${OBJECTDIR}/appAutomation2.o ${OBJECTDIR}/appOEM_1.o ${OBJECTDIR}/appAutomation4.o ${OBJECTDIR}/appAutomation4USB.o ${OBJECTDIR}/appAutomation4USB_1.o ${OBJECTDIR}/appAutomation5USB_1.o ${OBJECTDIR}/appAutomation5USB_2.o ${OBJECTDIR}/appAutomation5USB_3.o ${OBJECTDIR}/appAutomation5USB_5.o ${OBJECTDIR}/appAutomation3.o ${OBJECTDIR}/appCurrentSensing.o ${OBJECTDIR}/appCurrentLimiter.o ${OBJECTDIR}/appAutomation3Ethernet.o ${OBJECTDIR}/appTestRigMelac1USB.c.o ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o ${OBJECTDIR}/appGSMtest.o ${OBJECTDIR}/appSpiSlave.o ${OBJECTDIR}/appSpiMaster.o ${OBJECTDIR}/appOEM.o ${OBJECTDIR}/appAutomationWrapped.o ${OBJECTDIR}/wrapperUnitTest.o ${OBJECTDIR}/appTestRigMelac1Ethernet.o ${OBJECTDIR}/appTestRigMelac2Ethernet.o ${OBJECTDIR}/appEmpty.o ${OBJECTDIR}/appAutomation5USB.o ${OBJECTDIR}/appAutomationEthernetandSD.o ${OBJECTDIR}/appPeakEcoEthernet.o ${OBJECTDIR}/appPressureCurveCalibration.o ${OBJECTDIR}/appPressureFillRelease.o ${OBJECTDIR}/GSMFiles/board.o ${OBJECTDIR}/GSMFiles/cloudindustries_api.o ${OBJECTDIR}/GSMFiles/fifo_buffer.o ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o ${OBJECTDIR}/main.o ${OBJECTDIR}/malloc.o ${OBJECTDIR}/sd_spi.o ${OBJECTDIR}/mmc.o ${OBJECTDIR}/logRun.o ${OBJECTDIR}/display.o ${OBJECTDIR}/common.o ${OBJECTDIR}/gsm_main.o ${OBJECTDIR}/configurations.o ${OBJECTDIR}/onBoardADC.o ${OBJECTDIR}/onBoardRTCC.o ${OBJECTDIR}/sensors.o ${OBJECTDIR}/sensorValueConvertion.o ${OBJECTDIR}/readConfig.o ${OBJECTDIR}/melacs_spi.o ${OBJECTDIR}/buzzer.o ${OBJECTDIR}/setup.o ${OBJECTDIR}/_ext/893916629/appheader.o ${OBJECTDIR}/firmwareRecoveryUpdate.o ${OBJECTDIR}/wrapper.o ${OBJECTDIR}/tcp_start.o ${OBJECTDIR}/tcp_server.o ${OBJECTDIR}/mutex.o ${OBJECTDIR}/speedControl.o ${OBJECTDIR}/threeWayValve.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/analogToPhysical.o ${OBJECTDIR}/timeDifference.o ${OBJECTDIR}/analogSensor10bit.o ${OBJECTDIR}/usb_composite.o

# Source Files
SOURCEFILES=oemMain.c oemDisplay.c oemLog.c oemGSM.c oemFunctions.c oemOutputControl.c oemInputAcquisition.c oemCalculations.c oemInputAveraging.c oemSaveReadParameter.c oemSendRecvUsb.c portableInputAcquisition.c portableInputAveraging.c portableCalculations.c portableDisplay.c portableGSM.c portableLog.c portableMain.c portableOutputControl.c portableSaveReadParameter.c portableSendRecvUsb.c appAutomation.c appAutomation1.c appEngineLongRun.c applicationGeneral.c applicationGeneral1.c appPullDownTest.c appFeederTest.c appPelletFeed.c appSipMotorControl.c appOnlySensorRead.c appStatorRead.c appAutomationEthernet2.c appAutomationEthernet1.c appAutomationEthernet.c appTestRigMelacs2.c appTestRigMelacs1.c appTestRigMelac2Ethernet_2.c appTestRigMelac2Ethernet_1.c appTestRigMelac1Ethernet_1.c appTestRig1.c appTestRig.c appPulseGen.c appInjectorTest.c appValveControl.c appAutomation2.c appOEM_1.c appAutomation4.c appAutomation4USB.c appAutomation4USB_1.c appAutomation5USB_1.c appAutomation5USB_2.c appAutomation5USB_3.c appAutomation5USB_5.c appAutomation3.c appCurrentSensing.c appCurrentLimiter.c appAutomation3Ethernet.c appTestRigMelac1USB.c.c appAutomation5USB_BurstDelayAdded.c appAutomation5USB_BeforeFeedRamp.c appAutomation5USB_BeforeFanRamp_SlowDose.c appAutomation5USB_BeforeSetPressureCheck.c appTestRigMelac1Ethernet_2.c appTestRigMelac2Ethernet_3.c appTestRigMelac2Ethernet_4.c appGSMtest.c appSpiSlave.c appSpiMaster.c appOEM.c appAutomationWrapped.c wrapperUnitTest.c appTestRigMelac1Ethernet.c appTestRigMelac2Ethernet.c appEmpty.c appAutomation5USB.c appAutomationEthernetandSD.c appPeakEcoEthernet.c appPressureCurveCalibration.c appPressureFillRelease.c GSMFiles/board.c GSMFiles/cloudindustries_api.c GSMFiles/fifo_buffer.c GSMFiles/ublox_lisa_u230.c main.c malloc.c sd_spi.c mmc.c logRun.c display.c common.c gsm_main.c configurations.c onBoardADC.c onBoardRTCC.c sensors.c sensorValueConvertion.c readConfig.c melacs_spi.c buzzer.c setup.c ../_startup_ESK_EXP16/boot_app/appheader.c firmwareRecoveryUpdate.c wrapper.c tcp_start.c tcp_server.c mutex.c speedControl.c threeWayValve.c hBridge.c analogToPhysical.c timeDifference.c analogSensor10bit.c usb_composite.c


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
	${MAKE}  -f nbproject/Makefile-BOOTAPP.mk dist/${CND_CONF}/${IMAGE_TYPE}/InresolMain_20Jan2017.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="..\_startup_ESK_EXP16\boot_app\app_32MX795F512L.ld"
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
${OBJECTDIR}/oemMain.o: oemMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemMain.o.d 
	@${RM} ${OBJECTDIR}/oemMain.o 
	@${FIXDEPS} "${OBJECTDIR}/oemMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemMain.o.d" -o ${OBJECTDIR}/oemMain.o oemMain.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemDisplay.o: oemDisplay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemDisplay.o.d 
	@${RM} ${OBJECTDIR}/oemDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/oemDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemDisplay.o.d" -o ${OBJECTDIR}/oemDisplay.o oemDisplay.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemLog.o: oemLog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemLog.o.d 
	@${RM} ${OBJECTDIR}/oemLog.o 
	@${FIXDEPS} "${OBJECTDIR}/oemLog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemLog.o.d" -o ${OBJECTDIR}/oemLog.o oemLog.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemGSM.o: oemGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemGSM.o.d 
	@${RM} ${OBJECTDIR}/oemGSM.o 
	@${FIXDEPS} "${OBJECTDIR}/oemGSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemGSM.o.d" -o ${OBJECTDIR}/oemGSM.o oemGSM.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemFunctions.o: oemFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemFunctions.o.d 
	@${RM} ${OBJECTDIR}/oemFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/oemFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemFunctions.o.d" -o ${OBJECTDIR}/oemFunctions.o oemFunctions.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemOutputControl.o: oemOutputControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemOutputControl.o.d 
	@${RM} ${OBJECTDIR}/oemOutputControl.o 
	@${FIXDEPS} "${OBJECTDIR}/oemOutputControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemOutputControl.o.d" -o ${OBJECTDIR}/oemOutputControl.o oemOutputControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemInputAcquisition.o: oemInputAcquisition.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o.d 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o 
	@${FIXDEPS} "${OBJECTDIR}/oemInputAcquisition.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemInputAcquisition.o.d" -o ${OBJECTDIR}/oemInputAcquisition.o oemInputAcquisition.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemCalculations.o: oemCalculations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemCalculations.o.d 
	@${RM} ${OBJECTDIR}/oemCalculations.o 
	@${FIXDEPS} "${OBJECTDIR}/oemCalculations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemCalculations.o.d" -o ${OBJECTDIR}/oemCalculations.o oemCalculations.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemInputAveraging.o: oemInputAveraging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o.d 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o 
	@${FIXDEPS} "${OBJECTDIR}/oemInputAveraging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemInputAveraging.o.d" -o ${OBJECTDIR}/oemInputAveraging.o oemInputAveraging.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemSaveReadParameter.o: oemSaveReadParameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o.d 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o 
	@${FIXDEPS} "${OBJECTDIR}/oemSaveReadParameter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemSaveReadParameter.o.d" -o ${OBJECTDIR}/oemSaveReadParameter.o oemSaveReadParameter.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemSendRecvUsb.o: oemSendRecvUsb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o.d 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o 
	@${FIXDEPS} "${OBJECTDIR}/oemSendRecvUsb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemSendRecvUsb.o.d" -o ${OBJECTDIR}/oemSendRecvUsb.o oemSendRecvUsb.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableInputAcquisition.o: portableInputAcquisition.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableInputAcquisition.o.d 
	@${RM} ${OBJECTDIR}/portableInputAcquisition.o 
	@${FIXDEPS} "${OBJECTDIR}/portableInputAcquisition.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableInputAcquisition.o.d" -o ${OBJECTDIR}/portableInputAcquisition.o portableInputAcquisition.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableInputAveraging.o: portableInputAveraging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableInputAveraging.o.d 
	@${RM} ${OBJECTDIR}/portableInputAveraging.o 
	@${FIXDEPS} "${OBJECTDIR}/portableInputAveraging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableInputAveraging.o.d" -o ${OBJECTDIR}/portableInputAveraging.o portableInputAveraging.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableCalculations.o: portableCalculations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableCalculations.o.d 
	@${RM} ${OBJECTDIR}/portableCalculations.o 
	@${FIXDEPS} "${OBJECTDIR}/portableCalculations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableCalculations.o.d" -o ${OBJECTDIR}/portableCalculations.o portableCalculations.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableDisplay.o: portableDisplay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableDisplay.o.d 
	@${RM} ${OBJECTDIR}/portableDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/portableDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableDisplay.o.d" -o ${OBJECTDIR}/portableDisplay.o portableDisplay.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableGSM.o: portableGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableGSM.o.d 
	@${RM} ${OBJECTDIR}/portableGSM.o 
	@${FIXDEPS} "${OBJECTDIR}/portableGSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableGSM.o.d" -o ${OBJECTDIR}/portableGSM.o portableGSM.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableLog.o: portableLog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableLog.o.d 
	@${RM} ${OBJECTDIR}/portableLog.o 
	@${FIXDEPS} "${OBJECTDIR}/portableLog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableLog.o.d" -o ${OBJECTDIR}/portableLog.o portableLog.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableMain.o: portableMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableMain.o.d 
	@${RM} ${OBJECTDIR}/portableMain.o 
	@${FIXDEPS} "${OBJECTDIR}/portableMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableMain.o.d" -o ${OBJECTDIR}/portableMain.o portableMain.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableOutputControl.o: portableOutputControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableOutputControl.o.d 
	@${RM} ${OBJECTDIR}/portableOutputControl.o 
	@${FIXDEPS} "${OBJECTDIR}/portableOutputControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableOutputControl.o.d" -o ${OBJECTDIR}/portableOutputControl.o portableOutputControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableSaveReadParameter.o: portableSaveReadParameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableSaveReadParameter.o.d 
	@${RM} ${OBJECTDIR}/portableSaveReadParameter.o 
	@${FIXDEPS} "${OBJECTDIR}/portableSaveReadParameter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableSaveReadParameter.o.d" -o ${OBJECTDIR}/portableSaveReadParameter.o portableSaveReadParameter.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableSendRecvUsb.o: portableSendRecvUsb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableSendRecvUsb.o.d 
	@${RM} ${OBJECTDIR}/portableSendRecvUsb.o 
	@${FIXDEPS} "${OBJECTDIR}/portableSendRecvUsb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableSendRecvUsb.o.d" -o ${OBJECTDIR}/portableSendRecvUsb.o portableSendRecvUsb.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation.o: appAutomation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation.o.d 
	@${RM} ${OBJECTDIR}/appAutomation.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation.o.d" -o ${OBJECTDIR}/appAutomation.o appAutomation.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation1.o: appAutomation1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation1.o.d 
	@${RM} ${OBJECTDIR}/appAutomation1.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation1.o.d" -o ${OBJECTDIR}/appAutomation1.o appAutomation1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appEngineLongRun.o: appEngineLongRun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appEngineLongRun.o.d 
	@${RM} ${OBJECTDIR}/appEngineLongRun.o 
	@${FIXDEPS} "${OBJECTDIR}/appEngineLongRun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appEngineLongRun.o.d" -o ${OBJECTDIR}/appEngineLongRun.o appEngineLongRun.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/applicationGeneral.o: applicationGeneral.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/applicationGeneral.o.d 
	@${RM} ${OBJECTDIR}/applicationGeneral.o 
	@${FIXDEPS} "${OBJECTDIR}/applicationGeneral.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/applicationGeneral.o.d" -o ${OBJECTDIR}/applicationGeneral.o applicationGeneral.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/applicationGeneral1.o: applicationGeneral1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/applicationGeneral1.o.d 
	@${RM} ${OBJECTDIR}/applicationGeneral1.o 
	@${FIXDEPS} "${OBJECTDIR}/applicationGeneral1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/applicationGeneral1.o.d" -o ${OBJECTDIR}/applicationGeneral1.o applicationGeneral1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPullDownTest.o: appPullDownTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPullDownTest.o.d 
	@${RM} ${OBJECTDIR}/appPullDownTest.o 
	@${FIXDEPS} "${OBJECTDIR}/appPullDownTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPullDownTest.o.d" -o ${OBJECTDIR}/appPullDownTest.o appPullDownTest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appFeederTest.o: appFeederTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appFeederTest.o.d 
	@${RM} ${OBJECTDIR}/appFeederTest.o 
	@${FIXDEPS} "${OBJECTDIR}/appFeederTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appFeederTest.o.d" -o ${OBJECTDIR}/appFeederTest.o appFeederTest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPelletFeed.o: appPelletFeed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPelletFeed.o.d 
	@${RM} ${OBJECTDIR}/appPelletFeed.o 
	@${FIXDEPS} "${OBJECTDIR}/appPelletFeed.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPelletFeed.o.d" -o ${OBJECTDIR}/appPelletFeed.o appPelletFeed.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appSipMotorControl.o: appSipMotorControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appSipMotorControl.o.d 
	@${RM} ${OBJECTDIR}/appSipMotorControl.o 
	@${FIXDEPS} "${OBJECTDIR}/appSipMotorControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appSipMotorControl.o.d" -o ${OBJECTDIR}/appSipMotorControl.o appSipMotorControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appOnlySensorRead.o: appOnlySensorRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appOnlySensorRead.o.d 
	@${RM} ${OBJECTDIR}/appOnlySensorRead.o 
	@${FIXDEPS} "${OBJECTDIR}/appOnlySensorRead.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appOnlySensorRead.o.d" -o ${OBJECTDIR}/appOnlySensorRead.o appOnlySensorRead.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appStatorRead.o: appStatorRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appStatorRead.o.d 
	@${RM} ${OBJECTDIR}/appStatorRead.o 
	@${FIXDEPS} "${OBJECTDIR}/appStatorRead.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appStatorRead.o.d" -o ${OBJECTDIR}/appStatorRead.o appStatorRead.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationEthernet2.o: appAutomationEthernet2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationEthernet2.o.d 
	@${RM} ${OBJECTDIR}/appAutomationEthernet2.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationEthernet2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationEthernet2.o.d" -o ${OBJECTDIR}/appAutomationEthernet2.o appAutomationEthernet2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationEthernet1.o: appAutomationEthernet1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationEthernet1.o.d 
	@${RM} ${OBJECTDIR}/appAutomationEthernet1.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationEthernet1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationEthernet1.o.d" -o ${OBJECTDIR}/appAutomationEthernet1.o appAutomationEthernet1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationEthernet.o: appAutomationEthernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationEthernet.o.d 
	@${RM} ${OBJECTDIR}/appAutomationEthernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationEthernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationEthernet.o.d" -o ${OBJECTDIR}/appAutomationEthernet.o appAutomationEthernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelacs2.o: appTestRigMelacs2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelacs2.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelacs2.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelacs2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelacs2.o.d" -o ${OBJECTDIR}/appTestRigMelacs2.o appTestRigMelacs2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelacs1.o: appTestRigMelacs1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelacs1.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelacs1.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelacs1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelacs1.o.d" -o ${OBJECTDIR}/appTestRigMelacs1.o appTestRigMelacs1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet_2.o: appTestRigMelac2Ethernet_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet_2.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o appTestRigMelac2Ethernet_2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet_1.o: appTestRigMelac2Ethernet_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet_1.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o appTestRigMelac2Ethernet_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac1Ethernet_1.o: appTestRigMelac1Ethernet_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac1Ethernet_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac1Ethernet_1.o.d" -o ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o appTestRigMelac1Ethernet_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRig1.o: appTestRig1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRig1.o.d 
	@${RM} ${OBJECTDIR}/appTestRig1.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRig1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRig1.o.d" -o ${OBJECTDIR}/appTestRig1.o appTestRig1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRig.o: appTestRig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRig.o.d 
	@${RM} ${OBJECTDIR}/appTestRig.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRig.o.d" -o ${OBJECTDIR}/appTestRig.o appTestRig.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPulseGen.o: appPulseGen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPulseGen.o.d 
	@${RM} ${OBJECTDIR}/appPulseGen.o 
	@${FIXDEPS} "${OBJECTDIR}/appPulseGen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPulseGen.o.d" -o ${OBJECTDIR}/appPulseGen.o appPulseGen.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appInjectorTest.o: appInjectorTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appInjectorTest.o.d 
	@${RM} ${OBJECTDIR}/appInjectorTest.o 
	@${FIXDEPS} "${OBJECTDIR}/appInjectorTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appInjectorTest.o.d" -o ${OBJECTDIR}/appInjectorTest.o appInjectorTest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appValveControl.o: appValveControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appValveControl.o.d 
	@${RM} ${OBJECTDIR}/appValveControl.o 
	@${FIXDEPS} "${OBJECTDIR}/appValveControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appValveControl.o.d" -o ${OBJECTDIR}/appValveControl.o appValveControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation2.o: appAutomation2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation2.o.d 
	@${RM} ${OBJECTDIR}/appAutomation2.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation2.o.d" -o ${OBJECTDIR}/appAutomation2.o appAutomation2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appOEM_1.o: appOEM_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appOEM_1.o.d 
	@${RM} ${OBJECTDIR}/appOEM_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appOEM_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appOEM_1.o.d" -o ${OBJECTDIR}/appOEM_1.o appOEM_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation4.o: appAutomation4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation4.o.d 
	@${RM} ${OBJECTDIR}/appAutomation4.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation4.o.d" -o ${OBJECTDIR}/appAutomation4.o appAutomation4.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation4USB.o: appAutomation4USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation4USB.o.d 
	@${RM} ${OBJECTDIR}/appAutomation4USB.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation4USB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation4USB.o.d" -o ${OBJECTDIR}/appAutomation4USB.o appAutomation4USB.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation4USB_1.o: appAutomation4USB_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation4USB_1.o.d 
	@${RM} ${OBJECTDIR}/appAutomation4USB_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation4USB_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation4USB_1.o.d" -o ${OBJECTDIR}/appAutomation4USB_1.o appAutomation4USB_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_1.o: appAutomation5USB_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_1.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_1.o.d" -o ${OBJECTDIR}/appAutomation5USB_1.o appAutomation5USB_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_2.o: appAutomation5USB_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_2.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_2.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_2.o.d" -o ${OBJECTDIR}/appAutomation5USB_2.o appAutomation5USB_2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_3.o: appAutomation5USB_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_3.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_3.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_3.o.d" -o ${OBJECTDIR}/appAutomation5USB_3.o appAutomation5USB_3.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_5.o: appAutomation5USB_5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_5.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_5.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_5.o.d" -o ${OBJECTDIR}/appAutomation5USB_5.o appAutomation5USB_5.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation3.o: appAutomation3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation3.o.d 
	@${RM} ${OBJECTDIR}/appAutomation3.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation3.o.d" -o ${OBJECTDIR}/appAutomation3.o appAutomation3.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appCurrentSensing.o: appCurrentSensing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appCurrentSensing.o.d 
	@${RM} ${OBJECTDIR}/appCurrentSensing.o 
	@${FIXDEPS} "${OBJECTDIR}/appCurrentSensing.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appCurrentSensing.o.d" -o ${OBJECTDIR}/appCurrentSensing.o appCurrentSensing.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appCurrentLimiter.o: appCurrentLimiter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appCurrentLimiter.o.d 
	@${RM} ${OBJECTDIR}/appCurrentLimiter.o 
	@${FIXDEPS} "${OBJECTDIR}/appCurrentLimiter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appCurrentLimiter.o.d" -o ${OBJECTDIR}/appCurrentLimiter.o appCurrentLimiter.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation3Ethernet.o: appAutomation3Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation3Ethernet.o.d 
	@${RM} ${OBJECTDIR}/appAutomation3Ethernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation3Ethernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation3Ethernet.o.d" -o ${OBJECTDIR}/appAutomation3Ethernet.o appAutomation3Ethernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac1USB.c.o: appTestRigMelac1USB.c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac1USB.c.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac1USB.c.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac1USB.c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac1USB.c.o.d" -o ${OBJECTDIR}/appTestRigMelac1USB.c.o appTestRigMelac1USB.c.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o: appAutomation5USB_BurstDelayAdded.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o.d" -o ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o appAutomation5USB_BurstDelayAdded.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o: appAutomation5USB_BeforeFeedRamp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o.d" -o ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o appAutomation5USB_BeforeFeedRamp.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o: appAutomation5USB_BeforeFanRamp_SlowDose.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o.d" -o ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o appAutomation5USB_BeforeFanRamp_SlowDose.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o: appAutomation5USB_BeforeSetPressureCheck.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o.d" -o ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o appAutomation5USB_BeforeSetPressureCheck.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac1Ethernet_2.o: appTestRigMelac1Ethernet_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac1Ethernet_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac1Ethernet_2.o.d" -o ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o appTestRigMelac1Ethernet_2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet_3.o: appTestRigMelac2Ethernet_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet_3.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o appTestRigMelac2Ethernet_3.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet_4.o: appTestRigMelac2Ethernet_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet_4.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o appTestRigMelac2Ethernet_4.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appGSMtest.o: appGSMtest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appGSMtest.o.d 
	@${RM} ${OBJECTDIR}/appGSMtest.o 
	@${FIXDEPS} "${OBJECTDIR}/appGSMtest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appGSMtest.o.d" -o ${OBJECTDIR}/appGSMtest.o appGSMtest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appSpiSlave.o: appSpiSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appSpiSlave.o.d 
	@${RM} ${OBJECTDIR}/appSpiSlave.o 
	@${FIXDEPS} "${OBJECTDIR}/appSpiSlave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appSpiSlave.o.d" -o ${OBJECTDIR}/appSpiSlave.o appSpiSlave.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appSpiMaster.o: appSpiMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appSpiMaster.o.d 
	@${RM} ${OBJECTDIR}/appSpiMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/appSpiMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appSpiMaster.o.d" -o ${OBJECTDIR}/appSpiMaster.o appSpiMaster.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appOEM.o: appOEM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appOEM.o.d 
	@${RM} ${OBJECTDIR}/appOEM.o 
	@${FIXDEPS} "${OBJECTDIR}/appOEM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appOEM.o.d" -o ${OBJECTDIR}/appOEM.o appOEM.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationWrapped.o: appAutomationWrapped.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationWrapped.o.d 
	@${RM} ${OBJECTDIR}/appAutomationWrapped.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationWrapped.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationWrapped.o.d" -o ${OBJECTDIR}/appAutomationWrapped.o appAutomationWrapped.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/wrapperUnitTest.o: wrapperUnitTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wrapperUnitTest.o.d 
	@${RM} ${OBJECTDIR}/wrapperUnitTest.o 
	@${FIXDEPS} "${OBJECTDIR}/wrapperUnitTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/wrapperUnitTest.o.d" -o ${OBJECTDIR}/wrapperUnitTest.o wrapperUnitTest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac1Ethernet.o: appTestRigMelac1Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac1Ethernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac1Ethernet.o.d" -o ${OBJECTDIR}/appTestRigMelac1Ethernet.o appTestRigMelac1Ethernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet.o: appTestRigMelac2Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet.o appTestRigMelac2Ethernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appEmpty.o: appEmpty.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appEmpty.o.d 
	@${RM} ${OBJECTDIR}/appEmpty.o 
	@${FIXDEPS} "${OBJECTDIR}/appEmpty.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appEmpty.o.d" -o ${OBJECTDIR}/appEmpty.o appEmpty.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB.o: appAutomation5USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB.o.d" -o ${OBJECTDIR}/appAutomation5USB.o appAutomation5USB.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationEthernetandSD.o: appAutomationEthernetandSD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationEthernetandSD.o.d 
	@${RM} ${OBJECTDIR}/appAutomationEthernetandSD.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationEthernetandSD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationEthernetandSD.o.d" -o ${OBJECTDIR}/appAutomationEthernetandSD.o appAutomationEthernetandSD.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPeakEcoEthernet.o: appPeakEcoEthernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPeakEcoEthernet.o.d 
	@${RM} ${OBJECTDIR}/appPeakEcoEthernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appPeakEcoEthernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPeakEcoEthernet.o.d" -o ${OBJECTDIR}/appPeakEcoEthernet.o appPeakEcoEthernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPressureCurveCalibration.o: appPressureCurveCalibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPressureCurveCalibration.o.d 
	@${RM} ${OBJECTDIR}/appPressureCurveCalibration.o 
	@${FIXDEPS} "${OBJECTDIR}/appPressureCurveCalibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPressureCurveCalibration.o.d" -o ${OBJECTDIR}/appPressureCurveCalibration.o appPressureCurveCalibration.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPressureFillRelease.o: appPressureFillRelease.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPressureFillRelease.o.d 
	@${RM} ${OBJECTDIR}/appPressureFillRelease.o 
	@${FIXDEPS} "${OBJECTDIR}/appPressureFillRelease.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPressureFillRelease.o.d" -o ${OBJECTDIR}/appPressureFillRelease.o appPressureFillRelease.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/GSMFiles/board.o: GSMFiles/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GSMFiles" 
	@${RM} ${OBJECTDIR}/GSMFiles/board.o.d 
	@${RM} ${OBJECTDIR}/GSMFiles/board.o 
	@${FIXDEPS} "${OBJECTDIR}/GSMFiles/board.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/GSMFiles/board.o.d" -o ${OBJECTDIR}/GSMFiles/board.o GSMFiles/board.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/GSMFiles/cloudindustries_api.o: GSMFiles/cloudindustries_api.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GSMFiles" 
	@${RM} ${OBJECTDIR}/GSMFiles/cloudindustries_api.o.d 
	@${RM} ${OBJECTDIR}/GSMFiles/cloudindustries_api.o 
	@${FIXDEPS} "${OBJECTDIR}/GSMFiles/cloudindustries_api.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/GSMFiles/cloudindustries_api.o.d" -o ${OBJECTDIR}/GSMFiles/cloudindustries_api.o GSMFiles/cloudindustries_api.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/GSMFiles/fifo_buffer.o: GSMFiles/fifo_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GSMFiles" 
	@${RM} ${OBJECTDIR}/GSMFiles/fifo_buffer.o.d 
	@${RM} ${OBJECTDIR}/GSMFiles/fifo_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/GSMFiles/fifo_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/GSMFiles/fifo_buffer.o.d" -o ${OBJECTDIR}/GSMFiles/fifo_buffer.o GSMFiles/fifo_buffer.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o: GSMFiles/ublox_lisa_u230.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GSMFiles" 
	@${RM} ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o.d 
	@${RM} ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o 
	@${FIXDEPS} "${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o.d" -o ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o GSMFiles/ublox_lisa_u230.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/malloc.o: malloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/malloc.o.d 
	@${RM} ${OBJECTDIR}/malloc.o 
	@${FIXDEPS} "${OBJECTDIR}/malloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/malloc.o.d" -o ${OBJECTDIR}/malloc.o malloc.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/sd_spi.o: sd_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/sd_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/sd_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/sd_spi.o.d" -o ${OBJECTDIR}/sd_spi.o sd_spi.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/mmc.o: mmc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc.o.d 
	@${RM} ${OBJECTDIR}/mmc.o 
	@${FIXDEPS} "${OBJECTDIR}/mmc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/mmc.o.d" -o ${OBJECTDIR}/mmc.o mmc.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/logRun.o: logRun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/logRun.o.d 
	@${RM} ${OBJECTDIR}/logRun.o 
	@${FIXDEPS} "${OBJECTDIR}/logRun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/logRun.o.d" -o ${OBJECTDIR}/logRun.o logRun.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/display.o: display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	@${FIXDEPS} "${OBJECTDIR}/display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/display.o.d" -o ${OBJECTDIR}/display.o display.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/common.o: common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/common.o.d 
	@${RM} ${OBJECTDIR}/common.o 
	@${FIXDEPS} "${OBJECTDIR}/common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/common.o.d" -o ${OBJECTDIR}/common.o common.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/gsm_main.o: gsm_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gsm_main.o.d 
	@${RM} ${OBJECTDIR}/gsm_main.o 
	@${FIXDEPS} "${OBJECTDIR}/gsm_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/gsm_main.o.d" -o ${OBJECTDIR}/gsm_main.o gsm_main.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/configurations.o: configurations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configurations.o.d 
	@${RM} ${OBJECTDIR}/configurations.o 
	@${FIXDEPS} "${OBJECTDIR}/configurations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/configurations.o.d" -o ${OBJECTDIR}/configurations.o configurations.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/onBoardADC.o: onBoardADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardADC.o.d 
	@${RM} ${OBJECTDIR}/onBoardADC.o 
	@${FIXDEPS} "${OBJECTDIR}/onBoardADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/onBoardADC.o.d" -o ${OBJECTDIR}/onBoardADC.o onBoardADC.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/onBoardRTCC.o: onBoardRTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o.d 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o 
	@${FIXDEPS} "${OBJECTDIR}/onBoardRTCC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/onBoardRTCC.o.d" -o ${OBJECTDIR}/onBoardRTCC.o onBoardRTCC.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/sensors.o: sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensors.o.d 
	@${RM} ${OBJECTDIR}/sensors.o 
	@${FIXDEPS} "${OBJECTDIR}/sensors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/sensors.o.d" -o ${OBJECTDIR}/sensors.o sensors.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/sensorValueConvertion.o: sensorValueConvertion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o.d 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o 
	@${FIXDEPS} "${OBJECTDIR}/sensorValueConvertion.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/sensorValueConvertion.o.d" -o ${OBJECTDIR}/sensorValueConvertion.o sensorValueConvertion.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/readConfig.o: readConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/readConfig.o.d 
	@${RM} ${OBJECTDIR}/readConfig.o 
	@${FIXDEPS} "${OBJECTDIR}/readConfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/readConfig.o.d" -o ${OBJECTDIR}/readConfig.o readConfig.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/melacs_spi.o: melacs_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/melacs_spi.o.d 
	@${RM} ${OBJECTDIR}/melacs_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/melacs_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/melacs_spi.o.d" -o ${OBJECTDIR}/melacs_spi.o melacs_spi.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/buzzer.o: buzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	@${FIXDEPS} "${OBJECTDIR}/buzzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/buzzer.o.d" -o ${OBJECTDIR}/buzzer.o buzzer.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/setup.o: setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/setup.o.d 
	@${RM} ${OBJECTDIR}/setup.o 
	@${FIXDEPS} "${OBJECTDIR}/setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/setup.o.d" -o ${OBJECTDIR}/setup.o setup.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/_ext/893916629/appheader.o: ../_startup_ESK_EXP16/boot_app/appheader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/893916629" 
	@${RM} ${OBJECTDIR}/_ext/893916629/appheader.o.d 
	@${RM} ${OBJECTDIR}/_ext/893916629/appheader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/893916629/appheader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/_ext/893916629/appheader.o.d" -o ${OBJECTDIR}/_ext/893916629/appheader.o ../_startup_ESK_EXP16/boot_app/appheader.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/firmwareRecoveryUpdate.o: firmwareRecoveryUpdate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/firmwareRecoveryUpdate.o.d 
	@${RM} ${OBJECTDIR}/firmwareRecoveryUpdate.o 
	@${FIXDEPS} "${OBJECTDIR}/firmwareRecoveryUpdate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/firmwareRecoveryUpdate.o.d" -o ${OBJECTDIR}/firmwareRecoveryUpdate.o firmwareRecoveryUpdate.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/wrapper.o: wrapper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wrapper.o.d 
	@${RM} ${OBJECTDIR}/wrapper.o 
	@${FIXDEPS} "${OBJECTDIR}/wrapper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/wrapper.o.d" -o ${OBJECTDIR}/wrapper.o wrapper.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/tcp_start.o: tcp_start.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_start.o.d 
	@${RM} ${OBJECTDIR}/tcp_start.o 
	@${FIXDEPS} "${OBJECTDIR}/tcp_start.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/tcp_start.o.d" -o ${OBJECTDIR}/tcp_start.o tcp_start.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/tcp_server.o: tcp_server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_server.o.d 
	@${RM} ${OBJECTDIR}/tcp_server.o 
	@${FIXDEPS} "${OBJECTDIR}/tcp_server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/tcp_server.o.d" -o ${OBJECTDIR}/tcp_server.o tcp_server.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/mutex.o: mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mutex.o.d 
	@${RM} ${OBJECTDIR}/mutex.o 
	@${FIXDEPS} "${OBJECTDIR}/mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/mutex.o.d" -o ${OBJECTDIR}/mutex.o mutex.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/speedControl.o: speedControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/speedControl.o.d 
	@${RM} ${OBJECTDIR}/speedControl.o 
	@${FIXDEPS} "${OBJECTDIR}/speedControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/speedControl.o.d" -o ${OBJECTDIR}/speedControl.o speedControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/threeWayValve.o: threeWayValve.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/threeWayValve.o.d 
	@${RM} ${OBJECTDIR}/threeWayValve.o 
	@${FIXDEPS} "${OBJECTDIR}/threeWayValve.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/threeWayValve.o.d" -o ${OBJECTDIR}/threeWayValve.o threeWayValve.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/hBridge.o: hBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	@${FIXDEPS} "${OBJECTDIR}/hBridge.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/hBridge.o.d" -o ${OBJECTDIR}/hBridge.o hBridge.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/analogToPhysical.o: analogToPhysical.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogToPhysical.o.d 
	@${RM} ${OBJECTDIR}/analogToPhysical.o 
	@${FIXDEPS} "${OBJECTDIR}/analogToPhysical.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/analogToPhysical.o.d" -o ${OBJECTDIR}/analogToPhysical.o analogToPhysical.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/timeDifference.o: timeDifference.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timeDifference.o.d 
	@${RM} ${OBJECTDIR}/timeDifference.o 
	@${FIXDEPS} "${OBJECTDIR}/timeDifference.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/timeDifference.o.d" -o ${OBJECTDIR}/timeDifference.o timeDifference.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/analogSensor10bit.o: analogSensor10bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o.d 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o 
	@${FIXDEPS} "${OBJECTDIR}/analogSensor10bit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/analogSensor10bit.o.d" -o ${OBJECTDIR}/analogSensor10bit.o analogSensor10bit.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/usb_composite.o: usb_composite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_composite.o.d 
	@${RM} ${OBJECTDIR}/usb_composite.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_composite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/usb_composite.o.d" -o ${OBJECTDIR}/usb_composite.o usb_composite.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
else
${OBJECTDIR}/oemMain.o: oemMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemMain.o.d 
	@${RM} ${OBJECTDIR}/oemMain.o 
	@${FIXDEPS} "${OBJECTDIR}/oemMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemMain.o.d" -o ${OBJECTDIR}/oemMain.o oemMain.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemDisplay.o: oemDisplay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemDisplay.o.d 
	@${RM} ${OBJECTDIR}/oemDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/oemDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemDisplay.o.d" -o ${OBJECTDIR}/oemDisplay.o oemDisplay.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemLog.o: oemLog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemLog.o.d 
	@${RM} ${OBJECTDIR}/oemLog.o 
	@${FIXDEPS} "${OBJECTDIR}/oemLog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemLog.o.d" -o ${OBJECTDIR}/oemLog.o oemLog.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemGSM.o: oemGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemGSM.o.d 
	@${RM} ${OBJECTDIR}/oemGSM.o 
	@${FIXDEPS} "${OBJECTDIR}/oemGSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemGSM.o.d" -o ${OBJECTDIR}/oemGSM.o oemGSM.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemFunctions.o: oemFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemFunctions.o.d 
	@${RM} ${OBJECTDIR}/oemFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/oemFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemFunctions.o.d" -o ${OBJECTDIR}/oemFunctions.o oemFunctions.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemOutputControl.o: oemOutputControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemOutputControl.o.d 
	@${RM} ${OBJECTDIR}/oemOutputControl.o 
	@${FIXDEPS} "${OBJECTDIR}/oemOutputControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemOutputControl.o.d" -o ${OBJECTDIR}/oemOutputControl.o oemOutputControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemInputAcquisition.o: oemInputAcquisition.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o.d 
	@${RM} ${OBJECTDIR}/oemInputAcquisition.o 
	@${FIXDEPS} "${OBJECTDIR}/oemInputAcquisition.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemInputAcquisition.o.d" -o ${OBJECTDIR}/oemInputAcquisition.o oemInputAcquisition.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemCalculations.o: oemCalculations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemCalculations.o.d 
	@${RM} ${OBJECTDIR}/oemCalculations.o 
	@${FIXDEPS} "${OBJECTDIR}/oemCalculations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemCalculations.o.d" -o ${OBJECTDIR}/oemCalculations.o oemCalculations.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemInputAveraging.o: oemInputAveraging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o.d 
	@${RM} ${OBJECTDIR}/oemInputAveraging.o 
	@${FIXDEPS} "${OBJECTDIR}/oemInputAveraging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemInputAveraging.o.d" -o ${OBJECTDIR}/oemInputAveraging.o oemInputAveraging.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemSaveReadParameter.o: oemSaveReadParameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o.d 
	@${RM} ${OBJECTDIR}/oemSaveReadParameter.o 
	@${FIXDEPS} "${OBJECTDIR}/oemSaveReadParameter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemSaveReadParameter.o.d" -o ${OBJECTDIR}/oemSaveReadParameter.o oemSaveReadParameter.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/oemSendRecvUsb.o: oemSendRecvUsb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o.d 
	@${RM} ${OBJECTDIR}/oemSendRecvUsb.o 
	@${FIXDEPS} "${OBJECTDIR}/oemSendRecvUsb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/oemSendRecvUsb.o.d" -o ${OBJECTDIR}/oemSendRecvUsb.o oemSendRecvUsb.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableInputAcquisition.o: portableInputAcquisition.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableInputAcquisition.o.d 
	@${RM} ${OBJECTDIR}/portableInputAcquisition.o 
	@${FIXDEPS} "${OBJECTDIR}/portableInputAcquisition.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableInputAcquisition.o.d" -o ${OBJECTDIR}/portableInputAcquisition.o portableInputAcquisition.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableInputAveraging.o: portableInputAveraging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableInputAveraging.o.d 
	@${RM} ${OBJECTDIR}/portableInputAveraging.o 
	@${FIXDEPS} "${OBJECTDIR}/portableInputAveraging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableInputAveraging.o.d" -o ${OBJECTDIR}/portableInputAveraging.o portableInputAveraging.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableCalculations.o: portableCalculations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableCalculations.o.d 
	@${RM} ${OBJECTDIR}/portableCalculations.o 
	@${FIXDEPS} "${OBJECTDIR}/portableCalculations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableCalculations.o.d" -o ${OBJECTDIR}/portableCalculations.o portableCalculations.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableDisplay.o: portableDisplay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableDisplay.o.d 
	@${RM} ${OBJECTDIR}/portableDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/portableDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableDisplay.o.d" -o ${OBJECTDIR}/portableDisplay.o portableDisplay.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableGSM.o: portableGSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableGSM.o.d 
	@${RM} ${OBJECTDIR}/portableGSM.o 
	@${FIXDEPS} "${OBJECTDIR}/portableGSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableGSM.o.d" -o ${OBJECTDIR}/portableGSM.o portableGSM.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableLog.o: portableLog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableLog.o.d 
	@${RM} ${OBJECTDIR}/portableLog.o 
	@${FIXDEPS} "${OBJECTDIR}/portableLog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableLog.o.d" -o ${OBJECTDIR}/portableLog.o portableLog.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableMain.o: portableMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableMain.o.d 
	@${RM} ${OBJECTDIR}/portableMain.o 
	@${FIXDEPS} "${OBJECTDIR}/portableMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableMain.o.d" -o ${OBJECTDIR}/portableMain.o portableMain.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableOutputControl.o: portableOutputControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableOutputControl.o.d 
	@${RM} ${OBJECTDIR}/portableOutputControl.o 
	@${FIXDEPS} "${OBJECTDIR}/portableOutputControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableOutputControl.o.d" -o ${OBJECTDIR}/portableOutputControl.o portableOutputControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableSaveReadParameter.o: portableSaveReadParameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableSaveReadParameter.o.d 
	@${RM} ${OBJECTDIR}/portableSaveReadParameter.o 
	@${FIXDEPS} "${OBJECTDIR}/portableSaveReadParameter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableSaveReadParameter.o.d" -o ${OBJECTDIR}/portableSaveReadParameter.o portableSaveReadParameter.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/portableSendRecvUsb.o: portableSendRecvUsb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/portableSendRecvUsb.o.d 
	@${RM} ${OBJECTDIR}/portableSendRecvUsb.o 
	@${FIXDEPS} "${OBJECTDIR}/portableSendRecvUsb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/portableSendRecvUsb.o.d" -o ${OBJECTDIR}/portableSendRecvUsb.o portableSendRecvUsb.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation.o: appAutomation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation.o.d 
	@${RM} ${OBJECTDIR}/appAutomation.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation.o.d" -o ${OBJECTDIR}/appAutomation.o appAutomation.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation1.o: appAutomation1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation1.o.d 
	@${RM} ${OBJECTDIR}/appAutomation1.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation1.o.d" -o ${OBJECTDIR}/appAutomation1.o appAutomation1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appEngineLongRun.o: appEngineLongRun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appEngineLongRun.o.d 
	@${RM} ${OBJECTDIR}/appEngineLongRun.o 
	@${FIXDEPS} "${OBJECTDIR}/appEngineLongRun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appEngineLongRun.o.d" -o ${OBJECTDIR}/appEngineLongRun.o appEngineLongRun.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/applicationGeneral.o: applicationGeneral.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/applicationGeneral.o.d 
	@${RM} ${OBJECTDIR}/applicationGeneral.o 
	@${FIXDEPS} "${OBJECTDIR}/applicationGeneral.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/applicationGeneral.o.d" -o ${OBJECTDIR}/applicationGeneral.o applicationGeneral.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/applicationGeneral1.o: applicationGeneral1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/applicationGeneral1.o.d 
	@${RM} ${OBJECTDIR}/applicationGeneral1.o 
	@${FIXDEPS} "${OBJECTDIR}/applicationGeneral1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/applicationGeneral1.o.d" -o ${OBJECTDIR}/applicationGeneral1.o applicationGeneral1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPullDownTest.o: appPullDownTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPullDownTest.o.d 
	@${RM} ${OBJECTDIR}/appPullDownTest.o 
	@${FIXDEPS} "${OBJECTDIR}/appPullDownTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPullDownTest.o.d" -o ${OBJECTDIR}/appPullDownTest.o appPullDownTest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appFeederTest.o: appFeederTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appFeederTest.o.d 
	@${RM} ${OBJECTDIR}/appFeederTest.o 
	@${FIXDEPS} "${OBJECTDIR}/appFeederTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appFeederTest.o.d" -o ${OBJECTDIR}/appFeederTest.o appFeederTest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPelletFeed.o: appPelletFeed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPelletFeed.o.d 
	@${RM} ${OBJECTDIR}/appPelletFeed.o 
	@${FIXDEPS} "${OBJECTDIR}/appPelletFeed.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPelletFeed.o.d" -o ${OBJECTDIR}/appPelletFeed.o appPelletFeed.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appSipMotorControl.o: appSipMotorControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appSipMotorControl.o.d 
	@${RM} ${OBJECTDIR}/appSipMotorControl.o 
	@${FIXDEPS} "${OBJECTDIR}/appSipMotorControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appSipMotorControl.o.d" -o ${OBJECTDIR}/appSipMotorControl.o appSipMotorControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appOnlySensorRead.o: appOnlySensorRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appOnlySensorRead.o.d 
	@${RM} ${OBJECTDIR}/appOnlySensorRead.o 
	@${FIXDEPS} "${OBJECTDIR}/appOnlySensorRead.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appOnlySensorRead.o.d" -o ${OBJECTDIR}/appOnlySensorRead.o appOnlySensorRead.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appStatorRead.o: appStatorRead.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appStatorRead.o.d 
	@${RM} ${OBJECTDIR}/appStatorRead.o 
	@${FIXDEPS} "${OBJECTDIR}/appStatorRead.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appStatorRead.o.d" -o ${OBJECTDIR}/appStatorRead.o appStatorRead.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationEthernet2.o: appAutomationEthernet2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationEthernet2.o.d 
	@${RM} ${OBJECTDIR}/appAutomationEthernet2.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationEthernet2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationEthernet2.o.d" -o ${OBJECTDIR}/appAutomationEthernet2.o appAutomationEthernet2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationEthernet1.o: appAutomationEthernet1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationEthernet1.o.d 
	@${RM} ${OBJECTDIR}/appAutomationEthernet1.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationEthernet1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationEthernet1.o.d" -o ${OBJECTDIR}/appAutomationEthernet1.o appAutomationEthernet1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationEthernet.o: appAutomationEthernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationEthernet.o.d 
	@${RM} ${OBJECTDIR}/appAutomationEthernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationEthernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationEthernet.o.d" -o ${OBJECTDIR}/appAutomationEthernet.o appAutomationEthernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelacs2.o: appTestRigMelacs2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelacs2.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelacs2.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelacs2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelacs2.o.d" -o ${OBJECTDIR}/appTestRigMelacs2.o appTestRigMelacs2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelacs1.o: appTestRigMelacs1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelacs1.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelacs1.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelacs1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelacs1.o.d" -o ${OBJECTDIR}/appTestRigMelacs1.o appTestRigMelacs1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet_2.o: appTestRigMelac2Ethernet_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet_2.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet_2.o appTestRigMelac2Ethernet_2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet_1.o: appTestRigMelac2Ethernet_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet_1.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet_1.o appTestRigMelac2Ethernet_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac1Ethernet_1.o: appTestRigMelac1Ethernet_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac1Ethernet_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac1Ethernet_1.o.d" -o ${OBJECTDIR}/appTestRigMelac1Ethernet_1.o appTestRigMelac1Ethernet_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRig1.o: appTestRig1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRig1.o.d 
	@${RM} ${OBJECTDIR}/appTestRig1.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRig1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRig1.o.d" -o ${OBJECTDIR}/appTestRig1.o appTestRig1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRig.o: appTestRig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRig.o.d 
	@${RM} ${OBJECTDIR}/appTestRig.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRig.o.d" -o ${OBJECTDIR}/appTestRig.o appTestRig.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPulseGen.o: appPulseGen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPulseGen.o.d 
	@${RM} ${OBJECTDIR}/appPulseGen.o 
	@${FIXDEPS} "${OBJECTDIR}/appPulseGen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPulseGen.o.d" -o ${OBJECTDIR}/appPulseGen.o appPulseGen.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appInjectorTest.o: appInjectorTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appInjectorTest.o.d 
	@${RM} ${OBJECTDIR}/appInjectorTest.o 
	@${FIXDEPS} "${OBJECTDIR}/appInjectorTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appInjectorTest.o.d" -o ${OBJECTDIR}/appInjectorTest.o appInjectorTest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appValveControl.o: appValveControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appValveControl.o.d 
	@${RM} ${OBJECTDIR}/appValveControl.o 
	@${FIXDEPS} "${OBJECTDIR}/appValveControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appValveControl.o.d" -o ${OBJECTDIR}/appValveControl.o appValveControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation2.o: appAutomation2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation2.o.d 
	@${RM} ${OBJECTDIR}/appAutomation2.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation2.o.d" -o ${OBJECTDIR}/appAutomation2.o appAutomation2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appOEM_1.o: appOEM_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appOEM_1.o.d 
	@${RM} ${OBJECTDIR}/appOEM_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appOEM_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appOEM_1.o.d" -o ${OBJECTDIR}/appOEM_1.o appOEM_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation4.o: appAutomation4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation4.o.d 
	@${RM} ${OBJECTDIR}/appAutomation4.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation4.o.d" -o ${OBJECTDIR}/appAutomation4.o appAutomation4.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation4USB.o: appAutomation4USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation4USB.o.d 
	@${RM} ${OBJECTDIR}/appAutomation4USB.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation4USB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation4USB.o.d" -o ${OBJECTDIR}/appAutomation4USB.o appAutomation4USB.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation4USB_1.o: appAutomation4USB_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation4USB_1.o.d 
	@${RM} ${OBJECTDIR}/appAutomation4USB_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation4USB_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation4USB_1.o.d" -o ${OBJECTDIR}/appAutomation4USB_1.o appAutomation4USB_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_1.o: appAutomation5USB_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_1.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_1.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_1.o.d" -o ${OBJECTDIR}/appAutomation5USB_1.o appAutomation5USB_1.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_2.o: appAutomation5USB_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_2.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_2.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_2.o.d" -o ${OBJECTDIR}/appAutomation5USB_2.o appAutomation5USB_2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_3.o: appAutomation5USB_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_3.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_3.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_3.o.d" -o ${OBJECTDIR}/appAutomation5USB_3.o appAutomation5USB_3.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_5.o: appAutomation5USB_5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_5.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_5.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_5.o.d" -o ${OBJECTDIR}/appAutomation5USB_5.o appAutomation5USB_5.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation3.o: appAutomation3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation3.o.d 
	@${RM} ${OBJECTDIR}/appAutomation3.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation3.o.d" -o ${OBJECTDIR}/appAutomation3.o appAutomation3.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appCurrentSensing.o: appCurrentSensing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appCurrentSensing.o.d 
	@${RM} ${OBJECTDIR}/appCurrentSensing.o 
	@${FIXDEPS} "${OBJECTDIR}/appCurrentSensing.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appCurrentSensing.o.d" -o ${OBJECTDIR}/appCurrentSensing.o appCurrentSensing.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appCurrentLimiter.o: appCurrentLimiter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appCurrentLimiter.o.d 
	@${RM} ${OBJECTDIR}/appCurrentLimiter.o 
	@${FIXDEPS} "${OBJECTDIR}/appCurrentLimiter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appCurrentLimiter.o.d" -o ${OBJECTDIR}/appCurrentLimiter.o appCurrentLimiter.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation3Ethernet.o: appAutomation3Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation3Ethernet.o.d 
	@${RM} ${OBJECTDIR}/appAutomation3Ethernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation3Ethernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation3Ethernet.o.d" -o ${OBJECTDIR}/appAutomation3Ethernet.o appAutomation3Ethernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac1USB.c.o: appTestRigMelac1USB.c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac1USB.c.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac1USB.c.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac1USB.c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac1USB.c.o.d" -o ${OBJECTDIR}/appTestRigMelac1USB.c.o appTestRigMelac1USB.c.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o: appAutomation5USB_BurstDelayAdded.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o.d" -o ${OBJECTDIR}/appAutomation5USB_BurstDelayAdded.o appAutomation5USB_BurstDelayAdded.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o: appAutomation5USB_BeforeFeedRamp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o.d" -o ${OBJECTDIR}/appAutomation5USB_BeforeFeedRamp.o appAutomation5USB_BeforeFeedRamp.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o: appAutomation5USB_BeforeFanRamp_SlowDose.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o.d" -o ${OBJECTDIR}/appAutomation5USB_BeforeFanRamp_SlowDose.o appAutomation5USB_BeforeFanRamp_SlowDose.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o: appAutomation5USB_BeforeSetPressureCheck.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o.d" -o ${OBJECTDIR}/appAutomation5USB_BeforeSetPressureCheck.o appAutomation5USB_BeforeSetPressureCheck.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac1Ethernet_2.o: appTestRigMelac1Ethernet_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac1Ethernet_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac1Ethernet_2.o.d" -o ${OBJECTDIR}/appTestRigMelac1Ethernet_2.o appTestRigMelac1Ethernet_2.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet_3.o: appTestRigMelac2Ethernet_3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet_3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet_3.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet_3.o appTestRigMelac2Ethernet_3.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet_4.o: appTestRigMelac2Ethernet_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet_4.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet_4.o appTestRigMelac2Ethernet_4.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appGSMtest.o: appGSMtest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appGSMtest.o.d 
	@${RM} ${OBJECTDIR}/appGSMtest.o 
	@${FIXDEPS} "${OBJECTDIR}/appGSMtest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appGSMtest.o.d" -o ${OBJECTDIR}/appGSMtest.o appGSMtest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appSpiSlave.o: appSpiSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appSpiSlave.o.d 
	@${RM} ${OBJECTDIR}/appSpiSlave.o 
	@${FIXDEPS} "${OBJECTDIR}/appSpiSlave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appSpiSlave.o.d" -o ${OBJECTDIR}/appSpiSlave.o appSpiSlave.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appSpiMaster.o: appSpiMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appSpiMaster.o.d 
	@${RM} ${OBJECTDIR}/appSpiMaster.o 
	@${FIXDEPS} "${OBJECTDIR}/appSpiMaster.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appSpiMaster.o.d" -o ${OBJECTDIR}/appSpiMaster.o appSpiMaster.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appOEM.o: appOEM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appOEM.o.d 
	@${RM} ${OBJECTDIR}/appOEM.o 
	@${FIXDEPS} "${OBJECTDIR}/appOEM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appOEM.o.d" -o ${OBJECTDIR}/appOEM.o appOEM.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationWrapped.o: appAutomationWrapped.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationWrapped.o.d 
	@${RM} ${OBJECTDIR}/appAutomationWrapped.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationWrapped.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationWrapped.o.d" -o ${OBJECTDIR}/appAutomationWrapped.o appAutomationWrapped.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/wrapperUnitTest.o: wrapperUnitTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wrapperUnitTest.o.d 
	@${RM} ${OBJECTDIR}/wrapperUnitTest.o 
	@${FIXDEPS} "${OBJECTDIR}/wrapperUnitTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/wrapperUnitTest.o.d" -o ${OBJECTDIR}/wrapperUnitTest.o wrapperUnitTest.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac1Ethernet.o: appTestRigMelac1Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac1Ethernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac1Ethernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac1Ethernet.o.d" -o ${OBJECTDIR}/appTestRigMelac1Ethernet.o appTestRigMelac1Ethernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appTestRigMelac2Ethernet.o: appTestRigMelac2Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet.o.d 
	@${RM} ${OBJECTDIR}/appTestRigMelac2Ethernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appTestRigMelac2Ethernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appTestRigMelac2Ethernet.o.d" -o ${OBJECTDIR}/appTestRigMelac2Ethernet.o appTestRigMelac2Ethernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appEmpty.o: appEmpty.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appEmpty.o.d 
	@${RM} ${OBJECTDIR}/appEmpty.o 
	@${FIXDEPS} "${OBJECTDIR}/appEmpty.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appEmpty.o.d" -o ${OBJECTDIR}/appEmpty.o appEmpty.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomation5USB.o: appAutomation5USB.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomation5USB.o.d 
	@${RM} ${OBJECTDIR}/appAutomation5USB.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomation5USB.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomation5USB.o.d" -o ${OBJECTDIR}/appAutomation5USB.o appAutomation5USB.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appAutomationEthernetandSD.o: appAutomationEthernetandSD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appAutomationEthernetandSD.o.d 
	@${RM} ${OBJECTDIR}/appAutomationEthernetandSD.o 
	@${FIXDEPS} "${OBJECTDIR}/appAutomationEthernetandSD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appAutomationEthernetandSD.o.d" -o ${OBJECTDIR}/appAutomationEthernetandSD.o appAutomationEthernetandSD.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPeakEcoEthernet.o: appPeakEcoEthernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPeakEcoEthernet.o.d 
	@${RM} ${OBJECTDIR}/appPeakEcoEthernet.o 
	@${FIXDEPS} "${OBJECTDIR}/appPeakEcoEthernet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPeakEcoEthernet.o.d" -o ${OBJECTDIR}/appPeakEcoEthernet.o appPeakEcoEthernet.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPressureCurveCalibration.o: appPressureCurveCalibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPressureCurveCalibration.o.d 
	@${RM} ${OBJECTDIR}/appPressureCurveCalibration.o 
	@${FIXDEPS} "${OBJECTDIR}/appPressureCurveCalibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPressureCurveCalibration.o.d" -o ${OBJECTDIR}/appPressureCurveCalibration.o appPressureCurveCalibration.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/appPressureFillRelease.o: appPressureFillRelease.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/appPressureFillRelease.o.d 
	@${RM} ${OBJECTDIR}/appPressureFillRelease.o 
	@${FIXDEPS} "${OBJECTDIR}/appPressureFillRelease.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/appPressureFillRelease.o.d" -o ${OBJECTDIR}/appPressureFillRelease.o appPressureFillRelease.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/GSMFiles/board.o: GSMFiles/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GSMFiles" 
	@${RM} ${OBJECTDIR}/GSMFiles/board.o.d 
	@${RM} ${OBJECTDIR}/GSMFiles/board.o 
	@${FIXDEPS} "${OBJECTDIR}/GSMFiles/board.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/GSMFiles/board.o.d" -o ${OBJECTDIR}/GSMFiles/board.o GSMFiles/board.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/GSMFiles/cloudindustries_api.o: GSMFiles/cloudindustries_api.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GSMFiles" 
	@${RM} ${OBJECTDIR}/GSMFiles/cloudindustries_api.o.d 
	@${RM} ${OBJECTDIR}/GSMFiles/cloudindustries_api.o 
	@${FIXDEPS} "${OBJECTDIR}/GSMFiles/cloudindustries_api.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/GSMFiles/cloudindustries_api.o.d" -o ${OBJECTDIR}/GSMFiles/cloudindustries_api.o GSMFiles/cloudindustries_api.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/GSMFiles/fifo_buffer.o: GSMFiles/fifo_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GSMFiles" 
	@${RM} ${OBJECTDIR}/GSMFiles/fifo_buffer.o.d 
	@${RM} ${OBJECTDIR}/GSMFiles/fifo_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/GSMFiles/fifo_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/GSMFiles/fifo_buffer.o.d" -o ${OBJECTDIR}/GSMFiles/fifo_buffer.o GSMFiles/fifo_buffer.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o: GSMFiles/ublox_lisa_u230.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GSMFiles" 
	@${RM} ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o.d 
	@${RM} ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o 
	@${FIXDEPS} "${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o.d" -o ${OBJECTDIR}/GSMFiles/ublox_lisa_u230.o GSMFiles/ublox_lisa_u230.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/malloc.o: malloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/malloc.o.d 
	@${RM} ${OBJECTDIR}/malloc.o 
	@${FIXDEPS} "${OBJECTDIR}/malloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/malloc.o.d" -o ${OBJECTDIR}/malloc.o malloc.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/sd_spi.o: sd_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/sd_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/sd_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/sd_spi.o.d" -o ${OBJECTDIR}/sd_spi.o sd_spi.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/mmc.o: mmc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc.o.d 
	@${RM} ${OBJECTDIR}/mmc.o 
	@${FIXDEPS} "${OBJECTDIR}/mmc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/mmc.o.d" -o ${OBJECTDIR}/mmc.o mmc.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/logRun.o: logRun.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/logRun.o.d 
	@${RM} ${OBJECTDIR}/logRun.o 
	@${FIXDEPS} "${OBJECTDIR}/logRun.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/logRun.o.d" -o ${OBJECTDIR}/logRun.o logRun.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/display.o: display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/display.o.d 
	@${RM} ${OBJECTDIR}/display.o 
	@${FIXDEPS} "${OBJECTDIR}/display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/display.o.d" -o ${OBJECTDIR}/display.o display.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/common.o: common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/common.o.d 
	@${RM} ${OBJECTDIR}/common.o 
	@${FIXDEPS} "${OBJECTDIR}/common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/common.o.d" -o ${OBJECTDIR}/common.o common.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/gsm_main.o: gsm_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gsm_main.o.d 
	@${RM} ${OBJECTDIR}/gsm_main.o 
	@${FIXDEPS} "${OBJECTDIR}/gsm_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/gsm_main.o.d" -o ${OBJECTDIR}/gsm_main.o gsm_main.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/configurations.o: configurations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configurations.o.d 
	@${RM} ${OBJECTDIR}/configurations.o 
	@${FIXDEPS} "${OBJECTDIR}/configurations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/configurations.o.d" -o ${OBJECTDIR}/configurations.o configurations.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/onBoardADC.o: onBoardADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardADC.o.d 
	@${RM} ${OBJECTDIR}/onBoardADC.o 
	@${FIXDEPS} "${OBJECTDIR}/onBoardADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/onBoardADC.o.d" -o ${OBJECTDIR}/onBoardADC.o onBoardADC.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/onBoardRTCC.o: onBoardRTCC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o.d 
	@${RM} ${OBJECTDIR}/onBoardRTCC.o 
	@${FIXDEPS} "${OBJECTDIR}/onBoardRTCC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/onBoardRTCC.o.d" -o ${OBJECTDIR}/onBoardRTCC.o onBoardRTCC.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/sensors.o: sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensors.o.d 
	@${RM} ${OBJECTDIR}/sensors.o 
	@${FIXDEPS} "${OBJECTDIR}/sensors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/sensors.o.d" -o ${OBJECTDIR}/sensors.o sensors.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/sensorValueConvertion.o: sensorValueConvertion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o.d 
	@${RM} ${OBJECTDIR}/sensorValueConvertion.o 
	@${FIXDEPS} "${OBJECTDIR}/sensorValueConvertion.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/sensorValueConvertion.o.d" -o ${OBJECTDIR}/sensorValueConvertion.o sensorValueConvertion.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/readConfig.o: readConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/readConfig.o.d 
	@${RM} ${OBJECTDIR}/readConfig.o 
	@${FIXDEPS} "${OBJECTDIR}/readConfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/readConfig.o.d" -o ${OBJECTDIR}/readConfig.o readConfig.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/melacs_spi.o: melacs_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/melacs_spi.o.d 
	@${RM} ${OBJECTDIR}/melacs_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/melacs_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/melacs_spi.o.d" -o ${OBJECTDIR}/melacs_spi.o melacs_spi.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/buzzer.o: buzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buzzer.o.d 
	@${RM} ${OBJECTDIR}/buzzer.o 
	@${FIXDEPS} "${OBJECTDIR}/buzzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/buzzer.o.d" -o ${OBJECTDIR}/buzzer.o buzzer.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/setup.o: setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/setup.o.d 
	@${RM} ${OBJECTDIR}/setup.o 
	@${FIXDEPS} "${OBJECTDIR}/setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/setup.o.d" -o ${OBJECTDIR}/setup.o setup.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/_ext/893916629/appheader.o: ../_startup_ESK_EXP16/boot_app/appheader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/893916629" 
	@${RM} ${OBJECTDIR}/_ext/893916629/appheader.o.d 
	@${RM} ${OBJECTDIR}/_ext/893916629/appheader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/893916629/appheader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/_ext/893916629/appheader.o.d" -o ${OBJECTDIR}/_ext/893916629/appheader.o ../_startup_ESK_EXP16/boot_app/appheader.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/firmwareRecoveryUpdate.o: firmwareRecoveryUpdate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/firmwareRecoveryUpdate.o.d 
	@${RM} ${OBJECTDIR}/firmwareRecoveryUpdate.o 
	@${FIXDEPS} "${OBJECTDIR}/firmwareRecoveryUpdate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/firmwareRecoveryUpdate.o.d" -o ${OBJECTDIR}/firmwareRecoveryUpdate.o firmwareRecoveryUpdate.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/wrapper.o: wrapper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/wrapper.o.d 
	@${RM} ${OBJECTDIR}/wrapper.o 
	@${FIXDEPS} "${OBJECTDIR}/wrapper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/wrapper.o.d" -o ${OBJECTDIR}/wrapper.o wrapper.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/tcp_start.o: tcp_start.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_start.o.d 
	@${RM} ${OBJECTDIR}/tcp_start.o 
	@${FIXDEPS} "${OBJECTDIR}/tcp_start.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/tcp_start.o.d" -o ${OBJECTDIR}/tcp_start.o tcp_start.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/tcp_server.o: tcp_server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tcp_server.o.d 
	@${RM} ${OBJECTDIR}/tcp_server.o 
	@${FIXDEPS} "${OBJECTDIR}/tcp_server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/tcp_server.o.d" -o ${OBJECTDIR}/tcp_server.o tcp_server.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/mutex.o: mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mutex.o.d 
	@${RM} ${OBJECTDIR}/mutex.o 
	@${FIXDEPS} "${OBJECTDIR}/mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/mutex.o.d" -o ${OBJECTDIR}/mutex.o mutex.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/speedControl.o: speedControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/speedControl.o.d 
	@${RM} ${OBJECTDIR}/speedControl.o 
	@${FIXDEPS} "${OBJECTDIR}/speedControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/speedControl.o.d" -o ${OBJECTDIR}/speedControl.o speedControl.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/threeWayValve.o: threeWayValve.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/threeWayValve.o.d 
	@${RM} ${OBJECTDIR}/threeWayValve.o 
	@${FIXDEPS} "${OBJECTDIR}/threeWayValve.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/threeWayValve.o.d" -o ${OBJECTDIR}/threeWayValve.o threeWayValve.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/hBridge.o: hBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	@${FIXDEPS} "${OBJECTDIR}/hBridge.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/hBridge.o.d" -o ${OBJECTDIR}/hBridge.o hBridge.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/analogToPhysical.o: analogToPhysical.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogToPhysical.o.d 
	@${RM} ${OBJECTDIR}/analogToPhysical.o 
	@${FIXDEPS} "${OBJECTDIR}/analogToPhysical.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/analogToPhysical.o.d" -o ${OBJECTDIR}/analogToPhysical.o analogToPhysical.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/timeDifference.o: timeDifference.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timeDifference.o.d 
	@${RM} ${OBJECTDIR}/timeDifference.o 
	@${FIXDEPS} "${OBJECTDIR}/timeDifference.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/timeDifference.o.d" -o ${OBJECTDIR}/timeDifference.o timeDifference.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/analogSensor10bit.o: analogSensor10bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o.d 
	@${RM} ${OBJECTDIR}/analogSensor10bit.o 
	@${FIXDEPS} "${OBJECTDIR}/analogSensor10bit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/analogSensor10bit.o.d" -o ${OBJECTDIR}/analogSensor10bit.o analogSensor10bit.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
${OBJECTDIR}/usb_composite.o: usb_composite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_composite.o.d 
	@${RM} ${OBJECTDIR}/usb_composite.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_composite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -D_USE_ESK -D_PIC32_ -DUSE_DUAL_TCP_STACK -DBOOTAPP -I"../../include" -I"../../stdio" -I"." -MMD -MF "${OBJECTDIR}/usb_composite.o.d" -o ${OBJECTDIR}/usb_composite.o usb_composite.c    -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -msmart-io=0
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/InresolMain_20Jan2017.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../servers/fsys-fatfs/fsys-fatfs.a ../../iolib/iolib.a ../../servers/usb/usb_server/usb_server.a ../../servers/usb/device/usbd_cdc_serial_driver/usbd_cdc_serial_driver.a ../../servers/usb/device/usbd_core/usbd_core.a ../../servers/usb/device/usbd_pic32x_port/usbd_pic32x_port.a ../../servers/tty/tty.a ../../stdio/stdiolib.a ../../kernel/Unison.a ../../servers/_ipv6/tcp6/server6/tcp_dual.a ../../servers/_ipv6/tcp6/ENC424J600_v6/ENC424J600_v6.a ../../servers/usb/device/usbd_msc_driver/usbd_msc_driver.a  ../_startup_ESK_EXP16/boot_app/app_32MX795F512L.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/InresolMain_20Jan2017.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\servers\fsys-fatfs\fsys-fatfs.a ..\..\iolib\iolib.a ..\..\servers\usb\usb_server\usb_server.a ..\..\servers\usb\device\usbd_cdc_serial_driver\usbd_cdc_serial_driver.a ..\..\servers\usb\device\usbd_core\usbd_core.a ..\..\servers\usb\device\usbd_pic32x_port\usbd_pic32x_port.a ..\..\servers\tty\tty.a ..\..\stdio\stdiolib.a ..\..\kernel\Unison.a ..\..\servers\_ipv6\tcp6\server6\tcp_dual.a ..\..\servers\_ipv6\tcp6\ENC424J600_v6\ENC424J600_v6.a ..\..\servers\usb\device\usbd_msc_driver\usbd_msc_driver.a      -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--defsym=_min_heap_size=0,--defsym=_min_stack_size=0,-L"C:/Program Files/Microchip/MPLAB_v8.10/MPLAB C32/lib",-L"C:/Program Files/Microchip/MPLAB_v8.10/MPLAB C32/pic32mx/lib",-Map="${DISTDIR}/fatfs-sd.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/InresolMain_20Jan2017.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../servers/fsys-fatfs/fsys-fatfs.a ../../iolib/iolib.a ../../servers/usb/usb_server/usb_server.a ../../servers/usb/device/usbd_cdc_serial_driver/usbd_cdc_serial_driver.a ../../servers/usb/device/usbd_core/usbd_core.a ../../servers/usb/device/usbd_pic32x_port/usbd_pic32x_port.a ../../servers/tty/tty.a ../../stdio/stdiolib.a ../../kernel/Unison.a ../../servers/_ipv6/tcp6/server6/tcp_dual.a ../../servers/_ipv6/tcp6/ENC424J600_v6/ENC424J600_v6.a ../../servers/usb/device/usbd_msc_driver/usbd_msc_driver.a ../_startup_ESK_EXP16/boot_app/app_32MX795F512L.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/InresolMain_20Jan2017.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\servers\fsys-fatfs\fsys-fatfs.a ..\..\iolib\iolib.a ..\..\servers\usb\usb_server\usb_server.a ..\..\servers\usb\device\usbd_cdc_serial_driver\usbd_cdc_serial_driver.a ..\..\servers\usb\device\usbd_core\usbd_core.a ..\..\servers\usb\device\usbd_pic32x_port\usbd_pic32x_port.a ..\..\servers\tty\tty.a ..\..\stdio\stdiolib.a ..\..\kernel\Unison.a ..\..\servers\_ipv6\tcp6\server6\tcp_dual.a ..\..\servers\_ipv6\tcp6\ENC424J600_v6\ENC424J600_v6.a ..\..\servers\usb\device\usbd_msc_driver\usbd_msc_driver.a      -DXPRJ_BOOTAPP=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--defsym=_min_stack_size=0,-L"C:/Program Files/Microchip/MPLAB_v8.10/MPLAB C32/lib",-L"C:/Program Files/Microchip/MPLAB_v8.10/MPLAB C32/pic32mx/lib",-Map="${DISTDIR}/fatfs-sd.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/InresolMain_20Jan2017.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/BOOTAPP
	${RM} -r dist/BOOTAPP

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
