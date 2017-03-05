//
//  BallObject.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/5/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "BallObject.hpp"


BallObject::BallObject()
: GameObject()
{
  this->radius = 12.5;
  this->stuck = true;
}

BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
: GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity)
{
  this->radius = radius;
  this->stuck = true;
}

glm::vec2 BallObject::move(GLfloat dt, GLuint window_width)
{
  // If not stuck to player board
  if (!this->stuck)
  {
    // Move the ball
    this->position += this->velocity * dt;
    // Check if outside window bounds; if so, reverse velocity and restore at correct position
    if (this->position.x <= 0.0f)
    {
      this->velocity.x = -this->velocity.x;
      this->position.x = 0.0f;
    }
    else if (this->position.x + this->size.x >= window_width)
    {
      this->velocity.x = -this->velocity.x;
      this->position.x = window_width - this->size.x;
    }
    if (this->position.y <= 0.0f)
    {
      this->velocity.y = -this->velocity.y;
      this->position.y = 0.0f;
    }
    
  }
  return this->position;
}

void BallObject::reset(glm::vec2 position, glm::vec2 velocity)
{
  this->velocity = velocity;
  this->position = position;
  
  this->stuck = true;
}
