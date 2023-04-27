#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>


#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "models.h"
#include "shader_obj.h"

namespace player {
  







  class Player {

    class Projectile;

   
    glm::vec3        pos_       =  glm::vec3(0.0f, 0.0f, 0.0f);
    float            rotation_  =  0.0f;
    
    shader_obj::Shader& current_shader_;
    std::vector<Projectile> projectiles_;
    models::Quad& model_;


  public:

    Player(shader_obj::Shader& shader, models::Quad& model) 
      : current_shader_(shader), model_(model) {
    }




    inline glm::vec3 GetPos() const {
      return pos_;
    }



    inline void SetRotation(float angle) {
      rotation_ = angle;
    }



    void ProcessMovement(GLFWwindow* window) {
      // make key input do stuff
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        pos_ += glm::vec3(0.0f, 0.1f, 0.0f);
      }
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        pos_ += glm::vec3(-0.1f, 0.0f, 0.0f);
      }
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        pos_ += glm::vec3(0.0f, -0.1f, 0.0f);
      }
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        pos_ += glm::vec3(0.1f, 0.0f, 0.0f);
      }
      if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        Shoot();
      }
    }

    void ProcessLookingDirection(GLFWwindow* window) {
      double mouse_posx, mouse_posy;
      glfwGetCursorPos(window, &mouse_posx, &mouse_posy);
      int width, height;
      glfwGetWindowSize(window, &width, &height);
      mouse_posy = height - mouse_posy;
      int player_posx = width / 2;
      int player_posy = height / 2;

      int look_directionx = mouse_posx - player_posx;
      int look_directiony = mouse_posy - player_posy;

      constexpr double NDIR = glm::radians(90.0f);

      double angle = atan2(look_directiony, look_directionx) - NDIR;

      rotation_ = angle;
    }



    void Draw() {

      current_shader_.use();
      model_.Select();

      glm::mat4 model_mat = glm::mat4(1.0f);
      model_mat = glm::translate(model_mat, pos_);
      model_mat = glm::rotate(model_mat, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
      current_shader_.SetMat4fv("model", model_mat);

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }


    void Shoot() {
      projectiles_.push_back(Projectile(*this, rotation_));
      std::cout << projectiles_.size() << std::endl;
    }
    


    void DrawProjectiles() {

      if (projectiles_.size()) {
        for (Projectile& p : projectiles_) {
          p.Draw(current_shader_);
        }
      }
    }



    void UpdateProjectiles() { // TODO: FIX
      if (projectiles_.size()) {
        for (int i = 0; i < projectiles_.size(); i++) {
          projectiles_[i].Move();
          if (projectiles_[i].is_dead_) {
            projectiles_.erase(projectiles_.begin() + i);
            i--;
          }
          else {
            projectiles_[i].age_++;
          }
         
          
        }
      }
    }


    



  private:
    
    class Projectile {
   
      models::Quad    model_     =  models::Quad(); // TODO dump instance of quad in each projectile
      glm::vec3       pos_       =  glm::vec3(0.0f, 0.0f, 0.0f);
      glm::vec3       direct_    =  glm::vec3(0.1f, 0.1f, 0.0f);
      const int       lifetime_  =  120;

    public:

      bool            is_dead_   =  false;
      int             age_       =  0;


    public:


      Projectile(Player& player, double angle) {

        pos_ = player.GetPos();


      }



      Projectile() {}



      void Draw(shader_obj::Shader& shader) {

        shader.use();
        model_.Select();

        glm::mat4 model_mat = glm::mat4(1.0f);
        model_mat = glm::translate(model_mat, pos_);
        shader.SetMat4fv("model", model_mat);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      }



      void Move() {

        if (age_ < lifetime_) {
          pos_ += direct_;
        }
        else {
          is_dead_ = true;
        }
      }



    };
  
    

  };

  

}

#endif