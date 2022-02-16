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

#include "JPEG.h"
//------------------------------------------------------------------------------

JPEG::JPEG(){
 Rows       = 0;
 Width      = 0;
 Height     = 0;
 Components = 0;
}
//------------------------------------------------------------------------------

JPEG::~JPEG(){
 Clear();
}
//------------------------------------------------------------------------------

void JPEG::Clear(){
 int j;

 if(Rows){
  for(j = 0; j < Height; j++){
   if(Rows[j]) delete[] Rows[j];
  }
  delete[] Rows;
 }

 Rows       = 0;
 Width      = 0;
 Height     = 0;
 Components = 0;
}
//------------------------------------------------------------------------------

bool JPEG::Allocate(int Width, int Height, int Components){
 Clear();

 this->Width      = Width;
 this->Height     = Height;
 this->Components = Components;

 int j;
 int Stride = Width * Components;

 Rows = new JSAMPLE*[Height];
 if(!Rows){
  printf("ERROR: Memory allocation failure\n");
  return false;
 }
 for(j = 0; j < Height; j++){
  Rows[j] = new JSAMPLE[Stride];
  if(!Rows[j]){
   printf("ERROR: Memory allocation failure\n");
   for(j++; j < Height; j++) Rows[j] = 0;
   return false;
  }
 }
 return true;
}
//------------------------------------------------------------------------------

bool JPEG::Read(const char* Filename){
 Clear();

 struct jpeg_decompress_struct D_Struct;
 struct jpeg_error_mgr jerr;
 FILE*  File;

 // Allocate and initialise JPEG decompression object
 D_Struct.err = jpeg_std_error(&jerr);
 jpeg_create_decompress(&D_Struct);

 // open & specify data source (eg, a file)
 File = fopen(Filename, "rb");
 if(!File){
  printf("ERROR: Can't open input file %s\n", Filename);
  return false;
 }
 jpeg_stdio_src(&D_Struct, File);

 // read file parameters with jpeg_read_header()
 jpeg_read_header(&D_Struct, 1);

 // Start decompressor
 jpeg_start_decompress(&D_Struct);

 // Create a frame struct & buffers and fill in the blanks
 printf(
  "Opened \"%s\": width = %d, height = %d, c = %d\n",
  Filename,
  D_Struct.output_width,
  D_Struct.output_height,
  D_Struct.output_components
 );
 if(!Allocate(
  D_Struct.output_width,
  D_Struct.output_height,
  D_Struct.output_components
 )) return false;

 // Populate the rows
 while(D_Struct.output_scanline < D_Struct.output_height){
  jpeg_read_scanlines(&D_Struct, &(Rows[D_Struct.output_scanline]), 1);
 }

 // Finish
 jpeg_finish_decompress(&D_Struct);

 // Release JPEG decompression object & file
 jpeg_destroy_decompress(&D_Struct);
 fclose(File);
 printf("File closed\n\n");

 return true;
}
//------------------------------------------------------------------------------

bool JPEG::Write(const char* Filename){
 struct jpeg_compress_struct C_Struct;
 struct jpeg_error_mgr jerr;
 FILE*  File;

 // allocate and initialise JPEG compression object
 C_Struct.err = jpeg_std_error(&jerr);
 jpeg_create_compress(&C_Struct);

 // specify data destination (eg, a file)
 File = fopen(Filename, "wb");
 if(!File){
  printf("ERROR: Can't open output file %s\n", Filename);
  return false;
 }
 jpeg_stdio_dest(&C_Struct, File);

 // set parameters for compression

 // Set basic picture parameters (not optional)
 C_Struct.image_width      = Width;
 C_Struct.image_height     = Height;
 C_Struct.input_components = Components;
 switch(Components){
  case 1 : C_Struct.in_color_space = JCS_GRAYSCALE; break;
  case 3 : C_Struct.in_color_space = JCS_RGB;       break;

  default:
   printf("ERROR: Non-standard colourspace for compressing!\n");
   return false;
 }
 jpeg_set_defaults(&C_Struct);
 jpeg_set_quality (&C_Struct, OUT_QUALITY, 1);

 jpeg_start_compress(&C_Struct, 1);

 while(C_Struct.next_scanline < C_Struct.image_height){
  jpeg_write_scanlines(&C_Struct, &(Rows[C_Struct.next_scanline]), 1);
 }

 // Finish compression & close output

 jpeg_finish_compress(&C_Struct);
 fclose(File);

 // release JPEG compression object
 jpeg_destroy_compress(&C_Struct);

 return true;
}
//------------------------------------------------------------------------------
