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
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DispMelacs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DispMelacs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
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
SOURCEFILES_QUOTED_IF_SPACED=Source/Analog.c Source/Bus.c Source/Common.c Source/Display.c Source/EPFlash.c Source/Fuses.c Source/IFlash.c Source/LED.c Source/Main.c Source/Numeric.c Source/Protocol.c Source/Switch.c Source/Timer.c Source/UART.c Source/Window.c Source/Core.asm Source/Data/Font_Courier.c Source/Data/Font_Icons.c Source/Logo.c Tools/Image_Logo.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Source/Analog.o ${OBJECTDIR}/Source/Bus.o ${OBJECTDIR}/Source/Common.o ${OBJECTDIR}/Source/Display.o ${OBJECTDIR}/Source/EPFlash.o ${OBJECTDIR}/Source/Fuses.o ${OBJECTDIR}/Source/IFlash.o ${OBJECTDIR}/Source/LED.o ${OBJECTDIR}/Source/Main.o ${OBJECTDIR}/Source/Numeric.o ${OBJECTDIR}/Source/Protocol.o ${OBJECTDIR}/Source/Switch.o ${OBJECTDIR}/Source/Timer.o ${OBJECTDIR}/Source/UART.o ${OBJECTDIR}/Source/Window.o ${OBJECTDIR}/Source/Core.o ${OBJECTDIR}/Source/Data/Font_Courier.o ${OBJECTDIR}/Source/Data/Font_Icons.o ${OBJECTDIR}/Source/Logo.o ${OBJECTDIR}/Tools/Image_Logo.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Source/Analog.o.d ${OBJECTDIR}/Source/Bus.o.d ${OBJECTDIR}/Source/Common.o.d ${OBJECTDIR}/Source/Display.o.d ${OBJECTDIR}/Source/EPFlash.o.d ${OBJECTDIR}/Source/Fuses.o.d ${OBJECTDIR}/Source/IFlash.o.d ${OBJECTDIR}/Source/LED.o.d ${OBJECTDIR}/Source/Main.o.d ${OBJECTDIR}/Source/Numeric.o.d ${OBJECTDIR}/Source/Protocol.o.d ${OBJECTDIR}/Source/Switch.o.d ${OBJECTDIR}/Source/Timer.o.d ${OBJECTDIR}/Source/UART.o.d ${OBJECTDIR}/Source/Window.o.d ${OBJECTDIR}/Source/Core.o.d ${OBJECTDIR}/Source/Data/Font_Courier.o.d ${OBJECTDIR}/Source/Data/Font_Icons.o.d ${OBJECTDIR}/Source/Logo.o.d ${OBJECTDIR}/Tools/Image_Logo.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Source/Analog.o ${OBJECTDIR}/Source/Bus.o ${OBJECTDIR}/Source/Common.o ${OBJECTDIR}/Source/Display.o ${OBJECTDIR}/Source/EPFlash.o ${OBJECTDIR}/Source/Fuses.o ${OBJECTDIR}/Source/IFlash.o ${OBJECTDIR}/Source/LED.o ${OBJECTDIR}/Source/Main.o ${OBJECTDIR}/Source/Numeric.o ${OBJECTDIR}/Source/Protocol.o ${OBJECTDIR}/Source/Switch.o ${OBJECTDIR}/Source/Timer.o ${OBJECTDIR}/Source/UART.o ${OBJECTDIR}/Source/Window.o ${OBJECTDIR}/Source/Core.o ${OBJECTDIR}/Source/Data/Font_Courier.o ${OBJECTDIR}/Source/Data/Font_Icons.o ${OBJECTDIR}/Source/Logo.o ${OBJECTDIR}/Tools/Image_Logo.o

