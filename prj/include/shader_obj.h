#ifndef PRJ_INCLUDE_SHADER_OBJ_H
#define PRJ_INCLUDE_SHADER_OBJ_H

#include <glad/glad.h> 
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>

enum MatrixType {
  MODEL, VIEW, PROJECTION
};




class ShaderProgram {

public:

  unsigned int id_{};

private:

  // given: the shader as a c string, type of shader desired, 
  // returns: 
  //! 
  //! 
  //! 
  //! @return unsigned int the id corresponding to an OpenGL shader object of that type compiled from the c string
  //! 
  unsigned int compileShader(const char* shaderSource, GLenum shaderType) {

    unsigned int shader;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    // error handling
    {
      int success;
      char infoLog[512];
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:" << shaderType << ":COMPILATION_FAILED\n" << infoLog << "\n";
      }
    }
    return shader;
  }

  // given: file path to vertex shader file, file path to fragment shader file
  // returns: the id corresponding to and OpenGL shader PROGRAM compiled from those files.
  unsigned int createProgram(const char* vertexSource, const char* fragmentSource) {
     unsigned int program;
    program = glCreateProgram();

    unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);


    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    // error handling
    {
      int success;
      char infoLog[512];
      glGetProgramiv(program, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED" << infoLog << "\n";
      }
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
  }

public:


  ShaderProgram(const char* vertex_path, const char* fragment_path) {

      // this will store the corresponding shaders code as a string
    std::string vertexCode;
    std::string fragmentCode;

    std::stringstream vertexBuffer; // need these to read in file
    std::stringstream fragmentBuffer;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    std::cout << "Vertex shader path: " << vertex_path << std::endl;
    std::cout << "Fragment shader path: " << fragment_path << std::endl;

      // error handling
    vertexShaderFile.open(vertex_path);
    if (vertexShaderFile.fail()) {
      std::cout << "ERROR : FAILED TO OPEN VERTEX SHADER!\n";
    }
    fragmentShaderFile.open(fragment_path);
    if (fragmentShaderFile.fail()) {
      std::cout << "ERROR : FAILED TO OPEN FRAGMENT SHADER\n";
    }

    // read in the contents, convert them to strings, close the files.
    vertexBuffer << vertexShaderFile.rdbuf();
    fragmentBuffer << fragmentShaderFile.rdbuf();
    vertexCode = vertexBuffer.str();
    fragmentCode = fragmentBuffer.str();
    vertexShaderFile.close();
    fragmentShaderFile.close();
    // convert them to c style strings for OpenGl
    const char* vertexCString = vertexCode.c_str();
    const char* fragmentCString = fragmentCode.c_str();

    id_ = createProgram(vertexCString, fragmentCString);

  }

  ShaderProgram() {}

  inline void select() {
    glUseProgram(id_);
  }


  // note that these uniform setting functions will deselect the
  // shader in use. always follow unifrom setting function with a 
  // use() call. 

  void setBool(const std::string& name, bool value) const {
    glUseProgram(id_);
    glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
    glUseProgram(0);
  }
  void setInt(const std::string& name, int value) const {
    glUseProgram(id_);
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
    glUseProgram(0);
  }
  void setFloat(const std::string& name, float value) const {
    glUseProgram(id_);
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
    glUseProgram(0);
  }
  void setMat4fv(const std::string& name, glm::mat4& mat4) const {
    glUseProgram(id_);
    unsigned int location = glGetUniformLocation(id_, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
    glUseProgram(0);
  }


  // for projection 
  void updateMatrix(MatrixType type, float aspectRatio, float fovDegrees, float near, float far) {
    if (type == PROJECTION) {

      glm::mat4 projectionMatrix = glm::mat4(1.0f);
      projectionMatrix = glm::perspective(glm::radians(fovDegrees), aspectRatio, near, far);

      setMat4fv("projection", projectionMatrix);

    }
    else {
      std::cout << "ERROR::SHADER::INCORRECT PARAMETERS FOR MATRIX TYPE PROJECTION" << std::endl;
    }

  }
  // for model with NO rotation
  void updateMatrix(MatrixType type, glm::vec3& worldPosition) {
  
    if (type == MODEL) {

      glm::mat4 modelMatrix = glm::mat4(1.0f);
      modelMatrix = glm::translate(modelMatrix, worldPosition);
      setMat4fv("model", modelMatrix);

    }
    else {
      std::cout << "ERROR::SHADER::INCORRECT PARAMETERS FOR MATRIX TYPE MODEL" << std::endl;
    }
  
  }
  // for model WITH rotation
  void updateMatrix(MatrixType type, glm::vec3& worldPosition, float rotationRadians) {

    if (type == MODEL) {

      glm::mat4 modelMatrix = glm::mat4(1.0f);
      modelMatrix = glm::translate(modelMatrix, worldPosition);
      modelMatrix = glm::rotate(modelMatrix, rotationRadians, glm::vec3(0.0f, 0.0f, 1.0f));
      setMat4fv("model", modelMatrix);

    }
    else {
      std::cout << "ERROR::SHADER::INCORRECT PARAMETERS FOR MATRIX TYPE MODEL" << std::endl;
    }

  }
  // for view
  void updateMatrix(MatrixType type, glm::vec3 cameraOrigin, glm::vec3& offset) {

    if (type == VIEW) {

      glm::mat4 viewMatrix = glm::mat4(1.0f);
      viewMatrix = glm::translate(viewMatrix, (cameraOrigin -= offset));
      setMat4fv("view", viewMatrix);

    }
    else {
      std::cout << "ERROR::SHADER::INCORRECT PARAMETERS FOR MATRIX TYPE VIEW" << std::endl;
    }


  }




  



  




};


#endif