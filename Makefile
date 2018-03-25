#
# OMNeT++/OMNEST Makefile for OMNetCom
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out
#

# Name of target to be created (-o option)
TARGET = OMNetCom$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -ISimApp \
    -Iresults \
    -Isimulations \
    -Isimulations/model \
    -Isimulations/results \
    -Isrc \
    -Isrc/Common \
    -Isrc/EPON \
    -Isrc/EPON/IPACT \
    -Isrc/EPON/Queue \
    -Isrc/Host \
    -Isrc/SDH

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/SimApp/drv_base.o \
    $O/SimApp/drv_sstp.o \
    $O/SimApp/drv_xml.o \
    $O/SimApp/IEDdata.o \
    $O/SimApp/main.o \
    $O/SimApp/MinimalEnv.o \
    $O/SimApp/modelconfig.o \
    $O/SimApp/pugixml.o \
    $O/SimApp/SimApp.o \
    $O/SimApp/SocketApp.o \
    $O/simulations/model/SimSink.o \
    $O/simulations/model/SimSource.o \
    $O/src/Common/App.o \
    $O/src/Common/BaseChannel.o \
    $O/src/Common/L2Queue.o \
    $O/src/Common/Manager.o \
    $O/src/Common/Routing.o \
    $O/src/Common/Sink.o \
    $O/src/Common/Source.o \
    $O/src/EPON/cTDMPON.o \
    $O/src/EPON/EPON_Queue.o \
    $O/src/EPON/Scheduler.o \
    $O/src/EPON/Splitter.o \
    $O/src/EPON/IPACT/InterScheduler.o \
    $O/src/EPON/IPACT/IntraScheduler.o \
    $O/src/EPON/Queue/MultiQueue.o \
    $O/src/EPON/Queue/Queue.o \
    $O/src/SDH/SDH_Queue.o \
    $O/src/SDH/SDH_Routing.o \
    $O/src/Common/Packet_m.o \
    $O/src/EPON/mpcp_m.o \
    $O/src/SDH/SDH_Packet_m.o

