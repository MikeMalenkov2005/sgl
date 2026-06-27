#include <sgl.h>

#include <glad/glad.h>

#include <stdarg.h>
#include <string.h>

SGLmesh sglCreateMesh(uint stride, ...)
{
  static int max;
  static GLenum lut1[8] =
  {
    0, GL_FLOAT, GL_INT, GL_SHORT, GL_BYTE,
    GL_UNSIGNED_INT, GL_UNSIGNED_SHORT, GL_UNSIGNED_BYTE
  };
  static unsigned int lut2[8] = { 0, 4, 4, 2, 1, 4, 2, 1 };
  
  va_list ap;
  SGLmesh mesh = { 0 };
  uint size, type, attrib, i;
  const char *offset = NULL;

  if (!max) glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max);

  mesh.stride = stride;
  glGenBuffers(1, &mesh.vbo);
  glGenVertexArrays(1, &mesh.vao);
  if (mesh.vao && mesh.vbo)
  {
    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    va_start(ap, stride);
    for (i = 0; i < (uint)max; ++i)
    {
      attrib = va_arg(ap, int);
      type = sglGetAttribType(attrib);
      if (!type) break;
      size = sglGetAttribSize(attrib);
      glEnableVertexAttribArray(i);
      if (type == SGL_ATTRIB_TYPE_FLOAT || !sglIsAttribInteger(attrib))
      {
        glVertexAttribPointer(i, size, lut1[type],
            sglIsAttribNormalized(attrib), stride, offset);
      }
      else glVertexAttribIPointer(i, size, lut1[type], stride, offset);
      offset += lut2[type] * size;
    }
    va_end(ap);
    glBindVertexArray(0);
  }
  else
  {
    fprintf(stderr, ERR"Failed to create a mesh!\n");
    sglDeleteMesh(&mesh);
  }
  return mesh;
}

void sglDeleteMesh(SGLmesh *mesh)
{
  if (mesh)
  {
    glDeleteVertexArrays(1, &mesh->vao);
    glDeleteBuffers(1, &mesh->vbo);
    memset(mesh, 0, sizeof(*mesh));
  }
}

bool sglSetMeshData(SGLmesh *mesh, const void *data, size_t size)
{
  if (!mesh || !mesh->vao || !mesh->vbo || !mesh->stride) return false;
  mesh->count = size / mesh->stride;
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  return true;
}

void sglDrawMesh(const SGLmesh *mesh)
{
  if (mesh && mesh->vao && mesh->vbo && mesh->count)
  {
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->count);
    glBindVertexArray(0);
  }
}

