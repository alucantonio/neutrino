#include "opencl.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// "get_error" FUNCTION //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
const char* get_error(cl_int error)
{
  switch(error)
  {
    // run-time and JIT compiler errors
    case      0: return "CL_SUCCESS";
    case     -1: return "CL_DEVICE_NOT_FOUND";
    case     -2: return "CL_DEVICE_NOT_AVAILABLE";
    case     -3: return "CL_COMPILER_NOT_AVAILABLE";
    case     -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case     -5: return "CL_OUT_OF_RESOURCES";
    case     -6: return "CL_OUT_OF_HOST_MEMORY";
    case     -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case     -8: return "CL_MEM_COPY_OVERLAP";
    case     -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case    -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case    -11: return "CL_BUILD_PROGRAM_FAILURE";
    case    -12: return "CL_MAP_FAILURE";
    case    -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case    -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case    -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case    -16: return "CL_LINKER_NOT_AVAILABLE";
    case    -17: return "CL_LINK_PROGRAM_FAILURE";
    case    -18: return "CL_DEVICE_PARTITION_FAILED";
    case    -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // compile-time errors
    case    -30: return "CL_INVALID_VALUE";
    case    -31: return "CL_INVALID_DEVICE_TYPE";
    case    -32: return "CL_INVALID_PLATFORM";
    case    -33: return "CL_INVALID_DEVICE";
    case    -34: return "CL_INVALID_CONTEXT";
    case    -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case    -36: return "CL_INVALID_COMMAND_QUEUE";
    case    -37: return "CL_INVALID_HOST_PTR";
    case    -38: return "CL_INVALID_MEM_OBJECT";
    case    -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case    -40: return "CL_INVALID_IMAGE_SIZE";
    case    -41: return "CL_INVALID_SAMPLER";
    case    -42: return "CL_INVALID_BINARY";
    case    -43: return "CL_INVALID_BUILD_OPTIONS";
    case    -44: return "CL_INVALID_PROGRAM";
    case    -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case    -46: return "CL_INVALID_KERNEL_NAME";
    case    -47: return "CL_INVALID_KERNEL_DEFINITION";
    case    -48: return "CL_INVALID_KERNEL";
    case    -49: return "CL_INVALID_ARG_INDEX";
    case    -50: return "CL_INVALID_ARG_VALUE";
    case    -51: return "CL_INVALID_ARG_SIZE";
    case    -52: return "CL_INVALID_KERNEL_ARGS";
    case    -53: return "CL_INVALID_WORK_DIMENSION";
    case    -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case    -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case    -56: return "CL_INVALID_GLOBAL_OFFSET";
    case    -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case    -58: return "CL_INVALID_EVENT";
    case    -59: return "CL_INVALID_OPERATION";
    case    -60: return "CL_INVALID_GL_OBJECT";
    case    -61: return "CL_INVALID_BUFFER_SIZE";
    case    -62: return "CL_INVALID_MIP_LEVEL";
    case    -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case    -64: return "CL_INVALID_PROPERTY";
    case    -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case    -66: return "CL_INVALID_COMPILER_OPTIONS";
    case    -67: return "CL_INVALID_LINKER_OPTIONS";
    case    -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // extension errors
    case  -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case  -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case  -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case  -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case  -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case  -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";

    default: return "Unknown OpenCL error";
  }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// "INFO" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
info::info(size_t value_size)
{
  size = value_size;                                                            // Setting value array size...
  value = (char*) malloc(value_size);                                           // Allocating value array...
}

info::~info()
{
  free(value);                                                                   // Freeing value array...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "PLATFORM" CLASS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
platform::platform(cl_uint pl_index)
{
  info*   profile     = new info(get_info_size(CL_PLATFORM_PROFILE));           // Platform info.
  info*   version     = new info(get_info_size(CL_PLATFORM_VERSION));           // Platform info.
  info*   name        = new info(get_info_size(CL_PLATFORM_NAME));              // Platform info.
  info*   vendor      = new info(get_info_size(CL_PLATFORM_VENDOR));            // Platform info.
  info*   extensions  = new info(get_info_size(CL_PLATFORM_EXTENSIONS));        // Platform info.

  profile->value    = get_info_value(CL_PLATFORM_PROFILE, profile->size);       // Setting info value...
  version->value    = get_info_value(CL_PLATFORM_VERSION, version->size);       // Setting info value...
  name->value       = get_info_value(CL_PLATFORM_NAME, name->size);             // Setting info value...
  vendor->value     = get_info_value(CL_PLATFORM_VENDOR, vendor->size);         // Setting info value...
  extensions->value = get_info_value(CL_PLATFORM_EXTENSIONS, extensions->size); // Setting info value...

  platform_index = pl_index;                                                    // Initializing platform index...
  theplatform = NULL;                                                           // Initializing theplatform...
}

// PRIVATE METHODS:
size_t platform::get_info_size(cl_platform_info parameter_name)
{
  cl_int  err;                                                                  // Error code.
  size_t  parameter_size;                                                       // Parameter size.

  // Getting platform information:
  err = clGetPlatformInfo(platform[platform_index]->theplatform,                // Platform id.
                          parameter_name,                                       // Parameter name.
                          0,                                                    // Dummy parameter size: "0" means we ask for the # of parameters, not for a value.
                          NULL,                                                 // Dummy parameter.
                          &parameter_size);                                     // Returned parameter size.

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  return (parameter_size);                                                      // Returning parameter size...
}

char* platform::get_info_value(cl_platform_info parameter_name, size_t parameter_size)
{
  cl_int  err;                                                                  // Error code.
  char*   parameter;                                                            // Parameter.

  // Getting platform information:
  err = clGetPlatformInfo(platform[index_platform]->theplatform,                // Platform id.
                          parameter_name,                                       // Parameter name.
                          parameter_size,                                       // Parameter size.
                          parameter,                                            // Parameter.
                          NULL);                                                // Returned parameter size (NULL = ignored).

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  return (parameter);                                                           // Returning parameter...
}

platform::~platform()
{
  delete profile;
  delete version;
  delete name;
  delete vendor;
  delete extensions;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "DEVICE" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
device::device(cl_uint num_device)
{
  info*   address_bits              = new info(get_info_size(CL_DEVICE_ADDRESS_BITS));
  info*   device_available          = new info(get_info_size(CL_DEVICE_AVAILABLE));
  info*   compiler_available        = new info(get_info_size(CL_DEVICE_COMPILER_AVAILABLE));
  info*   endian_little             = new info(get_info_size(CL_DEVICE_ENDIAN_LITTLE));
  info*   error_correction_support  = new info(get_info_size(CL_DEVICE_ERROR_CORRECTION_SUPPORT));

  address_bits->value               = get_info_value(CL_PLATFORM_PROFILE, address_bits->size);
  device_available->value           = get_info_value(CL_PLATFORM_VERSION, device_available->size);
  compiler_available->value         = get_info_value(CL_PLATFORM_NAME, compiler_available->size);
  endian_little->value              = get_info_value(CL_PLATFORM_VENDOR, endian_little->size);
  error_correction_support->value   = get_info_value(CL_PLATFORM_EXTENSIONS, error_correction_support->size);

  thedevice = NULL;                                                             // Initializing thedevice...
}

// PRIVATE METHODS:
size_t device::get_info_size(cl_device_info parameter_name)
{
  cl_int  err;                                                                  // Error code.
  size_t  parameter_size;                                                       // Parameter size.

  // Getting device information:
  err = clGetDeviceInfo(device[index_device],
                        name_param,
                        0,
                        NULL,
                        &size_value);

  if(err != CL_SUCCESS)
  {
    printf("Error:  %s\n", get_error(err));
    exit(err);
  }

  return (size_value);
}

device::~device()
{
  delete address_bits;
  delete device_available;
  delete compiler_available;
  delete endian_little;
  delete error_correction_support;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "OPENCL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
opencl::opencl()
{
  num_platforms = 0;
  num_devices = 0;
}

// PRIVATE METHODS:
cl_uint opencl::get_num_platforms()
{
  cl_int err;
  cl_uint num_platforms;

  printf("Action: getting number of OpenCL platforms... ");

  err = clGetPlatformIDs(0, NULL, &num_platforms);                              // Getting number of existing OpenCL platforms...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("\n        Found %d platform(s)!\n", num_platforms);
  printf("        DONE!\n");

  return num_platforms;                                                         // Returning number of existing platforms...
}

cl_uint opencl::get_platforms()
{
  cl_int          err;
  cl_platform_id* pl_id;
  int             i;

  num_platforms = get_num_platforms();
  pl_id = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);     // Allocating platform array...
  err = clGetPlatformIDs(num_platforms, pl_id, NULL);                           // Getting OpenCL platform IDs...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  existing_platform = new platform[num_platforms];

  for(i = 0; i < num_platforms; i++)
  {
    existing_platform[i]->theplatform = pl_id[i];
  }

  printf("\n        Found %d platform(s)!\n", num_platforms);
  printf("        DONE!\n");

  return(num_platforms);
}

cl_uint device::get_num_devices(int pl_index)
{
  cl_int err;
  cl_uint num_devices;

  printf("Action: getting number of OpenCL devices... ");

  err = clGetDeviceIDs(platform[index_index]->theplatform,                      // Getting number of existing OpenCL GPU devices...
                       CL_DEVICE_TYPE_GPU,
                       0,
                       NULL,
                       &num_devices);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("\n        Found %d device(s)!\n", num_devices);
  printf("        DONE!\n");

  return num_devices;                                                           // Returning number of existing OpenCL GPU devices...
}

opencl::get_devices(int pl_index)
{
  cl_int          err;
  cl_uint         num_devices;
  cl_device_id*   dev_id;
  int             i;

  num_devices = get_num_devices();
  dev_id = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);          // Allocating device array...
  err = clGetPlatformIDs(num_platforms, platfomr[pl_index]->theplatform, NULL); // Getting OpenCL device IDs...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  existing_device = new device[num_devices];

  for(i = 0; i < num_devices; i++)
  {
    existing_device[i]->thedevice = dev_id[i];
  }

  printf("\n        Found %d device(s)!\n", num_devices);
  printf("        DONE!\n");

  return(num_devices);
}

// PUBLIC METHODS:
opencl::init()
{
  cl_uint i;                                                                    // Defining platform number [#]...
  cl_uint j;                                                                    // Defining device [#]...
  cl_int  err;                                                                  // Defining error code [#]...

  num_platforms = get_platforms();                                              // Getting number of existing platforms [#]...

  for (i = 0; i < num_platforms; i++)
  {
    num_devices = get_devices(i);                                               // Getting # of existing devices on a platform [#]...
  }

  #ifdef __APPLE__                                                              // Checking for APPLE system...
    printf("Found APPLE system!\n");                                            // Printing message...

    CGLContextObj     kCGLContext     = CGLGetCurrentContext();                 // Setting APPLE OpenCL context properties...
    CGLShareGroupObj  kCGLShareGroup  = CGLGetShareGroup(kCGLContext);          // Setting APPLE OpenCL context properties...
    cl_context_properties properties[] =                                        // Setting APPLE OpenCL context properties...
    {
      CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
      (cl_context_properties) kCGLShareGroup,
      0
    };
  #endif

  #ifdef __linux__                                                              // Checking for LINUX system...
    printf("Found LINUX system!\n");                                            // Printing message...

    cl_context_properties properties[] =                                        // Setting LINUX OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetGLXContext(window),
      CL_GLX_DISPLAY_KHR, (cl_context_properties)glfwGetX11Display(),
      CL_CONTEXT_PLATFORM, (cl_context_properties)platform[0],
      0
    };
  #endif

  #ifdef __WINDOWS__                                                            // Checking for WINDOWS system...
    printf("Found WINDOWS system!\n");                                          // Printing message...

    cl_context_properties properties[] =                                        // Setting WINDOWS OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetWGLContext(window),
      CL_WGL_HDC_KHR, (cl_context_properties)GetDC(glfwGetWin32Window(window)),
      CL_CONTEXT_PLATFORM, (cl_context_properties)platform[0],
      0
    };
  #endif

  printf("Action: creating OpenCL context for GPU... ");                        // Printing message...

  // Creating OpenCL context:
  context = clCreateContext(properties,
                            num_devices,
                            existing_device,
                            NULL,
                            NULL,
                            &err);

  if(err != CL_SUCCESS)                                                         // Checking for error...
  {
    printf("\nError:  %s\n", get_error(err));                                   // Printing message...
    exit(err);                                                                  // Exiting...
  }

  printf("DONE!\n");                                                            // Printing message...
}

