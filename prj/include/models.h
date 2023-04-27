#ifndef MODELS_H_
#define MODELS_H_

#include <glad/glad.h>

// models contains all the 2D and 3D graphical objects
// that are used in the game.
namespace models {



  // the Quad class is just a square
  class Quad {

  private:
    
    unsigned int vao_{};
    unsigned int vbo_{};
    unsigned int ebo_{};

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



  // The wall class defines a 3D graphical object that will
  // display be a wall when selected and drawn by openGL
  class Wall {

  private:

    unsigned int vao_{};
    unsigned int vbo_{};
    unsigned int ebo_{};

  public:

    Wall() {

      float vertex_data[] = {
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

  // enable depth testing with the z-buffer
  // with openGL so we dont get weird stuff
  inline void TurnOnOpenGLDepthTesting() {
    
  }
  

  // enable face culling. OpenGL will cull all faces of 
  // objects that are not front facing. saves 50% performance.
  inline void TurnOnClockwiseOpenGLFaceCulling() {
    
  }
  
  // wirecframe mode!
  inline void TurnOnOpenGLWireframeMode() {
   
  }
  

}

#endif