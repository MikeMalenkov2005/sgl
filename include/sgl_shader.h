#ifndef SGL_SHADER_H
#define SGL_SHADER_H

#include "sgl_types.h"
#include "sgl_linalg.h"

#define SGL_SHADER_NONE 0
#define SGL_SHADER_VERT 1
#define SGL_SHADER_FRAG 2

uint sglCreateShader(uint type, const char *source);
void sglDeleteShader(uint shader);

uint sglLoadShader(uint type, const char *path);

uint sglCreateProgram(uint shader, ...);
void sglDeleteProgram(uint program);

uint sglLoadSimpleProgram(const char *vert_path, const char *frag_path);

uint sglBindProgram(uint program);

int sglGetAttributeIndex(uint program, const char *name);

int sglGetUniformIndex(uint program, const char *name);

void sglUniform1i(uint program, int index, int x);
void sglUniform2i(uint program, int index, int x, int y);
void sglUniform3i(uint program, int index, int x, int y, int z);
void sglUniform4i(uint program, int index, int x, int y, int z, int w);

void sglUniform1f(uint program, int index, float x);
void sglUniform2f(uint program, int index, float x, float y);
void sglUniform3f(uint program, int index, float x, float y, float z);
void sglUniform4f(uint program, int index, float x, float y, float z, float w);

void sglUniformMatrix(uint program, int index, const SGLmatrix *matrix);

#endif