# Message files
MSGFILES = \
    src/Common/Packet.msg \
    src/EPON/mpcp.msg \
    src/SDH/SDH_Packet.msg

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f OMNetCom OMNetCom.exe libOMNetCom.so libOMNetCom.a libOMNetCom.dll libOMNetCom.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h
	$(Q)-rm -f SimApp/*_m.cc SimApp/*_m.h SimApp/*_sm.cc SimApp/*_sm.h
	$(Q)-rm -f results/*_m.cc results/*_m.h results/*_sm.cc results/*_sm.h
	$(Q)-rm -f simulations/*_m.cc simulations/*_m.h simulations/*_sm.cc simulations/*_sm.h
	$(Q)-rm -f simulations/model/*_m.cc simulations/model/*_m.h simulations/model/*_sm.cc simulations/model/*_sm.h
	$(Q)-rm -f simulations/results/*_m.cc simulations/results/*_m.h simulations/results/*_sm.cc simulations/results/*_sm.h
	$(Q)-rm -f src/*_m.cc src/*_m.h src/*_sm.cc src/*_sm.h
	$(Q)-rm -f src/Common/*_m.cc src/Common/*_m.h src/Common/*_sm.cc src/Common/*_sm.h
	$(Q)-rm -f src/EPON/*_m.cc src/EPON/*_m.h src/EPON/*_sm.cc src/EPON/*_sm.h
	$(Q)-rm -f src/EPON/IPACT/*_m.cc src/EPON/IPACT/*_m.h src/EPON/IPACT/*_sm.cc src/EPON/IPACT/*_sm.h
	$(Q)-rm -f src/EPON/Queue/*_m.cc src/EPON/Queue/*_m.h src/EPON/Queue/*_sm.cc src/EPON/Queue/*_sm.h
	$(Q)-rm -f src/Host/*_m.cc src/Host/*_m.h src/Host/*_sm.cc src/Host/*_sm.h
	$(Q)-rm -f src/SDH/*_m.cc src/SDH/*_m.h src/SDH/*_sm.cc src/SDH/*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc SimApp/*.cc results/*.cc simulations/*.cc simulations/model/*.cc simulations/results/*.cc src/*.cc src/Common/*.cc src/EPON/*.cc src/EPON/IPACT/*.cc src/EPON/Queue/*.cc src/Host/*.cc src/SDH/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/SimApp/IEDdata.o: SimApp/IEDdata.cc
$O/SimApp/MinimalEnv.o: SimApp/MinimalEnv.cc \
	SimApp/SocketApp.h \
	SimApp/sysconfig.h \
	src/Common/Packet_m.h
$O/SimApp/SimApp.o: SimApp/SimApp.cc \
	SimApp/SimApp.h \
	SimApp/SocketApp.h \
	SimApp/drv_sstp.h \
	SimApp/sstp_def.h \
	SimApp/sysconfig.h \
	src/Common/Packet_m.h
$O/SimApp/SocketApp.o: SimApp/SocketApp.cc \
	SimApp/SocketApp.h \
	SimApp/sysconfig.h
$O/SimApp/drv_base.o: SimApp/drv_base.cc \
	SimApp/drv_base.h \
	SimApp/sysconfig.h
$O/SimApp/drv_sstp.o: SimApp/drv_sstp.cc \
	SimApp/drv_sstp.h \
	SimApp/sysconfig.h
$O/SimApp/drv_xml.o: SimApp/drv_xml.cc \
	SimApp/drv_xml.h
$O/SimApp/main.o: SimApp/main.cc \
	SimApp/MinimalEnv.cc \
	SimApp/SimApp.h \
	SimApp/SocketApp.h \
	SimApp/drv_sstp.h \
	SimApp/drv_xml.h \
	SimApp/modelconfig.h \
	SimApp/sstp_def.h \
	SimApp/sysconfig.h \
	src/Common/Packet_m.h
$O/SimApp/modelconfig.o: SimApp/modelconfig.cc \
	SimApp/drv_xml.h \
	SimApp/modelconfig.h
$O/SimApp/pugixml.o: SimApp/pugixml.cc
$O/simulations/model/SimSink.o: simulations/model/SimSink.cc
$O/simulations/model/SimSource.o: simulations/model/SimSource.cc \
	src/Common/Packet_m.h
$O/src/Common/App.o: src/Common/App.cc \
	src/Common/Packet_m.h
$O/src/Common/BaseChannel.o: src/Common/BaseChannel.cc
$O/src/Common/L2Queue.o: src/Common/L2Queue.cc \
	src/Common/L2Queue.h
$O/src/Common/Manager.o: src/Common/Manager.cc
$O/src/Common/Packet_m.o: src/Common/Packet_m.cc \
	src/Common/Packet_m.h
$O/src/Common/Routing.o: src/Common/Routing.cc \
	src/Common/Packet_m.h \
	src/Common/Routing.h
$O/src/Common/Sink.o: src/Common/Sink.cc
$O/src/Common/Source.o: src/Common/Source.cc \
	src/Common/Packet_m.h
$O/src/EPON/EPON_Queue.o: src/EPON/EPON_Queue.cc \
	src/Common/L2Queue.h
$O/src/EPON/Scheduler.o: src/EPON/Scheduler.cc \
	src/Common/Packet_m.h \
	src/EPON/Scheduler.h \
	src/EPON/cTDMPON.h \
	src/EPON/mpcp_m.h
$O/src/EPON/Splitter.o: src/EPON/Splitter.cc \
	src/EPON/Splitter.h \
	src/EPON/cTDMPON.h \
	src/EPON/mpcp_m.h
$O/src/EPON/cTDMPON.o: src/EPON/cTDMPON.cc \
	src/EPON/cTDMPON.h \
	src/EPON/mpcp_m.h
$O/src/EPON/mpcp_m.o: src/EPON/mpcp_m.cc \
	src/EPON/mpcp_m.h
$O/src/EPON/IPACT/InterScheduler.o: src/EPON/IPACT/InterScheduler.cc \
	src/Common/Packet_m.h \
	src/EPON/IPACT/InterScheduler.h \
	src/EPON/Queue/MultiQueue.h \
	src/EPON/Queue/Queue.h \
	src/EPON/Scheduler.h \
	src/EPON/cTDMPON.h \
	src/EPON/mpcp_m.h
$O/src/EPON/IPACT/IntraScheduler.o: src/EPON/IPACT/IntraScheduler.cc \
	src/Common/Packet_m.h \
	src/EPON/IPACT/IntraScheduler.h \
	src/EPON/Queue/Queue.h \
	src/EPON/Scheduler.h \
	src/EPON/cTDMPON.h \
	src/EPON/mpcp_m.h
$O/src/EPON/Queue/MultiQueue.o: src/EPON/Queue/MultiQueue.cc \
	src/EPON/Queue/MultiQueue.h \
	src/EPON/Queue/Queue.h \
	src/EPON/cTDMPON.h \
	src/EPON/mpcp_m.h
$O/src/EPON/Queue/Queue.o: src/EPON/Queue/Queue.cc \
	src/EPON/Queue/Queue.h \
	src/EPON/cTDMPON.h \
	src/EPON/mpcp_m.h
$O/src/SDH/SDH_Packet_m.o: src/SDH/SDH_Packet_m.cc \
	src/SDH/SDH_Packet_m.h
$O/src/SDH/SDH_Queue.o: src/SDH/SDH_Queue.cc \
	src/Common/L2Queue.h \
	src/SDH/SDH_Packet_m.h
$O/src/SDH/SDH_Routing.o: src/SDH/SDH_Routing.cc \
	src/Common/Packet_m.h \
	src/Common/Routing.h \
	src/SDH/SDH_Packet_m.h

