#include <stdexcept>

#include <AABB2D.h>

AABB::AABB(glm::vec2 A, glm::vec2 B) noexcept(std::invalid_argument)
  : A(A), B(B)
{
  if (not this->VerifyState()) {
    throw std::invalid_argument(std::format("Invalid verticies for AABB. A={} B={}", 
      this->GetA(), this->GetB()))
  }
}


bool AABB::IsColliding(const AABB *other)
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

FaceAABB AABB::WillCollide(const AABB* other, const glm::vec2 step, 
                               glm::vec2 &out)
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
      out = glm::vec2(gap, shift);
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
      out = glm::vec2(gap, shift);
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
      out = glm::vec2(gap, shift);
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
      out = glm::vec2(gap, shift);
      return TOP_FACE;
    }
  }

  return NO_FACE;
}

glm::vec2 AABB::GetA()
{
  return this->A;
}

glm::vec2 AABB::GetB()
{
  return this->B;
}

void AABB::SetA(const glm::vec2 &a)
{
  this->A = a;
}

bool AABB::VerifyState()
{
  return this->A.x < this->B.x && this->B.y < this->A.y;
}
