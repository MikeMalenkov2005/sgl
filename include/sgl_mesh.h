#ifndef SGL_MESH_H
#define SGL_MESH_H

#include "sgl_types.h"

typedef struct _SGLmesh
{
  uint vao;
  uint vbo;
  uint count;
  uint stride;
} SGLmesh;

#define SGL_ATTRIB_TYPE_NULL            0
#define SGL_ATTRIB_TYPE_FLOAT           1
#define SGL_ATTRIB_TYPE_INT             2
#define SGL_ATTRIB_TYPE_SHORT           3
#define SGL_ATTRIB_TYPE_BYTE            4
#define SGL_ATTRIB_TYPE_UNSIGNED_INT    5
#define SGL_ATTRIB_TYPE_UNSIGNED_SHORT  6
#define SGL_ATTRIB_TYPE_UNSIGNED_BYTE   7

#define SGL_ATTRIB_MODE_FLOAT           0
#define SGL_ATTRIB_MODE_NORMALIZED      1
#define SGL_ATTRIB_MODE_INTEGER         2

#define sglGetAttribType(attrib) (((attrib) >> 0) & 7)
#define sglGetAttribSize(attrib) ((((attrib) >> 3) & 3) + 1)
#define sglGetAttribMode(attrib) (((attrib) >> 5) & 3)

#define sglIsAttribNormalized(attrib) \
  (!!((attrib) & (SGL_ATTRIB_MODE_NORMALIZED << 5)))
#define sglIsAttribInteger(attrib)    \
  (!!((attrib) & (SGL_ATTRIB_MODE_INTEGER << 5)))

#define sglAttrib(type, size, mode)   \
  (((type) << 0) | (((size) - 1) << 3) | ((mode) << 5))

SGLmesh sglCreateMesh(uint stride, ...);
void sglDeleteMesh(SGLmesh *mesh);

bool sglSetMeshData(SGLmesh *mesh, const void *data, size_t size);

void sglDrawMesh(const SGLmesh *mesh);

#endif

