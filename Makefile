# Name of the folders where the libraries are. Change them to match your configuration
# path to OpenCV. e.g. /home/user/opencv_4.9.0
OPENCV_LIB=PATH_TO_OPENCV
# path to GLEW, e.g /home/user/glew-EGL-2.1.0 (GLEW must be compiled to support EGL)
EGL_LIB=PATH_TO_GLEW


# Name of the compiler
CC=g++

# compilation options, e.g., -g for debugging, -Wall for warnings, -O2 for optimization
CFLAGS=-O2 -Wall
CXXFLAGS=-O2 -Wall
INCPATH= -I. -I$(OPENCV_LIB)/include/opencv4 -I$(OPENCV_LIB)/include/opencv4/opencv2 -I$(EGL_LIB)/include -I./shaders

# Libraries
LIBS= -L$(EGL_LIB)/lib -lGLEW -L$(OPENCV_LIB)/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lEGL -lpthread -lGL

# Name of the program
APP=mhd

# folders for sources, objets and program
SRCDIR=src
OBJDIR=obj
BINDIR=.

# fins all .cc in SRCDIR for compiling
SOURCES=$(wildcard $(SRCDIR)/*.cc)

# change the folder and extension of the files to get the names of files in OBJDIR
OBJECTS=$(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SOURCES))

# Rules
all: $(BINDIR)/$(APP)

# How to build the program
$(BINDIR)/$(APP): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

# How to build the .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< $(CXXFLAGS) $(INCPATH)

# Clean all the files
clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/$(APP)
