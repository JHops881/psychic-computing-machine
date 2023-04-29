#ifndef PRJ_INCLUDE_PLAYER_H
#define PRJ_INCLUDE_PLAYER_H

#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>


#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <models.h>
#include <shader_obj.h>

namespace player {








  class Player {

    class Projectile;
    //+------------------------------


    glm::vec3    pos_       =  glm::vec3(0.0f, 0.0f, 0.0f);
    float        rotation_  =  0.0f;

    double       shootCD_  =  0.35;   // time between shots
    double       lastShot_  =  0.0; // the of the last shot


    shaderObj::Shader& currentShader_;
    std::vector<Projectile> projectiles_; // vector of all active projectiles
    models::Quad& model_; // in this case the player model is just a square


  public:

    Player(shaderObj::Shader& shader, models::Quad& model)
      : currentShader_(shader), model_(model) {

    }




    inline glm::vec3 getPos() const {

      return pos_;

    }



    inline void setRotation(float angle) {

      rotation_ = angle;

    }


    // called 60 times a second in each FixedUpdate()
    // processes movement actions from the glfwPollEvents()
    // called before it.
    void processMovement(GLFWwindow* window) {

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
    void processLookingDirection(GLFWwindow* window) {

      double mousePosX, mousePosY;
      glfwGetCursorPos(window, &mousePosX, &mousePosY);
      int width, height;
      glfwGetWindowSize(window, &width, &height);
      mousePosY = height - mousePosY;
      int playerPosX = width / 2;
      int playerPosY = height / 2;

      int lookDirectionX = mousePosX - playerPosX;
      int lookDirectionY = mousePosY - playerPosY;

      constexpr double NDIR = glm::radians(90.0f);

      double angle = atan2(lookDirectionY, lookDirectionX) - NDIR;

      rotation_ = angle;

    }


    // called 60 times a second in each FixedUpdate() to check mouse button
    // input and the cooldown on the shooting player. 
    // basically, this recieves mouse input and makes the player shoot
    // accordingly.
    void processShooting(GLFWwindow* window) {

      if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        if (glfwGetTime() - lastShot_ > shootCD_) {
          shoot();
          lastShot_ = glfwGetTime();
        }

      }

    }


    // called every frame in Render() to draw the player
    void draw() {


      model_.select();

      glm::mat4 modelMatrix = glm::mat4(1.0f);
      modelMatrix = glm::translate(modelMatrix, pos_);
      modelMatrix = glm::rotate(
        modelMatrix, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
      currentShader_.setMat4fv("model", modelMatrix);

      currentShader_.use();
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }



    // called in ProcessShooting() when the player is able to shoot
    void shoot() {

      projectiles_.push_back(Projectile(*this, model_, rotation_));
      //std::cout << projectiles_.size() << std::endl;

    }



    // called every frame in Render()
    void drawProjectiles() {

      if (projectiles_.size()) {

        for (Projectile& p : projectiles_) {

          p.draw(currentShader_);

        }
      }
    }


    // called 60 times a second in each FixedUpdate() to
    // update the positions of the player's projectiles and cull
    // ones that have expired
    void updateProjectiles() {

      if (projectiles_.size()) {

        for (int i = 0; i < projectiles_.size(); i++) {

          projectiles_[i].move();

          if (projectiles_[i].isDead_) {

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

      bool            isDead_   =  false; // when this is true it is deleted
      int             age_       =  0; // measured in FixedUpdate()s


    public:


      Projectile(Player& player, models::Quad& model, double angle)
        : model_(model) {

        pos_ = player.getPos();
        rotation_ = player.rotation_;

        constexpr float NDIR = glm::radians(90.0f);

        direct_.x = cos(rotation_ + NDIR) / 5.0f;
        direct_.y = sin(rotation_ + NDIR) / 5.0f;

      }




      // called for every projectile for a player in 
      // player::Player.DrawProjectiles() which is called every frame
      // in Render()
      void draw(shaderObj::Shader& shader) {


        // since model_ is a std::reference_wrapper, you have to use
        // .get() to "get" to to access the object it is wrapping
        model_.get().select();

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, pos_);
        modelMatrix = glm::rotate(
          modelMatrix, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4fv("model", modelMatrix);

        shader.use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      }


      // used to update the postion of a projectile
      void move() {

        if (age_ < lifetime_) {
          pos_ += direct_;
        }
        else {
          isDead_ = true;
        }

      }



    };



  };



}

#endif