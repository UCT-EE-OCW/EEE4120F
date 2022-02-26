#include "OpenCL_Wrapper.h"
//------------------------------------------------------------------------------

static cl_device_id     Device        = 0;
static cl_context       Context       = 0;
static cl_command_queue Commands      = 0;
static cl_uint          MaxDimensions = 0;

static cl_kernel  Kernel  = 0;
static cl_program Program = 0;
//------------------------------------------------------------------------------

// Returns true if String starts with Test
static bool StartWith(const char* String, const char* Test){
 if(!String || !Test) return false;

 int j;
 for(j = 0; String[j] && Test[j]; j++){
  if(String[j] != Test[j]) return false;
 }
 if(Test[j]) return false;
 return true;
}
//------------------------------------------------------------------------------

// Chooses the vendor specified.  If Vendor is null, chooses the first one.
bool OpenCL_Init(const char* Vendor){
 static bool platforms_displayed = false;

 cl_int         error;
 cl_platform_id platform = 0;

 // Get number of platforms
 cl_uint num_platforms = 0;

 error = clGetPlatformIDs(0, 0, &num_platforms);
 if(error != CL_SUCCESS || num_platforms == 0){
  if(error == -1001){
   printf("Error: Vendor ICD problem - cannot find platforms.\n");
  }else if(error == CL_SUCCESS){
   printf("Error: No platforms available.\n");
  }else{
   printf("Error: Cannot find platforms.\n");
  }
  return false;
 }
 if(!platforms_displayed) printf("%d platforms available.\n", num_platforms);

 // Get list of platforms
 cl_platform_id* platforms =
  (cl_platform_id*)malloc(num_platforms*sizeof(cl_platform_id));

 error = clGetPlatformIDs(num_platforms, platforms, 0);
 if(error != CL_SUCCESS){
  printf("Error: Cannot list platforms.\n");
  free(platforms);
  return false;
 }

 int   j, c;
 int   platform_choice;
 char* Info = (char*)malloc(0x1000*sizeof(char));

 if(Vendor) platform_choice = -1;
 else       platform_choice =  0;

 for(j = 0; j < num_platforms; j++){
  if(platforms_displayed){
   clGetPlatformInfo(platforms[j], CL_PLATFORM_VENDOR    , 0x1000, Info, 0);
   if(StartWith(Info, Vendor)) platform_choice = j;
  }else{
   printf("\n");
   clGetPlatformInfo(platforms[j], CL_PLATFORM_NAME      , 0x1000, Info, 0);
   printf("Name      : %s\n", Info);
   clGetPlatformInfo(platforms[j], CL_PLATFORM_VENDOR    , 0x1000, Info, 0);
   if(StartWith(Info, Vendor)) platform_choice = j;
   printf("Vendor    : %s\n", Info);
   clGetPlatformInfo(platforms[j], CL_PLATFORM_VERSION   , 0x1000, Info, 0);
   printf("Version   : %s\n", Info);
   clGetPlatformInfo(platforms[j], CL_PLATFORM_PROFILE   , 0x1000, Info, 0);
   printf("Profile   : %s\n", Info);
   clGetPlatformInfo(platforms[j], CL_PLATFORM_EXTENSIONS, 0x1000, Info, 0);
   printf("Extensions: ");
   for(c = 0; Info[c]; c++){
    if(Info[c] == ' ') printf("\n            ");
    else               printf("%c", Info[c]   );
   }
   printf("\n");
  }
 }
 platforms_displayed = true;

 if(platform_choice < 0){
  printf("Error: Cannot find %s platform.\n", Vendor);
  free(Info);
  free(platforms);
  return false;

 }else{
  platform = platforms[platform_choice];
  clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0x1000, Info, 0);
  printf("\nUsing %s platform.\n\n", Info);
 }
 free(Info);
 free(platforms);

 // Get device ID
 error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &Device, 0);
 if(error != CL_SUCCESS){
  error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &Device, 0);
  if(error != CL_SUCCESS){
   printf("Error: Cannot get device ID.\n");
   return false;
  }
 }

 cl_ulong MemSize;
 cl_uint  ComputeUnits;
 size_t   WorkGroupSize;

 clGetDeviceInfo(
  Device, CL_DEVICE_GLOBAL_MEM_SIZE,
  sizeof(MemSize), &MemSize, 0
 );
 printf("Global memory size      : %u\n", (unsigned)MemSize);
 clGetDeviceInfo(
  Device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
  sizeof(MemSize), &MemSize, 0
 );
 printf("Global memory cache size: %u\n", (unsigned)MemSize);
 clGetDeviceInfo(
  Device, CL_DEVICE_LOCAL_MEM_SIZE,
  sizeof(MemSize), &MemSize, 0
 );
 printf("Local memory size       : %u\n", (unsigned)MemSize);
 clGetDeviceInfo(
  Device, CL_DEVICE_MAX_COMPUTE_UNITS,
  sizeof(ComputeUnits), &ComputeUnits, 0
 );
 printf("Maximum compute units   : %u\n", (unsigned)ComputeUnits);
 clGetDeviceInfo(
  Device, CL_DEVICE_MAX_WORK_GROUP_SIZE,
  sizeof(WorkGroupSize), &WorkGroupSize, 0
 );
 printf("Maximum work group size : %u\n", (unsigned)WorkGroupSize);
 printf("\n");

 // Create a compute context
 Context = clCreateContext(0, 1, &Device, 0, 0, &error);
 if(!Context || error != CL_SUCCESS){
  printf("Error: Failed to create a compute context.\n");
  return false;
 }

 // Create a command queue
 Commands = clCreateCommandQueue(Context, Device, 0, &error);
 if(!Commands || error != CL_SUCCESS){
  printf("Error: Failed to create a command queue.\n");
  clReleaseContext(Context);
  return false;
 }

 // Query the maximum dimensions
 clGetDeviceInfo(
  Device,
  CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
  sizeof(cl_uint),
  &MaxDimensions,
  0
 );
 printf("Maximum work dimensions supported: %d\n", (int)MaxDimensions);

 return true;
}
//------------------------------------------------------------------------------

