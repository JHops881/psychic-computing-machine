#ifndef PRJ_INCLUDE_PROJECTILE_H
#define PRJ_INCLUDE_PROJECTILE_H

#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>


#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <GameObject.h>
#include <models.h>
#include <shader_obj.h>
#include <player.h>



class Projectile : GameObject {

  Quad2D& model_ = *g_QUAD2D;



  glm::vec3           velocity_ = glm::vec3(0.0f, 0.0f, 0.0f); // below*
  static const int    lifetime_ = 120; // measured in FixedUpdate()s

  // * velocity_ is initialized to zero, but immedialty changes in the
  // constructor to be a unit vector in the direction that the player
  // shot in. it is then added to the pos_ of the projectile every
  // FixedUpdate() in Move() to make the projectile travel through space

  

public:

  bool            isDead_ = false; // when this is true it is deleted
  int             age_ = 0; // measured in FixedUpdate()s


public:


  Projectile(Player& player, ShaderProgram& shaderProgram) 
    : GameObject(player.getPos(), 0.0f, shaderProgram) {

    pos_ = player.getPos();
    rotation_ = player.getRotation();

    constexpr float NDIR = glm::radians(90.0f);

    velocity_.x = cos(rotation_ + NDIR) / 5.0f;
    velocity_.y = sin(rotation_ + NDIR) / 5.0f;

  }



  void update() {

    
    if (age_ < lifetime_) {
      pos_ += velocity_;
    }
    else {
      isDead_ = true;
    }
    /*else {
      projectiles_[i].age_++;
    }*/
    



  }




  // called for every projectile for a player in 
  // player::Player.DrawProjectiles() which is called every frame
  // in Render()
  void draw() {


    // since model_ is a std::reference_wrapper, you have to use
    // .get() to "get" to to access the object it is wrapping
    model_.select();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, pos_);
    modelMatrix = glm::rotate(modelMatrix, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
    shaderProgram_.setMat4fv("model", modelMatrix);

    shaderProgram_.select();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  }


  // used to update the postion of a projectile
  void move() {

    

  }



};


#endif