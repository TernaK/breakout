//
//  SpriteRenderer.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/4/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp

#include "Shader.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class SpriteRenderer
{
public:
  /* constructor destructor */
  SpriteRenderer(const Shader& shader);
  ~SpriteRenderer();
  
  /* methods */
  void draw(const Texture2D& texture,
                  glm::vec2 position,
                  glm::vec2 size = glm::vec2(10, 10),
                  GLfloat rotate = 0.0f,
                  glm::vec3 color = glm::vec3(1.0f));
  
private:
  /* members */
  Shader shader;
  GLuint VAO;
  
  /* methods */
  void init();
};

#endif /* SpriteRenderer_hpp */
