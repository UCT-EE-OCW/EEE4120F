# This Makefile requires GNU make, which is called gmake on Solaris systems
#
# 'make'        : builds and runs the project
# 'make clean'  : remove build products

# where the executable program binary is placed:
PROG = bin/*
# Where the object files are placed:
OBJS = obj/*

# Which compiler to use, note for MPI a special purpose compiler is used
CC = mpic++

# Precompiled libraries to link in:
LDLIBS  = -L/usr/lib/openmpi/lib -L/usr/lib -lm -ljpeg -lmpi
# Included H files needed during compiling:
INCLUDE = -ITools -I/usr/lib/openmpi/include

.PHONY: clean Prac3 run
all:    clean Prac3 run

clean:
	rm -f -r $(PROG) $(OBJS)

Prac3:
	$(CC) $(INCLUDE) -c Prac3.cpp -o obj/Prac3.o
	$(CC) $(INCLUDE) -c Tools/JPEG.cpp -o obj/JPEG.o
	$(CC) $(INCLUDE) -c Tools/Timer.cpp -o obj/Timer.o
	$(CC) -o bin/Prac3 obj/Prac3.o obj/JPEG.o obj/Timer.o $(LDLIBS)

# you can type "make run" to execute the program in this case with a default of 5 nodes
run:
	mpirun -np 5 bin/Prac3

doxy: Prac3.cpp
	doxygen Prac3.doxy

