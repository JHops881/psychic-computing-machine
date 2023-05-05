#ifndef PRJ_INCLUDE_WALL_H
#define PRJ_INCLUDE_WALL_H



#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <GameObject.h>
#include <shader_obj.h>
#include <models.h>

class Wall : GameObject {

public:
  
  Wall(glm::vec3 position, ShaderProgram& shaderProgram)
    : GameObject(position, 0.0f , shaderProgram) {

  }

  
  void draw() override {
    
    cuboidModel_->select();

    shaderProgram_.updateMatrix(MODEL, pos_);

    shaderProgram_.select();
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

  }

};



#endif

