#Makefile for image feature space analyser

CC=g++
COMPILE_FLAGS= -g -Wall -std=c++0x -I $(INC_DIRS)
LINK_FLAGS= -L $(LIB_DIRS) 
INC_DIRS= /usr/include/python2.6/ `pkg-config --cflags opencv` 
LIB_DIRS= `pkg-config --libs opencv` -lpython2.6
TARGET=analyser

OBJECTS=	main.o \
		analyser.o \
		helper_functions.o \
		converter_functions.o

All:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LINK_FLAGS)

%.o:%.cpp
	$(CC) $< -o $@ -c $(COMPILE_FLAGS)

clean:
	rm -f *.o 