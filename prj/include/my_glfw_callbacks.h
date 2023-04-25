#ifndef MY_GLFW_CALLBACKS_H_
#define MY_GLFW_CALLBACKS_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void MouseButtonCallback(GLFWwindow* window, int button, int actions, int mods);


#endif

