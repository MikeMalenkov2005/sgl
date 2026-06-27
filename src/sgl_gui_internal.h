#ifndef SGL_GUI_INTERNAL_H
#define SGL_GUI_INTERNAL_H

#include <sgl_types.h>

bool __sglInitGUI(void);
void __sglFreeGUI(void);

void __sglRenderGUI(void);
bool __sglPressGUI(int button, int mods);
bool __sglScrollGUI(double dx, double dy);

#endif

