#!/bin/bash

# the path to the libraries must be known before execute the program
# change to put the corresponding paths. It must be the same as in the Makefile
# path to OpenCV. e.g. /home/user/opencv_4.9.0
# path to GLEW, e.g /home/user/glew-EGL-2.1.0 (GLEW must be compiled to support EGL)

export LD_LIBRARY_PATH=PATH_TO_EGL/lib:PATH_TO_OPENCV/lib:$LD_LIBRARY_PATH

# pass all the arguments
./mhd "$@"

