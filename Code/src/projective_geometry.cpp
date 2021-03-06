/// @file     projective_geometry.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of various projective geometry functions.

#include "projective_geometry.hpp"

void backup
(
 float M_mat[16],                                                                                   // New matrix: takes values from old matrix.
 float M_mat_old[16]                                                                                // Old matrix.
)
{
  M_mat[0]  = M_mat_old[0]; M_mat[4] = M_mat_old[4], M_mat[8] = M_mat_old[8];
  M_mat[12] = M_mat_old[12];                                                                        // Backing up matrix...
  M_mat[1]  = M_mat_old[1]; M_mat[5] = M_mat_old[5], M_mat[9] = M_mat_old[9];
  M_mat[13] = M_mat_old[13];                                                                        // Backing up matrix...
  M_mat[2]  = M_mat_old[2];
  M_mat[6]  = M_mat_old[6], M_mat[10] = M_mat_old[10];
  M_mat[14] = M_mat_old[14];                                                                        // Backing up matrix...
  M_mat[3]  = M_mat_old[3];
  M_mat[7]  = M_mat_old[7], M_mat[11] = M_mat_old[11];
  M_mat[15] = M_mat_old[15];                                                                        // Backing up matrix...
}

void multiplicate
(
 float C_mat[16],                                                                                   // 4x4 matrix result.
 float A_mat[16],                                                                                   // 4x4 matrix.
 float B_mat[16]                                                                                    // 4x4 matrix.
)
{
  float a11, a12, a13, a14;                                                                         // Matrix elements.
  float a21, a22, a23, a24;                                                                         // Matrix elements.
  float a31, a32, a33, a34;                                                                         // Matrix elements.
  float a41, a42, a43, a44;                                                                         // Matrix elements.

  float b11, b12, b13, b14;                                                                         // Matrix elements.
  float b21, b22, b23, b24;                                                                         // Matrix elements.
  float b31, b32, b33, b34;                                                                         // Matrix elements.
  float b41, b42, b43, b44;                                                                         // Matrix elements.

  a11       = A_mat[0];  a12 = A_mat[4];  a13 = A_mat[8];  a14 = A_mat[12];                         // Setting matrix elements...
  a21       = A_mat[1];  a22 = A_mat[5];  a23 = A_mat[9];  a24 = A_mat[13];                         // Setting matrix elements...
  a31       = A_mat[2];  a32 = A_mat[6];  a33 = A_mat[10]; a34 = A_mat[14];                         // Setting matrix elements...
  a41       = A_mat[3];  a42 = A_mat[7];  a43 = A_mat[11]; a44 = A_mat[15];                         // Setting matrix elements...

  b11       = B_mat[0];  b12 = B_mat[4];  b13 = B_mat[8];  b14 = B_mat[12];                         // Setting matrix elements...
  b21       = B_mat[1];  b22 = B_mat[5];  b23 = B_mat[9];  b24 = B_mat[13];                         // Setting matrix elements...
  b31       = B_mat[2];  b32 = B_mat[6];  b33 = B_mat[10]; b34 = B_mat[14];                         // Setting matrix elements...
  b41       = B_mat[3];  b42 = B_mat[7];  b43 = B_mat[11]; b44 = B_mat[15];                         // Setting matrix elements...

  C_mat[0]  = a11*b11 + a12*b21 + a13*b31 + a14*b41;                                                // Computing matrix multiplication...
  C_mat[1]  = a21*b11 + a22*b21 + a23*b31 + a24*b41;                                                // Computing matrix multiplication...
  C_mat[2]  = a31*b11 + a32*b21 + a33*b31 + a34*b41;                                                // Computing matrix multiplication...
  C_mat[3]  = a41*b11 + a42*b21 + a43*b31 + a44*b41;                                                // Computing matrix multiplication...
  C_mat[4]  = a11*b12 + a12*b22 + a13*b32 + a14*b42;                                                // Computing matrix multiplication...
  C_mat[5]  = a21*b12 + a22*b22 + a23*b32 + a24*b42;                                                // Computing matrix multiplication...
  C_mat[6]  = a31*b12 + a32*b22 + a33*b32 + a34*b42;                                                // Computing matrix multiplication...
  C_mat[7]  = a41*b12 + a42*b22 + a43*b32 + a44*b42;                                                // Computing matrix multiplication...
  C_mat[8]  = a11*b13 + a12*b23 + a13*b33 + a14*b43;                                                // Computing matrix multiplication...
  C_mat[9]  = a21*b13 + a22*b23 + a23*b33 + a24*b43;                                                // Computing matrix multiplication...
  C_mat[10] = a31*b13 + a32*b23 + a33*b33 + a34*b43;                                                // Computing matrix multiplication...
  C_mat[11] = a41*b13 + a42*b23 + a43*b33 + a44*b43;                                                // Computing matrix multiplication...
  C_mat[12] = a11*b14 + a12*b24 + a13*b34 + a14*b44;                                                // Computing matrix multiplication...
  C_mat[13] = a21*b14 + a22*b24 + a23*b34 + a24*b44;                                                // Computing matrix multiplication...
  C_mat[14] = a31*b14 + a32*b24 + a33*b34 + a34*b44;                                                // Computing matrix multiplication...
  C_mat[15] = a41*b14 + a42*b24 + a43*b34 + a44*b44;                                                // Computing matrix multiplication...
}

