#ifndef PROCESS_INPUT_H_
#define PROCESS_INPUT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/player.h"

void ProcessInput(GLFWwindow* window, player::Player& player);

#endif