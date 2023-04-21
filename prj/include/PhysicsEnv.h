#ifndef PHYSICS_ENV_H
#define PHYSICS_ENV_H

#include <vector>

#include "PhysicsObj.h"


class PhysicsEnv {



public:
  PhysicsEnv();
  ~PhysicsEnv();

  bool add(PhysicsObj* obj);

  void tick();

private:

  std::vector<PhysicsObj> objs;

};


#endif // !PHYSICS_ENV_H
