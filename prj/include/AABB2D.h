#ifndef AABB2D_H
#define AABB2D_H

#include <glm/glm/glm.hpp>

typedef enum {
  NO_FACE, LEFT_FACE, RIGHT_FACE, TOP_FACE, BOT_FACE
} FaceAABB;

class AABB 
{
public:

  /// <summary>
  /// Create a new box 
  /// </summary>
  /// 
  /// <param name="A">upper left corner</param>
  /// <param name="B">lower right corner</param>
  AABB(glm::vec2 A, glm::vec2 B);

  /// <summary>
  /// Check if two boxes are coliding (overlapping)
  /// </summary>
  /// <param name="other">The box to check against</param>
  /// <returns>true if the two boxes are coliding, false otherwise</returns>
  bool IsColliding(const AABB *other);

  /// <summary>
  /// Check if this box will collide with other box given a velocity
  /// </summary>
  /// <param name="other">box to collide with</param>
  /// <param name="step">the movement vector of this</param>
  /// <param name="out">maximum seperating vector for collision</param>
  /// <returns>the face on which the collision happened</returns>
  FaceAABB WillCollide(const AABB* other, const glm::vec2 step, glm::vec2 &out);

  /// <summary>
  /// Get the upper left corner of this box
  /// </summary>
  /// <returns>upper left corner</returns>
  glm::vec2 GetA();

  /// <summary>
  /// Get the lower right corner of this object
  /// </summary>
  /// <returns></returns>
  glm::vec2 GetB();

  //! @brief set the upper left corner of this box
  //! 
  //! @param a the upper left corner
  void SetA(const glm::vec2& a);

  /// <summary>
  /// Verify that the internal state of this AABB is valid
  /// </summary>
  /// <returns>true if valid, false otherwise</returns>
  bool VerifyState();

private:
  glm::vec2 A; 
  glm::vec2 B; 
};

#endif // !AABB2D_H
