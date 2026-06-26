#include <sgl.h>

#include <string.h>
#include <mach-o/dyld.h>

const char *sglGetBasePath(void)
{
  static const char *path;
  static char buffer[1024];
  uint32_t length = (uint32_t)sizeof(buffer);
  char *slash;
  if (path) return path;
  if (_NSGetExecutablePath(buffer, &length)) return NULL;
  if (!(slash = strrchr(buffer, '/'))) return NULL;
  *slash = 0;
  return path = buffer;
}


