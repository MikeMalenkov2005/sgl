#ifndef SGL_LINALG_H
#define SGL_LINALG_H

typedef struct _SGLvec2
{
  double x, y;
} SGLvec2;

typedef struct _SGLvec3
{
  double x, y, z;
} SGLvec3;

typedef struct _SGLvec4
{
  double x, y, z, w;
} SGLvec4;

SGLvec2 sglVec2(double x, double y);
SGLvec3 sglVec3(double x, double y, double z);
SGLvec4 sglVec4(double x, double y, double z, double w);

SGLvec2 sglAddVec2(SGLvec2 a, SGLvec2 b);
SGLvec3 sglAddVec3(SGLvec3 a, SGLvec3 b);
SGLvec4 sglAddVec4(SGLvec4 a, SGLvec4 b);

SGLvec2 sglSubVec2(SGLvec2 a, SGLvec2 b);
SGLvec3 sglSubVec3(SGLvec3 a, SGLvec3 b);
SGLvec4 sglSubVec4(SGLvec4 a, SGLvec4 b);

SGLvec2 sglMulVec2(SGLvec2 a, SGLvec2 b);
SGLvec3 sglMulVec3(SGLvec3 a, SGLvec3 b);
SGLvec4 sglMulVec4(SGLvec4 a, SGLvec4 b);

SGLvec2 sglDivVec2(SGLvec2 a, SGLvec2 b);
SGLvec3 sglDivVec3(SGLvec3 a, SGLvec3 b);
SGLvec4 sglDivVec4(SGLvec4 a, SGLvec4 b);

double sglDotVec2(SGLvec2 a, SGLvec2 b);
double sglDotVec3(SGLvec3 a, SGLvec3 b);
double sglDotVec4(SGLvec4 a, SGLvec4 b);

SGLvec2 sglScaleVec2(SGLvec2 vec, double scale);
SGLvec3 sglScaleVec3(SGLvec3 vec, double scale);
SGLvec4 sglScaleVec4(SGLvec4 vec, double scale);

typedef union _SGLmatrix
{
  float M[4][4];
  float data[16];
} SGLmatrix;

void sglInitIdentityMatrix(SGLmatrix *matrix);

void sglInitPerspectiveMatrix(
    double fov, double aspect, double clip, SGLmatrix *matrix);

void sglInitTranslationMatrix(double x, double y, double z, SGLmatrix *matrix);

void sglInitRotationMatrix(
    double x, double y, double z, double angle, SGLmatrix *matrix);

void sglInitScaleMatrix(double x, double y, double z, SGLmatrix *matrix);

void sglApplyMatrix(const SGLmatrix *applied, SGLmatrix *matrix);

void sglTranslateMatrix(double x, double y, double z, SGLmatrix *matrix);

void sglRotateMatrix(
    double x, double y, double z, double angle, SGLmatrix *matrix);

void sglScaleMatrix(double x, double y, double z, SGLmatrix *matrix);

#endif

