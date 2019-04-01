#include "data.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "FLOAT1" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
data::data()
{

}

/// # OpenCL error get function
/// ### Description:
/// Translates an OpenCL numeric error code into a human-readable string.
const char* data::get_error (
                             cl_int loc_error                                   // Local error code.
                            )
{
  switch(loc_error)
  {
    // Run-time and JIT compiler errors:
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

    // Compile-time errors:
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

    // Extension errors:
    case  -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case  -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case  -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case  -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case  -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case  -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";

    default:     return "Unknown OpenCL error";
  }
}

/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it so stdout.
void data::check_error (
                        cl_int loc_error                                        // Error code.
                       )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    baseline -> error (get_error (loc_error));                                  // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

/// # Initialization function
/// ### Description:
/// Prepares a contiguous (unfolded) array to be used as data buffer
/// allocated on the client memory space.
void data::init (
                 neutrino* loc_baseline,                                        // Neutrino baseline.
                 data_type loc_variant,                                         // Data type.
                 size_t    loc_data_size                                        // Data number.
                )

{
  cl_int loc_error;                                                             // Error code.
  size_t i;                                                                     // Index.

  baseline       = loc_baseline;                                                // Getting Neutrino baseline...
  position       = new size_t[baseline -> k_num];                               // Initializing kernel argument position array...
  variant        = loc _variant;                                                // Data type.
  size           = loc_data_size;                                               // Data array size.
  buffer         = NULL;                                                        // OpenCL data buffer.
  opencl_context = baseline -> context_id;                                      // Getting OpenCL context...

  switch(variant)
  {
    case      INT:
      baseline -> action ("initializing \"int\" object...");                    // Printing message...

      data   = new cl_long[1*size];                                             // Creating array for unfolded data...

      for(i = 0; i < size; i++)                                                 // Filling unfolded data array...
      {
        data[1*i + 0] = 0.0f;                                                   // Filling data...
      }

      // Creating OpenCL memory buffer:
      buffer = clCreateBuffer (
                               opencl_context,                                  // OpenCL context.
                               CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,        // Memory flags.
                               1*sizeof(cl_long)*size,                          // Data buffer size.
                               data,                                            // Data buffer.
                               &loc_error                                       // Error code.
                              );

      check_error (loc_error);                                                  // Checking returned error code...

      break;

    case      INT4:
      baseline -> action ("initializing \"int4\" object...");                   // Printing message...

      data   = new cl_long[4*size];                                             // Creating array for unfolded data...

      for(i = 0; i < size; i++)                                                 // Filling unfolded data array...
      {
        data[4*i + 0] = 0.0f;                                                   // Filling "x" data...
        data[4*i + 1] = 0.0f;                                                   // Filling "y" data...
        data[4*i + 2] = 0.0f;                                                   // Filling "z" data...
        data[4*i + 3] = 1.0f;                                                   // Filling "w" data...
      }

      // Creating OpenCL memory buffer:
      buffer = clCreateBuffer (
                               opencl_context,                                  // OpenCL context.
                               CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,        // Memory flags.
                               4*sizeof(cl_long)*size,                          // Data buffer size.
                               data,                                            // Data buffer.
                               &loc_error                                       // Error code.
                              );

      check_error (loc_error);                                                  // Checking returned error code...

      break;

    case      FLOAT:
      baseline -> action ("initializing \"float\" object...");                  // Printing message...

      data   = new cl_float[1*size];                                            // Creating array for unfolded data...

      for(i = 0; i < size; i++)                                                 // Filling unfolded data array...
      {
        data[1*i + 0] = 0.0f;                                                   // Filling "x"...
      }

      // Creating OpenCL memory buffer:
      buffer = clCreateBuffer (
                               opencl_context,                                  // OpenCL context.
                               CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,        // Memory flags.
                               1*sizeof(cl_float)*size,                         // Data buffer size.
                               data,                                            // Data buffer.
                               &loc_error                                       // Error code.
                              );

      check_error (loc_error);                                                  // Checking returned error code...

      break;

    case      FLOAT4:
      baseline -> action ("initializing \"float4\" object...");                 // Printing message...

      data   = new cl_float[4*size];                                            // Creating array for unfolded data...

      for(i = 0; i < size; i++)                                                 // Filling unfolded data array...
      {
        data[4*i + 0] = 0.0f;                                                   // Filling "x" data...
        data[4*i + 1] = 0.0f;                                                   // Filling "y" data...
        data[4*i + 2] = 0.0f;                                                   // Filling "z" data...
        data[4*i + 3] = 1.0f;                                                   // Filling "w" data...
      }

      // Creating OpenCL memory buffer:
      buffer = clCreateBuffer (
                               opencl_context,                                  // OpenCL context.
                               CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,        // Memory flags.
                               4*sizeof(cl_float)*size,                         // Data buffer size.
                               data,                                            // Data buffer.
                               &loc_error                                       // Error code.
                              );

      check_error (loc_error);                                                  // Checking returned error code...

      break;

    case      MESH:
      baseline -> action ("initializing \"mesh\" object...");                   // Printing message...

      if(baseline -> use_cl_gl_interop)
      {
        vbo  = 0;                                                               // OpenGL data VBO.
        data = new GLfloat[4*size];                                             // Creating array for unfolded data...

        for(i = 0; i < size; i++)                                               // Filling unfolded data array...
        {
          data[4*i + 0] = 0.0f;                                                 // Filling "x"...
          data[4*i + 1] = 0.0f;                                                 // Filling "y"...
          data[4*i + 2] = 0.0f;                                                 // Filling "z"...
          data[4*i + 3] = 1.0f;                                                 // Filling "w"...
        }

        glGenVertexArrays (1, &vao);                                            // Generating glyph VAO...
        glBindVertexArray (vao);                                                // Binding glyph VAO...

        // Generating VBO:
        glGenBuffers (
                      1,                                                        // # of VBOs to generate.
                      &vbo                                                      // VBOs array.
                     );

        // Binding VBO:
        glBindBuffer (
                      GL_ARRAY_BUFFER,                                          // VBO target.
                      vbo                                                       // VBO to bind.
                     );

        // Creating and initializing a buffer object's data store:
        glBufferData (
                      GL_ARRAY_BUFFER,                                          // VBO target.
                      (GLsizeiptr)(4*sizeof(GLfloat)*(size)),                   // VBO size.
                      data,                                                     // VBO data.
                      GL_DYNAMIC_DRAW                                           // VBO usage.
                     );

        // Enabling "layout = 0" attribute in vertex shader:
        glEnableVertexAttribArray (
                                   LAYOUT_0                                     // VAO index.
                                  );

        // Binding VBO:
        glBindBuffer (
                      GL_ARRAY_BUFFER,                                          // VBO target.
                      vbo                                                       // VBO to bind.
                     );

        // Specifying the format for "layout = 0" attribute in vertex shader:
        glVertexAttribPointer (
                               LAYOUT_0,                                        // VAO index.
                               4,                                               // VAO's # of components.
                               GL_FLOAT,                                        // Data type.
                               GL_FALSE,                                        // Not using normalized numbers.
                               0,                                               // Data stride.
                               0                                                // Data offset.
                              );

        // Creating OpenCL buffer from OpenGL buffer:
        buffer = clCreateFromGLBuffer (
                                       opencl_context,                          // OpenCL context.
                                       CL_MEM_READ_WRITE,                       // Memory flags.
                                       vbo,                                     // VBO.
                                       &loc_error                               // Returned error.
                                      );

      }
      else                                                                      // Replicate float4 init.
      {
        data   = new cl_float[4*size];                                          // Creating array for unfolded data...

        for(i = 0; i < size; i++)                                               // Filling unfolded data array...
        {
          data[4*i + 0] = 0.0f;                                                 // Filling "x"...
          data[4*i + 1] = 0.0f;                                                 // Filling "y"...
          data[4*i + 2] = 0.0f;                                                 // Filling "z"...
          data[4*i + 3] = 1.0f;                                                 // Filling "w"...
        }

        // Creating OpenCL memory buffer:
        buffer = clCreateBuffer (
                                 opencl_context,                                // OpenCL context.
                                 CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,      // Memory flags.
                                 4*sizeof(cl_float)*size,                       // Data buffer size.
                                 data,                                          // Data buffer.
                                 &loc_error                                     // Error code.
                                );

      }

      check_error (loc_error);                                                  // Checking returned error code...

      break;

    case      COLOR:
      baseline -> action ("initializing \"color\" object...");                  // Printing message...

      if(baseline -> use_cl_gl_interop)
      {
        vbo  = 0;                                                               // OpenGL data VBO.
        data = new GLfloat[4*size];                                             // Creating array for unfolded data...

        for(i = 0; i < size; i++)                                               // Filling unfolded data array...
        {
          data[4*i + 0] = 0.0f;                                                 // Filling "r"...
          data[4*i + 1] = 0.0f;                                                 // Filling "g"...
          data[4*i + 2] = 0.0f;                                                 // Filling "b"...
          data[4*i + 3] = 1.0f;                                                 // Filling "a"...
        }

        glGenVertexArrays (1, &vao);                                            // Generating glyph VAO...
        glBindVertexArray (vao);                                                // Binding glyph VAO...

        // Generating VBO:
        glGenBuffers (
                      1,                                                        // # of VBOs to generate.
                      &vbo                                                      // VBOs array.
                     );

        // Binding VBO:
        glBindBuffer (
                      GL_ARRAY_BUFFER,                                          // VBO target.
                      vbo                                                       // VBO to bind.
                     );

        // Creating and initializing a buffer object's data store:
        glBufferData (
                      GL_ARRAY_BUFFER,                                          // VBO target.
                      (GLsizeiptr)(4*sizeof(GLfloat)*(size)),                   // VBO size.
                      data,                                                     // VBO data.
                      GL_DYNAMIC_DRAW                                           // VBO usage.
                     );

        // Enabling "layout = 0" attribute in vertex shader:
        glEnableVertexAttribArray (
                                   LAYOUT_1                                     // VAO index.
                                  );

        // Binding VBO:
        glBindBuffer (
                      GL_ARRAY_BUFFER,                                          // VBO target.
                      vbo                                                       // VBO to bind.
                     );

        // Specifying the format for "layout = 0" attribute in vertex shader:
        glVertexAttribPointer (
                               LAYOUT_1,                                        // VAO index.
                               4,                                               // VAO's # of components.
                               GL_FLOAT,                                        // Data type.
                               GL_FALSE,                                        // Not using normalized numbers.
                               0,                                               // Data stride.
                               0                                                // Data offset.
                              );

        // Creating OpenCL buffer from OpenGL buffer:
        buffer = clCreateFromGLBuffer (
                                       opencl_context,                          // OpenCL context.
                                       CL_MEM_READ_WRITE,                       // Memory flags.
                                       vbo,                                     // VBO.
                                       &loc_error                               // Returned error.
                                      );

      }
      else
      {
        data   = new cl_float[4*size];                                          // Creating array for unfolded data...

        for(i = 0; i < size; i++)                                               // Filling unfolded data array...
        {
          data[4*i + 0] = 0.0f;                                                 // Filling "x"...
          data[4*i + 1] = 0.0f;                                                 // Filling "y"...
          data[4*i + 2] = 0.0f;                                                 // Filling "z"...
          data[4*i + 3] = 1.0f;                                                 // Filling "w"...
        }

        // Creating OpenCL memory buffer:
        buffer = clCreateBuffer (
                                 opencl_context,                                // OpenCL context.
                                 CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,      // Memory flags.
                                 4*sizeof(cl_float)*size,                       // Data buffer size.
                                 data,                                          // Data buffer.
                                 &loc_error                                     // Error code.
                                );
      }

      check_error (loc_error);                                                  // Checking returned error code...

      break;
  }

  baseline -> done ();                                                          // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// HOST "SET" FUNCTIONS:  ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Kernel set function
/// ### Description:
/// Sets a kernel argument at a specified index position.
void data::set_arg (
                    kernel* loc_kernel,                                         // OpenCL kernel.
                    cl_uint loc_kernel_arg                                      // OpenCL kernel argument #.
                   )
{
  cl_int loc_error;                                                             // Error code.
  size_t kernel_index;
  size_t i;

  baseline -> action ("setting \"float1\" kernel argument...");                 // Printing message...

  // Getting kernel index:
  for(i = 0; i < baseline -> k_num; i++)                                        // Scanning OpenCL kernel id array...
  {
    if(baseline -> kernel_id[i] == loc_kernel -> kernel_id)                     // Finding current kernel id...
    {
      kernel_index = i;                                                         // Setting kernel index...
    }
  }

  position[kernel_index] = loc_kernel_arg;                                      // Setting kernel argument position in current kernel...

  // Setting OpenCL buffer as kernel argument:
  loc_error              = clSetKernelArg (
                                           loc_kernel -> kernel_id,             // Kernel.
                                           loc_kernel_arg,                      // Kernel argument index.
                                           sizeof(cl_mem),                      // Kernel argument size.
                                           &buffer                              // Kernel argument value.
                                          );

  check_error (loc_error);                                                      // Checking returned error code...

  baseline -> done ();                                                          // Printing message...
}

/// # "data" set function
/// ### Description:
/// Sets value in data array.
void data::set_data (
                     size_t   loc_index,                                        // Data index.
                     cl_float loc_value                                         // Data value.
                    )
{
  switch(variant)
  {
    case      INT:
      data[1*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      INT4:
      data[4*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      data[4*loc_index + 1] = (cl_long)loc_value;                               // Setting data value...
      data[4*loc_index + 2] = (cl_long)loc_value;                               // Setting data value...
      data[4*loc_index + 3] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      FLOAT:
      data[1*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      FLOAT4:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 1] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 2] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 3] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      MESH:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 1] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 2] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 3] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      COLOR:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 1] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 2] = (cl_float)loc_value;                              // Setting data value...
      data[4*loc_index + 3] = (cl_float)loc_value;                              // Setting data value...
      break;
  }

}

