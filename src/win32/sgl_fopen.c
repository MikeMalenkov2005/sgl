#include "sgl_utf8.h"

FILE *__sgl_win32_fopen(const char *filename, const char *mode)
{
  FILE *file;
  wchar_t *wfilename = __sgl_decode_utf8(filename);
  wchar_t *wmode = __sgl_decode_utf8(mode);
  file = _wfopen(wfilename, wmode);
  if (wfilename) sglDeallocate(wfilename);
  if (wmode) sglDeallocate(wmode);
  return file;
}

