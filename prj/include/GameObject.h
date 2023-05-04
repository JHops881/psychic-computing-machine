#ifndef PRJ_INCLUDE_GAMEOBJECT_H
#define PRJ_INCLUDE_GAMEOBJECT_H


#include <iostream>
#include <vector>


#include <glm/glm/glm.hpp>

#include <shader_obj.h>
#include <models.h>



class GameObject {

protected: // related to the graphics component


  ShaderProgram& shaderProgram_;


protected: // related to existing existing in 3d space

  glm::vec3    pos_;
  float        rotation_;



protected:

  GameObject(glm::vec3 position, float rotation, ShaderProgram& shaderProgram) 
    : pos_(position), rotation_(rotation), shaderProgram_(shaderProgram) {

  }




  // every object in the game must be able to be displayed on the screen
  virtual void draw() = 0;




};


#endif