#include <sgl.h>

#include <stdarg.h>

#ifdef _WIN32
#define SLASH '\\'
#else
#define SLASH '/'
#endif

char *sglJoinPath(char *buffer, size_t size, ...)
{
  va_list ap;
  size_t offset = 0;
  const char *part;
  if (buffer && size)
  {
    va_start(ap, size);
    while (buffer && (part = va_arg(ap, char*)))
    {
      offset += (size_t)snprintf(
          buffer + offset, size - offset, "%s%c", part, SLASH);
      if (offset > size) buffer = NULL;
    }
    if (!offset) buffer = NULL;
    else if (buffer) buffer[--offset] = 0;
    va_end(ap);
  }
  return buffer;
}

void *sglLoadFile(const char *path, size_t *size)
{
  size_t length;
  char *data = NULL;
  FILE *file = fopen(path, "rb");
  if (file)
  {
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    if ((data = sglAllocate(length + 1)))
    {
      fread(data, 1, length, file);
      data[length] = 0;
      if (size) *size = length;
    }
    fclose(file);
  }
  return data;
}

bool sglSaveFile(const char *path, const void *data, size_t size)
{
  FILE *file;
  bool result = false;
  if (path && !(!data ^ !size) && (file = fopen(path, "wb")))
  {
    result = fwrite(data, 1, size, file) == size;
    fclose(file);
  }
  return result;
}



