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
    //+------------------------------

   
    glm::vec3    pos_       =  glm::vec3(0.0f, 0.0f, 0.0f);
    float        rotation_  =  0.0f;
    
    double       shoot_cd_  =  0.75;   // time between shots
    double       lastshot_  =  0.0; // the of the last shot
    

    shader_obj::Shader& current_shader_;
    std::vector<Projectile> projectiles_; // vector of all active projectiles
    models::Quad& model_; // in this case the player model is just a square


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


    // called 60 times a second in each FixedUpdate()
    // processes movement actions from the glfwPollEvents()
    // called before it.
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

    }


    // called 60 times a second in each FixedUpdate()
    // processes the positional data of the cursor to change
    // rotation of the player to look at the cursor.
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


    // called 60 times a second in each FixedUpdate() to check mouse button
    // input and the cooldown on the shooting player. 
    // basically, this recieves mouse input and makes the player shoot
    // accordingly.
    void ProcessShooting(GLFWwindow* window) {

      if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        if (glfwGetTime() - lastshot_ > shoot_cd_) {
          Shoot();
          lastshot_ = glfwGetTime();
        }

      }

    }


    // called every frame in Render() to draw the player
    void Draw() {

      current_shader_.use();
      model_.Select();

      glm::mat4 model_mat = glm::mat4(1.0f);
      model_mat = glm::translate(model_mat, pos_);
      model_mat = glm::rotate(
      model_mat, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
      current_shader_.SetMat4fv("model", model_mat);

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    

    // called in ProcessShooting() when the player is able to shoot
    void Shoot() {

      projectiles_.push_back(Projectile(*this, model_, rotation_));
      //std::cout << projectiles_.size() << std::endl;

    }
    


    // called every frame in Render()
    void DrawProjectiles() {

      if (projectiles_.size()) {

        for (Projectile& p : projectiles_) {

          p.Draw(current_shader_);

        }
      }
    }


    // called 60 times a second in each FixedUpdate() to
    // update the positions of the player's projectiles and cull
    // ones that have expired
    void UpdateProjectiles() {

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

      glm::vec3           pos_       =  glm::vec3(0.0f, 0.0f, 0.0f);
      glm::vec3           direct_    =  glm::vec3(0.0f, 0.0f, 0.0f); // below*
      float               rotation_  =  0.0f;
      static const int    lifetime_  =  120; // measured in FixedUpdate()s

      // * direct_ is initialized to zero, but immedialty changes in the
      // constructor to be a unit vector in the direction that the player
      // shot in. it is then added to the pos_ of the projectile every
      // FixedUpdate() in Move() to make the projectile travel through space

      std::reference_wrapper<models::Quad> model_;
      // reference_wrapper is a reference that is copyable and
      // movable. it is needed because Projectile objects are going
      // into a std::vector, where they are copied and moved

    public:

      bool            is_dead_   =  false; // when this is true it is deleted
      int             age_       =  0; // measured in FixedUpdate()s


    public:


      Projectile(Player& player, models::Quad& model, double angle)
        : model_(model) {

        pos_ = player.GetPos();
        rotation_ = player.rotation_;

        constexpr float NDIR = glm::radians(90.0f);

        direct_.x = cos(rotation_ + NDIR) / 5.0f;
        direct_.y = sin(rotation_ + NDIR) / 5.0f;

      }




      // called for every projectile for a player in 
      // player::Player.DrawProjectiles() which is called every frame
      // in Render()
      void Draw(shader_obj::Shader& shader) {

        shader.use();

        // since model_ is a std::reference_wrapper, you have to use
        // .get() to "get" to to access the object it is wrapping
        model_.get().Select();

        glm::mat4 model_mat = glm::mat4(1.0f);
        model_mat = glm::translate(model_mat, pos_);
        model_mat = glm::rotate(
        model_mat, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetMat4fv("model", model_mat);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      }


      // used to update the postion of a projectile
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