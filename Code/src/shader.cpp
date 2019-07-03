#include "shader.hpp"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// CONSTRUCTOR ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
shader::shader ()
{
  // Doing nothing.
}

/// # OpenGL shader init function
/// ### Description:
/// Initializes an OpenGL shader.
void shader::init (
                   neutrino*   loc_baseline,                                    // Neutrino baseline.
                   const char* loc_shader_home,                                 // Shader home directory.
                   const char* loc_vertex_file_name,                            // Vertex shader file name.
                   const char* loc_geometry_file_name,                          // Geometry shader file name.
                   const char* loc_fragment_file_name                           // Fragment shader file name.
                  )
{
  strncpy (shader_home, loc_shader_home, strlen (loc_shader_home));             // Getting shader home directory...

  // Building up vertex file full name:
  snprintf (
            vertex_file_name,                                                   // Destination string.
            MAX_PATH_SIZE,                                                      // Size of destination string.
            "%s/%s",                                                            // Compiled string.
            shader_home,                                                        // Shader home directory.
            loc_vertex_file_name                                                // Vertex shader file name.
           );

  // Building up geometry file full name:
  snprintf (
            geometry_file_name,                                                 // Destination string.
            MAX_PATH_SIZE,                                                      // Size of destination string.
            "%s/%s",                                                            // Compiled string.
            shader_home,                                                        // Shader home directory.
            loc_geometry_file_name                                              // Geometry shader file name.
           );

  // Building up fragment file full name:
  snprintf (
            fragment_file_name,                                                 // Destination string.
            MAX_PATH_SIZE,                                                      // Size of destination string.
            "%s/%s",                                                            // Compiled string.
            shader_home,                                                        // Shader home directory.
            loc_fragment_file_name                                              // Fragment shader file name.
           );

  vertex   = compile (vertex_file_name, VERTEX);                                // Compiling vertex shader...
  geometry = compile (geometry_file_name, GEOMETRY);                            // Compiling geometry shader...
  fragment = compile (fragment_file_name, FRAGMENT);                            // Compiling fragment shader...
  program  = glCreateProgram ();                                                // Creating program...
}

/// # OpenGL shader compile function
/// ### Description:
/// Compiles an OpenGL shader.
GLuint shader::compile (
                        const char* loc_shader_filename,                        // GLSL shader file name.
                        shader_type loc_shader_type                             // GLSL shader type.
                       )
{
  GLuint  shader;                                                               // Shader.
  char*   shader_source;                                                        // Shader source.
  size_t  shader_size;                                                          // Shader size [characters].
  GLint   success;                                                              // "GL_COMPILE_STATUS" flag.
  GLchar* log;                                                                  // Buffer for OpenGL error log.
  GLsizei log_size;                                                             // Size of OpenGL error log.
  char    shader_fullname [MAX_PATH_SIZE];                                      // Shader full file name.

  strncpy (
           shader_fullname,
           loc_shader_filename,
           strlen (loc_shader_filename)
          );                                                                    // Setting shader full file name...

  // Loading shader from file:
  baseline->load_file (
                       loc_shader_filename,                                     // Shader file.
                       &shader_source,                                          // Shader buffer.
                       &shader_size                                             // Shader buffer size.
                      );

  // Selecting shader type:
  switch(loc_shader_type)
  {
    case VERTEX:
      shader = glCreateShader (GL_VERTEX_SHADER);                               // Creating shader...
      break;

    case FRAGMENT:
      shader = glCreateShader (GL_FRAGMENT_SHADER);                             // Creating shader...
      break;

    case GEOMETRY:
      shader = glCreateShader (GL_GEOMETRY_SHADER);                             // Creating shader...
      break;
  }

  // Attaching source code to shader:
  glShaderSource (
                  shader,                                                       // GLSL shader.
                  1,                                                            // # of shaders.
                  (const char**)&shader_source,                                 // Shader source.
                  (GLint*)&shader_size                                          // Shader size.
                 );

  glCompileShader (shader);                                                     // Compiling shader...

  // Reading "GL_COMPILE_STATUS" flag:
  glGetShaderiv (
                 shader,                                                        // GLSL shader.
                 GL_COMPILE_STATUS,                                             // Requested shader parameter.
                 &success                                                       // Success status flag.
                );

  // Checking compiled shader code:
  if(!success)
  {
    glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &log_size);                      // Getting log length...
    log           = (char*) malloc (log_size + 1);                              // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog (shader, log_size + 1, NULL, log);                       // Getting log...
    printf ("%s\n", log);                                                       // Printing log...
    free (log);                                                                 // Freeing log...
    exit (1);                                                                   // Exiting...
  }

  baseline->free_file (shader_source);                                          // Freeing shader source file...

  return (shader);                                                              // Returning shader...
}

/// # OpenGL shader init function
/// ### Description:
/// Initializes an OpenGL shader.
void shader::build ()
{
  glAttachShader (program, vertex);                                             // Attaching vertex shader to program...
  glAttachShader (program, geometry);                                           // Attaching geometry shader to program...
  glAttachShader (program, fragment);                                           // Attaching fragment shader to program...
  glLinkProgram (program);                                                      // Linking program...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// SETARG "point" overload ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void shader::setarg (
                     point* loc_data,                                           // Data object.
                     GLuint loc_layout_index                                    // Data layout index.
                    )
{
  glBindAttribLocation (
                        program,                                                // OpenGL GLSL program.
                        loc_layout_index,                                       // Data layout index.
                        loc_data->name                                          // Data name.
                       );

  if(old_size == 0)
  {
    size     = loc_data->size;
    old_size = size;
  }

  else
  {
    size = loc_data->size;
    if(size != old_size)
    {
      baseline->error ("shader argument size mismatch!");
      exit (EXIT_FAILURE);
    }
  }

};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// SETARG "color" overload ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void shader::setarg (
                     color* loc_data,                                           // Data object.
                     GLuint loc_layout_index                                    // Data layout index.
                    )
{
  glBindAttribLocation (
                        program,                                                // OpenGL GLSL program.
                        loc_layout_index,                                       // Data layout index.
                        loc_data->name                                          // Data name.
                       );

  if(old_size == 0)
  {
    size     = loc_data->size;
    old_size = size;
  }

  else
  {
    size = loc_data->size;
    if(size != old_size)
    {
      baseline->error ("shader argument size mismatch!");
      exit (EXIT_FAILURE);
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// DESTRUCTOR /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
shader::~shader ()
{
  // Doing nothing.
}
