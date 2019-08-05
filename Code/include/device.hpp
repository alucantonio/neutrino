/// @file

#ifndef device_hpp
#define device_hpp

  #include "neutrino.hpp"
  #include "datatypes.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "DEVICE" CLASS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class device
{
private:
  neutrino*    baseline;                                                        // Neutrino baseline.
  std::string  parameter_value;                                                 // Parameter value.
  // OpenCL get info value function:
  std::string get_info (
                        cl_device_id   loc_platform_id,                         // Platform ID.
                        cl_device_info loc_parameter_name                       // Paramenter name.
                       );

public:
  cl_device_id id;                                                              // OpenCL device id.
  std::string  name;                                                            // Device name.
  std::string  profile;                                                         // Device profile.

  device        ();
  void init (
             cl_device_id loc_device_id                                         // Device ID.
            );

  ~device();
};

#endif
