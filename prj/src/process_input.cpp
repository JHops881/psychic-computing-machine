// C headers

// C++ headers

// std headers
#include <iostream>
#include <cmath>

// library headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>

// project headers

//#include "../include/shader.h"
//#include "../include/models.h"
#include "../include/player.h"

// self
#include "../include/process_input.h"



// defines the way we process key input e.i. what we do when certain keys
// are pressed.
void ProcessInput(GLFWwindow* window, plr::Player& player) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.0f, 0.1f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(-0.1f, 0.0f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.0f, -0.1f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.1f, 0.0f, 0.0f));
  }
  //if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
  //  double xpos;
  //  double ypos;
  //  glfwGetCursorPos(window, &xpos, &ypos);
  //  std::cout << "RAW " << xpos << " " << ypos << std::endl;
  //  // convert to a normal y positive is up
  //  ypos = kScreenHeight - ypos;
  //  // make them (0,0) to (1,1)
  //  xpos /= kScreenWidth;
  //  ypos /= kScreenHeight;
  //  // make it (-0.5,-0.5) to (0.5,0.5)
  //  xpos -= 0.5;
  //  ypos -= 0.5;
  //  // ndc is (-1,-1) to (1,1)
  //  xpos *= 2;
  //  ypos *= 2;
  //  std::cout << "NDC " << xpos << " " << ypos << std::endl;

  //  double angle = glm::degrees(atan(ypos/xpos));
  //  if (ypos > 0) {
  //    angle = abs(angle);
  //  }
  //  else {
  //    angle = 360.0 - abs(angle);
  //  }

  //  std::cout << "angle: " << angle << std::endl;
  //  plr::Projectile pro = plr::Projectile(player, angle);

  //  std::cout << "position: " << pro.pos_.x << " " << pro.pos_.y << std::endl;
  //  std::cout << "end pos: " << pro.endpos_.x << " " << pro.endpos_.y << std::endl;
  //  std::cout << "kill me now." << std::endl;

  //}

}