void translate
(
 float T_mat[16],                                                                                   // 4x4 translation matrix.
 float T_mat_old[16],                                                                               // 4x4 translation matrix backup.
 float t[3]                                                                                         // 3D translation vector.
)
{
  float M_mat[16];

  M_mat[0] = 1.0f; M_mat[4] = 0.0f; M_mat[8] = 0.0f; M_mat[12] = t[0];                              // Building translation...
  M_mat[1] = 0.0f; M_mat[5] = 1.0f; M_mat[9] = 0.0f; M_mat[13] = t[1];                              // Building translation...
  M_mat[2] = 0.0f; M_mat[6] = 0.0f; M_mat[10] = 1.0f; M_mat[14] = t[2];                             // Building translation...
  M_mat[3] = 0.0f; M_mat[7] = 0.0f; M_mat[11] = 0.0f; M_mat[15] = 1.0f;                             // Building translation...

  multiplicate (T_mat, T_mat_old, M_mat);                                                           // Rotating matrix...
}

void rotate
(
 float R[16],                                                                                       // 4x4 rotation matrix.
 float R_old[16],                                                                                   // 4x4 rotation matrix backup.
 float q[4]                                                                                         // Rotation quaternion.
)

{
  float M_mat[9];                                                                                   // Matrix corresponding to rotation quaternion...
  float Q[16];                                                                                      // Projective matrix corresponding to rotation quaternion...

  float q11, q12, q13, q14;                                                                         // Quaternion matrix form backup.
  float q21, q22, q23, q24;                                                                         // Quaternion matrix form backup.
  float q31, q32, q33, q34;                                                                         // Quaternion matrix form backup.
  float q41, q42, q43, q44;                                                                         // Quaternion matrix form backup.

  float r11, r12, r13, r14;                                                                         // Rotation matrix backup.
  float r21, r22, r23, r24;                                                                         // Rotation matrix backup.
  float r31, r32, r33, r34;                                                                         // Rotation matrix backup.
  float r41, r42, r43, r44;                                                                         // Rotation matrix backup.

  rotation_matrix (M_mat, q);                                                                       // Computing matrix representation from quaternion...

  Q[0]  = M_mat[0]; Q[4] = M_mat[3]; Q[8] = M_mat[6]; Q[12] = 0.0f;                                 // Computing quaternion in matrix form...
  Q[1]  = M_mat[1]; Q[5] = M_mat[4]; Q[9] = M_mat[7]; Q[13] = 0.0f;                                 // Computing quaternion in matrix form...
  Q[2]  = M_mat[2]; Q[6] = M_mat[5]; Q[10] = M_mat[8]; Q[14] = 0.0f;                                // Computing quaternion in matrix form...
  Q[3]  = 0.0;  Q[7] = 0.0;  Q[11] = 0.0;  Q[15] = 1.0;                                             // Computing quaternion in matrix form...

  q11   = Q[0];  q12 = Q[4];  q13 = Q[8];  q14 = Q[12];                                             // Backing up quaternion matrix form...
  q21   = Q[1];  q22 = Q[5];  q23 = Q[9];  q24 = Q[13];                                             // Backing up quaternion matrix form...
  q31   = Q[2];  q32 = Q[6];  q33 = Q[10]; q34 = Q[14];                                             // Backing up quaternion matrix form...
  q41   = Q[3];  q42 = Q[7];  q43 = Q[11]; q44 = Q[15];                                             // Backing up quaternion matrix form...

  r11   = R_old[0];  r12 = R_old[4];  r13 = R_old[8];  r14 = R_old[12];                             // Backing up rotation matrix...
  r21   = R_old[1];  r22 = R_old[5];  r23 = R_old[9];  r24 = R_old[13];                             // Backing up rotation matrix...
  r31   = R_old[2];  r32 = R_old[6];  r33 = R_old[10]; r34 = R_old[14];                             // Backing up rotation matrix...
  r41   = R_old[3];  r42 = R_old[7];  r43 = R_old[11]; r44 = R_old[15];                             // Backing up rotation matrix...

  R[0]  = q11*r11 + q12*r21 + q13*r31 + q14*r41;                                                    // Computing rotation matrix...
  R[1]  = q21*r11 + q22*r21 + q23*r31 + q24*r41;                                                    // Computing rotation matrix...
  R[2]  = q31*r11 + q32*r21 + q33*r31 + q34*r41;                                                    // Computing rotation matrix...
  R[3]  = q41*r11 + q42*r21 + q43*r31 + q44*r41;                                                    // Computing rotation matrix...
  R[4]  = q11*r12 + q12*r22 + q13*r32 + q14*r42;                                                    // Computing rotation matrix...
  R[5]  = q21*r12 + q22*r22 + q23*r32 + q24*r42;                                                    // Computing rotation matrix...
  R[6]  = q31*r12 + q32*r22 + q33*r32 + q34*r42;                                                    // Computing rotation matrix...
  R[7]  = q41*r12 + q42*r22 + q43*r32 + q44*r42;                                                    // Computing rotation matrix...
  R[8]  = q11*r13 + q12*r23 + q13*r33 + q14*r43;                                                    // Computing rotation matrix...
  R[9]  = q21*r13 + q22*r23 + q23*r33 + q24*r43;                                                    // Computing rotation matrix...
  R[10] = q31*r13 + q32*r23 + q33*r33 + q34*r43;                                                    // Computing rotation matrix...
  R[11] = q41*r13 + q42*r23 + q43*r33 + q44*r43;                                                    // Computing rotation matrix...
  R[12] = q11*r14 + q12*r24 + q13*r34 + q14*r44;                                                    // Computing rotation matrix...
  R[13] = q21*r14 + q22*r24 + q23*r34 + q24*r44;                                                    // Computing rotation matrix...
  R[14] = q31*r14 + q32*r24 + q33*r34 + q34*r44;                                                    // Computing rotation matrix...
  R[15] = q41*r14 + q42*r24 + q43*r34 + q44*r44;                                                    // Computing rotation matrix...
}