void OpenCL_Destroy(){
 if(Commands) clReleaseCommandQueue(Commands);
 if(Context ) clReleaseContext     (Context );
 if(Program ) clReleaseProgram     (Program );
 if(Kernel  ) clReleaseKernel      (Kernel  );
}
//------------------------------------------------------------------------------

bool OpenCL_LoadKernel(const char* Filename, const char* Function){
 cl_int error;

 // Open file
 FILE* File = fopen(Filename, "rb");
 if(!File){
  printf("Error: Cannot open file: %s\n", Filename);
  return false;
 }

 // Get file size
 int FileSize;
 fseek(File, 0, SEEK_END);
 FileSize = ftell(File);
 fseek(File, 0, SEEK_SET);

 // Allocate source buffer
 char* Source = (char*)malloc((FileSize+1)*sizeof(char));
 if(!Source){
  printf("Error: Cannot allocate memory for source buffer.\n");
  fclose(File);
  return false;
 }

 // Read the file
 int j = 0;
 int c = fgetc(File);
 while(c != EOF){
  Source[j++] = (char)c;
  c = fgetc(File);
 }
 fclose(File);
 Source[j] = 0;

 // Create the compute program from the source buffer
 Program = clCreateProgramWithSource(
  Context,
  1, (const char**)&Source, 0,
  &error
 );
 if(!Program || error != CL_SUCCESS){
  printf("Error: Failed to create compute program.\n");
  free(Source);
  return false;
 }
 free(Source);

 // Build the program executable
 error = clBuildProgram(Program, 0, 0, 0, 0, 0);
 if(error != CL_SUCCESS){
  char Info[0x1000];
  printf("Error: Failed to build program executable:\n");
  clGetProgramBuildInfo(
   Program,
   Device,
   CL_PROGRAM_BUILD_LOG,
   0x1000,
   Info,
   0
  );
  printf("%s\n", Info);
  return false;
 }

 // Create the compute kernel in the program we wish to run
 Kernel = clCreateKernel(Program, Function, &error);
 if(!Kernel || error != CL_SUCCESS){
  printf("Error: Failed to create compute kernel.\n");
  return false;
 }

 return true;
}
//------------------------------------------------------------------------------

