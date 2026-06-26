#ifndef SGL_LINALG_H
#define SGL_LINALG_H

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

