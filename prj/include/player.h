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
#include <GameObject.h>










class Player : GameObject{

  Quad2D& model_ = *g_QUAD2D;



  double       shootCD_  =  0.35;   // time between shots
  double       lastShot_  =  0.0; // the of the last shot

 


public:

  Player(ShaderProgram& shaderProgram)
    : GameObject(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, shaderProgram) {

  }


  inline float getRotation() const {
    return rotation_;
  }


  inline glm::vec3& getPos() {

    return pos_;

  }

  inline ShaderProgram& getShader() {
    return shaderProgram_;
  }


  void update(GLFWwindow* window) {

    // movement
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

    // looking somewhere
    {
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

    // shooting
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

      if (glfwGetTime() - lastShot_ > shootCD_) {
        // shoot();
        std::cout << "pew" << std::endl;
        lastShot_ = glfwGetTime();
      }

    }



  }







  // called every frame in Render() to draw the player
  void draw() {

    model_.select();

    shaderProgram_.updateMatrix(MODEL, pos_, rotation_);

    shaderProgram_.select();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }



};





#endif