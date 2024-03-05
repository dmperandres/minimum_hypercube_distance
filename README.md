# Minimum Hypercube Distance
This is the code of the Minimum Hypercube Distance[1] method implemented with GPU.

[1] J. D. Martı́n-Ramos, G. Chiari, SmART scan: A method to produce composition maps using any elemental, molecular and image data, Journal of Cultural Heritage 39 (2019) 260–269. doi:10.1016/j.culher.2019.04.003.

## General
This repository contains the source code for the MHD program that we developed as part of our publication: XXX

## Project website
https://calipso.ugr.es/xmapslab.org

## Note
Please note the software is provided "as is".  Use it at your own risk, although data loss is unlikely. Do take the standard precautions like saving your work in other programs.

## Requirements
This project compiles under Linux. The project requires these additional components:

* ```OpenCV```, checked with version 4.9: https://opencv.org/
* ```GLEW```, checked with version 2.1: https://glew.sourceforge.net/

The GLEW library must be compiled to include EGL

### Installation of the requirements under Linux
* update your environment: `sudo apt update ; sudo apt upgrade`
* install the compiler and other complementary tools: `sudo apt install build-essential libxcb-cursor0 cmake cmake-qt-gui wget git`
* create a folder to place all the necessary code and libraries and change to that folder: `cd ~ ; mkdir code ; cd code`
* now we get and compile [OpenCV](https://opencv.org/)
  * download the sources: `wget https://github.com/opencv/opencv/archive/4.9.0.zip`
  * unzip the downloaded archive: `unzip 4.9.0.zip`
  * change the name of the created folder: `mv opencv-4.9.0 opencv-4.9`
  * create a new folder to hold the created library: `mkdir opencv-4.9.0`
  * change to the sources directory: `cd opencv-4.9`
  * create a new folder to hold the object code: `mkdir build`
  * start the CMake GUI: `cmake-gui`
  * click the "Browse Source..." button and select the "sources" folder of OpenCV, by default this should be `/home/user/code/opencv-4.9` with `user` being your Linux user name
  * click the "Browse Build..." button and select the "build" folder you previously created for OpenCV, by default this should be `/home/user/code/opencv-4.9/build`
  * click the "Configure" button and select "Unix Makefiles" from the drop-down list, leave "Use native compilers" selected, then click the "Finish" button
  * this runs some processes and then shows some options; from these options select BUILD_JPEG and BUILD_PNG, in addition to the already selected ones
  * specify where the library and complementary files will be placed for a local installation: in the field CMAKE_INSTALL_PREFIX change `/usr/local` to `/home/user/code/opencv-4.9.0`
  * click the "Generate" button to generate the Makefiles, then close the CMake GUI window
  * back in the command line, change to build folder: `cd build`
  * compile OpenCV by running `make` (depending on your machine and its processors it could be done quicker with the `-j` option and specifying the number of threads to use; e.g., `make -j4`); this process may take quite a while ...
  * finally do the local installation: `make install`
  * this should have added the compiled OpenCV to `~/code/opencv-4.9.0`
* now we get and and compile [GLEW](https://glew.sourceforge.net/)
  * change back to the code directory: `cd ~/code`
  * download the sources: `wget https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip/download -O glew.zip`
  * unzip the downloaded archive: `unzip glew.zip`
  * rename the generated archive to avoid errors with the installation later: `mv glew-2.1.0 glew-2.1`
  * create a folder for the resulting installation: `mkdir glew-2.1.0`
  * if you follow this process on a real machine then the needed OpenGL drivers and development files for X11 should be installed already; nothing do to at this point
  * if, in contrast, you follow this process in a virtual machine then we have to install the needed OpenGL drivers and development files for X11 (using free drivers)
    * run `sudo apt install freeglut3-dev libx11-dev`
  * change to the GLEW sources folder: `cd glew-2.1`
  * edit the Makefile to specify Makefile a local installation instead of a global one: `nano Makefile`, look for `GLEW_DEST`, change `/usr` to `/home/user/code/glew-2.1.0`
  * also you need to indicate that EGL must be included. This is done by commenting this line "SYSTEM ?= $(shell config/config.guess | cut -d - -f 3 | sed -e 's/[0-9\.]//g;')" and adding this "SYSTEM=linux-egl". It is a good idea to change the destination folder to get a different version of GLEW. Otherwise it will only run for console applications.
  * save the file with Ctrl-O, and then exit nano with Ctrl-X
  * compile GLEW: `make`
  * install GLEW: `make install`

## Compile the program
For compiling you only have to change the paths to the needed libraries, OpenCV and GLEW (compiled to include EGL). Once the changes are applied the program is compiled using the command ```make```

## Run the program
If everything compiles right, try to run the program with this command: ```./mhd```

This will give information about the parameters. In case that appears a message with a problem with some library or a unknown problem, it is probably due that the program can't find the libraries. A script has been included to solve this problem. You have to change the paths to the needed libraries and the run the program with this command: ```./mhd.bat```

