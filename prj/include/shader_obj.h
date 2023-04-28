#ifndef SHADER_OBJ_H
#define SHADER_OBJ_H

#include <glad/glad.h> 
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>

namespace shader_obj{

  class Shader {

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
    unsigned int CompileShader(const char* shader_source, GLenum shader_type) {

      unsigned int shader;
      shader = glCreateShader(shader_type);
      glShaderSource(shader, 1, &shader_source, NULL);
      glCompileShader(shader);
      // error handling
      {
        int success;
        char info_log[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
          glGetShaderInfoLog(shader, 512, NULL, info_log);
          std::cout << "ERROR::SHADER:" << shader_type << ":COMPILATION_FAILED\n" << info_log << "\n";
        }
      }
      return shader;
    }

    // given: file path to vertex shader file, file path to fragment shader file
    // returns: the id corresponding to and OpenGL shader PROGRAM compiled from those files.
    unsigned int CreateProgram(const char* vertex_source, const char* fragment_source) {

      unsigned int program;
      program = glCreateProgram();

      unsigned int vertex_shader = CompileShader(vertex_source, GL_VERTEX_SHADER);
      unsigned int fragment_shader = CompileShader(fragment_source, GL_FRAGMENT_SHADER);


      glAttachShader(program, vertex_shader);
      glAttachShader(program, fragment_shader);
      glLinkProgram(program);
      // error handling
      {
        int success;
        char info_log[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
          glGetProgramInfoLog(program, 512, NULL, info_log);
          std::cout << "ERROR::PROGRAM::COMPILATION_FAILED" << info_log << "\n";
        }
      }
      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);

      return program;
    }

  public:


    Shader(const char* vertex_path, const char* fragment_path) {

      // this will store the corresponding shaders code as a string
      std::string vertex_code;
      std::string fragment_code;

      std::stringstream vertex_buffer; // need these to read in file
      std::stringstream fragment_buffer;

      std::ifstream vertex_shader_file;
      std::ifstream fragment_shader_file;

      std::cout << "Vertex shader path: " << vertex_path << std::endl;
      std::cout << "Fragment shader path: " << fragment_path << std::endl;

      // error handling
      vertex_shader_file.open(vertex_path);
      if (vertex_shader_file.fail()) {
        std::cout << "ERROR : FAILED TO OPEN VERTEX SHADER!\n";
      }
      fragment_shader_file.open(fragment_path);
      if (fragment_shader_file.fail()) {
        std::cout << "ERROR : FAILED TO OPEN FRAGMENT SHADER\n";
      }

      // read in the contents, convert them to strings, close the files.
      vertex_buffer << vertex_shader_file.rdbuf();
      fragment_buffer << fragment_shader_file.rdbuf();
      vertex_code = vertex_buffer.str();
      fragment_code = fragment_buffer.str();
      vertex_shader_file.close();
      fragment_shader_file.close();
      // convert them to c style strings for OpenGl
      const char* vertex_cstr = vertex_code.c_str();
      const char* fragment_cstr = fragment_code.c_str();

      id_ = CreateProgram(vertex_cstr, fragment_cstr);

    }

    Shader() {}

    inline void use() {
      glUseProgram(id_);
    }


    // note that these uniform setting functions will deselect the
    // shader in use. always follow unifrom setting function with a 
    // use() call. 

    void SetBool(const std::string& name, bool value) const {
      glUseProgram(id_);
      glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
      glUseProgram(0);
    }
    void SetInt(const std::string& name, int value) const {
      glUseProgram(id_);
      glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
      glUseProgram(0);
    }
    void SetFloat(const std::string& name, float value) const {
      glUseProgram(id_);
      glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
      glUseProgram(0);
    }
    void SetMat4fv(const std::string& name, glm::mat4& mat4) const {
      glUseProgram(id_);
      unsigned int loc = glGetUniformLocation(id_, name.c_str());
      glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
      glUseProgram(0);
    }




  };
}


#endif