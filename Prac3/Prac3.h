//==============================================================================
// Copyright (C) John-Philip Taylor
// tyljoh010@myuct.ac.za
//
// Revised by S Winberg 2018
//
// This file is part of the EEE4084F Course
//
// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//==============================================================================

#ifndef Prac3_h
#define Prac3_h
//------------------------------------------------------------------------------

#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//------------------------------------------------------------------------------

#include "JPEG.h"
#include "Timer.h"
//------------------------------------------------------------------------------

#define BUFSIZE 128
#define TAG       0
//------------------------------------------------------------------------------

// MPI House-keeping
int numprocs;
//------------------------------------------------------------------------------

// Input and output buffers
JPEG Input;
JPEG Output;
//------------------------------------------------------------------------------

void Master();       // This is the "main" process (rank 0)
void Slave (int ID); // ID is the process "rank"
//------------------------------------------------------------------------------

#endif
//------------------------------------------------------------------------------
