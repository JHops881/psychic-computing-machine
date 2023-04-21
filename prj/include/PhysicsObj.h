#ifndef PHYSICS_OBJ_H
#define PHYSICS_OBJ_H

#include "AABB2D.h"
#include <glm/glm/glm.hpp>

/// <summary>
/// A 2d physics object 
/// </summary>
typedef struct {


  AABB *hit_boxes;

  float mass;
  float surface_area;

  glm::vec2 velocity;
  glm::vec2 position;

} PhysicsObj;


#endif // !PHYSICS_OBJ_H