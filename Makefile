#Makefile for image feature space analyser

CC=g++
COMPILE_FLAGS= -g -Wall -std=c++0x -I $(INC_DIRS)
LINK_FLAGS= -L $(LIB_DIRS) 
INC_DIRS= /usr/local/include/TooN `pkg-config --cflags opencv`
LIB_DIRS= -llapack -lblas `pkg-config --libs opencv`
TARGET=analyser

OBJECTS=	main.o \
		analyser.o \
		helper_functions.o

All:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LINK_FLAGS)

%.o:%.cpp
	$(CC) $< -o $@ -c $(COMPILE_FLAGS)

clean:
	rm -f *.o 