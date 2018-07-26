#ifndef opencl_hpp
#define opencl_hpp

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

  #include <stdio.h>
  #include <stdlib.h>

  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
    #include <OpenGL/OpenGL.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
    #include <GL/gl.h>
  #endif

  #define KERNEL_NAME             "thekernel"
  #define KERNEL_OPTIONS          ""

  extern  char*                   value;
  extern  cl_platform_id*         platforms;
  extern  unsigned int            num_platforms;
  extern  cl_device_id*           devices;
  extern  unsigned int            num_devices;
  extern  cl_context_properties*  properties;
  extern  cl_context              context;
  extern  cl_command_queue        queue;
  extern  cl_program              program;
  extern  cl_kernel               kernel;
  extern  char*                   kernel_source;
  extern  size_t                  size_kernel;
  extern  cl_program              kernel_program;
  extern  size_t                  size_global;
  extern  cl_uint                 dim_kernel;
  extern  cl_event                kernel_event;

  const char* get_error(cl_int error);
  cl_uint     get_platforms();
  void        get_platform_info(cl_uint index_platform, cl_platform_info name_param);
  cl_uint     get_devices(cl_uint index_platform);
  void        get_device_info(cl_uint index_device, cl_device_info name_param);
  void        load_kernel(const char* filename_kernel);
  void        init_opencl_kernel();
  void        get_kernel_workgroup_size(cl_kernel kernel, cl_device_id device_id, size_t* local);
  void        execute_kernel();
  void        push_point4(cl_mem* CL_memory_buffer, int kernel_arg);
  void        push_color4(cl_mem* CL_memory_buffer, int kernel_arg);
  void        enqueue_task();
  void        wait_for_event();
  void        pop_point4(cl_mem* CL_memory_buffer, int kernel_arg);
  void        pop_color4(cl_mem* CL_memory_buffer, int kernel_arg);
  void        finish_queue();
  void        release_event();
  void        release_mem_object(cl_mem CL_memory_buffer);
  void        release_kernel();
  void        release_queue();
  void        release_program();
  void        release_context();
  void        set_kernel();
  void        push_kernel();
  void        pop_kernel();

#endif