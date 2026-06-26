#include "sgl_utf8.h"

#include <Windows.h>

wchar_t *__sgl_decode_utf8(const char *string)
{
  unsigned length;
  wchar_t *result = NULL;
  if (string)
  {
    length = MultiByteToWideChar(CP_UTF8, 0, string, -1, NULL, 0);
    if (length && (result = sglAllocate(sizeof(*result) * length)))
    {
      (void)MultiByteToWideChar(CP_UTF8, 0, string, -1, result, length);
    }
  }
  return result;
}

