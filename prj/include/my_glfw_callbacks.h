#ifndef PRJ_INCLUDE_MY_GLFW_CALLBACKS_H
#define PRJ_INCLUDE_MY_GLFW_CALLBACKS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void mouseButtonCallback(GLFWwindow* window, int button, int actions, int mods);


#endif

