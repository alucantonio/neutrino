/// @file

#ifndef queue_hpp
#define queue_hpp

#include "neutrino.hpp"
#include "datatypes.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "QUEUE" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class queue
{
private:
  neutrino*        baseline;                                                                        // Neutrino baseline.

public:
  cl_command_queue queue_id;                                                                        // OpenCL queue.
  cl_context       context_id;                                                                      // OpenCL context.
  cl_device_id     device_id;                                                                       // OpenCL device id.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// CONSTRUCTOR ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  queue();
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////// INIT ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void init (
             neutrino* loc_baseline
            );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// READ "float1" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             float1* loc_data,                                                                      // float1 object.
             cl_uint loc_layout_index                                                               // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// READ "int1" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             int1*   loc_data,                                                                      // int1 object.
             cl_uint loc_layout_index                                                               // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// READ "float4" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             float4* loc_data,                                                                      // Data object.
             cl_uint loc_layout_index                                                               // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// READ "int4" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             int4*   loc_data,                                                                      // Data object.
             cl_uint loc_layout_index                                                               // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// READ "float1G" overload /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             float1G* loc_data,                                                                     // Data object.
             GLuint   loc_layout_index                                                              // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// READ "float4G" overload /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             float4G* loc_data,                                                                     // Data object.
             GLuint   loc_layout_index                                                              // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// WRITE "float1" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              float1* loc_data,                                                                     // float1 object.
              cl_uint loc_layout_index                                                              // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// WRITE "int1" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              int1*   loc_data,                                                                     // int1 object.
              cl_uint loc_layout_index                                                              // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// WRITE "float4" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              float4* loc_data,                                                                     // Data object.
              cl_uint loc_layout_index                                                              // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// WRITE "int4" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              int4*   loc_data,                                                                     // Data object.
              cl_uint loc_layout_index                                                              // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// WRITE "float1G" overload ////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              float1G* loc_data,                                                                    // Data object.
              GLuint   loc_layout_index                                                             // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// WRITE "float4G" overload ////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              float4G* loc_data,                                                                    // Data object.
              GLuint   loc_layout_index                                                             // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// ACQUIRE "float1G" overload ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void acquire (
                float1G* loc_data,                                                                  // Data object.
                GLuint   loc_layout_index                                                           // OpenGL shader layout index.
               );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// ACQUIRE "float4G" overload ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void acquire (
                float4G* loc_data,                                                                  // Data object.
                GLuint   loc_layout_index                                                           // OpenGL shader layout index.
               );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// RELEASE "float1G" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void release (
                float1G* loc_data,                                                                  // Data object.
                GLuint   loc_layout_index                                                           // OpenGL shader layout index.
               );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// RELEASE "float4G" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void release (
                float4G* loc_data,                                                                  // Data object.
                GLuint   loc_layout_index                                                           // OpenGL shader layout index.
               );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// DESTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~queue();
};

#endif