cl_mem OpenCL_CreateBuffer(cl_uint Argument, cl_mem_flags Flags, size_t Size){
 cl_int error;
 cl_mem Buffer;

 Buffer = clCreateBuffer(Context, Flags, Size, 0, &error);
 if(!Buffer || error != CL_SUCCESS){
  printf("Error: Failed to allocate buffer.\n");
  return 0;
 }

 error = clSetKernelArg(Kernel, Argument, sizeof(cl_mem), &Buffer);
 if(error != CL_SUCCESS){
  printf("Error: Failed to set kernel argument.\n");
  clReleaseMemObject(Buffer);
  return 0;
 }

 return Buffer;
}
//------------------------------------------------------------------------------

void OpenCL_FreeBuffer(cl_mem Buffer){
 clReleaseMemObject(Buffer);
}
//------------------------------------------------------------------------------

bool OpenCL_ConstantInt(cl_uint Argument, int Value){
 cl_int error = clSetKernelArg(Kernel, Argument, sizeof(int), &Value);
 if(error != CL_SUCCESS){
  printf("Error: Failed set integer constant.\n");
  return false;
 }
 return true;
}
//------------------------------------------------------------------------------

bool OpenCL_ReadData(cl_mem Buffer, size_t Size, void* Data){
 cl_int error = clEnqueueReadBuffer(
  Commands,
  Buffer,
  CL_TRUE,
  0,
  Size,
  Data,
  0, 0, 0
 );
 if(error != CL_SUCCESS){
  printf("Error: Failed to read buffer\n");
  return false;
 }
 return true;
}
//------------------------------------------------------------------------------

bool OpenCL_WriteData(cl_mem Buffer, size_t Size, void* Data){
 cl_int error = clEnqueueWriteBuffer(
  Commands,
  Buffer,
  CL_TRUE,
  0,
  Size,
  Data,
  0, 0, 0
 );
 if(error != CL_SUCCESS){
  printf("Error: Failed to write buffer.\n");
  return false;
 }
 return true;
}
//------------------------------------------------------------------------------

void OpenCL_PrepareLocalSize(int N, size_t* LocalSize){
 cl_int error;

 // Default
 LocalSize[0] = 1;
 LocalSize[1] = 1;

 // Get the maximum work group size for executing the kernel on the device
 size_t LocalMaxSize;

 error = clGetKernelWorkGroupInfo(
  Kernel,
  Device,
  CL_KERNEL_WORK_GROUP_SIZE,
  sizeof(LocalMaxSize),
  &LocalMaxSize,
  0
 );
 if(error != CL_SUCCESS){
  printf("Error: Failed to retrieve kernel work group info.\n");
  return;
 }else{
  printf("Maximum kernel work group size: %d:\n", (int)LocalMaxSize);
 }

 // Brute-force search for the optimal partitioning (maximum number of workers)
 int w;
 int h;
 int test;

 w = 1;
 while(w <= N){
  h = 1;
  while(h <= N){
   test = N/w * N/h;
   if(test <= LocalMaxSize && test > LocalSize[0]*LocalSize[1]){
    LocalSize[0] = N / w;
    LocalSize[1] = N / h;
   }
   h++;
   while((h < N) && (N % h)) h++;
  }
  w++;
  while((w < N) && (N % w)) w++;
 }
}
//------------------------------------------------------------------------------

bool OpenCL_Run(int N, size_t* LocalSize){
 cl_int error;

 printf(
  "Local work group size: %d x %d\n",
  (int)LocalSize[0],
  (int)LocalSize[1]
 );

 // Execute the kernel
 size_t GlobalSize[2] = {N, N};

 error  = clEnqueueNDRangeKernel(
  Commands,
  Kernel,
  2, // Dimensions
  0,
  GlobalSize,
  LocalSize,
  0, 0, 0
 );
 if(error != CL_SUCCESS){
  printf("Error: Failed to execute kernel (error %d).\n", error);
  return false;
 }

 // Wait for the commands to get serviced
 clFinish(Commands);

 return true;
}
//------------------------------------------------------------------------------