# Source Files
SOURCEFILES=Source/Analog.c Source/Bus.c Source/Common.c Source/Display.c Source/EPFlash.c Source/Fuses.c Source/IFlash.c Source/LED.c Source/Main.c Source/Numeric.c Source/Protocol.c Source/Switch.c Source/Timer.c Source/UART.c Source/Window.c Source/Core.asm Source/Data/Font_Courier.c Source/Data/Font_Icons.c Source/Logo.c Tools/Image_Logo.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/DispMelacs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F67J93
MP_PROCESSOR_OPTION_LD=18f67j93
MP_LINKER_DEBUG_OPTION=  -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source/Core.o: Source/Core.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Core.o.d 
	@${RM} ${OBJECTDIR}/Source/Core.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/Source/Core.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG -d__MPLAB_DEBUGGER_PK3=1 -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/Source/Core.lst\" -e\"${OBJECTDIR}/Source/Core.err\" $(ASM_OPTIONS) -y -o\"${OBJECTDIR}/Source/Core.o\" \"Source/Core.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/Source/Core.o"
	@${FIXDEPS} "${OBJECTDIR}/Source/Core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/Source/Core.o: Source/Core.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Core.o.d 
	@${RM} ${OBJECTDIR}/Source/Core.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/Source/Core.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/Source/Core.lst\" -e\"${OBJECTDIR}/Source/Core.err\" $(ASM_OPTIONS) -y -o\"${OBJECTDIR}/Source/Core.o\" \"Source/Core.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/Source/Core.o"
	@${FIXDEPS} "${OBJECTDIR}/Source/Core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source/Analog.o: Source/Analog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Analog.o.d 
	@${RM} ${OBJECTDIR}/Source/Analog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Analog.o   Source/Analog.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Analog.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Analog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Bus.o: Source/Bus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Bus.o.d 
	@${RM} ${OBJECTDIR}/Source/Bus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Bus.o   Source/Bus.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Bus.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Bus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Common.o: Source/Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Common.o.d 
	@${RM} ${OBJECTDIR}/Source/Common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Common.o   Source/Common.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Common.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Display.o: Source/Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Display.o.d 
	@${RM} ${OBJECTDIR}/Source/Display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Display.o   Source/Display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Display.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/EPFlash.o: Source/EPFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/EPFlash.o.d 
	@${RM} ${OBJECTDIR}/Source/EPFlash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/EPFlash.o   Source/EPFlash.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/EPFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/EPFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Fuses.o: Source/Fuses.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Fuses.o.d 
	@${RM} ${OBJECTDIR}/Source/Fuses.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Fuses.o   Source/Fuses.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Fuses.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Fuses.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/IFlash.o: Source/IFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/IFlash.o.d 
	@${RM} ${OBJECTDIR}/Source/IFlash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/IFlash.o   Source/IFlash.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/IFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/IFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/LED.o: Source/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/LED.o.d 
	@${RM} ${OBJECTDIR}/Source/LED.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/LED.o   Source/LED.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Main.o: Source/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Main.o.d 
	@${RM} ${OBJECTDIR}/Source/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Main.o   Source/Main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Numeric.o: Source/Numeric.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Numeric.o.d 
	@${RM} ${OBJECTDIR}/Source/Numeric.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Numeric.o   Source/Numeric.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Numeric.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Numeric.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Protocol.o: Source/Protocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Protocol.o.d 
	@${RM} ${OBJECTDIR}/Source/Protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Protocol.o   Source/Protocol.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Protocol.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Protocol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Switch.o: Source/Switch.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Switch.o.d 
	@${RM} ${OBJECTDIR}/Source/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Switch.o   Source/Switch.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Switch.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Switch.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Timer.o: Source/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Timer.o.d 
	@${RM} ${OBJECTDIR}/Source/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Timer.o   Source/Timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Timer.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/UART.o: Source/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/UART.o.d 
	@${RM} ${OBJECTDIR}/Source/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/UART.o   Source/UART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Window.o: Source/Window.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Window.o.d 
	@${RM} ${OBJECTDIR}/Source/Window.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Window.o   Source/Window.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Window.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Window.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Data/Font_Courier.o: Source/Data/Font_Courier.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source/Data" 
	@${RM} ${OBJECTDIR}/Source/Data/Font_Courier.o.d 
	@${RM} ${OBJECTDIR}/Source/Data/Font_Courier.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Data/Font_Courier.o   Source/Data/Font_Courier.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Data/Font_Courier.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Data/Font_Courier.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Data/Font_Icons.o: Source/Data/Font_Icons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source/Data" 
	@${RM} ${OBJECTDIR}/Source/Data/Font_Icons.o.d 
	@${RM} ${OBJECTDIR}/Source/Data/Font_Icons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Data/Font_Icons.o   Source/Data/Font_Icons.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Data/Font_Icons.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Data/Font_Icons.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Logo.o: Source/Logo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Logo.o.d 
	@${RM} ${OBJECTDIR}/Source/Logo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Logo.o   Source/Logo.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Logo.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Logo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Tools/Image_Logo.o: Tools/Image_Logo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Tools" 
	@${RM} ${OBJECTDIR}/Tools/Image_Logo.o.d 
	@${RM} ${OBJECTDIR}/Tools/Image_Logo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Tools/Image_Logo.o   Tools/Image_Logo.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Tools/Image_Logo.o 
	@${FIXDEPS} "${OBJECTDIR}/Tools/Image_Logo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/Source/Analog.o: Source/Analog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Analog.o.d 
	@${RM} ${OBJECTDIR}/Source/Analog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Analog.o   Source/Analog.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Analog.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Analog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Bus.o: Source/Bus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Bus.o.d 
	@${RM} ${OBJECTDIR}/Source/Bus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Bus.o   Source/Bus.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Bus.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Bus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Common.o: Source/Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Common.o.d 
	@${RM} ${OBJECTDIR}/Source/Common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Common.o   Source/Common.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Common.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Display.o: Source/Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Display.o.d 
	@${RM} ${OBJECTDIR}/Source/Display.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Display.o   Source/Display.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Display.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/EPFlash.o: Source/EPFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/EPFlash.o.d 
	@${RM} ${OBJECTDIR}/Source/EPFlash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/EPFlash.o   Source/EPFlash.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/EPFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/EPFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Fuses.o: Source/Fuses.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Fuses.o.d 
	@${RM} ${OBJECTDIR}/Source/Fuses.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Fuses.o   Source/Fuses.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Fuses.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Fuses.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/IFlash.o: Source/IFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/IFlash.o.d 
	@${RM} ${OBJECTDIR}/Source/IFlash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/IFlash.o   Source/IFlash.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/IFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/IFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/LED.o: Source/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/LED.o.d 
	@${RM} ${OBJECTDIR}/Source/LED.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/LED.o   Source/LED.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Main.o: Source/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Main.o.d 
	@${RM} ${OBJECTDIR}/Source/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Main.o   Source/Main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Numeric.o: Source/Numeric.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Numeric.o.d 
	@${RM} ${OBJECTDIR}/Source/Numeric.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Numeric.o   Source/Numeric.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Numeric.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Numeric.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Protocol.o: Source/Protocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Protocol.o.d 
	@${RM} ${OBJECTDIR}/Source/Protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Protocol.o   Source/Protocol.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Protocol.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Protocol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Switch.o: Source/Switch.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Switch.o.d 
	@${RM} ${OBJECTDIR}/Source/Switch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Switch.o   Source/Switch.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Switch.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Switch.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Timer.o: Source/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Timer.o.d 
	@${RM} ${OBJECTDIR}/Source/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Timer.o   Source/Timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Timer.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/UART.o: Source/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/UART.o.d 
	@${RM} ${OBJECTDIR}/Source/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/UART.o   Source/UART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Window.o: Source/Window.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Window.o.d 
	@${RM} ${OBJECTDIR}/Source/Window.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Window.o   Source/Window.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Window.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Window.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Data/Font_Courier.o: Source/Data/Font_Courier.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source/Data" 
	@${RM} ${OBJECTDIR}/Source/Data/Font_Courier.o.d 
	@${RM} ${OBJECTDIR}/Source/Data/Font_Courier.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Data/Font_Courier.o   Source/Data/Font_Courier.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Data/Font_Courier.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Data/Font_Courier.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Data/Font_Icons.o: Source/Data/Font_Icons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source/Data" 
	@${RM} ${OBJECTDIR}/Source/Data/Font_Icons.o.d 
	@${RM} ${OBJECTDIR}/Source/Data/Font_Icons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Data/Font_Icons.o   Source/Data/Font_Icons.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Data/Font_Icons.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Data/Font_Icons.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Source/Logo.o: Source/Logo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/Logo.o.d 
	@${RM} ${OBJECTDIR}/Source/Logo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Source/Logo.o   Source/Logo.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Source/Logo.o 
	@${FIXDEPS} "${OBJECTDIR}/Source/Logo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Tools/Image_Logo.o: Tools/Image_Logo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Tools" 
	@${RM} ${OBJECTDIR}/Tools/Image_Logo.o.d 
	@${RM} ${OBJECTDIR}/Tools/Image_Logo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms --extended -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Tools/Image_Logo.o   Tools/Image_Logo.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Tools/Image_Logo.o 
	@${FIXDEPS} "${OBJECTDIR}/Tools/Image_Logo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DispMelacs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    GeniusDisplay.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "GeniusDisplay.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" -u_EXTENDEDMODE -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/DispMelacs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/DispMelacs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   GeniusDisplay.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "GeniusDisplay.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" -u_EXTENDEDMODE -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/DispMelacs.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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
