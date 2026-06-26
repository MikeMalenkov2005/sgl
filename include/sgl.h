#ifndef SGL_H
#define SGL_H

#include <stdio.h>

#include "sgl_types.h"
#include "sgl_alloc.h"
#include "sgl_path.h"

#include "sgl_linalg.h"
#include "sgl_buttons.h"
#include "sgl_texture.h"
#include "sgl_shader.h"

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

void sglCloseWindow(void);

void sglSetWindowSizeLimits(
    int min_width, int min_height, int max_width, int max_height);

void sglGetWindowSize(int *width, int *height);
void sglSetWindowSize(int width, int height);

bool sglGetFullscreen(void);
void sglSetFullscreen(bool fullscreen);

bool sglGetVSync(void);
void sglSetVSync(bool vsync);

bool sglGetCursorEnabled(void);
void sglSetCursorEnabled(bool enabled);

void sglGetCursor(int *x, int *y);
void sglSetCursor(int x, int y);

bool sglGetButton(int button);

void sglSetRenderCallback(void (*callback)(void));
void sglSetUpdateCallback(void (*callback)(double delta));
void sglSetScrollCallback(void (*callback)(double dx, double dy));
void sglSetButtonCallback(void (*callback)(int button, int action, int mods));
void sglSetCursorCallback(
    void (*callback)(double x, double y, double dx, double dy));

#endif

