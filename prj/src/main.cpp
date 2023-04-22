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
#include "stb_image.h" // not mine

#include "shader.h"
#include "models.h"
#include "player.h"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window, plr::Player& player);
bool glfwSetWindowCenter(GLFWwindow* window);

const unsigned int kScreenWidth = 800;
const unsigned int kScreenHeight = 600;
const char* kWindowTitle = "Game";

int main() {
  
  // make the glfw window, init glfw, init glad, error handling, start openGL
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(kScreenWidth, kScreenHeight, kWindowTitle, NULL, NULL);
  if (window == NULL) {
    std::cout << "GLFW FAILED TO INIT" << std::endl; // still making it
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "FAILED TO LOAD GLAD" << std::endl; // still making it
    return -1;
  }
 
  glfwSetWindowCenter(window);
  glViewport(0, 0, kScreenWidth, kScreenHeight); 
  glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback); // Done!

  // create player
  plr::Player player = plr::Player();

  // create the shader program
  Shader shader(".\\res\\shaders\\vertex_shader.vert", ".\\res\\shaders\\fragment_shader.frag");

  // select the shader program
  shader.use();

  // load in the cube model
  mod::Cube cube = mod::Cube();

  // list of all the positions we want to make a cube
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
  
  

  // defining the projection matrix
  glm::mat4 projection_mat = glm::mat4(1.0f);
  projection_mat = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  // setting the uniform matrixes to be corresponding to the ones above
  shader.SetMat4fv("projection", projection_mat);

  // enable depth testing with the z-buffer with openGL so we dont get weird stuff
  glEnable(GL_DEPTH_TEST);

  // enable face culling. OpenGL will cull all faces of obejects that are not
  // front facing. saves 50% performance. 
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  // wirecframe mode!
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // game loop
  while (!glfwWindowShouldClose(window)) {

    // make key input do stuff
    ProcessInput(window, player);

    // select the shader
    shader.use();

   
    // flush the screen and the buffers
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 

    // defining the view matrix per frame because it changes with movement
    glm::mat4 view_mat = glm::mat4(1.0f);
    view_mat = glm::translate(view_mat, (glm::vec3(0.0f, 0.0f, -6.0f) -= player.GetPos()));
    shader.SetMat4fv("view", view_mat);

    // player
    player.Draw(shader);

    // draw all the cubes
    cube.Select();
    for (int i = 0; i < 10; i++) {
        glm::mat4 model_mat = glm::mat4(1.0f);
        model_mat = glm::translate(model_mat, cubes_pos[i]);
        shader.SetMat4fv("model", model_mat);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    
    // swap frame buffer
    glfwSwapBuffers(window);
    // grab key input from GLFW
    glfwPollEvents();
    
  }

  // kill glfw and free the resources
  glfwTerminate();
  return 0;
}

// this is a callback for glfw to resize the viewport every time the window is
// resized
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// defines the way we process key input e.i. what we do when certain keys
// are pressed.
void ProcessInput(GLFWwindow* window, plr::Player& player) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.0f, 0.05f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(-0.05f, 0.0f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.0f, -0.05f, 0.0f));
  }if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.05f, 0.0f, 0.0f));
  }

}

// https://github.com/glfw/glfw/issues/310 | sagaceilo commented on Jun 21, 2014
bool glfwSetWindowCenter(GLFWwindow* window) {
  if (!window)
    return false;

  int sx = 0, sy = 0;
  int px = 0, py = 0;
  int mx = 0, my = 0;
  int monitor_count = 0;
  int best_area = 0;
  int final_x = 0, final_y = 0;

  glfwGetWindowSize(window, &sx, &sy);
  glfwGetWindowPos(window, &px, &py);

  // Iterate throug all monitors
  GLFWmonitor** m = glfwGetMonitors(&monitor_count);
  if (!m)
    return false;

  for (int j = 0; j < monitor_count; ++j)
  {

    glfwGetMonitorPos(m[j], &mx, &my);
    const GLFWvidmode* mode = glfwGetVideoMode(m[j]);
    if (!mode)
      continue;

    // Get intersection of two rectangles - screen and window
    int minX = std::max(mx, px);
    int minY = std::max(my, py);

    int maxX = std::min(mx + mode->width, px + sx);
    int maxY = std::min(my + mode->height, py + sy);

    // Calculate area of the intersection
    int area = std::max(maxX - minX, 0) * std::max(maxY - minY, 0);

    // If its bigger than actual (window covers more space on this monitor)
    if (area > best_area)
    {
      // Calculate proper position in this monitor
      final_x = mx + (mode->width - sx) / 2;
      final_y = my + (mode->height - sy) / 2;

      best_area = area;
    }

  }

  // We found something
  if (best_area)
    glfwSetWindowPos(window, final_x, final_y);

  // Something is wrong - current window has NOT any intersection with any monitors. Move it to the default one.
  else
  {
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    if (primary)
    {
      const GLFWvidmode* desktop = glfwGetVideoMode(primary);

      if (desktop)
        glfwSetWindowPos(window, (desktop->width - sx) / 2, (desktop->height - sy) / 2);
      else
        return false;
    }
    else
      return false;
  }

  return true;
}