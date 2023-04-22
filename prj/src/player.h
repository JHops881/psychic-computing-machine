#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <glad/glad.h>


#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "models.h"
#include "shader.h"

namespace plr {

  class Player {

  private:

    mod::Quad model = mod::Quad();
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);

  public:
    
    Player() {
    std::cout << "made player" << std::endl;
    }

  private:

  public:
    glm::vec3 GetPos() {
      return pos;
    }

    void Draw(Shader shader) {
      shader.use();
      model.Select();
      glm::mat4 model_mat = glm::mat4(1.0f);
      model_mat = glm::translate(model_mat, pos);
      shader.SetMat4fv("model", model_mat);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    void MoveAmount(glm::vec3 amount) {
      pos += amount;
    }

  
    

  };

}

#endif