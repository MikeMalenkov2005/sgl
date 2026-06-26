#ifndef SGL_PATH_H
#define SGL_PATH_H

#include "sgl_types.h"

const char *sglGetBasePath(void);

char *sglJoinPath(char *buffer, size_t size, ...);

void *sglLoadFile(const char *path, size_t *size);

bool sglSaveFile(const char *path, const void *data, size_t size);

#endif

