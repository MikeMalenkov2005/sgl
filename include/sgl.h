#ifndef SGL_H
#define SGL_H

#include <stdio.h>

#include "sgl_types.h"
#include "sgl_alloc.h"
#include "sgl_path.h"

#include "sgl_texture.h"

#include "sgl_gui.h"

#define ERR "\x1b[91mERROR: \x1b[0m"
#define WRN "\x1b[93mWARNING: \x1b[0m"
#define DBG "\x1b[96mDEBUG: \x1b[0m"
#define INF "\x1b[97mINFO: \x1b[0m"

#ifdef _WIN32
FILE *__sgl_win32_fopen(const char *filename, const char *mode);
#define fopen __sgl_win32_fopen
#endif

/* SGL window functions */

bool sglInitWindow(int width, int height, const char *title);
void sglLoopWindow(void);

bool sglGetFullscreen(void);
void sglSetFullscreen(bool fullscreen);

bool sglGetVSync(void);
void sglSetVSync(bool vsync);

bool sglGetCursorEnabled(void);
void sglSetCursorEnabled(bool enabled);

#endif

