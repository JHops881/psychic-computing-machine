#ifndef PRJ_INCLUDE_GAMEOBJECT_H
#define PRJ_INCLUDE_GAMEOBJECT_H


#include <iostream>
#include <vector>


#include <glm/glm/glm.hpp>

#include <shader_obj.h>
#include <models.h>



class GameObject {

protected: // related to the graphics component

public:

  static Quad2D*    quadModel_;
  static Cuboid3D*  cuboidModel_;

protected:

  ShaderProgram&    shaderProgram_;



protected: // related to existing existing in 3d space

  glm::vec3    pos_;
  float        rotation_;



protected:

  GameObject(glm::vec3 position, float rotation, ShaderProgram& shaderProgram) 
    : pos_(position), rotation_(rotation), shaderProgram_(shaderProgram) {

  }




  // every object in the game must be able to be displayed on the screen
  virtual void draw() = 0;


public:

  static void configureModels(Cuboid3D* cubeptr, Quad2D* quadptr) {
    quadModel_ = quadptr;
    cuboidModel_ = cubeptr;
  }


};

#endif
