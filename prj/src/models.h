#ifndef MODELS_H_
#define MODELS_H_

#include <glad/glad.h>


namespace mod {

  class Quad {

  private:
    
    unsigned int vao_, vbo_, ebo_;

  public:

    Quad() {

      float vertex_data[] = {
        // position attr
      -0.5f,  0.5f, 0.0f,  //top left
       0.5f,  0.5f, 0.0f,   //top right
       0.5f, -0.5f, 0.0f,  //bottom right
      -0.5f, -0.5f, 0.0f   //bottom left
      };

      unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
      };

      glGenVertexArrays(1, &vao_);
      glGenBuffers(1, &vbo_);
      glGenBuffers(1, &ebo_);

      glBindVertexArray(vao_);

      glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
      glEnableVertexAttribArray(0);

      glBindVertexArray(0);
    }

  public:
    
    inline void Select() {
      glBindVertexArray(vao_);
    }
    inline void Deselect() {
      glBindVertexArray(0);
    }

  };



}

#endif