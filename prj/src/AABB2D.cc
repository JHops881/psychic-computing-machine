#include "../include/AABB2D.h"

AABB2D::AABB2D(glm::vec2 A, glm::vec2 B)
  : A(A), B(B)
{

}


bool AABB2D::IsColliding(const AABB2D *other)
{
  // other is to the left
  if (other->B.x <= this->A.x) {
    return false;
  } 
  // other is to the right
  if (this->B.x <= other->A.x) {
    return false;
  }
  // other is above
  if (this->A.y <= other->B.y) {
    return false;
  }
  // other is below
  if (other->A.y <= this->B.y) {
    return false;
  }
  return true;
}

FaceAABB2D AABB2D::WillCollide(const AABB2D* other, const glm::vec2 step, 
                               glm::vec2* &out)
{
  
  float gap;  // signed distance between this and other
  float shift;  // orthoganal to gap and proportional to shift

  // leftward collision
  gap = other->A.x - this->B.x;
  if (0 < gap && gap < step.x) 
  {
    shift = gap / step.x * step.y;
    if (other->B.y < this->A.y + shift && this->B.y + shift < other->A.y) 
    {
      out = new glm::vec2(gap, shift);
      return RIGHT_FACE;
    }
  }

  // rightward collision
  gap = other->B.x - this->A.x;
  if (gap < 0 && step.x < gap)
  {
    shift = gap / step.x * step.y;
    if (other->B.y < this->A.y + shift && this->B.y + shift < other->A.y)
    {
      out = new glm::vec2(gap, shift);
      return LEFT_FACE;
    }
  }

  // upward collision
  gap = other->B.y - this->A.y;
  if (0 < gap && gap < step.y)
  {
    shift = gap / step.y * step.x;
    if (other->A.x < this->B.x + shift && this->A.x + shift < other->B.x)
    {
      out = new glm::vec2(gap, shift);
      return BOT_FACE;
    }
  }

  // downward collision
  gap = other->A.y - this->B.y;
  if (gap < 0 && step.y < gap)
  {
    shift = gap / step.y * step.x;
    if (other->A.x < this->B.x + shift && this->A.x + shift < other->B.x)
    {
      out = new glm::vec2(gap, shift);
      return TOP_FACE;
    }
  }

  return NO_FACE;
}

glm::vec2 AABB2D::GetA()
{
  return this->A;
}

glm::vec2 AABB2D::GetB()
{
  return this->B;
}