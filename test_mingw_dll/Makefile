###############################################################################
#
# Generic Makefile for C/C++ Program
#
# Author: whyglinux (whyglinux AT hotmail DOT com)
# Date: 2006/03/04

# Description:
# The makefile searches in directories for the source files
# with extensions specified in , then compiles the sources
# and finally produces the , the executable file, by linking
# the objectives.

# Usage:
# $ make compile and link the program.
# $ make objs compile only (no linking. Rarely used).
# $ make clean clean the objectives and dependencies.
# $ make cleanall clean the objectives, dependencies and executable.
# $ make rebuild rebuild the program. The same as make clean && make all.
#==============================================================================

## Customizing Section: adjust the following if necessary.
##=============================================================================

############### Added by cxp ##############
TARGET_NAME := test.dll
PREFIX ?= $(CROSS_COMPILE)
POSTFIX := $(CROSS_COMPILE_POSTFIX)
AS := $(PREFIX)as$(POSTFIX)
LD := $(PREFIX)gcc$(POSTFIX)
###########################################

# The executable file name.
# It must be specified.
PROGRAM := $(TARGET_NAME)

# The directories in which source files reside.
# At least one path should be specified.
# SRCDIRS := . # current directory
SRCDIRS := .
SRCDIRS += ../main_window/share 
SRCDIRS += ../main_window/lua 
SRCDIRS += ../main_window/common

# The source file types (headers excluded).
# At least one type should be specified.
# The valid suffixes are among of .c, .C, .cc, .cpp, .CPP, .c++, .cp, or .cxx.
# SRCEXTS := .c # C program
# SRCEXTS := .cpp # C++ program
# SRCEXTS := .c .cpp # C/C++ program
SRCEXTS := .cpp .c

# The compiling flags used only for C.
# If it is a C++ program, no need to set these flags.
# If it is a C and C++ merging program, set these flags for the C parts.
CFLAGS := -O2 -Wall 
CFLAGS += -I.
CFLAGS += -I../main_window/share 
CFLAGS += -I../main_window/lua 
CFLAGS += -I../main_window/common
CFLAGS += -I../main_window/platform

CXXFLAGS := $(CFLAGS)

CFLAGS += $(APPEND_CFLAGS) -std=gnu99

# The compiling flags used only for C++.
# If it is a C program, no need to set these flags.
# If it is a C and C++ merging program, set these flags for the C++ parts.
OBJCOPY := $(PREFIX)objcopy
OBJCOPY +=

# The library and the link options ( C and C++ common).
LDFLAGS := $(APPEND_LDFLAGS) -lstdc++ -lm -ldl 
LDFLAGS += -lmingw32 -lmsvcrt -lgcc_s -lgcc 
LDFLAGS += -lkernel32 -lwinmm -luser32 -lgdi32 -lcomctl32 -lcomdlg32 -lole32 -luuid -lws2_32
LDFLAGS += -Xlinker "--enable-auto-import" -shared  -Wl,--retain-symbols-file=export.txt

## Implict Section: change the following only when necessary.
##=============================================================================
# The C program compiler. Uncomment it to specify yours explicitly.
CC = $(PREFIX)gcc$(POSTFIX)

# The C++ program compiler. Uncomment it to specify yours explicitly.
CXX = $(PREFIX)g++$(POSTFIX)

# Uncomment the 2 lines to compile C programs as C++ ones.
#CC = $(CXX)
#CFLAGS = $(CXXFLAGS)

# The command used to delete file.
RM = rm -f

## Stable Section: usually no need to be changed. But you can add more.
##=============================================================================
SHELL = /bin/sh
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))

OBJS = $(foreach x,$(SRCEXTS), \
$(patsubst %$(x),%.$(TARGET_NAME).o,$(filter %$(x),$(SOURCES))))

DEPS = $(patsubst %.$(TARGET_NAME).o,%.$(TARGET_NAME).d,$(OBJS))

.PHONY : all objs clean cleanall rebuild

all : $(PROGRAM)
-include $(DEPS)

# Rules for creating the dependency files (.d).
#---------------------------------------------------

# Rules for producing the objects.
#---------------------------------------------------
objs : $(OBJS)
%.$(TARGET_NAME).o : %.c
	$(CC) -c $(CFLAGS) $< -o $@ -MMD -MF $*.$(TARGET_NAME).d -MP
%.$(TARGET_NAME).o : %.C
	$(CC) -c $(CXXFLAGS) $< -o $@ -MMD -MF $*.$(TARGET_NAME).d -MP
%.$(TARGET_NAME).o : %.cc
	$(CC) -c $(CXXFLAGS) $< -o $@ -MMD -MF $*.$(TARGET_NAME).d -MP
%.$(TARGET_NAME).o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ -MMD -MF $*.$(TARGET_NAME).d -MP
%.$(TARGET_NAME).o : %.CPP
	$(CXX) -c $(CXXFLAGS) $< -o $@ -MMD -MF $*.$(TARGET_NAME).d -MP
%.$(TARGET_NAME).o : %.c++
	$(CXX) -c $(CXXFLAGS) $< -o $@ -MMD -MF $*.$(TARGET_NAME).d -MP
%.$(TARGET_NAME).o : %.cp
	$(CXX) -c $(CXXFLAGS) $< -o $@ -MMD -MF $*.$(TARGET_NAME).d -MP
%.$(TARGET_NAME).o : %.cxx
	$(CXX) -c $(CXXFLAGS) $< -o $@ -MMD -MF $*.$(TARGET_NAME).d -MP

# Rules for producing the executable.
#----------------------------------------------
$(PROGRAM) : $(OBJS)
ifeq ($(strip $(SRCEXTS)), .c) # C file
	$(LD) -o $(PROGRAM) $(OBJS) $(LDFLAGS)
else # C++ file
	$(LD) -o $(PROGRAM) $(OBJS) $(LDFLAGS)
endif

-include $(DEPS)

rebuild: clean all

clean :
	for name in `echo $(SRCDIRS)`; \
    do \
        $(RM) $$name/*.$(TARGET_NAME).o $$name/*.$(TARGET_NAME).d $(PROGRAM); \
    done

#############################################################################
### End of the Makefile ## Suggestions are welcome ## All rights reserved ###
#############################################################################
