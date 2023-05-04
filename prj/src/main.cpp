// thisIsAVariable
// thisIsAFunction
// ThisIsAClass
// ThisIsAnEnum
// this_is_a_member_variable_
// THIS_IS_AN_ENUM_MEMBER
// THIS_IS_A_MACRO
// thisIsANameSpace




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

#include <shader_obj.h>
#include <models.h>
#include <player.h>
#include <my_glfw_callbacks.h>


void fixedUpdate(GLFWwindow* window, Player& player);
void render(GLFWwindow* window, Player& player);
void setProjMatrixFor(ShaderProgram& shader, float scrnW, float scrnH);


int main() {

  unsigned int screenWidth{};
  unsigned int screenHeight{};
  const char* windowTitle = "Game";

  std::cout << "Please select a resolution: \n\n";
  std::cout << "'a' for 1920x1080.\n";
  std::cout << "'b' for 1366x768.\n";
  
  bool gottenValidInput = false;

  while (!gottenValidInput)
  {
    std::string input;
    std::cin >> input;
    
    
    if (input == "a") {
      screenWidth = 1920;
      screenHeight = 1080;
      gottenValidInput = true;
    }
    else if (input == "b") {
      screenWidth = 1366;
      screenHeight = 768;
      gottenValidInput = true;
    }
    else {
      std::cout << "??? try again: " << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }


  
  // make the glfw window, init glfw, init glad, error handling, start openGL
  //--------------------------------------------------------------------------++
                                                                            
  glfwInit(); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                                                                             
  
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, windowTitle, glfwGetPrimaryMonitor(), NULL);
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
                                                                  
  glViewport(0, 0, screenWidth, screenHeight);                    
  glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);        
                                                                  
  //--------------------------------------------------------------



  // create the shader program
  ShaderProgram generalShader(".\\res\\shaders\\general.vert", ".\\res\\shaders\\general.frag");




  Player playerOne = Player(generalShader);





  // defining the projection matrix
  setProjMatrixFor(generalShader, screenWidth, screenHeight);






  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode on




  //------------------------------GAME-LOOP-----------------------------------++

  double lastLoopTime;
  double totalTime = 0.0;
  constexpr double timeBetweenUpdates = (1.0 / 60.0);
  double startTime = 0.0;
  double endTime = 0.0;
  

  while (!glfwWindowShouldClose(window)) {

    lastLoopTime = endTime - startTime;
    startTime = glfwGetTime();
    totalTime += lastLoopTime;

    while (totalTime >= timeBetweenUpdates) {

      // fixedUpdate
      fixedUpdate(window, playerOne);
      totalTime -= timeBetweenUpdates;
    }

    render(window, playerOne);
   
    endTime = glfwGetTime();
  } 
  //--------------------------------------------------------------------------++
 
  // kill glfw and free the resources
  glfwTerminate();
  return 0;
}











// called 60 times a seccond to update the state of the game.
void fixedUpdate(GLFWwindow* window, Player& player) {

  // grab key input from GLFW
  glfwPollEvents();

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  player.update(window);

}



// called every frame.
void render(GLFWwindow* window, Player&player) {
        
         
  // background color grey
  glClearColor(0.09f, 0.06f, 0.09f, 1.0f);                           
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // defining the view matrix per                                       
  // frame because it changes with movement                       
  glm::mat4 viewMat = glm::mat4(1.0f);                                 
  viewMat = glm::translate(viewMat, (glm::vec3(0.0f, 0.0f, -10.0f) -= player.getPos()));                                                                 
  player.getShader().setMat4fv("view", viewMat);
  

  // map::Draw();

  player.draw();

  glfwSwapBuffers(window);
}





void setProjMatrixFor(ShaderProgram& shader, float scrnW, float scrnH) {

  glm::mat4 projectionMatrix = glm::mat4(1.0f);
  float aspectRatio = scrnW / scrnH;
  projectionMatrix = glm::perspective(glm::radians(80.0f), aspectRatio, 0.1f, 100.0f);

  shader.setMat4fv("projection", projectionMatrix);
}