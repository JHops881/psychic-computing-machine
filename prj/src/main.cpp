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
#include <stb_image.h> // not mine

#include <shader_obj.h>
#include <models.h>
#include <player.h>
#include <my_glfw_callbacks.h>
#include <Wall.h>
#include <Tile.h>
#include <GameObject.h>


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

  Quad2D* g_QUAD2D = new Quad2D();
  Cuboid3D* g_CUBOID3D = new Cuboid3D();

  GameObject::configureModels(g_CUBOID3D, g_QUAD2D);



  // create the shader program
  ShaderProgram generalShader(".\\res\\shaders\\general.vert", ".\\res\\shaders\\general.frag");
  generalShader.updateMatrix(PROJECTION, ((float)screenWidth / (float)screenHeight), 80.0f, 0.1f, 100.0f);



  Player playerOne = Player(generalShader);

  Wall wallOne = Wall(glm::vec3(1.0f, 1.0f, 0.0f), generalShader);
  Wall wallTwo = Wall(glm::vec3(4.0f, 6.0f, 0.0f), generalShader);

  Tile tileOne = Tile(glm::vec3(1.0f, 1.0f, 0.0f), generalShader);
  Tile tileTwo = Tile(glm::vec3(2.0f, 2.0f, 0.0f), generalShader);
  Tile tileThree = Tile(glm::vec3(3.0f, 3.0f, 0.0f), generalShader);
  Tile tileFour = Tile(glm::vec3(4.0f, 4.0f, 0.0f), generalShader);
  Tile tileFive = Tile(glm::vec3(5.0f, 5.0f, 0.0f), generalShader);
  Tile tileSix = Tile(glm::vec3(6.0f, 6.0f, 0.0f), generalShader);
  Tile tileSeven = Tile(glm::vec3(7.0f, 7.0f, 0.0f), generalShader);


  






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
      {
        // grab key input from GLFW
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
          glfwSetWindowShouldClose(window, true);
        }

        playerOne.update(window);
      }
      totalTime -= timeBetweenUpdates;
    }

    //render
    {
      // background color grey
      glClearColor(0.09f, 0.06f, 0.09f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // defining the view matrix per                                       
      // frame because it changes with movement                       
      generalShader.updateMatrix(VIEW, glm::vec3(0.0f, 0.0f, -10.0f), playerOne.getPos());


      // map::Draw();

      playerOne.draw();
      wallOne.draw();
      wallTwo.draw();
      tileOne.draw();
      tileTwo.draw();
      tileThree.draw();
      tileFour.draw();
      tileFive.draw();
      tileSix.draw();
      tileSeven.draw();


      glfwSwapBuffers(window);
    }
   
    endTime = glfwGetTime();
  } 
  //--------------------------------------------------------------------------++
 
  // kill glfw and free the resources
  delete g_CUBOID3D;
  delete g_QUAD2D;
  glfwTerminate();
  return 0;
}


