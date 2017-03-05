//
//  BallObject.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/5/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef BallObject_hpp
#define BallObject_hpp

#include "GameObject.hpp"

class BallObject : public GameObject
{
public:
  // Ball state
  GLfloat   radius;
  GLboolean stuck;
  
  
  BallObject();
  BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
  
  glm::vec2 move(GLfloat dt, GLuint window_width);
  void      reset(glm::vec2 position, glm::vec2 velocity);
};

#endif /* BallObject_hpp */