void frustum
(
 float F_mat[16],                                                                                   // 4x4 frustum matrix.
 float left,                                                                                        // Projective screen left side...
 float right,                                                                                       // Projective screen right side...
 float bottom,                                                                                      // Projective screen bottom side...
 float top,                                                                                         // Projective screen top side...
 float z_near,                                                                                      // Projective screen near depth...
 float z_far                                                                                        // Projective screen far depth...
)
{
  float a11 = +2.0f*          z_near/(right - left);                                                // Setting frustum matrix term...
  float a13 = +1.0f*  (right + left)/(right - left);                                                // Setting frustum matrix term...
  float a22 = +2.0f*          z_near/(top - bottom);                                                // Setting frustum matrix term...
  float a23 = +1.0f*  (top + bottom)/(top - bottom);                                                // Setting frustum matrix term...
  float a33 = -1.0f*(z_far + z_near)/(z_far - z_near);                                              // Setting frustum matrix term...
  float a34 = -2.0f*  (z_far*z_near)/(z_far - z_near);                                              // Setting frustum matrix term...

  F_mat[0] = a11;    F_mat[4] = 0.0f;  F_mat[8] = a13;      F_mat[12] = 0.0f;                       // Setting frustum matrix...
  F_mat[1] = 0.0f;   F_mat[5] = a22;   F_mat[9] = a23;      F_mat[13] = 0.0f;                       // Setting frustum matrix...
  F_mat[2] = 0.0f;   F_mat[6] = 0.0f;  F_mat[10] = a33;     F_mat[14] = a34;                        // Setting frustum matrix...
  F_mat[3] = 0.0f;   F_mat[7] = 0.0f;  F_mat[11] = -1.0f;   F_mat[15] = 0.0f;                       // Setting frustum matrix...
}

void perspective_mono
(
 float P_mat[16],                                                                                   // 4x4 perspective matrix.
 float fov,                                                                                         // Field of view [rad].
 float aspect_ratio,                                                                                // Projective screen aspect ratio.
 float z_near,                                                                                      // Projective screen near depth...
 float z_far                                                                                        // Projective screen far depth...
)
{
  float x_max;                                                                                      // Projective screen maximum "x" coordinate.
  float y_max;                                                                                      // Projective screen maximum "y" coordinate.

  y_max = z_near*tanf (fov/2.0f);                                                                   // Computing y_max...
  x_max = y_max*aspect_ratio;                                                                       // Computing x_max...

  // Computing perspective frustum:
  frustum (
           P_mat,                                                                                   // 4x4 perspective matrix.
           -x_max,                                                                                  // Projective screen left side...
           +x_max,                                                                                  // Projective screen right side...
           -y_max,                                                                                  // Projective screen bottom side...
           +y_max,                                                                                  // Projective screen top side...
           +z_near,                                                                                 // Projective screen near depth...
           +z_far                                                                                   // Projective screen far depth...
          );
}

