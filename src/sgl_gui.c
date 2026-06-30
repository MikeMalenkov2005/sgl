#include <sgl.h>

#include "sgl_gui_internal.h"

#include <string.h>

static uint program;
static SGLmesh mesh;
static int u_window, u_texture, u_sampler;

static void (*GUI)(void);

static double X, Y, SX, SY, DX, DY;
static int flags, pressing, pressing_mods;
static uint current, scale = 1;

static SGLfont _font;

#define __F_RENDERING 0x01
#define __F_DRAGGING  0x02
#define __F_SCROLLING 0x04
#define __F_TEXTURED  0x08

#define __BUFLEN  (128 * 6)

static struct
{
  shrt  x;
  shrt  y;
  ushrt u;
  ushrt v;
  uchar r;
  uchar g;
  uchar b;
  uchar a;
} vertex_buffer[__BUFLEN];
static uint vertex_count;

static void __sglFlushGUI(void)
{
  if (vertex_count)
  {
    sglSetMeshData(&mesh, vertex_buffer, sizeof(*vertex_buffer) * vertex_count);
    sglDrawMesh(&mesh);
    vertex_count = 0;
  }
}

bool __sglInitGUI(void)
{
  static const char *vert_source =
    "#version 150 core\n"
    "\n"
    "in vec2 a_offset;\n"
    "in vec2 a_value;\n"
    "in vec4 a_color;\n"
    "\n"
    "out vec2 v_uv;\n"
    "out vec4 v_color;\n"
    "\n"
    "uniform vec2 u_window;\n"
    "uniform vec2 u_texture;\n"
    "\n"
    "const vec2 lut[6] =\n"
    "{\n"
    "  vec2(0.0, 0.0),\n"
    "  vec2(0.0, 1.0),\n"
    "  vec2(1.0, 1.0),\n"
    "  vec2(0.0, 0.0),\n"
    "  vec2(1.0, 1.0),\n"
    "  vec2(1.0, 0.0)\n"
    "};\n"
    "\n"
    "void main()\n"
    "{\n"
    "  vec2 offset = a_offset / u_window * 2.0 - 1.0;\n"
    "  v_uv = (lut[gl_VertexID % 6] + a_value) / u_texture;\n"
    "  v_color = a_color;\n"
    "  gl_Position = vec4(offset.x, -offset.y, 0.0, 1.0);\n"
    "}\n";
  static const char *frag_source =
    "#version 150 core\n"
    "\n"
    "in vec2 v_uv;\n"
    "in vec4 v_color;\n"
    "\n"
    "out vec4 o_color;\n"
    "\n"
    "uniform sampler2D u_sampler;\n"
    "\n"
    "void main()\n"
    "{\n"
    "  o_color = texture(u_sampler, v_uv) * v_color;\n"
    "}\n";
  uint vert = sglCreateShader(SGL_SHADER_VERT, vert_source);
  uint frag = sglCreateShader(SGL_SHADER_FRAG, frag_source);
  program = sglCreateProgram(vert, frag, 0);
  sglDeleteShader(vert);
  sglDeleteShader(frag);
  if (program)
  {
    sglSetAttributeIndex(program, "a_offset", 0);
    sglSetAttributeIndex(program, "a_value", 1);
    sglSetAttributeIndex(program, "a_color", 2);
    u_window = sglGetUniformIndex(program, "u_window");
    u_texture = sglGetUniformIndex(program, "u_texture");
    u_sampler = sglGetUniformIndex(program, "u_sampler");
    mesh = sglCreateMesh(12,
        sglAttrib(SGL_ATTRIB_TYPE_SHORT, 2, SGL_ATTRIB_MODE_FLOAT),
        sglAttrib(SGL_ATTRIB_TYPE_UNSIGNED_SHORT, 2, SGL_ATTRIB_MODE_FLOAT),
        sglAttrib(SGL_ATTRIB_TYPE_UNSIGNED_BYTE, 4, SGL_ATTRIB_MODE_NORMALIZED),
        0);
    if (!mesh.vao)
    {
      sglDeleteProgram(program);
      program = 0;
    }
  }
  return !!program;
}

void __sglFreeGUI(void)
{
  sglSetFont(NULL);
  sglDeleteMesh(&mesh);
  sglDeleteProgram(program);
  DX = DY = SX = SY = 0;
  current = program = 0;
  GUI = NULL;
}

void __sglRenderGUI(void)
{
  int w, h;
  uint old_program;
  if (!GUI) return;
  sglGetCursor(&X, &Y);
  sglGetWindowSize(&w, &h);
  X /= scale;
  Y /= scale;
  if (!sglGetButton(SGLB_MOUSE_LEFT))
  {
    flags &= ~__F_DRAGGING;
    DX = X;
    DY = Y;
  }
  else flags |= __F_DRAGGING;
  old_program = sglBindProgram(program);
  sglUniform2f(0, u_window, w, h);
  flags |= __F_RENDERING;
  GUI();
  __sglFlushGUI();
  sglBindProgram(old_program);
  flags &= ~(__F_RENDERING | __F_TEXTURED);
}

