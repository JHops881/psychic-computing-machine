#include <GameObject.h>
#include <memory>

enum Team {
  PLAYER,
  HOSTILE,
  PASSIVE
};


class Mob : GameObject {
  
  uint64_t age_ {};
  uint64_t maxAge_ {};

  uint16_t currentHealth_ {};
  uint16_t maxHealth_ {};
  short def_ {}:
  short atk_ {};
  short spd_ {};
  short dex_ {};
  // short wis_;
  short vit_ {};

  std::unique_ptr<Invetory> inv_ {nullptr};

  ///@brief A mob is an agent in our game
  ///
  ///@param pos position of the mob in 2d space
  ///@param vel velocity of the mob in 2d space
  ///@param mass kilogams
  ///@param sarea surface area in m^2
  ///@param shader 
  ///@param model 
  ///@param texture 
  ///@param maxAge 0 for never die, >0 for die at t=maxAge
  ///@param hp max hit points of the mob
  ///@param def 
  ///@param atk 
  ///@param spd 
  ///@param dex 
  ///@param vit 
  Mob(glm::vec2 pos, glm::vec2 vel, float mass, float sarea, Shader *shader,
      Model *model, Texture *texture, uint64_t maxAge, uint16_t hp, short def,
      short atk, short spd, short dex, short vit)
  : GameObject(pos, vel, mass, sarea, shader, model, texture) maxAge_(maxAge),
    currentHealth_(hp), maxHealth_(hp), def_(def), atk_(atk), spd_(spd), 
    dex_(dex), vit_(vit) 
  {
    this->inv_ = std::unique_ptr<Invetory>(new Invetory());
  };

  static Mob SpawnZombie() {
    // TODO
  } 




};
