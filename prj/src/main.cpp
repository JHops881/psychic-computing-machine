// KThisIsAConstant
// this_is_a_variable
// ThisIsAFunction
// ThisIsAClass
// ThisIsAnEnum
// this_is_a_member_variable_
// kThisIsAnEnumMember




// C headers

// C++ headers

// std headers
#include <iostream>
#include <string>

// library headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

// project headers
#include "shader.h"
#include "stb_image.h"
#include "models.h"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

const unsigned int kScreenWidth = 800;
const unsigned int kScreenHeight = 600;
const char* kWindowTitle = "Game";

int main() {
  
  // make the glfw window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(kScreenWidth, kScreenHeight, kWindowTitle, NULL, NULL);
  if (window == NULL) {
    std::cout << "GLFW FAILED TO INIT" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "FAILED TO LOAD GLAD" << std::endl;
    return -1;
  }
 
  glViewport(0, 0, kScreenWidth, kScreenHeight);
  glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

  

  Shader shader(".\\res\\shaders\\vertex_shader.vert", ".\\res\\shaders\\fragment_shader.frag");
  shader.use();

  mod::Quad quad = mod::Quad();
  mod::Cube cube = mod::Cube();

  glm::vec3 cubes_pos[] = {
      glm::vec3(3.0f, 0.0f, 0.0f),
      glm::vec3(3.0f, 1.0f, 0.0f),
      glm::vec3(3.0f, 3.0f, 0.0f),
      glm::vec3(3.0f, 4.0f, 0.0f),
      glm::vec3(2.0f, 4.0f, 0.0f),
      glm::vec3(1.0f, 4.0f, 0.0f),
      glm::vec3(0.0f, 4.0f, 0.0f),
      glm::vec3(-2.0f, 4.0f, 0.0f),
      glm::vec3(-3.0f, 4.0f, 0.0f),
      glm::vec3(-3.0f, 3.0f, 0.0f)
  };
    
  glm::mat4 view_mat = glm::mat4(1.0f);
  view_mat = glm::translate(view_mat, glm::vec3(0.0f, 0.0f, -6.0f));

  glm::mat4 projection_mat = glm::mat4(1.0f);
  projection_mat = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  shader.SetMat4fv("view", view_mat);
  shader.SetMat4fv("projection", projection_mat);

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {

    ProcessInput(window);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    quad.Select();
    {
        glm::mat4 model_mat = glm::mat4(1.0f);
        model_mat = glm::translate(model_mat, glm::vec3(0.0f, 0.0f,0.0f));
        shader.SetMat4fv("model", model_mat);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    cube.Select();
    for (int i = 0; i < 10; i++) {
        glm::mat4 model_mat = glm::mat4(1.0f);
        model_mat = glm::translate(model_mat, cubes_pos[i]);
        shader.SetMat4fv("model", model_mat);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    

    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }

  glfwTerminate();
  return 0;
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

}