/// # "x" set function
/// ### Description:
/// Sets "x" data value in data array.
void float4::set_x (
                    size_t   loc_index,                                         // Data index.
                    cl_float loc_value                                          // Data value.
                   )
{
  switch(variant)
  {
    case      INT:
      data[1*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      INT4:
      data[4*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      FLOAT:
      data[1*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      FLOAT4:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      MESH:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      COLOR:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;
  }
}

/// # "y" set function
/// ### Description:
/// Sets "y" data value in data array.
void float4::set_y (
                    size_t   loc_index,                                         // Data index.
                    cl_float loc_value                                          // Data value.
                   )
{
  switch(variant)
  {
    case      INT:
      data[1*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      INT4:
      data[4*loc_index + 1] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      FLOAT:
      data[1*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      FLOAT4:
      data[4*loc_index + 1] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      MESH:
      data[4*loc_index + 1] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      COLOR:
      data[4*loc_index + 1] = (cl_float)loc_value;                              // Setting data value...
      break;
  }
}

/// # "z" set function
/// ### Description:
/// Sets "z" data value in data array.
void float4::set_z (
                    size_t   loc_index,                                         // Data index.
                    cl_float loc_value                                          // Data value.
                   )
{
  switch(variant)
  {
    case      INT:
      data[1*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      INT4:
      data[4*loc_index + 2] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      FLOAT:
      data[1*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      FLOAT4:
      data[4*loc_index + 2] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      MESH:
      data[4*loc_index + 2] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      COLOR:
      data[4*loc_index + 2] = (cl_float)loc_value;                              // Setting data value...
      break;
  }
}

/// # "w" set function
/// ### Description:
/// Sets "w" data value in data array.
void float4::set_w (
                    size_t   loc_index,                                         // Data index.
                    cl_float loc_value                                          // Data value.
                   )
{
  switch(variant)
  {
    case      INT:
      data[1*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      INT4:
      data[4*loc_index + 3] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      FLOAT:
      data[1*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      FLOAT4:
      data[4*loc_index + 3] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      MESH:
      data[4*loc_index + 3] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      COLOR:
      data[4*loc_index + 3] = (cl_float)loc_value;                              // Setting data value...
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// HOST "GET" FUNCTIONS:  ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Kernel get function:
/// ### Description:
/// Gets the index position of a kernel argument.
size_t data::get_arg (
                      kernel* loc_kernel                                        // OpenCL kernel.
                     )
{
  cl_int loc_error;                                                             // Error code.
  size_t kernel_index;
  size_t i;

  // Getting kernel index:
  for(i = 0; i < baseline -> k_num; i++)                                        // Scanning OpenCL kernel id array...
  {
    if(baseline -> kernel_id[i] == loc_kernel -> kernel_id)                     // Finding current kernel id...
    {
      kernel_index = i;                                                         // Setting kernel index...
    }
  }

  return(position[kernel_index]);                                               // Returning index of current argument in current kernel...
}

/// # "data" get function
/// ### Description:
/// Gets "data" from data array.
cl_float data::get_data (
                         size_t loc_index                                       // Data index.
                        )
{
  switch(variant)
  {
    case      INT:
      data[1*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      INT4:
      data[4*loc_index + 0] = (cl_long)loc_value;                               // Setting data value...
      break;

    case      FLOAT:
      data[1*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      FLOAT4:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      MESH:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;

    case      COLOR:
      data[4*loc_index + 0] = (cl_float)loc_value;                              // Setting data value...
      break;
  }

  cl_float loc_value;                                                           // Value.

  loc_value = data[1*loc_index + 0];                                            // Getting data value...

  return(loc_value);                                                            // Returning data value...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CLIENT FUNCTIONS:  /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # OpenCL write buffer function
/// ### Description:
/// Enqueues commands to write to a buffer object from host memory.
void data::push (
                 queue*  loc_queue,                                             // Queue.
                 cl_uint loc_kernel_arg                                         // Kernel argument index.
                )
{
  cl_int loc_error;                                                             // Local error code.

  loc_error = clEnqueueWriteBuffer (
                                    loc_queue -> queue_id,                      // OpenCL queue ID.
                                    buffer,                                     // Data buffer.
                                    CL_TRUE,                                    // Blocking write flag.
                                    0,                                          // Data buffer offset.
                                    (size_t)(1*sizeof(cl_float)*size),          // Data buffer size.
                                    data,                                       // Data buffer.
                                    0,                                          // Number of events in the list.
                                    NULL,                                       // Event list.
                                    NULL                                        // Event.
                                   );

  check_error (loc_error);
}

/// # OpenCL read buffer function
/// ### Description:
/// Enqueues commands to read from a buffer object to host memory.
void data::pull (
                 queue*  loc_queue,                                             // Queue.
                 cl_uint loc_kernel_arg                                         // Kernel argument index.
                )
{
  cl_int loc_error;                                                             // Local error code.

  loc_error = clEnqueueReadBuffer (
                                   loc_queue -> queue_id,                       // OpenCL queue ID.
                                   buffer,                                      // Data buffer.
                                   CL_TRUE,                                     // Blocking write flag.
                                   0,                                           // Data buffer offset.
                                   (size_t)(1*sizeof(cl_float)*size),           // Data buffer size.
                                   data,                                        // Data buffer.
                                   0,                                           // Number of events in the list.
                                   NULL,                                        // Event list.
                                   NULL                                         // Event.
                                  );

  check_error (loc_error);
}

data::~data()
{
  cl_int loc_error;                                                             // Local error code.

  baseline -> action ("releasing \"float1\" object...");                        // Printing message...

  if(buffer != NULL)                                                            // Checking buffer..
  {
    loc_error = clReleaseMemObject (buffer);                                    // Releasing OpenCL buffer object...

    check_error (loc_error);                                                    // Checking returned error code...
  }

  delete[] data;                                                                // Releasing data buffer...
  delete[] position;                                                            // Deleting kernel argument position array...

  baseline -> done ();                                                          // Printing message...
}