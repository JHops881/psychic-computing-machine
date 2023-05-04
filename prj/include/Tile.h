#ifndef PRJ_INCLUDE_TILE_H
#define PRJ_INCLUDE_TILE_H



#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <GameObject.h>
#include <shader_obj.h>
#include <models.h>

class Tile : GameObject {


  Quad2D model_ = Quad2D();


public:

  Tile(glm::vec3 position, ShaderProgram& shaderProgram)
    : GameObject(position, 0.0f, shaderProgram) {

  }


  void draw() override {

    model_.select();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, pos_);
    shaderProgram_.setMat4fv("model", modelMatrix);

    shaderProgram_.use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  }

};



#endif