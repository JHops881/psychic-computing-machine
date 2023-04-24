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

  class Projectile {
  public:

    mod::Quad model_{ mod::Quad() };
    glm::vec3 pos_{ glm::vec3(0.0f, 0.0f, 0.0f) };
    glm::vec3 endpos_{ glm::vec3(0.0f, 0.0f, 0.0f) };
    glm::mat4 matrix_{ glm::mat4(1.0f) };

  public:

    Projectile(Player& player, double angle) {
      
      pos_ = player.GetPos();

      double projectile_distance = 10.0;
      float endpos_y = (float)(projectile_distance * sin(glm::degrees(angle)));
      float endpos_x = (float)(sqrt(pow(projectile_distance, 2) - pow(endpos_y, 2)));

      endpos_ = glm::vec3(endpos_x, endpos_y, 0.0f);
      
      float m = (endpos_y / endpos_x);

      matrix_ = glm::translate(matrix_, glm::vec3(1.0f / 10.0f, m / 10.0f, 0.0f));

    }

    Projectile() {}

    void Draw(Shader shader) {
      shader.use();
      model_.Select();
      glm::mat4 model_mat = glm::mat4(1.0f);
      model_mat = glm::translate(model_mat, pos_);
      shader.SetMat4fv("model", model_mat);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void Move() {
      
      if (pos_.x < endpos_.x && pos_.y < endpos_.y) {
        glm::vec4 r = glm::vec4(pos_.x, pos_.y, pos_.z, 1.0f);
        r = matrix_ * r;
        pos_ = glm::vec3(r.x, r.y, r.z);
      }
      else {
        delete this;
      }
    }

  };

}

#endif