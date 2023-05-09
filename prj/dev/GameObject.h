
#include <glm/glm.h>

class GameObject {

protected:
  glm::vec2 pos_;
  glm::vec2 vel_;
  float mass_;
  float sarea_;

  Shader *shader_;
  Model *model_;
  Texture *texture_;

public:

  /// @brief A game object can be placed in the game envirionment and
  ///        drawn to the screen
  /// @param pos the 2d coordinated of this object
  /// @param vel the 2d velocity vector of this object, usually 0,0
  /// @param mass the mass in killograms
  /// @param sarea the surface area in m^2
  /// @param shader 
  /// @param model the object's form in 2d or 3d
  /// @param texture the texture to map onto the surface of this object
  GameObject(glm::vec2 pos, glm::vec2 vel, float mass, float sarea, 
             Shader *shader, Model *model, Texture *texture) 
  : pos_(pos), vel_(vel), mass_(mass), sarea_(sarea), shader_(shader), 
    model_(model), texture_(texture)
  {}

  inline float get_x() const { return this->pos_.x; }
  inline float get_y() const { return this->pos_.y; }
};