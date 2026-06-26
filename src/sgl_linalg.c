#include <sgl.h>

#include <math.h>
#include <string.h>

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

