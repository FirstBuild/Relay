#---------
#
# CppUTest Examples Makefile
#
#----------

#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

CPPUTEST_CXXFLAGS += -Wno-old-style-cast

#--- Inputs ----#
COMPONENT_NAME = RelayTests
CPPUTEST_HOME = ~/source/cpputest

CPPUTEST_USE_GCOV = Y

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc

CPPUTEST_WARNINGFLAGS += -Wno-unknown-warning-option
CPPUTEST_CXXFLAGS += -fprofile-arcs -ftest-coverage

# This line is overriding the default new macros.  This is helpful
# when using std library includes like <list> and other containers
# so that memory leak detection does not conflict with stl.
#CPPUTEST_MEMLEAK_DETECTOR_NEW_MACRO_FILE = -include ApplicationLib/ExamplesNewOverrides.h

SRC_DIRS = ..\

SRC_FILES = ../src/Relay.cpp \
	    
TEST_SRC_DIRS = \
	test \
	test/AllTests \
	test/RelayTests \

MOCKS_SRC_DIRS = test/mocks \
		 test/mocks/Arduino

INCLUDE_DIRS = ./ \
	test/mocks \
	test/mocks/Arduino \
	$(CPPUTEST_HOME)/include \
	../src/

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

