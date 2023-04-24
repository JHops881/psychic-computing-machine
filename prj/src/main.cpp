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
#include "../include/stb_image.h" // not mine

#include "../include/shader.h"
#include "../include/models.h"
#include "../include/player.h"
#include "../include/process_input.h"
#include "../include/my_glfw_callbacks.h"

inline unsigned int ToMillis(double time);



int main() {

  const unsigned int kScreenWidth = 1920;
  const unsigned int kScreenHeight = 1080;
  const char* kWindowTitle = "Game";

  
  // make the glfw window, init glfw, init glad, error handling, start openGL
  //--------------------------------------------------------------------------++
                                                                              //
  glfwInit();                                                                 //
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                              //
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);                              //
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);              //
                                                                              //
                                                                              //
  GLFWwindow* window = glfwCreateWindow(kScreenWidth, kScreenHeight,          //
    kWindowTitle, glfwGetPrimaryMonitor(), NULL);                             //
                                                                              //
  if (window == NULL) {                                                       //
    std::cout << "GLFW FAILED TO INIT" << std::endl;                          //
    glfwTerminate();                                                          //
    return -1;                                                                //
  }                                                                           //
  glfwMakeContextCurrent(window);                                             //
                                                                              //
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {                  //
    std::cout << "FAILED TO LOAD GLAD" << std::endl;                          //
    return -1;                                                                //
  }                                                                           //
                                                                              //
  glViewport(0, 0, kScreenWidth, kScreenHeight);                              //
  glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);            //
                                                                              //
  //--------------------------------------------------------------------------++
   
  // create player
  plr::Player player = plr::Player();

  // create the shader program
  Shader shader(
    ".\\res\\shaders\\vertex_shader.vert",
    ".\\res\\shaders\\fragment_shader.frag");

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
      glm::vec3(4.0f, 4.0f, 0.0f),
      glm::vec3(-2.0f, 4.0f, 0.0f),
      glm::vec3(-3.0f, 4.0f, 0.0f),
      glm::vec3(-3.0f, 3.0f, 0.0f)
  };

  
  

  // defining the projection matrix
  glm::mat4 projection_mat = glm::mat4(1.0f);

  float aspect_ratio = (float)kScreenWidth / (float)kScreenHeight;

  projection_mat = 
    glm::perspective(glm::radians(80.0f), aspect_ratio , 0.1f, 100.0f);

  shader.SetMat4fv("projection", projection_mat);

  // enable depth testing with the z-buffer
  // with openGL so we dont get weird stuff
  glEnable(GL_DEPTH_TEST);

  // enable face culling. OpenGL will cull all faces of 
  // objects that are not front facing. saves 50% performance. 
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  // wirecframe mode!
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // game loop
  //--------------------------------------------------------------------------++
                                                                              //
  unsigned int last_loop_time;                                                //
  unsigned int total_time = 0;                                                //
  const unsigned int time_between_updates = ToMillis((1.0 / 60.0));           //
  unsigned int start_time = 0;                                                //
  unsigned int end_time = 0;                                                  //
                                                                              //
  while (!glfwWindowShouldClose(window)) {                                    //
                                                                              //
    last_loop_time = end_time - start_time;                                   //
    start_time = ToMillis(glfwGetTime());                                     //
    total_time += last_loop_time;                                             //
                                                                              //
    while (total_time >= time_between_updates) {                              //
      // update                                                               //
      // grab key input from GLFW                                             //
      glfwPollEvents();                                                       //
                                                                              //
      // make key input do stuff                                              //
      ProcessInput(window, player);                                           //
                                                                              //
      total_time -= time_between_updates;                                     //
    }                                                                         //
                                                                              //
    //draw                                                                    //
                                                                              //
    // select the shader                                                      //
    shader.use();                                                             //
                                                                              //
                                                                              //
    // flush the screen and the buffers                                       //
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);                                     //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                       //
                                                                              //
                                                                              //
                                                                              //
    // defining the view matrix per                                           //
    // frame because it changes with movement                                 //
    glm::mat4 view_mat = glm::mat4(1.0f);                                     //
    view_mat =                                                                //
      glm::translate(                                                         //
        view_mat, (glm::vec3(0.0f, 0.0f, -10.0f) -= player.GetPos())          //
        );                                                                    //
                                                                              //
    shader.SetMat4fv("view", view_mat);                                       //
                                                                              //
    // player                                                                 //
    player.Draw(shader);                                                      //
                                                                              //
    // draw all the cubes                                                     //
    cube.Select();                                                            //
    for (glm::vec3& pos : cubes_pos) {                                        //
      glm::mat4 model_mat = glm::mat4(1.0f);                                  //
                                                                              //
      model_mat = glm::translate(model_mat, pos);                             //
      shader.SetMat4fv("model", model_mat);                                   //
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);                   //
    }                                                                         //
                                                                              //
    // swap frame buffer                                                      //
    glfwSwapBuffers(window);                                                  //
                                                                              //
    end_time = ToMillis(glfwGetTime());                                       //
  }                                                                           //
  //--------------------------------------------------------------------------++
  
  // kill glfw and free the resources
  glfwTerminate();
  return 0;
}

inline unsigned int ToMillis(double time) {
  unsigned int milliseconds = static_cast<unsigned int>(time * 1000);
  return milliseconds;
}