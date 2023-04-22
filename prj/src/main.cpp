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

const unsigned int kScreenWidth = 1920;
const unsigned int kScreenHeight = 1080;
const char* kWindowTitle = "Game";

int main() {
  
  // make the glfw window, init glfw, init glad, error handling, start openGL
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(kScreenWidth, kScreenHeight, kWindowTitle, glfwGetPrimaryMonitor(), NULL);
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
  projection_mat = glm::perspective(glm::radians(80.0f), (float)kScreenWidth /(float)kScreenHeight, 0.1f, 100.0f);

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

  
  double last_loop_time;
  double total_time = 0;
  const double time_between_updates = (1.0 / 60.0);
  double start_time = 0;
  double end_time = 0;

  while (!glfwWindowShouldClose(window)) {

    last_loop_time = end_time - start_time;
    start_time = glfwGetTime();
    total_time += last_loop_time;

    while (total_time >= time_between_updates) {
      // update
      // grab key input from GLFW
      glfwPollEvents();

      // make key input do stuff
      ProcessInput(window, player);

      total_time -= time_between_updates;
    }

    //draw
  
    // select the shader
    shader.use();


    // flush the screen and the buffers
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // defining the view matrix per frame because it changes with movement
    glm::mat4 view_mat = glm::mat4(1.0f);
    view_mat = glm::translate(view_mat, (glm::vec3(0.0f, 0.0f, -7.0f) -= player.GetPos()));
    shader.SetMat4fv("view", view_mat);

    // player
    player.Draw(shader);

    // draw all the cubes
    cube.Select();
    for (glm::vec3& pos : cubes_pos) {
      glm::mat4 model_mat = glm::mat4(1.0f);
      model_mat = glm::translate(model_mat, pos);
      shader.SetMat4fv("model", model_mat);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    // swap frame buffer
    glfwSwapBuffers(window);
    
    end_time = glfwGetTime();    
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
    player.MoveAmount(glm::vec3(0.0f, 0.1f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(-0.1f, 0.0f, 0.0f));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.0f, -0.1f, 0.0f));
  }if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.1f, 0.0f, 0.0f));
  }

}