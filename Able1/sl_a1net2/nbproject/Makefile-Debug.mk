#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/929555163/PassiveSocket.o \
	${OBJECTDIR}/_ext/929555163/HTTPActiveSocket.o \
	${OBJECTDIR}/_ext/1815965308/HttpWebService.o \
	${OBJECTDIR}/_ext/929555163/ActiveSocket.o \
	${OBJECTDIR}/_ext/1815965308/URL.o \
	${OBJECTDIR}/_ext/929555163/SimpleSocket.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsl_a1net2.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsl_a1net2.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsl_a1net2.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsl_a1net2.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsl_a1net2.a

${OBJECTDIR}/_ext/929555163/PassiveSocket.o: ../public/a1net2/SimpleSockets/PassiveSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/929555163
	${RM} $@.d
	$(COMPILE.cc) -g -DUNIX -D_LINUX -I../public/a1core -I../public -I../public/a1net2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/929555163/PassiveSocket.o ../public/a1net2/SimpleSockets/PassiveSocket.cpp

${OBJECTDIR}/_ext/929555163/HTTPActiveSocket.o: ../public/a1net2/SimpleSockets/HTTPActiveSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/929555163
	${RM} $@.d
	$(COMPILE.cc) -g -DUNIX -D_LINUX -I../public/a1core -I../public -I../public/a1net2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/929555163/HTTPActiveSocket.o ../public/a1net2/SimpleSockets/HTTPActiveSocket.cpp

${OBJECTDIR}/_ext/1815965308/HttpWebService.o: ../public/a1net2/HttpWebService.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1815965308
	${RM} $@.d
	$(COMPILE.cc) -g -DUNIX -D_LINUX -I../public/a1core -I../public -I../public/a1net2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1815965308/HttpWebService.o ../public/a1net2/HttpWebService.cpp

${OBJECTDIR}/_ext/929555163/ActiveSocket.o: ../public/a1net2/SimpleSockets/ActiveSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/929555163
	${RM} $@.d
	$(COMPILE.cc) -g -DUNIX -D_LINUX -I../public/a1core -I../public -I../public/a1net2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/929555163/ActiveSocket.o ../public/a1net2/SimpleSockets/ActiveSocket.cpp

${OBJECTDIR}/_ext/1815965308/URL.o: ../public/a1net2/URL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1815965308
	${RM} $@.d
	$(COMPILE.cc) -g -DUNIX -D_LINUX -I../public/a1core -I../public -I../public/a1net2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1815965308/URL.o ../public/a1net2/URL.cpp

${OBJECTDIR}/_ext/929555163/SimpleSocket.o: ../public/a1net2/SimpleSockets/SimpleSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/929555163
	${RM} $@.d
	$(COMPILE.cc) -g -DUNIX -D_LINUX -I../public/a1core -I../public -I../public/a1net2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/929555163/SimpleSocket.o ../public/a1net2/SimpleSockets/SimpleSocket.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsl_a1net2.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
