#include <sgl.h>

static void (*GUI)(void);

void (*sglGetGUI(void))(void)
{
  return GUI;
}

void sglSetGUI(void (*gui)(void))
{
  GUI = gui;
}

