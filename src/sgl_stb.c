#include <sgl.h>

#define STBI_MALLOC   sglAllocate
#define STBI_REALLOC  sglReallocate
#define STBI_FREE     sglDeallocate

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

