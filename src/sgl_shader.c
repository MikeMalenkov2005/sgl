#include <sgl.h>

#include <glad/glad.h>

#include <stdarg.h>

uint sglCreateShader(uint type, const char *source)
{
  static const GLenum lut[2] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
  char *log;
  int value;
  uint shader = 0;
  if (type-- && type < 2 && source)
  {
    if ((shader = glCreateShader(lut[type])))
    {
      glShaderSource(shader, 1, &source, NULL);
      glCompileShader(shader);
      glGetShaderiv(shader, GL_COMPILE_STATUS, &value);
      if (!value)
      {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &value);
        fprintf(stderr, ERR"Failed to compile a shader!\n");
        if ((log = sglAllocate(value)))
        {
          glGetShaderInfoLog(shader, value, NULL, log);
          fprintf(stderr, "%s\n", log);
          sglDeallocate(log);
        }
        glDeleteShader(shader);
        shader = 0;
      }
    }
    else fprintf(stderr, ERR"Failed to create a shader!\n");
  }
  else fprintf(stderr, ERR"Invalid shader arguments!\n");
  return shader;
}

void sglDeleteShader(uint shader)
{
  glDeleteShader(shader);
}

uint sglLoadShader(uint type, const char *path)
{
  char *source = sglLoadFile(path, NULL);
  uint shader = sglCreateShader(type, source);
  if (source) sglDeallocate(source);
  if (!shader) fprintf(stderr, ERR "Failed to load shader from '%s'!\n", path);
  return shader;
}

uint sglCreateProgram(uint shader, ...)
{
  va_list ap;
  char *log;
  int value;
  uint program = glCreateProgram();
  if (program)
  {
    va_start(ap, shader);
    while (shader)
    {
      glAttachShader(program, shader);
      shader = va_arg(ap, uint);
    }
    va_end(ap);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &value);
    if (!value)
    {
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &value);
      fprintf(stderr, ERR"Failed to link a shader program!\n");
      if ((log = sglAllocate(value)))
      {
        glGetProgramInfoLog(shader, value, NULL, log);
        fprintf(stderr, "%s\n", log);
        sglDeallocate(log);
      }
      glDeleteProgram(program);
      program = 0;
    }
  }
  else fprintf(stderr, ERR"Failed to create a shader program!\n");
  return program;
}

void sglDeleteProgram(uint program)
{
  glDeleteProgram(program);
}

uint sglLoadSimpleProgram(const char *vert_path, const char *frag_path)
{
  uint vert = sglLoadShader(SGL_SHADER_VERT, vert_path);
  uint frag = sglLoadShader(SGL_SHADER_FRAG, frag_path);
  uint program = vert && frag ? sglCreateProgram(vert, frag, 0) : 0;
  sglDeleteShader(vert);
  sglDeleteShader(frag);
  return program;
}

uint sglBindProgram(uint program)
{
  static uint current;
  uint previous = current;
  if (program != current) glUseProgram(current = program);
  return previous;
}

void sglSetAttributeIndex(uint program, const char *name, uint index)
{
  glBindAttribLocation(program, index, name);
}

int sglGetUniformIndex(uint program, const char *name)
{
  return glGetUniformLocation(program, name);
}

void sglUniform1i(uint program, int index, int x)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniform1i(index, x);
  if (program) sglBindProgram(previous);
}

void sglUniform2i(uint program, int index, int x, int y)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniform2i(index, x, y);
  if (program) sglBindProgram(previous);
}

void sglUniform3i(uint program, int index, int x, int y, int z)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniform3i(index, x, y, z);
  if (program) sglBindProgram(previous);
}

void sglUniform4i(uint program, int index, int x, int y, int z, int w)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniform4i(index, x, y, z, w);
  if (program) sglBindProgram(previous);
}

void sglUniform1f(uint program, int index, float x)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniform1f(index, x);
  if (program) sglBindProgram(previous);
}

void sglUniform2f(uint program, int index, float x, float y)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniform2f(index, x, y);
  if (program) sglBindProgram(previous);
}

void sglUniform3f(uint program, int index, float x, float y, float z)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniform3f(index, x, y, z);
  if (program) sglBindProgram(previous);
}

void sglUniform4f(uint program, int index, float x, float y, float z, float w)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniform4f(index, x, y, z, w);
  if (program) sglBindProgram(previous);
}

void sglUniformMatrix(uint program, int index, const SGLmatrix *matrix)
{
  uint previous;
  if (program) previous = sglBindProgram(program);
  glUniformMatrix4fv(index, 1, GL_TRUE, matrix->data);
  if (program) sglBindProgram(previous);
}

