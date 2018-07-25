#include "projective_geometry.hpp"

void frustum(float F[16], float left, float right, float bottom,
             float top, float z_near, float z_far)
{
  float a11 = 2.0*z_near/(right - left);
  float a13 = (right + left)/(right - left);
  float a22 = 2.0*z_near/(top - bottom);
  float a23 = (top + bottom)/(top - bottom);
  float a33 = -(z_far + z_near)/(z_far - z_near);
  float a34 = -2.0*(z_far*z_near)/(z_far - z_near);

  F[0]  = a11;   F[4]  = 0.0;  F[8]  = a13;   F[12] = 0.0;
  F[1]  = 0.0;   F[5]  = a22;  F[9]  = a23;   F[13] = 0.0;
  F[2]  = 0.0;   F[6]  = 0.0;  F[10] = a33;   F[14] = a34;
  F[3]  = 0.0;   F[7]  = 0.0;  F[11] = -1.0;  F[15] = 0.0;
}

void perspective(float P[16], float fov, float aspect_ratio,
                    float z_near, float z_far)
{
    float x_max;
    float y_max;

    y_max = z_near*tanf(fov/2.0);
    x_max = y_max*aspect_ratio;
    
    frustum(P, -x_max, x_max, -y_max, y_max, z_near, z_far);
}

void rotate(float R[16], float R_old[16], float axis[3], float theta)
{
  float q[4];                                                                   // Quaternion describing the rotation...
  float M[9];                                                                   // Matrix corresponding to rotation quaternion...
  float Q[16];                                                                  // Projective matrix corresponding to rotation quaternion...
  float cos_theta_half;                                                         // cos(theta/2).
  float sin_theta_half;                                                         // sin(theta/2).

  float q11, q12, q13, q14;
  float q21, q22, q23, q24;
  float q31, q32, q33, q34;
  float q41, q42, q43, q44;

  float r11, r12, r13, r14;
  float r21, r22, r23, r24;
  float r31, r32, r33, r34;
  float r41, r42, r43, r44;

  cos_theta_half = cos(theta/2.0);                                              // Computing cos(theta/2)...
  sin_theta_half = sin(theta/2.0);                                              // Computing sin(theta/2)...

  normalize(axis);                                                              // Normalizing rotation axis...

  q[0] = axis[0]*sin_theta_half;
  q[1] = axis[1]*sin_theta_half;
  q[2] = axis[2]*sin_theta_half;
  q[3] = cos_theta_half;

  rotation_matrix(M, q);

  Q[0]  = M[0]; Q[4]  = M[3]; Q[8]  = M[6]; Q[12] = 0.0;
  Q[1]  = M[1]; Q[5]  = M[4]; Q[9]  = M[7]; Q[13] = 0.0;
  Q[2]  = M[2]; Q[6]  = M[5]; Q[10] = M[8]; Q[14] = 0.0;
  Q[3]  = 0.0;  Q[7]  = 0.0;  Q[11] = 0.0;  Q[15] = 1.0;

  q11 = Q[0];  q12 = Q[4];  q13 = Q[8];  q14 = Q[12];
  q21 = Q[1];  q22 = Q[5];  q23 = Q[9];  q24 = Q[13];
  q31 = Q[2];  q32 = Q[6];  q33 = Q[10]; q34 = Q[14];
  q41 = Q[3];  q42 = Q[7];  q43 = Q[11]; q44 = Q[15];

  r11 = R_old[0];  r12 = R_old[4];  r13 = R_old[8];  r14 = R_old[12];
  r21 = R_old[1];  r22 = R_old[5];  r23 = R_old[9];  r24 = R_old[13];
  r31 = R_old[2];  r32 = R_old[6];  r33 = R_old[10]; r34 = R_old[14];
  r41 = R_old[3];  r42 = R_old[7];  r43 = R_old[11]; r44 = R_old[15];

  R[0]  = q11*r11 + q12*r21 + q13*r31 + q14*r41;
  R[1]  = q21*r11 + q22*r21 + q23*r31 + q24*r41;
  R[2]  = q31*r11 + q32*r21 + q33*r31 + q34*r41;
  R[3]  = q41*r11 + q42*r21 + q43*r31 + q44*r41;
  R[4]  = q11*r12 + q12*r22 + q13*r32 + q14*r42;
  R[5]  = q21*r12 + q22*r22 + q23*r32 + q24*r42;
  R[6]  = q31*r12 + q32*r22 + q33*r32 + q34*r42;
  R[7]  = q41*r12 + q42*r22 + q43*r32 + q44*r42;
  R[8]  = q11*r13 + q12*r23 + q13*r33 + q14*r43;
  R[9]  = q21*r13 + q22*r23 + q23*r33 + q24*r43;
  R[10] = q31*r13 + q32*r23 + q33*r33 + q34*r43;
  R[11] = q41*r13 + q42*r23 + q43*r33 + q44*r43;
  R[12] = q11*r14 + q12*r24 + q13*r34 + q14*r44;
  R[13] = q21*r14 + q22*r24 + q23*r34 + q24*r44;
  R[14] = q31*r14 + q32*r24 + q33*r34 + q34*r44;
  R[15] = q41*r14 + q42*r24 + q43*r34 + q44*r44;
}

