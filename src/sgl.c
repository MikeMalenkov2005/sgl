#include <sgl.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <string.h>

#define __F_FULLSCREEN  0x0001
#define __F_VSYNC       0x0002
#define __F_CURSOR      0x0004

static int flags;
static GLFWwindow *window;

bool sglInitWindow(int width, int height, const char *title)
{
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
  if (!(window = glfwCreateWindow(width, height, title, NULL, NULL)))
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
  glfwSwapInterval(0);
  return true;
error:
  glfwTerminate();
  window = NULL;
  return false;
}

void sglLoopWindow(void)
{
  double time, delta;
  static double old_time;
  if (!window) return;
  old_time = glfwGetTime();
  while (!glfwWindowShouldClose(window))
  {
    time = glfwGetTime();
    delta = time - old_time;
    old_time = time;
    (void)delta;
  }
  glfwTerminate();
  window = NULL;
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

void sglSetCursorEnabled(bool enabled)
{
  if (window && (sglGetCursorEnabled() ^ !!enabled))
  {
    glfwSetInputMode(window, GLFW_CURSOR,
        enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    flags ^= __F_CURSOR;
  }
}