bool __sglPressGUI(int button, int mods)
{
  if (!GUI) return false;
  pressing = button;
  pressing_mods = mods;
  GUI();
  pressing_mods = 0;
  if (!pressing) return true;
  pressing = SGLB_NONE;
  return false;
}

bool __sglScrollGUI(double dx, double dy)
{
  if (!GUI) return false;
  SX = dx;
  SY = dy;
  flags |= __F_SCROLLING;
  GUI();
  if (!(flags & __F_SCROLLING)) return true;
  flags &= ~__F_SCROLLING;
  return false;
}

bool sglIsPointInRect(const SGLrect *rect, double x, double y)
{
  return !rect ||
    ((rect->width  <= 0 || (x >= rect->x && x <= rect->x + rect->width)) &&
     (rect->height <= 0 || (y >= rect->y && y <= rect->y + rect->height)));
}

void (*sglGetGUI(void))(void)
{
  return GUI;
}

void sglSetGUI(void (*gui)(void))
{
  if (program) GUI = gui;
}

uint sglScaleGUI(uint new_scale)
{
  uint previous = scale;
  if (new_scale) scale = new_scale;
  return previous;
}

bool sglTextureGUI(uint index, uint width, uint height)
{
  if (!(flags & __F_RENDERING)) return false;
  if (!(flags & __F_TEXTURED) || index != current)
  {
    __sglFlushGUI();
    sglUniform2f(0, u_texture, width, height);
    sglUniform1i(0, u_sampler, current = index);
    flags |= __F_TEXTURED;
  }
  return true;
}

void sglGetWindowSizeForGUI(double *width, double *height)
{
  int w, h;
  sglGetWindowSize(&w, &h);
  if (width) *width = w / (double) scale;
  if (height) *height = h / (double) scale;
}

void sglGetCursorForGUI(double *x, double *y)
{
  if (x) *x = X;
  if (y) *y = Y;
}

bool sglIsHoveringGUI(const SGLrect *rect)
{
  return sglIsPointInRect(rect, X, Y);
}

bool sglIsDraggingGUI(const SGLrect *rect)
{
  return (flags & __F_DRAGGING) && sglIsPointInRect(rect, DX, DY);
}

bool sglIsPressingGUI(const SGLrect *rect, int button)
{
  if (pressing && pressing == button && sglIsHoveringGUI(rect))
  {
    pressing = SGLB_NONE;
    return true;
  }
  return false;
}

bool sglIsScrollingGUI(const SGLrect *rect, double *dx, double *dy)
{
  if ((flags & __F_SCROLLING) && sglIsHoveringGUI(rect))
  {
    flags &= ~__F_SCROLLING;
    if (dx) *dx = SX;
    if (dy) *dy = SY;
    return true;
  }
  return false;
}

void sglSpriteGUI(const SGLrect *rect, const SGLsprite *sprite)
{
  if (!rect || !sprite || !(flags & __F_TEXTURED)) return;
  if (vertex_count == __BUFLEN) __sglFlushGUI();
  vertex_buffer[vertex_count].x = rect->x * scale;
  vertex_buffer[vertex_count].y = rect->y * scale;
  vertex_buffer[vertex_count].u = sprite->x_offset;
  vertex_buffer[vertex_count].v = sprite->y_offset;
  vertex_buffer[vertex_count].r = sglGetColorR(sprite->color);
  vertex_buffer[vertex_count].g = sglGetColorG(sprite->color);
  vertex_buffer[vertex_count].b = sglGetColorB(sprite->color);
  vertex_buffer[vertex_count].a = sglGetColorA(sprite->color);
  ++vertex_count;
  vertex_buffer[vertex_count].x = rect->x * scale;
  vertex_buffer[vertex_count].y = (rect->y + rect->height) * scale;
  vertex_buffer[vertex_count].u = sprite->x_offset;
  vertex_buffer[vertex_count].v = sprite->y_offset + sprite->height - 1;
  vertex_buffer[vertex_count].r = sglGetColorR(sprite->color);
  vertex_buffer[vertex_count].g = sglGetColorG(sprite->color);
  vertex_buffer[vertex_count].b = sglGetColorB(sprite->color);
  vertex_buffer[vertex_count].a = sglGetColorA(sprite->color);
  ++vertex_count;
  vertex_buffer[vertex_count].x = (rect->x + rect->width) * scale;
  vertex_buffer[vertex_count].y = (rect->y + rect->height) * scale;
  vertex_buffer[vertex_count].u = sprite->x_offset + sprite->width - 1;
  vertex_buffer[vertex_count].v = sprite->y_offset + sprite->height - 1;
  vertex_buffer[vertex_count].r = sglGetColorR(sprite->color);
  vertex_buffer[vertex_count].g = sglGetColorG(sprite->color);
  vertex_buffer[vertex_count].b = sglGetColorB(sprite->color);
  vertex_buffer[vertex_count].a = sglGetColorA(sprite->color);
  ++vertex_count;
  vertex_buffer[vertex_count].x = rect->x * scale;
  vertex_buffer[vertex_count].y = rect->y * scale;
  vertex_buffer[vertex_count].u = sprite->x_offset;
  vertex_buffer[vertex_count].v = sprite->y_offset;
  vertex_buffer[vertex_count].r = sglGetColorR(sprite->color);
  vertex_buffer[vertex_count].g = sglGetColorG(sprite->color);
  vertex_buffer[vertex_count].b = sglGetColorB(sprite->color);
  vertex_buffer[vertex_count].a = sglGetColorA(sprite->color);
  ++vertex_count;
  vertex_buffer[vertex_count].x = (rect->x + rect->width) * scale;
  vertex_buffer[vertex_count].y = (rect->y + rect->height) * scale;
  vertex_buffer[vertex_count].u = sprite->x_offset + sprite->width - 1;
  vertex_buffer[vertex_count].v = sprite->y_offset + sprite->height - 1;
  vertex_buffer[vertex_count].r = sglGetColorR(sprite->color);
  vertex_buffer[vertex_count].g = sglGetColorG(sprite->color);
  vertex_buffer[vertex_count].b = sglGetColorB(sprite->color);
  vertex_buffer[vertex_count].a = sglGetColorA(sprite->color);
  ++vertex_count;
  vertex_buffer[vertex_count].x = (rect->x + rect->width) * scale;
  vertex_buffer[vertex_count].y = rect->y * scale;
  vertex_buffer[vertex_count].u = sprite->x_offset + sprite->width - 1;
  vertex_buffer[vertex_count].v = sprite->y_offset;
  vertex_buffer[vertex_count].r = sglGetColorR(sprite->color);
  vertex_buffer[vertex_count].g = sglGetColorG(sprite->color);
  vertex_buffer[vertex_count].b = sglGetColorB(sprite->color);
  vertex_buffer[vertex_count].a = sglGetColorA(sprite->color);
  ++vertex_count;
}