void translate(float T[16], float translation[3])
{
  T[0] = 1.0; T[4] = 0.0; T[8]  = 0.0; T[12] = translation[0];
  T[1] = 0.0; T[5] = 1.0; T[9]  = 0.0; T[13] = translation[1];
  T[2] = 0.0; T[6] = 0.0; T[10] = 1.0; T[14] = translation[2];
  T[3] = 0.0; T[7] = 0.0; T[11] = 0.0; T[15] = 1.0;
}

void multiplicate(float C[16], float A[16], float B[16])
{
  float a11, a12, a13, a14;
  float a21, a22, a23, a24;
  float a31, a32, a33, a34;
  float a41, a42, a43, a44;

  float b11, b12, b13, b14;
  float b21, b22, b23, b24;
  float b31, b32, b33, b34;
  float b41, b42, b43, b44;

  a11 = A[0];  a12 = A[4];  a13 = A[8];  a14 = A[12];
  a21 = A[1];  a22 = A[5];  a23 = A[9];  a24 = A[13];
  a31 = A[2];  a32 = A[6];  a33 = A[10]; a34 = A[14];
  a41 = A[3];  a42 = A[7];  a43 = A[11]; a44 = A[15];

  b11 = B[0];  b12 = B[4];  b13 = B[8];  b14 = B[12];
  b21 = B[1];  b22 = B[5];  b23 = B[9];  b24 = B[13];
  b31 = B[2];  b32 = B[6];  b33 = B[10]; b34 = B[14];
  b41 = B[3];  b42 = B[7];  b43 = B[11]; b44 = B[15];

  C[0]  = a11*b11 + a12*b21 + a13*b31 + a14*b41;
  C[1]  = a21*b11 + a22*b21 + a23*b31 + a24*b41;
  C[2]  = a31*b11 + a32*b21 + a33*b31 + a34*b41;
  C[3]  = a41*b11 + a42*b21 + a43*b31 + a44*b41;
  C[4]  = a11*b12 + a12*b22 + a13*b32 + a14*b42;
  C[5]  = a21*b12 + a22*b22 + a23*b32 + a24*b42;
  C[6]  = a31*b12 + a32*b22 + a33*b32 + a34*b42;
  C[7]  = a41*b12 + a42*b22 + a43*b32 + a44*b42;
  C[8]  = a11*b13 + a12*b23 + a13*b33 + a14*b43;
  C[9]  = a21*b13 + a22*b23 + a23*b33 + a24*b43;
  C[10] = a31*b13 + a32*b23 + a33*b33 + a34*b43;
  C[11] = a41*b13 + a42*b23 + a43*b33 + a44*b43;
  C[12] = a11*b14 + a12*b24 + a13*b34 + a14*b44;
  C[13] = a21*b14 + a22*b24 + a23*b34 + a24*b44;
  C[14] = a31*b14 + a32*b24 + a33*b34 + a34*b44;
  C[15] = a41*b14 + a42*b24 + a43*b34 + a44*b44;
}
