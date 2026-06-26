#ifndef SGL_ALLOC_H
#define SGL_ALLOC_H

#include "sgl_types.h"

typedef struct _SGLallocator
{
  void *(*allocate)(size_t size, void *user);
  void *(*reallocate)(void *block, size_t size, void *user);
  void  (*deallocate)(void *block, void *user);
  void *user;
} SGLallocator;

const SGLallocator *sglGetAllocator(void);
bool sglSetAllocator(const SGLallocator *allocator);

void *sglAllocate(size_t size);

void *sglReallocate(void *block, size_t size);

void sglDeallocate(void *block);

#endif

