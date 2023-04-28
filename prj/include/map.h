#ifndef MAP_H_
#define MAP_H_



//#include <iostream>
//#include <vector>
//#include <cmath>
#include <unordered_map>

//#include <glad/glad.h>


#include <glm/glm/glm.hpp>
//#include <glm/glm/gtc/matrix_transform.hpp>

#include "models.h"
#include "shader_obj.h"






class map {

  class Wall {

    glm::vec3              pos_;
    models::WallModel&     model_;
    shader_obj::Shader&    shader_;


  public:
    
    Wall(glm::vec3 pos, models::WallModel& model, shader_obj::Shader shader) 
      : pos_(pos), model_(model), shader_(shader) {
      

    }

    void Draw() {

      model_.Select();

      glm::mat4 model_mat = glm::mat4(1.0f);
      model_mat = glm::translate(model_mat, pos_);
      
      shader_.SetMat4fv("model", model_mat);

      shader_.use();
      glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
    }


  };

// class map {

  Wall visible_walls_ [225];
  std::unordered_map<int[2], Wall> all_walls_;

};




#endif