#ifndef PRJ_INCLUDE_MODELS_H_
#define PRJ_INCLUDE_MODELS_H_

#include <glad/glad.h>

// models contains all the 2D and 3D graphical objects
// that are used in the game.
namespace models {



  // The Quad class defines a 3D graphical model that will
  // display be a 2DSquare when selected and drawn by openGL
  class Quad {

  private:
    
    unsigned int vao_{};
    unsigned int vbo_{};
    unsigned int ebo_{};

  public:

    Quad() {

      float vertexData[] = {
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
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
      glEnableVertexAttribArray(0);

      glBindVertexArray(0);
    }

  public:
    
    inline void select() {
      glBindVertexArray(vao_);
    }
    inline void deselect() {
      glBindVertexArray(0);
    }

  };



  // The WallModel class defines a 3D graphical model that will
  // display be a wall when selected and drawn by openGL
  class WallModel {

  private:

    unsigned int vao_{};
    unsigned int vbo_{};
    unsigned int ebo_{};

  public:

    WallModel() {

      float vertexData[] = {
        // position attr
        -0.5f,  0.5f,  2.5f,  //FTL front top left     [0]
         0.5f,  0.5f,  2.5f,  //FTR front top right    [1]
         0.5f, -0.5f,  2.5f,  //FBR front bottom right [2]
        -0.5f, -0.5f,  2.5f,  //FBL front bottom left  [3]

        -0.5f,  0.5f,  0.0f,  //BTL back top left      [4]
         0.5f,  0.5f,  0.0f,  //BTR back top right     [5]
         0.5f, -0.5f,  0.0f,  //BBR back bottom right  [6]
        -0.5f, -0.5f,  0.0f   //BBL back bottom left   [7]
        };

      unsigned int indices[] = {
        0, 1, 2, // front face
        0, 2, 3,

        2, 1, 5, // east face
        2, 5, 6, 

        3, 2, 6, // south face
        3, 6, 7,

        0, 3, 7, // west face
        0, 7, 4,

        1, 0, 4, // north face
        1, 4, 5//,

        //6, 5, 4, // back face    
        //7, 6, 4
      };

      glGenVertexArrays(1, &vao_);
      glGenBuffers(1, &vbo_);
      glGenBuffers(1, &ebo_);

      glBindVertexArray(vao_);

      glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
      glEnableVertexAttribArray(0);

      glBindVertexArray(0);
    }

  public:

    inline void select() {
      glBindVertexArray(vao_);
    }
    inline void deselect() {
      glBindVertexArray(0);
    }

  };

  

}

#endif