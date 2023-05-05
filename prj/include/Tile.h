#ifndef PRJ_INCLUDE_TILE_H
#define PRJ_INCLUDE_TILE_H



#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <GameObject.h>
#include <shader_obj.h>
#include <models.h>

class Tile : GameObject {


  Quad2D& model_ = *g_QUAD2D;


public:

  Tile(glm::vec3 position, ShaderProgram& shaderProgram)
    : GameObject(position, 0.0f, shaderProgram) {

  }


  void draw() override {

    model_.select();

    shaderProgram_.updateMatrix(MODEL, pos_);

    shaderProgram_.select();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  }

};



#endif