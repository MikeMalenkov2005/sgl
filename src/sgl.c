#include <sgl.h>

#include "sgl_gui_internal.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <string.h>

#define __F_FULLSCREEN  0x0001
#define __F_VSYNC       0x0002
#define __F_CURSOR      0x0004

static double X, Y;
static int W, H, flags;
static GLFWwindow *window;
static void (*on_render)(void);
static void (*on_update)(double delta);
static void (*on_scroll)(double dx, double dy);
static void (*on_button)(int button, int action, int mods);
static void (*on_cursor)(double x, double y, double dx, double dy);

static void __sgl_glfwErrorCallback(int code, const char *message)
{
  fprintf(stderr, ERR"GLFW %d: %s\n", code, message);
}

static void __sgl_glfwFramebufferSizeCallback(
    GLFWwindow *window, int width, int height)
{
  if (height < 1) glfwSetWindowSize(window, width, 1);
  else glViewport(0, 0, W = width, H = height);
}

static void __sgl_glfwScrollCallback(GLFWwindow *window, double dx, double dy)
{
  (void)window;
  if (!__sglScrollGUI(dx, dy) && on_scroll) on_scroll(dx, dy);
}

static void __sgl_glfwKeyCallback(
    GLFWwindow *window, int key, int scancode, int action, int mods)
{
  (void)window;
  (void)scancode;
  if (action != GLFW_PRESS || !__sglPressGUI(key, mods))
  {
    if (on_button) on_button(key, action, mods);
  }
}

static void __sgl_glfwMouseButtonCallback(
    GLFWwindow *window, int button, int action, int mods)
{
  __sgl_glfwKeyCallback(window, button + 1, 0, action, mods);
}

static void __sgl_glfwCursorPosCallback(GLFWwindow *window, double x, double y)
{
  (void)window;
  if (x != X || y != Y)
  {
    if (on_cursor) on_cursor(x, y, x - X, y - Y);
    X = x;
    Y = y;
  }
}

bool sglInitWindow(int width, int height, const char *title)
{
  glfwSetErrorCallback(__sgl_glfwErrorCallback);
  glfwInitAllocator((const GLFWallocator *)sglGetAllocator());
  if (!glfwInit())
  {
    fprintf(stderr, ERR"Failed to initialize GLFW!\n");
    goto error;
  }
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  if (!(window = glfwCreateWindow(W = width, H = height, title, NULL, NULL)))
  {
    fprintf(stderr, ERR"Failed to create the main window!\n");
    goto error;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    fprintf(stderr, ERR"Failed to load OpenGL 3.2!\n");
    goto error;
  }
  if (!__sglInitGUI())
  {
    fprintf(stderr, ERR"Failed to initialize GUI!\n");
    goto error;
  }
  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthFunc(GL_LEQUAL);
  glfwSetFramebufferSizeCallback(window, __sgl_glfwFramebufferSizeCallback);
  glfwSetMouseButtonCallback(window, __sgl_glfwMouseButtonCallback);
  glfwSetCursorPosCallback(window, __sgl_glfwCursorPosCallback);
  glfwSetScrollCallback(window, __sgl_glfwScrollCallback);
  glfwSetKeyCallback(window, __sgl_glfwKeyCallback);
  glfwGetCursorPos(window, &X, &Y);
  glfwSwapInterval(0);
  return true;
error:
  W = H = 0;
  window = NULL;
  glfwTerminate();
  return false;
}

void sglLoopWindow(void)
{
  double old_time, time;
  if (!window) return;
  old_time = glfwGetTime();
  while (!glfwWindowShouldClose(window))
  {
    time = glfwGetTime();
    if (on_update) on_update(time - old_time);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (on_render) on_render();
    __sglRenderGUI();
    glfwSwapBuffers(window);
    glfwPollEvents();
    old_time = time;
  }
  __sglFreeGUI();
  X = Y = 0;
  W = H = 0;
  flags = 0;
  window = NULL;
  on_render = NULL;
  on_update = NULL;
  on_scroll = NULL;
  on_button = NULL;
  on_cursor = NULL;
  glfwTerminate();
}

void sglCloseWindow(void)
{
  if (window) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void sglSetWindowColor(int color)
{
  if (window) glClearColor(
      sglGetColorR(color) / 255.0,
      sglGetColorG(color) / 255.0,
      sglGetColorB(color) / 255.0,
      sglGetColorA(color) / 255.0);
}

void sglSetWindowSizeLimits(
    int min_width, int min_height, int max_width, int max_height)
{
  if (window) glfwSetWindowSizeLimits(
      window, min_width, min_height, max_width, max_height);
}

void sglGetWindowSize(int *width, int *height)
{
  if (width) *width = W;
  if (height) *height = H;
}  

void sglSetWindowSize(int width, int height)
{
  if (window) glfwSetWindowSize(window, width, height);
}

bool sglGetFullscreen(void)
{
  return !!(flags & __F_FULLSCREEN);
}

void sglSetFullscreen(bool fullscreen)
{
  static int x, y, w, h;
  static GLFWmonitor *monitor;
  static const GLFWvidmode *vidmode;
  if (window && (sglGetFullscreen() ^ !!fullscreen))
  {
    if (fullscreen)
    {
      if (!monitor && !(monitor = glfwGetPrimaryMonitor())) return;
      if (!vidmode && !(vidmode = glfwGetVideoMode(monitor))) return;
      glfwSetWindowMonitor(window, monitor,
          0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
    }
    else glfwSetWindowMonitor(window, NULL, x, y, w, h, GLFW_DONT_CARE);
    flags ^= 1;
  }
}

bool sglGetVSync(void)
{
  return !!(flags & __F_VSYNC);
}

void sglSetVSync(bool vsync)
{
  if (window && (sglGetVSync() ^ !!vsync))
  {
    glfwSwapInterval(!!vsync);
    flags ^= __F_VSYNC;
  }
}

bool sglGetCursorEnabled(void)
{
  return !(flags & __F_CURSOR);
}

void sglGetCursor(double *x, double *y)
{
  if (x) *x = X;
  if (y) *y = Y;
}

void sglSetCursor(double x, double y)
{
  if (window) glfwSetCursorPos(window, X = x, Y = y);
}

bool sglGetButton(int button)
{
  if (window)
  {
    if (button > SGLB_MOUSE_LAST) return glfwGetKey(window, button);
    if (button > SGLB_NONE) return glfwGetMouseButton(window, button - 1);
  }
  return false;
}

void sglSetCursorEnabled(bool enabled)
{
  if (window && (sglGetCursorEnabled() ^ !!enabled))
  {
    glfwSetInputMode(window, GLFW_CURSOR,
        enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    flags ^= __F_CURSOR;
  }
}

void sglSetRenderCallback(void (*callback)(void))
{
  if (window) on_render = callback;
}

void sglSetUpdateCallback(void (*callback)(double delta))
{
  if (window) on_update = callback;
}

void sglSetScrollCallback(void (*callback)(double dx, double dy))
{
  if (window) on_scroll = callback;
}

void sglSetButtonCallback(void (*callback)(int button, int action, int mods))
{
  if (window) on_button = callback;
}

void sglSetCursorCallback(
    void (*callback)(double x, double y, double dx, double dy))
{
  if (window) on_cursor = callback;
}

