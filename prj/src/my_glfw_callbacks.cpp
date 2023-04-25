#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


//self
#include "../include/my_glfw_callbacks.h"
#


// this is a callback for glfw to resize the viewport every time the window is
// resized
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
void MouseButtonCallback(GLFWwindow* window, int button, int actions, int mods) {
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
  }
}
void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
  
}
