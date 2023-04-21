#ifndef AABB2D_H
#define AABB2D_H

#include <glm/glm/glm.hpp>

class AABB2D {
public:
  AABB2D(glm::vec2 x, glm::vec2 y);
private:
  glm::vec2 x; 
  glm::vec2 y; 
};

#endif // !AABB2D_H
