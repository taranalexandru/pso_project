#************************************************************
# Makefile
#************************************************************

#*****************
# Application data
#*****************

APP_NAME = app
SRC_DIR = ../src
BIN_DIR = ../bin

#******
# Tools
#******

CXX = gcc
DEFINES = -DLINUX

CXX_FLAGS = -std=c++11 -fno-exceptions -fno-rtti -O3 -Wall $(DEFINES)
LINK_FLAGS = $(DEFINES)

#*******************************
# Additional include directories
#*******************************

#INCLUDE_DIRS += 

#*******************************
# Additional library directories
#*******************************

#LIBRARY_DIRS += 

#*********************
# Additional libraries
#*********************

LIBS += pthread 
LIBS += m
LIBS += stdc++

#********
# Sources
#********

SOURCE_FILES += main.cpp
SOURCE_FILES += UString.cpp
SOURCE_FILES += WebCam.cpp

#************
# Conversions
#************

INCLUDE_DIRS := $(addprefix -I,$(INCLUDE_DIRS))
LIBRARY_DIRS := $(addprefix -L,$(LIBRARY_DIRS))
LIBS := $(addprefix -l,$(LIBS))

SOURCES := $(addprefix $(SRC_DIR)/,$(SOURCE_FILES))
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))

#************
# Build rules
#************

.PHONY: all
all:	$(APP_NAME)

$(APP_NAME): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(LINK_FLAGS) -o $(BIN_DIR)/$@ $^ $(LIBRARY_DIRS) $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/$(APP_NAME) $(OBJECTS)

