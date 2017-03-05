//
//  GameObject.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/4/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "GameObject.hpp"


GameObject::GameObject()
{
  
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
{
  this->position = pos;
  this->size = size;
  this->sprite = sprite;
  this->color = color;
  this->velocity = velocity;
  this->isSolid = false;
  this->destroyed = false;
}

// Draw sprite
void GameObject::draw(SpriteRenderer &renderer)
{
  renderer.draw(this->sprite, this->position, this->size, this->rotation, this->color);
}
