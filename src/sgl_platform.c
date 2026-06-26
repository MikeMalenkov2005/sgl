
#if defined(_WIN32)
#include "win32/sgl_utf8.c"
#include "win32/sgl_path.c"
#include "win32/sgl_fopen.c"
#elif defined(__APPLE__)
#include "apple/sgl_path.c"
#elif defined(__linux__)
#include "linux/sgl_path.c"
#else
#error "The target platform is not supported!"
#endif