int sglGetPressedButtonForGUI(const SGLrect *rect)
{
  int result = 0;
  if (pressing && sglIsHoveringGUI(rect))
  {
    result = pressing;
    pressing = 0;
  }
  return result;
}

const SGLfont *sglGetFont(void)
{
  return &_font;
}

bool sglSetFont(const SGLfont *font)
{
  if (!program) return false;
  if (font)
  {
    if (!font->texture_width ||
        !font->texture_height ||
        !font->glyph_width ||
        !font->texture_height ||
        !font->get_glyph ||
        !(font->texture_width / font->glyph_width)) return false;
    _font = *font;
  }
  else memset(&_font, 0, sizeof(_font));
  return true;
}

void sglGlyphGUI(const SGLrect *rect, int codepoint, int color)
{
  uint row;
  uint glyph;
  SGLsprite sprite;
  if (_font.get_glyph && sglTextureGUI(
        _font.texture_index, _font.texture_width, _font.texture_height))
  {
    row = _font.texture_width / _font.glyph_width;
    glyph = _font.get_glyph(codepoint);
    sprite.x_offset = (glyph % row) * _font.glyph_width;
    sprite.y_offset = (glyph / row) * _font.glyph_height;
    sprite.width = _font.glyph_width;
    sprite.height = _font.glyph_height;
    sprite.color = color;
    sglSpriteGUI(rect, &sprite);
  }
}

static int __sglNextCodepoint(const char **text)
{
  int result, left, ch = *(*text)++ & 0xFF;
  if (!(ch & 0x80)) return ch;
  else if (!(ch & 0x40)) return -1;
  else if (!(ch & 0x20))
  {
    result = ch & 0x1F;
    left = 1;
  }
  else if (!(ch & 0x10))
  {
    result = ch & 0x0F;
    left = 2;
  }
  else if (!(ch & 0x08))
  {
    result = ch & 0x07;
    left = 3;
  }
  else return -1;
  while (left--)
  {
    ch = **text & 0xFF;
    if ((ch & 0xC0) != 0x80) return -1;
    result = (result << 6) | (ch & 0x3F);
    ++*text;
  }
  return result;
}

void sglFlatTextGUI(double x, double y, const char *text, int color)
{
  SGLrect rect;
  int codepoint;
  if (!(flags & __F_RENDERING) || !text || !_font.get_glyph) return;
  rect.x = x;
  rect.y = y;
  rect.width = _font.glyph_width;
  rect.height = _font.glyph_height;
  while ((codepoint = __sglNextCodepoint(&text)))
  {
    sglGlyphGUI(&rect, codepoint, color);
    rect.x += rect.width;
  }
}

void sglGetTextRect(SGLrect *rect, double x, double y, const char *text)
{
  if (!rect) return;
  rect->x = x;
  rect->y = y;
  rect->width = 0;
  rect->height = 0;
  if (!text) return;
  rect->height = _font.glyph_height;
  if (!_font.glyph_width) return;
  while (__sglNextCodepoint(&text)) rect->width += _font.glyph_width;
}

