#ifndef TYPING_H
#define TYPING_H

#include "sgl_types.h"

#define SGL_ASCII_DIGIT "0123456789"

#define SGL_ASCII_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define SGL_ASCII_LOWER "abcdefghijklmnopqrstuvwxyz"

#define SGL_ASCII_ALPHA SGL_ASCII_UPPER SGL_ASCII_LOWER

#define SGL_ASCII_ALNUM SGL_ASCII_DIGIT SGL_ASCII_ALPHA

#define SGL_ASCII_PRINT                               \
  " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMN" \
  "OPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

void sglTypeCodepoint(int codepoint);
void sglTypeSpecialButton(int button, int mods);

void        sglSetTypingFilter(const char *filter);
const char *sglGetTypingFilter(void);

void        sglSetTypingBuffer(char *buffer, size_t size);
const char *sglGetTypingBuffer(void);

void    sglSetTypingIndex(size_t index);
size_t  sglGetTypingIndex(void);

void      sglSetTypingSelection(ptrdiff_t selection);
ptrdiff_t sglGetTypingSelection(void);

#endif

