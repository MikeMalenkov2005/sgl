#include <sgl.h>

#include <string.h>
#include <unistd.h>

const char *sglGetBasePath(void)
{
  static const char *path;
  static char buffer[1024];
  ssize_t length;
  char *slash;
  if (path) return path;
  length = readlink("/proc/self/exe", buffer, sizeof(buffer));
  if (length == -1 || (size_t)length >= sizeof(buffer)) return NULL;
  buffer[length] = 0;
  if (!(slash = strrchr(buffer, '/'))) return NULL;
  *slash = 0;
  return path = buffer;
}

