#ifndef PRJ_INCLUDE_EVIRONMENT_H
#define PRJ_INCLUDE_EVIRONMENT_H

#include <Wall.h>
#include <Tile.h>
#include <glm/glm/glm.hpp>


class Environment {

  class Chunk {

    glm::vec3 pos_;
  
    Wall wallsData_[81];
    Tile tilesData_[81];

  };


};


#endif