void perspective_stereo
(
 float PL_mat[16],                                                                                  // 4x4 right eye perspective matrix.
 float PR_mat[16],                                                                                  // 4x4 left eye perspective matrix.
 float TL_mat[16],                                                                                  // 4x4 right eye translation matrix.
 float TR_mat[16],                                                                                  // 4x4 left eye translation matrix.
 float iod,                                                                                         // Intraocular distance.
 float fov,                                                                                         // Field of view [rad].
 float aspect_ratio,                                                                                // Projective screen aspect ratio.
 float z_near,                                                                                      // Projective screen near depth...
 float z_far                                                                                        // Projective screen far depth...
)
{
  float x_max;                                                                                      // Projective screen maximum "x" coordinate.
  float y_max;                                                                                      // Projective screen maximum "y" coordinate.
  float eye_shift;                                                                                  // Eye horizontal shift, due to stereoscopic vision.
  float frustum_shift;                                                                              // Frustum horizontal shift, due to stereoscopic vision.
  float left_shift[3];                                                                              // Left eye shift
  float right_shift[3];                                                                             // Right eye position.
  float M_mat[16];

  M_mat[0]       = 1.0f; M_mat[4] = 0.0f; M_mat[8] = 0.0f; M_mat[12] = 0.0f;                        // Building matrix for eye translation...
  M_mat[1]       = 0.0f; M_mat[5] = 1.0f; M_mat[9] = 0.0f; M_mat[13] = 0.0f;                        // Building matrix for eye translation...
  M_mat[2]       = 0.0f; M_mat[6] = 0.0f; M_mat[10] = 1.0f; M_mat[14] = 0.0f;                       // Building matrix for eye translation...
  M_mat[3]       = 0.0f; M_mat[7] = 0.0f; M_mat[11] = 0.0f; M_mat[15] = 1.0f;                       // Building matrix for eye translation...

  y_max          = z_near* tanf (fov/2.0f);                                                         // Computing y_max...
  x_max          = y_max*aspect_ratio;                                                              // Computing x_max...
  eye_shift      = iod/2.0f;                                                                        // Computing x_eye_shift...
  frustum_shift  = eye_shift*z_near/(NU_SCREEN_DISTANCE);                                           // Computing x_shift...

  left_shift[0]  = +eye_shift;                                                                      // Setting left eye x-coordinate...
  left_shift[1]  = 0.0f;                                                                            // Setting left eye y-coordinate...
  left_shift[2]  = 0.0f;                                                                            // Setting left eye z-coordinate...

  right_shift[0] = -eye_shift;                                                                      // Setting right eye x-coordinate...
  right_shift[1] = 0.0f;                                                                            // Setting right eye y-coordinate...
  right_shift[2] = 0.0f;                                                                            // Setting right eye z-coordinate...

  // Computing left eye perspective frustum:
  frustum
  (
   PL_mat,                                                                                          // 4x4 perspective matrix.
   -x_max - frustum_shift,                                                                          // Projective screen left side...
   +x_max - frustum_shift,                                                                          // Projective screen right side...
   -y_max,                                                                                          // Projective screen bottom side...
   +y_max,                                                                                          // Projective screen top side...
   +z_near,                                                                                         // Projective screen near depth...
   +z_far                                                                                           // Projective screen far depth...
  );

  // Computing right eye perspective frustum:
  frustum
  (
   PR_mat,                                                                                          // 4x4 perspective matrix.
   -x_max + frustum_shift,                                                                          // Projective screen left side...
   +x_max + frustum_shift,                                                                          // Projective screen right side...
   -y_max,                                                                                          // Projective screen bottom side...
   +y_max,                                                                                          // Projective screen top side...
   +z_near,                                                                                         // Projective screen near depth...
   +z_far                                                                                           // Projective screen far depth...
  );

  // Computing left eye translation matrix:
  translate
  (
   TL_mat,                                                                                          // 4x4 translation matrix.
   M_mat,                                                                                           // 4x4 initial matrix.
   left_shift                                                                                       // 3D translation vector.
  );

  // Computing right eye translation matrix:
  translate
  (
   TR_mat,                                                                                          // 4x4 translation matrix.
   M_mat,                                                                                           // 4x4 initial matrix.
   right_shift                                                                                      // 3D translation vector.
  );
}