opencl::~opencl()
{
  cl_int err;

  printf("Action: releasing the OpenCL context... ");

  err = clReleaseContext(context);                                              // Releasing OpenCL context...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  free(device);                                                                // Freeing OpenCL devices...
  free(platform);                                                              // Freeing OpenCL platforms...

  printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "QUEUE" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::queue(int device_index)
{
  thequeue = NULL;
}

void queue::init()
{
  thequeue = clCreateCommandQueue(context, existing_device[0]->thedevice, 0, &err);                 // Creating OpenCL queue...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

queue::~queue()
{
  printf("Action: releasing the OpenCL command queue... ");

  err = clReleaseCommandQueue(thequeue);                                        // Releasing OpenCL queue...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "KERNEL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
kernel::kernel()
{
  thekernel = NULL;
  source = NULL;
  program = NULL;
  size = 0;
  dimension = 0;
  event = NULL;
}

void kernel::init(char* kernel_source, size_t kernel_size, cl_uint kernel_dimension)
{
  FILE* handle;                                                                 // Input file handle.

  printf("Action: loading OpenCL kernel source from file... ");

  source_file = kernel_source;
  size = kernel_size;
  dimension = kernel_dimension;

  handle = fopen(source_file, "rb");                                            // Opening OpenCL kernel source file...

  if(handle == NULL)
  {
    printf("\nError:  could not find the file!");
    exit(1);
  }

  fseek(handle, 0, SEEK_END);                                                   // Seeking end of file...
  source_size = (size_t)ftell(handle);                                          // Measuring file size...
  rewind(handle);                                                               // Rewinding to the beginning of the file...
  source = (char*)malloc(source_size + 1);                                      // Allocating buffer for reading the file...

  if (!(source))
  {
    printf("\nError:  unable to allocate buffer memory!\n");
    exit(EXIT_FAILURE);
  }

  fread(source, sizeof(char), source_size, handle);                             // Reading file (OpenCL kernel source)...
  source[source_size] = '\0';                                                   // Null-terminating buffer...
  fclose(handle);                                                               // Closing file.

  printf("DONE!\n");

  printf("Action: creating OpenCL program from kernel source... ");
  program = clCreateProgramWithSource(context,                                  // Creating OpenCL program from its source...
                                      1,
                                      (const char**)&source,
                                      &source_size, &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  free(source);                                                                 // Freeing OpenCL kernel buffer...
  printf("DONE!\n");

  printf("Action: building OpenCL program... ");
  err = clBuildProgram(program, 1, device, "", NULL, NULL);                     // Building OpenCL program...

  // Checking compiled kernel:
  if (err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));

    err = clGetProgramBuildInfo(program,                                        // Getting compiler information...
                                device[0],
                                CL_PROGRAM_BUILD_LOG,
                                0,
                                NULL,
                                &log_size);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    log = (char*) calloc(log_size + 1, sizeof(char));                           // Allocating log buffer...

    if (!log)
    {
      printf("\nError:  unable to allocate buffer memory log!\n");
      exit(EXIT_FAILURE);
    }

    err = clGetProgramBuildInfo(program, device[0],                             // Reading log...
                                CL_PROGRAM_BUILD_LOG,
                                log_size + 1,
                                log,
                                NULL);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    printf("%s\n", log);                                                        // Displaying log...
    free(log);                                                                  // Freeing log...
    exit(err);                                                                  // Exiting...
  }

  printf("DONE!\n");

  printf("Action: creating OpenCL kernel object from program... ");

  thekernel = clCreateKernel(program, KERNEL_NAME, &err);                       // Creating OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void kernel::execute(queue* q, kernel_event k_ev)
{
  err = clEnqueueNDRangeKernel(q->thequeue,                                     // Enqueueing OpenCL kernel (as a single task)...
                               thekernel,
                               dimension,
                               NULL,
                               &size,
                               NULL,
                               0,
                               NULL,
                               &event);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  switch(k_ev)
  {
    case WAIT:
      err = clWaitForEvents(1, &event);                                         // Waiting for kernel execution to be completed (host blocking)...

      if(err != CL_SUCCESS)
      {
        printf("\nError:  %s\n", get_error(err));
        exit(err);
      }
    break;

    case DONT_WAIT:
                                                                                // Doing nothing!
    break;

    default:
      err = clWaitForEvents(1, &event);                                         // Waiting for kernel execution to be completed (host blocking)...

      if(err != CL_SUCCESS)
      {
        printf("\nError:  %s\n", get_error(err));
        exit(err);
      }
    break;
  }


}

kernel::~kernel()
{
  printf("Action: releasing OpenCL kernel... ");

  err = clReleaseKernel(thekernel);                                             // Releasing OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

  printf("Action: releasing OpenCL kernel event... ");
  err = clReleaseEvent(event);                                                  // Releasing OpenCL event...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

  printf("Action: releasing OpenCL program... ");

  err = clReleaseProgram(program);                                              // Releasing OpenCL program...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}




/*
  switch (name_param)
  {
    case CL_PLATFORM_PROFILE:
      printf("        CL_PLATFORM_PROFILE = %s\n", value);
    break;

    case CL_PLATFORM_VERSION:
      printf("        CL_PLATFORM_VERSION = %s\n", value);
    break;

    case CL_PLATFORM_NAME:
      printf("        CL_PLATFORM_NAME = %s\n", value);
    break;

    case CL_PLATFORM_VENDOR:
      printf("        CL_PLATFORM_VENDOR = %s\n", value);
    break;

    case CL_PLATFORM_EXTENSIONS:
      printf("        CL_PLATFORM_EXTENSIONS = %s\n", value);
  }

*/




/*
case CL_DEVICE_ADDRESS_BITS:
  printf("        CL_DEVICE_ADDRESS_BITS = %s\n", value);
break;

case CL_DEVICE_AVAILABLE:
  printf("        CL_DEVICE_AVAILABLE = %s\n", value);
break;

case CL_DEVICE_COMPILER_AVAILABLE:
  printf("        CL_DEVICE_COMPILER_AVAILABLE = %s\n", value);
break;

case CL_DEVICE_ENDIAN_LITTLE:
  printf("        CL_DEVICE_ENDIAN_LITTLE = %s\n", value);
break;

case CL_DEVICE_ERROR_CORRECTION_SUPPORT:
  printf("        CL_DEVICE_ERROR_CORRECTION_SUPPORT = %s\n", value);
break;

case CL_DEVICE_EXECUTION_CAPABILITIES:
  printf("        CL_DEVICE_EXECUTION_CAPABILITIES = %s\n", value);
break;

case CL_DEVICE_EXTENSIONS:
  printf("        CL_DEVICE_EXTENSIONS = %s\n", value);
break;

case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:
  printf("        CL_DEVICE_GLOBAL_MEM_CACHE_SIZE = %s\n", value);
break;

case CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:
  printf("        CL_DEVICE_GLOBAL_MEM_CACHE_TYPE = %s\n", value);
break;

case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:
  printf("        CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE = %s\n", value);
break;

case CL_DEVICE_GLOBAL_MEM_SIZE:
  printf("        CL_DEVICE_GLOBAL_MEM_SIZE = %s\n", value);
break;

case CL_DEVICE_IMAGE_SUPPORT:
  printf("        CL_DEVICE_IMAGE_SUPPORT = %s\n", value);
break;

case CL_DEVICE_IMAGE2D_MAX_HEIGHT:
  printf("        CL_DEVICE_IMAGE2D_MAX_HEIGHT = %s\n", value);
break;

case CL_DEVICE_IMAGE2D_MAX_WIDTH:
  printf("        CL_DEVICE_IMAGE2D_MAX_WIDTH = %s\n", value);
break;

case CL_DEVICE_IMAGE3D_MAX_DEPTH:
  printf("        CL_DEVICE_IMAGE3D_MAX_DEPTH = %s\n", value);
break;

case CL_DEVICE_IMAGE3D_MAX_HEIGHT:
  printf("        CL_DEVICE_IMAGE3D_MAX_HEIGHT = %s\n", value);
break;

case CL_DEVICE_IMAGE3D_MAX_WIDTH:
  printf("        CL_DEVICE_IMAGE3D_MAX_WIDTH = %s\n", value);
break;

case CL_DEVICE_LOCAL_MEM_SIZE:
  printf("        CL_DEVICE_LOCAL_MEM_SIZE = %s\n", value);
break;

case CL_DEVICE_LOCAL_MEM_TYPE:
  printf("        CL_DEVICE_LOCAL_MEM_TYPE = %s\n", value);
break;

case CL_DEVICE_MAX_CLOCK_FREQUENCY:
  printf("        CL_DEVICE_MAX_CLOCK_FREQUENCY = %s\n", value);
break;

case CL_DEVICE_MAX_COMPUTE_UNITS:
  printf("        CL_DEVICE_MAX_COMPUTE_UNITS = %d\n", (int)*value);
break;

case CL_DEVICE_MAX_CONSTANT_ARGS:
  printf("        CL_DEVICE_MAX_CONSTANT_ARGS = %s\n", value);
break;

case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:
  printf("        CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE = %s\n", value);
break;

case CL_DEVICE_MAX_MEM_ALLOC_SIZE:
  printf("        CL_DEVICE_MAX_MEM_ALLOC_SIZE = %s\n", value);
break;

case CL_DEVICE_MAX_PARAMETER_SIZE:
  printf("        CL_DEVICE_MAX_PARAMETER_SIZE = %s\n", value);
break;

case CL_DEVICE_MAX_READ_IMAGE_ARGS:
  printf("        CL_DEVICE_MAX_READ_IMAGE_ARGS = %s\n", value);
break;

case CL_DEVICE_MAX_SAMPLERS:
  printf("        CL_DEVICE_MAX_SAMPLERS = %s\n", value);
break;

case CL_DEVICE_MAX_WORK_GROUP_SIZE:
  printf("        CL_DEVICE_MAX_WORK_GROUP_SIZE = %s\n", value);
break;

case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:
  printf("        CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS = %s\n", value);
break;

case CL_DEVICE_MAX_WORK_ITEM_SIZES:
  printf("        CL_DEVICE_MAX_WORK_ITEM_SIZES = %s\n", value);
break;

case CL_DEVICE_MAX_WRITE_IMAGE_ARGS:
  printf("        CL_DEVICE_MAX_WRITE_IMAGE_ARGS = %s\n", value);
break;

case CL_DEVICE_MEM_BASE_ADDR_ALIGN:
  printf("        CL_DEVICE_MEM_BASE_ADDR_ALIGN = %s\n", value);
break;

case CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE:
  printf("        CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE = %s\n", value);
break;

case CL_DEVICE_NAME:
  printf("        CL_DEVICE_NAME = %s\n", value);
break;

case CL_DEVICE_PLATFORM:
  printf("        CL_DEVICE_PLATFORM = %s\n", value);
break;

case CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR:
  printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR = %s\n", value);
break;

case CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE:
  printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE = %s\n", value);
break;

case CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT:
  printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT = %s\n", value);
break;

case CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT:
  printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT = %s\n", value);
break;

case CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG:
  printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG = %s\n", value);
break;

case CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT:
  printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT = %s\n", value);
break;

case CL_DEVICE_PROFILE:
  printf("        CL_DEVICE_PROFILE = %s\n", value);
break;

case CL_DEVICE_PROFILING_TIMER_RESOLUTION:
  printf("        CL_DEVICE_PROFILING_TIMER_RESOLUTION = %s\n", value);
break;

case CL_DEVICE_QUEUE_PROPERTIES:
  printf("        CL_DEVICE_QUEUE_PROPERTIES = %s\n", value);
break;

case CL_DEVICE_SINGLE_FP_CONFIG:
  printf("        CL_DEVICE_SINGLE_FP_CONFIG = %s\n", value);
break;

case CL_DEVICE_TYPE:
  printf("        CL_DEVICE_TYPE = %s\n", value);
break;

case CL_DEVICE_VENDOR_ID:
  printf("        CL_DEVICE_VENDOR_ID = %s\n", value);
break;

case CL_DEVICE_VENDOR:
  printf("        CL_DEVICE_VENDOR = %s\n", value);
break;

case CL_DEVICE_VERSION:
  printf("        CL_DEVICE_VERSION = %s\n", value);
break;

case CL_DRIVER_VERSION:
  printf("        CL_DRIVER_VERSION = %s\n", value);
}
*/