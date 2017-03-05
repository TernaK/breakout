//
//  GameObject.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/4/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Shader.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "SpriteRenderer.hpp"

class GameObject
{
public:
  // Object state
  glm::vec2   position, size, velocity;
  glm::vec3   color;
  GLfloat     rotation;
  GLboolean   isSolid;
  GLboolean   destroyed;
  // Render state
  Texture2D   sprite;
  // Constructor(s)
  GameObject();
  GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
  // Draw sprite
  virtual void draw(SpriteRenderer &renderer);
};

#endif /* GameObject_hpp */
