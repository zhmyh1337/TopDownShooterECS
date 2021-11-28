#pragma once
#include <vector>
#include <type_traits>
#include "glad/glad.h"
#include "3dmath.h"
class VertexArrayObject
{
private:
  GLuint vertexArrayBufferObject;
  int numIndices;
  template<int i>
    void InitChannel() { }
  template<int i, typename T, typename... Channel>
  void InitChannel(const std::vector<T> &channel, const Channel&... channels)
  {
    if (channel.size())
    {
      GLuint arrayBuffer;
      glGenBuffers(1, &arrayBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(T) * channel.size(), channel.data(), GL_STATIC_DRAW);
      glEnableVertexAttribArray(i);
      
      const int size = sizeof(T) / sizeof(channel[0][0]);
      static_assert(size <= 4);
      if (std::is_same<T, uvec4>::value) 
        glVertexAttribIPointer(i, size, GL_UNSIGNED_INT, 0, 0);
      else
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, 0, 0);
    }
    InitChannel<i + 1>(channels...);
  }
public:
  VertexArrayObject():
  vertexArrayBufferObject(0), numIndices(0)
  {}
  uint vao() const
  {
    return vertexArrayBufferObject;
  }
  template<typename... Channel>
  VertexArrayObject(const std::vector<unsigned int> &indices, const Channel&... channels)
  {
    //int channelCount = sizeof...(channels);
  
    glGenVertexArrays(1, &vertexArrayBufferObject);
    glBindVertexArray(vertexArrayBufferObject);

    InitChannel<0>(channels...);
  
    GLuint arrayIndexBuffer;
    glGenBuffers(1, &arrayIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arrayIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
 
    glBindVertexArray(0);
    numIndices = indices.size();
  }
  void render(bool wire_frame = false) const
  {
    glBindVertexArray(vertexArrayBufferObject);
    glDrawElementsBaseVertex(wire_frame ? GL_LINES : GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0, 0);
    glBindVertexArray(0);
  }
  void render_instances(int instance, bool wire_frame = false) const
  {
    glBindVertexArray(vertexArrayBufferObject);
    glDrawElementsInstancedBaseVertex(wire_frame ? GL_LINES : GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0, instance, 0);
    glBindVertexArray(0);
  }
  bool is_valid() const
  {
    return vertexArrayBufferObject > 0 && numIndices > 0;
  }
};