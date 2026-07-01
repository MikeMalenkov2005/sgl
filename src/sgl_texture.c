#include <sgl.h>

#include <glad/glad.h>
#include <stb_image.h>

#include <string.h>

static GLuint current;

SGLtexture sglCreateTexture(
    int width, int height, int channels, const uchar* pixels)
{
  static const GLenum lut1[4] =
  { GL_LUMINANCE8, GL_LUMINANCE8_ALPHA8, GL_RGB8, GL_RGBA8 };
  static const GLenum lut2[4] =
  { GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA };
  SGLtexture texture = { 0 };
  if (width > 0 && height > 0 && channels > 0 && channels < 5 && pixels)
  {
    glGenTextures(1, &texture._id);
    if (texture._id)
    {
      texture.width = width;
      texture.height = height;
      texture.channels = channels;
      glBindTexture(GL_TEXTURE_2D, texture._id);
      glTexImage2D(GL_TEXTURE_2D, 0, lut1[channels - 1],
          width, height, 0, lut2[channels - 1], GL_UNSIGNED_BYTE, pixels);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glBindTexture(GL_TEXTURE_2D, current);
    }
    else fprintf(stderr, ERR"Failed to create a texture!\n");
  }
  else fprintf(stderr, ERR"Invalid texture arguments!\n");
  return texture;
}

void sglDeleteTexture(SGLtexture *texture)
{
  if (texture)
  {
    if (current == texture->_id) current = 0;
    glDeleteTextures(1, &texture->_id);
    memset(texture, 0, sizeof(*texture));
  }
}

SGLtexture sglLoadTexture(const char *path)
{
  FILE *file;
  uchar *pixels;
  SGLtexture texture = { 0 };
  int width, height, channels;
  if (path && (file = fopen(path, "rb")))
  {
    if ((pixels = stbi_load_from_file(file, &width, &height, &channels, 0)))
    {
      texture = sglCreateTexture(width, height, channels, pixels);
      stbi_image_free(pixels);
    }
    fclose(file);
  }
  if (!texture._id)
  {
    fprintf(stderr, ERR "Failed to load texture from '%s'!\n", path);
  }
  return texture;
}

void sglBindTexture(uint index, const SGLtexture *texture)
{
  static int max;
  if (index)
  {
    if (!max) glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
    if ((uint)max > index)
    {
      glActiveTexture(GL_TEXTURE0 + index);
      glBindTexture(GL_TEXTURE_2D, texture ? texture->_id : 0);
      glActiveTexture(GL_TEXTURE0);
    }
  }
  else glBindTexture(GL_TEXTURE_2D, current = texture ? texture->_id : 0);
}

void sglSetTextureFilter(const SGLtexture *texture, bool filter)
{
  if (texture->_id != current) glBindTexture(GL_TEXTURE_2D, texture->_id);
  glTexParameteri(GL_TEXTURE_2D,
      GL_TEXTURE_MIN_FILTER, filter ? GL_LINEAR : GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,
      GL_TEXTURE_MAG_FILTER, filter ? GL_LINEAR : GL_NEAREST);
  if (texture->_id != current) glBindTexture(GL_TEXTURE_2D, current);
}

