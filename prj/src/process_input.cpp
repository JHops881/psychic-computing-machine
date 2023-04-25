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
void ProcessInput(GLFWwindow* window, player::Player& player) {
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
  

}