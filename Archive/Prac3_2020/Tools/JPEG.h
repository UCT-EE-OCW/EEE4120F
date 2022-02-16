//==============================================================================
// Copyright (C) John-Philip Taylor
// tyljoh010@myuct.ac.za
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

#ifndef JPEG_h
#define JPEG_h
//------------------------------------------------------------------------------

/** JPEG Quality:

A quality level of 2-100 can be provided (default = 75, high quality = ~95,
low quality = ~25, utter pixellation = 2).  This controls the degree of
compression at the output.                                                    */

#define OUT_QUALITY 75
//------------------------------------------------------------------------------

#include <stdio.h>
extern "C" {
 #include "jpeglib.h"
}
//------------------------------------------------------------------------------

/** IMAGE DATA FORMATS:

The standard input image format is a rectangular array of pixels, with
each pixel having the same number of "component" values (colour channels).
Each pixel row is an array of JSAMPLEs (which are typically unsigned chars).
If you are working with colour data, then the colour values for each pixel
must be adjacent in the row; for example, R,G,B,R,G,B,R,G,B,... for 24-bit
RGB colour.                                                                   */

class JPEG{
 public:
  JSAMPLE** Rows; // Points to an array of pointers to the
                  // beginning of each row in the image buffer.
                  //
                  // Use to access the image buffer in a row-wise
                  // fashion, with:
                  // Rows[row][num_components*column + component]

  int Width;      // Number of columns in image */
  int Height;     // Number of rows in image
  int Components; // Number of components (usually RGB=3 or gray=1)

 private:
  void Clear();

 public:
  JPEG();
 ~JPEG();

  // Allocate memory for the image
  bool Allocate(int Width, int Height, int Components);

  // File I/O
  bool Read (const char* Filename);
  bool Write(const char* Filename);
};
//------------------------------------------------------------------------------

#endif
//------------------------------------------------------------------------------
