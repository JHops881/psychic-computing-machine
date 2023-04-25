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
#include <cmath>

// library headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

// project headers
#include "../include/stb_image.h" // not mine

#include "../include/shader_obj.h"
#include "../include/models.h"
#include "../include/player.h"
#include "../include/my_glfw_callbacks.h"
#include "../include/terrain_graphics_handling.h"

inline unsigned int ToMillis(double time);
void Update(GLFWwindow* window, player::Player& player,
  double time_between_updates, double total_time, double last_frame_update_time);
void FixedUpdate(GLFWwindow* window, player::Player& player);
void Render(GLFWwindow* window, player::Player& player,
  shader_obj::Shader& shader, models::Wall& wall);


int main() {

  unsigned int screen_width{};
  unsigned int screen_height{};
  const char* kWindowTitle = "Game";

  std::cout << "Please select a resolution: \n\n";
  std::cout << "'a' for 1920x1080.\n";
  std::cout << "'b' for 1366x768.\n";

  bool gotten_valid_input = false;

  while (!gotten_valid_input)
  {
    std::string input;
    std::cin >> input;
    
    
    if (input == "a") {
      screen_width = 1920;
      screen_height = 1080;
      gotten_valid_input = true;
    }
    else if (input == "b") {
      screen_width = 1366;
      screen_height = 768;
      gotten_valid_input = true;
    }
    else {
      std::cout << "??? try again: " << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }


  
  // make the glfw window, init glfw, init glad, error handling, start openGL
  //--------------------------------------------------------------------------++
                                                                              //
  glfwInit();                                                                 //
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                              //
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);                              //
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);              //
                                                                              //
                                                                              //
  GLFWwindow* window = glfwCreateWindow(screen_width, screen_height,          //
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
  glViewport(0, 0, screen_width, screen_height);                              //
  glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);            //
  glfwSetMouseButtonCallback(window, MouseButtonCallback);                    //
                                                                              //
  //--------------------------------------------------------------------------++
   
  // create player
  player::Player player = player::Player();

  // create the shader program
  shader_obj::Shader shader(
    ".\\res\\shaders\\vertex_shader.vert",
    ".\\res\\shaders\\fragment_shader.frag");

  // select the shader program
  shader.use();

  // load in the wall model
  models::Wall wall = models::Wall();


  // defining the projection matrix
  glm::mat4 projection_mat = glm::mat4(1.0f);

  float aspect_ratio = (float)screen_width / (float)screen_height;

  projection_mat = 
    glm::perspective(glm::radians(80.0f), aspect_ratio , 0.1f, 100.0f);

  shader.SetMat4fv("projection", projection_mat);

  models::TurnOnOpenGLDepthTesting();
  models::TurnOnClockwiseOpenGLFaceCulling();
  models::TurnOnOpenGLWireframeMode();

  //------------------------------GAME-LOOP-----------------------------------++

  double last_loop_time;
  double total_time = 0.0;
  constexpr double time_between_updates = (1.0 / 60.0);
  double last_frame_update_time = 0.0;
  double last_fixed_update_time = 0.0;
  double start_time = 0.0;
  double end_time = 0.0;
  

  while (!glfwWindowShouldClose(window)) {

    last_loop_time = end_time - start_time;
    start_time = glfwGetTime();
    total_time += last_loop_time;

    while (total_time >= time_between_updates) {

      // update
      FixedUpdate(window, player);
      last_fixed_update_time = glfwGetTime();
      total_time -= time_between_updates;
    }

    // render
    //Update(window, player, time_between_updates, total_time, last_frame_update_time);
    last_frame_update_time = glfwGetTime() - last_fixed_update_time;
    Render(window, player, shader, wall);

   
    end_time = glfwGetTime();
  } 
  //--------------------------------------------------------------------------++
 
  // kill glfw and free the resources
  glfwTerminate();
  return 0;
}





// called every frame
void Update(GLFWwindow* window, player::Player& player,
  double time_between_updates, double total_time, 
  double last_frame_update_time)
{
  float interval_p =static_cast<float>(
    (total_time - last_frame_update_time) / time_between_updates);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.0f, 0.1f, 0.0f) * interval_p);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(-0.1f, 0.0f, 0.0f) * interval_p);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.0f, -0.1f, 0.0f) * interval_p);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.1f, 0.0f, 0.0f) * interval_p);
  }
}





// called ?? times a seccond at a fixed rate
void FixedUpdate(GLFWwindow* window, player::Player& player) {
  // grab key input from GLFW
  glfwPollEvents();

  // make key input do stuff
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
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    player.MoveAmount(glm::vec3(0.1f, 0.0f, 0.0f));
  }
  double mouse_posx, mouse_posy;
  glfwGetCursorPos(window, &mouse_posx, &mouse_posy);
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  mouse_posy = height - mouse_posy;
  int player_posx = width/2;
  int player_posy = height/2;

  int look_directionx = mouse_posx - player_posx;
  int look_directiony = mouse_posy - player_posy;

  constexpr double NDIR = glm::radians(90.0f);

  double angle = atan2(look_directiony, look_directionx) - NDIR;

  player.SetRotation(angle);
  
}






void Render(GLFWwindow* window, player::Player& player,
  shader_obj::Shader& shader, models::Wall& wall)
{  
  // select the shader             
  shader.use();       
         
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);                           
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // defining the view matrix per                                       
  // frame because it changes with movement                       
  glm::mat4 view_mat = glm::mat4(1.0f);                                 
  view_mat =                                                             
    glm::translate(
      view_mat, (glm::vec3(0.0f, 0.0f, -10.0f) -= player.GetPos())       
    );                                                                 

  shader.SetMat4fv("view", view_mat); 
  
  player.Draw(shader);
                                                            
  tgh::DrawVisibleWalls(shader, wall);                                                                        //

  glfwSwapBuffers(window);
}