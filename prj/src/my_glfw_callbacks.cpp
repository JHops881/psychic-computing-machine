#include <glad/glad.h>
#include <GLFW/glfw3.h>

//self
#include "../include/my_glfw_callbacks.h"


// this is a callback for glfw to resize the viewport every time the window is
// resized
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {

}