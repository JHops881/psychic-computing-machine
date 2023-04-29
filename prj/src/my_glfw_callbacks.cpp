#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


//self
#include <my_glfw_callbacks.h>


// this is a callback for glfw to resize the viewport every time the window is
// resized
void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}



void mouseButtonCallback(GLFWwindow* window, int button, int actions, int mods) {
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
    double xPos;
    double yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
  }
}



void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
  
}
