# This Makefile requires GNU make, which is called gmake on Solaris systems
#
# 'make'        : builds and runs the project
# 'make clean'  : remove build products

PROG = bin/*

OBJS = obj/*

ARCH = $(shell uname -m)
OS   = $(shell uname -s)

CC = gcc

LDLIBS  = -L/usr/lib/x86_64-linux-gnu -L/usr/lib -lm -lOpenCL
INCLUDE = -ITools -I/usr/include/CL

.PHONY: clean Prac2 run
all:    
	clean Prac2 run
	mkdir -p $(PROG) $(OBJS)
	
clean:
	rm -f -r $(PROG) $(OBJS)

Prac2:
	mkdir -p $(PROG) $(OBJS)
	$(CC) $(INCLUDE) -c main.c -o obj/main.o
	$(CC) $(INCLUDE) -c Tools/OpenCL_Wrapper.c -o obj/OpenCL_Wrapper.o
	$(CC) $(INCLUDE) -c Tools/Timer.c -o obj/Timer.o
	$(CC) -o bin/Prac2 obj/main.o obj/OpenCL_Wrapper.o obj/Timer.o $(LDLIBS)

run:
	bin/Prac2

