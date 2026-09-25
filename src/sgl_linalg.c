#include <sgl.h>

#include <math.h>

SGLvec2 sglVec2(double x, double y)
{
  SGLvec2 vec;
  vec.x = x;
  vec.y = y;
  return vec;
}

SGLvec3 sglVec3(double x, double y, double z)
{
  SGLvec3 vec;
  vec.x = x;
  vec.y = y;
  vec.z = z;
  return vec;
}

SGLvec4 sglVec4(double x, double y, double z, double w)
{
  SGLvec4 vec;
  vec.x = x;
  vec.y = y;
  vec.z = z;
  vec.w = w;
  return vec;
}

SGLvec2 sglAddVec2(SGLvec2 a, SGLvec2 b)
{
  return sglVec2(a.x + b.x, a.y + b.y);
}

SGLvec3 sglAddVec3(SGLvec3 a, SGLvec3 b)
{
  return sglVec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

SGLvec4 sglAddVec4(SGLvec4 a, SGLvec4 b)
{
  return sglVec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

SGLvec2 sglSubVec2(SGLvec2 a, SGLvec2 b)
{
  return sglVec2(a.x - b.x, a.y - b.y);
}

SGLvec3 sglSubVec3(SGLvec3 a, SGLvec3 b)
{
  return sglVec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

SGLvec4 sglSubVec4(SGLvec4 a, SGLvec4 b)
{
  return sglVec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

SGLvec2 sglMulVec2(SGLvec2 a, SGLvec2 b)
{
  return sglVec2(a.x * b.x, a.y * b.y);
}

SGLvec3 sglMulVec3(SGLvec3 a, SGLvec3 b)
{
  return sglVec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

SGLvec4 sglMulVec4(SGLvec4 a, SGLvec4 b)
{
  return sglVec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

SGLvec2 sglDivVec2(SGLvec2 a, SGLvec2 b)
{
  return sglVec2(a.x / b.x, a.y / b.y);
}

SGLvec3 sglDivVec3(SGLvec3 a, SGLvec3 b)
{
  return sglVec3(a.x / b.x, a.y / b.y, a.z / b.z);
}

SGLvec4 sglDivVec4(SGLvec4 a, SGLvec4 b)
{
  return sglVec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

double sglDotVec2(SGLvec2 a, SGLvec2 b)
{
  return a.x * b.x + a.y * b.y;
}

double sglDotVec3(SGLvec3 a, SGLvec3 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

double sglDotVec4(SGLvec4 a, SGLvec4 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

SGLvec2 sglScaleVec2(SGLvec2 vec, double scale)
{
  vec.x *= scale;
  vec.y *= scale;
  return vec;
}

SGLvec3 sglScaleVec3(SGLvec3 vec, double scale)
{
  vec.x *= scale;
  vec.y *= scale;
  vec.z *= scale;
  return vec;
}

SGLvec4 sglScaleVec4(SGLvec4 vec, double scale)
{
  vec.x *= scale;
  vec.y *= scale;
  vec.z *= scale;
  vec.w *= scale;
  return vec;
}

void sglInitIdentityMatrix(SGLmatrix *matrix)
{
  matrix->M[0][0] = 1;
  matrix->M[0][1] = 0;
  matrix->M[0][2] = 0;
  matrix->M[0][3] = 0;
  matrix->M[1][0] = 0;
  matrix->M[1][1] = 1;
  matrix->M[1][2] = 0;
  matrix->M[1][3] = 0;
  matrix->M[2][0] = 0;
  matrix->M[2][1] = 0;
  matrix->M[2][2] = 1;
  matrix->M[2][3] = 0;
  matrix->M[3][0] = 0;
  matrix->M[3][1] = 0;
  matrix->M[3][2] = 0;
  matrix->M[3][3] = 1;
}

void sglInitPerspectiveMatrix(
    double fov, double aspect, double clip, SGLmatrix *matrix)
{
  double f = 1 / tan(fov / 2);
  matrix->M[0][0] = f / aspect;
  matrix->M[0][1] = 0;
  matrix->M[0][2] = 0;
  matrix->M[0][3] = 0;
  matrix->M[1][0] = 0;
  matrix->M[1][1] = f;
  matrix->M[1][2] = 0;
  matrix->M[1][3] = 0;
  matrix->M[2][0] = 0;
  matrix->M[2][1] = 0;
  matrix->M[2][2] = -1;
  matrix->M[2][3] = -2 * clip;
  matrix->M[3][0] = 0;
  matrix->M[3][1] = 0;
  matrix->M[3][2] = -1;
  matrix->M[3][3] = 0;
}

void sglInitTranslationMatrix(double x, double y, double z, SGLmatrix *matrix)
{
  matrix->M[0][0] = 1;
  matrix->M[0][1] = 0;
  matrix->M[0][2] = 0;
  matrix->M[0][3] = 0;
  matrix->M[1][0] = 0;
  matrix->M[1][1] = 1;
  matrix->M[1][2] = 0;
  matrix->M[1][3] = 0;
  matrix->M[2][0] = 0;
  matrix->M[2][1] = 0;
  matrix->M[2][2] = 1;
  matrix->M[2][3] = 0;
  matrix->M[3][0] = x;
  matrix->M[3][1] = y;
  matrix->M[3][2] = z;
  matrix->M[3][3] = 1;
}

void sglInitRotationMatrix(
    double x, double y, double z, double angle, SGLmatrix *matrix)
{
  double s = sin(angle);
  double c = cos(angle);
  double o = 1 - c;
  matrix->M[0][0] = x * x * o + c;
  matrix->M[0][1] = x * y * o - z * s;
  matrix->M[0][2] = x * z * o + y * s;
  matrix->M[0][3] = 0;
  matrix->M[1][0] = y * x * o + z * s;
  matrix->M[1][1] = y * y * o + c;
  matrix->M[1][2] = y * z * o - x * s;
  matrix->M[1][3] = 0;
  matrix->M[2][0] = z * x * o - y * s;
  matrix->M[2][1] = z * y * o + x * s;
  matrix->M[2][2] = z * z * o + c;
  matrix->M[2][3] = 0;
  matrix->M[3][0] = 0;
  matrix->M[3][1] = 0;
  matrix->M[3][2] = 0;
  matrix->M[3][3] = 1;
}

void sglInitScaleMatrix(double x, double y, double z, SGLmatrix *matrix)
{
  matrix->M[0][0] = x;
  matrix->M[0][1] = 0;
  matrix->M[0][2] = 0;
  matrix->M[0][3] = 0;
  matrix->M[1][0] = 0;
  matrix->M[1][1] = y;
  matrix->M[1][2] = 0;
  matrix->M[1][3] = 0;
  matrix->M[2][0] = 0;
  matrix->M[2][1] = 0;
  matrix->M[2][2] = z;
  matrix->M[2][3] = 0;
  matrix->M[3][0] = 0;
  matrix->M[3][1] = 0;
  matrix->M[3][2] = 0;
  matrix->M[3][3] = 1;
}

void sglApplyMatrix(const SGLmatrix *applied, SGLmatrix *matrix)
{
  SGLmatrix result = { 0 };
  int i, j, k;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      for (k = 0; k < 4; ++k)
      {
        result.M[i][j] += applied->M[i][k] * matrix->M[k][j];
      }
    }
  }
  *matrix = result;
}

void sglTranslateMatrix(double x, double y, double z, SGLmatrix *matrix)
{
  matrix->M[0][0] += matrix->M[3][0] * x;
  matrix->M[0][1] += matrix->M[3][1] * x;
  matrix->M[0][2] += matrix->M[3][2] * x;
  matrix->M[0][3] += matrix->M[3][3] * x;
  matrix->M[1][0] += matrix->M[3][0] * y;
  matrix->M[1][1] += matrix->M[3][1] * y;
  matrix->M[1][2] += matrix->M[3][2] * y;
  matrix->M[1][3] += matrix->M[3][3] * y;
  matrix->M[2][0] += matrix->M[3][0] * z;
  matrix->M[2][1] += matrix->M[3][1] * z;
  matrix->M[2][2] += matrix->M[3][2] * z;
  matrix->M[2][3] += matrix->M[3][3] * z;
}

void sglRotateMatrix(
    double x, double y, double z, double angle, SGLmatrix *matrix)
{
  SGLmatrix rotation;
  sglInitRotationMatrix(x, y, z, angle, &rotation);
  sglApplyMatrix(&rotation, matrix);
}

void sglScaleMatrix(double x, double y, double z, SGLmatrix *matrix)
{
  matrix->M[0][0] *= x;
  matrix->M[0][1] *= x;
  matrix->M[0][2] *= x;
  matrix->M[0][3] *= x;
  matrix->M[1][0] *= y;
  matrix->M[1][1] *= y;
  matrix->M[1][2] *= y;
  matrix->M[1][3] *= y;
  matrix->M[2][0] *= z;
  matrix->M[2][1] *= z;
  matrix->M[2][2] *= z;
  matrix->M[2][3] *= z;
}

