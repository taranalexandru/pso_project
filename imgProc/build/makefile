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

INCLUDE_DIRS += /usr/local/include/opencv
INCLUDE_DIRS += /usr/local/include
INCLUDE_DIRS += /usr/local/include/opencv2

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
LIBS += opencv_highgui
LIBS += opencv_videostab
LIBS += opencv_video
LIBS += opencv_shape
LIBS += opencv_stitching
LIBS += opencv_superres
LIBS += opencv_features2d
LIBS += opencv_imgcodecs
LIBS += opencv_photo
LIBS += opencv_ml
LIBS += opencv_imgproc
LIBS += opencv_flann
LIBS += opencv_core
LIBS += opencv_face
LIBS += opencv_objdetect
LIBS += opencv_calib3d
LIBS += opencv_videoio

#********
# Sources
#********

SOURCE_FILES += main.cpp
SOURCE_FILES += UString.cpp
SOURCE_FILES += WebCam.cpp
SOURCE_FILES += ImageWorker.cpp
SOURCE_FILES += FaceDetector.cpp

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

