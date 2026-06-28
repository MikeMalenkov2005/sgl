#ifndef SGL_TEXTURE_H
#define SGL_TEXTURE_H

#include "sgl_types.h"

typedef struct _SGLtexture
{
  uint  _id;
  int   width;
  int   height;
  int   channels;
} SGLtexture;

SGLtexture sglCreateTexture(
    int width, int height, int channels, const uchar* pixels);

void sglDeleteTexture(SGLtexture *texture);

SGLtexture sglLoadTexture(const char *path);

void sglBindTexture(uint index, const SGLtexture *texture);

void sglSetTextureFilter(const SGLtexture *texture, bool filter);

#endif

