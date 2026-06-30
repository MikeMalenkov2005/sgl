#ifndef SGL_GUI_H
#define SGL_GUI_H

#include "sgl_types.h"

typedef struct _SGLrect
{
  double x;
  double y;
  double width;
  double height;
} SGLrect;

typedef struct _SGLsprite
{
  ushrt x_offset;
  ushrt y_offset;
  ushrt width;
  ushrt height;
  int   color;
} SGLsprite;

typedef struct _SGLfont
{
  uint  texture_index;
  uint  texture_width;
  uint  texture_height;
  ushrt glyph_width;
  ushrt glyph_height;
  uint  (*get_glyph)(int codepoint);
} SGLfont;

bool sglIsPointInRect(const SGLrect *rect, double x, double y);

void (*sglGetGUI(void))(void);
void sglSetGUI(void (*gui)(void));

uint sglScaleGUI(uint new_scale);

bool sglTextureGUI(uint index, uint width, uint height);

void sglGetWindowSizeForGUI(double *width, double *height);
void sglGetCursorForGUI(double *x, double *y);

bool sglIsHoveringGUI(const SGLrect *rect);
bool sglIsDraggingGUI(const SGLrect *rect);
bool sglIsPressingGUI(const SGLrect *rect, int button);

bool sglIsScrollingGUI(const SGLrect *rect, double *dx, double *dy);

void sglSpriteGUI(const SGLrect *rect, const SGLsprite *sprite);

int sglGetPressedButtonForGUI(const SGLrect *rect);

const SGLfont *sglGetFont(void);
bool sglSetFont(const SGLfont *font);

void sglGlyphGUI(const SGLrect *rect, int codepoint, int color);

void sglFlatTextGUI(double x, double y, const char *text, int color);

void sglGetTextRect(SGLrect *rect, double x, double y, const char *text);

#endif

