#include <sgl.h>

#include <stdlib.h>
#include <string.h>

static SGLallocator _allocator;
static size_t _blocks;
static bool _valid;

const SGLallocator *sglGetAllocator(void)
{
  return _valid ? &_allocator : NULL;
}

bool sglSetAllocator(const SGLallocator *allocator)
{
  if (_blocks) return false;
  if (allocator)
  {
    if (!allocator->allocate ||
        !allocator->reallocate ||
        !allocator->deallocate) return false;
    _allocator = *allocator;
  }
  else memset(&_allocator, 0, sizeof(_allocator));
  return true;
}

void *sglAllocate(size_t size)
{
  ++_blocks;
  if (!_allocator.allocate) return malloc(size);
  return _allocator.allocate(size, _allocator.user);
}

void *sglReallocate(void *block, size_t size)
{
  if (!_allocator.reallocate) return realloc(block, size);
  return _allocator.reallocate(block, size, _allocator.user);
}

void sglDeallocate(void *block)
{
  --_blocks;
  if (!_allocator.deallocate) free(block);
  else _allocator.deallocate(block, _allocator.user);
}

