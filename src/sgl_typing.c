#include <sgl.h>

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static const char *t_filter;

static char *t_buffer;
static size_t t_limit;
static size_t t_index;
static ptrdiff_t t_selection;

static void __sglTypeLeft(void)
{
  if (t_index) do --t_index;
  while (t_index && (t_buffer[t_index] & 0xC0) == 0x80);
}

static void __sglTypeRight(void)
{
  if (t_buffer[t_index]) do ++t_index;
  while ((t_buffer[t_index] & 0xC0) == 0x80);
}

static void __sglTypeDelete(void)
{
  size_t i;
  do for (i = t_index; t_buffer[i]; ++i) t_buffer[i] = t_buffer[i + 1];
  while ((t_buffer[t_index] & 0xC0) == 0x80);
}

static void __sglDeleteTypingSelection(void)
{
  if (t_selection < 0)
  {
    t_index += t_selection;
    t_selection = -t_selection;
  }
  while (t_selection)
  {
    --t_selection;
    __sglTypeDelete();
  }
}

static void __sglTypeString(const char *string)
{
  size_t i = strlen(string);
  size_t selection = t_selection < 0 ? -t_selection : t_selection;
  if (selection > i || (t_limit > i && !t_buffer[t_limit + selection - i]))
  {
    __sglDeleteTypingSelection();
    while (*string)
    {
      for (i = t_limit; i > t_index; --i)
      {
        t_buffer[i] = t_buffer[i - 1];
      }
      t_buffer[t_index++] = *string++;
    }
  }
}

void sglTypeCodepoint(int codepoint)
{
  char string[16] = { 0 };
  if (t_buffer && codepoint > 0)
  {
    if (codepoint < 0x80)
    {
      if ((isspace(codepoint) || isgraph(codepoint)))
      {
        string[0] = codepoint;
      }
      else if (codepoint == '\b')
      {
        if (t_index && !t_selection)
        {
          __sglTypeLeft();
          __sglTypeDelete();
        }
        else __sglDeleteTypingSelection();
      }
      else if (codepoint == 0x7F)
      {
        if (!t_selection) __sglTypeDelete();
        else __sglDeleteTypingSelection();
      }
    }
    else if (codepoint < 0x800)
    {
      string[0] = 0xC0 | ((codepoint >> 6) & 0x1F);
      string[1] = 0x80 | ((codepoint >> 0) & 0x3F);
    }
    else if (codepoint < 0x10000)
    {
      string[0] = 0xE0 | ((codepoint >> 12) & 0x0F);
      string[1] = 0x80 | ((codepoint >>  6) & 0x3F);
      string[2] = 0x80 | ((codepoint >>  0) & 0x3F);
    }
    else if (codepoint < 0x110000)
    {
      string[0] = 0xF0 | ((codepoint >> 18) & 0x07);
      string[1] = 0x80 | ((codepoint >> 12) & 0x3F);
      string[2] = 0x80 | ((codepoint >>  6) & 0x3F);
      string[3] = 0x80 | ((codepoint >>  0) & 0x3F);
    }
    if (!t_filter || strstr(t_filter, string)) __sglTypeString(string);
  }
}

void sglTypeSpecialButton(int button, int mods)
{
  if (t_buffer) switch (button)
  {
  case SGLB_KEY_BACKSPACE:
    sglTypeCodepoint('\b');
    break;
  case SGLB_KEY_KP_DECIMAL:
    if (mods & SGLB_MOD_NUM_LOCK) break;
  case SGLB_KEY_DELETE:
    sglTypeCodepoint(0x7F);
    break;
  case SGLB_KEY_RIGHT:
    t_selection -= ((mods & SGLB_MOD_SHIFT) && t_buffer[t_index]);
    __sglTypeRight();
    break;
  case SGLB_KEY_LEFT:
    t_selection += ((mods & SGLB_MOD_SHIFT) && t_index);
    __sglTypeLeft();
    break;
  }
}

void sglSetTypingFilter(const char *filter)
{
  t_filter = filter;
}

const char *sglGetTypingFilter(void)
{
  return t_filter;
}

void sglSetTypingBuffer(char *buffer, size_t size)
{
  if ((t_buffer = buffer))
  {
    buffer[t_limit = --size] = 0;
    t_index = strlen(buffer);
  }
  else t_limit = t_index = 0;
  t_selection = 0;
}

const char *sglGetTypingBuffer(void)
{
  return t_buffer;
}

void sglSetTypingIndex(size_t index)
{
  if (t_buffer)
  {
    t_index = min(index, t_limit);
    while (t_index && (!t_buffer[t_index - 1] ||
          (t_buffer[t_index] & 0xC0) == 0x80)) --t_index;
    t_selection = 0;
  }
}

size_t sglGetTypingIndex(void)
{
  return t_index;
}

void sglSetTypingSelection(ptrdiff_t selection)
{
  if (t_buffer)
  {
    selection = max(selection, -(ptrdiff_t)t_index);
    selection = min(selection, t_limit + 1 - t_index);
    while (t_index + selection && (!t_buffer[t_index + selection] ||
          (t_buffer[t_index + selection] & 0xC0) == 0x80)) --selection;
    t_selection = selection;
  }
}

ptrdiff_t sglGetTypingSelection(void)
{
  return t_selection;
}

