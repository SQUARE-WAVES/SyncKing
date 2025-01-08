# Project Name
TARGET = sync_king

DEV_SOURCES = $(wildcard src/devices/*.cpp)
AUDIO_SOURCES = $(wildcard src/audio/*.cpp)
UI_SOURCES = $(wildcard src/screens/*.cpp)

MAIN_SOURCES = src/tasks.cpp src/globals.cpp src/sync_king.cpp src/interface.cpp


# Sources
CPP_SOURCES = $(DEV_SOURCES) $(AUDIO_SOURCES) $(UI_SOURCES) $(MAIN_SOURCES)

#src/looper.cpp

# Library Locations
LIBDAISY_DIR = ../libDaisy
DAISYSP_DIR = ../DaisySP

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

