#include <sgl.h>

#include <string.h>
#include <Windows.h>

const char *sglGetBasePath(void)
{
  static const char *path;
  static char buffer[1024];
  static WCHAR wbuffer[MAX_PATH];
  DWORD length;
  char *slash;
  if (path) return path;
  length = GetModuleFileNameW(NULL, wbuffer, (DWORD)sizeof(wbuffer));
  if (!length || length > (DWORD)sizeof(wbuffer)) return NULL;
  (void)WideCharToMultiByte(
      CP_UTF8, 0, wbuffer, -1, buffer, sizeof(buffer), NULL, NULL);
  if (!(slash = strrchr(buffer, '\\'))) return NULL;
  *slash = 0;
  return path = buffer;
}

